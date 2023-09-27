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
    printf("%0.4f ", x[i]);
  }

  printf("\n");
}

void print_matrix(int n, float **a)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for(j = 0; j < n; j++) 
        printf("%0.4f ", a[i][j]);

    printf("\n");
  }

  printf("\n");
}

void ludcmp_diagonal(int n,
         float **a, float *b, float *x, float *y)
{
    int i, j, k;
    float w;

    /* Itera pelo índice da anti-diagonal */
    for (int d = 0; d < (2 * n) - 1; d++) {
        int x = d < n ? 0 : d - n + 1;
        int y = d < n ? d : n - 1;

        /* Itera por cada elemento da anti-diagonal d */
        for (i = x; i <= y; i++) {
            j = d - i;

            /* Se a[i][j] pertence a matriz L */
            if(i > j) {
                w = a[i][j];
                for (k = 0; k < j; k++) {
                    w -= a[i][k] * a[k][j];
                }
                a[i][j] = w / a[j][j];
            }

            /* Se a[i][j] pertence a matriz U */
            if (j >= i) {
                w = a[i][j];
                for (k = 0; k < i; k++) {
                    w -= a[i][k] * a[k][j];
                }
                a[i][j] = w;
            }
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
