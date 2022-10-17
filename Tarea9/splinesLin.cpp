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

double spl_lin(double *list_x, double (*f)(double), int n, double x)
{
    if(x < list_x[0] || x > list_x[n-1])
    {
        cout<<"Error!\n"<<"El punto esta fuera del rango de evaluacion";
        return -1;
    }
    int indi = bus_bin(list_x, n, x);
    if(indi == 0) indi = 1;
    double m = f(list_x[indi]) - f(list_x[indi - 1]);
    m /= ( list_x[indi] - list_x[indi - 1] );
    double res = m*(x - list_x[indi - 1]);
    res += f(list_x[indi - 1]); 
    return res;
}

int main(int argc, char* argv[])
{
    /*if(argc < 3)
    {
        cout<<"Numero insuficientes de argumentos";
        return 0;
    }*/
    double *pts = (double *)malloc(sizeof(double)*31);
    double *resp = (double *)malloc(sizeof(double)*1001);
    int n = 31;
    for(int i = 0; i < n; i++)
    {
        //Esta forma es para evitar problemas con las operaciones de enteros
        pts[i] = 20.0;
        pts[i] *= i;
        pts[i] /= (30.0);
        pts[i] -= 10.0;
    } 
    int m = 1001;
    double aux;
    ofstream myfil;
    myfil.open("splin.txt");
    for(int i = 0; i < m; i++)
    {
        //Esta forma es para evitar problemas con las operaciones de enteros
        aux = 20.0;
        aux *= i;
        aux /= (1000.0);
        aux -= 10.0;
        resp[i] = spl_lin(pts, f, n, aux);
        myfil << resp[i] << "\n";
    }
    myfil.close();
    free(pts);
    free(resp);
    return 0;
}