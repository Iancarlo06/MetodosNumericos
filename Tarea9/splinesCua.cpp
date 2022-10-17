#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<vector>
#include<math.h>
#include<iostream>

using namespace std;

double f(double x)
{
    double res;
    res = cos(x);
    return res;
}

void solveU(double *U, double *X, double *Y, int n)
{
    int fini;
    double sum;
    for(int i = (n-1) ; i >= 0; i--)
    {
        sum = *(Y + i);
        fini = i + 1;
        if( fini >  (n-1) ) fini = n-1;
        for(int j = fini; j > i; j--)
            sum -= (*(X + j))*(*(U + i*n + j));
        *(X + i) = sum;
    }
}

int bus_bin(double *list, int n, double x)
{
    int ini = 0, fini = n-1;
    int m;
    while(ini < fini)
    {
        m = (ini + fini)/2;
        if(x < list[m])
            fini = m;
        else
            ini = m+1;            
    }
    return ini;
}

double spl_cua(double *list_x, double (*f)(double), double *coef, int n, double x)
{
    if(x < list_x[0] || x > list_x[n-1])
    {
        cout<<"Error!\n"<<"El punto esta fuera del rango de evaluacion";
        return -1;
    }
    int indi = bus_bin(list_x, n, x);
    if(indi == 0) indi = 1;
    double a = coef[indi] - coef[indi - 1];
    a /= ( list_x[indi] - list_x[indi - 1] ); 
    a /= (2.0);
    double b = coef[indi - 1];
    double res = b*(x - list_x[indi - 1]);
    res += f(list_x[indi - 1]); 
    res += a*(x - list_x[indi - 1])*(x - list_x[indi - 1]);
    return res;
}

int main(int argc, char* argv[])
{
    /*if(argc < 3)
    {
        cout<<"Numero insuficientes de argumentos";
        return 0;
    }*/
    int n = 31, m = 1001;
    double *pts = (double *)malloc(sizeof(double)*n);
    double *resp = (double *)malloc(sizeof(double)*m);
    double *mat = (double *)malloc(sizeof(double)*n*n);
    double *B = (double *)malloc(sizeof(double)*n);
    double *Y = (double *)malloc(sizeof(double)*n);
    
    for(int i = 0; i < n; i++)
    {
        //Esta forma es para evitar problemas con las operaciones de enteros
        pts[i] = 20.0;
        pts[i] *= i;
        pts[i] /= (30.0);
        pts[i] -= 10.0;
    } 

    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(j == i || j == (i+1))
            {
                *(mat + i*n + j) = (pts[i + 1] - pts[i]);
                *(mat + i*n + j) /= (2.0);
            }
            else 
                *(mat + i*n + j) = 0;
        }
        B[i] = f(pts[i+1]) - f(pts[i]);
        B[i] /= (2.0);
    }
    for(int j = 0; j < n; j++)
        *(mat + (n-1)*n + j) = 0;
    *(mat + (n-1)*n + n-1) = 1;
    B[n-1] = 0;

    solveU(mat, Y, B, n);

    double aux;
    ofstream myfil;
    myfil.open("splcua.txt");
    for(int i = 0; i < m; i++)
    {
        //Esta forma es para evitar problemas con las operaciones de enteros
        aux = 20.0;
        aux *= i;
        aux /= (1000.0);
        aux -= 10.0;
        resp[i] = spl_cua(pts, f, Y, n, aux);
        myfil << resp[i] << "\n";
    }
    myfil.close();
    free(pts);
    free(resp);
    free(mat);
    free(B);
    free(Y);
    return 0;
}