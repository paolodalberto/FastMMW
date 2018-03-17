gpu=$1

echo Single
for i in 5000 7500 10000 12500 15000 17500 20000
do
    echo $i
    bash Scripts/gpu.sh Executable/Single/ex3_gpu $gpu $i | grep GFLOPS
done
echo Double
for i in 2500 5000 7500 10000 12500 15000 17500 
do
    echo $i
    bash Scripts/gpu.sh Executable/Double/ex3_gpu $gpu $i | grep GFLOPS
done
echo SComplex
for i in 1000 2500 5000 7500 10000 12500 15000 17500
do
    echo $i
    bash Scripts/gpu.sh Executable/SComplex/ex3_gpu $gpu $i | grep GFLOPS
done
echo DComplex
for i in 1000 2500 5000 7500 10000 12500 15000
do
    echo $i
    bash Scripts/gpu.sh Executable/DComplex/ex3_gpu $gpu $i | grep GFLOPS
done
