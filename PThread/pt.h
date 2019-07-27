/* 
   Copyright 2011 Paolo D'Alberto, Marco Bodrato, and Alexandru
   Nicolau

   This file is part of the Fast Matrix Multiply library (FMM).
      
   FMM is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   FMM is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General
   Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with FMM.  If not, see
   <http://www.gnu.org/licenses/>.

*/
#ifndef PTHREAD_IMPLEMENTATION
#define PTHREAD_IMPLEMENTATION

#include <mat-operands.h>
#include <mat-addkernels.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

/*
#define _GNU_SOURCE
#include <sched.h>
*/
#define CPU_SETSIZE __CPU_SETSIZE
# define CPU_ZERO(cpusetp) __CPU_ZERO_S (sizeof (cpu_set_t), cpusetp)
# define CPU_SET(cpu, cpusetp) __CPU_SET_S (cpu, sizeof (cpu_set_t), cpusetp)
# define CPU_ISSET(cpu, cpusetp) __CPU_ISSET_S (cpu, sizeof (cpu_set_t), cpusetp)
# define CPU_COUNT(cpusetp)      __CPU_COUNT_S (sizeof (cpu_set_t), cpusetp)


#include "ptarchitecture.h"

/*

//An example how to use only two cores of a four core system 

#define NUM_THREADS 2
#define NUM_CORES 2

static int _P[NUM_CORES]   = {2,8};
static int _A[NUM_THREADS]   = {2,8};
static int _T[NUM_THREADS] = {2,8};

*/

#if(APPLICATION) 
#define Matrix S_Matrix
#define DEF(C) S_Matrix C
#endif





#if(SINGLE_PRECISION && LIBRARY_PACKAGE)
#define pThreadedMatrixComputation S_pThreadedMatrixComputation
#define TAddOperands               S_TAddOperands
#define MatrixComputation          S_MatrixComputation
#define MatrixComputations         S_MatrixComputations
#define DivideOperands             S_DivideOperands

#elif(DOUBLE_PRECISION && LIBRARY_PACKAGE)
#define pThreadedMatrixComputation D_pThreadedMatrixComputation
#define TAddOperands               D_TAddOperands
#define MatrixComputation          D_MatrixComputation
#define DivideOperands             D_DivideOperands
#define MatrixComputations         D_MatrixComputations
#elif(SINGLE_COMPLEX && LIBRARY_PACKAGE)
#define pThreadedMatrixComputation C_pThreadedMatrixComputation
#define TAddOperands               C_TAddOperands
#define MatrixComputation          C_MatrixComputation
#define DivideOperands             C_DivideOperands
#define MatrixComputations         C_MatrixComputations

#elif(DOUBLE_COMPLEX &&  LIBRARY_PACKAGE)
#define TAddOperands               Z_TAddOperands
#define pThreadedMatrixComputation Z_pThreadedMatrixComputation
#define MatrixComputation          Z_MatrixComputation
#define DivideOperands             Z_DivideOperands
#define MatrixComputations         Z_MatrixComputations

#endif

typedef int  (*MatrixComputation)(DEF(c),DEF(a),DEF(b));
typedef struct operands_addition TAddOperands;

typedef TAddOperands* (*DivideOperands)(DEF(c), 
					DEF(a), 
					DEF(b), 
					MatrixComputation m, 
					int *k)  ;

struct operands_addition { 
  int  pi;
  MatrixComputation m;
  Matrix c;
  Matrix a;
  Matrix b;
} ;



typedef struct operands_composed TComposedOperands;

typedef void (*Sync)(void *);

struct operands_composed { 
  int gpu;
  int step; // step in the winograd computation
  int P;    // these are related to the shape of the computation  
  int Q;    // 7, 23, 49
  int base; //
  Matrix C; // Original matrices
  Matrix A;
  Matrix B;
  Matrix Ps; // temporary matrices
  Matrix *Cs; // temporary matrices
  Matrix As;
  Matrix Bs;
  float  *ALPHA; // winograd algorithms as tensors
  float  *BETA ;
  float  *GAMMA;
  Sync sync;
} ;







#ifndef MODULE_PTMATRIXCOMPUTATION

void pThreadedMatrixComputation(MatrixComputation m, DivideOperands d, DEF(c), DEF(a), DEF(b));


#endif


#endif
