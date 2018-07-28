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
	void update_reference_vectors();
	void evol_population();                                      // DE-based recombination
	// execute MOEAD
	void exec_emo(int run);

	void save_front(char savefilename[1024]);       // save the pareto front into files
	void save_pos(char savefilename[1024]);

	double distance( vector<double> &a, vector<double> &b);
	double distance_improvement( vector<double> &reference, vector<double> &current);
	double distance_improvement2( vector<double> &reference, vector<double> &current, double S);
	vector <CSubproblem> population;
	vector<CSubproblem> child_pop;	// memory solutions
        void improvement_selection(vector<CSubproblem> &offspring, vector<CSubproblem> &parents);
	void improvement_selection_vectors(vector<CSubproblem> &offspring, vector<CSubproblem> &parents);
	void operator=(const MOEA &moea);

public:

	// algorithm parameters
	int		max_gen, curren_gen;       //  the maximal number of generations and current gen
//	int     pops;          //  the population size
	double  prob;          //  the neighboring selection probability
	double  rate;          //  the differential rate between solutions
	int     nfes;//, max_nfes;          //  the number of function evluations

};

MOEA::MOEA()
{

}

MOEA::~MOEA()
{

}
double MOEA::distance_improvement2( vector<double> &reference, vector<double> &current, double S)
{
	double dist1 = 0.0, dist2=0.0 ;
	double teta = 1.0 - ((double)(2.0*curren_gen)/max_gen);
	teta = max(0.00001,teta );
//	teta = 0.001;

	double r1=0.0;
	double r2=0.0;
	double sum1 = 0.0;
   for(int i = 0; i < reference.size(); i++)
      {
	r1 += current[i]*current[i];
	r2 += reference[i]*reference[i];
	sum1 += current[i];
      }
	r1 = sqrt(r1);
	r2 = sqrt(r2);
   for(int i = 0; i < reference.size(); i++)
	{
		double omega1 = acos(current[i]/(r1));
		double omega2 = acos(reference[i]/(r2));
		double current_normalized = current[i];// r1*sin(omega1 + S*M_PI)/sin(S*M_PI);///(2.0*(i+1.0));// (current[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
		double current_normalized2 = r1*sin(omega1 + S*M_PI)/sin(S*M_PI);///(2.0*(i+1.0));// (current[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
//	cout << current[i] << " " << current_normalized <<endl;
		//double reference_normalized = reference[i];///(2.0*(i+1.0));// (reference[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
		double reference_normalized = reference[i];// r2*sin(omega2 + S*M_PI)/sin(S*M_PI);///(2.0*(i+1.0));// (current[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
		double reference_normalized2 = r2*sin(omega2 + S*M_PI)/sin(S*M_PI);///(2.0*(i+1.0));// (current[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
	   if(current_normalized <= reference_normalized)
	   {
	      dist1 += (reference_normalized2-current_normalized2)*(reference_normalized2-current_normalized2);// (reference[i] - current[i])*(reference[i] - current[i]);
	   }
//	   else
//	      dist1 -= 0.1*(current_normalized - reference_normalized)*(current_normalized - reference_normalized);
//	   else if (current_normalized > reference_normalized)
	}
   return sqrt(dist1);//+ 1.0/(1.0+sqrt(dist2));
   return (sqrt(dist1))?sqrt(dist1):-sqrt(dist2);

}
double MOEA::distance_improvement( vector<double> &reference, vector<double> &current)
{
	double dist1 = 0.0, dist2=0.0 ;
	double teta = 1.0 - ((double)(2.0*curren_gen)/max_gen);
	teta = max(0.00001,teta );
//	teta = 0.001;

	double r1=0.0;
	double r2=0.0;
	double sum1 = 0.0;
   for(int i = 0; i < reference.size(); i++)
      {
	r1 += current[i]*current[i];
	r2 += reference[i]*reference[i];
	sum1 += current[i];
      }
	r1 = sqrt(r1);
	r2 = sqrt(r2);
	double S=0.5;
   for(int i = 0; i < reference.size(); i++)
	{
		double omega1 = acos(current[i]/(r1));
		double omega2 = acos(reference[i]/(r2));
		double current_normalized = current[i];// r1*sin(omega1 + S*M_PI)/sin(S*M_PI);///(2.0*(i+1.0));// (current[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
		double current_normalized2 = r1*sin(omega1 + S*M_PI)/sin(S*M_PI);///(2.0*(i+1.0));// (current[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
//	cout << current[i] << " " << current_normalized <<endl;
		//double reference_normalized = reference[i];///(2.0*(i+1.0));// (reference[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
		double reference_normalized = reference[i];// r2*sin(omega2 + S*M_PI)/sin(S*M_PI);///(2.0*(i+1.0));// (current[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
		double reference_normalized2 = r2*sin(omega2 + S*M_PI)/sin(S*M_PI);///(2.0*(i+1.0));// (current[i]-idealpoint[i])/(nadirpoint[i] - idealpoint[i]);
	   if(current_normalized <= reference_normalized)
	   {
	      dist1 += (reference_normalized2-current_normalized2)*(reference_normalized2-current_normalized2);// (reference[i] - current[i])*(reference[i] - current[i]);
	   }
//	   else
//	      dist1 -= 0.1*(current_normalized - reference_normalized)*(current_normalized - reference_normalized);
//	   else if (current_normalized > reference_normalized)
	}
   return sqrt(dist1);//+ 1.0/(1.0+sqrt(dist2));
   return (sqrt(dist1))?sqrt(dist1):-sqrt(dist2);

}
double MOEA::distance( vector<double> &a, vector<double> &b)
{
	double dist = 0 ;
   for(int i = 0; i < a.size(); i++)
	{
	   double factor = (a[i]-b[i]);
	   dist += factor*factor;
	}
   return sqrt(dist);
}
void MOEA::init_population()
{

	idealpoint = vector<double>(nobj, 1.0e+30);
	nadirpoint= vector<double>(nobj, 0.0);
	currentidealpoint = vector<double>(nobj, 1.0e+30);
	currentnadirpoint= vector<double>(nobj, 0.0);


	char filename[1024];
	// Read weight vectors from a data file
//	sprintf(filename,"/home/joel.chacon/Current/MyResearchTopics/MOEA-D-Diversity/MOEAD-DE/vsd-moead-opt/ParameterSetting/Weight/W%dD_%d.dat", nobj, pops);
	//sprintf(filename,"ParameterSetting/Weight/W%dD_%d.dat", nobj, pops);
//	std::ifstream readf(filename);

    for(int i=0; i<pops; i++)
	{

		CSubproblem sub1, sub2;

		// Randomize and evaluate solution
		sub1.indiv.rnd_init();
		sub1.indiv.obj_eval();

		sub1.saved = sub1.indiv;

		// Initialize the reference point
		update_reference(sub1.indiv);

		// Load weight vectors
//		for(int j=0; j<nobj; j++)
//		{
//		    readf>>sub.namda[j];
//		}
	//	printf("\n"); getchar();

		// Save in the population
		population.push_back(sub1);

		sub2.indiv.rnd_init();
		sub2.indiv.obj_eval();

		sub2.saved = sub2.indiv;

		// Initialize the reference point
		update_reference(sub2.indiv);




		child_pop.push_back(sub2);
		nfes++;
	}
	curren_gen=1.0;
	idealpoint = currentidealpoint;
	for(int n=0; n<nobj; n++)
	nadirpoint[n] = currentnadirpoint[n];
	update_reference_vectors();
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
		if(ind.y_obj[n]<currentidealpoint[n])
			currentidealpoint[n] =ind.y_obj[n];
		if(ind.y_obj[n]>currentnadirpoint[n])
			currentnadirpoint[n] = ind.y_obj[n];
	}
