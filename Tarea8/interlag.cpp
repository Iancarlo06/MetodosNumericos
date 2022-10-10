#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#include<iostream>
#include<string>

using namespace std;

double Lag(double x, double *num, int n, int k, double deno)
{
    double res = 1;
    for(int i = 0; i < k; i++) res*= (x - num[i]);
    for(int i = k+1; i < n; i++) res*= (x - num[i]);
    return res/deno;
}

double Polagr(double x, double *pnts, double *fxs, double *dens, int n)
{
    double res = 0, aux;
    for(int i = 0; i < n; i++)
    {
        aux = Lag(x, pnts, n, i, dens[i]);
        res += (fxs[i]*aux);
    }
    return res;
}

double func(double x)
{
    return exp(x);
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Faltan argumentos");
        return 1;
    }
    ifstream myifs;
    myifs.open(argv[1]);
    int n;
    myifs >> n;
    double *xses = (double *)malloc(sizeof(double)*n);
    double *yses = (double *)malloc(sizeof(double)*n);
    double *deno = (double *)malloc(sizeof(double)*n);

    for(int i = 0; i < n; i++)
    {
        myifs >> xses[i];
        yses[i] = func(xses[i]);
    }
    myifs.close();
    for(int i = 0; i < n; i++)
    {
        deno[i] = 1;
        for(int j = 0; j < i; j++)
            deno[i] *= (xses[i] - xses[j]);

        for(int j = i+1; j < n; j++)
            deno[i] *= (xses[i] - xses[j]);
    }

    double *aprx = (double *)malloc(sizeof(double)*n);
    double error = 0;
    for(int i = 0; i < n; i++)
    {
        aprx[i] = Polagr(xses[i], xses, yses, deno, n);
        error += ((aprx[i] - yses[i])*(aprx[i] - yses[i]));
    }

    error = sqrt(error);
    cout<<"El error es: "<<error<<"\n";
    ofstream f;
    f.open(argv[2]);
	f << n << "\n";
    for(int i = 0; i < n; i++)	{
        f << aprx[i] << "\n";
    }
    f.close();

    free(xses);
    free(yses);
    free(deno);
    free(aprx);
    return 0;
}
