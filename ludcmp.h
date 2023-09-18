/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
#ifndef _LUDCMP_H
# define _LUDCMP_H

/* Define sample dataset sizes. */

const char *dataset_labels[] = {
    "MINI",
    "SMALL",
    "MEDIUM",
    "LARGE"
};

const int dataset_sizes[] = {
    20,
    100,
    2000,
    4000
};


/* Funções */

void print_array(int n,
         DATA_TYPE POLYBENCH_1D(b,n,n));
	
void init_array(int n,
		 DATA_TYPE POLYBENCH_2D(A,n,n,n,n),
         DATA_TYPE POLYBENCH_1D(b,n,n),
		 DATA_TYPE POLYBENCH_1D(x,n,n),
		 DATA_TYPE POLYBENCH_1D(y,n,n));

void kernel_ludcmp(int n,
		   DATA_TYPE POLYBENCH_2D(A,n,n,n,n),
		   DATA_TYPE POLYBENCH_1D(b,n,n),
		   DATA_TYPE POLYBENCH_1D(x,n,n),
		   DATA_TYPE POLYBENCH_1D(y,n,n));



#endif /* !_LUDCMP_H */
