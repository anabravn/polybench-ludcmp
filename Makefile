ludcmp: main.c ludcmp.c polybench.c
	gcc -Wall -g -I. main.c ludcmp.c polybench.c -DPOLYBENCH_TIME -o ludcmp



