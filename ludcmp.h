#ifndef _LUDCMP_H
# define _LUDCMP_H


const char *dataset_labels[] = {
    "MINI",
    "SMALL",
    "MEDIUM",
    "LARGE"
};

const int dataset_sizes[] = {
    3,
    3000,
    3500,
    4000
};


void print_array(int n, float *x);
void print_matrix(int n, float **a);

float **init_matrix(int n);
float **alloc_matrix (int n);
void free_matrix(int n, float **a); 
		 
void kernel_ludcmp(int n, float **a);
void ludcmp_diagonal(int n, float **a);
void ludcmp_threads(int t, int n, float **a);

#endif
