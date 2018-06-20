#include <iostream>
#include <cmath>
#include "wfg/WFG1/WFG1.h"
#include "wfg/WFG2/WFG2.h"
#include "wfg/WFG3/WFG3.h"
#include "wfg/WFG4/WFG4.h"
#include "wfg/WFG5/WFG5.h"
#include "wfg/WFG6/WFG6.h"
#include "wfg/WFG7/WFG7.h"
#include "wfg/WFG8/WFG8.h"
#include "wfg/WFG9/WFG9.h"
#include "Benchmark.hpp"
using namespace std;
Benchmark::Benchmark()
{
}
Benchmark::Benchmark(int TypeProblem)
{
    this->TypeProblem = TypeProblem;
    this->DefaultDimension = 2;
    this->SizeChrom = 30;
    InitConfig();
}
void Benchmark::SetAllMinimize()
{
    TypeDuality.resize(this->NObjectives, MINIMIZE);
}
void Benchmark::SetAllMaximize()
{
    TypeDuality.resize(this->NObjectives, MAXIMIZE);
}
void Benchmark::SetAllBounds(vector<vector<double>> &MatrixBound,double Min, double Max)
{
        for(int i=0; i < this->Dimension; i++)
            {
                vector<double> temp(2);
                temp[0] = Min;
                temp[1] = Max;
                MatrixBound.push_back(temp);
            }
}
void Benchmark::Eval(vector<double> &X, vector<double> &obj)
{
   switch(this->TypeProblem)
    {
        case SCH1:
            sch1(X, obj);
        break;
        case SCH2:
            sch2(X, obj);
        break;
        case FON:
            fon(X, obj);
        break;
        case KUR:
            kur(X, obj);
        break;
        case POL:
            pol(X, obj);
        break;
        case VNT:
            vnt(X, obj);
        break;
        case ZDT1:
            zdt1(X, obj);
        break;
        case ZDT2:
            zdt2(X, obj);
        break;
        case ZDT3:
            zdt3(X, obj);
        break;
        case ZDT4:
            zdt4(X, obj);
        break;
        case ZDT5:
            zdt5(X, obj);
        break;
        case ZDT6:
            zdt6(X, obj);
        break;
        case BNH:
            bnh(X, obj);
        break;
        case OSY:
            osy(X, obj);
        break;
        case SRN:
            srn(X, obj);
        break;
        case TNK:
            tnk(X, obj);
        break;
	case SINGLE:
	   Single(X, obj);
	break;
	case Type_WFG1:
	   wfg1(X, obj);
	break;
	case Type_WFG2:
	   wfg2(X, obj);
	break;
	case Type_WFG3:
	   wfg3(X, obj);
	break;
	case Type_WFG4:
	   wfg4(X, obj);
	break;
	case Type_WFG5:
	   wfg5(X, obj);
	break;
	case Type_WFG6:
	   wfg6(X, obj);
	break;
	case Type_WFG7:
	   wfg7(X, obj);
	break;
	case Type_WFG8:
	   wfg8(X, obj);
	break;
	case Type_WFG9:
	   wfg9(X, obj);
	break;
	case DTLZ1:
	   dtlz1(X, obj);
	break;
	case DTLZ2:
	   dtlz2(X, obj);
	break;
	case DTLZ3:
	   dtlz3(X, obj);
	break;
	case DTLZ4:
	   dtlz4(X, obj);
	break;
	case DTLZ5:
	   dtlz5(X, obj);
	break;
	case DTLZ6:
	   dtlz6(X, obj);
	break;
	case DTLZ7:
	   dtlz7(X, obj);
	break;
	case UF1:
	   uf1(X,obj);
	break;
	case UF2:
	   uf2(X,obj);
	break;
	case UF3:
	   uf3(X,obj);
	break;
	case UF4:
	   uf4(X,obj);
	break;
	case UF5:
	   uf5(X,obj);
	break;
	case UF6:
	   uf6(X,obj);
	break;
	case UF7:
	   uf7(X,obj);
	break;
	case UF8:
	   uf8(X,obj);
	break;
	case UF9:
	   uf9(X,obj);
	break;
	case UF10:
	   uf10(X,obj);
	break;
    }
}

