#include<iostream>

using namespace std;

int main()
{
	int n; 
	double b[10000], res[10000];
	double U[10000][10000];	
	double aux;	
	cin>>n; 
	for(int i = 0; i < n; i++)	cin>>b[i];
	for(int i = 0; i < n; i++)
	{	
		for(int j = 0; j < n; j++) 
		{
			cin>>U[i][j];
		}	
	}
	for(int i = n-1; i >= -1; i--)
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
	for(int i = 0; i < n; i++)	cout<<res[i];
	return 0;
}