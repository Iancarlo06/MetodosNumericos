#include<iostream>
#include<stdio.h>
#include<fstream>
#include<math.h>

using namespace std;

void CholeskyD(double *A, double *L, int n)
{
	double sum;
    for(int i = 0;i < n; i++)
    {
        for(int j = 0;j <= i; j++)
        {
            sum = 0;
 
            if (j == i) // entradas diagonal 
            {
                for (int k = 0; k < j; k++)
                    sum += (*(L + j*n + k))*(*(L + j*n + k));
                *(L + j*n + j) = sqrt((*(A + j*n + j)) - sum);
            } else {
 
                // Evaluamos L(i, j) usando L(j, j)
                for (int k = 0; k < j; k++)
                    sum +=  (*(L + i*n + k))*(*(L + j*n + k));
                (*(L + i*n + j)) = ((*(A + i*n + j)) - sum) / (*(L + j*n + j));
            }
        }
    }
}

void solveL(double *L, double *Y, double *B, int n) 
{
	double sum;
    for(int i = 0; i < n; i++)
    {
        sum = *(B + i);
        for(int j = 0;j < i;j++) sum = sum - (*(Y + j))*(*(L + i*n + j));
        *(Y + i) = sum/(*(L + i*n + i));
    }
}

void solveLT(double *L, double *X, double *Y, int n) 
{
	double sum;
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
   myput.open("mat.txt");
	double *A, *B, *X, *L, *Y;
   A = (double *)malloc(sizeof(double)*100000005);
   B = (double *)malloc(sizeof(double)*10005);
   X = (double *)malloc(sizeof(double)*10005);
   Y = (double *)malloc(sizeof(double)*10005);
   L = (double *)malloc(sizeof(double)*100000005);
    
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
   myo.open("puntos10000.txt");
   myo << 0 << "\n";
	for(int i = 0; i < n; i++)	{
		  myo << (*(X + i)) << "\n";
    }
    myo << 2;
    myo.close();
    
    free(A);
    free(B);
    free(X);
    free(Y);
    free(L);
    return 0;

}