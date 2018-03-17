#!/bin/bash

echo "0 0 1 1 1 3000 3000 3000 3000" | Executable/strassenatlas > out1.txt 
cat /dev/null > out2.txt #echo "0 0 1 1 1 3000 3000 3000 3000" | Executable/strassenatlas > out2.txt 
echo "0 0 1 1 1 3000 3000 3000 3000" | Executable/strassen > out3.txt 
cat /dev/null > out4.txt #echo "0 0 1 1 1 3000 3000 3000 3000" | Executable/strassen > out4.txt 
tail -n 1 out*