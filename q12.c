#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int search(int a , int b , int c , int rank , int size );
int f(int value);

int main(int argc,char* argv[]){


    int rank , size;
    int a = 1;
    int b = 35243637;
    int c = 64;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);


    if( rank == 0 ){
        printf("Master process with %d tasks\n",size);
        printf("Search from a to b to find integer J which satisfy f(J) = c\n");
        printf("a is %d\n",a);
        printf("b is %d\n",b);
        printf("c is %d\n",c);
    }

    double t1 = MPI_Wtime();
    int j = search(a,b,c,rank,size);
    double t2 = MPI_Wtime();

    if(j != -1 ){
        printf("Process %d found j to be %d\n",rank,j);
        printf("Verify that f(J) %d\n", f(j) );
        printf("Total time taken is %f",(t2-t1));
    }

    MPI_Finalize();
}
int search(int a, int b , int c , int rank , int size){
    int ji;
    int j = -1;
    for( int i = a + rank; i > 0 && i <= b; i = i + size){
        ji = f(i);

        if( ji == c ){
           j = i;
           break;
        }
    }

    return j;
}


int f(int value){
     
    return value*value*value;
}


