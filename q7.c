#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>

#define BUF_SIZE 32

int main(int argc , char* argv[]){
   int rank , size , root = 3 , tag = 0 , temp = 0;
   char msg[BUF_SIZE];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;
    
    if( rank == 3 ){
        strcpy(msg,"HELLO CAT");
        for(int i = 0; i < size; i++ ){
            if(i != 3){
                MPI_Send(msg,BUF_SIZE,MPI_CHAR,i,tag,MPI_COMM_WORLD);
            }
        }
    }
   else{
       MPI_Recv(msg,BUF_SIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD,&status);
       printf("%s in process %d from process %d",msg,rank,root);
   }

   MPI_Finalize();

}
