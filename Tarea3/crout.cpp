#include<iostream>
#include<stdio.h>
#include<fstream>
#include <ctime>
#include <chrono>

using namespace std;

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

int main()
{
	int n,m, uno;
    ifstream myput;
    myput.open("mat.txt");
   	double *A, *B, *X, *L, *Y, *E, *U, sum;
    A = (double *)malloc(sizeof(double)*25000000);
    B = (double *)malloc(sizeof(double)*5000);
    X = (double *)malloc(sizeof(double)*5000);
    L = (double *)malloc(sizeof(double)*25000000);
    Y = (double *)malloc(sizeof(double)*5000);
    U = (double *)malloc(sizeof(double)*25000000);
    E = (double *)malloc(sizeof(double)*25000000);

    myput >> n >> m;
    
    for(int i = 0; i < n; i++){
    	for(int j = 0;j < n; j++){
		    myput >> (*(A +i*n +j));
        }
    }
    myput.close();

    /*ifstream myifs;
    myifs.open("b.txt");
    
    myifs >> m >> uno;
    for(int i = 0; i < n; i++) 
    {
        myifs >> (*(B + i));
    }

    myifs.close();*/

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    //Descomposicion LU

    for(int i = 0;i < n; i++){
        for(int j = 0;j < n; j++){
            sum = 0;
            if(i < j){               //Es decir, solo se llenan los elementos de la diagonal y encima de ella para U
                for(int k = 0;k < i;k++) sum = sum + (*(L + i*n + k)) * (*(U + k*n + j));
                *(U + i*n + j) = (*(A + i*n + j) - sum)/(*(L + i*n + i));               //Llenado de elementos restantes de U
            } else{                 //Es decir, solo se llenan los elementos debajo de la diagonal para L
                for(int k = 0;k < j;k++) sum = sum + (*(L + i*n + k)) * (*(U + k*n + j));
                *(L + i*n + j) = *(A + i*n + j) - sum;      //Llenado de elementos restantes de L
            }
            if(i == j) *(U + i*n + j) = 1;
        }
    }

    /*for(int i = 0; i < n; i++)
    {
        sum = *(B + i);
        for(int j = 0;j < i;j++) sum = sum - (*(Y + j))*(*(L + i*n + j));
        *(Y + i) = sum/(*(L + i*n + i));
    }
    
    for(int i = (n-1) ; i >= 0; i--){
        sum = *(Y + i);
        for(int j = (n-1); j > i; j--)
            sum -= (*(X + j))*(*(U + i*n + j));
        *(X + i) = sum;
    }*/

    mat_mat(E, L, U, n, n, n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%lf ", *(L + i*n + j));
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%lf ", *(U + i*n + j));
        printf("\n");
    }

    printf("\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%lf ", *(E + i*n + j));
        printf("\n");
    }


    end = chrono::system_clock::now();
    
    ofstream myo;
    myo.open("x.txt");
	for(int i = 0; i < n; i++)	{
        myo << (*(X + i)) << "\n";
    }
    myo.close();
    
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Tiempo transcurrido: " << elapsed_seconds.count() << "s\n";
    free(A);
    free(B);
    free(X);
    free(Y);
    free(L);
    free(U);
    return 0;

}