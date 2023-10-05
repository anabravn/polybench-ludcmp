#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "ludcmp.h"

int main(int argc, char **argv) {
    MPI_Comm MPI_COMM_WORKERS;
    float **a, *buffer;
    int process_rank, world_size;
    int n = 5;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    MPI_Comm_split(MPI_COMM_WORLD, process_rank > 0, 
                   process_rank, &MPI_COMM_WORKERS);
   
    if (process_rank == 0) {
        a = init_matrix(n);
        print_matrix(n, a);
    } else {
        a = alloc_matrix(n);
    }

    for (int d = 0; d < (2 * n) - 1; d++) { 
        int start = d < n ? 0 : d - n + 1;
        int end = d < n ? d : n - 1;

        int size = (end - start) + 1;
        int size_per_proc = size/(world_size - 1);
        int rem = size % (world_size-1);
        float *buffer = (float *) malloc(sizeof(float) * size);

        if (process_rank == 0) {
            for (int i=start; i <= end; i++) {
                int j = d - i;
                buffer[i - start] = a[i][j];
            }

            printf("0 -> sending ");
            print_array(size, buffer);

            for (int i=0; i < world_size-1; i++) {
                int tmp = (i == world_size-2) ? (size_per_proc + rem) : size_per_proc;

                printf("0 -> sending to %d -> ", i + 1);
                MPI_Send(&buffer[i*size_per_proc], tmp, MPI_FLOAT, 
                        i + 1, i, MPI_COMM_WORLD); 
                print_array(tmp, &buffer[i*size_per_proc]);
            }
       }

       if (process_rank != 0) {
           for (int i=0; i < world_size-1; i++) {
               int tmp = (i == world_size-2) ? (size_per_proc + rem) : size_per_proc;

               if(process_rank - 1 == i) {
                    MPI_Recv(&buffer[i*size_per_proc], tmp, MPI_FLOAT, 
                        0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

                    printf("%d -> received ", process_rank);
                    print_array(tmp, &buffer[i*size_per_proc]);

                    printf("%d -> broadcasting results ", process_rank);
                } else {
                    printf("%d -> receiving results from %d -> ", process_rank, i + 1);
                }

                MPI_Bcast(&buffer[i*size_per_proc], tmp, MPI_FLOAT, i, MPI_COMM_WORKERS);
                print_array(tmp, &buffer[i*size_per_proc]);
            }

            printf("%d -> diagonal %d -> ", process_rank, d);
            print_array(size, buffer);

            for (int i=start; i <= end; i++) {
                int j = d - i;
                a[i][j] = buffer[i - start];
            }
         }
       
         MPI_Barrier(MPI_COMM_WORKERS);
    }

    if(process_rank == world_size - 1)
        print_matrix(n, a);

    MPI_Finalize();
    return 0;
}
