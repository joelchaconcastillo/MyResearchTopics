/**
	Autores:
		 Carlos Segura González
		 Joel Chacón Castillo
	Fecha: 31/10/2016
	Descripción:
**/
#include <fstream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <queue>
#include <algorithm>
#include "Measures.hpp"
#include "Benchmark.hpp"
#include "Individual.hpp"
#include "NSGAII.hpp"
inline ostream & operator << ( ostream &out,vector<Individual> Pool)
{
    for(int i = 0; i < (int)Pool.size(); i++)
    {
        for(int j = 0; j < Pool[i].getObjectives().getNumberObjectives() ; j++)
         out << Pool[i].getObjectives().SpaceObjectives[j].Fitness<<" ";
         out << endl;
    }
    return out;
}
inline ostream & operator << ( ostream &out,vector<double> data)
{
    for(int i = 0; i < (int)data.size(); i++)
    {
        out << data << endl;
    }
    return out;
}
inline vector<Individual> operator+(vector<Individual> PoolA, vector<Individual> PoolB )
{
    vector<Individual> C;
    for(int i=0 ; i < (int)PoolA.size(); i++ )
        C.push_back(PoolA[i]);
    for(int i = 0; i < (int)PoolB.size(); i++)
        C.push_back(PoolB[i]);
    return C;
}
NSGAII::NSGAII(int SizePool, double ProbCross, int NBitsMut, Benchmark &ObjBenchmark, int NumberGenerations, double ParameterDInit ,string ProblemName, int Semilla, string Ruta, string Label, int IdCrossover, int IdMutation, int PeriodReport  )
{
    srand(Semilla);

    this->D = 0;
    this->SizePool = SizePool;
    this->NumberObjectives = ObjBenchmark.getNObjectives();
    this->Dimension = ObjBenchmark.getDimension();
    this->ProbCross = ProbCross;
    this->NBitsMut = NBitsMut;
    this->ObjBenchmark = &ObjBenchmark;
    this->NumberGenerations = NumberGenerations;
    this->CurrentGeneration=0;
    this->IdCrossover = IdCrossover;
    this->IdMutation = IdMutation;
    this->PeriodReport = PeriodReport;
    this->DI = ParameterDInit;
    this->VariableRepresentation = BINARY_ENCODE;
    this->FilenameGenotype = Ruta+"/"+ProblemName+"/Genotype_"+Label+"_"+to_string(Semilla)+".txt";
    this->FilenameFenotype =  Ruta+"/"+ProblemName+"/Fenotype_"+Label+"_"+to_string(Semilla)+".txt";
    this->FilenameFitness = Ruta+"/"+ProblemName+"/Fitness_"+Label+"_"+to_string(Semilla)+".txt";
    this->FileNameSummary = Ruta+"/"+ProblemName+"/SummaryFront_"+Label+"_"+to_string(Semilla)+".txt";
    this->ProblemName = ProblemName;
	//Eliminar el archivo en caso de que existan
	ofstream SummaryGen, SummaryFen, SummaryFit;
    	SummaryGen.open (this->FilenameGenotype);
    	SummaryFen.open (this->FilenameFenotype);
    	SummaryFit.open (this->FilenameFitness);
	SummaryGen << "Total_Generations\t" << this->NumberGenerations<< "\tNumber_Objectives\t"<< this->NumberObjectives <<endl;
	SummaryFen << "Total_Generations\t" << this->NumberGenerations<< "\tDimension\t"<< this->Dimension <<endl;
	SummaryFit << "Total_Generations\t" << this->NumberGenerations<< "\tNumber_Objectives\t"<< this->NumberObjectives <<endl;
 //this->FileNameSummary = FileNameSummary ;

}
NSGAII::NSGAII(int SizePool, double ProbCross, double ProbMut ,Benchmark &ObjBenchmark, int NumberGenerations, double ParameterDInit , string ProblemName, int Semilla, string Ruta, string Label, int IdCrossover, int IdMutation, int PeriodReport  )
{
    srand(Semilla);
    this->DI = ParameterDInit;
    this->D = 0;
    this->SizePool = SizePool;
    this->NumberObjectives = ObjBenchmark.getNObjectives();
    this->Dimension = ObjBenchmark.getDimension();
    this->ProbCross = ProbCross;
    this->ProbMutation = ProbMut;
    this->ObjBenchmark = &ObjBenchmark;
    this->NumberGenerations = NumberGenerations;
    this->CurrentGeneration=0;
    this->IdCrossover = IdCrossover;
    this->IdMutation = IdMutation;
    this->PeriodReport = PeriodReport;
    this->VariableRepresentation = REAL_ENCODE;
    this->FilenameGenotype = Ruta+"/"+ProblemName+"/Genotype_"+Label+"_"+to_string(Semilla)+".txt";
    this->FilenameFenotype =  Ruta+"/"+ProblemName+"/Fenotype_"+Label+"_"+to_string(Semilla)+".txt";
    this->FilenameFitness = Ruta+"/"+ProblemName+"/Fitness_"+Label+"_"+to_string(Semilla)+".txt";
    this->FileNameSummary = Ruta+"/"+ProblemName+"/SummaryFront_"+Label+"_"+to_string(Semilla)+".txt";
    this->ProblemName = ProblemName;
	//Eliminar el archivo en caso de que existan
	ofstream SummaryGen, SummaryFen, SummaryFit;
   if(VariableRepresentation == BINARY_ENCODE)
    	SummaryGen.open (this->FilenameGenotype);
    	SummaryFen.open (this->FilenameFenotype);
    	SummaryFit.open (this->FilenameFitness);
   if(VariableRepresentation == BINARY_ENCODE)
	SummaryGen << "Total_Generations\t" << this->NumberGenerations<< "\tNumber_Objectives\t"<< this->NumberObjectives <<endl;
	SummaryFen << "Total_Generations\t" << this->NumberGenerations<< "\tDimension\t"<< this->Dimension <<endl;
	SummaryFit << "Total_Generations\t" << this->NumberGenerations<< "\tNumber_Objectives\t"<< this->NumberObjectives <<endl;
    //IdealVector.resize(this->NumberObjectives, INFINITY);
    //NadirVector.resize(this->NumberObjectives, -INFINITY);

 //this->FileNameSummary = FileNameSummary ;
}
NSGAII::~NSGAII()
{
   FreePool(Pool_Q);
   FreePool(Survivors);
//   free(ReferencePoint);
}
void NSGAII::ControlParameterD()
{

	double TElapsed = this->CurrentGeneration;
	double TEnd = this->NumberGenerations;
	//En esta sección se controla
	//el decremento del parámetro D
	this->D = DI - DI * ( 2*TElapsed / TEnd  );

  //this->D = DI - (DF - DI )* ( 2*TElapsed / TEnd  );

  this->D = ( 0 > this->D)? 0: this->D ;
}
/**
	Se regresa a los individuos más cercanos
	al vector ideal..
	Closest Ideal Vector
**/
void NSGAII::CIV(vector<ptrIndividual> &Set, vector<ptrIndividual> &Extremal)
{
    Extremal.clear();
	  
	//Definir maximizar o minimizar para cada objetivo
	vector<int> KindObjective =  ObjBenchmark->getTypeDuality();
	vector<double> Best(this->NumberObjectives);
	vector<int> BestIndex(this->NumberObjectives);
	
    //NadirVector.resize(this->NumberObjectives, -INFINITY);
    //IdealVector.resize(this->NumberObjectives, 0);
	for(int i = 0 ; i < this->NumberObjectives; i++)
		if(KindObjective[i]==MAXIMIZE)
			Best[i] = -INFINITY;
		else
			Best[i] = INFINITY;

///REFERENCIA SOLO CADA EJE..
  for(int i = 0; i < this->NumberObjectives ; i++)
        {
                for(int j =0; j < (int)Set.size(); j++)
                {
                        if(KindObjective[i]==MAXIMIZE)
                        {
                                if(Best[i] < Set[j]->getObjectiveValue(i))
                                {
                                        Best[i] = Set[j]->getObjectiveValue(i);
                                        BestIndex[i] = j;
                                }
                        }
                        else if(KindObjective[i] == MINIMIZE)
                        {
                                if(Best[i] > Set[j]->getObjectiveValue(i))
                                {
                                        Best[i] = Set[j]->getObjectiveValue(i);
                                        BestIndex[i] = j;
                                }
                                else if(Best[i] == Set[j]->getObjectiveValue(i) )
                                {
                                    if( Set[j]->getObjectives().Dominate(Set[BestIndex[i]]->getObjectives() ) )
                                    {
                                        Best[i] = Set[j]->getObjectiveValue(i);
                                        BestIndex[i] = j;
                                    }
                                }
//				   if(this->NadirVector[i] < Set[j]->getObjectiveValue(i) )
//					this->NadirVector[i] = Set[j]->getObjectiveValue(i);
//				   if(this->IdealVector[i] > Set[j]->getObjectiveValue(i) )
//					this->IdealVector[i] = Set[j]->getObjectiveValue(i);
                        }
                }
        }

	
///	for(int i = 0; i < this->NumberObjectives ; i++)
///	{
///		for(int j =0; j < (int)Set.size(); j++)
///		{
///			if(KindObjective[i]==MAXIMIZE)
///			{
///				if(ReferencePoint->getObjectiveValue(i) < Set[j]->getObjectiveValue(i))
///				{
///					ReferencePoint->setObjective(i,  Set[j]->getObjectiveValue(i));
///				}
///			}
///			else if(KindObjective[i] == MINIMIZE)
///			{
///				if(ReferencePoint->getObjectiveValue(i) > Set[j]->getObjectiveValue(i))
///				//if(Best[i] > Set[j]->getObjectiveValue(i))
///				{
///					ReferencePoint->setObjective(i,0);//  Set[j]->getObjectiveValue(i));
///				}
///				//else if(ReferencePoint->getObjectiveValue(i) > Set[j]->getObjectiveValue(i))//if(Best[i] == Set[j]->getObjectiveValue(i) )
///				//{
///				//    if( Set[j]->getObjectives().Dominate(Set[BestIndex[i]]->getObjectives() ) )
///				//    {
///				//	Best[i] = Set[j]->getObjectiveValue(i);
///				//    }
///				//}
///			}
///		}
///	}
///
///
/// 	vector<ptrIndividual> Projections(this->NumberObjectives);
///	
///
///	//Generar los vectores de proyección en cada objetivo....
///	for(int m = 0 ; m < this->NumberObjectives; m++)
///	{
///		Projections[m] = new Individual;   
///		*(Projections[m]) = *(Set[0]) ;
///		for(int i = 0; i < this->NumberObjectives; i++)
///		if( m == i) Projections[m]->setObjective(i, this->ReferencePoint->getObjectiveValue(m));
///		 else
///		 Projections[m]->setObjective(m, 0.0);
///	}
///
///	if( ! (CurrentGeneration % 100))
///	{
///		cout << "vector de referencia: ";
///	  for(int m = 0 ; m < this->NumberObjectives; m++)
///	  {
///		//->setObjective(m , Best[m]);
///		cout << ReferencePoint->getObjectiveValue(m) << " ";
///          }
///		cout << endl;
///	}
///	vector<bool> Checked(Set.size());
///	for(int i= 0 ; i < Set.size(); i++) Checked[i] = true;
///        for(int i = 0; i < this->NumberObjectives; i++)
///	{
///		double Min  = INFINITY;
///		int index = -1;
///		//Seleccionar el individuo con menor distancia al punto de referencia..
///		for(int j =0; j < (int)Set.size(); j++)
///		{
///		   double dist =  EuclideanObjectiveDistance(Set[j], Projections[i]);
///			if(Min > dist && Checked[j] )
///			{
///			   Min = dist;
///			   index = j;
///			}
///		}
///		BestIndex.push_back(index);
///		Checked[index] = false;
///	}
///        for(int i = 0; i < this->NumberObjectives; i++) delete Projections[i];
	
	/**
		Agregar los individuos que corresponden a los índices...
	**/
		std::vector<int>::iterator End;
		End = std::unique (BestIndex.begin(), BestIndex.end());
		BestIndex.resize( std::distance(BestIndex.begin(),End));
		//Ordenar los indices en orden ascendente y no tener problemas al momento de eliminar los elementos del vector original
		sort(BestIndex.begin(), BestIndex.end());

		for(int i = BestIndex.size()-1; i >= 0 ; i--)
		{
			int index = BestIndex[i];
			Extremal.push_back( Set[index]);
//			Es el mismo resultado que "Set.erase(Set.begin()+index);"
			iter_swap(Set.begin()+index, Set.end()-1);
			Set.pop_back();
		}

}
double NSGAII::EuclideanVariableDistance(ptrIndividual &indA, ptrIndividual &indB)
{
	double Sum = 0;
	for(int d = 0; d < indA->getDimension(); d++)
	{
		Sum += pow((indA->getVariable(d)- indB->getVariable(d)) / (indA->getMaximum(d) - indA->getMinimum(d)),2);
	}
	return sqrt(Sum);
}
double NSGAII::EuclideanObjectiveDistance(ptrIndividual &indA, ptrIndividual &indB)
{
	double Sum = 0;
	for(int d = 0; d < indA->getNumberObjectives(); d++)
	{
		Sum += pow(indA->getObjectiveValue(d)- indB->getObjectiveValue(d),2);
		//Sum += pow(indA->getObjectiveValue(d)- indB->getObjectiveValue(d) /(NadirVector[d] - IdealVector[d]),2);
	}
	return sqrt(Sum);
}
/**
	Distance Closest Neighbor
  Se busca la distancia mínima entre el conjunto de referencia y el conjunto, los
  individuos con menor distancia se mueven a penalized.
  Nota:  Se puede implementar una algoritmo mas eficiente este es O(n^2)
**/
void NSGAII::DCN(vector<ptrIndividual> &Set, vector<ptrIndividual> &PoolRef, vector<ptrIndividual> &Penalized)
{
	for(int i = 0; i < (int)Set.size(); i++)
	{
		double Distance = INFINITY;
		for(int j=0; j < (int)PoolRef.size(); j++)
		{
			double Euclidean = EuclideanVariableDistance(Set[i], PoolRef[j]);
      			Distance = min(Distance, Euclidean);
		}
		Set[i]->setVariableDistance(Distance);
	}
	for(int i = Set.size()-1; i >=0; i--)
	{	
		if( Set[i]->getVarDistance() < D)
		{
			Penalized.push_back(Set[i]);
//			Set.erase(Set.begin() + i);
			iter_swap(Set.begin()+i, Set.end()-1);
			Set.pop_back();
		}
	}
}
//int NSGAII::SV_DOM( ptrIndividual &A, ptrIndividual &B)
//{
//   int cont = 0;
//	for(int i = 0; i < this->NumberObjectives; i++)
//	 if(B->getObjectiveValue(i) < A->getObjectiveValue(i) )cont++;
//   return cont;
//}
/**
	Objective Distance Closest Negihbor
	Descripcion:
		Obtiene el individuo con mayor DCN en el espacio objetivo, 
		los indices de los individuos considerados pertenecen a Current y al menor 
		rank (frente mas cercano)
**/
void NSGAII::BestODCN( vector<int> &FirstFrontCurrent  ,vector<ptrIndividual> &CurrentSet, vector<ptrIndividual> &Survivors)
{
	int BestIndex=0;
	double MaxObjDistance = -INFINITY;
	int Low_Rank = this->NumberObjectives;
	vector<vector<double>> projections;
	vector<double> selected(this->NumberObjectives);
	double far = INFINITY;
	int indexfar = -1;
	
	for(int i = 0; i < (int)FirstFrontCurrent.size(); i++)
	{
		double Distance = INFINITY;
		int Distance_Subvector_Dominance = 0;
		int IndexBySurvivor = -1;
		double DistanceBySurvivor = INFINITY;
			double value= 0;
		 int indexCurrent = FirstFrontCurrent[i];
		 priority_queue< pair< double, bool>, vector< pair<double, bool> >, greater< pair< double, bool > > > pq;
	       for(int j=0; j < (int)Survivors.size(); j++)
		{
			double value= 0;

			for(int m = 0; m < this->NumberObjectives; m++)
			{			
				double di  = max(0.0,(Survivors[j]->getObjectiveValue(m) - CurrentSet[indexCurrent]->getObjectiveValue(m)) );
				value += di*di;
			}
			//value = sqrt(value);
			   //value = EuclideanObjectiveDistance(CurrentSet[indexCurrent], Survivors[j]);
				pq.push(make_pair(value, true));

		}

		IndexBySurvivor = indexCurrent;
		DistanceBySurvivor = pq.top().first;


		if(MaxObjDistance < DistanceBySurvivor)
		{
			MaxObjDistance = DistanceBySurvivor;
			BestIndex = IndexBySurvivor;
		}
	}

	  Survivors.push_back(CurrentSet[BestIndex]);
	  iter_swap(CurrentSet.begin()+BestIndex,CurrentSet.end()-1);
	  CurrentSet.pop_back();
//	  CurrentSet.erase(CurrentSet.begin()+BestIndex);
}
/**
Obtener el DCN de los individuos penalizados, 
esta seccion es de complejidad O(n^2), puede ser O(n(n-1)/2), hasta O(n log(n)).
**/
void NSGAII::DCN(vector<ptrIndividual> &Set1, vector<ptrIndividual> &Set2)
{  
  for(int i = 0; i < (int)Set1.size(); i++)
  {
	   double Distance = INFINITY;
	    for(int j=0; j < (int)Set2.size(); j++)
	    {
	      double Dis = EuclideanVariableDistance(Set1[i], Set2[j]);
	      Distance = min(Distance, Dis);
	    }
    Set1[i]->setVariableDistance(Distance);
  }
}
/**
	Get the best penalized individual
  Se agrega el individuo con mayor distancia de los considerados en el DCN.
**/
void NSGAII::AddCurrentBestIndividualPenalized(vector<ptrIndividual> &Penalized, vector<ptrIndividual> &CurrentSet)
{
	if(Penalized.empty()) return ;
	double BestPenalized = Penalized[0]->getVarDistance();
	int IndexBest=0;
	for(int i = 0; i < (int)Penalized.size(); i++)
	{
		if(Penalized[i]->getVarDistance() >  BestPenalized )
		{
			IndexBest = i;
			BestPenalized = Penalized[i]->getVarDistance();
		}
	}
	CurrentSet.push_back(Penalized[IndexBest]);
	//Penalized.erase(Penalized.begin()+IndexBest);
	iter_swap(Penalized.begin()+IndexBest, Penalized.end()-1);
	Penalized.pop_back();
}
/**
	Se implementa una union entre el set1 y el set2, la informacion que se almacena en Result son
	los apuntadores de los individuos y no se realizan copias de individuos.
**/
void NSGAII::Union(vector<ptrIndividual> &Set1, vector<ptrIndividual> &Set2, vector<ptrIndividual> &Result)
{
    Result.resize(Set1.size()+Set2.size(), NULL);
    for(int i = 0; i < (int)Set1.size(); i++)
    {
        Result[i] = Set1[i];
    }
    for(int j = 0; j < (int)Set2.size(); j++)
    {
        Result[j+Set1.size()] = Set2[j];
    }
}
void NSGAII::Init_NSGAII()
{
    InitializePool(Survivors);
//    this->ReferencePoint = new Individual;
//    (* ReferencePoint) = (*(Survivors[0]));
    //Inicialmente Pool_Q es un conjunto vacío...
    while(CriterionStop())
    {
          vector<ptrIndividual> CurrentSet;

	  
          //Se realiza la unión entre Survivors y PoolQ
          //se almacena en CurrentSet (solo los apuntadores)
          Union(Survivors, Pool_Q, CurrentSet);
          //Se insertan los individuos extremos
          //en survivors (primero se vacía survivors)
          CIV(CurrentSet, Survivors);
          //Control del parámetro
          ControlParameterD();

          vector<ptrIndividual> Penalized;

	//NadirVector.clear();
	//this->NadirVector.resize(this->NumberObjectives, -INFINITY);
	//for(int i = 0; i < (int)CurrentSet.size(); i++)
	//   {
	//	 int indexCurrent = i;
	//	for(int m = 0; m < this->NumberObjectives; m++)
	//	if(NadirVector[m] < CurrentSet[indexCurrent]->getObjectiveValue(m) )
	//			NadirVector[m] = CurrentSet[indexCurrent]->getObjectiveValue(m);
	//   }
//      NadirVector.clear();
//	this->NadirVector.resize(this->NumberObjectives, -INFINITY);
//	double far = -INFINITY;
//
//	for(int i = 0; i < (int)CurrentSet.size(); i++)
//	   {
//		 int indexCurrent = i;//FirstFrontCurrent[i];
//		double dist = 0;
//		for(int m = 0; m < this->NumberObjectives; m++)
//		   dist += pow(CurrentSet[indexCurrent]->getObjectiveValue(m),2);
//		dist = sqrt(dist);
//		if(dist > far)
//		{
//			far = dist;
//		        for(int m = 0; m < this->NumberObjectives; m++)
//			NadirVector[m] = CurrentSet[indexCurrent]->getObjectiveValue(m);
//		}
//		//for(int m = 0; m < this->NumberObjectives; m++)
//		//if(NadirVector[m] < CurrentSet[indexCurrent]->getObjectiveValue(m) )
//		//		NadirVector[m] = CurrentSet[indexCurrent]->getObjectiveValue(m);
//	   }
          while( (int)Survivors.size() < this->SizePool)
          {
              //Encuentra la distancia mínima y los
              //menores se penalizan y se mueven
              //a Penalized.
              DCN(CurrentSet, Survivors, Penalized);

              //Se agrega el mejor individuo de los penalizados a CurrentSet
              if(CurrentSet.empty())
		{
			  	DCN(Penalized, Survivors);
				AddCurrentBestIndividualPenalized( Penalized, CurrentSet );
		}
              vector<int>  FirstFrontCurrent;
              //Se clasifican los frentes y almacena los índices
              //del mejor frente de la unión entre CurrentSet y Survivors
              Fast_Non_Dominated_Sort_Current(CurrentSet, Survivors, FirstFrontCurrent );

              //Se agrega el individuo con mejor frente, si exiisten del mismo frente
              //se toma el que tenga la mayor mínima distancia en el espacio objetivo
              BestODCN(FirstFrontCurrent, CurrentSet, Survivors);
          }
		//Se asignan las direcciones de memoria de penalized y currentset
		//esto es para reciclar memoria y no volver a pedir memoria en el proceso
		for(int i = 0; i < Penalized.size(); i++)
			Pool_Q[i] = Penalized[i];
		for(int j = 0; j < CurrentSet.size(); j++)
			Pool_Q[j+Penalized.size()] = CurrentSet[j];
		
        New_Pop(Survivors, Pool_Q);


          if( ! (this->CurrentGeneration % PeriodReport) )//|| this->CurrentGeneration < 25000)
          {
              ExportIndividualsFile(this->Survivors, this->FilenameGenotype, this->FilenameFenotype, this->FilenameFitness, this->CurrentGeneration);
              //this->PlotInterfaceRSpaceObjective();
              //this->PlotInterfaceRSpaceVariables();
              //cout << "Generacion...."<<CurrentGeneration<<endl;
		/**
			Para realizar un analisis de los penalizados y del parametro D teorico
		**/
		//cout << CurrentGeneration << " "<<Penalized.size() << " " <<this->D<<endl;
		cout << "Generation: "<<CurrentGeneration<<endl;
          }
    }

          End();
}

