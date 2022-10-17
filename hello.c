#include <stdio.h>
#include <mpi.h>

void main(int argc, char** argv) {
  int ierr;
  ierr = MPI_Init(&argc, &argv);
  printf("Hello World\n");
  ierr = MPI_Finalize();
  return;
}
