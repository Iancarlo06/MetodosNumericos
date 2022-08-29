#include<iostream>
#include<fstream>
#include<stdio.h>

using namespace std;

int main()
{
	int n; 
	double b[1000], res[1000];
	double U[1000][1000];	
	double aux;	
	ifstream myput("U.txt");

   if (!myput.is_open())
   cout<<"Error opening file\n" ;

   myput >> n;
	
	for(int i = 0; i < n; i++)
	{	
		for(int j = 0; j < n; j++) 
		{
			myput>>U[i][j];
		}	
	}
	for(int i = 0; i < n; i++)	myput>>b[i];
	
	for(int i = n-1; i > -1; i--)
	{	
		if(U[i][i] == 0) 
		{
			cout<<"El sistema no tiene solucion"<<endl;
			return 0;		
		}
		aux = b[i];
		for(int j = n-i; j > i; j--) aux -= U[i][j]*res[j];
		res[i] = aux/U[i][i];
	}
	ofstream myo("ressup.txt");
	for(int i = 0; i < n; i++)	myo<<res[i]<<"\n";
	return 0;
}