#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "ludcmp.h"

int main(int argc, char **argv) {
    MPI_Comm MPI_COMM_WORKERS;
    float **a, *buffer;
    int process_rank, world_size;
    int n = 3;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    MPI_Comm_split(MPI_COMM_WORLD, process_rank > 0, 
                   process_rank, &MPI_COMM_WORKERS);

   
    a = init_matrix(n);
    if (process_rank == 0) {
        print_matrix(n, a);
    }

    for (int d = 0; d < (2 * n) - 1; d++) { 
        int x = d < n ? 0 : d - n + 1;
        int y = d < n ? d : n - 1;

        int m = (y - x) + 1;
        int dest = 1;

        for (int i = x; i <= y; i++, dest++) {
            int j = d - i;

            if (dest >= world_size) {
                dest = 1;
            }

            if (process_rank == dest) {
                MPI_Recv(&a[i][j], 1, MPI_FLOAT, 0, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("%d -> receiving a[%d][%d]\n", process_rank, i, j);

                /*
                if(i > j) {
                w = a[i][j];
                for (k = 0; k < j; k++) {
                    w -= a[i][k] * a[k][j];
                }
                a[i][j] = w / a[j][j];
                }

                if (j >= i) {
                w = a[i][j];
                for (k = 0; k < i; k++) {
                    w -= a[i][k] * a[k][j];
                }
                a[i][j] = w;
                }
                */

                //MPI_Bcast(&a[i][j], 1, MPI_FLOAT, process_rank, MPI_COMM_WORLD);
                printf("%d -> broadcasting result a[%d][%d]\n", process_rank, i, j);

            } else if (process_rank == 0) {
                printf("0 -> sending a[%d][%d] to %d\n", i, j, dest);
                MPI_Send(&a[i][j], 1, MPI_FLOAT, dest, i, MPI_COMM_WORLD);
            }
        }
       
        printf("%d -> at the barrier\n", process_rank);
        MPI_Barrier(MPI_COMM_WORKERS);
    }

    if(process_rank == world_size - 1) {
        print_matrix(n, a);
    }

    MPI_Finalize();
    return 0;
}
