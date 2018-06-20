#include <iostream>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Benchmark.hpp"
#include "EvolutiveAlgorithm.hpp"
#include "MOEAD.hpp"

MOEAD::MOEAD()
{
}
MOEAD::MOEAD(int SizePool, double ProbCross, int NBitsMut, Benchmark &ObjBenchmark, int TotalGenerations)
{
	this->H = 149;
	this->NumberObjectives = ObjBenchmark.getNObjectives();
	this->ProbCross = ProbCross;
	this->NBitsMut = NBitsMut;
	this->ObjBenchmark = &ObjBenchmark;
	this->NumberGenerations = TotalGenerations;
	this->SizePopulation = ComputeSizePopulation();
	NeighborhoodSize = 20;
	srand(time(NULL));
	this->FilenameGenotype = "OutPut/Genotype.txt";  
	this->FilenameFenotype =  "OutPut/Fenotype.txt";
	this->FilenameFitness = "OutPut/Fitness.txt";
	//Eliminar el archivo en caso de que existan
	ofstream SummaryGen, SummaryFen, SummaryFit;
	
    	SummaryGen.open (this->FilenameGenotype);
    	SummaryFen.open (this->FilenameFenotype);
    	SummaryFit.open (this->FilenameFitness);	
	SummaryGen << "Total_Generations\t" << this->NumberGenerations<< "\tNumber_Objectives\t"<< this->NumberObjectives <<endl;
	SummaryFen << "Total_Generations\t" << this->NumberGenerations<< "\tNumber_Objectives\t"<< this->NumberObjectives <<endl;
	SummaryFit << "Total_Generations\t" << this->NumberGenerations<< "\tNumber_Objectives\t"<< this->NumberObjectives <<endl;
}
int MOEAD::ComputeSizePopulation()
{
	int Size = 0;
	for(double i = 0; i <= this->H; i++) Size++;
	return Size;
}
void MOEAD::InitIdealVector()
{

	for(int i = 0; i < this->NumberObjectives; i++)
	{
		if(this->ObjBenchmark->getTypeDuality()[i] == MINIMIZE)
			this->IdealVector.resize(this->NumberObjectives, MAX_OBJ_VAL);
		if(this->ObjBenchmark->getTypeDuality()[i] == MAXIMIZE)
			this->IdealVector.resize(this->NumberObjectives, MIN_OBJ_VAL);
	}
}
void MOEAD::InitWeightVector()
{
	for(double i = 0; i <= this->H; i++)
	{
		vector<double> Wvec(this->NumberObjectives);
		Wvec[0] = i/this->H;
		if(this->NumberObjectives == 2)
			Wvec[1] = 1.0 - i/this->H;
		this->Weight.push_back(Wvec);
	}
}
double MOEAD::EuclideanDistance(vector<double> &vecA, vector<double> &vecB )
{
	double Suma = 0;
	for(int i = 0; i < vecA.size(); i++)
	{
		Suma += pow(vecA[i]-vecB[i],2);
	}
	return sqrt(Suma);
}
void MOEAD::Generation()
{
	Reproduction();
	Improvement();
	UpdateIdealVector();
	UpdateNeighboringSoltions();	
	UpdateEP();
	ExportIndividualsFile(this->EP, this->FilenameGenotype, this->FilenameFenotype, this->FilenameFitness, this->CurrentGeneration);
}
void MOEAD::Reproduction()
{
	for(int i = 0 ; i < this->SizePopulation; i++)
	{
		int Index1 = this->MatrixIndexNeigthborhood[i][rand()%NeighborhoodSize];
		int Index2 = this->MatrixIndexNeigthborhood[i][rand()%NeighborhoodSize];
		UniformCrossIndividual(this->Population[Index1], this->Population[Index2], this->OffSpring[i], this->ProbCross);	
		BitMutationIndividual(this->OffSpring[i], this->NBitsMut);
		this->OffSpring[i].EvalIndividual();
		UpdateIdealVectorIndividual(this->OffSpring[i]);
		SelectionNiche(i, this->OffSpring[i]);
	}
}
void MOEAD::SelectionNiche(int IndexParent, Individual &Child)
{
	for(int i = 0; i < this->NeighborhoodSize ;i++)
	{
		int IndexInd = this->MatrixIndexNeigthborhood[IndexParent][i];
		double f1, f2;
		f1 = getScalarFunction(this->Weight[IndexInd], this->Population[IndexInd]);
		f2 = getScalarFunction(this->Weight[IndexInd], Child  );
		if(f2 < f1) this->Population[IndexInd] = Child;
	}
}
void MOEAD::UpdateIdealVector()
{
	for(int i= 0; i < this->SizePopulation; i++)
	{
		UpdateIdealVectorIndividual(this->Population[i]);
	}	
}
void MOEAD::UpdateIdealVectorIndividual(Individual &Ind)
{
		for(int j = 0; j < NumberObjectives; j++)
		{
			if(this->ObjBenchmark->getTypeDuality()[j] == MINIMIZE)
			{
				if(this->IdealVector[j] > Ind.getObjectiveValue(j))
					this->IdealVector[j] = Ind.getObjectiveValue(j);
			}
			else if(this->ObjBenchmark->getTypeDuality()[j] == MAXIMIZE)
			{
				if(this->IdealVector[j] < Ind.getObjectiveValue(j))
					this->IdealVector[j] = Ind.getObjectiveValue(j);
			}
		}
}
void MOEAD::Improvement()
{

}
void MOEAD::InitNeighborhood()
{
	for(int i = 0; i < this->SizePopulation; i++)
	{
		vector<double> Distances;
		vector<int> Indexes;
		for(int j = 0; j < this->SizePopulation; j++)
		{
			if(i==j)continue;
			Distances.push_back(EuclideanDistance( this->Weight[i],  this->Weight[j]));
			Indexes.push_back(j);
		}
		SortMinDistaces(Distances, Indexes);
		//vector<int> Tmp( Indexes.begin(), Indexes.begin()+this->NeighborhoodSize  );
		//this->MatrixIndexNeigthborhood.push_back(  Tmp );
		//this->MatrixIndexNeigthborhood[i].insert( this->MatrixIndexNeigthborhood[i].begin(), Indexes.begin(), Indexes.end() );
		/** Puede no ser estable resize, sirve con std=x11*/
		Indexes.resize(this->NeighborhoodSize);
		this->MatrixIndexNeigthborhood.push_back(Indexes);
	}
}
void MOEAD::SortMinDistaces(vector<double> &Distances, vector<int> &Indexes)
{
	for(int i = 0; i < this->NeighborhoodSize; i++)
	{
		for(int j = i+1; j < Distances.size(); j++)
		{
			if(Distances[i] > Distances[j])
			{
			//	double dtmp = Distances[i];
			//	Distances[i] = Distances[j];
			//	Distances[j] = dtmp;
			//	int indextmp = Indexes[i];
			//	Indexes[i] = Indexes[j];
			//	Indexes[j] = indextmp; 
				swap(Distances[i], Distances[j]);
				swap(Indexes[i], Indexes[j]);	
			}
		}
	}
}
void MOEAD::UpdateNeighboringSoltions()
{

}
void MOEAD::UpdateEP()
{
	//Eliminar a todos los elementos de EP que son dominados
	for(int i = 0; i < this->Population.size(); i++)
	{
		bool Flag = true;
		for(vector<Individual>::iterator it = EP.begin(); it != EP.end(); )
		{
			if(Population[i].Dominate(*it))
			{
				EP.erase(it);
			}
			else
			{
				if( it->Dominate(Population[i]) )
					Flag=false;
				it++;
			}
		}
		if(Flag) this->EP.push_back(this->Population[i]);
	}
//	for(int i = 0; i < this->EP.size(); i++)
//	{
//		bool Flag = true;
//		int j = 0;
//		for(; j < this->Population.size(); j++)
//		{
//			if(this->EP[i].Dominate(this->Population[j]))
//			{
//				Flag = false;
//				break;	
//			}
//		}
//		if(Flag)
//		{
//			this->EP.push_back( this->Population[j] );
//		}
//	}
}
void MOEAD::Init()
{
	InitIdealVector();
	InitWeightVector();
	InitNeighborhood();	
	InitializePopulation();
	this->OffSpring = this->Population;
}
void MOEAD::End()
{
	
	//system("Rscript graph.r");
	//cout << Population;
	//cout << this->Weight;
}
