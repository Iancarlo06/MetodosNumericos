#include<iostream>
#include<stdio.h>
#include<fstream>
#include<math.h>
#include <ctime>
#include <chrono>

using namespace std;

#define MAXITER 1000
#define valor 0.00000001

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
                if(i != j) sum = sum + (*(vv + j))*(*(A + i*n + j));
            }
            *(vn + i) = ((*(b + i)) - sum)/(*(A + i*n + i));
            num = num + ( (*(vv + i)) - (*(vn + i)) )*( (*(vv + i)) - (*(vn + i)) );
            den = den + ( (*(vn + i)) * (*(vn + i)) );
        }
        num = sqrt(num);
        den = sqrt(num);
        tol = num/den;
        if(tol < valor) break;
        for(int i = 0; i < n; i++){
         	*(vv + i) = *(vn + i);		
			}        
        iter++;
    }
}

int main()
{
	int n,m, uno;
   ifstream myput;
   myput.open("mat.txt");
   double *A, *B, *vv, *vn, sum;
   A = (double *)malloc(sizeof(double)*100000005);
   B = (double *)malloc(sizeof(double)*10005);
   vv = (double *)malloc(sizeof(double)*10005);
   vn = (double *)malloc(sizeof(double)*10005);
    
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
    
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
    Jacobi(n, A, B, vv, vn);

    end = chrono::system_clock::now();

    ofstream myo;
    myo.open("x.txt");
    myo << 0 << "\n";
	double myerror = 0, aux;
    
    for(int i = 0; i < n; i++)	{
        aux = (i+1);
        aux /= (n+1);
        aux = aux*aux + aux;
        myerror += ( aux - (*(vn + i)) ) * ( aux - (*(vn + i)) );
        myo << (*(vn + i)) << "\n";
    }
    myo.close();
    myerror = sqrt(myerror);

    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Tiempo transcurrido: " << elapsed_seconds.count() << "s\n";
    cout << "Error: " << myerror << "\n";
    
    free(A);
    free(B);
    free(vv);
    free(vn);
    return 0;

}