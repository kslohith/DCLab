#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc , char* argv[]){
  MPI_Comm even_comm_id;
  MPI_Comm odd_comm_id;
  MPI_Group even_group_id;
  MPI_Group odd_group_id;
  MPI_Group global_group_id;
  int even_id , even_p , even_id_sum;
  int odd_id , odd_p , odd_id_sum;
  int rank , size;


  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if(rank == 0){
    printf("Master process running with %d processess\n",size);
  }
  printf("%d process says HELLO WORLD\n",rank);

  MPI_Comm_group(MPI_COMM_WORLD,&global_group_id);

  even_p = (size + 1)/2;
  int* even_rank = (int*) malloc(even_p * sizeof(int));
  int j = 0;
  for(int i = 0; i < size; i = i + 2){
    even_rank[j] = i;
    j += 1;
  }
  MPI_Group_incl(global_group_id,even_p,even_rank,&even_group_id);
  MPI_Comm_create(MPI_COMM_WORLD,even_group_id,&even_comm_id);

  odd_p = (size)/2;
  int* odd_rank = (int*) malloc(odd_p * sizeof(int));
  int j1 = 0;
  for(int i = 1; i < size; i = i + 2){
    odd_rank[j1] = i;
    j1 += 1;
  }
  MPI_Group_incl(global_group_id,odd_p,odd_rank,&odd_group_id);
  MPI_Comm_create(MPI_COMM_WORLD,odd_group_id,&odd_comm_id);
  if(rank%2 == 0){
    MPI_Comm_rank(even_comm_id,&even_id);
    odd_id = -1;
  }
  else{
    MPI_Comm_rank(odd_comm_id,&odd_id);
    even_id = -1;
  }
 if( even_id != -1 ){
   MPI_Reduce(&rank,&even_id_sum,1,MPI_INT,MPI_SUM,0,even_comm_id);
 }
 if( even_id == 0 ){
   printf("Number of processes in even communincator is %d\n",even_p);
   printf("Global sum of even id is %d\n",even_id_sum);
 }
 if( odd_id != -1 ){
   MPI_Reduce(&rank,&odd_id_sum,1,MPI_INT,MPI_SUM,0,odd_comm_id);
 }
 if( odd_id == 0 ){
   printf("Number of processes in even communincator is %d\n",odd_p);
   printf("Global sum of odd id is %d\n",odd_id_sum);
 }
 MPI_Finalize();
}