/**
    Agregar información al final del archivo...
**/
void NSGAII::InitializePool(vector<ptrIndividual> &Survivors)
{
    Survivors.resize(this->SizePool);
    for(int i = 0; i < this->SizePool; i++)
    {
        Survivors[i] = new Individual;
        Survivors[i]->InitializeIndividual(this->ObjBenchmark);
    }
}
void NSGAII::FreePool(vector<ptrIndividual> &Pool)
{
  for(int i = 0; i < (int)Pool.size(); i++)
    delete (Pool[i]);
    Pool.clear();
}
void NSGAII::New_Pop(vector <ptrIndividual> &Survivors, vector <ptrIndividual> &Pool_Q)
{
    if( Pool_Q.empty() )
      InitializePool(Pool_Q);

    Selection(Survivors, Pool_Q);
    Recombination(Pool_Q);
	if(this->VariableRepresentation == BINARY_ENCODE)
		BitMutation(Pool_Q ,this->NBitsMut);
	else if(this->VariableRepresentation == REAL_ENCODE)
	{
		switch(this->IdMutation)
		{
		   case _POLYNOMIAL:
			PolynomialMutation(Pool_Q, ProbMutation);
		   break;
		   case _NORMAL:
		   	NormallyDistribuitedMutation(Pool_Q);
		   break;
		   case _RANDOM:
			RandomMutation(Pool_Q);
		   break;
		}
	}
    Evaluation(Pool_Q);
}
void NSGAII::Selection(vector <ptrIndividual> &Survivors, vector <ptrIndividual> &Pool_Q)
{

    for(int i = 0; i < (int)Survivors.size(); i++)
    {
        int Index1 = rand()%Survivors.size();
        int Index2 = rand()%Survivors.size();

        if( Survivors[Index1]->getRank() < Survivors[Index2]->getRank() )
        {
            *(Pool_Q[i]) = *(Survivors[Index1]);
            //Pool_Q.push_back(Survivors[Index1]);
        }
        else if(Survivors[Index1]->getRank() == Survivors[Index2]->getRank())
        {
           // if(Survivors[Index1]->getObjDistance() > Survivors[Index2]->getObjDistance())
           // {
           //     *(Pool_Q[i]) = *(Survivors[Index1]);
           //     // Pool_Q.push_back(Survivors[Index1]);
           // }
           // else if(Survivors[Index1]->getObjDistance() < Survivors[Index2]->getObjDistance())
           // {
           //   *(Pool_Q[i]) = *(Survivors[Index2]);
           //     // Pool_Q.push_back(Survivors[Index2]);
           // }else
           // {
		///////Revisar el DCN....
	//	int a=0, b = 0;
	//	for(int i = 0; i < this->NumberObjectives; i++)
	//	{
	//	    if(Survivors[Index1]->getObjectiveValue(i) < Survivors[Index2]->getObjectiveValue(i))
	//		a++;
	//	    else if(Survivors[Index1]->getObjectiveValue(i) > Survivors[Index2]->getObjectiveValue(i))
	//		b++;

	//	}
	//	if(a > b)
        //          *(Pool_Q[i]) = *(Survivors[Index1]);
	//	else if(b > a)		
        //        *(Pool_Q[i]) = *(Survivors[Index2]);
        //        else
	//	{
	//		if (getRandom(0,1.0) <= 0.5)
	//		{
	//		  *(Pool_Q[i]) = *(Survivors[Index1]);
	//		    // Pool_Q.push_back(Survivors[Index1]);
	//		}else
	//		*(Pool_Q[i]) = *(Survivors[Index2]);
	//		    // Pool_Q.push_back(Survivors[Index2]);
	//	}


				if (getRandom(0,1.0) <= 0.5)
			{
			  *(Pool_Q[i]) = *(Survivors[Index1]);
			    // Pool_Q.push_back(Survivors[Index1]);
			}else
			*(Pool_Q[i]) = *(Survivors[Index2]);
			    // Pool_Q.push_back(Survivors[Index2]);
           // }
        }
        else
        {
          *(Pool_Q[i]) = *(Survivors[Index2]);
            // Pool_Q.push_back(Survivors[Index2]);
        }
    }
}
void NSGAII::Recombination(vector <ptrIndividual> &Pool_Q)
{
	if(this->VariableRepresentation == BINARY_ENCODE)
		UniformCross(Pool_Q, Pool_Q, this->ProbCross);
	else if(this->VariableRepresentation == REAL_ENCODE)
	{
		
			double TElapsed = this->CurrentGeneration;
			double TEnd = this->NumberGenerations;
			double ProbVariable  = 1.0-( TElapsed / TEnd  );

			switch(this->IdCrossover)
			{
			   case _SBX:
				SBX(Pool_Q, Pool_Q, this->ProbCross);
			   break;
			   case _SBXH:
				SBXHybrid(Pool_Q, Pool_Q, this->ProbCross);
			   break;
			   case _SBXHD:
				ProbVariable = max(0.5, ProbVariable);
				if(CurrentGeneration%100 == 0)
				cout << ProbVariable << endl;
				SBXHybridDynamic(Pool_Q, Pool_Q, this->ProbCross, ProbVariable);
			   break;
			   case _BLX:
				BLX(Pool_Q, Pool_Q, this->ProbCross);
			   break;
			   case _FUZZY:
				FuzzyCrossOver(Pool_Q, Pool_Q, this->ProbCross);
			   break;
			   case _HBX:
				HBX(Pool_Q, Pool_Q, this->ProbCross);
			   break;
			}
	}
}
void NSGAII::Evaluation(vector<ptrIndividual> &Pool_Q)
{
    for(int i = 0; i < (int)Pool_Q.size(); i++)
    {
        Pool_Q[i]->EvalIndividual();
      	Pool_Q[i]->setVariableDistance(0);
      	Pool_Q[i]->setObjDistance(0);
    }
}
double NSGAII::getRandom(double Min, double Max)
{
    double f = (double)rand() / RAND_MAX;
    return Min + f * (Max - Min);
}
bool NSGAII::CriterionStop()
{
    if(this->CurrentGeneration < this->NumberGenerations)
    {
        this->CurrentGeneration++;
        return true;
    }
    else
    {
        return false;
    }
}

