#include<stdio.h> 
#include<stdlib.h>
#include<math.h>

double Nis(double x, double *num, int k)
{   
    double res = 1;
    for(int i = 0; i < k; i++) res*= (x - num[i]);
    return res;
}

void MatNew(double *A, double *pnts,  int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            *(A + i*n + j) = Nis(pnts[i], pnts, j);
        }
    }
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
    
    for(int i = 0; i < n; i++)
    {
        xses[i] =  (2.0);
        xses[i] *= i;
        xses[i] /= n;
        xses[i] -= 1.0;
        yses[i] = func(xses[i]);
    }


    free(xses);
    free(yses);
    return 0;
}