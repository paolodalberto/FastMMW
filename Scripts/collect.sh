#!/bin/bash

export ARC=Fiji
export ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0
export LD_LIBRARY_PATH=/opt/AMDAPPSDK-3.0/lib/x86_64/:${ARCHITECTURE}/lib64/
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/paolo/fusion/paolo/Desktop/MM/Epyc/OpenBLAS/install/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../OpenBLAS/install/lib;
#export OPENBLAS_NUM_THREADS=128


export j=11111111111111110000000000000000

CORES=32

for D in  Single 
do
    for i in 10 15 20 25 30 35 #40 #45 #50 55 60 
    do
	for e in atlas winogradatlas marcoatlas_pipe # gotos winograd marco_pipe_2 
	do
	    echo $D ${i}000 $e 
	    echo "0 0 1 1 1 ${i}000 ${i}000 ${i}000 ${i}000 ${CORES} $j" | Executable/${D}/${e} | grep GFLOP 
	done
    done
done
for D in   SComplex  Double
do
    for i in 10 15 20 25 30 #35 40 #45 50 55  
    do
	for e in atlas winogradatlas marcoatlas_pipe # gotos winograd marco_pipe_2 
	do
	    echo $D ${i}000 $e 
	    echo "0 0 1 1 1 ${i}000 ${i}000 ${i}000 ${i}000 ${CORES} $j" | Executable/${D}/${e} | grep GFLOP 
	    #sleep 10
	done
    done
done
for D in DComplex
do
    for i in 5 10 15 20 25 #30 #35 40
    do
	for e in atlas winogradatlas marcoatlas_pipe # gotos winograd marco_pipe_2 
	do
	    echo $D ${i}000 $e 
	    echo "0 0 1 1 1 ${i}000 ${i}000 ${i}000 ${i}000 ${CORES} $j" | Executable/${D}/${e} | grep GFLOP 
	    #sleep 10
	done
    done
done
