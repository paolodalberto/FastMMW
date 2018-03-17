#!/bin/bash
#set -x
 
export ARC=$1
#export ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0
#export LD_LIBRARY_PATH=/opt/AMDAPPSDK-3.0/lib/x86_64/:${ARCHITECTURE}/lib64/  


function execute2 {
    ./${ARC}/${ARC}-$1gemm  1  $2 $3  $4 $5      # single
    ./${ARC}/${ARC}-$1gemm  3  $2 $3  $4 $5      # single 
    ./${ARC}/${ARC}-$1gemm3 1  $2 $3  $4 $5 3    # 2 Fiji 
    ./${ARC}/${ARC}-$1gemm3 2  $2 $3  $4 $5 4    # Fiji + Hawaii
    ./${ARC}/${ARC}-$1gemm3 3  $2 $3  $4 $5 5    # 2 Hawaii

    ./${ARC}/${ARC}-$1gemm3 1  $2 $3  $4 $5 5  # 2Fiji + 2Hawaii 
    ./${ARC}/${ARC}-$1gemm3 1  $2 $3  $4 $5 4  # 2Fiji + 1Hawaii
    ./${ARC}/${ARC}-$1gemm3 2  $2 $3  $4 $5 5  # 1Fiji + 2Hawaii
    
#    ./${ARC}/${ARC}-$1gemm2 1  $2 $3  $4 $5 3  
#    ./${ARC}/${ARC}-$1gemm2 2  $2 $3  $4 $5 4  
#    ./${ARC}/${ARC}-$1gemm2 1  $2 $3  $4 $5 4  

#    if [ $2 -le 10000 ]
#    then
#	./${ARC}/${ARC}-$1gemm2 0  $2 $3  $4 $5 4  
#	./${ARC}/${ARC}-$1gemm2 0  $2 $3  $4 $5 3  
#	./${ARC}/${ARC}-$1gemm2 0  $2 $3  $4 $5 2  
#    fi
}


function execute {
    ./${ARC}-$1gemm  1  $2 $3  $4 $5      # single
    ./${ARC}-$1gemm  3  $2 $3  $4 $5      # single 
    ./${ARC}-$1gemm3 1  $2 $3  $4 $5 3    # 2 Fiji 
    ./${ARC}-$1gemm3 2  $2 $3  $4 $5 4    # Fiji + Hawaii
    ./${ARC}-$1gemm3 3  $2 $3  $4 $5 5    # 2 Hawaii
    ./${ARC}-$1gemm3 1  $2 $3  $4 $5 5  # 2Fiji + 2Hawaii 
    ./${ARC}-$1gemm3 1  $2 $3  $4 $5 4  # 2Fiji + 1Hawaii
    ./${ARC}-$1gemm3 2  $2 $3  $4 $5 5  # 1Fiji + 2Hawaii
    
#    ./${ARC}/${ARC}-$1gemm2 1  $2 $3  $4 $5 3  
#    ./${ARC}/${ARC}-$1gemm2 2  $2 $3  $4 $5 4  
#    ./${ARC}/${ARC}-$1gemm2 1  $2 $3  $4 $5 4  

#    if [ $2 -le 10000 ]
#    then
#	./${ARC}/${ARC}-$1gemm2 0  $2 $3  $4 $5 4  
#	./${ARC}/${ARC}-$1gemm2 0  $2 $3  $4 $5 3  
#	./${ARC}/${ARC}-$1gemm2 0  $2 $3  $4 $5 2  
#    fi
}




function execute {
    ./${ARC}-$1gemm  1 1  $2 $3  $4 $5      # single
}

export LD_LIBRARY_PATH=/opt/AMDAPPSDK-3.0/lib/x86_64/:/usr/local/lib64/



for i in #500 600 700 800 900 1000
do
    echo $i
    execute s $i $i $i  300   | grep FLOPS
done

for i in #1500 2000 3000 4000 5000 
do
    echo $i
    execute s $i $i $i  150   | grep FLOPS
done

for i in #6000 7000 8000 9000 
do
    echo $i
    execute s $i $i $i  5   | grep FLOPS
done

for i in #8000 9000 
do
    echo $i
    execute s $i $i $i  2   | grep FLOPS
done


for i in #10000 12000  14000  16000  18000 
do
    echo $i
    execute s $i $i $i  1   | grep FLOPS
done

for i in 16000 18000 
do
    echo $i
    execute s $i $i $i  1   | grep FLOPS
done

for i in #20000 21000 22000 23000 24000 26000 27000 28000 29000 30000 
do
    echo $i
    execute s $i $i $i  1   | grep FLOPS
done
