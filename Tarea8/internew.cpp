#include<stdio.h> 
#include<stdlib.h>
#include<math.h>
#include<fstream>

double Nis(double x, double *num, int k)
{   
    double res = 1;
    for(int i = 1; i < k; i++) res*= (x - num[i]);
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

double polnew(double *cof, double *pnts, double x, int n)
{
    double res = 0;
    for(int i = 0; i < n; i++) 
    {
        res += cof[i]*Nis(x, pnts, i);
    }
    return res;
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
    double *mat = (double *)malloc(sizeof(double)*n*n);
    double *cof = (double *)malloc(sizeof(double)*n);

    for(int i = 0; i < n; i++)
    {
        xses[i] =  (2.0);
        xses[i] *= i;
        xses[i] /= n;
        xses[i] -= 1.0;
        yses[i] = func(xses[i]);
    }

    MatNew(mat, xses, n);
    solveL(mat, cof, yses, n);
    double aux, mini;
    

    free(xses);
    free(yses);
    free(mat);
    free(cof);
    return 0;
}