/**
    Establece las variables de configuración para
    inicializar la configuración de las funciones de prueba
**/
void Benchmark::InitConfig()
{
    switch(this->TypeProblem)
    {
        case SCH1:
            this->NObjectives = 2;
            this->Dimension = 1;
            SetAllMinimize();
            SetAllBounds(Bounds,-1000, 1000);
            SetAllBounds(OptimalBounds,0,2);

        break;
        case SCH2:
            this->NObjectives = 2;
            this->Dimension = 1;
            SetAllMinimize();
            SetAllBounds(Bounds, -1000, 1000);
        break;
        case FON:
            this->NObjectives = 2;
            this->Dimension = DefaultDimension;
            SetAllMinimize();
            SetAllBounds(Bounds, -4, 4);
        break;
        case KUR:
            this->NObjectives = 2;
            this->Dimension = 3;
            SetAllMinimize();
            SetAllBounds(Bounds, -5, 5);
        break;
        case POL:
            this->NObjectives = 2;
            this->Dimension = 2;
            SetAllMinimize();
            SetAllBounds(Bounds, -M_PI, M_PI);
        break;
        case VNT:
            this->NObjectives = 3;
            this->Dimension = 2;
            SetAllMinimize();
            SetAllBounds(Bounds, -5, 5);
        break;
        case ZDT1:
            this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
        case ZDT2:
            this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
        case ZDT3:
            this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
        case ZDT4:
            this->NObjectives = 2;
            this->Dimension = 10;
            SetAllMinimize();
            SetAllBounds(Bounds, -5, 5);
            this->Bounds[0][0] = 0;
            this->Bounds[0][1] = 1;
        break;
        case ZDT5:
            this->NObjectives = 2;
            this->Dimension = 11;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
        case ZDT6:
            this->NObjectives = 2;
            this->Dimension = 10;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
        case BNH:
            this->NObjectives = 2;
            this->Dimension = 2;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
        case OSY:
            this->NObjectives = 2;
            this->Dimension = 6;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
        case SRN:
            this->NObjectives = 2;
            this->Dimension = 2;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
        case TNK:
            this->NObjectives = 2;
            this->Dimension = 2;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
	case SINGLE:
	   this->NObjectives = 1;
	   this->Dimension = 2;
	   SetAllMinimize();
	   SetAllBounds(Bounds,0, 1);
	break;
	case Type_WFG1:
	   WFG1 Objwfg1;
	   this->NObjectives = 2;
	   Objwfg1.init( this->NObjectives);
	   this->Dimension = Objwfg1.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		this->Bounds.push_back(Row);
	   }
	break;
	case Type_WFG2:
	   WFG2 Objwfg2;
	   this->NObjectives = 2;
	   Objwfg2.init( this->NObjectives);
	   this->Dimension = Objwfg2.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		//Row.push_back(1);
		this->Bounds.push_back(Row);
	   }
	break;
	case Type_WFG3:
	   WFG3 Objwfg3;
	   this->NObjectives = 2;
	   Objwfg3.init( this->NObjectives);
	   this->Dimension = Objwfg3.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		this->Bounds.push_back(Row);
	   }
	break;
	case Type_WFG4:
	   WFG4 Objwfg4;
	   this->NObjectives = 2;
	   Objwfg4.init( this->NObjectives);
	   this->Dimension = Objwfg4.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		this->Bounds.push_back(Row);
	   }
	break;
	case Type_WFG5:
	   WFG5 Objwfg5;
	   this->NObjectives = 2;
	   Objwfg5.init( this->NObjectives);
	   this->Dimension = Objwfg5.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		this->Bounds.push_back(Row);
	   }
	break;
	case Type_WFG6:
	   WFG6 Objwfg6;
	   this->NObjectives = 2;
	   Objwfg6.init( this->NObjectives);
	   this->Dimension = Objwfg6.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		this->Bounds.push_back(Row);
	   }
	break;
	case Type_WFG7:
	   WFG7 Objwfg7;
	   this->NObjectives = 2;
	   Objwfg7.init( this->NObjectives);
	   this->Dimension = Objwfg7.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		this->Bounds.push_back(Row);
	   }
	break;
	case Type_WFG8:
	   WFG8 Objwfg8;
	   this->NObjectives = 2;
	   Objwfg8.init( this->NObjectives);
	   this->Dimension = Objwfg8.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		this->Bounds.push_back(Row);
	   }
	break;
	case Type_WFG9:
	   WFG9 Objwfg9;
	   this->NObjectives = 2;
	   Objwfg9.init( this->NObjectives);
	   this->Dimension = Objwfg9.getDimension();
	   SetAllMinimize();
	   for(int i = 0; i < this->Dimension; i++)
	   {
		vector<double> Row;
		//Límite Inferior
		Row.push_back(0.0);
		//Límite Superior
		Row.push_back(2*(i+1));
		this->Bounds.push_back(Row);
	   }
	break;
	case DTLZ1:
            this->NObjectives = 2;
            this->Dimension = this->NObjectives + 5 -1; // n = M+k-1
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
	case DTLZ2:
            this->NObjectives = 2;
            this->Dimension = this->NObjectives + 10 -1; // n = M+k-1
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
	case DTLZ3:
            this->NObjectives = 2;
            this->Dimension = this->NObjectives + 10 -1; // n = M+k-1
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
	case DTLZ4:
            this->NObjectives = 2;
            this->Dimension = this->NObjectives + 10 -1; // n = M+k-1
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
	case DTLZ5:
            this->NObjectives = 2;
            this->Dimension = this->NObjectives + 10 -1; // n = M+k-1
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
	case DTLZ6:
            this->NObjectives = 2;
            this->Dimension = this->NObjectives + 10 -1; // n = M+k-1
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
	case DTLZ7:
            this->NObjectives = 2;
            this->Dimension = this->NObjectives + 20 -1; // n = M+k-1
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
        break;
	case UF1:
	    this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
            SetAllBounds(Bounds, -1, 1);
	    this->Bounds[0][0] = 0.0;
	    this->Bounds[0][1] = 1.0;
		
	break;
	case UF2:
	    this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
	    SetAllBounds(Bounds, -1, 1);
	    this->Bounds[0][0] = 0.0;
	    this->Bounds[0][1] = 1.0;
	break;
	case UF3:
	    this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
	break;
	case UF4:
	    this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
            SetAllBounds(Bounds, -2.0, 2.0);
	    this->Bounds[0][0] = 0.0;
	    this->Bounds[0][1] = 1.0;
	break;
	case UF5:
	    this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
	    SetAllBounds(Bounds, -1.0, 1.0);
	    this->Bounds[0][0] = 0.0;
	    this->Bounds[0][1] = 1.0;
	break;
	case UF6:
	    this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
	    SetAllBounds(Bounds, -1.0, 1.0);
	    this->Bounds[0][0] = 0.0;
	    this->Bounds[0][1] = 1.0;
	break;
	case UF7:
	    this->NObjectives = 2;
            this->Dimension = 30;
            SetAllMinimize();
	    SetAllBounds(Bounds, -1.0, 1.0);
	    this->Bounds[0][0] = 0.0;
	    this->Bounds[0][1] = 1.0;
	break;
	case UF8:
	    this->NObjectives = 2;
            this->Dimension = 6;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
	break;
	case UF9:
	    this->NObjectives = 2;
            this->Dimension = 6;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
	break;
	case UF10:
	    this->NObjectives = 2;
            this->Dimension = 6;
            SetAllMinimize();
            SetAllBounds(Bounds, 0, 1);
	break;
    }
}
/**
    # de objetivos 2
**/
void Benchmark::sch1(vector<double> &X, vector<double> &obj)
{
    //Objetivo 1
    obj[0] = pow(X[0], 2.0);
    //Objetivo 2
    obj[1] = pow(X[0]-2.0, 2.0);
}
/**
    # de objetivos 2
**/
void Benchmark::sch2(vector<double> &X, vector<double> &obj)
{
     if (X[0]<=1.0)
    {
        obj[0] = -X[0];
        obj[1] = pow((X[0]-5.0),2.0);
        return;
    }
    if (X[0]<=3.0)
    {
        obj[0] = X[0]-2.0;
        obj[1] = pow((X[0]-5.0),2.0);
        return;
    }
    if (X[0]<=4.0)
    {
        obj[0] = 4.0-X[0];
        obj[1] = pow((X[0]-5.0),2.0);
        return;
    }
    obj[0] = X[0]-4.0;
    obj[1] = pow((X[0]-5.0),2.0);
    return;
}
/**
    # de objetivos 2
**/
void  Benchmark::fon(vector<double> &X, vector<double> &obj)
{
    double s1, s2;
    int i;
    s1 = s2 = 0.0;
    int nreal = X.size();
    for (i=0; i<nreal; i++)
    {
        s1 += pow((X[i]-(1.0/sqrt((double)nreal))),2.0);
        s2 += pow((X[i]+(1.0/sqrt((double)nreal))),2.0);
    }
    obj[0] = 1.0 - exp(-s1);
    obj[1] = 1.0 - exp(-s2);
    return;
}
/**
    # de objetivos 2
**/
void Benchmark::kur(vector<double> &X, vector<double> &obj)
{
    int i;
    double res1, res2;
    res1 = -0.2*sqrt((X[0]*X[0]) + (X[1]*X[1]));
    res2 = -0.2*sqrt((X[1]*X[1]) + (X[2]*X[2]));
    obj[0] = -10.0*( exp(res1) + exp(res2));
    obj[1] = 0.0;
    for (i=0; i<3; i++)
    {
        obj[1] += pow(fabs(X[i]),0.8) + 5.0*sin(pow(X[i],3.0));
    }
    return;
}
/**
    # de objetivos 2
**/
void Benchmark::pol(vector<double> &X, vector<double> &obj)
{
    double a1, a2, b1, b2;
    a1 = 0.5*sin(1.0) - 2.0*cos(1.0) + sin(2.0) - 1.5*cos(2.0);
    a2 = 1.5*sin(1.0) - cos(1.0) + 2.0*sin(2.0) - 0.5*cos(2.0);
    b1 = 0.5*sin(X[0]) - 2.0*cos(X[0]) + sin(X[1]) - 1.5*cos(X[1]);
    b2 = 1.5*sin(X[0]) - cos(X[0]) + 2.0*sin(X[1]) - 0.5*cos(X[1]);
    obj[0] = 1.0 + pow((a1-b1),2.0) + pow((a2-b2),2.0);
    obj[1] = pow((X[0]+3.0),2.0) + pow((X[1]+1.0),2.0);
    return;
}
/**
    # de objetivos 3
**/
void Benchmark::vnt(vector<double> &X, vector<double> &obj)
{
    obj[0] = 0.5*(X[0]*X[0] + X[1]*X[1]) + sin(X[0]*X[0] + X[1]*X[1]);
    obj[1] = (pow((3.0*X[0] - 2.0*X[1] + 4.0),2.0))/8.0 + (pow((X[0]-X[1]+1.0),2.0))/27.0 + 15.0;
    obj[2] = 1.0/(X[0]*X[0] + X[1]*X[1] + 1.0) - 1.1*exp(-(X[0]*X[0] + X[1]*X[1]));
    return;
}
/**
    # de objetivos 2
**/
void Benchmark::zdt1(vector<double> &X, vector<double> &obj)
{
        double f1, f2, g, h;
        int i;
        f1 = X[0];
        g = 0.0;
        for (i=1; i<30; i++)
        {
            g += X[i];
        }
        g = 9.0*g/29.0;
        g += 1.0;
        h = 1.0 - sqrt(f1/g);
        f2 = g*h;
        obj[0] = f1;
        obj[1] = f2;
        return;
}
/**
    # de objetivos 2
**/
void Benchmark::zdt2(vector<double> &X, vector<double> &obj)
{
      double f1, f2, g, h;
    int i;
    f1 = X[0];
    g = 0.0;
    for (i=1; i<30; i++)
    {
        g += X[i];
    }
    g = 9.0*g/29.0;
    g += 1.0;
    h = 1.0 - pow((f1/g),2.0);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}
