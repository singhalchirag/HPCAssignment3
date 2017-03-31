#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "math.h"
#include "util.h"

int main(int argc, char** argv) {
 timestamp_type time1, time2; 
 
        
        //get_timestamp(&time2);
        //double elapsed = timestamp_diff_in_seconds(time1,time2);
        //printf("Time elapsed is %f seconds.\n", elapsed);
  MPI_Init(NULL, NULL);
  // Find out rank, size
  
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  int size = 1024*512;
  int *arr= calloc(size,sizeof(int));
  //int token[1024*512];
  int loops=atoi(argv[1]);
  int count =0;
  while(1){
  if (world_rank != 0) {
    MPI_Recv(arr, size, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d\n", world_rank, arr[0],
           world_rank - 1);
                
  }
  
   
  arr[0] = arr[0] + world_rank;
  MPI_Send(arr, size, MPI_INT, (world_rank + 1) % world_size, 0,
           MPI_COMM_WORLD);
  if(world_rank==0){get_timestamp(&time1);}
  if(world_rank!=0){
	count = count +1;
        if(count == loops){break;}
  }  
  if (world_rank == 0) {
    MPI_Recv(arr, size, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    get_timestamp(&time2);
    double elapsed = timestamp_diff_in_seconds(time1,time2);
    printf("Process %d received token %d from process %d\n", world_rank, arr[0],
           world_size - 1);
    count = count +1;
    printf("Time elapsed is %f seconds.\n", elapsed);
    if(count == loops){break;}
  }
    
}
//printf("finalizing");
//get_timestamp(&time2);
//double elapsed = timestamp_diff_in_seconds(time1,time2);
//printf("Time elapsed is %f seconds.\n", elapsed);
MPI_Finalize();

}
