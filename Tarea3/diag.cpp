#include<stdio.h>
#include<iostream>
#include<fstream>

using namespace std;

int main()
{
   int n;
   double aux,deter = 1.0;
   double b[10000];
   double A[10000];
   ifstream myinput("D.txt");

   if (!myinput.is_open())
   cout<<"Error opening file" ;

   myinput >> n;
	for(int i = 0; i < n; i++)
   {
   	myinput >> A[i];
   	deter *= A[i];
     	if(A[i] == 0) break;
   }   
   if(deter == 0)
   {
		cout<<"La matriz no tiene solucion, su determinante es 0\n";
		return 0;
	}
	ofstream myout("resdiag.txt");
   myout<<"La determinante de la matriz es: "<<deter<<"\n";
	myout<<"El vector solución es:\n";	
	for(int i = 0; i < n; i++) 
	{
	   myinput >> b[i];
		myout<<b[i]/A[i]<<"\n";   
	}   
	myout<<"Y su inversa es:\n";
	for(int i = 0 ; i < n; i++) myout<<1.0/A[i]<<"\n";
	return 0;
}