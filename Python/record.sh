FINALDIR="./"

TIMES=10
#TIMES=100
          
for J in   21 42 50 64 70 86 90 100 120 150 175 200 250 300 350 400; 
#for J in  42
do
    for I in "[0,1]" "[-1,1]"; 
    do  
	#python /home/paolo/fusion/paolo/Desktop/MM/fmm/Python/distribution.py -i $TIMES -s $J -r "${I}" -m "I" -dAgg;  
	python ./distribution.py -i $TIMES -s $J -r "${I}" -m "I" -dagg;  
#	cp tmpheat.png ${FINALDIR}/HeatError${J}x${J}${TIMES}Times${I}Orthogonal.png; 
#	cp tmpheatM.png ${FINALDIR}/HeatMError${J}x${J}${TIMES}Times${I}Orthogonal.png; 
#	cp tmphist.png ${FINALDIR}/HistogramError${J}x${J}${TIMES}Times${I}Orthogonal.png; 
#	cp tmptime.png ${FINALDIR}/TimeError${J}x${J}${TIMES}Times${I}Orthogonal.png; 
    done  
done