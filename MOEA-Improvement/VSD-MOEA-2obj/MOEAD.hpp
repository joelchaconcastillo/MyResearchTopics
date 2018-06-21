/**
	Author: Joel Chacón Castillo
	Description: En este fichero se presenta la estructura del algoritmo.
**/
#ifndef MOEAD_HPP_INCLUDED
#define MOEAD_HPP_INCLUDED
#include "Benchmark.hpp"
#include "EvolutiveAlgorithm.hpp"
#include "DecompositionMethods.hpp"
#define MAX_OBJ_VAL 1e30
#define MIN_OBJ_VAL -1e30
using namespace std;
class MOEAD : public EvolutiveAlgorithm
{
	public:
		MOEAD();
		MOEAD(int SizePool, double ProbCross, int NBitsMut, Benchmark &ObjBenchmark, int TotalGenerations);
	private:
		vector<Individual> EP;
		vector<vector<double>> Weight;
		vector<vector<double>> MatrixDistaces;
		vector<vector<int>> MatrixIndexNeigthborhood;
		vector<double> IdealVector;
		int NumberObjectives, NeighborhoodSize;
		double H;
		void SortMinDistaces(vector<double> &Distances, vector<int> &Indexes);
		int ComputeSizePopulation();
		void UpdateIdealVector();
		void UpdateIdealVectorIndividual(Individual &Ind);
		void UpdateNeighboringSoltions();	
		void UpdateEP();
		void InitWeightVector();
		void InitIdealVector();
		void SelectionNiche(int IndexParent, Individual &Child);
		void InitNeighborhood();
		double EuclideanDistance(vector<double> &vecA, vector<double> &vecB );
		inline double getScalarFunction(vector<double> &IndividualWeight, Individual &Ind){ return ScalarTchebycheffApproach(IndividualWeight,IdealVector,Ind ); }

		//Métodos virtuales...
		void Init();
		void Generation();
		void Reproduction();
		void Improvement();
		void End();
};

#endif
