#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "./fparser/fparser.hh"
#include <cstdlib>

using namespace std;

string myf;
FunctionParser fparser;

int main(int argc, char *argv[])
{
    double a,b,aux, evalu;
    double epsilon = 0.00000001; //para saber si una derivada es 0
    double *func, *deri1, *deri2;
    int *candi;
    int tam = 0, parti = 5002, k; //Si no llega a cumplir la condición de paro, para que no se cicle
    a = atof(argv[1]);
    b = atof(argv[2]);
	myf = argv[3];
	fparser.AddConstant("pi", 3.1415926535897932);
	fparser.AddConstant("e", 2.7182818284590452);
	fparser.Parse(myf,"x");
    func = (double *)malloc(sizeof(double)*parti);
    deri1 = (double *)malloc(sizeof(double)*parti);
    deri2 = (double *)malloc(sizeof(double)*parti);
    candi = (int *)malloc(sizeof(int)*parti);
    
    aux = (b-a)/parti;
    evalu = a;
    for(int i = 0; i < parti; i++)
    {
        *(func + i) = fparser.Eval(&evalu);
        evalu += aux;
    }
    parti--;
    for(int i = 0; i < parti; i++)
    {
        *(deri1 + i) = (*(func + i)) - (*(func + i + 1));
        *(deri1 + i) /= aux;
        if((*(deri1 + i)) < epsilon)
        {
            *(candi + tam) = i;
            tam++;
        }        
    }

    parti--;
    for(int i = 0; i < parti; i++)
    {
        *(deri2 + i) = (*(deri1 + i)) - (*(deri1 + i + 1));
        *(deri2 + i) /= aux;        
    }
    *(deri2 + parti) = 0;
    cout<<"Los maximos locales son: \n";
    for(int i = 0; i < tam; i++)
    {
        k = *(candi + i);
        if(*(deri2 + k) < 0) cout<< (*(deri2 + k))<<"\n";
    }
    cout<<"Los minimos locales son: \n";
    for(int i = 0; i < tam; i++)
    {
        k = *(candi + i);
        if(*(deri2 + k) > 0) cout<< (*(deri2 + k))<<"\n";
    }

    free(func);
    free(deri1);
    free(deri2);
    free(candi);
    return 0;
}