/**
    # de objetivos 2
**/
void Benchmark::zdt3(vector<double> &X, vector<double> &obj)
{
      double f1, f2, g, h;
    int i;
    f1 = X[0];
    g = 0.0;
    for (i=1; i<30; i++)
    {
        g += X[i];
    }
    g = 9.0*g/29.0;
    g += 1.0;
    h = 1.0 - sqrt(f1/g) - (f1/g)*sin(10.0*M_PI*f1);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}
/**
    # de objetivos 2
**/
void Benchmark::zdt4(vector<double> &X, vector<double> &obj)
{
    double PI = 3.141592653589793;
    double f1, f2, g, h;
    int i;
    f1 = X[0];
    g = 0.0;
    for (i=1; i<10; i++)
    {
        //g += X[i]*X[i] - 10.0*cos(4.0*M_PI*X[i]);
        g += X[i]*X[i] - 10.0*cos(4.0*PI*X[i]);
    }
    g += 91.0;
    h = 1.0 - sqrt(f1/g);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}
/**
    # de objetivos 2
**/
void Benchmark::zdt5(vector<double> &X, vector<double> &obj)
{
    /*  int i, j;
    int u[11];
    int v[11];
    double f1, f2, g, h;
    for (i=0; i<11; i++)
    {
        u[i] = 0;
    }
    for (j=0; j<30; j++)
    {
        if (gene[0][j] == 1)
        {
            u[0]++;
        }
    }
    for (i=1; i<11; i++)
    {
        for (j=0; j<4; j++)
        {
            if (gene[i][j] == 1)
            {
                u[i]++;
            }
        }
    }
    f1 = 1.0 + u[0];
    for (i=1; i<11; i++)
    {
        if (u[i] < 5)
        {
            v[i] = 2 + u[i];
        }
        else
        {
            v[i] = 1;
        }
    }
    g = 0;
    for (i=1; i<11; i++)
    {
        g += v[i];
    }
    h = 1.0/f1;
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;*/

}
/**
    # de variables binarias 10
    # de objetivos 2
**/
void Benchmark::zdt6(vector<double> &X, vector<double> &obj)
{
      double f1, f2, g, h;
    int i;
    f1 = 1.0 - ( exp(-4.0*X[0]) ) * pow( (sin(6.0*M_PI*X[0])),6.0 );
    g = 0.0;
    for (i=1; i<10; i++)
    {
        g += X[i];
    }
    g = g/9.0;
    g = pow(g,0.25);
    g = 1.0 + 9.0*g;
    h = 1.0 - pow((f1/g),2.0);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;

}

