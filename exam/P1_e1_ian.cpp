#include<iostream>
#include<stdio.h>
#include<fstream>
#include <ctime>
#include<math.h>
#include <chrono>

#define toler 0.000000001
using namespace std;

void mat_vec(double *mat, double *vec_v, double *vec_n, int n)
{
    for(int i = 0; i < n; i++)
    {
        *(vec_n + i) = 0;
        for(int j = 0; j < n; j++) *(vec_n + i) += (*(mat + i*n + j))*(*(vec_v + j));
    }
}

void crout(double *A, double *L, double *U, int n)
{
    double sum;
    int ini,fini;
    for(int i = 0;i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i < j) *(L + i*n + j) = 0;
            if(j < i) *(U + i*n + j) = 0;
            if(abs(i - j) > 2) 
            {
                *(L + i*n + j) = 0;
                *(U + i*n + j) = 0;
            }
            if(j - i == 2)
            {
                *(U + i*n + j) = (*(A + i*n + j))/(*(L + i*n + i)); 
            } 
            if(j - i == 1)
            { 
                sum = 0;
                if(i > 0) sum += (*(L + i*n + (i - 1)))*(*(U + (i - 1)*n + j));
                *(U + i*n + j) = (*(A + i*n + j) - sum)/(*(L + i*n + i)); 
            }
            if(j == i)
            { 
                *(U + i*n + j) = 1;
                sum = 0;
                if(i > 1) sum += (*(L + i*n + (i - 2)))*(*(U + (i - 2)*n + j));
                if(i > 0) sum += (*(L + i*n + (i - 1)))*(*(U + (i -1)*n + i));
                *(L + i*n + j) = (*(A + i*n + j)) - sum;           
            }
            if(i - j == 1)
            { 
                *(L + i*n + j) = (*(A + i*n + j)); 
                if(i > 1) *(L + i*n + j) -= (*(L + i*n + (i - 2)))*(*(U + (i - 2)*n + j)); 
            }
            if(i - j == 2)
            { 
                *(L + i*n + j) = *(A + i*n + j); 
            }
        }
    }

}

void solveL(double *L, double *Y, double *B, int n)
{
    int ini = 0;
    double sum;
    for(int i = 0; i < n; i++)
    {
        sum = *(B + i);
        ini = i - 2;
        if(ini < 0) ini = 0;
        for(int j = ini; j < i; j++) sum -= (*(Y + j))*(*(L + i*n + j));
        *(Y + i) = sum/(*(L + i*n + i));
    }
}

void solveU(double *U, double *X, double *Y, int n)
{
    int fini;
    double sum;
    for(int i = (n-1) ; i >= 0; i--)
    {
        sum = *(Y + i);
        fini = i + 2;
        if( fini >  (n-1) ) fini = n-1;
        for(int j = fini; j > i; j--)
            sum -= (*(X + j))*(*(U + i*n + j));
        *(X + i) = sum;
    }

}

double norma(double *v, int n)
{
    double res = 0;
    for(int i = 0; i < n; i++) res+= ( *(v + i) )*( *(v + i) );
	    res = sqrt(res);    
    return res;
}


int main()
{
	int n,m, uno;
    ifstream myput;
    myput.open("mat.txt");
    
    myput >> n >> m;

    double *A = (double *)malloc(sizeof(double)*n*n);
    double *L = (double *)malloc(sizeof(double)*n*n);
    double *U = (double *)malloc(sizeof(double)*n*n);
    double *X = (double *)malloc(sizeof(double)*n);
    double *Y = (double *)malloc(sizeof(double)*n);
    double *B = (double *)malloc(sizeof(double)*n);

    for(int i = 0; i < n; i++){
    	for(int j = 0;j < n; j++){
		    myput >> (*(A +i*n +j));
        }
    }
    myput.close();

    ifstream myifs;
    myifs.open("vec.txt");
    
    myifs >> m >> uno;
    for(int i = 0; i < n; i++) 
    {
        myifs >> (*(B + i));
    }

    myifs.close();

    //Descomposicion LU

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
    crout(A, L, U, n);
    solveL(L, Y, B, n);
    solveU(U, X, Y, n);

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Tiempo transcurrido: " << elapsed_seconds.count() << "s\n";

    ofstream myo;
    myo.open("x.txt");
	for(int i = 0; i < n; i++)	{
        myo << (*(X + i)) << "\n";
    }
    myo.close();

    mat_vec(A, X, Y, n);
    for(int i = 0; i < n; i++)
    {
        *(Y + i) -= *(B + i);
    }
    cout<< "El error de la solucion es: "<< norma(Y,n)<<"\n";
    
    free(A);
    free(L);
    free(U);
    free(X);
    free(Y);
    free(B);
    return 0;

}