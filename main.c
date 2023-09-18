#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "polybench.h"
#include "ludcmp.h"


int main(int argc, char** argv)
{
  int n = 0; 

  if (argc < 3) {
      fprintf(stderr, "Usagem: ./ludcmp -d [SIZE]\n");
      return 1;

  } else if (!strcmp(argv[1], "-d")) {
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
  }


  /* Variable declaration/allocation. */
  POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, n, n, n, n);
  POLYBENCH_1D_ARRAY_DECL(b, DATA_TYPE, n, n);
  POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, n, n);
  POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, n, n);


  /* Initialize array(s). */
  init_array (n,
	      POLYBENCH_ARRAY(A),
	      POLYBENCH_ARRAY(b),
	      POLYBENCH_ARRAY(x),
	      POLYBENCH_ARRAY(y));

  /* Start timer. */
  polybench_start_instruments;

  /* Run kernel. */
  kernel_ludcmp (n,
		 POLYBENCH_ARRAY(A),
		 POLYBENCH_ARRAY(b),
		 POLYBENCH_ARRAY(x),
		 POLYBENCH_ARRAY(y));

  /* Stop and print timer. */
  polybench_stop_instruments;
  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(x)));

  /* Be clean. */
  POLYBENCH_FREE_ARRAY(A);
  POLYBENCH_FREE_ARRAY(b);
  POLYBENCH_FREE_ARRAY(x);
  POLYBENCH_FREE_ARRAY(y);

  return 0;
}
