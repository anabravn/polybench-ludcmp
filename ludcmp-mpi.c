#include <stdio.h> 
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

#include "ludcmp.h"

int main(int argc, char **argv) {
    MPI_Comm MPI_COMM_WORKERS;
    float **a, *buffer;
    int process_rank, world_size;
    int n;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    MPI_Comm_split(MPI_COMM_WORLD, process_rank > 0, 
                   process_rank, &MPI_COMM_WORKERS);

    if(!strcmp(argv[1], "-d")) {
          int i;

          for(i = 0; i < 4; i++) {
             if(!strcmp(argv[2], dataset_labels[i]))
                 break;
          }

          if (i >= 4) {
                fprintf(stderr, "Erro: Tamanho inválido\n");
                return 2;
          }

          n = dataset_sizes[i];
    }
   
    if (process_rank == 0) {
        a = init_matrix(n);
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

            for (int i=0; i < world_size-1; i++) {
                int tmp = (i == world_size-2) ? (size_per_proc + rem) : size_per_proc;

                MPI_Send(&buffer[i*size_per_proc], tmp, MPI_FLOAT, 
                        i + 1, i, MPI_COMM_WORLD); 
            }
       }

       if (process_rank != 0) {
           for (int proc=0; proc < world_size-1; proc++) {
               int tmp = (proc == world_size-2) ? (size_per_proc + rem) : size_per_proc;
               int x = start + size_per_proc * proc;
               int y = x + tmp;

               if(process_rank - 1 == proc) {
                    MPI_Recv(&buffer[proc*size_per_proc], tmp, MPI_FLOAT, 
                        0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

                    for(int i = x; i < y; i++)  {
                        int k, j = d - i;
                        float w;

                        a[i][j] = buffer[i - start];

                        if (i > j) {
                            w = a[i][j];
                            for (k = 0; k < j; k++) {
                              w -= a[i][k] * a[k][j];
                            }
                            a[i][j] = w / a[j][j];
                        } else {
                             w = a[i][j];
                           for (k = 0; k < i; k++) {
                                  w -= a[i][k] * a[k][j];
                               }
                           a[i][j] = w;
                        }

                        buffer[i - start] = a[i][j];
                    }
                } 

                MPI_Bcast(&buffer[proc*size_per_proc], tmp, MPI_FLOAT, proc, MPI_COMM_WORKERS);

                for (int i=start; i <= end; i++) {
                    int j = d - i;
                    a[i][j] = buffer[i - start];
                }
             }
        }
       
         MPI_Barrier(MPI_COMM_WORKERS);
    }

    if(process_rank == world_size - 1 && n <= dataset_sizes[0])
        print_matrix(n, a);

    MPI_Finalize();
    return 0;
}
