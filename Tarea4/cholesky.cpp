#include<iostream>
#include<stdio.h>
#include<fstream>
#include <ctime>
#include <chrono>

using namespace std;

int main()
{
	int n,m, uno;
    ifstream myput;
    myput.open("A.txt");
   	double *A, *B, *X, *L, sum;
    A = (double *)malloc(sizeof(double)*25000000);
    B = (double *)malloc(sizeof(double)*5000);
    X = (double *)malloc(sizeof(double)*5000);
    L = (double *)malloc(sizeof(double)*25000000);
    
    myput >> n >> m;
    
    for(int i = 0; i < n; i++){
    	for(int j = 0;j < n; j++){
		    myput >> (*(A +i*n +j));
        }
    }
    myput.close();

    ifstream myifs;
    myifs.open("b.txt");
    
    myifs >> m >> uno;
    for(int i = 0; i < n; i++) 
    {
        myifs >> (*(B + i));
    }

    myifs.close();

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    //Descomposicion LLT https://www.geeksforgeeks.org/cholesky-decomposition-matrix-decomposition/ continuar ahorita

    for(int i = 0;i < n; i++){
        for(int j = 0;j <= i; j++){
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

    for(int i = 0; i < n; i++)
    {
        sum = *(B + i);
        for(int j = 0;j < i;j++) sum = sum - (*(Y + j))*(*(L + i*n + j));
        *(Y + i) = sum;
    }
    
    for(int i = (n-1) ; i >= 0; i--){
        sum = *(Y + i);
        for(int j = (n-1); j > i; j--)
            sum -= (*(X + j))*(*(U + i*n + j));
        *(X + i) = sum/(*(U + i*n + i));
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
    free(L);
    return 0;

}