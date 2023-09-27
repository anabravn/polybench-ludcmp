/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
/* ludcmp.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "polybench.h"

/* Array initialization. */
void init_array (int n,
         float **a, float *b, float *x, float *y)
{
  int i, j;

  for (i = 0; i < n; i++)
    {
      x[i] = 0;
      y[i] = 0;
      b[i] = (i+1)/n/2.0 + 4;
    }

  for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
        a[i][j] = rand() % 100;
    }
}


void print_array(int n, float *x)
{
  int i;

  for (i = 0; i < n; i++) {
    printf("%f ", x[i]);
  }

  printf("\n");
}

void print_matrix(int n, float **a)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for(j = 0; j < n; j++) 
        printf("%f ", a[i][j]);

    printf("\n");
  }

  printf("\n");
}



void kernel_ludcmp(int n,
         float **a, float *b, float *x, float *y)
{
  int i, j, k;
  float w;

  for (i = 0; i < n; i++) {
    for (j = 0; j <i; j++) {
       w = a[i][j];
       for (k = 0; k < j; k++) {
          w -= a[i][k] * a[k][j];
       }
        a[i][j] = w / a[j][j];
    }
   for (j = i; j < n; j++) {
       w = a[i][j];
       for (k = 0; k < i; k++) {
          w -= a[i][k] * a[k][j];
       }
       a[i][j] = w;
    }
  }

  for (i = 0; i < n; i++) {
     w = b[i];
     for (j = 0; j < i; j++)
        w -= a[i][j] * y[j];
     y[i] = w;
  }

   for (i = n-1; i >=0; i--) {
     w = y[i];
     for (j = i+1; j < n; j++)
        w -= a[i][j] * x[j];
     x[i] = w / a[i][i];
  }
}
