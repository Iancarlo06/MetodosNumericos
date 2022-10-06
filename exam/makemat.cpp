#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

int main()
{
   int n = 5000;
   double aux = 0;
	
	ofstream f("mat.txt");
	f<< n << " "<< 10 <<"\n";
	for(int i = 0; i < n; i ++)
   {
		for(int j = 0; j < n; j++)
		{
			aux = 0;
			if(i == j) aux = 40;
			if( abs(i - j) == 1) aux = -8;
			if( abs(i - j) == 2) aux = -4;
			f << aux << " ";		
		}
		f<<"\n";
	}
   
	return 0;	
}
