#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "polybench.h"
#include "ludcmp.h"

int main(int argc, char** argv)
{
  int n = 0; 
  float **a, *b, *x, *y;

  // RANDOM SEED
  srand(0);

  if (argc >= 3 && !strcmp(argv[1], "-d")) {
      int i;

      for(i = 0; i < 3; i++) {
         if(!strcmp(argv[2], dataset_labels[i]))
             break;
      }

      if (i >= 3) {
            fprintf(stderr, "Erro: Tamanho inválido\n");
            return 2;
      }

      n = dataset_sizes[i];
  } else {
      fprintf(stderr, "Usagem: ./ludcmp -d [SIZE]\n");
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
  print_matrix(n, a);

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_ludcmp (n, a, b, x, y);

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  print_matrix(n, a);
  print_array(n, x);

  return 0;
}
