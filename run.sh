#!/bin/bash

threads=( 2 3 4 )

echo "time,size" >> "seq.csv"
echo "threads,time,size" >> "pthreads.csv"
echo "threads,time,size" >> "mpi.csv"

for i in "${threads[@]}"
do
    # SEQUENCIAL
    result=$(./ludcmp -d SMALL -s)
    echo $result,1 >> "seq.csv"

    result=$(./ludcmp -d MEDIUM -s)
    echo $result,2 >> "seq.csv"

    result=$(./ludcmp -d LARGE -s)
    echo $result,3 >> "seq.csv"

    for (( k=0; k<2; k++ ));
    do
        # PTHREADS
        result=$(./ludcmp -d SMALL -t $i)
        echo $i,$result,1 >> "pthreads.csv"

        result=$(./ludcmp -d MEDIUM -t $i)
        echo $i,$result,2 >> "pthreads.csv"

        result=$(./ludcmp -d LARGE -t $i)
        echo $i,$result,3 >> "pthreads.csv"

        # OPENMPI
        result=$(mpirun --mca btl_tcp_if_include lo \
		--use-hwthread-cpus -np $i ./ludcmp-mpi -d SMALL)
        echo $i,$result,1 >> "mpi.csv"

        result=$(mpirun --mca btl_tcp_if_include lo \
		--use-hwthread-cpus -np $i ./ludcmp-mpi -d MEDIUM)
        echo $i,$result,2 >> "mpi.csv"

        result=$(mpirun --mca btl_tcp_if_include lo \
		--use-hwthread-cpus -np $i ./ludcmp-mpi -d LARGE)
        echo $i,$result,3 >> "mpi.csv"
     done
done
