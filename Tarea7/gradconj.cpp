#include<stdlib.h>
#include <math.h>
#include<iostream>
#include<fstream>
#include <ctime>
#include <chrono>


#define toler 0.000001
#define MAXITER 500000

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
    if(suma != 0)
    {
        for(int i= 0; i < n; i++) (*(vec + i)) /= suma;
    }
}

double norma(double *v, int n)
{
    double res = 0;
    for(int i = 0; i < n; i++) res+= ( *(v + i) )*( *(v + i) );
    return res;
}

void gradiente(double *A, double *x, double *b, int n)
{
    double *r = (double *)malloc(sizeof(double)*n);
    double *p = (double *)malloc(sizeof(double)*n);
    double *w = (double *)malloc(sizeof(double)*n);
    double *rv = (double *)malloc(sizeof(double)*n);
    double alpha, beta, num, den, aux;
    mat_vec(A, x, r, n);
    for(int i = 0; i < n; i++)
    {
        *(r + i) = (*(b + i)) - (*(r + i));
        *(p + i) = (*(r + i));
    }
    int it = 0;
    for(it = 0; it < MAXITER; it++)
    {
        aux = norma(r, n);
        aux = sqrt(aux);
        if( aux < toler) break;
        mat_vec(A, p, w, n);
        vec_vec(p, r, &num, n);
        vec_vec(p, w, &den, n);
        alpha = num/den;
        for(int i = 0; i < n; i++)
        {
            *(x + i) = *(x + i) + alpha*(*(p + i));
            *(rv + i) = *(r + i);
            *(r + i) = *(r + i) - alpha*(*(w + i)); 
        }
        vec_vec(p, r, &num, n);
        vec_vec(p, p, &den, n);
        beta = num/den;
        for(int i = 0; i < n; i++)
        {
            *(p + i) = (*(r + i)) + beta*(*(p + i));
        }
    }
    printf("La norma del error r es %lf y tomo %d\n", aux, it);

    free(r);
    free(p);
    free(w);
    free(rv);
}

int main()
{
    ifstream myput; 
    myput.open("M_sys_125x125.txt");
    int n, m;
    myput >> n >> m;
    double *mat = (double *)malloc(sizeof(double)*n*n);
    double *vec = (double *)malloc(sizeof(double)*n);   
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
        *(vec + i) = 1;
    }
    myput.close();
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
    //Gradiente conjugado
    gradiente(mat, vec, b, n);
    
    end = chrono::system_clock::now();
    ofstream myout;
    myout.open("sol_grad_125x125.txt");
    myout << n << " " << 1 <<"\n";
    for(int i = 0; i < n; i++) myout<<*(vec + i)<<"\n";
	myout.close();

    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Tiempo transcurrido: " << elapsed_seconds.count() << "s\n";
    

    free(mat);
    free(vec);
    free(b);
    return 0;
}
