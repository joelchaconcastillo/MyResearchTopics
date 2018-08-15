/*

    These files are the code of "jSO" for Special Session & Competition on Real-Parameter Single Objective Optimization at CEC-2017 (see [1])

       [1] Janez Brest, Mirjam Sepesy Maucec, Borko Boskovic. Single Objective Real-Parameter Optimization: Algorithm jSO, 
           Proc. IEEE Congress on Evolutionary Computation (CEC-2017), Donostia - San Sebastián, Spain, June 2017.

   jSO is improved version of i-LSHADE.
   iL-SHADE: Improved L-SHADE Algorithm (L-SHADE was proposed by Ryoji Tanabe and Alex Fukunaga at CEC2014).
   Many thanks to Ryoji Tanabe and Alex Fukunaga for providing L-SHADE.

*/


/*
  L-SHADE implemented by C++ for Special Session & Competition on Real-Parameter Single Objective Optimization at CEC-2014
  See the details of L-SHADE in the following paper:

  * Ryoji Tanabe and Alex Fukunaga: Improving the Search Performance of SHADE Using Linear Population Size Reduction,  Proc. IEEE Congress on Evolutionary Computation (CEC-2014), Beijing, July, 2014.
  
  Version: 1.0   Date: 16/Apr/2014
  Written by Ryoji Tanabe (rt.ryoji.tanabe [at] gmail.com)
*/

#include "de.h"

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

int g_function_number;
int g_problem_size;
unsigned int g_max_num_evaluations;

int g_pop_size;
double g_arc_rate;
int g_memory_size;
double g_p_best_rate;

ofstream outFile;

int main(int argc, char **argv) {

  int sed = atoi(argv[1]);

  int problem = atoi(argv[2]);

  //dimension size. please select from 10, 30, 50, 100
  g_problem_size = atoi(argv[3]);
  //available number of fitness evaluations 
  g_max_num_evaluations = g_problem_size * 10000;
  g_max_num_evaluations = 25000000;

  //random seed is selected based on time according to competition rules
  srand(sed);

  g_pop_size = 10000;// (int)round(sqrt(g_problem_size) * log(g_problem_size) * 25); 

  // raw data: Record function error value (Fi(x)-Fi(x*)) after (0.01, 0.02, 0.03, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0)*MaxFES for each run.
  stringstream ss;
  ss << g_problem_size;
  string tmp(ss.str());
  string fileNameStr="rawDataD"+tmp+".dat";
  char fileName[500];
  sprintf(fileName, "/home/joel.chacon/Chacon/DE_diversity/CEC2018/%dD/%d/%d.txt ", g_problem_size, problem, sed );
//sprintf(fileName, "%dD/%d/%d.txt", g_problem_size, problem, sed );

//  strcpy(fileName,fileNameStr.c_str());
  //ofstream outFile(fileName, ios::out);
  outFile.open(fileName, ios::out);

    g_function_number = problem;


      searchAlgorithm *alg = new LSHADE();
      outFile << alg->run();
      delete alg;

 //free memory of the benchmark
		free(M);
		free(OShift);
		free(y);
		free(z);
		free(x_bound);
  return 0;
}

