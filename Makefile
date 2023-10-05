ludcmp: main.c ludcmp.c polybench.c ludcmp.h polybench.h
	gcc -Wall -g -I. main.c ludcmp.c polybench.c \
		-DPOLYBENCH_TIME -o ludcmp

ludcmp-mpi: ludcmp.c ludcmp.h ludcmp-mpi.c
	mpicc ludcmp.c ludcmp-mpi.c -o ludcmp-mpi

mpirun: ludcmp-mpi
	# Run nodes on local network
	mpirun --mca btl_tcp_if_include lo \
		--use-hwthread-cpus ./ludcmp-mpi
