#!/bin/bash

#set -x

export ARC=Fiji
export ARCHITECTURE=../../CLBlast/rocm
export LD_LIBRARY_PATH=/opt/rocm/opencl/lib/x86_64/:${ARCHITECTURE}
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




function execute45 { 

    for i in 25000 28000  30000 35000 38000 40000 43000 45000 
    do
	small_body_cp $1 $i $2 $3 $4
    done
}




function execute40 { 

    for i in 17000  20000 22000 25000 28000 33000 35000 38000 40000 
    do
	small_body_cp $1 $i $2 $3 $4
    done
}

function execute40_x { 

    for i in 40000 
    do
	small_body_cp $1 $i $2 $3 $4
    done
}


function execute30 { 


    for i in  13000 15000 18000 20000 25000 27000 30000 
    do
	small_body_cp $1 $i $2 $3 $4
    done
}

function execute24 { 


    for i in  10000 11000 13000 15000 18000 21000 24000 
    do
	small_body_cp $1 $i $2  $3 $4
    done
}
function execute21 { 


    for i in  10000 11000 13000 15000 18000 21000 
    do
	small_body_cp $1 $i $2  $3 $4
    done
}

function execute21_2 { 


    for i in  21000 
    do
	small_body_cp $1 $i $2  $3 $4
    done
}


echo "Half" 
execute40 Half   0 2 0
execute40 Half   2 4 0
execute40 Half   0 4 0


echo "Single" 
execute40 Single   0 2 0
execute40 Single   2 4 0
execute40 Single   0 4 0




echo "Double Complex"
execute21 DComplex 0 2 0
execute21 DComplex 2 4 0
execute21 DComplex 0 4 0




echo "Double"
execute30 Double   0 2 0
execute30 Double   2 4 0
execute30 Double   0 4 0



echo "Single Complex"
execute30 SComplex 0 2 0
execute30 SComplex 2 4 0
execute30 SComplex 0 4 0



