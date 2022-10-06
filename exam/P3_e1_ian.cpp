#include<stdio.h>
#include<math.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>

#define toler 0.000000001
#define numgran 100000000

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
    for(int i = 0; i < n; i++) (*res) += (*(vec_0 + i) )*(*(vec_1 + i) );
}

void normaliza(double *vec, int n)
{
    double suma;
    vec_vec(vec, vec, &suma, n);
    
   if(suma != 0)
   {
		suma = sqrt(suma);
		for(int i = 0; i < n; i++) (*(vec + i)) /= suma;
   }
}

void met_pot(double *mat, double *vec_v, double *phi, double *val, int n)
{
    double error = numgran, valor = 0;
    *val = 0;
    double *vec_n = (double *)malloc(sizeof(double)*n);
    for(int i = 0; i < n; i++) (*(phi + i)) = (*(vec_v + i));
    for(int i = 0; i < 2000; i++)
    {
        mat_vec(mat, phi, vec_n, n);
        vec_vec(phi, vec_n, &valor, n);
        error = fabs(valor - (*val));
        *val = valor;
        normaliza(vec_n, n);
        for(int j = 0; j < n; j++)
        {
            (*(phi + j)) = (*(vec_n + j));
        }
        if(error < toler) break;
    }
    free(vec_n);
}

void hotelling(double *mat, double *phi, double lamb, int n)
{
	double div, aux;
	vec_vec(phi, phi, &div, n);
	if(div != 0)
	{		
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{			
				aux = lamb/div;
				aux = aux * (*(phi + i)) * (*(phi + j));				
				*(mat + i*n + j) -= aux;	
			}	
		}	
	}
}

int main()
{
    int n,m;
    ifstream myput;
    myput.open("mat.txt");
    myput >> n >> m ;
    double *mat = (double *)malloc(sizeof(double)*n*n);
    double *inv = (double *)malloc(sizeof(double)*n*n);
    double *vec = (double *)malloc(sizeof(double)*n);
	double *phi = (double *)malloc(sizeof(double)*n);	
	
    for(int i = 0; i < n; i++) *(vec + i) = 1;
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
       	    myput >> (*(mat + i*n + j));
    }

    myput.close();


    myput.open("inv.txt");
    myput >> n >> m ;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
       	    myput >> (*(inv + i*n + j));
    }

    myput.close();

	double aux = n *n;
    ofstream f("eigenvector.txt");   
    cout <<"Los "<< m <<" eigenvalores mas grandes son son: \n";
    for(int j = 0; j < m; j++)
    {
   	    met_pot(mat, vec, phi, &aux, n);
    
    	f <<"El eigenvalor es: "<<aux<<endl;
        cout<<aux<<endl;
        f <<"El eigenvector es:\n";
   	    for(int i = 0; i < n; i++) f <<(*(phi + i))<<"\n";
 		f <<"\n";
 		hotelling(mat, phi,aux,n);
	}
	

    for(int i = 0; i < n; i++) *(vec + i) = 1;

    aux = n*n;
    cout <<"Los "<< m <<" eigenvalores mas chicos son son: \n";
    for(int j = 0; j < m; j++)
    {
   	    met_pot(inv, vec, phi, &aux, n);
    
    	f <<"El eigenvalor es: "<<(1/aux)<<endl;
        cout<<(1/aux)<<endl;
        f <<"El eigenvector es:\n";
   	    for(int i = 0; i < n; i++) f <<(*(phi + i))<<"\n";
 		f <<"\n";
 		hotelling(inv, phi,aux,n);
	}
	
	free(phi);
    free(inv);
	free(mat);
    free(vec);
    return 0;
}