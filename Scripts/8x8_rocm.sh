#!/bin/bash

set -x

export ARC=Fiji
export ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0
export LD_LIBRARY_PATH=/opt/amdgpu-pro/lib/x86_64/:${ARCHITECTURE}/lib64/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../OpenBLAS/install/lib;
#export LD_LIBRARY_PATH=/opt/rocm/opencl/lib/x86_64/:/home/paolo/fusion/paolo/Desktop/MM/clBLAS/fijibuild/library/


function small_body_cp {
    echo ${2} M7---${5}-${3}-${4} 
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos7 | grep GFLOPS 
    echo ${2} M23--${5}-$3-$4
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos23 | grep GFLOPS 
    echo ${2} M49--${5}-$3-$4
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos49 | grep GFLOPS 
#    echo ${2} M99--$3-$4
#    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos99 | grep GFLOPS 
#    echo ${2} M343-$3-$4
#    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos343 | grep GFLOPS 
}

function small_body_single {
    echo ${2} M8S--${5}-${3}-${4} 
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $3 $4  | Executable/$1/ex3_gpu | grep GFLOPS
    echo ${2} M23--${5}-$3-$4
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $3 $4  | Executable/$1/winogradgpu | grep GFLOPS 
    echo ${2} M49--${5}-$3-$4
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/ex3_pipe_gpu | grep GFLOPS 
#    echo ${2} M99--$3-$4
#    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos99 | grep GFLOPS 
#    echo ${2} M343-$3-$4
#    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos343 | grep GFLOPS 
}

function small_body_p {
    echo ${2} M7---${3}-${4} 
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos7 
    echo ${2} M23--$3-$4
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos23 
    echo ${2} M49--$3-$4
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos49 
    echo ${2} M99--$3-$4
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos99 
#    echo ${2} M343-$3-$4
#    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos343 
}
function small_body_p23 {
    #echo ${2} M7---${3}-${4} 
    #echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos7 
    echo ${2} M23--$3-$4
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos23 
    #echo ${2} M49--$3-$4
    #echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos49 
    #echo ${2} M99--$3-$4
    #echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos99 
    #echo ${2} M343-$3-$4
    #echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $5 $3 $4  | Executable/$1/gotos343 
}

    



function small_execute30 { 

    for i in 17000  20000 22000 25000 28000 33000 35000 38000 42000 #44000 #45000 
    do
	small_body_cp $1 $i $2 $3 $4
    done
}


function small_execute20 { 


    for i in  13000 15000 18000 20000 25000 27000 30000 33000 #35000 #37000
    do
	small_body_cp $1 $i $2 $3 $4
    done
}

function small_execute15 { 


    for i in  10000 11000 13000 15000 18000 21000 21000 24000 #27000 #29000 #32000
    do
	small_body_cp $1 $i $2  $3 $4
    done
}



#echo "Double Complex"
small_execute15 DComplex 0 3 0
#small_execute15 DComplex 0 4 0



echo "Double"
#small_execute20 Double   0 1 0
small_execute20 Double   0 3 0


echo "Single Complex"
#small_execute20 SComplex 0 1 0
small_execute20 SComplex 0 3 0

#echo "Single" 
#small_execute30 Single   0 1 0
small_execute30 Single   0 3 0

