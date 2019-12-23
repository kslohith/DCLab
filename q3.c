#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>


int* prime_table(int size)
{
    int* primes = (int*) malloc(size * sizeof(int));
    int p = 0;
    int i = 2;
    int prime;
    while( p <= size )
    {
        prime = 1;
        for(int j = 2; j < i; j++ )
        {
            if( (i%j) == 0 )
            {
                prime = 0;
                break;
            }
        }
        if(prime)
        {
            primes[p] = i;
            p += 1;
        }
        i += 1;
    }

    return primes;
}

double* sine_table(int size)
{
    double pi = 3.1415675369;
    double* sines = (double*) malloc(size * sizeof(double));

    for(int i = 0; i < size; i++ ){
        sines[i] = 0.0;
        for(int j = 0; j <= i; j++ ){
            double a = (double) (j * pi)/(double) (size-1);
            sines[i] += sin(a);
        }
    }

    return sines;
}




void main()
{
    int* a;
    double* b;
    int size = 10;

    for(int i = 0; i < 4; i++ )
    {
        for(int j = 0;j < 4; j++ )
        {
            double t1 = omp_get_wtime();
            #pragma omp parallel sections
            {

                #pragma omp section
                {
                    a = (int*) malloc(size * sizeof(int));
                    a = prime_table(size);
                }

                #pragma omp section
                {
                    b = (double*) malloc(size * sizeof(double));
                    b = sine_table(size);
                }

            }
            double t2 = omp_get_wtime();

            printf("Time taken is %f\n",(t2-t1));
        }

        size = size * 10;
    }

}
