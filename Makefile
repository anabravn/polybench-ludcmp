ludcmp: ludcmp.c polybench.c ludcmp.h polybench.h
	gcc -O3 -I. polybench.c ludcmp.c -DPOLYBENCH_TIME -o ludcmp
