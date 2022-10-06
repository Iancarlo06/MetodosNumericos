#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<fstream>

#define toler 0.000000001
#define MAXITER 100000

using namespace std;

double vec_vec(double *x, double *y, int n) { 
 
    double res = 0; 
 
    for(int i = 0; i < n; i++) res += (*(x + i))*(*(y + i)); 
 
    return res; 
} 

void mat_mat(double *C, double *A, double *B, int n, int m, int l)
{ 
    
    for (int i = 0; i < n; i++) 
    {
        for(int j = 0; j < l; j++) 
        {
            *(C + i*n + j) = 0;
 
            for (int k = 0; k < m; k++) 
            {
                *(C + i*n + j) += (*(A + i*m + k)) * (*(B + k*l + j));
            }
        }
    }

}

void normaliza(double *vec, int n)
{
    double suma = 0;
    for(int i = 0; i < n; i++) suma+= (*(vec + i))*(*(vec + i));
    suma = sqrt(suma);
    if(suma > toler)
    {
        for(int i= 0; i < n; i++) (*(vec + i)) /= suma;
    }
}

void gram_schimdt(double *q, int n, int m) { 
 
    double *v1 = (double *)malloc(sizeof(double)*n);
    double *v2 = (double *)malloc(sizeof(double)*n);
    double aux;
    for(int i = 1; i < m; i++) 
    { 
        for(int j = 0; j < i; j++) 
        { 

            for(int k = 0; k < n; k++)
            {
                *(v1 + k) = (*( q + k*m + i ));
                *(v2 + k) = (*( q + k*m + j ));
            }
            aux = vec_vec(v2, v1, n); 
            aux /= vec_vec(v2, v2, n);
             
            /* Subtract each scaled component of q_j from q_i */ 
            for(int k = 0; k < n; k++) 
            {
                *(q + k*m + i) -= aux*(*(q + k*m +j));
            }
        } 
    } 
 
    /* Now normalize all the 'm' orthogonal vectors */ 
    for(int i = 0; i < m; i++) 
    {
        for(int j = 0; j < n; j++) *(v1 + j) = (*(q + j*m + i));
        normaliza(v1, n);
        for(int j = 0; j < n; j++) *(q + j*m + i) = (*(v1 + j));
    }
    
    free(v1);
    free(v2);
}

void itersub(double *A, double *W, int n, int m)
{
    double *V = (double *)malloc(sizeof(double)*n*m);
    double *E = (double *)malloc(sizeof(double)*m*m);
    int it = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            *(V + i*m + j) = *(A + i*n + j); 
        }
    }
    double sum;
    for(it = 0; it < MAXITER; it++)
    {
        printf("Flag1\n");
        mat_mat(W, A, V, n, n, m);
        printf("Flag2\n");
        gram_schimdt(W, n, m);
        printf("Flag3\n");
        mat_mat(V, A, W, n, n, m);
        
        printf("Flag4\n");
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < m; j++)
            {
                *(E + i*m + j) = 0;
                for(int k = 0; k < n; k++)
                {
                    *(E + i*m + j) += ( *(W + k*m + i ) )*( *(V + k*m + j) );
                }
            }
        }
        printf("Flag5\n");
        sum = 0;
        for(int i = 0 ; i < m; i++)
        {
            for(int j = 0 ; j < m; j++) 
            {
                if(i != j) sum += fabs(*(E + i*m + j));
            }
        }
        if(sum < toler) break;
    }
    printf("se pudo en %d\n", it);

    printf("HOla\n");
    free(V);
    printf("Mundo\n");
    free(E);
    printf("Que\n");
}

int main()
{
    ifstream myput;
    myput.open("mat.txt");
    int n,m;
    myput >> n >> m;
    
    double *A = (double *)malloc(sizeof(double)*n*n);
    double *W = (double *)malloc(sizeof(double)*n*m);
    double *V = (double *)malloc(sizeof(double)*n*m);
    
    for(int i = 0; i < n; i++){
    	for(int j = 0;j < n; j++){
		    myput >> (*(A +i*n +j));
        }
    }
    myput.close();
    printf("Flag0\n");
    itersub(A, W, n, m);
    printf("Flag6\n");
    mat_mat(V, A, W, n, n, m);
    double *E = (double *)malloc(sizeof(double)*m*m);
    printf("Flag7\n");
    for(int i = 0; i < m; i++)
    {

        for(int j = 0; j < m; j++)
        {
            *(E + i*m + j) = 0;
            for(int k = 0; k < m; k++)
            {
                *(E + i*m + j) += ( *(W + k*m + i ) )*( *(V + k*m + j) );
            }
        }
    }
    double aux = 0;
    for(int i = 0; i < n; i++)
    {
        aux = (*(E + i*m + i));
        printf("%lf\n", aux);
    }


    free(A);
    free(W);
    free(V);
    free(E);
    return 0;
 }