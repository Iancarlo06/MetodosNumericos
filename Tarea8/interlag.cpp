#include<stdio.h> 
#include<stdlib.h>
#include<math.h>

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
    return cos(x);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Faltan argumentos");
        return 1;
    }
    int n = atoi(argv[1]);
    double *xses = (double *)malloc(sizeof(double)*n);
    double *yses = (double *)malloc(sizeof(double)*n);
    double *deno = (double *)malloc(sizeof(double)*n);
    
    for(int i = 0; i < n; i++)
    {
        xses[i] =  (2.0);
        xses[i] *= i;
        xses[i] /= n;
        xses[i] -= 1.0;
        yses[i] = func(xses[i]);
    }
    for(int i = 0; i < n; i++)
    {
        yses[i] = 1/xses[i];
        deno[i] = 1;
        for(int j = 0; j < i; j++)
            deno[i] *= (xses[i] - xses[j]);

        for(int j = i+1; j < n; j++)
            deno[i] *= (xses[i] - xses[j]);
    }


    free(xses);
    free(yses);
    free(deno);
    return 0;
}