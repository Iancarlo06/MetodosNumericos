#include<iostream>
#include<fstream>

using namespace std;

int main()
{
   double n = 101.0;
   double aux = 0;
	
	ofstream f("mat.txt");
	f<< n - 1 <<"\n";
	for(int i = 0; i < n-1; i ++)
   {
		for(int j = 0; j < n-1; j++)
		{
			aux = 0;
			if(i == j) aux = 2;
			if( i - j == 1) aux = -1;
			if( j - i == 1) aux = -1;
			f << aux << " ";		
		}
		f<<"\n";
	}
	
	ofstream fout("b.txt");	
	fout << n-1 <<"\n";
	aux = 1.0;
	aux = aux/n;
	aux = aux/n;
	aux = aux*(-2.0);
	for(int i = 0; i < n-2; i++)
	{	
		fout << aux << "\n";
	}
	fout <<  2 + aux;
   
	return 0;	
}