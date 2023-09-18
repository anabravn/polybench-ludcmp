sources = ludcmp.c polybench.c 
 
ludcmp: $(sources)
	gcc -O3 -I. main.c $(sources) -DPOLYBENCH_TIME \
		-DPOLYBENCH_DUMP_ARRAYS -o ludcmp

check: $(sources) 
	gcc -O3 -I. test.c $(sources) -o check -lcheck

test: check
	./check

