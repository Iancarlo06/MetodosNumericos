#include<iostream>
#include<stdio.h>
#include<fstream>
#include<math.h>
#include <ctime>
#include <chrono>

using namespace std;
#define toler 0.000000001

void mat_mat(double *C, double *A, double *B, int n, int m, int l)
{ 
    
    for (int i = 0; i < n; i++) 
    {
        for(int j = 0; j < l; j++) 
        {
            *(C + i*n + j) = 0;
 
            for (int k = 0; k < m; k++) 
            {
                *(C + i*n + j) += (*(A + i*m + k)) * (*(B + k*l + j));
            }
        }
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

void inversa(double *inv, double *A, int n)
{
    double *L = (double *)malloc(sizeof(double)*n*n);
    double *U = (double *)malloc(sizeof(double)*n*n);
    double *B = (double *)malloc(sizeof(double)*n);
    double *Y = (double *)malloc(sizeof(double)*n);

    crout(A, L, U, n);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++) *(B + j) = 0.0;
        *(B + i) = 1.0;
        solveL(L, Y, B, n);
        solveU(U, B, Y, n);
        for(int j = 0; j < n; j++)
        {
            *(inv + j*n + i) = *(B + j);
        }
    }

    free(L);
    free(U);
    free(B);
    free(Y);
}


int main()
{
	int n,m, uno;
    ifstream myput;
    myput.open("mat.txt");
    
    myput >> n >> m;

    double *A = (double *)malloc(sizeof(double)*n*n);
    double *E = (double *)malloc(sizeof(double)*n*n);
    double *C = (double *)malloc(sizeof(double)*n*n);

    for(int i = 0; i < n; i++)
    {
    	for(int j = 0;j < n; j++)
        {
		    myput >> (*(A +i*n +j));
        }
    }
    myput.close();

    //Descomposicion LU
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
    inversa(E, A, n);

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Tiempo transcurrido: " << elapsed_seconds.count() << "s\n";

    ofstream myo;
    myo.open("inv.txt");
    myo<<n <<" "<<10<<"\n";
	for(int i = 0; i < n; i++)	
    {
        for(int j = 0; j < n; j++)	
            myo << (*(E + i*n + j)) << " ";
        myo<< "\n";
    }
    myo.close();

    /*mat_mat(C, A, E, n, n, n);

    for(int i = 0; i < n; i++)	
    {
        for(int j = 0; j < n; j++)	
        {
            if(i != j)
            {
                if(fabs(*(C + i*n + j)) > toler) cout<<"Error en la casilla " << i <<" " << j<< " de "<< *(C + i*n + j) << "\n";
            }
        }
    }*/

    free(A);
    free(E);
    free(C);
    return 0;

}