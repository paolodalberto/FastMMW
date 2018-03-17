#!/bin/bash

export ARC=Fiji
export ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0
export LD_LIBRARY_PATH=/opt/AMDAPPSDK-3.0/lib/x86_64/:${ARCHITECTURE}/lib64/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../OpenBLAS/install/lib;






/usr/bin/make clean intgpu \
	      MACROS="-DSINGLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=16000" \
	      TYPE=Single UNROLL=4 > out1 2>&1

/usr/bin/make clean intgpu \
	      MACROS="-DDOUBLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=12000" \
	      TYPE=Double UNROLL=4 > out2 2>&1

/usr/bin/make clean intgpu \
	      MACROS="-DSINGLE_COMPLEX -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=12000" \
	      TYPE=SComplex UNROLL=4 > out3 2>&1

/usr/bin/make clean intgpu \
	      MACROS="-DDOUBLE_COMPLEX -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=9000" \
	      TYPE=DComplex UNROLL=4 > out4 2>&1


function execute30 { 

    for i in 1 5 10 15 20 25 30 
    do
	echo ${i} 0 1 2 3 
	echo ${i}000 0 1 2 3 1  | Executable/$1/int_gpu > $1-${i}-0-1-2-3.txt 2>&1
	grep GFLOPS  $1-${i}-0-1-2-3.txt 
    done
}


function execute20 { 


    for i in 1 5 10 15 20
    do
	echo ${i} 0 1 2 3 
	echo ${i}000 0 1 2 3 1  | Executable/$1/int_gpu > $1-${i}-0-1-2-3.txt 2>&1
	grep GFLOPS  $1-${i}-0-1-2-3.txt 
    done
}

function execute15 { 


    for i in 1 5 10 15
    do
	echo ${i} 0 1 2 3 
	echo ${i}000 0 1 2 3 1  | Executable/$1/int_gpu > $1-${i}-0-1-2-3.txt 2>&1
	grep GFLOPS  $1-${i}-0-1-2-3.txt 
    done
}


echo "Single"
execute30 Single SINGLE_PRECISION 
echo "Double"
execute20 Double DOUBLE_PRECISION 
echo "Single Complex"
execute20 SComplex SINGLE_COMPLEX 
echo "Double Complex"
execute15 DComplex DOUBLE_PRECISION 

