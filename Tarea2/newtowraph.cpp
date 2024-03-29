#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "./fparser/fparser.hh"
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
   double x0, f0, d0, aux;
   string func, deri;
	FunctionParser fparser, dparser;
   double epsilon = 0.00000001; //Nuestra condición de paro
   int itera = 1000000; //Si no llega a cumplir la condición de paro, para que no se cicle
	x0 = atof(argv[1]);
	func = argv[2];
	deri = argv[3];
	fparser.AddConstant("pi", 3.1415926535897932);
	fparser.AddConstant("e", 2.7182818284590452);
	dparser.AddConstant("pi", 3.1415926535897932);
	dparser.AddConstant("e", 2.7182818284590452);
	fparser.Parse(func,"x");	
	dparser.Parse(deri,"x");
	for(int i = 0; i < itera; i++)
	{	
		f0 = fparser.Eval(&x0);
		if(abs(f0) < epsilon) 
		{
			cout<<"El algoritmo convergio despues de "<<i<<" iteraciones\n";
			cout<<"El valor de la raiz es: "<<x0<<"\n";
			return 0;
		}
		d0 = dparser.Eval(&x0);
		if(abs(d0) < epsilon) 
		{
			cout<<"El algoritmo no convergio, la derivada es 0\n";
			cout<<f0<<" "<<d0<<endl;
			return 0;
		}
		x0 = x0 - f0/d0;			
	}
	cout<<"El algoritmo no convergio\n";
	cout<<"Pero la aproximacion que encontrarmos es: "<<x0<<"\n";
	f0 = fparser.Eval(&x0);	
	cout<<"Y su valor en la funcion es: "<<f0<<"\n";	
	return 0;
}