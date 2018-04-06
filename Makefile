##################################################################
#
# Makefile 
#
# BLAS functionalities C = aC + b op(A)op(B)
# 
# 
#
#
#

# Code root directory 
D = $(PWD)/../
#D = $(HOME)/Winograd
HOMEDIR= $(D)/FastMMW

# ATLAS location 
#ATLAS= $(D)/ATLAS_3_9_9/build/
ATLAS= $(D)/ATLAS/install

# GotoBLAS location 
GOTO_BLAS= $(D)/OpenBLAS/install/lib


# MKL BLAS
MKL_BLAS= $(D)/MKL/10.0.5.025/lib/64


## C and FORTAN compilers. I use gcc but you may change it. 
CC  = gcc
FF  = gfortran
AR = ar rcs


## Machine Specific optimizations 
#OPT =   $(EXTRA) $(MACROS)   -g  #-std=gnu99 -fPIC -O2  -Wall -msse3       # -m64
OPT =   $(EXTRA) $(MACROS)  -O1 -g #-fPIC -msse2 -msse4 -m64  #-mtune=zen #-m64 -march=opteron -mtune=opteron -m64   #     # -m64

#ARCHITECTUREGPU=/usr/local
#ARC=Fiji
#ARCHITECTUREGPU= /home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0

ARCHITECTUREGPU= $(D)/CLBlast/

# Includes
INC = -I $(HOMEDIR) -I $(ATLAS)/include -I $(HOMEDIR)/Add -I $(HOMEDIR)/Mul \
	-I $(HOMEDIR)/Matrices -I $(HOMEDIR)/Sort -I $(HOMEDIR)/Scaling \
	-I $(HOMEDIR)/PThread -I $(HOMEDIR)/Error \
	-I $(ARCHITECTUREGPU)/include -I $(HOMEDIR)/GPU \
	-I /opt/rocm/opencl/include/ 


## Specific directory for ATLAS and GotoBLAS Library

ALIB = -L $(ATLAS)/lib/ 
GLIB = -L $(GOTO_BLAS) 
MKLLIB = -L ${MKL_BLAS}
##CLLIBS = -L /opt/amdgpu-pro/lib/x86_64-linux-gnu/  -L $(ARCHITECTUREGPU)/lib64/ #-L /opt/AMDAPPSDK-3.0/lib/x86_64/

#CLLIBS =   -L /home/paolo/fusion/paolo/Desktop/MM/clBLAS/fijibuild/library -L /opt/rocm/opencl/lib/x86_64/
CLLIBS =   -L $(ARCHITECTUREGPU)/build/   -L /opt/amdgpu-pro/lib/x86_64-linux-gnu/ # /opt/rocm/opencl/lib/x86_64/ # #

FPGALIBS = -L /home/prj47-rack-31/gemx/fcn/out_hw/xbinst/runtime/lib/x86_64 \
	-L /home/prj47-rack-31/gemx/lib  \
	-L$(ARCHITECTUREGPU)/build/ \
	-L /opt/amdgpu-pro/lib/x86_64-linux-gnu/


opencllibs =  -l OpenCL -l clBLAS -lpthread
opencllibs =  -l OpenCL -l clblast -lpthread

fpgalibs =  -l gemxhost -lpthread -l clblast -l xilinxopencl -l OpenCL


## Libraries 
atlaslib =-llapack  -lptcblas   -latlas -lm  -lpthread #-lptf77blas -lcblas -lpthread -lf77blas
#atlaslib =-llapack  -lcblas  -latlas -lm   -lpthread -lf77blas
gotolib =  -lopenblas -lpthread  -lm #-lefence
mklblas = -lmkl
math = -lm 

FASTLIBDIR = -L $(HOMEDIR)/lib 
FASTLIBS= -lsfastmm -ldfastmm -lscfastmm -ldcfastmm

EXTRA = $(EXTRA_GOTO)  $(EXTRA_ATLAS)


#################################################################################
#################################################################################
#  
#  Below this point you should not need to modify anything :)
#
#
#
#
#################################################################################
#################################################################################


## Default rule to build the object files
#$(CC) -E  $(OPT)  $(INC) $< -o $@.c
.c.o:
	$(CC) -c  $(OPT) $(INC) $< -o $@




