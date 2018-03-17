##################################################################
#
# Makefile 
#
#
#

# Code root directory 



HOMEDIR = $(PWD)/../../../
#HOMEDIR = /home/paolo/Martingale/FastLibrary_7/
RDIR = $(HOMEDIR)/R/FastMMW/src/
RCOMMAND=/usr/bin/R

## C and FORTAN compilers. I use gcc but you may change it. 
CC  = gcc
FF  = gfortran
AR  = ar rcs

## Machine Specific optimizations 
MACHTYPE = x86_64
ARCH = -D$(MACHTYPE)
#PROCESSOR=athlon

#ifeq ($(PROCESSOR),athlon)
#	OPT_PROC = -O2 -Wall   -msse2  -march=opteron -mtune=opteron -fPIC
	#OPT_PROC = -O2  -fPIC# -msse2  -march=opteron -mtune=opteron
#else 
OPT_PROC = -O2   -msse2 -fPIC
#	#OPT_PROC = -O2   -fPIC# -msse2  -march=opteron -mtune=opteron #-O2   -msse2 
#endif


OPT = $(OPT_PROC) -DRDEF $(ARCH) 




# Includes
INC = -I ../include\
	-I /usr/share/R/include/ \
	-I $(PWD)  


## Libraries 
math = -lm 
fastmmwlib  = -L../lib/ -lFastMMWR


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

#.c.o:
#	$(CC) -E $(OPT) $(INC) $< -o $@.c
#	$(CC) -c $(OPT) $(INC) $< -o $@





#lib:FastMMWR.o
#	echo $(PWD)
#	ls -l  ../lib/*
#	$(AR)v ../lib/libFastMMWR.a ../lib/libdcfastmm.a  ../lib/libdfastmm.a  ../lib/libscfastmm.a  ../lib/libsfastmm.a
#	cp ../lib/libFastMMWR.a .


#lib: 
#	echo $(HOMEDIR)/R/FastMMW/lib
#	cp /home/paolo/fusion/paolo/Desktop/MM/fmm/lib/*.a  $(HOMEDIR)/R/FastMMW/lib
all:
#	make lib
	$(RCOMMAND) CMD SHLIB FastMMWR.c   
	#	$(HOMEDIR)/R/R-2.10.1/bin/R CMD SHLIB cdlR.c $(INC) $(cdl)  -o cdlR.so
R:
#	make lib
	$(RCOMMAND) CMD SHLIB FastMMWR.c 
#	cp FastMMWR.so $(HOMEDIR)/R/FastMMW/lib
#	ls $(HOMEDIR)/R/FastMMW/lib


## Example 2 is used to check whether or not an MM algorithm implementation is correct 
 

clean: 
	rm FastMMWR.o
#	rm -f $(obj) $(HOMEDIR)/Examples/*.o $(HOMEDIR)/Executable/* $(HOMEDIR)/*.o.c $(HOMEDIR)/*/*.o.c $(HOMEDIR)/*/*/*.o.c $(HOMEDIR)/lib/*
