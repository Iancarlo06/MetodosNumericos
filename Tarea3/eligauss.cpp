#include<iostream>
#include<stdio.h>
#include<fstream>
#include <ctime>
#include <chrono>
#include<math.h>

using namespace std;

int main()
{
	int n,m, uno, indi;
    ifstream myput;
    myput.open("A.txt");
   	double *A, *B, *X,  aux, Amax;
    A = (double *)malloc(sizeof(double)*25000000);
    B = (double *)malloc(sizeof(double)*5000);
    X = (double *)malloc(sizeof(double)*5000);
    
    myput >> n >> m;
    
    for(int i = 0; i < n; i++){
    	for(int j = 0;j < m; j++){
		    myput >> (*(A +i*n +j));
        }
    }
    myput.close();

    ifstream myifs;
    myifs.open("b.txt");
    
    myifs >> m >> uno;
    for(int i = 0; i < m; i++) 
    {
        myifs >> (*(B + i));
    }

    myifs.close();

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    //Eliminacion Gaussiana

    //Escalono la matriz
    for(int i=0;i < n;i++)
    {
        indi = i;
        Amax = fabs((*(A + i*m + i)));
        for(int j = i+1;j < n;j++) //Esto es para que siempre este en la diagonal el valor mayor
		{
            if(fabs((*(A + j*m + i))) > Amax)
            {
                Amax = fabs((*(A + j*m + i)));
                indi = j;
            }
        }
        if(Amax == 0){
            cout<<"La matriz es singular\n";
            return 0;
        }
        if(indi != i){ //Intercambio si no es el mayor de su columna el A[i,i]
            for(int j = i;j < m;j++)
		    {            
                aux = *(A + i*m + j);
                *(A + i*m + j) = *(A + indi*m + j);
                *(A + indi*m + j) = aux;
    	    }
            aux = *(B + i);
            *(B + i) = *(B + indi);
            *(B + indi) = aux;    
        }
    	for(int j = i+1;j < n;j++)
		{            
      	    aux = (*(A + j*m + i))/(*(A + i*m + i));
            for(int k = i+1; k < m; k++)
            {
                *(A + j*m + k) -= (*(A + i*m + k))*aux; 
            }
            *(B + j) -= (*(B + i))*aux; 
    	}
    }
    
    //Es una matriz diagonal superior
    for(int i = (n-1) ; i >= 0; i--){
        aux = *(B + i);
        for(int j = (m-1); j > i; j--)
            aux -= (*(X + j))*(*(A + i*m + j));
        *(X + i) = aux/(*(A + i*m + i));
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
    return 0;

}
