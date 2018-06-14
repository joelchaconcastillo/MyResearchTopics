#ifndef __EVOLUTION_H_
#define __EVOLUTION_H_

#include "global.h"
#include "recomb.h"
#include "common.h"
#include "individual.h"


class CMOEAD
{

public:
	CMOEAD();
	virtual ~CMOEAD();

	void init_neighbourhood();               // calculate the neighbourhood of each subproblem
	void init_population();                  // initialize the population

	void load_parameter();

	void update_reference(CIndividual &ind);                 // update ideal point which is used in Tchebycheff or NBI method
	void update_problem(CIndividual &ind, int &id, int &type); // update current solutions in the neighbourhood

	void evol_population();                                      // DE-based recombination
	void mate_selection(vector<int> &list, int cid, int size, int type);  // select mating parents

	// execute MOEAD
	void exec_emo(int run);

	void save_front(char savefilename[1024]);       // save the pareto front into files
	void save_pos(char savefilename[1024]);

	void tour_selection(int depth, vector<int> &selected);
	void comp_utility();
	double regularization_nearest(int k, CIndividual &ind);

    vector <CSubproblem> population;
	vector <double>      utility;

	void operator=(const CMOEAD &moea);

public:

	// algorithm parameters
    int		max_gen, curren_gen;       //  the maximal number of generations
	int     pops;          //  the population size
    int	    niche;         //  the neighborhood size
	int     limit;         //  the maximal number of solutions replaced
	double  prob;          //  the neighboring selection probability
	double  rate;          //  the differential rate between solutions

	int     nfes;          //  the number of function evluations

};

CMOEAD::CMOEAD()
{

}

CMOEAD::~CMOEAD()
{

}

void CMOEAD::init_population()
{

	idealpoint = vector<double>(nobj, 1.0e+30);
	utility    = vector<double>(pops, 1.0);

	char filename[1024];
	// Read weight vectors from a data file
	//sprintf(filename,"/home/joel.chacon/Chacon/Tesis/MOEA-D_Diversity/Code_CEC09/moead_based_diversity_DE/ParameterSetting/Weight/W%dD_%d.dat", nobj, pops);
	sprintf(filename,"ParameterSetting/Weight/W%dD_%d.dat", nobj, pops);
	std::ifstream readf(filename);

    for(int i=0; i<pops; i++)
	{

		CSubproblem sub;

		// Randomize and evaluate solution
		sub.indiv.rnd_init();
		sub.indiv.obj_eval();

		sub.saved = sub.indiv;

		// Initialize the reference point
		update_reference(sub.indiv);

		// Load weight vectors
		for(int j=0; j<nobj; j++)
		{
		    readf>>sub.namda[j];
		}

		// Save in the population
		population.push_back(sub);
		nfes++;
	}

	readf.close( );
}

void CMOEAD::operator=(const CMOEAD &alg)
{
	//population = alg.population;
}

void CMOEAD::init_neighbourhood()
{
    vector<double> dist   = vector<double>(pops, 0);
	vector<int>    indx   = vector<int>(pops, 0);

	for(int i=0; i<pops; i++)
	{
		// calculate the distances based on weight vectors
		for(int j=0; j<pops; j++)
		{
		    dist[j]    = dist_vector(population[i].namda,population[j].namda);
			indx[j]  = j;
		}

		// find 'niche' nearest neighboring subproblems
		minfastsort(dist,indx,population.size(),niche);

		// save the indexes of the nearest 'niche' neighboring weight vectors
		for(int k=0; k<niche; k++)
		{
			population[i].table.push_back(indx[k]);
		}

	}
    dist.clear();
	indx.clear();
}

void CMOEAD::tour_selection(int depth, vector<int> &selected)
{
	// selection based on utility
	vector<int> candidate;
	for(int k=0;    k<nobj; k++)    selected.push_back(k);   // select first m weights
	for(int n=nobj; n<pops; n++)    candidate.push_back(n);  // set of unselected weights

	while(selected.size()<int(pops/5.0))
	{
	    int best_idd = int(rnd_uni(&rnd_uni_init)*candidate.size()), i2;
		int best_sub = candidate[best_idd], s2;
		for(int i=1; i<depth; i++)
		{
		    i2  = int(rnd_uni(&rnd_uni_init)*candidate.size());
			s2  = candidate[i2];
			if(utility[s2]>utility[best_sub])
			{
				best_idd = i2;
			    best_sub = s2;
			}
		}
		selected.push_back(best_sub);
		candidate.erase(candidate.begin()+best_idd);
	}
}

void CMOEAD::comp_utility()
{
	double f1, f2, uti, delta;
    for(int n=0; n<pops; n++)
	{
		f1 = fitnessfunction(population[n].indiv.y_obj, population[n].namda);
		f2 = fitnessfunction(population[n].saved.y_obj, population[n].namda);
		delta = f2 - f1;
        if(delta>0.001)  utility[n] = 1.0;
		else{
            uti        = 0.95*(1.0+delta/0.001)*utility[n];
			utility[n] = uti<1.0?uti:1.0;
		}
        population[n].saved = population[n].indiv;
	}
}