code:
	make clean clean_lib
	tar zcvf fmm.tar.gz  ../fmm/Makefile ../fmm/Add/*.c ../fmm/Add/*.h  \
	../fmm/Mul/*.c ../fmm/Mul/*.h   ../fmm/Matrices/*.h  \
	../fmm/Sort/*.c ../fmm/Sort/*.h  ../fmm/Scaling/*.c ../fmm/Scaling/*.h  \
	../fmm/PThread/*.c  ../fmm/PThread/*.h  \
	../fmm/Error/*.c ../fmm/Error/*.h  ../fmm/MAT-ADD-Generator \
	../fmm/Examples/*.c ../fmm/Examples/*.h   ../fmm/Mixed/*.c  ../fmm/Mixed/*.h ../fmm/COPYING.LESSER ../fmm/INSTALL.txt \
	 ../fmm/Scripts ../fmm/lib ../fmm/R/FastMMWR ../fmm/Python ../fmm/GPU



## defaults object files

obj = PThread/pt.o Add/mat-addkernels.o Mul/mat-mulkernels.o Scaling/scaling.o 
objgpu = PThread/pt.o Add/mat-addkernels.o Mul/mat-mulkernels.o Scaling/scaling.o GPU/dgemm_multigraphic.o GPU/platform.o  Mul/mat-s3x3x3_23_JinsooOh_20131108a.o
objfpga = ${objgpu} FPGA/fpga.o
obj2 = $(obj) Error/doubly_compensated_sumc.o Sort/quicksort.o 

UNROLL = 8

add-gen: 
	$(HOMEDIR)/MAT-ADD-Generator/addgen $(UNROLL) > $(HOMEDIR)/Add/mat-addkernels.h
	ls 

all: ex2 ex3 ex4

lib-goto: clean_lib
	make lib EXTRA_GOTO=-DGOTO_BLAS

lib-atlas: clean_lib
	make lib EXTRA_ATLAS=-DATLAS

lib     : clean
	MAT-ADD-Generator/addgen $(UNROLL) > Add/mat-addkernels.h
	make clean doublelib
	MAT-ADD-Generator/addgen $(UNROLL) > Add/mat-addkernels.h
	make clean singlelib
	MAT-ADD-Generator/addgen $(UNROLL) > Add/mat-addkernels.h
	make clean scomplexlib
	MAT-ADD-Generator/addgen $(UNROLL) > Add/mat-addkernels.h
	make clean dcomplexlib


singlelib: MACROS = -DSINGLE_PRECISION -DLIBRARY_PACKAGE
singlelib: UNROLL = 32 	
singlelib: $(obj2)
	$(AR) $(HOMEDIR)/lib/libsfastmm.a $(obj2)

doublelib: MACROS = -DDOUBLE_PRECISION -DLIBRARY_PACKAGE
doublelib: $(obj2)
	$(AR) $(HOMEDIR)/lib/libdfastmm.a $(obj2)

scomplexlib: MACROS = -DSINGLE_COMPLEX -DLIBRARY_PACKAGE
scomplexlib: $(obj2)
	$(AR) $(HOMEDIR)/lib/libscfastmm.a $(obj2)

dcomplexlib: MACROS = -DDOUBLE_COMPLEX -DLIBRARY_PACKAGE
dcomplexlib: $(obj2)
	$(AR) $(HOMEDIR)/lib/libdcfastmm.a $(obj2)

sumerrorall: 
	make clean summerrorsingle 
	make clean summerrordouble 
	make clean summerrorscomplex 
	make clean summerrordcomplex

summerrorsingle:  MACROS = -DSINGLE_PRECISION -DLIBRARY_PACKAGE
summerrorsingle:  TYPE = Single
summerrorsingle:  DEST = $(HOMEDIR)/Executable/$(TYPE)/error
summerrorsingle:  FASTLIBS= -lsfastmm 
summerrorsingle: sumerror

summerrordouble:  MACROS = -DDOUBLE_PRECISION -DLIBRARY_PACKAGE
summerrordouble:  TYPE = Double
summerrordouble:  DEST = $(HOMEDIR)/Executable/$(TYPE)/error
summerrordouble:  FASTLIBS= -ldfastmm 
summerrordouble:sumerror
summerrorscomplex:  MACROS = -DSINGLE_COMPLEX -DLIBRARY_PACKAGE
summerrorscomplex:  TYPE = SComplex
summerrorscomplex:  DEST =  $(HOMEDIR)/Executable/$(TYPE)/error
summerrorscomplex:  FASTLIBS= -lscfastmm 
summerrorscomplex:sumerror
summerrordcomplex:  MACROS = -DDOUBLE_COMPLEX -DLIBRARY_PACKAGE
summerrordcomplex:  TYPE = DComplex
summerrordcomplex:  DEST = $(HOMEDIR)/Executable/$(TYPE)/error
summerrordcomplex:  FASTLIBS= -ldcfastmm 
summerrordcomplex: sumerror

sumerror: Examples/error.o 
	$(FF) $(OPT) $(INC)  Examples/error.o -o $(DEST) $(GLIB) $(gotolib)  -lm  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

mixed: MACROS = -DAPPLICATION -DGOTO_BLAS
mixed: INC+=-I $(HOMEDIR)/Mixed
mixed: Examples/example.mix.3.o Mixed/mixed_precision.o
	$(FF) $(OPT) $(INC)  Examples/example.mix.3.o Mixed/mixed_precision.o -o Executable/mixed $(GLIB) $(gotolib)  -lm  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

mixed-error: MACROS = -DAPPLICATION -DGOTO_BLAS
mixed-error: INC+=-I $(HOMEDIR)/Mixed
mixed-error: Examples/example.mix.error.o Mixed/mixed_precision.o
	$(FF) $(OPT) $(INC)  Examples/example.mix.error.o Mixed/mixed_precision.o -o Executable/mixed-error $(GLIB) $(gotolib)  -lm  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

mixed-error-complex: MACROS = -DAPPLICATION -DGOTO_BLAS
mixed-error-complex: INC+=-I $(HOMEDIR)/Mixed
mixed-error-complex: Examples/example.mix.error.complex.o Mixed/mixed_precision.o
	$(FF) $(OPT) $(INC)  Examples/example.mix.error.complex.o Mixed/mixed_precision.o -o Executable/mixed-error-complex $(GLIB) $(gotolib)  -lm  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

mixed-atlas: MACROS = -DAPPLICATION -DATLAS
mixed-atlas: INC+=-I $(HOMEDIR)/Mixed
mixed-atlas: Examples/example.mix.3.o Mixed/mixed_precision.o
	$(CC) $(OPT) $(INC)  Examples/example.mix.3.o Mixed/mixed_precision.o -o Executable/mixed-atlas  -lm  $(FASTLIBDIR) $(FASTLIBS) $(ALIB) $(atlaslib)

mixed-error-atlas: MACROS = -DAPPLICATION -DATLAS
mixed-error-atlas: INC+=-I $(HOMEDIR)/Mixed
mixed-error-atlas: Examples/example.mix.error.o Mixed/mixed_precision.o
	$(CC) $(OPT) $(INC)  Examples/example.mix.error.o Mixed/mixed_precision.o -o Executable/mixed-error-atlas  -lm  $(FASTLIBDIR) $(FASTLIBS) $(ALIB) $(atlaslib)

mixed-error-complex-atlas: MACROS = -DAPPLICATION -DATLAS
mixed-error-complex-atlas: INC+=-I $(HOMEDIR)/Mixed
mixed-error-complex-atlas: Examples/example.mix.error.complex.o Mixed/mixed_precision.o
	$(CC) $(OPT) $(INC)  Examples/example.mix.error.complex.o Mixed/mixed_precision.o -o Executable/mixed-error-complex-atlas  -lm  $(FASTLIBDIR) $(FASTLIBS) $(ALIB) $(atlaslib)


########################################################################################
########################################################################################

# for the analysis and testing of each examples
#
# Define the MACROS 
#MACROS = -DSINGLE_PRECISION# Single precision methods  
#MACROS = -DDOUBLE_PRECISION # Double precision methods  
#MACROS = -DSINGLE_COMPLEX # Single Complex   methods 
#MACROS = -DDOUBLE_COMPLEX # Double Complex   methods 


#TYPE=Single# Single precision types
#TYPE=Double# Double precision types
#TYPE=SComplex# Single Complex   types
#TYPE=DComplex# Double Complex   types


## Example 2 is used to check whether or not an MM algorithm implementation is correct 
ex2: TYPE=Single
ex2: MACROS+=-DLIBRARY_PACKAGE -DPERMUTATION -DSINGLE_PRECISION  -DGOTO_BLAS #-DMARCO_PIPE_TEST=1 #-DDCMUL_TEST 
ex2: $(obj2)
	$(CC) -c $(OPT)  $(INC) Examples/example.2.c -o Examples/example.2.o
	$(FF) $(OPT) $(INC) Examples/example.2.o $(obj2) -o Executable/$(TYPE)/ex2  $(GLIB) $(gotolib)  #-lefence   #$(ALIB) $(atlaslib) #



## Example 5 is used to check whether or not an matrix addition algorithm implementation is correct 

ex5: Examples/example.5.o $(obj)
	$(FF) $(OPT) $(INC) Examples/example.5.o $(obj) -o Executable/$(TYPE)/ex5  $(GLIB) $(gotolib) #-lefence #$(ALIB) $(atlaslib) #



## Example.err.1 is used to measure quantitatively the error analysis for all this MMs based on Priest's algorithm 
exerr2: Examples/example.err.1.o $(obj2)
	$(FF) $(OPT) $(INC)  Examples/example.err.1.o $(obj2) -o Executable/$(TYPE)/exerrGoto $(GLIB) $(gotolib)  -lm #$(ALIB) $(atlaslib)  
exerr3: Examples/example.err.1.o $(obj2)
	$(FF) $(OPT) $(INC)  Examples/example.err.1.o $(obj2) -o Executable/$(TYPE)/exerrATLAS   -lm $(ALIB) $(atlaslib)  



## Example 3 is the core for performance evaluation
## It can be used to generate executable for Goto's, ATLAS, W-Goto, W-ATLAS




ex3gpu:	EXTRA_GOTO=-DCLBLAS 
ex3gpu: MACROS+=-DLIBRARY_PACKAGE
ex3gpu: $(objgpu) 
	$(CC) -c $(OPT) -DGOTOS_TEST=1 $(INC) $(INCCL) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(objgpu)  -o Executable/$(TYPE)/ex3_gpu  \
	$(math)  $(CLLIBS) $(opencllibs) #$(ALIB) $(atlaslib)

intgpu:	EXTRA_GOTO=-DCLBLAS 
intgpu: MACROS+=-DLIBRARY_PACKAGE
intgpu: $(objgpu) 
	$(CC) -c $(OPT) -DGOTOS_TEST=1 $(INC) $(INCCL) Examples/interpreter.c -o Examples/interpreter.o
	$(FF) $(OPT) $(INC) Examples/interpreter.o $(objgpu)  -o Executable/$(TYPE)/int_gpu  \
	$(math)  $(CLLIBS) $(opencllibs) #$(ALIB) $(atlaslib)



ex3:	EXTRA_GOTO=-DGOTO_BLAS 
ex3:    MACROS+=-DLIBRARY_PACKAGE
ex3:    $(obj)
	$(CC) -c $(OPT) -DALPHA=1  -DGOTOS_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(obj)  -o Executable/$(TYPE)/ex3_g  $(math) $(GLIB) $(gotolib)  #$(ALIB) $(atlaslib)

ex3_pipe:EXTRA_GOTO=-DGOTO_BLAS 
ex3_pipe:MACROS+=-DLIBRARY_PACKAGE
ex3_pipe: $(obj)
	$(CC) -c $(OPT)   -DWM_PIPE_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(obj)  -o Executable/$(TYPE)/ex3_pipe  $(math) $(GLIB) $(gotolib)  #$(ALIB) $(atlaslib)

marco_pipe:  EXTRA_GOTO=-DGOTO_BLAS 
marco_pipe:  MACROS+=-DLIBRARY_PACKAGE
marco_pipe:  $(obj)
	$(CC) -c $(OPT)   -DMARCO_PIPE_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(obj)  -o Executable/$(TYPE)/marco_pipe  $(math) $(GLIB) $(gotolib)  #$(ALIB) $(atlaslib)

marco_pipe_2:  EXTRA_GOTO=-DGOTO_BLAS 
marco_pipe_2:  MACROS+=-DLIBRARY_PACKAGE
marco_pipe_2:  $(obj)
	$(CC) -c $(OPT)   -DMARCO_PIPE_TEST_2=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(obj)  -o Executable/$(TYPE)/marco_pipe_2  $(math) $(GLIB) $(gotolib)  #$(ALIB) $(atlaslib)

ex3_spipe:  EXTRA_GOTO=-DGOTO_BLAS 
ex3_spipe:  MACROS+=-DLIBRARY_PACKAGE
ex3_spipe:  $(obj)
	$(CC) -c $(OPT)   -DSM_PIPE_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(obj)  -o Executable/$(TYPE)/ex3_spipe  $(math) $(GLIB) $(gotolib)  #$(ALIB) $(atlaslib)


gotos3: EXTRA_GOTO=-DGOTO_BLAS 
gotos3: MACROS+=-DLIBRARY_PACKAGE
gotos3:$(obj)
	$(CC) -c $(OPT) -DGOTOS_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/gotos $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

gotos23: EXTRA_GOTO=-DCLBLAS
gotos23: MACROS+=-DLIBRARY_PACKAGE
gotos23:$(objgpu)
	$(CC) -c $(OPT) -DM23_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(objgpu) -o Executable/$(TYPE)/gotos23 $(math)  $(CLLIBS) $(opencllibs) #$(ALIB) $(atlaslib) #$(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

gotos7: EXTRA_GOTO=-DCLBLAS
gotos7: MACROS+=-DLIBRARY_PACKAGE
gotos7:$(objgpu)
	$(CC) -c $(OPT) -DM7_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(objgpu) -o Executable/$(TYPE)/gotos7 $(math)  $(CLLIBS) $(opencllibs) #$(ALIB) $(atlaslib) #$(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

gotos7p: EXTRA_GOTO=-DFPGA -DCLBLAS 
gotos7p: MACROS+=-DLIBRARY_PACKAGE
gotos7p:$(objfpga)
	$(CC) -c $(OPT) -DM7_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(objfpga) -o Executable/$(TYPE)/gotos7p $(math)  $(FPGALIBS) $(fpgalibs) 


gotos49: EXTRA_GOTO=-DCLBLAS
gotos49: MACROS+=-DLIBRARY_PACKAGE
gotos49:$(objgpu)
	$(CC) -c $(OPT) -DM49_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(objgpu) -o Executable/$(TYPE)/gotos49 $(math)  $(CLLIBS) $(opencllibs) #$(ALIB) $(atlaslib) #$(GLIB) $(gotolib) #$(ALIB) $(atlaslib)


gotos99: EXTRA_GOTO=-DCLBLAS
gotos99: MACROS+=-DLIBRARY_PACKAGE
gotos99:$(objgpu)
	$(CC) -c $(OPT) -DM99_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(objgpu) -o Executable/$(TYPE)/gotos99 $(math)  $(CLLIBS) $(opencllibs) #$(ALIB) $(atlaslib) #$(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

gotos343: EXTRA_GOTO=-DCLBLAS
gotos343: MACROS+=-DLIBRARY_PACKAGE
gotos343:$(objgpu)
	$(CC) -c $(OPT) -DM343_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(objgpu) -o Executable/$(TYPE)/gotos343 $(math)  $(CLLIBS) $(opencllibs) #$(ALIB) $(atlaslib) #$(GLIB) $(gotolib) #$(ALIB) $(atlaslib)



marco3:EXTRA_GOTO=-DGOTO_BLAS 
marco3:MACROS+=-DLIBRARY_PACKAGE
marco3:$(obj)
	$(CC) -c $(OPT) -DMARCO_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/marco $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

marco3_old:EXTRA_GOTO=-DGOTO_BLAS 
marco3_old:MACROS+=-DLIBRARY_PACKAGE
marco3_old:$(obj)
	$(CC) -c $(OPT) -DMARCO_TEST_2=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/marco_2 $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

rmul:EXTRA_GOTO=-DGOTO_BLAS 
rmul:MACROS+=-DLIBRARY_PACKAGE
rmul:$(obj)
	$(CC) -c $(OPT) -DRMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/rmul $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

adaptive:EXTRA_GOTO=-DGOTO_BLAS
adaptive:MACROS+=-DLIBRARY_PACKAGE 
adaptive:$(obj)
	$(CC) -c $(OPT) -DGOTOS_TEST=1  -DADAPTIVE=1 -DALPHA=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/adaptive $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

mkl3:$(obj)
	$(CC) -c $(OPT) -DGOTOS_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/gotos $(MKLLIB) $(mklblas) #$(ALIB) $(atlaslib)


strassen3:EXTRA_GOTO=-DGOTO_BLAS 
strassen3:MACROS+=-DLIBRARY_PACKAGE
strassen3:$(obj)
	$(CC) -c $(OPT) -DSMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/strassen $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

winograd3:EXTRA_GOTO=-DGOTO_BLAS 
winograd3:MACROS+=-DLIBRARY_PACKAGE
winograd3:$(obj)
	$(CC) -c $(OPT) -DWMUL_OPT_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/winograd $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

winograd3gpu:EXTRA_GOTO=-DCLBLAS 
winograd3gpu:MACROS+=-DLIBRARY_PACKAGE
winograd3gpu:$(objgpu)
	$(CC) -c $(OPT) -DWMUL_OPT_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(objgpu) -o Executable/$(TYPE)/winogradgpu $(CLLIBS) $(opencllibs) #$(ALIB) $(atlaslib)

ex3_pipe_gpu:EXTRA_GOTO=-DCLBLAS 
ex3_pipe_gpu:MACROS+=-DLIBRARY_PACKAGE
ex3_pipe_gpu: $(objgpu)
	$(CC) -c $(OPT)   -DWM_PIPE_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(objgpu)  -o Executable/$(TYPE)/ex3_pipe_gpu  $(math) $(CLLIBS) $(opencllibs)   #$(ALIB) $(atlaslib)


ostrassen3:EXTRA_GOTO=-DGOTO_BLAS 
ostrassen3:MACROS+=-DLIBRARY_PACKAGE
ostrassen3:$(obj)
	$(CC) -c $(OPT) -DOMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/ostrassen $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

owinograd3::EXTRA_GOTO=-DGOTO_BLAS 
owinograd3:MACROS+=-DLIBRARY_PACKAGE
owinograd3:$(obj)
	$(CC) -c $(OPT) -DOWMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/owinograd $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

strassen3atlas:EXTRA_ATLAS=-DATLAS
strassen3atlas:MACROS+=-DLIBRARY_PACKAGE
strassen3atlas:$(obj)
	$(CC) -c $(OPT) -DSMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/strassenatlas $(ALIB) $(atlaslib)

winograd3atlas:EXTRA_ATLAS=-DATLAS
winograd3atlas:MACROS+=-DLIBRARY_PACKAGE
winograd3atlas:$(obj)
	$(CC) -c $(OPT) -DWMUL_OPT_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/winogradatlas $(ALIB) $(atlaslib)

winograd3atlaspipe:EXTRA_ATLAS=-DATLAS
winograd3atlaspipe:MACROS+=-DLIBRARY_PACKAGE
winograd3atlaspipe:$(obj)
	$(CC) -c $(OPT) -DWM_PIPE_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/winogradatlas_pipe $(ALIB) $(atlaslib)

marcoatlas_pipe:EXTRA_ATLAS=-DATLAS
marcoatlas_pipe:MACROS+=-DLIBRARY_PACKAGE
marcoatlas_pipe:$(obj)
	$(CC) -c $(OPT) -DMARCO_PIPE_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/marcoatlas_pipe $(ALIB) $(atlaslib)

marcoatlas_pipe_2:EXTRA_ATLAS=-DATLAS
marcoatlas_pipe_2:MACROS+=-DLIBRARY_PACKAGE
marcoatlas_pipe_2:$(obj)
	$(CC) -c $(OPT) -DMARCO_PIPE_TEST_2=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/marcoatlas_pipe $(ALIB) $(atlaslib)

ostrassen3atlas:EXTRA_ATLAS=-DATLAS
ostrassen3atlas:MACROS+=-DLIBRARY_PACKAGE
ostrassen3atlas:$(obj)
	$(CC) -c $(OPT) -DOMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC)  Examples/example.3.o $(obj) -o Executable/$(TYPE)/ostrassenatlas $(ALIB) $(atlaslib)

owinograd3atlas:EXTRA_ATLAS=-DATLAS
owinograd3atlas:MACROS+=-DLIBRARY_PACKAGE
owinograd3atlas:$(obj)
	$(CC) -c $(OPT) -DOWMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC) Examples/example.3.o $(obj) -o Executable/$(TYPE)/owinogradatlas $(ALIB) $(atlaslib)

ex2atlas: EXTRA_GOTO= -DATLAS
ex2atlas: MACROS+=-DLIBRARY_PACKAGE -DMARCO_PIPE_TEST=1 #-DDCMUL_TEST 
ex2atlas: $(obj2)
	$(CC) -c $(OPT)  $(INC) Examples/example.2.c -o Examples/example.2.o
	$(FF) $(OPT) $(INC) Examples/example.2.o $(obj2) -o Executable/$(TYPE)/ex2atlas  $(ALIB) $(atlaslib) #

ex3atlas: EXTRA_GOTO=-DATLAS 
ex3atlas: MACROS+=-DLIBRARY_PACKAGE
ex3atlas: $(obj)
	$(CC) -c $(OPT) -DALPHA=1  -DGOTOS_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(obj)  -o Executable/$(TYPE)/ex3atlas_g  $(ALIB) $(atlaslib)

ex3_atlas: EXTRA_ATLAS=-DATLAS
ex3_atlas: MACROS+=-DLIBRARY_PACKAGE
ex3_atlas:  $(obj)
	$(CC) -c $(OPT) -DGOTOS_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC) Examples/example.3.o $(obj)  -o Executable/$(TYPE)/atlas  $(ALIB) $(atlaslib) 

ex3_gotos_all:
	#MAT-ADD-Generator/addgen 4 > Add/mat-addkernels.h	
	make ex2
	make ex3
	make ex3_pipe
	make gotos3
	make marco3
	make marco3_old
	make marco_pipe
	make marco_pipe_2
	make strassen3
	make winograd3
	make ostrassen3
	make owinograd3
	make 3M
	make ex3_spipe
	make ex3_pipe
	make ex3gpu

ex3_atlas_all: 
	make ex2atlas		
	make ex3_atlas
	make strassen3atlas
	make winograd3atlas
	make winograd3atlaspipe
	make marcoatlas_pipe
	make ostrassen3atlas
	make owinograd3atlas
	make ex3gpu
	#make exerr3

## Example 4 is a parallel implementation

ex4_a: Examples/example.4.o $(obj)
	$(CC) $(OPT) $(INC) Examples/example.4.o $(obj) -o Executable/$(TYPE)/ex4_a $(ALIB) $(atlaslib)
ex4_g: Examples/example.4.o $(obj)
	$(FF) $(OPT) $(INC) Examples/example.4.o $(obj) -o Executable/$(TYPE)/ex4 $(GLIB) $(gotolib)


## Example 6 is a 3M complex multiplication 

3M:
	make ex6_3M
	make ex6
	make ex6_w
	make ex6_wpipe
	make ex6_spipe

ex6_3M:EXTRA_GOTO=-DGOTO_BLAS 
ex6_3M:MACROS+=-DLIBRARY_PACKAGE 
ex6_3M:  $(obj)
	$(CC) -c $(OPT)  -DGOTOS_TEST_3M=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o $(obj)  -o Executable/$(TYPE)/ex6_3m  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)
ex6:EXTRA_GOTO=-DGOTO_BLAS 
ex6:MACROS+=-DLIBRARY_PACKAGE 
ex6:  $(obj)
	$(CC) -c $(OPT)  -DGOTOS_TEST=1 $(INC) Examples/example.6.c -o Examples/example.6.o
	$(FF) $(OPT) $(INC) Examples/example.6.o $(obj)  -o Executable/$(TYPE)/ex6_g  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)
ex6_w:EXTRA_GOTO=-DGOTO_BLAS 
ex6_w:MACROS+=-DLIBRARY_PACKAGE 
ex6_w:  $(obj)
	$(CC) -c $(OPT)  -DWMUL_OPT_TEST=1 $(INC) Examples/example.6.c -o Examples/example.6.o
	$(FF) $(OPT) $(INC) Examples/example.6.o $(obj)  -o Executable/$(TYPE)/ex6_w  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)
ex6_wpipe:EXTRA_GOTO=-DGOTO_BLAS 
ex6_wpipe:MACROS+=-DLIBRARY_PACKAGE 
ex6_wpipe:  $(obj)
	$(CC) -c $(OPT)  -DWM_PIPE_TEST=1 $(INC) Examples/example.6.c -o Examples/example.6.o
	$(FF) $(OPT) $(INC) Examples/example.6.o $(obj)  -o Executable/$(TYPE)/ex6_wpipe  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)
ex6_spipe:EXTRA_GOTO=-DGOTO_BLAS 
ex6_spipe:MACROS+=-DLIBRARY_PACKAGE 
ex6_spipe:  $(obj)
	$(CC) -c $(OPT)  -DSM_PIPE_TEST=1 $(INC) Examples/example.6.c -o Examples/example.6.o
	$(FF) $(OPT) $(INC) Examples/example.6.o $(obj)  -o Executable/$(TYPE)/ex6_spipe  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib)

arun:Examples/pthreads.o 
	$(CC)  $(OPT) $(INC) Examples/pthreads.o -o Executable/pt  -lpthread

clean: 
	rm -f  */*.o #Executable/$(TYPE)/* 
