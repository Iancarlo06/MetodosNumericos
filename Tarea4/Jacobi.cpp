#include<iostream>
#include<stdio.h>
#include<fstream>

using namespace std;

#define MAXITER 100000;
#define valor 0.00000001;

void Jacobi(int n, double *A, double *b, double *vv, double *vn)
{
    for(int i = 0; i < n; i++) *(vv + i) = (*(b + i))/(*(A + i*n + i));
    int iter = 0;
    double tol, num, den, sum;
    while(iter < MAXITER)
    {
        num = 0;
        den = 0;
        for(int i = 0; i < n; i++)
        {
            sum = 0;
            for(int j = 0; j < n; j++)
            {
                if(i != j) suma = suma + (*(vv + j))*(*(A + i*n + j));
            }
            *(vn + i) = ((*(b + i)) - suma)/(*(A+i*n+i));
            num = num + ( (*(vv + i)) - (*(vn + i)) )*( (*(vv + i)) - (*(vn + i)) );
            den = den + ( (*(vn +i)) * (*(vn +i)) );
        }
        tol = num/den;
        if(tol < valor) break;
        for(int i = 0; i < n; i++) *(vv + i) = *(vn + i);
        iter++;
    }
}

int main()
{
	int n,m, uno;
    ifstream myput;
    myput.open("A.txt");
   	double *A, *B, *vv, *vn, sum;
    A = (double *)malloc(sizeof(double)*25000000);
    B = (double *)malloc(sizeof(double)*5000);
    vv = (double *)malloc(sizeof(double)*5000);
    vn = (double *)malloc(sizeof(double)*5000);
    
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
    
    Jacobi(n, A, b, vv, vn);
    
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