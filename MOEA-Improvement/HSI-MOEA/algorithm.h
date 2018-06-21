#ifndef __EVOLUTION_H_
#define __EVOLUTION_H_

#include <queue>
#include <iomanip>
#include <cfloat>
#include "global.h"
#include "recomb.h"
#include "common.h"
#include "individual.h"

class MOEA
{

public:
	MOEA();
	virtual ~MOEA();

	void init_population();                  // initialize the population

	void load_parameter();

	void update_reference(CIndividual &ind);                 // update ideal point which is used in Tchebycheff or NBI method
	void evol_population();                                      // DE-based recombination
	// execute MOEAD
	void exec_emo(int run);

	void save_front(char savefilename[1024]);       // save the pareto front into files
	void save_pos(char savefilename[1024]);

	double distance( vector<double> &a, vector<double> &b);
	double distance_improvement( vector<double> &reference, vector<double> &current);
	vector <CSubproblem> population;
	vector<CSubproblem> child_pop;	// memory solutions
        void improvement_selection(vector<CSubproblem> &offspring, vector<CSubproblem> &parents);
	void operator=(const MOEA &moea);

public:

	// algorithm parameters
	int		max_gen, curren_gen;       //  the maximal number of generations and current gen
	int     pops;          //  the population size
	double  prob;          //  the neighboring selection probability
	double  rate;          //  the differential rate between solutions
	int     nfes;          //  the number of function evluations

};

MOEA::MOEA()
{

}

MOEA::~MOEA()
{

}

double MOEA::distance_improvement( vector<double> &reference, vector<double> &current)
{
	double dist = 0 ;
   for(int i = 0; i < reference.size(); i++)
	{
	   if(current[i] < reference[i])
	      dist += (current[i] - reference[i])*(current[i] - reference[i]);
	   else
	      dist += 0.001*(reference[i] - current[i])*(reference[i] - current[i]);
	}
   return sqrt(dist);

}
double MOEA::distance( vector<double> &a, vector<double> &b)
{
	double dist = 0 ;
   for(int i = 0; i < a.size(); i++)
	{
	   double factor = (a[i]-b[i])/(vuppBound[i]-vlowBound[i]);
	   dist += factor*factor;
	}
   return sqrt(dist);
}
void MOEA::init_population()
{

	idealpoint = vector<double>(nobj, 1.0e+30);

	char filename[1024];
	// Read weight vectors from a data file
//	sprintf(filename,"/home/joel.chacon/Current/MyResearchTopics/MOEA-D-Diversity/MOEAD-DE/vsd-moead-opt/ParameterSetting/Weight/W%dD_%d.dat", nobj, pops);
	//sprintf(filename,"ParameterSetting/Weight/W%dD_%d.dat", nobj, pops);
//	std::ifstream readf(filename);

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
//		for(int j=0; j<nobj; j++)
//		{
//		    readf>>sub.namda[j];
//		}
	//	printf("\n"); getchar();

		// Save in the population
		population.push_back(sub);
		child_pop.push_back(sub);
		nfes++;
	}
//	readf.close( );
}

void MOEA::operator=(const MOEA &alg)
{
	//population = alg.population;
}
void MOEA::update_reference(CIndividual &ind)
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
void MOEA::evol_population()
{

	///vector<int> order;	this->tour_selection(10, order);
	vector<int> order;
	for(int i = 0; i < pops; i++) order.push_back(i);
	

    for(int sub=0; sub<order.size(); sub++)
	{

		int c_sub = order[sub];    // random order

		int type;
		double rnd1 = int(rnd_uni(&rnd_uni_init)*pops) ;//;rnd_uni(&rnd_uni_init);
		double rnd2 = int(rnd_uni(&rnd_uni_init)*pops) ;//;rnd_uni(&rnd_uni_init);
		while(rnd2 !=rnd1)
		  rnd2 = int(rnd_uni(&rnd_uni_init)*pops);
		
	

		// select the indexes of mating parents
		vector<int> plist;
		// produce a child solution
		CIndividual child1, child2;
		double rate2 = 0.5; //rate + 0.25*(rnd_uni(&rnd_uni_init) - 0.5);
		//double rate2 = rate + 0.25*(rnd_uni(&rnd_uni_init) - 0.5);
		diff_evo_xoverB(population[c_sub].indiv,population[rnd1].indiv,population[rnd2].indiv, child1, rate2);

		//real_sbx_xoverA(population[plist[0]].indiv, population[plist[1]].indiv, child1, child2);
		//real_sbx_hybrid(population[plist[0]].indiv,population[plist[1]].indiv, child1, child2, max_gen, curren_gen);
		
		plist.clear();

		// apply polynomial mutation
		realmutation(child1, 1.0/nvar);
	//	realmutation(child2, 1.0/nvar);
		
		// repair method
		//repait
		// evaluate the child solution
		child1.obj_eval();
	//	child2.obj_eval();

		// update the reference points and other solutions in the neighborhood or the whole population
		update_reference(child1);
	//	update_reference(child2);

		child_pop[c_sub].indiv = child1;
		nfes++;
	}
	improvement_selection(child_pop, population);
}