void CMOEAD::update_problem(CIndividual &indiv, int &id, int &type)
{
	// indiv: child solution
	// id:   the id of current subproblem
	// type: update solutions in - neighborhood (1) or whole population (otherwise)
	int size, time = 0;
	if(type==1)	size = population[id].table.size();  // from neighborhood
	else        size = population.size();            // from whole population

	// a random order to update
	std::vector<int> perm(std::vector<int>(size, 0));
	for(int k=0; k<size; k++) perm[k] = k;
	random_shuffle(perm.begin(), perm.end());


    for(int i=0; i<size; i++)
	{
		// Pick a subproblem to update
		int k;
		if(type==1) k = population[id].table[perm[i]];
		else        k = perm[i];

		// calculate the values of objective function regarding the current subproblem
		double f1, f2;
		f1 = fitnessfunction(population[k].indiv.y_obj, population[k].namda);
		f2 = fitnessfunction(indiv.y_obj, population[k].namda);

   		double factor = 1.0-((double)curren_gen)/(max_gen);
		factor=max(factor,0.0);
		//Compute nearest objective vector...
	        f1 = (1.0-factor)*f1 - factor*regularization_nearest(k,  population[k].indiv);
	        f2 = (1.0-factor)*f2 - factor*regularization_nearest(k,  indiv);
		//f1 = -10.0*regularization_nearest(k,  population[k].indiv);
	        //f2 = -10.0*regularization_nearest(k,  indiv);
		if(f2<f1)
		{
			population[k].indiv = indiv;
			time++;
		}
		// the maximal number of solutions updated is not allowed to exceed 'limit'
		if(time>=limit)
		{
			return;
		}
	}
	perm.clear();
}
//Compute the nearest individual discarding the k-index
double CMOEAD::regularization_nearest(int k, CIndividual &ind)
{
    double maxd = INFINITY;
    for(int i =  0 ; i  < population.size(); i++)
   {
	if(k==i) continue;
	double dist = dist_vector(population[i].indiv.y_obj, ind.y_obj);
	maxd = min(dist, maxd);
   }
   return maxd;
}
void CMOEAD::update_reference(CIndividual &ind)
{
	//ind: child solution
	for(int n=0; n<nobj; n++)
	{
		if(ind.y_obj[n]<idealpoint[n])
		{
			idealpoint[n] = ind.y_obj[n];
		}
	}
}

void CMOEAD::mate_selection(vector<int> &list, int cid, int size, int type){
	// list : the set of the indexes of selected mating parents
	// cid  : the id of current subproblem
	// size : the number of selected mating parents
	// type : 1 - neighborhood; otherwise - whole population
	int ss   = population[cid].table.size(), id, parent;
    while(list.size()<size)
	{
		if(type==1){
		    id      = int(ss*rnd_uni(&rnd_uni_init));
			parent  = population[cid].table[id];
		}
		else
			parent  = int(population.size()*rnd_uni(&rnd_uni_init));

		// avoid the repeated selection
		bool flag = true;
		for(int i=0; i<list.size(); i++)
		{
			if(list[i]==parent) // parent is in the list
			{
				flag = false;
				break;
			}
		}

		if(flag) list.push_back(parent);
	}
}

void CMOEAD::evol_population()
{

	// random order of subproblems at each generation
	//vector<int> order(vector<int>(pops,0));
	//for(int i=0; i<pops; i++)  order[i] = i;
	//random_shuffle(order.begin(), order.end());

	///vector<int> order;	this->tour_selection(10, order);
	vector<int> order;
	for(int i = 0; i < pops; i++) order.push_back(i);
	

    for(int sub=0; sub<order.size(); sub++)
	{

		int c_sub = order[sub];    // random order
		//  printf("%d ", c_sub);

		int type;
        double rnd = rnd_uni(&rnd_uni_init);

		// mating selection based on probability
		if(rnd<prob)     type = 1;   // from neighborhood
		else             type = 2;   // from population

		// select the indexes of mating parents
		vector<int> plist;
		mate_selection(plist, c_sub, 2, type);  // neighborhood selection


		// produce a child solution
		CIndividual child1, child2;
		double rate2 = 0.5; //rate + 0.25*(rnd_uni(&rnd_uni_init) - 0.5);
		diff_evo_xoverB(population[c_sub].indiv,population[plist[0]].indiv,population[plist[1]].indiv, child1, rate2);
		//real_sbx_xoverB(population[plist[0]].indiv,population[plist[1]].indiv, child);
		//real_sbx_hybrid(population[plist[0]].indiv,population[plist[1]].indiv, child1, child2, max_gen, curren_gen);
//		real_sbx_xoverA(population[plist[0]].indiv,population[plist[1]].indiv, child1, child2);

		plist.clear();

		// apply polynomial mutation
		realmutation(child1, 1.0/nvar);
		//realmutation(child2, 1.0/nvar);

		// evaluate the child solution
		child1.obj_eval();
		//child2.obj_eval();

		// update the reference points and other solutions in the neighborhood or the whole population
		update_reference(child1);
		//update_reference(child2);
		update_problem(child1, c_sub, type);
		//update_problem(child2, c_sub, type);

		nfes++;
	}

	//getchar();

}