void NSGAII::Fast_Non_Dominated_Sort_Current(vector<ptrIndividual> &Current, vector<ptrIndividual> &Survivors, vector<int> &CurrentFirstFront)
{
    CurrentFirstFront.clear();
    vector<ptrIndividual> Pop;
    //Realizar la unión de los dos conjuntos
    Union(Current, Survivors, Pop);

    vector< vector<int> > F(1), S(Pop.size());
    vector<int> n(Pop.size(),0);

    for(int i = 0; i < (int)Pop.size(); i++)
    {
        for(int j = 0; j < (int)Pop.size(); j++)
        {
            if(j==i) continue;
            if( Pop[i]->getObjectives().Dominate(Pop[j]->getObjectives()) )
            {
                S[i].push_back(j);
            }
            else if( Pop[j]->getObjectives().Dominate(Pop[i]->getObjectives()))
            {
                n[i]++;
            }
        }
        if( n[i] == 0)
        {
            F[0].push_back(i);
        }
    }
    int k=0;

    while(F[k].size())
    {
        vector<int> Q;
        for(int i = 0; i  < (int)F[k].size(); i++)
        {
            int indexSi = F[k][i];
            for(int j = 0; j < (int)S[indexSi].size(); j++)
            {
                n[S[indexSi][j]]--;
                if(n[S[indexSi][j]]== 0)
                {
                    Q.push_back(S[indexSi][j]);
                }
            }
        }
      k++;
        F.push_back(Q);
    }

    bool FlagFirstFront = true;
     for(int i = 0; i < (int)F.size(); i++)
    {
        for(int j = 0; j < (int)F[i].size(); j++)
        {
            int indexIndividual = F[i][j];
            if(indexIndividual < (int)Current.size())
            {
              Pop[indexIndividual]->setRank(i);
              Current[indexIndividual] = Pop[indexIndividual];

              if( FlagFirstFront )
                  CurrentFirstFront.push_back(indexIndividual);
            }else
            {
              Survivors[indexIndividual-Current.size()]->setRank(i);
            }
        }

        if(CurrentFirstFront.size())
          FlagFirstFront =false;
    }
  //  return CurrentFirstFront;
}
void NSGAII::PlotInterfaceRSpaceObjective()
{
    string Comand, X = "", Y = "";

    for(int i = 0; i < (int)this->Pool_Q.size(); i++)
    {
            std::stringstream temporal;
            temporal << Pool_Q[i]->getObjectives().SpaceObjectives[0].Fitness << " , ";
            X += temporal.str();
            temporal.str("");
            temporal << Pool_Q[i]->getObjectives().SpaceObjectives[1].Fitness << " , ";
            Y += temporal.str();
            temporal.str("");
    }
    X = X.substr(0, X.size()-2);
    Y = Y.substr(0, Y.size()-2);
    Comand = "echo \"  pdf(file = paste('Objective_"+this->ProblemName+"_"+to_string(this->CurrentGeneration)+"','.pdf' , sep = '' )) ;  plot(x = c("+ X +"), y = c("+Y+"), main=('NSGAII Generation "+to_string(this->CurrentGeneration)+"') ,xlab='f1', ylab='f2' ) ;    \" | R --Silent --no-save 2>/dev/null | tail -n 0";

    //Comand = "echo \"plot(x = c(3.47788,4), y = c(4,5) ) \" | R --Silent --no-save 2>/dev/null | tail -n 0";
   // cout << Comand<<endl;
    system(Comand.c_str());
}
void NSGAII::PlotInterfaceRSpaceVariables()
{
    string Comand, X = "", Y = "";

    for(int i = 0; i < (int)this->Pool_Q.size(); i++)
    {
            std::stringstream temporal;
            temporal << Pool_Q[i]->getFenotype(0) << " , ";
            X += temporal.str();
            temporal.str("");
            temporal << Pool_Q[i]->getFenotype(1) << " , ";
            Y += temporal.str();
            temporal.str("");
    }
    X = X.substr(0, X.size()-2);
    Y = Y.substr(0, Y.size()-2);
    Comand = "echo \"  pdf(file = paste('Desicion_"+this->ProblemName+"_"+to_string(this->CurrentGeneration)+"','.pdf' , sep = '' )) ;  plot(x = c("+ X +"), y = c("+Y+"), main=('NSGAII Generation "+to_string(this->CurrentGeneration)+"') ,xlab='f1', ylab='f2' ) ;    \" | R --Silent --no-save 2>/dev/null | tail -n 0";

    //Comand = "echo \"plot(x = c(3.47788,4), y = c(4,5) ) \" | R --Silent --no-save 2>/dev/null | tail -n 0";
   // cout << Comand<<endl;
    system(Comand.c_str());
}
void NSGAII::End()
{
 ofstream save;
  save.open (FileNameSummary);
   save << this->Survivors.size() << " " << this->NumberObjectives<<endl;
  for(int i = 0; i < (int)this->Survivors.size(); i++)
  {
    for(int m = 0; m < this->NumberObjectives; m++)
      save << this->Survivors[i]->getObjectiveValue(m)<< " ";
    save << endl;
  }
  //save << this->Survivors;
}
