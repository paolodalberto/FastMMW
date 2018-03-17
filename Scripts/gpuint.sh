#!/bin/bash

export ARC=Fiji
export ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0
export LD_LIBRARY_PATH=/opt/AMDAPPSDK-3.0/lib/x86_64/:${ARCHITECTURE}/lib64/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../OpenBLAS/install/lib;

/usr/bin/make clean intgpu MACROS="-D$2 -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=9000" TYPE=$1 UNROLL=4 > out 2>&1

for i in 10 #15 #20 #25 30 
do
    #echo ${i} 0 1 0 1 
    #echo ${i}000 0 1 0 1  | Executable/$1/int_gpu  | grep GFLOP  | grep HOT
    #echo ${i} 0 0 0 0 
    #echo ${i}000 0 0 0 0  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
    #echo ${i} 1 1 1 1 
    #echo ${i}000 1 1 1 1  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
    echo ${i} 2 3 2  3 
    echo ${i}000 2 3 2 3  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
    echo ${i} 2 2 2 2 
    echo ${i}000 2 2 2 2  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
    echo ${i} 3 3 3 3  
    echo ${i}000 3 3 3 3  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
done
for i in 15 #20 #25 30 
do
    echo ${i} 0 1 0 1 
    echo ${i}000 0 1 0 1  | Executable/$1/int_gpu  | grep GFLOP  | grep HOT
    echo ${i} 0 0 0 0 
    echo ${i}000 0 0 0 0  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
    echo ${i} 1 1 1 1 
    echo ${i}000 1 1 1 1  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
    echo ${i} 2 3 2  3 
    echo ${i}000 2 3 2 3  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
    echo ${i} 2 2 2 2 
    echo ${i}000 2 2 2 2  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
    echo ${i} 3 3 3 3  
    echo ${i}000 3 3 3 3  | Executable/$1/int_gpu  | grep GFLOP | grep HOT
done