void MOEA::improvement_selection(vector<CSubproblem> &offspring, vector<CSubproblem> &parents)
{
   vector< CIndividual> reference, candidates(offspring.size() + parents.size());

   for(int i = 0 ; i < offspring.size(); i++) candidates.push_back(offspring[i].indiv);
   for(int i = 0 ; i < parents.size(); i++) candidates.push_back(parents[i].indiv);


   vector<double> sumfit (candidates.size(), 0.0);
   //select the m reference individuals..
   for(int i = 0 ; i < candidates.size(); i++)
	for(int j = 0; j < nobj; j++) sumfit[i]+= candidates[i].y_obj[j];
	
	for(int j = 0; j < nobj; j++)
	{
	  double minf=DBL_MAX;
	  int indexb=-1;
   	  for(int i = 0 ; i < candidates.size(); i++)
	  {
	   double extremefitness = abs(candidates[i].y_obj[j] - idealpoint[j]) + 0.001*sumfit[i];
//	   double extremefitness = abs(candidates[i].y_obj[j] );// + 0.001*sumfit[i];
	   if( extremefitness < minf )
	   {
		minf = extremefitness;
		indexb = i;
	   }
	  }
	    reference.push_back(candidates[indexb]);
	    iter_swap(candidates.begin()+indexb, candidates.end()-1);
	    candidates.pop_back();
	}
  while(reference.size() < pops) 
  {
	double maxi = DBL_MIN;
	int indexi=-1;
	for(int i = 0; i < candidates.size(); i++)
	{
	   double mini = DBL_MAX;
	   for(int j = 0; j < reference.size(); j++)
		mini = min(mini, distance_improvement(reference[j].y_obj, candidates[i].y_obj));
		//mini = min(mini, distance(reference[j].y_obj, candidates[i].y_obj));
	  if( maxi < mini  ) 
	   {
		indexi = i;
		maxi = mini;
	    }
	}
	reference.push_back(candidates[indexi]);
	iter_swap(candidates.begin()+indexi, candidates.end()-1);
	candidates.pop_back();
  }
   for(int i = 0; i < parents.size(); i++)   
   parents[i].indiv = reference[i]; 
}
void MOEA::exec_emo(int run)
{
    char filename1[5024];
    char filename2[5024];
		seed = run;
	seed = (seed + 23)%1377;
	rnd_uni_init = -(long)seed;

	// initialization
	nfes      = 0;
	//indexSeeds.push_back(0);
	init_population();
	//sprintf(filename1,"/home/joel.chacon/Current/MyResearchTopics/MOEA-D-Diversity/MOEAD-DE/vsd-moead-opt/POS/POS_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	sprintf(filename1,"POS/POS_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	//sprintf(filename2,"/home/joel.chacon/Current/MyResearchTopics/MOEA-D-Diversity/MOEAD-DE/vsd-moead-opt/POF/POF_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	sprintf(filename2,"POF/POF_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	for(int gen=1; gen<=max_gen; gen++)
	//while(nfes<300000)
	{
	   cout << gen <<endl;
		curren_gen = gen;	
		evol_population();
	}
		save_pos(filename1);
		save_front(filename2);

	//printf("%d generations used \n", gen);

	population.clear();
	idealpoint.clear();

}

void MOEA::load_parameter()
{
	char filename[1024];

//	sprintf(filename,"/home/joel.chacon/Current/MyResearchTopics/MOEA-D-Diversity/MOEAD-DE/vsd-moead-opt/ParameterSetting/%s.txt", strTestInstance);
//	//sprintf(filename,"ParameterSetting/%s.txt", strTestInstance);
//
//	char temp[1024];
//	std::ifstream readf(filename);
//	readf.getline(temp, 1024);
//	//puts(temp);
//
//	readf>>pops;
//	readf>>max_gen;
//	readf>>niche;
//	readf>>limit;
//	readf>>prob;
//	readf>>rate;
//	niche=10;
pops=100;
max_gen=50000/100;
prob=0.9;
rate=0.8;
//	printf("\n Parameter Setting in MOEA/D \n");
//	printf("\n pop %d, gen %d, niche %d, limit %d, prob %f, rate %f\n\n", pops, max_gen, niche, limit, prob, rate);

//	readf.close();
}


void MOEA::save_front(char saveFilename[1024])
{

    std::fstream fout;
	//fout.open(saveFilename,std::ios::out);
	fout.open(saveFilename,fstream::app|fstream::out );
	for(int n=0; n<pops; n++)
	{
	//	for(int k=0;k<nobj;k++)
	//		fout<<best[n].y_obj[k]<<"  ";
		for(int k=0;k<nobj;k++)
			fout<<population[n].indiv.y_obj[k]<<"  ";
	for(int k=0;k<nobj;k++)
			fout<<child_pop[n].indiv.y_obj[k]<<"  ";
		fout<<"\n";
	}
	fout.close();
}

void MOEA::save_pos(char saveFilename[1024])
{
    std::fstream fout;
	//fout.open(saveFilename,std::ios::out);
	fout.open(saveFilename, fstream::app|fstream::out);
	for(int n=0; n<pops; n++)
	{
		for(int k=0;k<nvar;k++)
			fout<<population[n].indiv.x_var[k] << "  ";
			//fout<<population[n].indiv.x_var[k]<< fixed << setprecision(30) << "  ";
//	  for(int k=0;k<nvar;k++)
//			fout<<best[n].x_var[k]<<"  ";
//	  for(int k=0;k<nvar;k++)
//			fout<<child_pop[n].x_var[k]<<"  ";
		fout<<"\n";
	}
	fout.close();
}



#endif
