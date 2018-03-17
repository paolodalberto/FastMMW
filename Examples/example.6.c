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
#include <pt.h>

//#define ATLAS_TEST 1
// #define SMUL_TEST 1
// #define WMUL_TEST 1
//#define OMUL_TEST 1

#ifdef GOTOS_TEST   
  char *program = "GOTOS";
#endif  
#ifdef SMUL_TEST
  char *program = "STRASSEN";
#endif
#ifdef WMUL_TEST 
  char *program = "WINOGRAD";
#endif
#ifdef WMUL_OPT_TEST 
  char *program = "WINOGRAD-OPT";
#endif
#ifdef OMUL_TEST
  char *program = "Oblivious STRASSEN";
#endif
#ifdef OWMUL_TEST
  char *program = "Oblivious WINO";
#endif
#ifdef WM_PIPE_TEST   
  char *program = "WM_PIPE";
#endif  
#ifdef SM_PIPE_TEST   
  char *program = "SM_PIPE";
#endif  


#define ADDINTERVAL 3
#define MULINTERVAL 10
#include <stdio.h>
//#include <scaling.h>

static int echo =1;






int main() {
  double time_mul;
  double time_add, ops,mops_add,mops_mul;
  Matrix c1,c2,a1,a2,b1,b2,t1,t2;
  int sel;
  char d[100]={0, 0};
  char TRANSPOSE[3] = {'n', 't', 'c'};
 
  // If Voltage and frequency Scaling is possible, we initialize the driver

#ifdef SCALING
  openCpuScalingDriver();
  switchC();
#endif

  printf("A [n/t/c]\n");
  SELECT(sel);
  printf("%d  A[%c]\n", sel, a1.trans=TRANSPOSE[sel]);
  printf("B [n/t/c]\n");
  SELECT(sel);
  printf("%d  B[%c]\n", sel, b1.trans=TRANSPOSE[sel]);
  c1.trans  = 'n';


  strcpy(d,"1");
  printf("Beta A \n");
  scanf("%s",d);
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  a1.beta=atof(d)+0*I;
  printf("B[%e+i%e]\n", creal(a1.beta),cimag(a1.beta));
#else
  a1.beta=atof(d);
  printf("B[%e]\n", (double)a1.beta);
#endif
  printf("Beta B \n");
  scanf("%s",d);
  printf("Beta C \n");
  scanf("%s",d);
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  b1.beta=atof(d)+0*I;
  printf("B[%e+i%e]\n", creal(b1.beta),cimag(b1.beta));
#else
  b1.beta=atof(d);
  printf("B[%e]\n",  (double)b1.beta);
#endif
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  c1.beta=atof(d)+0*I;
  printf("C[%e+i%e]\n", creal(c1.beta),cimag(c1.beta));
#else
  c1.beta=atof(d);
  printf("C[%e]\n",  (double)c1.beta);
#endif

  

  printf(" <a.m,a.n,b.m,b.n> ?\n");
  scanf("%d %d %d %d", &a1.M,&a1.N,&b1.M,&b1.N);

  a1.m=a1.M ; a1.n=a1.N ;
  b1.m=b1.M ; b1.n=b1.N ;
  if (a1.trans=='n') {
    c1.m=c1.M =a1.M; 
  }
  else {
    c1.m=c1.M =a1.N;
  }
  if (b1.trans=='n') {
    c1.n=c1.N =b1.N;
  }
  else {
    c1.n=c1.N =b1.M;
  }
  
 
  printf(" You selected the following problem \n");
  printf("      A %d x %d \n",a1.m,a1.n);
  printf("      B %d x %d \n",b1.m,b1.n);
  printf(" Thus C %d x %d \n",c1.m,c1.n);
  
  if (a1.trans == 'n' && b1.trans == 'n' && a1.n != b1.m ) { 
    printf(" N N wrong sizes ... a.n != b.m\n");
    return 0;
  }
  if (a1.trans != 'n' && b1.trans == 'n' && a1.m != b1.m ) { 
    printf("T N wrong sizes ... a.m != b.m\n");
    return 0;
  }
  if (a1.trans != 'n' && b1.trans != 'n' && a1.m != b1.n ) { 
    printf("T T wrong sizes ... a.m != b.n\n");
    return 0;
  }
  if (a1.trans == 'n' && b1.trans != 'n' && a1.n != b1.n ) { 
    printf("N T wrong sizes ... a.n != b.n\n");
    return 0;
  }
  a2 = a1;
  b2 = b1;
  c2 = c1;
  t1 = a1;
  t2 = b1;

  printf("Creation ...\n");
  
  a1.data    = (Mat *) CALLOC(a1);
  b1.data    = (Mat *) CALLOC(b1);
  c1.data    = (Mat *) CALLOC(c1);
  a2.data    = (Mat *) CALLOC(a2);
  b2.data    = (Mat *) CALLOC(b2);
  c2.data    = (Mat *) CALLOC(c2);
  t1.data    = (Mat *) CALLOC(t1);
  t2.data    = (Mat *) CALLOC(t2);
	
	
  printf("Initialization ...\n");
  
  
  randomInitialization(b1,rand(),rand());
  randomInitialization(a1,rand(),rand());
  randomInitialization(b2,rand(),rand());
  randomInitialization(a2,rand(),rand());

    
#ifdef ALPHA
  printf("Addition ... \n");
  TIMING(CMC(c1, =, a1, s_add, b1),time_add,ADDINTERVAL);
  if (echo) printf(" Time %e \n", time_add);
  ops=(((double)(a1.M))*(double)a1.N);
  printf(" ADD OPS %e", ops);if (echo) printf("\n");
  mops_add = (ops/time_add)/(double)1000000;
  printf(" ADD MFLOPS %e", mops_add);if (echo) printf("\n");
#endif
  printf("MUL ... \n");

  // 3M(c1,c2,a1,a2,b1,b2,t1,t2, MM, MADD, MA, MA_t) {	
#ifdef WM_PIPE_TEST   
  TIMING_COLD(MM3_PIPE(c1,c2,a1,a2,b1,b2,t1,t2,wmpipe, wmaddpipe, s_add, s_add_t),time_mul,MULINTERVAL);
#endif  
#ifdef SM_PIPE_TEST   
  TIMING_COLD(MM3_PIPE(c1,c2,a1,a2,b1,b2,t1,t2,smpipe, smaddpipe, s_add, s_add_t),time_mul,MULINTERVAL);
#endif  

#ifdef GOTOS_TEST   
  TIMING_COLD(MM3(c1,c2,a1,a2,b1,b2,t1,t2,mm_leaf_computation, mm_leaf_computation_madd, s_add, s_add_t),time_mul,MULINTERVAL);
#endif  
#ifdef SMUL_TEST

  TIMING_COLD(MM3(c1,c2,a1,a2,b1,b2,t1,t2,smul, saddmul, s_add, s_add_t),time_mul,MULINTERVAL);
#endif
#ifdef WMUL_TEST
  TIMING_COLD(MM3(c1,c2,a1,a2,b1,b2,t1,t2,wmul, waddmul, s_add, s_add_t),time_mul,MULINTERVAL);
#endif
#ifdef WMUL_OPT_TEST
  TIMING_COLD(MM3(c1,c2,a1,a2,b1,b2,t1,t2,wm, wmadd, s_add, s_add_t),time_mul,MULINTERVAL);
#endif
#ifdef OMUL_TEST
  TIMING_COLD(MM3(c1,c2,a1,a2,b1,b2,t1,t2,omul, oaddmul, s_add, s_add_t),time_mul,MULINTERVAL);
#endif
#ifdef OWMUL_TEST
  TIMING_COLD(MM3(c1,c2,a1,a2,b1,b2,t1,t2,owmul, owaddmul, s_add, s_add_t),time_mul,MULINTERVAL);
#endif

  //  fastCPU();  

  if (echo) printf(" Time %e Cold\n", time_mul);
  ops = ((double)2*c1.M)*((double)c1.N*(double)((b1.trans=='n')?b1.M:b1.N));
  printf(" MUL OPS %e", ops);if (echo) printf("\n");
  mops_mul=(ops/time_mul)/(double)1000000;
  printf(" %s OPS %e MFLOPS COLD %e", program, ops, mops_mul);if (echo) printf("\n");

#ifdef WM_PIPE_TEST   
  TIMING(MM3_PIPE(c1,c2,a1,a2,b1,b2,t1,t2,wmpipe, wmaddpipe, s_add, s_add_t),time_mul,MULINTERVAL);
#endif  
#ifdef SM_PIPE_TEST   
  TIMING(MM3_PIPE(c1,c2,a1,a2,b1,b2,t1,t2,smpipe, smaddpipe, s_add, s_add_t),time_mul,MULINTERVAL);
#endif  

#ifdef GOTOS_TEST   
  TIMING(MM3(c1,c2,a1,a2,b1,b2,t1,t2,mm_leaf_computation, mm_leaf_computation_madd, s_add, s_add_t),time_mul,MULINTERVAL);
#endif  
#ifdef SMUL_TEST
  TIMING(MM3(c1,c2,a1,a2,b1,b2,t1,t2,smul, saddmul, s_add, s_add_t),time_mul,MULINTERVAL);
#endif
#ifdef WMUL_TEST
  TIMING(MM3(c1,c2,a1,a2,b1,b2,t1,t2,wmul, waddmul, s_add, s_add_t),time_mul,MULINTERVAL);
#endif
#ifdef WMUL_OPT_TEST
  TIMING(MM3(c1,c2,a1,a2,b1,b2,t1,t2,wm, wmadd, s_add, s_add_t),time_mul,MULINTERVAL);
#endif
#ifdef OMUL_TEST
  TIMING(MM3(c1,c2,a1,a2,b1,b2,t1,t2,omul, oaddmul, s_add, s_add_t),time_mul,MULINTERVAL);
#endif
#ifdef OWMUL_TEST
  TIMING(MM3(c1,c2,a1,a2,b1,b2,t1,t2,owmul, owaddmul, s_add, s_add_t),time_mul,MULINTERVAL);
#endif

  //  fastCPU();  

  if (echo) printf(" Time %e Hot\n", time_mul);
  ops = ((double)2*c1.M)*((double)c1.N*(double)((b1.trans=='n')?b1.M:b1.N));
  printf(" MUL OPS %e", ops);if (echo) printf("\n");
  mops_mul=(ops/time_mul)/(double)1000000;
  printf(" %s OPS %e MFLOPS HOT  %e", program, ops, mops_mul);if (echo) printf("\n");

#ifdef ALPHA
  printf("22*pi/alpha = %e\n", (((double)22)*mops_mul)/mops_add);
#endif


  free(a1.data);
  free(a2.data);
  free(b1.data);
  free(b2.data);
  free(c1.data);
  free(c2.data);

#ifdef SCALING
  closeCpuScalingDriver();
#endif

  return 0;
}
