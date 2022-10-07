#include<stdio.h> 
#include<stdlib.h>
#include<math.h>
#include<fstream>

void MatNew(double *A, double *pnts,  int n)
{
    for(int i = 0; i < n; i++)
    {
        *(A + i*n) = 1;
        for(int j = 1; j < n; j++)
        {
            *(A + i*n + j) = pnts[i]*(*(A + i*n + (j-1)));
        }
    }
}

double func(double x)
{
    return cos(x);
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

double polaproxx(double *cof, double x, int n)
{
    double res = cof[0];
    double aux = 1;
    for(int i = 1; i < n; i++) 
    {
        aux *= x;
        res += (cof[i]*aux);
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
    double *U = (double *)malloc(sizeof(double)*n*n);
    double *L = (double *)malloc(sizeof(double)*n*n);
    double *X = (double *)malloc(sizeof(double)*n);

    for(int i = 0; i < n; i++)
    {
        xses[i] =  (2.0);
        xses[i] *= i;
        xses[i] /= n;
        xses[i] -= 1.0;
        yses[i] = func(xses[i]);
    }

    MatNew(mat, xses, n);
    crout(U, L, mat, n);
    solveL(L, X, yses, n);
    solveU(U, cof, X, n);

    free(xses);
    free(yses);
    free(mat);
    free(cof);
    free(U);
    free(L);
    free(X);
    return 0;
}