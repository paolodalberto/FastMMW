#!/bin/bash

#set -x
export ARCHITECTURE=/home/paolo/FastMM/rocBLAS/build/release/library/src/
export LD_LIBRARY_PATH=/opt/rocm/opencl/lib/x86_64/:${ARCHITECTURE}



function gpu {
    echo ${2} ROCM---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/ex3_gpurocm  | grep GFLOPS
}
function g7 {
    echo ${2} M7---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos7rocm | grep GFLOPS
}
function g23 {
    echo ${2} M23---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos23rocm | grep GFLOPS
}
function g49 {
    echo ${2} M49---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos49rocm | grep GFLOPS 
}
function g99 {
    echo ${2} M99---${5}-${3}-${4}
    echo "0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4"  | Executable/$1/gotos99rocm | grep GFLOPS 
}

function small_body_cp {
    
    g49 $1 $2 $3 $4 $5
    g23 $1 $2 $3 $4 $5
    g7 $1 $2 $3 $4 $5 
    

}



function execute42 { 
    for i in 17000  20000 22000 25000 28000 33000 35000 38000 40000 42000
    do
	small_body_cp $1 $i $2 $3 $4
    done
}

function execute33 { 
    for i in 17000  20000 22000 25000 28000 33000
    do
	small_body_cp $1 $i $2 $3 $4
    done
}


function execute42_gpu { 
    for i in 10000  #20000 22000 25000 28000 33000 35000 38000 40000 42000
    do
	gpu $1 $i $2 $3 $4
    done
}



#g7 Double 32000 0 3 0 

#exit 0

echo "Double"
#execute42_gpu Double   0 1 0
#execute42_gpu Double   1 2 0
#execute42_gpu Double   2 3 0
execute42 Double   0 1 0
#execute33 Double   1 3 0
#execute33 Double   0 3 0
echo "Single" 
#execute42_gpu Single 0 1 0
#execute42_gpu Single 1 2 0
#execute42_gpu Single 2 3 0
execute42 Single 0 1 0
#execute42 Single 1 3 0
#execute42 Single 0 3 0
echo "Half" 
#execute42_gpu Half 0 1 0
#execute42_gpu Half 1 2 0
#execute42_gpu Half 2 3 0
execute42 Half 0 1 0
#execute42 Half 1 3 0
#execute42 Half 0 3 0





