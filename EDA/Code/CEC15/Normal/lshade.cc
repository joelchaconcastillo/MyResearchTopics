/*
authors: Joel Chacón Castillo, Carlos Segura González
*/
/*
  Differential Evolution with Diversity Replacement
           
  Version: 1.0   Date: 16/01/2018
*/

#include"de.h"

Fitness LSHADE::run() {
  ////cout << scientific << setprecision(8);
  initializeParameters();
  setSHADEParameters();

  vector <Individual> pop;
  vector <Fitness> fitness(pop_size, 10);
  vector <Individual> children;
  vector <Fitness> children_fitness(pop_size, 10);
  vector <Individual> elite;
  vector <Fitness> elite_fitness(pop_size, 10);
  Di = sqrt(problem_size)*0.1;

  //initialize pop, children and elite..
  for (int i = 0; i < pop_size; i++) {
    pop.push_back(makeNewIndividual());
    children.push_back((variable*)malloc(sizeof(variable) * problem_size));
    elite.push_back((variable*)malloc(sizeof(variable) * problem_size));
  }
  evaluatePopulation(pop, fitness);
  for(int i = 0; i < pop_size; i++)
  {
	elite_fitness[i] = fitness[i];
	for(int j = 0; j < problem_size; j++) // copy the parents information to elite...
	elite[i][j] = pop[i][j];
  }
  evaluatePopulation(elite, elite_fitness);


  //initialize and update the memory of the best individual

  Individual bsf_solution = (variable*)malloc(sizeof(variable) * problem_size);
  Fitness bsf_fitness;

  if ((fitness[0] - optimum) < epsilon) fitness[0] = optimum;
  bsf_fitness = fitness[0];
  for (int j = 0; j < problem_size; j ++) bsf_solution[j] = pop[0][j];

  for (int i = 0; i < pop_size; i++) {
    nfes++;

    if ((fitness[i] - optimum) < epsilon) fitness[i] = optimum;


    if (fitness[i] < bsf_fitness) {
      bsf_fitness = fitness[i];
      for (int j = 0; j < problem_size; j ++) bsf_solution[j] = pop[i][j];
    }


    if (nfes >= max_num_evaluations) break;
  }
  ////////////////////////////////////////////////////////////////////////////


  variable *pop_sf = (variable*)malloc(sizeof(variable) * pop_size);
  variable *pop_cr = (variable*)malloc(sizeof(variable) * pop_size);

  //for current-to-pbest/1 --- temporally deactive
  //int p_best_ind;
  //int p_num = round(pop_size *  p_best_rate);
  //int *sorted_array = (int*)malloc(sizeof(int) * pop_size);
  //Fitness *temp_fit = (Fitness*)malloc(sizeof(Fitness) * pop_size);

  //main loop
  while (nfes < max_num_evaluations) 
  { 
      //Decrement the linear parameter of diversity
      updateD();
     // for (int i = 0; i < pop_size; i++) sorted_array[i] = i;
     // for (int i = 0; i < pop_size; i++) temp_fit[i] = elite_fitness[i];
     // sortIndexWithQuickSort(&temp_fit[0], 0, pop_size - 1, sorted_array);
     
      for (int target = 0; target < pop_size; target++) 
      {
        //generate random CR and F params
          if(randDouble() > 0.5)
            pop_cr[target] =  gauss(0.1, 0.1 );
          else
            pop_cr[target] =  gauss(0.9, 0.1 );

          if (pop_cr[target] > 1) pop_cr[target] = 1;
          else if (pop_cr[target] < 0) pop_cr[target] = 0;	

        //generate F_i and repair its value
        do {	
          pop_sf[target] = cauchy_g(0.5, 0.5*(double)nfes/max_num_evaluations );
         // pop_sf[target] = cauchy_g(0.5, 0.5);
        } while (pop_sf[target] <= 0.0);

        if (pop_sf[target] > 1) pop_sf[target] = 1.0;

        //it's for the mutation p-best...
        //do {
        //   p_best_ind = sorted_array[rand() % p_num];
        //} while (p_best_ind == target);                  

        operateCurrentToPBest1BinWithArchive(pop, &children[target][0], target, pop_sf[target], pop_cr[target]);
      }
  
    // evaluate the children's fitness values
    evaluatePopulation(children, children_fitness);

    /////////////////////////////////////////////////////////////////////////
    //update the bsf-solution and check the current number of fitness evaluations
    // if the current number of fitness evaluations over the max number of fitness evaluations, the search is terminated
    // the optimum is setted if the error is below of 1e-08
    for (int i = 0; i < pop_size; i++) 
     {
        nfes++;

       if ((elite_fitness[i] - optimum) < epsilon) elite_fitness[i] = optimum;

        if (elite_fitness[i] < bsf_fitness) 
        {
          bsf_fitness = elite_fitness[i];
          for (int j = 0; j < problem_size; j ++) bsf_solution[j] = elite[i][j];
        }

        if (nfes >= max_num_evaluations) break;
     }
    
    // Differential evolution selection
    for (int i = 0; i < pop_size; i++) 
    {
      if (children_fitness[i] == fitness[i]) 
      {
  	elite_fitness[i] = children_fitness[i];
  	for (int j = 0; j < problem_size; j ++) elite[i][j] = children[i][j];
      }
      else if (children_fitness[i] < elite_fitness[i]) 
      {
  	elite_fitness[i] = children_fitness[i];

  	for (int j = 0; j < problem_size; j ++) elite[i][j] = children[i][j];
      }
    }

    replacement(pop, fitness, children, children_fitness, elite, elite_fitness);
  }

 //free dynamic memory 
  for (int i = 0; i < pop_size; i++) 
  {
    free(pop[i]); 
    free(children[i]); 
    free(elite[i]);
  }
  pop.clear(); 
  children.clear(); 
  fitness.clear();
  elite.clear();
  children_fitness.clear();
  free(bsf_solution);

  ////sorted_array.clear();
  //free(sorted_array);
  //free(temp_fit); //.clear();

  return bsf_fitness - optimum;
}


