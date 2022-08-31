#include<iostream>
#include<stdio.h>
#include<fstream>

#define MAXITER 100000;

using namespace std;

void Jacobi(int n, double *A, double *b, double *vv, double *vn)
{
    for(int i = 0; i < n; i++) *(vv + i) = (*(b + i))/(*(A + i*n + i));
    int iter = 0, num = 0, den = 0;
    while(iter < MAXITER)
    {
        
    }
}

void solveL(double *L, double *Y, double *B, int n) 
{
    for(int i = 0; i < n; i++)
    {
        sum = *(B + i);
        for(int j = 0;j < i;j++) sum = sum - (*(Y + j))*(*(L + i*n + j));
        *(Y + i) = sum/(*(L + i*n + i));
    }
}

void solveLT(double *L, double *X, double *Y, int n) 
{
    for(int i = (n-1) ; i >= 0; i--)
    {
        sum = *(Y + i);
        for(int j = (n-1); j > i; j--)
            sum -= (*(X + j))*(*(L + j*n + i));
        *(X + i) = sum/(*(L + i*n + i));
    }
}

int main()
{
	int n,m, uno;
    ifstream myput;
    myput.open("A.txt");
   	double *A, *B, *X, *L, sum;
    A = (double *)malloc(sizeof(double)*25000000);
    B = (double *)malloc(sizeof(double)*5000);
    X = (double *)malloc(sizeof(double)*5000);
    Y = (double *)malloc(sizeof(double)*5000);
    L = (double *)malloc(sizeof(double)*25000000);
    
    myput >> n;
    
    for(int i = 0; i < n; i++){
    	for(int j = 0;j < n; j++){
		    myput >> (*(A +i*n +j));
        }
    }
    myput.close();

    ifstream myifs;
    myifs.open("b.txt");
    
    myifs >> n;
    for(int i = 0; i < n; i++) 
    {
        myifs >> (*(B + i));
    }
    myifs.close();
    
    CholeskyD(A, L, n);   
    solveL(L, Y, B, n);
    solveLT(L, X, Y, n);

    
    ofstream myo;
    myo.open("x.txt");
	for(int i = 0; i < n; i++)	{
        myo << (*(X + i)) << "\n";
    }
    myo.close();
    
    free(A);
    free(B);
    free(X);
    free(L);
    return 0;

}