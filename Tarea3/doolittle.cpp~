#include<iostream>
#include<stdio.h>
#include<fstream>

using namespace std;

int main(){
	int n;
	cin >> n;
   float A[n][n]={0}, B[n]={0}, X[n]={0}, L[n][n]={0}, Y[n]={0}, U[n][n]={0},sum=0;
   for(i=0;i<n;i++){
   	for(j=0;j<n;j++){
			cin >> A[i][j];
      }
   }
   
   for(i=0;i<n;i++){
   	cin >> B[i];
   }

    //Descomposicion LU

    //Llenado de ceros y unos en posiciones conocidas
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++)
		{            
      	if(i > j){
         	U[i][j]=0;    //Ceros debajo de la diagonal para la matriz U
         }
         else if(i==j){
         	L[i][j]=1;    //Unos en la diagonal de L
         } else{
           L[i][j]=0;    //Ceros encima de la diagonal para la matriz L 
        	}
    	}
    }

    for(int i = 0;i < n; i++){
        for(int j = 0;j < n; j++){
            sum=0;
            if(i <= j){               //Es decir, solo se llenan los elementos de la diagonal y encima de ella para U
                for(int k = 0;k < n;k++){
                    if(k != i){
                        sum=sum+L[i][k]*U[k][j];
                    }else {
                        U[i][j]=A[i][j]-sum;               //Llenado de elementos restantes de U
                    }
                }
            } else{                 //Es decir, solo se llenan los elementos debajo de la diagonal para L
                for(int k = 0;k<n;k++){
                    if(k!=j){
                        sum = sum + L[i][k]*U[k][j];
                    }else {
                        L[i][j]= (A[i][j] - sum)/U[j][j];      //Llenado de elementos restantes de L
                    }
                }
            }
        }
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)

                        printf ("%10.2f",L[i][j]);
            printf("\n    ");
    }

        printf("\n\n U =");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
                         printf ("%10.2f",U[i][j]);
            printf("\n    ");
    }

    Y[0]=B[0]/L[0][0];
    for(i=1;i<n;i++)
    {
        sum=0;
        for(j=0;j<i;j++)
        {
            sum=sum+Y[j]*L[i][j];

        }
        Y[i]=B[i]-sum;
    }
    printf("\n\n Y =");
    for(i=0;i<n;i++)
    {
                printf ("%10.2f",Y[i]);
            printf("\n    ");
    }

    X[n-1]=Y[n-1]/U[n-1][n-1];
    for(i=n-2;i>=0;i--){
        sum=0;
        for(j=n-1;j>i;j--)
            sum=sum+X[j]*U[i][j];
        X[i]=(Y[i]-sum)/U[i][i];
    }

    printf("\nLa solucion es :\n");
    for(i=0;i<n;i++)
        printf("\n x[%d] = %.2f ",i+1,X[i]);
    printf("\n\n");
}