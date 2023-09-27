#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "polybench.h"
#include "ludcmp.h"

int main(int argc, char** argv)
{
  int t, n, seq; 
  float **a, *b, *x, *y;

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

  /* Alocar arrays */
  a = (float **) malloc(sizeof(float*) * n);
  b = (float *) malloc(sizeof(float) * n);
  x = (float *) malloc(sizeof(float) * n);
  y = (float *) malloc(sizeof(float) * n);

  for(int i = 0; i < n; i++)
      a[i] = (float *) malloc(sizeof(float) * n);

  /* Initialize array(s). */
  init_array (n, a, b, x, y);

  polybench_start_instruments;

  if (!seq)
      ludcmp_threads (t, n, a, b, x, y);
  else
      kernel_ludcmp (n, a, b, x, y);

  polybench_stop_instruments;
  polybench_print_instruments;

  return 0;
}
