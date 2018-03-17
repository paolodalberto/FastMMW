#!/bin/sh
#export OMP_NUM_THREADS=4
export LD_LIBRARY_PATH=../../GotoBLAS2

echo "Single"
for M in  3400 3500 3600 3700 
do
    for type in Single 
    do
	for e in gotos atlas winograd winogradatlas
	do
	    echo "0 0 1 1 1 $M $M $M $M" #>> out.$type.$e
	    echo "0 0 1 1 1 $M $M $M $M" | ../Executable/$type/$e | grep MFLOPS #>> out.$type.$e
	done;
    done;
done;    

echo "Double"
for M in  2900 3000 3100
do
    for type in Double
    do
	for e in gotos atlas winograd winogradatlas
	do
	    echo "0 0 1 1 1 $M $M $M $M" #>> out.$type.$e
	    echo "0 0 1 1 1 $M $M $M $M" | ../Executable/$type/$e | grep MFLOPS #>> out.$type.$e
	done;
    done;
done;    

echo "SComplex"
for M in  2000 3000 4000 5000 6000 
do
    for type in SComplex
    do
	for e in gotos atlas winograd winogradatlas
	do
	    echo "0 0 1 1 1 $M $M $M $M" #>> out.$type.$e
	    echo "0 0 1 1 1 $M $M $M $M" | ../Executable/$type/$e | grep MFLOPS #>> out.$type.$e
	done;
    done;
done;    

echo "DComplex"
for M in  1300 1400 1500 1600 1700 
do
    for type in DComplex
    do
	for e in gotos atlas winograd winogradatlas
	do
	    echo "0 0 1 1 1 $M $M $M $M" #>> out.$type.$e
	    echo "0 0 1 1 1 $M $M $M $M" | ../Executable/$type/$e | grep MFLOPS #>> out.$type.$e
	done;
    done;
done;    
    


#/sbin/poweroff
