#!/bin/sh
export OMP_NUM_THREADS=4
export LD_LIBRARY_PATH=/home/paolo/Winograd/GotoBLAS


for M in  6001 6501  # 1601 2001 2601 3001 3501 4001 5001 
do
        
    for type in DComplex 
    do
	for e in winograd marco_pipe #ex3_pipe marco marco_2  marco_pipe_2     
	do
	    echo "0 0 1 1 1 $M $M $M $M" >> out.$type.$e
	    echo "0 0 1 1 1 $M $M $M $M 10" | ../Executable/$type/$e  >> out.$type.$e
	done;
    done;
    
done;

for M in  #2601 3001 3501 4001 5001 6001 7001 7501 8001
do
        
    for type in Double
    do
	for e in winograd ex3_pipe marco marco_2 marco_pipe marco_pipe_2     
	do
	    echo "0 0 1 1 1 $M $M $M $M" >> out.$type.$e
	    echo "0 0 1 1 1 $M $M $M $M" | ../Executable/$type/$e | grep MFLOPS >> out.$type.$e
	done;
    done;
    
done;




#/usr/bin/poweroff