/**
    # de variables binarias 2
    # de objetivos 2
**/
void Benchmark::bnh(vector<double> &X, vector<double> &obj)
{
    obj[0] = 4.0*(X[0]*X[0] + X[1]*X[1]);
    obj[1] = pow((X[0]-5.0),2.0) + pow((X[1]-5.0),2.0);
//    constr[0] = 1.0 - (pow((xreal[0]-5.0),2.0) + xreal[1]*xreal[1])/25.0;
//    constr[1] = (pow((xreal[0]-8.0),2.0) + pow((xreal[1]+3.0),2.0))/7.7 - 1.0;
    return;
}

/**
    # de objetivos 2
**/
void Benchmark::osy(vector<double> &X, vector<double> &obj)
{
    obj[0] = -(25.0*pow((X[0]-2.0),2.0) + pow((X[1]-2.0),2.0) + pow((X[2]-1.0),2.0) + pow((X[3]-4.0),2.0) + pow((X[4]-1.0),2.0));
    obj[1] = X[0]*X[0] +  X[1]*X[1] + X[2]*X[2] + X[3]*X[3] + X[4]*X[4] + X[5]*X[5];
   /* constr[0] = (xreal[0]+xreal[1])/2.0 - 1.0;
    constr[1] = 1.0 - (xreal[0]+xreal[1])/6.0;
    constr[2] = 1.0 - xreal[1]/2.0 + xreal[0]/2.0;
    constr[3] = 1.0 - xreal[0]/2.0 + 3.0*xreal[1]/2.0;
    constr[4] = 1.0 - (pow((xreal[2]-3.0),2.0))/4.0 - xreal[3]/4.0;
    constr[5] = (pow((xreal[4]-3.0),2.0))/4.0 + xreal[5]/4.0 - 1.0;*/
    return;
}

