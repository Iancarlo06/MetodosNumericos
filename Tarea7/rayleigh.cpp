#include<stdlib.h>
#include <math.h>
#include<iostream>
#include<fstream>

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

double vAv(double *A, double *v, int n)
{
    double suma, res = 0;
    for(int i = 0; i < n; i++)
    {
        suma = 0;
        for(int j = 0; j < n; j++)
        {
            suma += (*(A + i*n + j) )*(*(vec + j));
        }
        res += suma*(*(v + i));
    }
    return res;
}

void Ray(double *A, double *v, double *val, int n)
{
	double *vec = (double *)malloc(n*sizeof(double));
    double *B = (double *)malloc(n*n*sizeof(double));
	for(int i = 0; i < n; i++) 
    {
        for(int j = 0 ; j < n; j++)
        {
            *(B + i*n + j) = (*(A + i*n + j))
        }
        *(B + i*n + i) -= (*val);
        *(vec + i) = (*(v + i));
    }
    *val = vAv(A, vec, n);
    
	double aux = norma(vec,n);
	normaliza(vec, n);
	for(int i = 0; i < n; i++) *(Q + i*n) = (*(vec + i));
	
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
	
    free(B);
	free(vec);
}

int main()
{
    ifstream myput; 
    myput.open("M_sys_3x3.txt");
    int n, m;
    myput >> n >> m;
    double *mat = (double *)malloc(sizeof(double)*n*n);
    double *Q = (double *)malloc(sizeof(double)*n*n);
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
    myput.open("V_sys_3x1.txt");
	 myput >> n >> m;    
    for(int i = 0; i < n; i++)
    {
        myput >> (*(b + i));
    }
    myput.close();
    factQR(mat, Q, R, n);
	 solveQ(Q, y, b, n);
	 diagsup(R, x, y, n);	     
    ofstream myout;
    myout.open("sol_QR_3x3.txt");
    myout << 3 <<" "<<1<<"\n";
    for(int i = 0; i < n; i++) myout<<*(x + i)<<"\n";
	 myout.close();
	    
    free(mat);
    free(Q);
    free(R);
    free(x);
    free(y);
    free(b);
    return 0;
}
