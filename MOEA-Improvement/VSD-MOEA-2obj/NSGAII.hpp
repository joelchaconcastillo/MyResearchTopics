#ifndef NSGAII_HPP_INCLUDED
#define NSGAII_HPP_INCLUDED
#include <vector>
#include <iostream>
#include "Individual.hpp"
#include "EAOperators.hpp"
#include "EvolutiveAlgorithm.hpp"
/////Identificador de cada operador de cruza
#define _SBX 101
#define _BLX 102
#define _HBX 103
#define _FUZZY 104
#define _SBXH 105
#define _SBXHD 106
/////identificador de cada operador de mutación....
#define _POLYNOMIAL 201
#define _NORMAL 202
#define _RANDOM 203
using namespace std;
class NSGAII : public EvolutiveAlgorithm
{
    public:
      typedef Individual * ptrIndividual;
      NSGAII(int SizePool, double ProbCross, int NBitsMut, Benchmark &ObjBenchmark, int NumberGenerations, double ParameterDInit ,string ProblemName, int Semilla, string Ruta, string Label,int IdCrossover, int IdMutation, int PeriodReport  );

    	NSGAII(int SizePool, double ProbCross, double ProbMut ,Benchmark &ObjBenchmark, int NumberGenerations, double ParameterDInit , string ProblemName, int Semilla, string Ruta, string Label, int IdCrossover, int IdMutation, int PeriodReport );

       NSGAII();
        ~NSGAII();
        void Init_NSGAII();
        void PlotInterfaceRSpaceObjective();
        void PlotInterfaceRSpaceVariables();
        //void getSolutions(vector<vector<double>> &SetFront, vector<vector<double>> &SetParetoOptimal, vector<int> &IndexBoundsObjectives);
        //void WriteFilePool();
    private:
        Benchmark *ObjBenchmark;
        int SizePool, NumberObjectives, Dimension, TotalGenerations, CurrentGeneration;
        double ProbCross, ProbMutation;
        string FileNameSummary, FileNameFront, FilenameGenotype, FilenameFitness, FilenameFenotype, ProblemName;
        int NBitsMut, IdCrossover, IdMutation, PeriodReport;

	double D, DI;

	//int VariableRepresentation;
	ptrIndividual ReferencePoint;
        vector<ptrIndividual> Survivors, Pool_Q;
        vector< vector<ptrIndividual> > Fronts;
	vector<double> IdealVector, NadirVector;

        void InitializePool(vector<ptrIndividual> &Survivors);
        void Fast_Non_Dominated_Sort_Current(vector<ptrIndividual> &Current, vector<ptrIndividual> &Survivors, vector<int> &CurrentFirstFront);
        void New_Pop(vector <ptrIndividual> &Poop_P, vector <ptrIndividual> &Pool_Q);
        bool CriterionStop();
        void Selection(vector <ptrIndividual> &Poop_P, vector <ptrIndividual> &Pool_Q);
        void Recombination(vector <ptrIndividual> &Pool_Q);
        void Evaluation(vector<ptrIndividual> &Pool_Q);
        void ControlParameterD();
        double getRandom(double Min, double Max);
        void CIV(vector<ptrIndividual> &Set, vector<ptrIndividual> &Extremal);
        void DCN(vector<ptrIndividual> &Set, vector<ptrIndividual> &PoolRef, vector<ptrIndividual> &Penalized);
        void DCN(vector<ptrIndividual> &Set1, vector<ptrIndividual> &Set2 );
        void BestODCN( vector<int> &FirstFrontCurrent  ,vector<ptrIndividual> &CurrentSet, vector<ptrIndividual> &Survivors);
        double EuclideanVariableDistance(ptrIndividual &indA, ptrIndividual &indB);
        double EuclideanObjectiveDistance(ptrIndividual &indA, ptrIndividual &indB);
        void AddCurrentBestIndividualPenalized(vector<ptrIndividual> &Penalized, vector<ptrIndividual> &CurrentSet);
        void End();
        void FreePool(vector<ptrIndividual> &Pool);
	int Improvement_Current( vector<int> &FirstFrontCurrent  ,vector<ptrIndividual> &CurrentSet, vector<ptrIndividual> &Survivors);

        /**
            Operaciones con conjuntos..
        **/
        void Union(vector<ptrIndividual> &Set1, vector<ptrIndividual> &Set2, vector<ptrIndividual> &Result);
};
//vector< Individual > operator+(vector<Individual> PoolA, vector<Individual> PoolB );
//ostream & operator << ( ostream &out,vector<Individual> Pool);
//ostream & operator << ( ostream &out,vector<double> data);

#endif // NSGAII_HPP_INCLUDED