/**
    # de objetivos 2
**/
void Benchmark::srn(vector<double> &X, vector<double> &obj)
{
    obj[0] = 2.0 + pow((X[0]-2.0),2.0) + pow((X[1]-1.0),2.0);
    obj[1] = 9.0*X[0] - pow((X[1]-1.0),2.0);
    /*constr[0] = 1.0 - (pow(xreal[0],2.0) + pow(xreal[1],2.0))/225.0;
    constr[1] = 3.0*xreal[1]/10.0 - xreal[0]/10.0 - 1.0;*/
    return;
}


/**
    # de objetivos 2
**/
void Benchmark::tnk(vector<double> &X, vector<double> &obj)
{
    obj[0] = X[0];
    obj[1] = X[1];
   /* if (xreal[1] == 0.0)
    {
        constr[0] = -1.0;
    }
    else
    {
        constr[0] = xreal[0]*xreal[0] + xreal[1]*xreal[1] - 0.1*cos(16.0*atan(xreal[0]/xreal[1])) - 1.0;
    }
    constr[1] = 1.0 - 2.0*pow((xreal[0]-0.5),2.0) + 2.0*pow((xreal[1]-0.5),2.0);*/
    return;
}

void Benchmark::Single(vector<double> &X,vector<double> &obj)
{
	obj[0] = X[0]*X[0] + X[1]*X[1];
}

