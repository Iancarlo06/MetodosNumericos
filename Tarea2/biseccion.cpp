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
    double epsilon = 0.00000001; //Esto es por si la funcion es casi una linea horizontal en el intervalo asignado
    int itera = 100000;
    string func;
    FunctionParser fparser;
    a = atof(argv[1]);
	b = atof(argv[2]);
	func = argv[3];
	fparser.Parse(func,"x");	
	fparser.AddConstant("pi", 3.1415926535897932);
    fa = fparser.Eval(&a);
    fb = fparser.Eval(&b);
    if(fa*fb > 0 && abs(fa - fb) > epsilon)
    {
        cout<<"Los extremos no cumplen la condicion inicial"; 
        return 0;
    }
    if(fa == 0)
    {
        cout<<"El algoritmo converge y su raiz es "<<a<<endl;
    }
    if(fb == 0)
    {
        cout<<"El algoritmo converge y su raiz es "<<b<<endl;
    }
    for(int i = 0; i < itera; i++)
    {
        if( abs(fa-fb) < epsilon)
        {
            cout<<"El algoritmo converge y su raiz es "<<a<<endl;
            return 0;
        }
        c = (a+b)/2;
        fc = fparser.Eval(&c);
        if(fc*fa > 0) a = c;
        else b = c;
    }
    cout<<"EL algoritmo no converge, pero la aproximacion que conseguimos es "<<a<<endl;
    return 0;
}