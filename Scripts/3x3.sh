#!/bin/bash

set -x

export ARC=Fiji
export ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0
export LD_LIBRARY_PATH=/opt/AMDAPPSDK-3.0/lib/x86_64/:${ARCHITECTURE}/lib64/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../OpenBLAS/install/lib;




#bash ./Scripts/buildgpu.sh




function body {
    echo ${2} 0 1
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  0 1  | Executable/$1/gotos23 | grep GFLOPS 
    echo ${2} 2 1
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  2 1  | Executable/$1/gotos23 | grep GFLOPS 
    echo ${2} 0 2
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  0 2  | Executable/$1/gotos23 | grep GFLOPS 
    echo ${2} 2 2  
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  2 2  | Executable/$1/gotos23 | grep GFLOPS 
    echo ${2} 0 4  
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  0 4  | Executable/$1/gotos23 | grep GFLOPS 
    echo ${2} W 0
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  0    | Executable/$1/winogradgpu | grep GFLOPS 
    echo ${2} W 2
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  2    | Executable/$1/winogradgpu | grep GFLOPS 
}


function execute30 { 

    for i in 3000 6000 12000 15000 21000 27000 35000 
    do
	body $1 $i
    done
}


function execute20 { 


    for i in 3000 6000 12000 15000 21000
    do
	body $1 $i
    done
}

function execute15 { 


    for i in 3000 6000 12000 15000 21000
    do
	body $1 $i
    done
}


function small_body {
    echo ${2} M23  0
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $3 1  | Executable/$1/gotos23 | grep GFLOPS 
    echo ${2} M99  0
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $3 1  | Executable/$1/gotos99 | grep GFLOPS 
    echo ${2} W7W  0
    echo 0 0 1 1 1 ${2} ${2} ${2} ${2}  $3    | Executable/$1/winogradgpu | grep GFLOPS 
}

    



function small_execute30 { 

    for i in 33000 35000 38000 42000 44000 45000 
    do
	small_body $1 $i $2
    done
}


function small_execute20 { 


    for i in  25500 27000 30000 33000 35000 37000
    do
	small_body $1 $i $2
    done
}

function small_execute15 { 


    for i in  18000 21000 24000 27000 30000 32000
    do
	small_body $1 $i $2 
    done
}





echo "Double"
small_execute20 Double   1
echo "Double Complex"
small_execute15 DComplex 1
echo "Single Complex"
small_execute20 SComplex  1
echo "Single" 
small_execute30 Single   1

