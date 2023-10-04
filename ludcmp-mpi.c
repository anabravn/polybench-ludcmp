#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "ludcmp.h"

int main(int argc, char **argv) {
    int process_rank, world_size;
    int n = 3;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    float **a, *buffer;
   
    if (process_rank == 0) {
        a = init_matrix(n);
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
                MPI_Barrier(MPI_COMM_WORLD);
            }

            if (process_rank == 0) {
                printf("0 -> enviando a[%d][%d] para %d\n", i, j, dest);
                MPI_Send(&a[i][j], 1, MPI_FLOAT, dest, MPI_ANY_TAG, MPI_COMM_WORLD);
            } else if (process_rank == dest) {
                float w;
                
                MPI_Recv(&w, 1, MPI_FLOAT, 0, MPI_ANY_TAG, 
                        MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("%d -> recebido %f\n", process_rank, w);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
