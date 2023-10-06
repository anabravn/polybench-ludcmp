#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "polybench.h"
#include "ludcmp.h"

int main(int argc, char** argv)
{
  int t, n, seq; 
  float **a;

  // RANDOM SEED
  srand(0);

  if (argc >= 4) {
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

    if(argc >= 5 && !strcmp(argv[3], "-t")) {
        t = atoi(argv[4]); 
    }
    else if(!strcmp(argv[3], "-s")) {
        seq = 1;
    }
  } else {
      fprintf(stderr, "Usagem: ./ludcmp -d [SIZE] -t [threads]\n");
      return 1;
  }

  a = init_matrix(n); 

  polybench_start_instruments;

  if (!seq)
      ludcmp_threads (t, n, a);
  else
      kernel_ludcmp (n, a);

  if (n == dataset_sizes[0]) 
      print_matrix(n, a);

  free_matrix(n, a);

  polybench_stop_instruments;
  polybench_print_instruments;

  return 0;
}
