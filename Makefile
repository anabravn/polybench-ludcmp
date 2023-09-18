ludcmp: main.c ludcmp.c polybench.c ludcmp.h polybench.h
	gcc -O3 -I. main.c polybench.c ludcmp.c -DPOLYBENCH_TIME -DPOLYBENCH_DUMP_ARRAYS -DMINI_DATASET -o ludcmp
