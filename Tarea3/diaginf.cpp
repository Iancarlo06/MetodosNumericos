#include<iostream>

using namespace std;

int main()
{
	int n; 
	double b[10000], res[10000];
	double L[10000][10000];	
	double aux;	
	cin>>n; 
	for(int i = 0; i < n; i++)	cin>>b[i];
	for(int i = 0; i < n; i++)
	{	
		for(int j = 0; j < n; j++) 
		{
			cin>>L[i][j];
		}	
	}
	for(int i = 0; i < n; i++)
	{	
		if(L[i][i] == 0) 
		{
			cout<<"El sistema no tiene solucion"<<endl;
			return 0;		
		}
		aux = b[i];
		for(int j = 0; j < i; j++) aux -= L[i][j]*res[j];
		res[i] = aux/L[i][i];
	}
	for(int i = 0; i < n; i++)	cout<<res[i];
	return 0;
}