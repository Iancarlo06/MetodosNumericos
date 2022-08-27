#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "./fparser/fparser.hh"
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
   double a,b, fa, fb, c, fc;
   double epsilon = 0.00000001; //Nuestra condición de paro
   int itera = 1000000; //Si no llega a cumplir la condición de paro, para que no se cicle
   string func;
   FunctionParser fparser;
   a = atof(argv[1]);
	b = atof(argv[2]);
	func = argv[3];
	fparser.Parse(func,"x");	
	fparser.AddConstant("pi", 3.1415926535897932);
   fa = fparser.Eval(&a);
   fb = fparser.Eval(&b);
   if(fa*fb > 0 && abs(fa - fb) > epsilon) //Los extremos no cumplen las condiciones iniciales
   {
   	cout<<"Los extremos no cumplen la condicion inicial"<<endl; 
   	return 0;
   }
   if(fa == 0) //Compruebo si alguno de los extremos no es ya la raiz
   {
   	cout<<"El algoritmo converge y su raiz es "<<a<<endl;
		cout<<"El número de iteraciones es 0"<<endl;       
      return 0;
   }
   if(fb == 0) //Compruebo si alguno de los extremos no es ya la raiz
   {
       cout<<"El algoritmo converge y su raiz es "<<b<<endl;
       cout<<"El número de iteraciones es 0"<<endl;
       return 0;
   }
   for(int i = 1; i <= itera; i++)
   {
		if( abs(fa-fb) < epsilon) //Condición de paro
      {
			cout<<"El algoritmo converge y su raiz es "<<a<<endl;
			cout<<"El número de iteraciones es "<<i<<endl;         
         return 0;
      }
      c = (a+b)/2;
      fc = fparser.Eval(&c);
		if(abs(fc) < epsilon) //condición de paro
		{		
			cout<<"El algoritmo converge y su raiz es "<<c<<endl;
			cout<<"El número de iteraciones es "<<i<<endl;			
			return 0;
		}      
      if(fc*fa > 0) 
      {
      	a = c;
      	fa = fc;
      }
      else
		{      
      	b = c;
      	fb = fc;
      }
    }
    cout<<"EL algoritmo no convergio despues de "<<itera<<" iteraciones pero la aproximacion que conseguimos es "<<a<<endl;
    return 0;
}