//	nadirpoint[nobj-1] = 2*nobj+1;
	
}
void MOEA::evol_population()
{

	///vector<int> order;	this->tour_selection(10, order);
	vector<int> order;
	for(int i = 0; i < pops; i++) order.push_back(i);
	

	improvement_selection_vectors(child_pop, population);

	update_reference_vectors();
    //for(int sub=0; sub<order.size(); sub++)
    for(int sub=0; sub<order.size(); sub+=2)
	{

		int c_sub = order[sub];    // random order

		int type;
	
		double rnd1 = int(rnd_uni(&rnd_uni_init)*pops) ;//;rnd_uni(&rnd_uni_init);
		double rnd2 = int(rnd_uni(&rnd_uni_init)*pops) ;//;rnd_uni(&rnd_uni_init);

		int p1 = int(rnd_uni(&rnd_uni_init)*pops), p2 = int(rnd_uni(&rnd_uni_init)*pops), p3=int(rnd_uni(&rnd_uni_init)*pops), p4 = int(rnd_uni(&rnd_uni_init)*pops);
		while( population[p1].dist == 0)
		  p1= int(rnd_uni(&rnd_uni_init)*pops);
		while(p2 == p1 || population[p2].dist == 0  )
		  p2 = int(rnd_uni(&rnd_uni_init)*pops);

		while( population[p3].dist == 0)
		  p3= int(rnd_uni(&rnd_uni_init)*pops);
		while(p3 == p4 || population[p4].dist == 0  )
		  p4 = int(rnd_uni(&rnd_uni_init)*pops);

	      rnd1=p1;
	      rnd2=p2;
	      //binary tournament...
		if(population[p1].dist > population[p2].dist)	
		rnd1 = p1;
		else rnd1=p2;

		if(population[p3].dist > population[p4].dist)	
		rnd2 = p3;
		else rnd2=p4;


//		if(sub<60) {rnd1=0;  }	else rnd1=1;

//		while( rnd1==c_sub)
///		  rnd1 = int(rnd_uni(&rnd_uni_init)*pops);
///		while(rnd2 ==rnd1 || rnd2==c_sub)
///		  rnd2 = int(rnd_uni(&rnd_uni_init)*pops);
				
	

		// produce a child solution
		CIndividual child1, child2;
		double rate2 = 0.5; //rate + 0.25*(rnd_uni(&rnd_uni_init) - 0.5);
		//double rate2 = rate + 0.25*(rnd_uni(&rnd_uni_init) - 0.5);
		//diff_evo_xoverB(population[c_sub].indiv,population[rnd1].indiv,population[rnd2].indiv, child1, rate2);

		real_sbx_xoverA(population[rnd2].indiv, population[rnd1].indiv, child1, child2);
		//real_sbx_hybrid(population[plist[0]].indiv,population[plist[1]].indiv, child1, child2, max_gen, curren_gen);
		

		// apply polynomial mutation
		realmutation(child1, 1.0/nvar);
		realmutation(child2, 1.0/nvar);
		
		// repair method
		//repait
		// evaluate the child solution
		child1.obj_eval();
		child2.obj_eval();

		// update the reference points and other solutions in the neighborhood or the whole population
		update_reference(child1);
		update_reference(child2);
		child_pop[c_sub].indiv = child1;
		child_pop[c_sub+1].indiv = child2;
		nfes+=2;
	}
}
void MOEA::update_reference_vectors()
{
   for(int m = 0; m < nobj; m++)
   {
	double w = max_gen;
	
	
	idealpoint[m] += (1.0/w)*(currentidealpoint[m]-idealpoint[m]);
	//idealpoint[m] = 0.5*(idealpoint[m] + currentidealpoint[m]);

	nadirpoint[m] += (1.0/(max_gen))*(currentnadirpoint[m]/pops-nadirpoint[m]);
//	nadirpoint[m] =10;// 0.5*(nadirpoint[m] + currentnadirpoint[m]/pops);
//	nadirpoint[m] = currentidealpoint[m]/pops;
   }
 // nadirpoint[nobj-1]=70; 
   idealpoint = currentidealpoint;
   nadirpoint = currentnadirpoint;
//		cout << distance(idealpoint, nadirpoint)<<endl;
//	for(int i = 0; i < nobj; i++)
//	   cout << idealpoint[i]<<" ";
//	for(int i = 0; i < nobj; i++)
//	   cout << nadirpoint[i]<<" ";
//	cout << endl;

}
void MOEA::improvement_selection_vectors(vector<CSubproblem> &offspring, vector<CSubproblem> &parents)
{
   vector< CIndividual> reference, candidates;//(offspring.size() + parents.size());

   for(int i = 0 ; i < offspring.size(); i++)
   {
	 candidates.push_back(offspring[i].indiv);
   }
   for(int i = 0 ; i < parents.size(); i++)
   {
	 candidates.push_back(parents[i].indiv);
   }
	vector<double> distances(parents.size(),INFINITY);

   vector<double> sumfit (candidates.size(), 0.0);
   //select the m reference individuals..
   for(int i = 0 ; i < candidates.size(); i++)
	for(int j = 0; j < nobj; j++)
	   sumfit[i]+= (candidates[i].y_obj[j]);//-idealpoint[j])/(nadirpoint[j] - idealpoint[j]);
	
	for(int j = 0; j < nobj; j++)
	{
	  double minf=INFINITY;
	  int indexb=-1;
	  double minobj = INFINITY;
   	  for(int i = 0 ; i < candidates.size(); i++)
	  {
	   double extremefitness = 0.0;
//candidates[i].y_obj[j] + 0.1*sumfit[i];  ;// fabs(candidates[i].y_obj[j] - idealpoint[j])/(nadirpoint[j] - idealpoint[j]);// + 0.001*sumfit[i];

	     for(int z = 0; z < nobj; z++) if(j!=z) extremefitness+=candidates[i].y_obj[z] ;
//	   double extremefitness = sumfit[i];
//	   double extremefitness = -INFINITY;
//	for(int z = 0; z < nobj; z++) if(z!=j)	extremefitness = max(extremefitness,candidates[i].y_obj[z]);
	   //double extremefitness = fabs(candidates[i].y_obj[j]) + 0.001*sumfit[i];
	  // double extremefitness =  ;//sumfit[i];
	   if( extremefitness < minf )
	   {
		minf = extremefitness;
		indexb = i;
	   }
		minobj = min(minobj, candidates[i].y_obj[j]);
	  }

//		indexb = int(rnd_uni(&rnd_uni_init)*candidates.size()) ;//;rnd_uni(&rnd_uni_init);
//	for(int k = 0; k < nobj; k++)
//	   candidates[indexb].y_obj[j] -= 0.1*candidates[indexb].y_obj[j];
	    reference.push_back(candidates[indexb]);
	    iter_swap(candidates.begin()+indexb, candidates.end()-1);
	    candidates.pop_back();
	}
//	if(nfes > max_nfes-pops-1)
	{
	for(int i = 0; i < nobj; i++)
	{
	   for(int j = 0; j < nobj; j++)
	   {
		cout << reference[i].y_obj[j]<<" ";
	   }
		cout << endl;
	}
	}

  while(reference.size() < pops) 
  {
	double maxeuclidean = -INFINITY;
	int indexa=-1;
	int indexb=-1;
	
	for(int i = 0; i < reference.size(); i++)
	{
	   priority_queue< pair<double, int> > pqeuclidean;
	   for(int j = 0; j < reference.size(); j++)
		{
			if(i==j) continue;
		   double dist = distance(reference[j].y_obj, reference[i].y_obj);
		   pqeuclidean.push( make_pair(-dist, j ));
		}
		double score =0.0;// -pqimprovement.top().first-0.1*pqimprovement.top().second;//+ 0.1*pqimprovement.top().second;
		  score += -pqeuclidean.top().first;
		  //pqeuclidean.pop();
		  //score += -pqeuclidean.top().first;
		  //pqeuclidean.pop();
		  //score += -pqeuclidean.top().first;

	  if( maxeuclidean< score  ) 
	   {
		indexa = i;
		indexb = pqeuclidean.top().second;
		maxeuclidean= score;
	   }
	}
	cout << indexa <<" "<<indexb<<endl;
	//generate the artifitial vector....	
	vector<double> reference_art(nobj);
	double normref=0.0;
	for(int j = 0; j<nobj;j++)
	{
	 reference_art[j] = (reference[indexa].y_obj[j] + reference[indexb].y_obj[j]);
	 normref += reference_art[j];
	}
	for(int j = 0; j<nobj;j++) reference_art[j] /= normref;
		
	//Select the best point...
	int indexi=-1;
	double minfitness = INFINITY;
	for(int i =0; i < candidates.size(); i++)
	{
		double ft =  distance(candidates[i].y_obj, reference_art);// fitnessfunction( candidates[i].y_obj, reference_art);
		if(minfitness > ft)
		{
		   minfitness = ft;
		   indexi = i;
		}
	}

	reference.push_back(candidates[indexi]);
	iter_swap(candidates.begin()+indexi, candidates.end()-1);
	candidates.pop_back();
//	distances[reference.size()-1] = -minfitness;//maximprovement;
  }
	static int gen2=0;
	cout << gen2+1<<endl; gen2++;
//	getchar();
	//mean /= (pops-nobj);
	//cout << mean <<endl;
	//getchar();
	//for(int i = 0; i < nobj; i++)
	//reference[reference.size()-i-1].y_obj[i]-=1;
   for(int i = 0; i < reference.size(); i++)   
   {

      parents[i].indiv = reference[i]; 
      parents[i].indiv.obj_eval();
      parents[i].dist = distances[i];
   }
}
void MOEA::improvement_selection(vector<CSubproblem> &offspring, vector<CSubproblem> &parents)
{
   vector< CIndividual> reference, candidates;//(offspring.size() + parents.size());

   for(int i = 0 ; i < offspring.size(); i++)
   {
	 candidates.push_back(offspring[i].indiv);
   }
   for(int i = 0 ; i < parents.size(); i++)
   {
	 candidates.push_back(parents[i].indiv);
   }
	vector<double> distances(parents.size(),INFINITY);

   vector<double> sumfit (candidates.size(), 0.0);
   //select the m reference individuals..
   for(int i = 0 ; i < candidates.size(); i++)
	for(int j = 0; j < nobj; j++)
	   sumfit[i]+= (candidates[i].y_obj[j]);//-idealpoint[j])/(nadirpoint[j] - idealpoint[j]);
	
	for(int j = 0; j < nobj; j++)
	{
	  double minf=INFINITY;
	  int indexb=-1;
	  double minobj = INFINITY;
   	  for(int i = 0 ; i < candidates.size(); i++)
	  {
	   double extremefitness = 0.0;
//candidates[i].y_obj[j] + 0.1*sumfit[i];  ;// fabs(candidates[i].y_obj[j] - idealpoint[j])/(nadirpoint[j] - idealpoint[j]);// + 0.001*sumfit[i];

	     for(int z = 0; z < nobj; z++) if(j!=z) extremefitness+=candidates[i].y_obj[z] ;
//	   double extremefitness = sumfit[i];
//	   double extremefitness = -INFINITY;
//	for(int z = 0; z < nobj; z++) if(z!=j)	extremefitness = max(extremefitness,candidates[i].y_obj[z]);
	   //double extremefitness = fabs(candidates[i].y_obj[j]) + 0.001*sumfit[i];
	  // double extremefitness =  ;//sumfit[i];
	   if( extremefitness < minf )
	   {
		minf = extremefitness;
		indexb = i;
	   }
		minobj = min(minobj, candidates[i].y_obj[j]);
	  }

//		indexb = int(rnd_uni(&rnd_uni_init)*candidates.size()) ;//;rnd_uni(&rnd_uni_init);
//	for(int k = 0; k < nobj; k++)
	   candidates[indexb].y_obj[j] -= 0.1*candidates[indexb].y_obj[j];
	    reference.push_back(candidates[indexb]);
	    iter_swap(candidates.begin()+indexb, candidates.end()-1);
	    candidates.pop_back();
	}
//	if(nfes > max_nfes-pops-1)
	{
	for(int i = 0; i < nobj; i++)
	{
	   for(int j = 0; j < nobj; j++)
	   {
		cout << reference[i].y_obj[j]<<" ";
	   }
		cout << endl;
	}
	}

	double mean=0.0;
  while(reference.size() < pops) 
  {
	double maximprovement = -INFINITY;// DBL_MIN;
	double maxeuclidean = -INFINITY;
	double maxscore = -INFINITY;
	double euclidean ;
	int indexi=-1;
	
	for(int i = 0; i < candidates.size(); i++)
	{

		double sum=0.0;
		for(int k =0 ; k < nobj;k++) sum += candidates[i].y_obj[k];

	priority_queue< pair<double, double> > pqimprovement, pqeuclidean;
	   double minimprovement = INFINITY, mineuclidean=INFINITY ;
	   for(int j = 0; j < reference.size(); j++)
		{
		   //pqimprovement.push( make_pair( -distance_improvement(candidates[i].y_obj, reference[j].y_obj), -distance_improvement(reference[j].y_obj, candidates[i].y_obj) ));

		   double score2 = distance_improvement2(reference[j].y_obj, candidates[i].y_obj, 0.6) ;//+ 0.01*distance(reference[j].y_obj, candidates[i].y_obj); 
		   double dist = distance(reference[j].y_obj, candidates[i].y_obj);
		   //pqimprovement.push( make_pair(-score2, -dist ));
		   pqimprovement.push( make_pair(-score2, -(score2) ));
		}
		double score =0.0;// -pqimprovement.top().first-0.1*pqimprovement.top().second;//+ 0.1*pqimprovement.top().second;
		  score += -pqimprovement.top().first;
//		  pqimprovement.pop();

	  if( maxscore< score  ) 
	   {
		indexi = i;
		maxscore=score;
		maximprovement = score;
		euclidean = -pqimprovement.top().second;
	   }
//	if( maximprovement < -pqimprovement.top()  ) 
//	   {
//		maximprovement= -pqimprovement.top();
//	   }
	}
//	cout << "improvement... " << maximprovement << " euclidean.." << euclidean<<endl;
	mean += maximprovement;
	reference.push_back(candidates[indexi]);
	iter_swap(candidates.begin()+indexi, candidates.end()-1);
	candidates.pop_back();
	distances[reference.size()-1] = maximprovement;
  }
	static int gen2=0;
	cout << gen2+1<<endl; gen2++;
//	getchar();
	//mean /= (pops-nobj);
	//cout << mean <<endl;
	//getchar();
	//for(int i = 0; i < nobj; i++)
	//reference[reference.size()-i-1].y_obj[i]-=1;
   for(int i = 0; i < reference.size(); i++)   
   {

      parents[i].indiv = reference[i]; 
      parents[i].indiv.obj_eval();
      parents[i].dist = distances[i];
   }
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


	//sprintf(filename1,"/home/joel.chacon/Current/MyResearchTopics/MOEA-Improvement/HSI-MOEA/POS/POS_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	sprintf(filename1,"POS/POS_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	//sprintf(filename2,"/home/joel.chacon/Current/MyResearchTopics/MOEA-D-Diversity/MOEAD-DE/vsd-moead-opt/POF/POF_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	//sprintf(filename2,"/home/joel.chacon/Current/MyResearchTopics/MOEA-Improvement/HSI-MOEA/POF/POF_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	sprintf(filename2,"POF/POF_MOEAD_%s_RUN%d_seed_%d_nobj_%d.dat_bounded",strTestInstance,run, seed, nobj);
	//for(int gen=1; gen<=max_gen; gen++)
	int gen=1;
	while(nfes < max_nfes )
	{
//	   cout << gen <<endl;
//	   cout <<nfes<<endl;
		curren_gen = gen;	
		evol_population();
//		if( gen%1000 ==0)
//		{
//		save_pos(filename1);
//		save_front(filename2);
//		}
	//getchar();
	gen++;
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

//if(nobj == 2 || nobj == 3 || nobj == 4 || nobj==8)
//{
//   pops=120;
//   max_nfes = 49920;
//}
//else if (nobj==5 || nobj==6)
//{
//   pops=126;
//   max_nfes = 49896;
//}
//else if (nobj==7)
//{
//   pops=84;
//   max_nfes = 49980;
//}
//else
//{
//   pops=120;
//   max_nfes = 49920;
//}
cout << max_nfes<<endl;
max_gen= max_nfes/pops;
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