void CMOEAD::exec_emo(int run)
{
    char filename[1024];
	seed =run ;// (seed + 23)%1377;
	rnd_uni_init = -(long)seed;

	// initialization
	nfes      = 0;

	init_population();
    init_neighbourhood();

	int gen = 5;

    //sprintf(filename,"/home/joel.chacon/Chacon/Tesis/MOEA-D_Diversity/Code_CEC09/moead_based_diversity_DE/POF/POF_MOEAD_%s_RUN%d_G%d_%d.dat",strTestInstance,run, gen, nobj);

    sprintf(filename,"POF/POF_MOEAD_%s_RUN%d_G%d_%d.dat",strTestInstance,run, gen, nobj);

	// evolution
	for(int gen=2; gen<=max_gen; gen++)
	{
		curren_gen = gen;
		evol_population();
		if(gen%1000 == 0) cout << "Generation.. "<<gen <<endl;
		if(gen%100 == 0)
		{
		   sprintf(filename,"POS/POS_MOEAD_%s_RUN%d_seed_%d_%d.dat",strTestInstance,run, seed, nobj);
		   save_pos(filename);
		   //sprintf(filename,"/home/joel.chacon/Chacon/Tesis/MOEA-D_Diversity/Code_CEC09/moead_based_diversity_DE/POF/POF_MOEAD_%s_RUN%d_seed_%d_%d.dat",strTestInstance,run, seed, nobj);
		   sprintf(filename,"POF/POF_MOEAD_%s_RUN%d_seed_%d_%d.dat",strTestInstance,run, seed, nobj);
		   save_front(filename);

		}

	}
		   //sprintf(filename,"/home/joel.chacon/Chacon/Tesis/MOEA-D_Diversity/Code_CEC09/moead_based_diversity_DE/POS/POS_MOEAD_%s_RUN%d_seed_%d_%d.dat",strTestInstance,run, seed, nobj);
		   sprintf(filename,"POS/POS_MOEAD_%s_RUN%d_seed_%d_%d.dat",strTestInstance,run, seed, nobj);
		   save_pos(filename);
		   //sprintf(filename,"/home/joel.chacon/Chacon/Tesis/MOEA-D_Diversity/Code_CEC09/moead_based_diversity_DE/POF/POF_MOEAD_%s_RUN%d_seed_%d_%d.dat",strTestInstance,run, seed, nobj);
		   sprintf(filename,"POF/POF_MOEAD_%s_RUN%d_seed_%d_%d.dat",strTestInstance,run, seed, nobj);
		   save_front(filename);

	//printf("%d generations used \n", gen);

	population.clear();
	idealpoint.clear();

}

void CMOEAD::load_parameter()
{
	char filename[1024];

	sprintf(filename,"ParameterSetting/%s.txt", strTestInstance);

	char temp[1024];
	std::ifstream readf(filename);
	readf.getline(temp, 1024);
	//puts(temp);

	readf>>pops;
	readf>>max_gen;
	readf>>niche;
	readf>>limit;
	readf>>prob;
	readf>>rate;
	max_gen=250000;
	niche=10;//##############TEMPORAL!!!!!!!!!!!
	printf("\n Parameter Setting in MOEA/D \n");
	printf("\n pop %d, gen %d, niche %d, limit %d, prob %f, rate %f\n\n", pops, max_gen, niche, limit, prob, rate);

	readf.close();
}


void CMOEAD::save_front(char saveFilename[1024])
{
    std::fstream fout;
	//fout.open(saveFilename,std::ios::out);
	fout.open(saveFilename, fstream::app|fstream::out);
	for(int n=0; n<pops; n++)
	{
		for(int k=0;k<nobj;k++)
			fout<<population[n].indiv.y_obj[k]<<"  ";
		fout<<"\n";
	}
	fout.close();
}

void CMOEAD::save_pos(char saveFilename[1024])
{
    std::fstream fout;
	//fout.open(saveFilename,std::ios::out);
	fout.open(saveFilename, fstream::app|fstream::out);
	for(int n=0; n<pops; n++)
	{
		for(int k=0;k<nvar;k++)
			fout<<population[n].indiv.x_var[k]<<"  ";
		fout<<"\n";
	}
	fout.close();
}



#endif
