#include<stdio.h>
#include<iostream>

using namespace std;

int main()
{
   int n;
   int b[10000];
   int A[10000];
   int res[10000];
   cin>>n;
   for(int i = 0; i < n; i++) cin>>b[i];
   for(int i = 0; i < n; i++)
   {
       cin>>A[i];
       if(A[i] == 0)
       {
          cout<<"La matriz no tiene solucion"<<endl;
           return 0;
         }
        res[i] = b[i]/A[i];
    }
    cout<<"El vector que buscamos es:\n";
    for(int i = 0; i < n; i++)
     cout<<res[i]<<"\n";
}