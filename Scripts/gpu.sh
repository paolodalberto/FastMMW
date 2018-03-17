Exec=$1
gpu=$2
i=$3

export ARC=Fiji
export ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0
export LD_LIBRARY_PATH=/opt/AMDAPPSDK-3.0/lib/x86_64/:${ARCHITECTURE}/lib64/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/paolo/fusion/paolo/Desktop/MM/Epyc/OpenBLAS/install/lib



echo $i; echo "0 0 1 1 1 ${i} ${i} ${i} ${i} ${gpu}" |  ${Exec} 

	 
