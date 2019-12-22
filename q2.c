#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void main()
{
  int n;
  printf("Enter the size for the matrix");
  scanf("%d",&n);

  int a[n][n] , c[n] , res[n];

  for(int i = 0; i < n; i++ ){
    for(int j = 0; j < n; j++ ){
        a[i][j] = rand()%100;
    }
    c[i] = rand()%100;
  }

  printf("Matrix a is \n");
  for(int i = 0; i < n; i++ ){
    for(int j = 0; j < n; j++ ){
        printf("%d\t",a[i][j]);
    }
    printf("\n");
  }

  printf("Vector v is \n");
  for(int i = 0; i < n; i++ ){
    printf("%d \t",c[i]);
  }

  #pragma omp parallel for num_threads(8)
  for(int i = 0; i < n; i++ ){
    for(int j = 0; j < n; j++ ){
            res[i] += a[i][j] * c[j];
     }
  }

  printf("Resultant matrix is \n");

  for(int i = 0; i < n; i++ ){
        printf("%d\t",res[i]);
 }

}
