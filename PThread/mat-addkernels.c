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
#define MODULE_MATKERNEL 1
#include <mat-operands.h>
#include <mat-addkernels.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



#define PTHREAD_IMPLEMENTATION

#ifdef PTHREAD_IMPLEMENTATION


typedef int  (*)(DEF(c),DEF(a),DEF(b))  MatrixComputation;



struct operands_addition { 
  int pi;
  MatrixComputation m;
  Matrix c;
  Matrix a;
  Matrix b;
} ;

typedef struct operands_addition TAddOperands;


typedef TAddOperands* (*)(DEF(c), DEF(a), DEF(b), MatrixComputation m)  DivideOperands;

#define NUM_THREADS 2


static void *basicComputation( void *s) { 
  TAddOperands m = *(TAddOperands *)s;
  m.p(m.c,m.a,m.b);
  return 0;
}

void pThreadedMatrixComputation(MatrixComputation m, 
				DivideOperands d,
				DEF(c), DEF(a), DEF(b)) {
  
  pthread_t*  p_thread; /* thread's structure */
  pthread_attr_t attr;
  int* thr_id;
  int i;

  
  thr_id = malloc(NUM_THREADS * sizeof(int) );
  p_thread = malloc(NUM_THREADS * sizeof(pthread_t) );
  pthread_attr_init(&attr);

  TAddOperands *args = d(USE(c),USE(a),USE(b),m);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
  
  for (i = 0; i<NUM_THREADS; i++){
    thr_id[i] = pthread_create(&p_thread[i], 
			       &attr, 
			       basicComputation, 
			       (void *)(args+i));
  }
  
 //START_CLOCK;
 /* wait for the threads to complete */
 for (i = 0; i<NUM_THREADS; i++){
   pthread_join(p_thread[i], NULL);
 }
 //printf(" Done pthreading \n");
}


#endif
