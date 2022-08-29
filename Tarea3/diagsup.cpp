#include<iostream>
#include<fstream>
#include<stdio.h>

using namespace std;

int main()
{
	int n; 
	double b[5000], res[5000];
	double U[5000][5000];	
	double aux;	
	ifstream myput("U.txt");

   	if (!myput.is_open())
   	cout<<"Error opening file\n" ;

   myput >> n;
	
	for(int i = 0; i < n; i++) //Leo la matriz U
	{	
		for(int j = 0; j < n; j++) 
		{
			myput>>U[i][j];
		}	
	}
	for(int i = 0; i < n; i++)	myput>>b[i]; //Leo la el vector B
	
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