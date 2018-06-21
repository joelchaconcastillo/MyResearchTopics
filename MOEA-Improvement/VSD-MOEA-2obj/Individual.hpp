#ifndef INDIVIDUAL_HPP_INCLUDED
#define INDIVIDUAL_HPP_INCLUDED
#define BINARY_ENCODE 111
#define REAL_ENCODE 112
#include "Objectives.hpp"
using namespace std;
class Individual{
    public:
        Individual();
        void InitializeIndividual(Benchmark *ObjBenchmark);
	void TruncateVariable(int Dim, double Value);
        /**
            Se obtiene el objeto objectives el cual consta de la información
            de todas las funciones objetivo.
        **/

        /**
            Get
        **/
        inline Objectives& getObjectives(){ return ObjObjectives; }
	inline double getObjDistance(){return this->ObjectiveDistance;}
	inline double getVarDistance(){ return this->VariableDistance;}
        inline double getRank(){return this->Rank;}
        inline int getNumberObjectives(){return this->NumberObjectives;}
        inline int getDimension(){return this->Dimension;}
	inline int getVariableRepresentation(){return this->VariableRepresentation;}
	double getEvaluationMethod();
	inline double getObjectiveValue(int N){ return this->ObjObjectives.SpaceObjectives[N].Fitness;}
	inline double getFenotype(int Dimension){ return this->ObjObjectives.DecisionVariables[Dimension];}
	inline bool Dominate(Individual &Ind){ return this->ObjObjectives.Dominate(Ind.ObjObjectives);}
	inline int getNBits(){ return this->nbits;}
	inline double getVariable(int d){ return this->ObjObjectives.DecisionVariables[d];}
	inline double getMaximum(int d){ return this->Bounds[d][1]; }
	inline double getMinimum(int d){ return this->Bounds[d][0];}
        /**
            Set
        **/
        inline void setRank(int Rank){ this->Rank = Rank;}
	inline void setVariableDistance(double Distance){ this->VariableDistance = Distance;}
	inline void setObjDistance(double Distance){ this->ObjectiveDistance = Distance;}
	inline void setVariableRepresentation(int VariableRepresentation){this->VariableRepresentation = VariableRepresentation;}
	inline void setFenotype(int Dimension, double Value){ this->ObjObjectives.DecisionVariables[Dimension] = Value; }
//	inline void setObjective(int m, double value){this->ObjObjectives.setObjective(m, value);}
        void EvalIndividual();
        void DecodeIndividual(vector<double> & Genotype);

        /**
		Variable de desición para el caso encod-binary
	**/
	vector<vector<bool>> DecisionVariables;
	bool Active;
    private:
        Objectives ObjObjectives;

        int Dimension, NumberObjectives, Rank, nbits;
	int VariableRepresentation;
	//Distancias del DCN y ODCN
	double ObjectiveDistance, VariableDistance;


        double getBase10(vector<bool> &Individuo, double Min , double Max);
        int BinarytoInt(vector<bool> &Individuo);
        vector<vector<double>> Bounds;
        void setRandomBinary();
	double DoubleRandom(double Min, double Max);
        //Generar boleanos aleatorios con una distribución bernoulli
        vector<bool>random_bool( double p  = 0.5);

};


#endif // INDIVIDUAL_HPP_INCLUDED
