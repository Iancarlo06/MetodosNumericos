#include<stdlib.h>
#include <math.h>
#include<iostream>
#include<fstream>
#include <ctime>
#include <chrono>

#define toler 0.000000001
#define MAXITER 1000

using namespace std;

void mat_vec(double *mat, double *vec_v, double *vec_n, int n)
{
    for(int i = 0; i < n; i++)
    {
        *(vec_n + i) = 0;
        for(int j = 0; j < n; j++) *(vec_n + i) += (*(mat + i*n + j))*(*(vec_v + j));
    }
}

void vec_vec(double *vec_0, double *vec_1, double *res, int n)
{
    *res = 0;
    for(int i = 0; i < n; i++) 
        (*res) += (*(vec_0 + i) )*( *(vec_1 + i));
}

void normaliza(double *vec, int n)
{
    double suma = 0;
    for(int i = 0; i < n; i++) suma+= (*(vec + i))*(*(vec + i));
    suma = sqrt(suma);
    if(suma > toler)
    {
        for(int i= 0; i < n; i++) (*(vec + i)) /= suma;
    }
}

double norma(double *v, int n)
{
    double res = 0;
    for(int i = 0; i < n; i++) res+= ( *(v + i) )*( *(v + i) );
	 res = sqrt(res);    
    return res;
}

void factQR(double *A, double *Q, double *R, int n)
{
	double *vec = (double *)malloc(n*sizeof(double));
	for(int i = 0; i < n; i++) *(vec + i) = *(A + i*n);
	double aux = norma(vec,n);
	*R	= aux; 
	normaliza(vec, n);
	for(int i = 0; i < n; i++) *(Q + n*i) = (*(vec + i));
	
	for(int j = 1; j < n; j++)
	{
		for(int i = 0; i < j; i++)
		{
			*(R + i*n + j) = 0;
			for(int k = 0; k < n; k++) *(R + i*n + j) += (*(Q + k*n + i) )*( *(A + k*n +j) );
		}
		for(int k = 0; k < n; k++) 
		{
			*(vec + k) = *(A + k*n + j);
			for(int i = 0; i < j; i++) *(vec + k) -= (*(R + i*n + j))*(*(Q + k*n + i));
		}
		*(R + j*n + j) = norma(vec, n);
		normaliza(vec, n);
		for(int k = 0; k < n; k++) *(Q + k*n + j) = (*(vec + k));  
	}
	
	free(vec);
}

void diagsup(double *U, double *X, double *Y, int n)
{
	 double sum;
    for(int i = (n-1) ; i >= 0; i--)
    {
        sum = *(Y + i);
        for(int j = (n-1); j > i; j--) sum -= (*(X + j))*(*(U + i*n + j));
        *(X + i) = sum/(*(U + i*n + i));
    }
}

void solveQ(double *Q, double *y, double *b, int n)
{
	for(int i = 0; i < n; i++)
	{
		*(y + i) = 0;
		for(int j = 0; j < n; j++)
		{
			*(y + i) += (*(Q + j*n + i) )*(*(b + j));
		}	
	}
}

int main()
{
    ifstream myput; 
    myput.open("M_sys_125x125.txt");
    int n, m;
    myput >> n >> m;
    double *mat = (double *)malloc(sizeof(double)*n*n);
    double *Q = (double *)malloc(sizeof(double)*n*n);
    double *R = (double *)malloc(sizeof(double)*n*n);   
    double *x = (double *)malloc(sizeof(double)*n);    
	double *y = (double *)malloc(sizeof(double)*n);    
    double *b = (double *)malloc(sizeof(double)*n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            myput >> (*(mat + i*n + j));
        }
    }
    myput.close();
    myput.open("V_sys_125x1.txt");
	 myput >> n >> m;    
    for(int i = 0; i < n; i++)
    {
        myput >> (*(b + i));
    }
    myput.close();

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    factQR(mat, Q, R, n);
	solveQ(Q, y, b, n);
	diagsup(R, x, y, n);	     

    end = chrono::system_clock::now();

    ofstream myout;
    myout.open("sol_QR_125x1.txt");
    myout << 125 <<" "<<1<<"\n";
    for(int i = 0; i < n; i++) myout<<*(x + i)<<"\n";
	myout.close();

	chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Tiempo transcurrido: " << elapsed_seconds.count() << "s\n";
        
    free(mat);
    free(Q);
    free(R);
    free(x);
    free(y);
    free(b);
    return 0;
}
