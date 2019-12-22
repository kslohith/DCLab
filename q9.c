#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define SEED 35467892

int main(){
    int rank , size;
    long niter = 1000000;
    double x , y , z;
    int count = 0;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int recieved[size];
    int recvniter[size];
    srand(SEED+rank);
    if(rank != 0 ){
        for(int i = 0; i < niter; i++ ){
            x = ((double)rand())/RAND_MAX;
            y = ((double)rand())/RAND_MAX;
            z = sqrt(x*x + y*y);
            if(z <= 1){
                count++;
            }
        }
        for(int j = 0; j < size; j++ ){
            MPI_Send(&count,1,MPI_INT,0,1,MPI_COMM_WORLD);
            MPI_Send(&niter,1,MPI_LONG,0,2,MPI_COMM_WORLD);
        }
    }
    else if( rank == 0 ) {
        for(int i = 0; i < size; i++ ){
            MPI_Recv(&recieved[i],size,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&recvniter[i],size,MPI_LONG,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
    }
   if( rank == 0 ){
       int finalcount = 0;
       long finalniter = 0;

       for(int i = 0; i < size; i++ ){
           finalcount += recieved[i];
           finalniter += recvniter[i];
       }

       double pi = ((double) finalcount/(double) finalniter) * 4.0;
       printf("The value of pi is %f",pi);
   }

   MPI_Finalize();
}