void LSHADE::operateCurrentToPBest1BinWithArchive(const vector<Individual> &pop, Individual child, int &target, variable &scaling_factor, variable &cross_rate) {

  int r1, r2;
  
  do {
    r1 = rand() % pop_size;
  } while (r1 == target);
  do {
    r2 = rand() % (pop_size);
  } while ((r2 == target) || (r2 == r1));

  int random_variable = rand() % problem_size;

    for (int i = 0; i < problem_size; i++) 
    {
      if ((randDouble() < cross_rate) || (i == random_variable)) 
      {
	child[i] = pop[target][i] + scaling_factor* (pop[r1][i] - pop[r2][i]);     // jSO
      }
      else 
	child[i] = pop[target][i];
    }
  //If the mutant vector violates bounds, the bound handling method is applied
  modifySolutionWithParentMedium(child,  pop[target]);
}

double LSHADE::distance(Individual &A, Individual &B)
{
   double distance = 0.0;
   for(int i = 0; i < problem_size; i++)
   {
	double term = (A[i] - B[i])/(max_region - min_region);
	distance += term*term;
  }
   return sqrt(distance);
}

void LSHADE::updateD()
{
	double TElapsed = nfes;
        double TEnd = max_num_evaluations;

        D = Di - Di * (1.1*TElapsed / TEnd  );
	D = ( D<=0 )? 0: D ;
//	D = ( -1 > D)? -1: D ;
}

void LSHADE::replacement(vector<Individual> &pop, vector<Fitness> &fitness, vector<Individual> &children,vector<Fitness> &children_fitness, vector<Individual> &elite, vector<Fitness> &elite_fitness)
{
  priority_queue < pair <Fitness, Individual> > pq;
  vector<Individual> survivors, penalized;
  vector<Fitness> survivors_fitness, penalized_fitness;
   int j = 0;
  for(int i = 0 ; i < pop.size(); i++)
  {
	  pq.push( make_pair(-fitness[i], pop[i]));
	  pq.push( make_pair(-children_fitness[i], children[i] ));
	  pq.push( make_pair(-elite_fitness[i], elite[i]));
  }

  while(!pq.empty())
  {
     pair<Fitness, Individual> data = pq.top();
     Individual current_individual = data.second;
     Fitness current_fitness = data.first;
     pq.pop();
     
     double mind = INFINITY;
     for(int i = 0 ; i < survivors.size(); i++)
	{
	     double d =  distance(survivors[i], current_individual) ;
	     if( d < mind ) mind = d;
	}
     if(mind <= D)
	{
	   penalized_fitness.push_back(current_fitness);
	   penalized.push_back(current_individual);
	}
    else
	{
	   survivors_fitness.push_back(current_fitness);
	   survivors.push_back(current_individual);
	}
  }

     while(survivors.size() < pop.size())
     {
	double maxd = -INFINITY;
	int maxindex = -1;
	//find the max near point from survivor to childrens....
        for(int i = 0 ; i < penalized.size(); i++)
        {
	   double mind = INFINITY;	
	   for(int j = 0; j < survivors.size(); j++)
 	   {
		double d= distance(penalized[i], survivors[j]);
		mind = min(d, mind);
	   }	
	   if( mind > maxd)
	  {
		maxd = mind;
		maxindex = i;
	  }
        }
        survivors.push_back(penalized[maxindex]);	
        survivors_fitness.push_back(penalized_fitness[maxindex]);	
	penalized.erase(penalized.begin()+maxindex);
	penalized_fitness.erase(penalized_fitness.begin()+maxindex);
     }

  for(int i = 0 ; i < pop.size(); i++)
  {
 	for(int j = 0 ; j < problem_size; j++)
	 pop[i][j] = survivors[i][j];
  }
	fitness = survivors_fitness;

}
void  LSHADE::setSHADEParameters() {
//  arc_rate = g_arc_rate;
 // arc_size = (int)round(pop_size * arc_rate);
 // p_best_rate = g_p_best_rate;
  //memory_size = g_memory_size;
}
