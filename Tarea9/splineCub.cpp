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

void crout(double *U, double *L, double *A, int n)
{
    double sum;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            sum = 0;
            if(i < j)
            {               //Es decir, solo se llenan los elementos de la diagonal y encima de ella para U
                for(int k = 0; k < i; k++) sum = sum + (*(L + i*n + k)) * (*(U + k*n + j));
                *(U + i*n + j) = (*(A + i*n + j) - sum)/(*(L + i*n + i));               //Llenado de elementos restantes de U
            } else
            {                 //Es decir, solo se llenan los elementos debajo de la diagonal para L
                for(int k = 0; k < j; k++) sum = sum + (*(L + i*n + k)) * (*(U + k*n + j));
                *(L + i*n + j) = *(A + i*n + j) - sum;      //Llenado de elementos restantes de L
            }
            if(i == j) *(U + i*n + j) = 1;
        }
    }

}

void solveL(double *L, double *Y, double *B, int n) 
{
	double sum;
    for(int i = 0; i < n; i++)
    {
        sum = *(B + i);
        for(int j = 0;j < i;j++) sum = sum - (*(Y + j))*(*(L + i*n + j));
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

double spl_cub(double *list_x, double (*f)(double), double *coef, int n, double x)
{
    if(x < list_x[0] || x > list_x[n-1])
    {
        cout<<"Error!\n"<<"El punto esta fuera del rango de evaluacion";
        return -1;
    }
    int indi = bus_bin(list_x, n, x);
    if(indi == 0) indi = 1;
    double d = coef[indi] - coef[indi - 1];
    d /= (list_x[indi] - list_x[indi - 1]); 
    d /= (3.0);
    double c = coef[indi - 1]/(2.0);
    double aux, b = (f(list_x[indi]) - f(list_x[indi - 1]));
    b /= (list_x[indi] - list_x[indi - 1]);
    aux = (list_x[indi] - list_x[indi - 1])/(3.0);
    aux *= (coef[indi] - 2*coef[indi - 1]);
    b -= aux;

    double res = b*(x - list_x[indi - 1]);
    res += f(list_x[indi - 1]); 
    aux = c*(x - list_x[indi - 1]); 
    aux *= (x - list_x[indi - 1]);
    res += aux;
    aux = d*(x - list_x[indi - 1]);
    aux *= (x - list_x[indi - 1]);
    aux *= (x - list_x[indi - 1]);
    res += aux;
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
    double *U = (double *)malloc(sizeof(double)*n*n);
    double *L = (double *)malloc(sizeof(double)*n*n);
    double *B = (double *)malloc(sizeof(double)*n);
    double *Y = (double *)malloc(sizeof(double)*n);
    double *X = (double *)malloc(sizeof(double)*n);
    
    for(int i = 0; i < n; i++)
    {
        //Esta forma es para evitar problemas con las operaciones de enteros
        pts[i] = 20.0;
        pts[i] *= i;
        pts[i] /= (30.0);
        pts[i] -= 10.0;
    } 

    double aux;
    
    for(int i = 1; i < n-1; i++)
    {
        for(int j = 0; j < n; j++)
        {
            *(mat + i*n + j) = 0;
            if(j == i)
            {
                *(mat + i*n + j) = (pts[i - 1] + pts[i]);
                *(mat + i*n + j) *= (2.0);
            }
            else if (j - i == 1) 
            {
                *(mat + i*n + j) = pts[i];
            } 
            else if (i - j == 1) 
            {
                *(mat + i*n + j) = pts[i-1];
            }
        }
        aux = f(pts[i+1]) - f(pts[i]);
        aux /= (pts[i+1] - pts[i]);
        aux *= (3.0); 
        B[i] = aux;
        aux = f(pts[i]) - f(pts[i - 1]);
        aux /= (pts[i] - pts[i-1]);
        aux *= (3.0); 
        B[i] += aux;
    }
    for(int j = 0; j < n; j++)
    {
        *(mat + (n-1)*n + j) = 0;
        *(mat + j) = 0;
    }
    *(mat + (n-1)*n + n-1) = 1;
    mat[0] = 1;
    B[0] = 0;
    B[n-1] = 0;

    crout(U, L, mat, n);
    solveL(L, Y, B, n);
    solveU(U, X, Y, n);
    
    ofstream myfil;
    myfil.open("splcub.txt");
    for(int i = 0; i < m; i++)
    {
        //Esta forma es para evitar problemas con las operaciones de enteros
        aux = 20.0;
        aux *= i;
        aux /= (1000.0);
        aux -= 10.0;
        resp[i] = spl_cub(pts, f, X, n, aux);
        myfil << resp[i] << "\n";
    }
    myfil.close();

    free(pts);
    free(resp);
    free(mat);
    free(U);
    free(L);
    free(B);
    free(Y);
    free(X);
    return 0;
}