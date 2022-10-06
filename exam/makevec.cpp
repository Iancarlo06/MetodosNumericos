#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

int main()
{
   int n = 5000;
   double aux = 0;
	
	ofstream f("vec.txt");
	f<< n << "\n";
	for(int i = 0; i < n; i ++)
   {
	    f << 1 << " ";		
		f<<"\n";
	}
   
	return 0;	
}
