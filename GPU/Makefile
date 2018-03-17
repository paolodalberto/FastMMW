CC = gcc

ARC=Fiji

HOMEDIR=../

ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.10.0-${ARC}-Linux-x64-CL2.0
#ARCHITECTURE=/usr/local
	                                 
#ARCHITECTURE=/home/paolo/Desktop/OpenCL3/clBLAS-2.11.0-Linux-x64
#ARCHITECTURE=/opt/clAmdBlas-1.10.321/
#ARCHITECTURE=/home/paolo/Desktop/O/usr/local/./include/penCL3/clBLAS-2.10.0-Hawaii-Linux-x64-CL2.0
ATLAS= $(D)/ATLAS/install


INCLUDE = -I $(HOMEDIR) -I $(ATLAS)/include -I $(HOMEDIR)/Add -I $(HOMEDIR)/Mul \
	-I $(HOMEDIR)/Matrices -I $(HOMEDIR)/Sort -I $(HOMEDIR)/Scaling \
	-I $(HOMEDIR)/PThread -I $(HOMEDIR)/Error \
	-I /opt/AMDAPPSDK-3.0/include/ -I $(ARCHITECTURE)/include -I $(HOMEDIR)/GPU

LIBS = -l OpenCL -l clBLAS -pthread #-l clAmdBlas
LIBRARYPATH = -L /opt/AMDAPPSDK-3.0/lib/x86_64/ -L $(ARCHITECTURE)/lib64/
OPT= -O1  -Wall -g

.c.o: 
	$(CC) -E  $(OPT) $(OPTD)  $(INCLUDE) $< -o $@.c
	$(CC) -c  $(OPT) $(OPTD) $(INCLUDE) $< -o $@


clear: 
	rm *.o $(ARC)-?gemm? *.o.c
clean: 
	rm *.o 
all: sgemm  dgemm  cgemm zgemm devices platforms



DEBUG="-DDEBUG=1"

obj = example_sgemm.o example_sgemm_multigraphic.o  example_sgemm_multigraphic_2.o
objg = example_sgemm_multigraphic_main.o 
obj2 = example_sgemm.o example_sgemm_multigraphic.o  example_sgemm_multigraphic_2.o  


devices:devices.o
	$(CC) $(INCLUDE) devices.o $(LIBRARYPATH) $(LIBS)   -o devices
platforms:platforms.o
	$(CC) $(INCLUDE) platforms.o $(LIBRARYPATH) $(LIBS)   -o platforms

gemm: OPTD = -DCLBLAS -DAPPLICATION #-DDEBUG=1
gemm: $(objg)
	$(CC) $(INCLUDE) example_sgemm_multigraphic_main.o  \
	$(LIBRARYPATH) $(LIBS)  -o $(ARC)-gemm



sgemm: OPTD = -DDATATYPE=cl_float -DALPHA=1.0 -DBETA=1.0 -DGEMM=clblasSgemm #-DDEBUG=1
sgemm: $(obj)
	$(CC) $(INCLUDE) example_sgemm.o $(LIBRARYPATH) $(LIBS)                -o $(ARC)-sgemm
	$(CC) $(INCLUDE) example_sgemm_multigraphic.o $(LIBRARYPATH) $(LIBS)   -o $(ARC)-sgemm2
	$(CC) $(INCLUDE) example_sgemm_multigraphic_2.o $(LIBRARYPATH) $(LIBS) -o $(ARC)-sgemm3


dgemm: 	OPTD = -DDATATYPE=cl_double -DALPHA=1.0 -DBETA=1.0 -DGEMM=clblasDgemm
dgemm:  $(obj)
	$(CC) $(INCLUDE) example_sgemm.o $(LIBRARYPATH) $(LIBS)                -o $(ARC)-dgemm
	$(CC) $(INCLUDE) example_sgemm_multigraphic.o $(LIBRARYPATH) $(LIBS)   -o $(ARC)-dgemm2
	$(CC) $(INCLUDE) example_sgemm_multigraphic_2.o $(LIBRARYPATH) $(LIBS) -o $(ARC)-dgemm3


pdgemm: OPTD = -DDATATYPE=cl_double -DALPHA=1.0 -DBETA=1.0 -DGEMM=clblasDgemm -DPOORPRECISION=1
pdgemm: example_sgemm_multigraphic_2_3m.o
	$(CC) $(INCLUDE) example_sgemm_multigraphic_2_3m.o $(LIBRARYPATH) $(LIBS) -o $(ARC)-pdgemm	


cgemm:  OPTD = -DDATATYPE=FloatComplex -DALPHA='{1.0,1.0}' -DBETA='{1.0,1.0}'  -DGEMM=clblasCgemm -DCOMPLEX  -DQF=floatComplex -DMDATATYPE=FloatComplex #-DMDATATYPE="float complex"   -DDEBUG=1 
cgemm:  $(obj) 
	$(CC) $(INCLUDE) example_sgemm.o $(LIBRARYPATH) $(LIBS)                -o $(ARC)-cgemm
	$(CC) $(INCLUDE) example_sgemm_multigraphic.o $(LIBRARYPATH) $(LIBS)   -o $(ARC)-cgemm2
	$(CC) $(INCLUDE) example_sgemm_multigraphic_2.o $(LIBRARYPATH) $(LIBS) -o $(ARC)-cgemm3
	#$(CC) $(INCLUDE) cgemm.o $(LIBRARYPATH) $(LIBS) -o cgemm4

zgemm: 	OPTD =-DDATATYPE=DoubleComplex -DALPHA='{1.0,1.0}' -DBETA='{1.0,1.0}'  -DGEMM=clblasZgemm -DCOMPLEX -DQF=doubleComplex     -DMDATATYPE=DoubleComplex #-DDEBUG=1 -DMDATATYPE="double complex"
zgemm:  $(obj)
	$(CC) $(INCLUDE) example_sgemm.o $(LIBRARYPATH) $(LIBS)                -o $(ARC)-zgemm
	$(CC) $(INCLUDE) example_sgemm_multigraphic.o $(LIBRARYPATH) $(LIBS)   -o $(ARC)-zgemm2
	$(CC) $(INCLUDE) example_sgemm_multigraphic_2.o $(LIBRARYPATH) $(LIBS) -o $(ARC)-zgemm3

