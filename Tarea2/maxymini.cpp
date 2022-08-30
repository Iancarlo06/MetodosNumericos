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
   double a,b,aux, evalu, delta;
   double epsilon = 0.00000001; //para saber si una derivada es 0
   double *range, *deri1, *deri2;
 	int *candi;
	int tam = 0, parti = 5000, k; //Si no llega a cumplir la condición de paro, para que no se cicle
   a = atof(argv[1]);
   b = atof(argv[2]);
	myf = argv[3];
	fparser.AddConstant("pi", 3.1415926535897932);
	fparser.AddConstant("e", 2.7182818284590452);
	fparser.Parse(myf,"x");
   range = (double *)malloc(sizeof(double)*parti);
   deri1 = (double *)malloc(sizeof(double)*parti);
   deri2 = (double *)malloc(sizeof(double)*parti);
   candi = (int *)malloc(sizeof(int)*parti);
    
   aux = (b-a)/parti;
   *range = a;
   for(int i = 1; i < parti; i++)
   {
   	*(range + i) = a + i*aux;	
		*(deri1 + i) = fparser.Eval(range + i);
   	delta = (*(range+i))/parti + 1.0/parti;   	
   	evalu = a + i*aux + delta;
   	
   	(*(deri1 + i)) += fparser.Eval(&evalu);
   	(*(deri1 + i)) /= delta;
   	
   	(*(deri2 + i)) = fparser.Eval(&evalu);
   	evalu = a + i*aux - delta; 
   	(*(deri2 + i)) += fparser.Eval(&evalu);
   	(*(deri2 + i)) -= (2*fparser.Eval(range + i));
   	(*(deri2 + i)) /= (delta*delta);
   	cout<<(*(range + i))<<" "<<(*(deri1 + i))<<"\n";
   }
  
	for(int i = 0; i < parti; i++)
	{
		if(fabs((*(deri1 + i))) < epsilon)
		{
			*(candi + tam) = i;
			tam++;      
      }	
	}  
  
   cout<<"Los maximos locales son: \n";
   for(int i = 0; i < tam; i++)
   {
   	k = *(candi + i);
      if(*(deri2 + k) < 0) cout<< fparser.Eval(range + k)<<"\n";
   }
   cout<<"Los minimos locales son: \n";
   for(int i = 0; i < tam; i++)
   {
   	k = *(candi + i);
      if(*(deri2 + k) > 0) cout<< fparser.Eval(range + k)<<"\n";
   }
   free(range);
   free(deri1);
   free(deri2);
   free(candi);
   return 0;
}