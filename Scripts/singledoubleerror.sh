

#!/bin/sh
export OMP_NUM_THREADS=2

for M in  4001 
do
    for type in  DComplex
    do
	for e in exerrGoto
	do
	    echo "$M $M $M 0" >> out.$type.$e
	    echo "$M $M $M 1" | ../Executable/$type/$e >> out.$type.$e.1
	done;
    done;
    
done;
for M in  5001  6001 7001 
do
    for type in Single Double SComplex DComplex
    do
	for e in exerrGoto
	do
	    echo "$M $M $M 0" >> out.$type.$e
	    echo "$M $M $M 0" | ../Executable/$type/$e >> out.$type.$e.0
	    echo "$M $M $M 1" | ../Executable/$type/$e >> out.$type.$e.1
	done;
    done;
    
done;


/usr/bin/poweroff
