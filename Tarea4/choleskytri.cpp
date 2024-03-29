#include<iostream>
#include<stdio.h>
#include<fstream>
#include<math.h>

using namespace std;

void CholeskyD( double *L, int n)
{
	double sum;
	*(L + 1) = sqrt(2);
    for(int i = 1;i < n; i++)
    {
        *(L + 2*i) = -1.0;
        *(L + 2*i) /= *(L + 2*i - 1);
        *(L + 2*i +1) = sqrt(2.0 - (*(L + 2*i)));
    }
}

void solveL(double *L, double *Y, int n, double dosl) 
{
	double sum;
	*Y = dosl/(*(L + 1));
    for(int i = 1; i < n-1; i++)
    {
    	*(Y + i) = (dosl - (*(Y + i - 1))*(*(L + 2*i)) );
    	*(Y + i) /= (*(L + 2*i + 1)); 
    }
    *(Y + n - 1) = (dosl + 2 - (*(Y + n - 2))*(*(L + 2*n - 2)) );
    *(Y + n - 1) /= (*(L + 2*n - 1));
}

void solveLT(double *L, double *X, double *Y, int n) 
{
	double sum;
	*(X + n - 1) = ( *(Y + n -1) )/(*(L + 2*n -1));
    for(int i = (n - 2) ; i >= 0; i--)
    {
        *(X + i) = (*(Y + i)) - (*(X + i + 1))*(*(L + 2*i + 2));
        *(X + i) /= (*(L + 2*i + 1));
    }
}

int main()
{
	double n, dosl;
   double *X, *L, *Y;
   X = (double *)malloc(sizeof(double)*10000);
   Y = (double *)malloc(sizeof(double)*10000);
   L = (double *)malloc(sizeof(double)*30000);
	cin >> n;
	dosl = (-2.0); 
	dosl /= n;
	dosl /= n; 	   
   
   CholeskyD(L, n);   
   solveL(L, Y, n, dosl);
   solveLT(L, X, Y, n);
	
	ofstream myo;
   myo.open("puntos10.txt");
   myo << n << "\n";
   myo << 0 << " " << 0 << "\n";
   double aux = 1.0/n;
	for(int i = 1; i <= n; i++)	{        
        myo << aux*i << " " << *(Y + i -1) << "\n";
    }
    myo << 1 << " " << 2;
    myo.close();
    
    free(Y);
    free(X);
    free(L);
    return 0;

}