#include<iostream>
#include<fstream>
#include<stdio.h>

using namespace std;

int main()
{
	int n; 
	double b[5000], res[5000];
	double L[5000][5000];	
	double sum;	
	ifstream myput("L.txt");

   if (!myput.is_open())
   cout<<"Error opening file\n" ;

   myput >> n;
	for(int i = 0; i < n; i++)
	{	
		for(int j = 0; j < n; j++) 
		{
			myput >> L[i][j];
		}	
	}
	for(int i = 0; i < n; i++)	myput>>b[i];
	for(int i = 0; i < n; i++)
	{	
		if(L[i][i] == 0) 
		{
			cout<<"El sistema no tiene solucion\n";
			return 0;		
		}
		sum = b[i];
		for(int j = 0; j < i; j++) sum -= L[i][j]*res[j];
		res[i] = sum/L[i][i];
	}
	ofstream myo("resinf.txt");
	for(int i = 0; i < n; i++)	myo<<res[i]<<"\n";
	return 0;
}