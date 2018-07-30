
## Ellesmere  32000 25000 25000 17000
## Fiji       16000 12000 12000  9000


set -x 

for n in gotos23 gotos7 gotos49 gotos99 gotos343 intgpu  ex3gpu winograd3gpu ex3_pipe_gpu
do
    #echo /usr/bin/make clean add-gen ${n} MACROS="-DSINGLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=30000"   TYPE=Single UNROLL=2
    /usr/bin/make clean add-gen ${n} MACROS="-DHALF_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=40000"   TYPE=Half UNROLL=2 > out1 2>&1
    /usr/bin/make clean add-gen ${n} MACROS="-DSINGLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=30000"   TYPE=Single UNROLL=2 > out1 2>&1
    /usr/bin/make clean add-gen ${n} MACROS="-DDOUBLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=25000"   TYPE=Double UNROLL=2 > out2 2>&1
    /usr/bin/make clean add-gen ${n} MACROS="-DSINGLE_COMPLEX   -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=25000"   TYPE=SComplex UNROLL=8 > out3 2>&1
    /usr/bin/make clean add-gen ${n} MACROS="-DDOUBLE_COMPLEX   -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=17000"   TYPE=DComplex UNROLL=16 > out4 2>&1
done 


for n in #gotos49 gotos23 gotos7  gotos99 gotos343  winograd3gpu ex3_pipe_gpu #intgpu  ex3gpu
do
    #echo /usr/bin/make clean add-gen ${n} MACROS="-DSINGLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=30000"   TYPE=Single UNROLL=2
    /usr/bin/make clean add-gen ${n} MACROS="-DHALF_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=25000"   TYPE=Half UNROLL=2 > out1 2>&1
#    /usr/bin/make clean add-gen ${n} MACROS="-DSINGLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=16000"   TYPE=Single UNROLL=2 > out1 2>&1
#    /usr/bin/make clean add-gen ${n} MACROS="-DDOUBLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=12000"   TYPE=Double UNROLL=2 > out2 2>&1
#    /usr/bin/make clean add-gen ${n} MACROS="-DSINGLE_COMPLEX   -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=12000"   TYPE=SComplex UNROLL=8 > out3 2>&1
#    /usr/bin/make clean add-gen ${n} MACROS="-DDOUBLE_COMPLEX   -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=9000"   TYPE=DComplex UNROLL=16 > out4 2>&1
    
done 

#/usr/bin/make clean intgpu gotos23 ex3gpu winograd3gpu ex3_pipe_gpu\
#	      MACROS="-DSINGLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=16000" \
#	      TYPE=Single UNROLL=4 > out1 2>&1
 
#/usr/bin/make clean intgpu gotos23 ex3gpu winograd3gpu ex3_pipe_gpu\
#	      MACROS="-DDOUBLE_PRECISION -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=12000" \
#	      TYPE=Double UNROLL=4 > out2 2>&1
 
#/usr/bin/make clean intgpu gotos23 ex3gpu winograd3gpu ex3_pipe_gpu\
#	      MACROS="-DSINGLE_COMPLEX -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=12000" \
#	      TYPE=SComplex UNROLL=4 > out3 2>&1
 
#/usr/bin/make clean intgpu gotos23 ex3gpu winograd3gpu ex3_pipe_gpu\
#	      MACROS="-DDOUBLE_COMPLEX -DLIBRARY_PACKAGE -DAUTOMATIC -DLEAF=9000" \
#	      TYPE=DComplex UNROLL=4 > out4 2>&1
