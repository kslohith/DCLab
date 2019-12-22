#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void main()
{
    long long fact1 = 1 , fact2 = 1;
    int n = 0;
    printf("Enter the number for factorial\n");
    scanf("%d",&n);

    #pragma omp parallel for firstprivate(n) num_threads(8)
    for(int i = 1; i <= n; i++ ){
        fact1 = fact1 * i;
    }

    printf("Without using firstprivate the value of factorial of %d is %llu\n",n,fact1);

    #pragma omp parallel for firstprivate(n,fact2) num_threads(8)
    for(int i = 2; i <= n; i++ ){
        fact2 = fact2 * i;
    }

    printf("With using firstprivate the value of factorial of %d is %llu\n",n,fact2);


}
