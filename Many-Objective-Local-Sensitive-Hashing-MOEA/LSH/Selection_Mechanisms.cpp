#include <iostream>
#include <bits/stdc++.h>
#include <random>
#include <fstream>
#include <queue>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

double Rand(double min = 0.0, double max = 1.0)
{
   return min + ((double)rand()/RAND_MAX)*(max-min);
}
void Fu(vector<double> &F)
{
	
	double value = 0.0;
	double x1 = Rand(), x2 = Rand(), x3 = Rand();
    	do{

		x1 = Rand(), x2 = Rand(), x3 = Rand();
		F[0] = x1*Rand(1.0,3);
		//F[1] = x2*Rand(1.0,10);
		//value = 1.0-x1*x1-x2*x2;
		value = 1.0-x1*x1;
	}
	//while( x1*x1 + x2*x2 >= 1.0);
	while( x1*x1  >= 1.0);
//	F[2] = sqrt(value);	
//        F[2] = (value>0)?sqrt(value)*Rand(1.0,3.0): 0.0;
        F[1] = (value>0)?sqrt(value)*Rand(1.0,3.0): 0.0;
}
double Distance(vector<double> &A, vector<double> &B)
{
   double value = 0.0;
   for(int i = 0; i < A.size(); i++)
   //value +=  (A[i]-B[i])*(A[i]-B[i]);
   value +=  max(0.0, (B[i]-A[i]));
   return value;
   //return sqrt(value);
}
double Evaluateimprovement(vector<double> &x, vector<double> &w)
{
  return Distance(x, w); 
}
double Evaluatepbi(vector<double> &x, vector<double> &w)
{
   double norm = 0, d1 = 0, d2 = 0;
  int i;

  // Normalize the namdaeight vector (line segment)
  for(i = 0; i < w.size(); i++)
  {
    norm  += w[i] * w[i]; 
    d1 += (( x[i])* w[i] );
  }
  norm = sqrt(norm);
  d1 = fabs(d1)/norm;
 
  //d1 = fabs(d1);
  for(i = 0; i < w.size(); i++)
    d2  += pow( (x[i]) - d1  *(w[i]/norm), 2.0); 
    d2 = sqrt(d2);
  return (d1 + 5.0 * d2); 
}
void pbi(vector<vector<double> > &in, vector<vector<double> > &out, int Nout)
{

 char filename[1024];
  // Read weight vectors from a data file
  sprintf(filename,"Weight/W3D_100.dat");
//  sprintf(filename,"./ParameterSetting/Weight/W%dD_%d.dat", nobj, pops);
  std::ifstream readf(filename);

	int NVectors = 100;
   //load the weigth vectors....
    vector<vector<double> > w( NVectors, vector<double> (3, 0.0)   );
   vector<bool> gridpool(in.size(), false);
   for(int i  = 0  ; i < NVectors; i++)
   {
      for(int m = 0 ; m < 3; m++)
	readf >> w[i][m];
   }
   readf.close();
   //evalutate the weigth vectors...
  for(int iw = 0; iw < NVectors; iw++)
  {
   priority_queue< pair<double, int  > >pq;
   for(int i = 0; i < in.size(); i++)
   {
	if( gridpool[i]) continue;
	pq.push(make_pair(-Evaluatepbi(in[i], w[iw]), i) );
	//pq.push(make_pair(-Evaluateimprovement(in[i], w[iw]), i) );
   }
	int bestid = pq.top().second;
	gridpool[bestid] = true;
       out.push_back(in[bestid]);
  }

}
void Selection(vector<vector<double> > &in, vector<vector<double> > &out, int Nout)
{
    //Seleccionar los puntos de referencia.....
   for(int m = 0 ;m < 3; m++)
   {
	double max = INFINITY;
	int index = -1;
     for(int i = 0 ; i < in.size(); i++)
     {
	if( in[i][m] < max)
	{
	   index = i;
	   max = in[i][m];
	}
     }
	out.push_back(in[index]);
	in.erase(in.begin()+index);
   }

 for(int k = 0; k < Nout; k++) 
{
   double Max = -INFINITY;
	int index= -1;
   for(int i = 0; i < in.size(); i++)
	{
	       double Min = INFINITY;
		for(int j = 0; j < out.size(); j++)
		{
		        double value = Distance(in[i], out[j]);
			Min = min(value, Min);
		}
	   if(Max < Min)
	   {
		index = i;
		Max = Min;
	   }
	}
//	if(Max== 0.0)cout <<"AAAAAAAA"<<endl;
	out.push_back(in[index]);
	in.erase(in.begin()+index);
}
	
}
int main()
{
	srand(time(0));
   int N =10000, S=100, M = 2;
   
   vector<vector<double> >Data(N,vector<double>(M,0.0)), out;
   vector<vector<double> >projections(S,vector<double>(M,0.0));
   for(int i = 0; i < N; i++)
   {
	//int o = 90;
	//if(i < o)	
	 Fu(Data[i]);
	//else	
	//{
	//	int t = rand()%o;
	//	for(int m = 0; m < M; m++)
	//	Data[i][m] = Data[t][m]*(Rand(1.0,1.5));
	//}
      
   }

   //Generate normal vectors...
   random_device rd;
   mt19937 gen(rd()); //Spetial uniform generator....
   normal_distribution<double> distribution(0.0, 1.0); //Alternatively could work the box-muller method...

  for(int i = 0; i < S; i++)
  { 	
       for(int j = 0; j < M; j++)
	{
	   projections[i][j] = fabs(distribution(gen));
	}
  }

  for(int k = 0; k < S; k++)
   {
	double MIN = DBL_MAX;	
	int index = -1;
		double sum=0.0;
	   for(int i = 0; i < Data.size(); i++)
	   {
		sum=0.0;
	       for(int j = 0; j < M; j++)
		   sum+=(projections[k][j]*Data[i][j]);	
		double n=0.0;
	//       for(int j = 0; j < M; j++)n += pow(projections[k][j],2);
	//	n = sqrt(n);	
	//	sum /=n;
		 if(sum < MIN)
		  {
		    MIN=sum;
		   index = i;
		  }
	//cout << sum << " "<<endl;getchar();
	   }
	out.push_back(Data[index]);
	iter_swap(Data.begin() + index, Data.end()-1);
   	Data.pop_back();

  }
  
//out = projections;
//   //Selection(Data, out, S);
//   //pbi(Data, out, S);
   for(int i = 0; i < out.size(); i++)
   {
	for(int m = 0; m < out[i].size(); m++)
	{
	   cout << out[i][m]<< " ";
	}
	for(int m = 0; m < out[i].size(); m++)
	{
	   cout << projections[i][m]<< " ";
	}
       cout <<endl;
   }
     

}

