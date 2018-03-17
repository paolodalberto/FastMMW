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
/************************************************************
 *
 * This the core example for purpose measure. With the right macro
 * defined, I can test any MM algorithm.
 * 
 *
 *
 *
 */

#define GETTIME
#include <architecture.h>
#include <mat-operands.h>
#include <mat-mulkernels.h>
#include <mat-addkernels.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>


#ifdef CLBLAS
#include <clAmdBlas.h>
#endif



#define ADDINTERVAL 5
#define MULINTERVAL 20

#include <omp.h>

#include <stdio.h>
//#include <scaling.h>

static int echo =1;

extern int debug;

#define MAXMAT 6

int main() {
  double time_mul;
  double time_add, ops,mops_add,mops_add_2,mops_mul;
  double time_add_2;
  char d[100];
  int M;
  Matrix c[MAXMAT];

  /*
   TIME;
   C0 += A*B;
   C1 += A*B;
   C2 += A*B;
   C3 += A*B;
   TIME;
  */

  
  { // beta initialization
    int i=0;
    
    for (i=0;i<MAXMAT;i++){ 
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
      c[i].beta=1.0+0*I;
      printf("B[%e+i%e]\n", creal(a.beta),cimag(a.beta));
#else
      a.beta=1.0;
      printf("B[%e]\n", (double)a.beta);
#endif
      c[i].gpu=-1;
    }
  }
  

  printf("Size %d float %d double %d complex %d z-complex %d cpu_set_t %d \n", \
	 sizeof(Mat), sizeof(float),sizeof(double), sizeof(float complex) , sizeof(double complex),
	 sizeof(cpu_set_t));
  
  printf("Size:\n")
  scanf("%d", &M);
  { // beta initialization
    int i=0;
    
    for (i=0;i<MAXMAT;i++){
      c[i].m = c[i].n = c[i].M = c[i].N = M;
      c[i].trans = 'n';
    }
  }


  printf(" size of the matrix element %d\n", sizeof(Mat));
  printf(" You selected the following problem \n");
  printf("      A %d x %d gpu %d\n",c[0].m,c[0].n,c[0].gpu);
   
  printf("Creation ...\n");


  { // beta initialization
    int i=0;
    for (i=0;i<MAXMAT;i++){
      c[i].data = (Mat *) CALLOC(c[i]);
    }
  }


	
  printf("Initialization ...\n");
  
  { // beta initialization
    int i=0;
    for (i=0;i<MAXMAT;i++){
      randomInitialization(c[i],rand(),rand());
    }
  }
  
  
  
#ifdef CLBLAS
  set_platform_and_devices(1);
#endif
  
  
  
  
  TIMING_COLD(							\
	      {							\
		CMC(c[2], =, c[0], mm_leaf_computation, c[1]);	\
		CMC(c[3], =, c[0], mm_leaf_computation, c[1]);	\
		CMC(c[4], =, c[0], mm_leaf_computation, c[1]);	\
		CMC(c[5], =, c[0], mm_leaf_computation, c[1]);	\
	      },						\
	      time_mul,MULINTERVAL				\
								);
  if (echo) printf(" Time Cold %e \n", time_mul);
  ops = ((double)2*c.M)*((double)c.N*(double)((b.trans=='n')?b.M:b.N));
  printf(" MUL OPS %e", ops);if (echo) printf("\n");
  mops_mul=(ops/time_mul)/(double)1000000000;
  printf(" %s OPS %e GFLOPS COLD %e", program, ops, mops_mul);if (echo) printf("\n");
  

  TIMING_ITER(						\
	      {							\
		CMC(c[2], =, c[0], mm_leaf_computation, c[1]);	\
		CMC(c[3], =, c[0], mm_leaf_computation, c[1]);	\
		CMC(c[4], =, c[0], mm_leaf_computation, c[1]);	\
		CMC(c[5], =, c[0], mm_leaf_computation, c[1]);	\
	      },time_mul,MULINTERVAL, mask);


  if (echo) printf(" Time HOT %e \n", time_mul);
  ops = ((double)2*c.M)*((double)c.N*(double)((b.trans=='n')?b.M:b.N));
  printf(" MUL OPS %e", ops);if (echo) printf("\n");
  mops_mul=(ops/time_mul)/(double)1000000000;
  printf(" %s OPS %e GFLOPS HOT  %e", program, ops, mops_mul);if (echo) printf("\n");


  { // beta initialization
    int i=0;
    for (i=0;i<MAXMAT;i++){
      FREE(c[i].data);
    }
  }


#ifdef CLBLAS
  release_blas_context();
#endif
  
  return 0;
}
