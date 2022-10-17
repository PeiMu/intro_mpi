/*
 * print with different process
 * */
#include <stdio.h>
#include <mpi.h>

void main(int argc, char** argv){
  int ierr, root_process, num_procs, my_id;
  MPI_Status status;
  ierr = MPI_Init(&argc, &argv);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  for (size_t idx = 0; idx < 10; idx++)
    printf("process %d, idx %ld: %ld\n", my_id, idx, idx%(my_id+1));

  ierr = MPI_Finalize();
  return;
}