void Benchmark::wfg1(vector<double> &X, vector<double> &obj)
{
	WFG1 Objwfg1;
	Objwfg1.init(obj.size() );
	this->Dimension = Objwfg1.getDimension();
	Objwfg1.evaluate(X, obj);
}
void Benchmark::wfg2(vector<double> &X, vector<double> &obj)
{
	WFG2 Objwfg2;
	Objwfg2.init(obj.size() );
	this->Dimension = Objwfg2.getDimension();
	Objwfg2.evaluate(X, obj);
}
void Benchmark::wfg3(vector<double> &X, vector<double> &obj)
{
	WFG3 Objwfg3;
	Objwfg3.init(obj.size() );
	this->Dimension = Objwfg3.getDimension();
	Objwfg3.evaluate(X, obj);
}
void Benchmark::wfg4(vector<double> &X, vector<double> &obj)
{
	WFG4 Objwfg4;
	Objwfg4.init(obj.size() );
	this->Dimension = Objwfg4.getDimension();
	Objwfg4.evaluate(X, obj);
}
void Benchmark::wfg5(vector<double> &X, vector<double> &obj)
{
	WFG5 Objwfg5;
	Objwfg5.init(obj.size() );
	this->Dimension = Objwfg5.getDimension();
	Objwfg5.evaluate(X, obj);
}
void Benchmark::wfg6(vector<double> &X, vector<double> &obj)
{
	WFG6 Objwfg6;
	Objwfg6.init(obj.size() );
	this->Dimension = Objwfg6.getDimension();
	Objwfg6.evaluate(X, obj);
}
void Benchmark::wfg7(vector<double> &X, vector<double> &obj)
{
	WFG7 Objwfg7;
	Objwfg7.init(obj.size() );
	this->Dimension = Objwfg7.getDimension();
	Objwfg7.evaluate(X, obj);
}
void Benchmark::wfg8(vector<double> &X, vector<double> &obj)
{
	WFG8 Objwfg8;
	Objwfg8.init(obj.size() );
	this->Dimension = Objwfg8.getDimension();
	Objwfg8.evaluate(X, obj);
}
void Benchmark::wfg9(vector<double> &X, vector<double> &obj)
{
	WFG9 Objwfg9;
	Objwfg9.init(obj.size() );
	this->Dimension = Objwfg9.getDimension();
	Objwfg9.evaluate(X, obj);
}
void Benchmark::dtlz1(vector<double> &X, vector<double> &obj)
{

  int k = X.size()- obj.size() + 1;

  double g = 0.0 ;

  for (int i = X.size() - k; i < X.size(); i++)
    g += (X[i] - 0.5)*(X[i] - 0.5) - cos(20.0 * M_PI * (X[i] - 0.5));

  g = 100 * (k + g);
  for (int i = 0; i < obj.size(); i++)
    obj[i] = (1.0 + g) * 0.5;

  for (int i = 0; i < obj.size(); i++){
    for (int j = 0; j < obj.size() - (i + 1); j++)
      obj[i] *= X[j];
      if (i != 0){
        int aux = obj.size() - (i + 1);
        obj[i] *= 1 - X[aux];
      } //if
  }//for

}
void Benchmark::dtlz2(vector<double> &X, vector<double> &obj)
{

  int numberOfVariables_ = X.size();
  int numberOfObjectives_ = obj.size();
  int k = numberOfVariables_ - numberOfObjectives_ + 1;
   double g = 0.0;
  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (X[i] - 0.5)*(X[i] - 0.5);

  for (int i = 0; i < numberOfObjectives_; i++)
    obj[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++){
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      obj[i] *= cos(X[j]*0.5*M_PI);
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        obj[i] *= sin(X[aux]*0.5*M_PI);
      } //if
  } // for
}
void Benchmark::dtlz3(vector<double> &X, vector<double> &obj)
{
  int numberOfVariables_ = X.size();
  int numberOfObjectives_ = obj.size();

  int k = numberOfVariables_ - numberOfObjectives_ + 1;


  double g = 0.0;
  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (X[i] - 0.5)*(X[i] - 0.5) - cos(20.0 * M_PI * (X[i] - 0.5));

  g = 100.0 * (k + g);
  for (int i = 0; i < numberOfObjectives_; i++)
    obj[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++){
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      obj[i] *= cos(X[j]*0.5*M_PI);
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        obj[i] *= sin(X[aux]*0.5*M_PI);
      } // if
  } //for

}
void Benchmark::dtlz4(vector<double> &X, vector<double> &obj)
{

  int numberOfVariables_ = X.size();
  int numberOfObjectives_ = obj.size();
  int k = numberOfVariables_ - numberOfObjectives_ + 1;
  double alpha = 100.0;


  double g = 0.0;
  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (X[i] - 0.5)*(X[i] - 0.5);

  for (int i = 0; i < numberOfObjectives_; i++)
    obj[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++) {
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      obj[i] *= cos(pow(X[j],alpha)*(M_PI/2.0));
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        obj[i] *= sin(pow(X[aux],alpha)*(M_PI/2.0));
      } //if
  } // for

}
void Benchmark::dtlz5(vector<double> &X, vector<double> &obj)
{
  double g = 0.0;
  int numberOfVariables_ = X.size();
  int numberOfObjectives_ = obj.size();
  vector<double> theta_(numberOfObjectives_-1,0);
  int k = numberOfVariables_ - numberOfObjectives_ + 1;
  double alpha = 100.0;


  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (X[i] - 0.5)*(X[i] - 0.5);

  double t = M_PI / (4.0 * (1.0 + g));

  theta_[0] = X[0] * M_PI / 2.0;
  for (int i = 1; i < (numberOfObjectives_-1); i++)
    theta_[i] = t * (1.0 + 2.0 * g * X[i]);

  for (int i = 0; i < numberOfObjectives_; i++)
    obj[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++){
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      obj[i] *= cos(theta_[j]);
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        obj[i] *= sin(theta_[aux]);
      } // if
  } //for

}
void Benchmark::dtlz6(vector<double> &X, vector<double> &obj)
{
  double g = 0.0;
  int numberOfVariables_ = X.size();
  int numberOfObjectives_ = obj.size();

  vector<double> theta_(numberOfObjectives_-1,0);
  int k = numberOfVariables_ - numberOfObjectives_ + 1;
  double alpha = 100.0;

  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += pow(X[i],0.1);

  double t = M_PI / (4.0 * (1.0 + g));

  theta_[0] = X[0] * M_PI / 2.0;
  for (int i = 1; i < (numberOfObjectives_-1); i++)
    theta_[i] = t * (1.0 + 2.0 * g * X[i]);

  for (int i = 0; i < numberOfObjectives_; i++)
    obj[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++){
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      obj[i] *= cos(theta_[j]);
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        obj[i] *= sin(theta_[aux]);
      } // if
  } //for

}
void Benchmark::dtlz7(vector<double> &X, vector<double> &obj)
{
  double g = 0.0;
  int numberOfVariables_ = X.size();
  int numberOfObjectives_ = obj.size();
  int k = numberOfVariables_ - numberOfObjectives_ + 1;
  double alpha = 100.0;

  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += X[i] ;

  g = 1 + (9.0 * g)/k ;


  for (int i = 0; i < numberOfObjectives_ - 1; i++)
    obj[i] = X[i] ;

  double h = 0.0 ;
  for (int i = 0; i < numberOfObjectives_ - 1; i++){
    h+=(obj[i]/(1.0+g))*(1 + sin(3.0*M_PI*obj[i])) ;
  } //for

  h = numberOfObjectives_ - h ;

  obj[numberOfObjectives_ - 1] = (1+g)*h ;
}
void Benchmark::uf1(vector<double> &X, vector<double> &obj)
{
	unsigned int j, count1, count2;
	double sum1, sum2, yj;
	int nx = X.size();
	sum1   = sum2   = 0.0;
	count1 = count2 = 0;
	for(j = 2; j <= nx; j++) 
	{
		yj = X[j-1] - sin(6.0*M_PI*X[0] + j*M_PI/nx);
		yj = yj * yj;
		if(j % 2 == 0) 
		{
			sum2 += yj;
			count2++;
		} 
		else 
		{
			sum1 += yj;
			count1++;
		}
	}
	obj[0] = X[0] + 2.0 * sum1 / (double)count1;
	obj[1] = 1.0 - sqrt(X[0]) + 2.0 * sum2 / (double)count2;
}
void Benchmark::uf2(vector<double> &X, vector<double> &obj)
{
		unsigned int j, count1, count2;
		double sum1, sum2, yj;
		int nx = X.size();
		
		sum1   = sum2   = 0.0;
		count1 = count2 = 0;
		for(j = 2; j <= nx; j++) 
		{
			if(j % 2 == 0) 
			{
				yj = X[j-1]-0.3*X[0]*(X[0]*cos(24.0*M_PI*X[0]+4.0*j*M_PI/nx)+2.0)*sin(6.0*M_PI*X[0]+j*M_PI/nx);
				sum2 += yj*yj;
				count2++;
			} 
			else 
			{
				yj = X[j-1]-0.3*X[0]*(X[0]*cos(24.0*M_PI*X[0]+4.0*j*M_PI/nx)+2.0)*cos(6.0*M_PI*X[0]+j*M_PI/nx);
				sum1 += yj*yj;
				count1++;
			}
		}
		obj[0] = X[0]+ 2.0 * sum1 / (double)count1;
		obj[1] = 1.0 - sqrt(X[0]) + 2.0 * sum2 / (double)count2;
}
void Benchmark::uf3(vector<double> &X, vector<double> &obj)
{
	int nx = X.size();
	unsigned int j, count1, count2;
	double sum1, sum2, prod1, prod2, yj, pj;
		
		sum1   = sum2   = 0.0;
		count1 = count2 = 0;
		prod1  = prod2  = 1.0;
		for(j = 2; j <= nx; j++) 
		{
			yj = X[j-1]-pow(X[0],0.5*(1.0+3.0*(j-2.0)/(nx-2.0)));
			pj = cos(20.0*yj*M_PI/sqrt(j+0.0));
			if (j % 2 == 0) 
			{
				sum2  += yj*yj;
				prod2 *= pj;
				count2++;
			} 
			else 
			{
				sum1  += yj*yj;
				prod1 *= pj;
				count1++;
			}
		}
		obj[0] = X[0] + 2.0*(4.0*sum1 - 2.0*prod1 + 2.0) / (double)count1;
		obj[1] = 1.0 - sqrt(X[0]) + 2.0*(4.0*sum2 - 2.0*prod2 + 2.0) / (double)count2;
}
void Benchmark::uf4(vector<double> &X, vector<double> &obj)
{
	int nx = X.size();
	unsigned int j, count1, count2;
	double sum1, sum2, yj, hj;
		
		sum1   = sum2   = 0.0;
		count1 = count2 = 0;
		for(j = 2; j <= nx; j++) 
		{
			yj = X[j-1]-sin(6.0*M_PI*X[0]+j*M_PI/nx);
			hj = fabs(yj)/(1.0+exp(2.0*fabs(yj)));
			if (j % 2 == 0) 
			{
				sum2  += hj;
				count2++;
			} 
			else 
			{
				sum1  += hj;
				count1++;
			}
		}
		obj[0] = X[0]+ 2.0*sum1 / (double)count1;
		obj[1] = 1.0 - X[0]*X[0] + 2.0*sum2 / (double)count2;
}
void Benchmark::uf5(vector<double> &X, vector<double> &obj)
{
	int nx = X.size();
    	unsigned int j, count1, count2;
	double sum1, sum2, yj, hj, N, E;
		
		sum1   = sum2   = 0.0;
		count1 = count2 = 0;
		N = 10.0; E = 0.1;
		for(j = 2; j <= nx; j++) 
		{
			yj = X[j-1]-sin(6.0*M_PI*X[0]+j*M_PI/nx);
			hj = 2.0*yj*yj - cos(4.0*M_PI*yj) + 1.0;
			if (j % 2 == 0) 
			{
				sum2  += hj;
				count2++;
			} 
			else 
			{
				sum1  += hj;
				count1++;
			}
		}
		hj = (0.5/N + E)*fabs(sin(2.0*N*M_PI*X[0]));
		obj[0] = X[0] + hj + 2.0*sum1 / (double)count1;
		obj[1] = 1.0 - X[0] + hj + 2.0*sum2 / (double)count2;
}
void Benchmark::uf6(vector<double> &X, vector<double> &obj)
{
		int nx = X.size();
		unsigned int j, count1, count2;
		double sum1, sum2, prod1, prod2, yj, hj, pj, N, E;
		N = 2.0; E = 0.1;

		sum1   = sum2   = 0.0;
		count1 = count2 = 0;
		prod1  = prod2  = 1.0;
		for(j = 2; j <= nx; j++) 
		{
			yj = X[j-1]-sin(6.0*M_PI*X[0]+j*M_PI/nx);
			pj = cos(20.0*yj*M_PI/sqrt(j+0.0));
			if (j % 2 == 0) 
			{
				sum2  += yj*yj;
				prod2 *= pj;
				count2++;
			} 
			else 
			{
				sum1  += yj*yj;
				prod1 *= pj;
				count1++;
			}
		}

		hj = 2.0*(0.5/N + E)*sin(2.0*N*M_PI*X[0]);
		if(hj<0.0) hj = 0.0;
		obj[0] = X[0] + hj + 2.0*(4.0*sum1 - 2.0*prod1 + 2.0) / (double)count1;
		obj[1] = 1.0 - X[0] + hj + 2.0*(4.0*sum2 - 2.0*prod2 + 2.0) / (double)count2;
}
void Benchmark::uf7(vector<double> &X, vector<double> &obj)
{
		int nx = X.size();
		unsigned int j, count1, count2;
		double sum1, sum2, yj;
		
		sum1   = sum2   = 0.0;
		count1 = count2 = 0;
		for(j = 2; j <= nx; j++) 
		{
			yj = X[j-1] - sin(6.0*M_PI*X[0]+j*M_PI/nx);
			if (j % 2 == 0) 
			{
				sum2 += yj*yj;
				count2++;
			} 
			else 
			{
				sum1  += yj*yj;
				count1++;
			}
		}
		yj = pow(X[0],0.2);
		obj[0] = yj+ 2.0*sum1 / (double)count1;
		obj[1] = 1.0 - yj + 2.0*sum2 / (double)count2;
}
void Benchmark::uf8(vector<double> &X, vector<double> &obj)
{
		int nx = X.size();
		unsigned int j, count1, count2, count3;
		double sum1, sum2, sum3, yj;
		
		sum1   = sum2   = sum3   = 0.0;
		count1 = count2 = count3 = 0;
		for(j = 3; j <= nx; j++) 
		{
			yj = X[j-1] - 2.0*X[1]*sin(2.0*M_PI*X[0]+j*M_PI/nx);
			if(j % 3 == 1) 
			{
				sum1  += yj*yj;
				count1++;
			} 
			else if(j % 3 == 2) 
			{
				sum2  += yj*yj;
				count2++;
			}
			else
			{
				sum3  += yj*yj;
				count3++;
			}
		}
		obj[0] = cos(0.5*M_PI*X[0])*cos(0.5*M_PI*X[1]) + 2.0*sum1 / (double)count1;
		obj[1] = cos(0.5*M_PI*X[0])*sin(0.5*M_PI*X[1]) + 2.0*sum2 / (double)count2;
		obj[2] = sin(0.5*M_PI*X[0]) + 2.0*sum3 / (double)count3;
}
void Benchmark::uf9(vector<double> &X, vector<double> &obj)
{
		int nx = X.size();
		unsigned int j, count1, count2, count3;
		double sum1, sum2, sum3, yj, E;
		
		E = 0.1;
		sum1   = sum2   = sum3   = 0.0;
		count1 = count2 = count3 = 0;
		for(j = 3; j <= nx; j++) 
		{
			yj = X[j-1] - 2.0*X[1]*sin(2.0*M_PI*X[0]+j*M_PI/nx);
			if(j % 3 == 1) 
			{
				sum1  += yj*yj;
				count1++;
			} 
			else if(j % 3 == 2) 
			{
				sum2  += yj*yj;
				count2++;
			}
			else
			{
				sum3  += yj*yj;
				count3++;
			}
		}
		yj = (1.0+E)*(1.0-4.0*(2.0*X[0]-1.0)*(2.0*X[0]-1.0));
		if(yj<0.0) yj = 0.0;
		obj[0] = 0.5*(yj + 2*X[0])*X[1]	+ 2.0*sum1 / (double)count1;
		obj[1] = 0.5*(yj - 2*X[0] + 2.0)*X[1] + 2.0*sum2 / (double)count2;
		obj[2] = 1.0 - X[1] + 2.0*sum3 / (double)count3;

}
void Benchmark::uf10(vector<double> &X, vector<double> &obj)
{
		int nx = X.size();
		unsigned int j, count1, count2, count3;
		double sum1, sum2, sum3, yj, hj;
		
		sum1   = sum2   = sum3   = 0.0;
		count1 = count2 = count3 = 0;
		for(j = 3; j <= nx; j++) 
		{
			yj = X[j-1] - 2.0*X[1]*sin(2.0*M_PI*X[0]+j*M_PI/nx);
			hj = 4.0*yj*yj - cos(8.0*M_PI*yj) + 1.0;
			if(j % 3 == 1) 
			{
				sum1  += hj;
				count1++;
			} 
			else if(j % 3 == 2) 
			{
				sum2  += hj;
				count2++;
			}
			else
			{
				sum3  += hj;
				count3++;
			}
		}
		obj[0] = cos(0.5*M_PI*X[0])*cos(0.5*M_PI*X[1]) + 2.0*sum1 / (double)count1;
		obj[1] = cos(0.5*M_PI*X[0])*sin(0.5*M_PI*X[1]) + 2.0*sum2 / (double)count2;
		obj[2] = sin(0.5*M_PI*X[0]) + 2.0*sum3 / (double)count3;

}
