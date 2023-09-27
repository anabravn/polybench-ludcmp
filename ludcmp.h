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
    3,
    100,
    2000,
    4000
};


/* Funções */

void print_array(int n, float *x);
void print_matrix(int n, float **a);
	
void init_array(int n,
            float **a, float *b, float *x, float *y);
		 
void kernel_ludcmp(int n,
            float **a, float *b, float *x, float *y);

void ludcmp_diagonal(int n,
            float **a, float *b, float *x, float *y);

void ludcmp_threads(int t, int n,
            float **a, float *b, float *x, float *y);


#endif /* !_LUDCMP_H */
