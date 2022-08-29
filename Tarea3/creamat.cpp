#include<iostream>
#include<fstream>

using namespace std;

int main()
{
   int n, aux = 0;

   cin >> n;
	ofstream f("U.txt");
   f<<n<<"\n";
   for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < i; j++)
		{
				f<<0<<" ";
		}
		for(int j = i; j < n; j++)
		{
			f<<(i*n + j + 1)<<" ";	
		}
		f<<"\n";
	}
	for(int i = 0; i < n; i++)
	{
		f<<1<<"\n";	
	}
	return 0;
	
}