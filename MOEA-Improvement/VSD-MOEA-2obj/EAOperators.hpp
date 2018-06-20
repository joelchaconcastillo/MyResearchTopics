/**
	Author: Joel Chacón Castillo
**/
#ifndef EAOperators_HPP_INCLUDED
#define EAOperators_HPP_INCLUDED
#include "Individual.hpp"
#define EPS 1.0e-14
//#define EPS 1.0e-300
using namespace std;
typedef Individual * ptrIndividual;
//class EAOperators
//{
//	public:
//		EAOperators();
//	protected:

	double NextRand();
	/**
		Operadores relacionados con la selección
	**/
	 void TournamentSelection(vector<ptrIndividual> &Population, vector<ptrIndividual> &OffSpring);
	 void RouletteWhell();
	 void SUS();//Stochastic Universal Sampling
	/**
		Operadores relacionados con la cruza..
	**/
	//Binary Representation
	 void OnePointCrossOver();
	void UniformCross(vector<ptrIndividual> &Population ,vector<ptrIndividual> &OffSpring, double ProbCross);
	void UniformCrossIndividual(ptrIndividual &A, ptrIndividual &B, ptrIndividual &OffSpring, double ProbCross);
	 void NPointCrossOver();
	//Real Representation
	 void LinearCrossover();
	 void HBX(vector<ptrIndividual> &Population, vector<ptrIndividual> &OffSpring, double PCross);
	 void HBXIndividual(ptrIndividual &Parent1, ptrIndividual &Parent2, ptrIndividual &Parent3, ptrIndividual &OffSpring1, double PCross );
	 void BLX(vector<ptrIndividual> &Population, vector<ptrIndividual> &OffSpring, double PCross);
	 void BLXIndividual(ptrIndividual &Parent1, ptrIndividual &Parent2, ptrIndividual &OffSpring1, ptrIndividual &OffSpring2, double PCross );
	 void FuzzyCrossOver(vector<ptrIndividual> &Population, vector<ptrIndividual> &OffSpring, double PCross);
	 void FuzzyIndividual(ptrIndividual &Parent1, ptrIndividual &Parent2, ptrIndividual &OffSpring1, ptrIndividual &OffSpring2, double PCross );
	 void SBXHybrid(vector<ptrIndividual> &Population ,vector<ptrIndividual> &OffSpring, double PCross); //Simulated Binary Crossover
	 void SBXIndividualHybrid(ptrIndividual &Parent1, ptrIndividual &Parent2, ptrIndividual &OffSpring1, ptrIndividual &OffSpring2, double PCross );
	 void SBX(vector<ptrIndividual> &Population ,vector<ptrIndividual> &OffSpring, double PCross); //Simulated Binary Crossover
	 void SBXIndividual(ptrIndividual &Parent1, ptrIndividual &Parent2, ptrIndividual &OffSpring1, ptrIndividual &OffSpring2, double PCross );
	 void SBXHybridDynamic(vector<ptrIndividual> &Population ,vector<ptrIndividual> &OffSpring, double PCross, double ProbVariable);
	 void SBXIndividualHybridDynamic(ptrIndividual &Parent1, ptrIndividual &Parent2, ptrIndividual &OffSpring1, ptrIndividual &OffSpring2, double PCross, double ProbVariable );

	 
	 
	 void UNDX(); //Unimodal Normally Distributed Crossover
	  void SPX(); //Simplex Crossover
	 
	 void UnfairAverageCrossover();

	/**
		Operadores relacionados con la mutación..
	**/
	//Binary Representation
	 void BitMutation(vector<ptrIndividual> &Population, int NBitsMut);
	 void BitMutationIndividual(ptrIndividual &A, int NBitsMut);
	//Real Representation
	 void RandomMutation(vector<ptrIndividual> &Population);
	 void NonUniformMutation();
	 void NormallyDistribuitedMutation(vector<ptrIndividual> &Population);
	 void PolynomialMutation(vector<ptrIndividual> &Population, double p_mut);
	 void PolynomialMutationIndividual(ptrIndividual &Ind, double eta, double p_mut);
//};

#endif
