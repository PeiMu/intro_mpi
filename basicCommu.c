/*
 * accumulate 1-11 parallel
 * */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define max_rows 100000
#define send_data_tag 2001
#define return_data_tag 2002

int array[max_rows];
int array2[max_rows];

int main(int argc, char** argv){
  long int sum, partial_sum;
  int ierr, num_procs, my_id, i, num_rows, an_id, sender;
  int num_rows_to_receive, avg_rows_per_process, num_rows_received, start_row, end_row, num_rows_to_send;
  const int root_process = 0;
  MPI_Status status;
  ierr = MPI_Init(&argc, &argv);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  if (my_id == root_process) {
    /* I must be the root process, so I will query the user to determine how many numbers to sum. */
//    printf("please enter the number of numbers to sum: ");
    scanf("%i", &num_rows);
      
    if(num_rows > max_rows) {
      printf("Too many numbers.\n");
      exit(1);
    }

    avg_rows_per_process = (num_rows + num_procs - 1) / num_procs;

    /* initialize an array */
    for (i = 0; i < num_rows; i++) {
      array[i] = i + 1;
    }

    /* distribute a portion of the vector to each child process */
    for (an_id = 1; an_id < num_procs; an_id++) {
      start_row = an_id * avg_rows_per_process;
      end_row = (an_id + 1) * avg_rows_per_process;

      if(num_rows < end_row)
          end_row = num_rows;

      num_rows_to_send = end_row - start_row;

      ierr = MPI_Send(&num_rows_to_send, 1 , MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);
      ierr = MPI_Send(&array[start_row], num_rows_to_send, MPI_INT, an_id, send_data_tag, MPI_COMM_WORLD);
    }

    /* and calculate the sum of the values in the segment assigned to the root process */
    sum = 0;
    for (i = 0; i < avg_rows_per_process; i++)
        sum += array[i];

    printf("sum %ld calculated by root process\n", sum);

      /* and, finally, I collect the partial sums from the slave processes,
       * print them, and add them to the grand sum, and print it */
      for (an_id = 1; an_id < num_procs; an_id++) {
          ierr = MPI_Recv(&partial_sum, 1, MPI_LONG, MPI_ANY_SOURCE,
                          return_data_tag, MPI_COMM_WORLD, &status);
          sender = status.MPI_SOURCE;
          printf("Partial sum %ld return from process %d\n", partial_sum, sender);
          sum += partial_sum;
      }
      printf("The grand total is: %ld\n", sum);
  } else {
      /* I must be a slave process, so I must receive my array segment,
       * storing it in a "local" array, array1. */
      ierr = MPI_Recv(&num_rows_to_receive, 1, MPI_INT, root_process,
                      send_data_tag, MPI_COMM_WORLD, &status);
      ierr = MPI_Recv(&array2, num_rows_to_receive, MPI_INT, root_process,
                      send_data_tag, MPI_COMM_WORLD, &status);
      num_rows_received = num_rows_to_receive;

      /* Calculate the sum of my portion of the array */
      partial_sum = 0;
      for (i = 0; i < num_rows_received; i++) {
          partial_sum += array2[i];
      }

      /* and finally, send my partial sum to the root process */
      ierr = MPI_Send(&partial_sum, 1, MPI_LONG, root_process, return_data_tag, MPI_COMM_WORLD);
  }
  ierr = MPI_Finalize();

  return 0;
}
