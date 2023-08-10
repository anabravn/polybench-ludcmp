/**
 * ludcmp.h: This file is part of the PolyBench 3.0 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#ifndef LUDCMP_H
# define LUDCMP_H

/* Define the possible dataset sizes. */
#  define SMALL_DATASET 1000
#  define MEDIUM_DATASET 5120 
#  define LARGE_DATASET 6144

# ifndef DATA_TYPE
#  define DATA_TYPE double
#  define DATA_PRINTF_MODIFIER "%0.2lf "
# endif


#endif /* !LUDCMP */
