#include <check.h>
#include <stdlib.h>

#include "polybench.h"
#include "ludcmp.h"

void assert_result(int n, DATA_TYPE POLYBENCH_1D(x,n,n), 
        DATA_TYPE POLYBENCH_1D(result,n,n)) {

    for (int i = 0; i < n; i++) {
        ck_assert(x[i] == result[i]);
    }
}

START_TEST (ludcmp_seq)
{
    int n = 20;
    DATA_TYPE result[] = {
        4.00, -0.00, -0.00, -0.00, -0.01, -0.01, -0.01, -0.01, 
        -0.02, -0.02, -0.03, -0.04, -0.04, -0.03, -0.02, -0.00,
        0.02, 0.06, 0.09, 0.11
    };


    POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, n, n, n, n);
    POLYBENCH_1D_ARRAY_DECL(b, DATA_TYPE, n, n);
    POLYBENCH_1D_ARRAY_DECL(x, DATA_TYPE, n, n);
    POLYBENCH_1D_ARRAY_DECL(y, DATA_TYPE, n, n);

    init_array (n,
          POLYBENCH_ARRAY(A),
          POLYBENCH_ARRAY(b),
          POLYBENCH_ARRAY(x),
          POLYBENCH_ARRAY(y));

    kernel_ludcmp (n,
         POLYBENCH_ARRAY(A),
         POLYBENCH_ARRAY(b),
         POLYBENCH_ARRAY(x),
         POLYBENCH_ARRAY(y));

    assert_result(n, POLYBENCH_ARRAY(x), result);
}

Suite *ludcmp_suite(void) {
    Suite *s;
    TCase *tc;

    s = suite_create("LU Decomposition");
    tc = tcase_create("LU Sequêncial");

    tcase_add_test(tc, ludcmp_seq);
    suite_add_tcase(s, tc);
}

int main(void) {
  int no_failed = 0;                   
  Suite *s;                            
  SRunner *runner;                     

  s = ludcmp_suite();                   
  runner = srunner_create(s);          

  srunner_run_all(runner, CK_NORMAL);  
  no_failed = srunner_ntests_failed(runner); 

  srunner_free(runner);                      

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
