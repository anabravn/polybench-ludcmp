/**
 * This version is stamped on May 10, 2016
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://polybench.sourceforge.net
 */
/*
 * polybench.h: this file is part of PolyBench/C
 *
 * Polybench header for instrumentation.
 *
 * Programs must be compiled with `-I utilities utilities/polybench.c'
 *
 * Optionally, one can define:
 *
 * -DPOLYBENCH_TIME, to report the execution time,
 *   OR (exclusive):
 * -DPOLYBENCH_PAPI, to use PAPI H/W counters (defined in polybench.c)
 *
 *
 * See README or utilities/polybench.c for additional options.
 *
 */
#ifndef POLYBENCH_H
# define POLYBENCH_H

# include <stdlib.h>

# define polybench_start_instruments
# define polybench_stop_instruments
# define polybench_print_instruments


/* PAPI support. */
# ifdef POLYBENCH_PAPI
extern const unsigned int polybench_papi_eventlist[];
#  undef polybench_start_instruments
#  undef polybench_stop_instruments
#  undef polybench_print_instruments
#  define polybench_set_papi_thread_report(x)	\
   polybench_papi_counters_threadid = x;
#  define polybench_start_instruments				\
  polybench_prepare_instruments();				\
  polybench_papi_init();					\
  int evid;							\
  for (evid = 0; polybench_papi_eventlist[evid] != 0; evid++)	\
    {								\
      if (polybench_papi_start_counter(evid))			\
	continue;						\

#  define polybench_stop_instruments		\
      polybench_papi_stop_counter(evid);	\
    }						\
  polybench_papi_close();			\

#  define polybench_print_instruments polybench_papi_print();
# endif


/* Timing support. */
# if defined(POLYBENCH_TIME) || defined(POLYBENCH_GFLOPS)
#  undef polybench_start_instruments
#  undef polybench_stop_instruments
#  undef polybench_print_instruments
#  define polybench_start_instruments polybench_timer_start();
#  define polybench_stop_instruments polybench_timer_stop();
#  define polybench_print_instruments polybench_timer_print();
extern double polybench_program_total_flops;
extern void polybench_timer_start();
extern void polybench_timer_stop();
extern void polybench_timer_print();
# endif

/* PAPI support. */
# ifdef POLYBENCH_PAPI
extern int polybench_papi_start_counter(int evid);
extern void polybench_papi_stop_counter(int evid);
extern void polybench_papi_init();
extern void polybench_papi_close();
extern void polybench_papi_print();
# endif

extern void polybench_prepare_instruments();


#endif /* !POLYBENCH_H */