clean_lib: 
	rm -f lib/* 


########################################################################################
########################################################################################

# for the analysis and testing of each examples
#
# Define the MACROS
#MACROS = -DSINGLE_PRECISION -DAPPLICATION -Dcopy=s_copy -DrandomInitialization=s_randomInitialization -Dmm_leaf_computation=mm_leaf_computation_s
#MACROS = -DDOUBLE_PRECISION -DAPPLICATION -Dcopy=d_copy -DrandomInitialization=d_randomInitialization -Dmm_leaf_computation=mm_leaf_computation_d
# MACROS = -DSINGLE_COMPLEX -DAPPLICATION -Dcopy=c_copy -DrandomInitialization=c_randomInitialization -Dmm_leaf_computation=mm_leaf_computation_c
# MACROS = -DDOUBLE_COMPLEX -DAPPLICATION -Dcopy=z_copy -DrandomInitialization=z_randomInitialization -Dmm_leaf_computation=mm_leaf_computation_z
# FASTLIBS= -lsfastmm 
# FASTLIBS= -ldfastmm  
# FASTLIBS= -lscfastmm 
# FASTLIBS= -ldcfastmm 


ex3_gotos_all_lib:
	make ex2_lib 
	make ex3_lib
	make gotos3_lib
	make marco3_lib
	make marco_pipe_lib
	make strassen3_lib
	make winograd3_lib
	make ostrassen3_lib
	make owinograd3_lib
	make ex6_lib
	make ex6_w_lib
	make marco_pipe_lib
	make ex3_spipe_lib
	make ex3_pipe_lib
	make ex6_wpipe_lib
	make ex6_spipe_lib
	make ex6_3M_lib
	make exerr2_lib

ex3_atlas_all_lib: 
	make ex3_atlas_lib
	make strassen3atlas_lib
	make winograd3atlas_lib
	make winograd3pipeatlas_lib
	make marcoatlas_pipe_lib
	make ostrassen3atlas_lib
	make owinograd3atlas_lib
	make exerr3_lib



## Example 2 is used to check whether or not an MM algorithm implementation is correct 
 
ex2_lib: 
	$(CC) -c $(OPT) -DMARCO_PIPE_TEST=1 $(INC) Examples/example.2.c -o Examples/example.2.o
	$(FF) $(OPT) $(INC) Examples/example.2.o  -o Executable/$(TYPE)/ex2  $(GLIB) $(gotolib)  $(FASTLIBDIR) $(FASTLIBS) #-lefence   #$(ALIB) $(atlaslib) #


## Example 5 is used to check whether or not an matrix addition algorithm implementation is correct 

ex5_lib: Examples/example.5.o 
	$(FF) $(OPT) $(INC) Examples/example.5.o  -o Executable/$(TYPE)/ex5  $(GLIB) $(gotolib) #-lefence #$(ALIB) $(atlaslib) #



exerr2_lib: Examples/example.err.1.o 
	$(FF) $(OPT) $(INC)  Examples/example.err.1.o  -o $(DEST) $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) -lm #$(ALIB) $(atlaslib)  
exerr3_lib: Examples/example.err.1.o 
	$(FF) $(OPT) $(INC)  Examples/example.err.1.o $(obj2) -o Executable/exerrATLAS   -lm $(ALIB) $(atlaslib)  



## Example 3 is the core for performance evaluation
## It can be used to generate executable for Goto's, ATLAS, W-Goto, W-ATLAS

ex3_lib:    
	$(CC) -c $(OPT) -DALPHA=1  -DGOTOS_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o   -o Executable/ex3_g  $(math) $(GLIB) $(gotolib)  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

ex3_pipe_lib:  	
	$(CC) -c $(OPT)   -DWM_PIPE_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o   -o Executable/ex3_pipe  $(math) $(GLIB) $(gotolib)  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

marco_pipe_lib:  
	$(CC) -c $(OPT)   -DMARCO_PIPE_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o   -o Executable/marco_pipe  $(math) $(GLIB) $(gotolib)  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)


ex3_spipe_lib:  
	$(CC) -c $(OPT)   -DSM_PIPE_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o   -o Executable/ex3_spipe  $(math) $(GLIB) $(gotolib)  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

ex3_atlas_lib:  
	$(CC) -c $(OPT) -DGOTOS_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC) Examples/example.3.o   -o Executable/atlas  $(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS) #$(GLIB) $(gotolib) #

gotos3_lib:
	$(CC) -c $(OPT) -DGOTOS_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/gotos $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)
gpu_lib:
	$(CC) -c $(OPT) -DGOTOS_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/gotos $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

marco3_lib:
	$(CC) -c $(OPT) -DMARCO_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/marco $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

rmul_lib:
	$(CC) -c $(OPT) -DRMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/rmul $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

adaptive_lib:
	$(CC) -c $(OPT) -DGOTOS_TEST=1  -DADAPTIVE=1 -DALPHA=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/adaptive $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

mkl3_lib:
	$(CC) -c $(OPT) -DGOTOS_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/gotos $(MKLLIB) $(mklblas) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)


strassen3_lib:
	$(CC) -c $(OPT) -DSMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/strassen $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

winograd3_lib:
	$(CC) -c $(OPT) -DWMUL_OPT_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/winograd $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

ostrassen3_lib:
	$(CC) -c $(OPT) -DOMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC)  Examples/example.3.o  -o Executable/ostrassen $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

owinograd3_lib:
	$(CC) -c $(OPT) -DOWMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC)  Examples/example.3.o  -o Executable/owinograd $(GLIB) $(gotolib) $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)

strassen3atlas_lib:
	$(CC) -c $(OPT) -DSMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC)  Examples/example.3.o  -o Executable/strassenatlas $(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)


winograd3pipeatlas_lib:
	$(CC) -c $(OPT) -DWMUL_PIPE_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC)  Examples/example.3.o  -o Executable/winogradatlas $(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)

ostrassen3atlas_lib:
	$(CC) -c $(OPT) -DOMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC)  Examples/example.3.o  -o Executable/ostrassenatlas $(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)

owinograd3atlas_lib:
	$(CC) -c $(OPT) -DOWMUL_TEST=1  $(INC) Examples/example.3.c -o Examples/example.3.o
	$(CC) $(OPT) $(INC) Examples/example.3.o  -o Executable/owinogradatlas $(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)
marcoatlas_pipe_lib:  
	$(CC) -c $(OPT)   -DMARCO_PIPE_TEST=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o   -o Executable/marco_pipe $(ALIB) $(atlaslib)  $(FASTLIBDIR) $(FASTLIBS) #$(ALIB) $(atlaslib)
## Example 4 is a parallel implementation

ex4_a_lib: Examples/example.4.o 
	$(CC) $(OPT) $(INC) Examples/example.4.o  -o Executable/ex4_a $(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)
ex4_g_lib: Examples/example.4.o 
	$(FF) $(OPT) $(INC) Examples/example.4.o  -o Executable/ex4 $(GLIB) $(gotolib)   $(FASTLIBDIR) $(FASTLIBS)


## Example 6 is a 3M complex multiplication 

ex6_3M_lib:  
	$(CC) -c $(OPT)  -DGOTOS_TEST_3M=1 $(INC) Examples/example.3.c -o Examples/example.3.o
	$(FF) $(OPT) $(INC) Examples/example.3.o   -o Executable/ex6_3m  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)
ex6_lib:  
	$(CC) -c $(OPT)  -DGOTOS_TEST=1 $(INC) Examples/example.6.c -o Examples/example.6.o
	$(FF) $(OPT) $(INC) Examples/example.6.o   -o Executable/ex6_g  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)
ex6_w_lib:  
	$(CC) -c $(OPT)  -DWMUL_OPT_TEST=1 $(INC) Examples/example.6.c -o Examples/example.6.o
	$(FF) $(OPT) $(INC) Examples/example.6.o   -o Executable/ex6_w  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)
ex6_wpipe_lib:  
	$(CC) -c $(OPT)  -DWM_PIPE_TEST=1 $(INC) Examples/example.6.c -o Examples/example.6.o
	$(FF) $(OPT) $(INC) Examples/example.6.o   -o Executable/ex6_wpipe  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)
ex6_spipe_lib:  
	$(CC) -c $(OPT)  -DSM_PIPE_TEST=1 $(INC) Examples/example.6.c -o Examples/example.6.o
	$(FF) $(OPT) $(INC) Examples/example.6.o   -o Executable/ex6_spipe  $(math) $(GLIB) $(gotolib) #$(ALIB) $(atlaslib) $(FASTLIBDIR) $(FASTLIBS)
