


#!/bin/bash

#set -x

export ARC=Fiji
export ARCHITECTURE=../../CLBlast/rocm
export LD_LIBRARY_PATH=/opt/rocm/opencl/lib/x86_64/:${ARCHITECTURE}
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../OpenBLAS/install/lib;
#export LD_LIBRARY_PATH=/opt/rocm/opencl/lib/x86_64/:/home/paolo/fusion/paolo/Desktop/MM/clBLAS/fijibuild/library/


function g7 {
    echo ${2} M7---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos7 | grep GFLOPS
}
function g23 {
    echo ${2} M23---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos23 | grep GFLOPS
}
function g49 {
    echo ${2} M49---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos49 | grep GFLOPS 
}
function g99 {
    echo ${2} M99---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos99 | grep GFLOPS 
}
function g343 {
    echo ${2} M434---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos343 | grep GFLOPS 
}

function small_body_cp {

    g7 $1 $2 $3 $4 $5 
    g23 $1 $2 $3 $4 $5 
    g49 $1 $2 $3 $4 $5
#    g99 $1 $2 $3 $4 $5
#    g343 $1 $2 $3 $4 $5

}


function small_rocm {

    ./build/release/clients/staging/rocblas-bench -f gemm -r $1 -m $2  -n $2 -k $2   --device $3 -i 2 | grep "N,N"
} 

function execute { 
    for i in 17000  20000 22000 25000 28000 33000 35000 38000 40000 42000
    do
	small_body_cp $1 $i $2 $3 $4
    done
}
function execute42 { 
    for i in 17000  20000 22000 25000 28000 33000 35000 38000 40000 42000
    do
	small_body_cp $1 $i $2 $3 $4
    done
}


function execute31 { 
    for i in  13000 15000 18000 20000 25000 28000 31000
    do
	small_body_cp $1 $i $2 $3 $4
    done
}


echo "Double Complex"
#execute31 DComplex 0 2 0
#execute31 DComplex 2 4 0
execute31 DComplex 0 3 0
echo "Double"
#execute42 Double   0 2 0
#execute42 Double   2 4 0
execute42 Double   0 3 0
echo "Single Complex"
#execute42 SComplex 0 2 0
#execute42 SComplex 2 4 0
execute42 SComplex 0 3 0
echo "Single" 
#execute42 Single   0 2 0
#execute42 Single   2 4 0
execute42 Single 0 3 0
echo "Half" 
#execute40 Half   0 2 0
#execute40 Half   2 4 0
execute42 Half 0 3 0
















