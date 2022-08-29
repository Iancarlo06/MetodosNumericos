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
   	double *A, *B, *X, *L, *Y, *D, *Z, *U,  sum;
    A = (double *)malloc(sizeof(double)*25000000);
    B = (double *)malloc(sizeof(double)*5000);
    X = (double *)malloc(sizeof(double)*5000);
    L = (double *)malloc(sizeof(double)*25000000);
    Z = (double *)malloc(sizeof(double)*5000);
    D = (double *)malloc(sizeof(double)*5000);
    Y = (double *)malloc(sizeof(double)*5000);
    U = (double *)malloc(sizeof(double)*25000000);
    
    myput >> n >> m;
    
    for(int i = 0; i < n; i++){ //Leo A
    	for(int j = 0;j < m; j++){
		    myput >> (*(A +i*m +j));
        }
    }
    myput.close();

    ifstream myifs;
    myifs.open("b.txt");
    
    myifs >> m >> uno;
    for(int i = 0; i < n; i++) //Lectura de B
    {
        myifs >> (*(B + i));
    }

    myifs.close();

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    //Factorizacion LDU

    for(int i = 0;i < n; i++){
        for(int j = 0;j < n; j++){
            sum = 0;
            if(i < j){               //Es decir, solo se llenan los elementos de la diagonal y encima de ella para U
                for(int k = 0;k < i;k++) sum = sum + (*(D + k))*(*(L + i*n + k)) * (*(U + k*n + j));
                *(U + i*n + j) = (*(A + i*n + j) - sum)/(*(D + i));               //Llenado de elementos restantes de U
            } else{ 
                if(i > j)
                {                //Es decir, solo se llenan los elementos debajo de la diagonal para L
                    for(int k = 0;k < j;k++) sum = sum + (*(D + k))*(*(L + i*n + k)) * (*(U + k*n + j));
                    *(L + i*n + j) = (*(A + i*n + j) - sum)/(*(D + j));      //Llenado de elementos restantes de L
                }
                else { //Llenamos los elementos de D
                    for(int k = 0;k < i;k++) sum = sum + (*(D + k))*(*(L + i*n + k)) * (*(U + k*n + j));
                    *(D + i) = (*(A + i*n + j) - sum);
                }
            }
        }
    }

    for(int i = 0; i < n; i++) //Lz = b
    {
        sum = *(B + i);
        for(int j = 0;j < i;j++) sum = sum - (*(Z + j))*(*(L + i*n + j));
        *(Z + i) = sum;
    }

    for(int i = 0; i < n; i++) //Dy = z
    {
        *(Y + i) = (*(Z + i))/(*(D + i));
    }
    
    for(int i = (n-1) ; i >= 0; i--){ //Ux = y
        sum = *(Y + i);
        for(int j = (n-1); j > i; j--)
            sum -= (*(X + j))*(*(U + i*n + j));
        *(X + i) = sum;
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