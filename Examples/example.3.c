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


#ifdef CLBLAS
#include <clblast_c.h>
//#include <clAmdBlas.h>
#endif
//#include <scaling.h>

//#define ATLAS_TEST 1
// #define SMUL_TEST 1
// #define WMUL_TEST 1
//#define OMUL_TEST 1

#include "example.3.h"

#ifdef GOTOS_TEST   
  char *program = "GOTOS";
#endif  
#ifdef RMUL_TEST   
  char *program = "RMUL";
#endif  
#ifdef WM_PIPE_TEST   
  char *program = "WM_PIPE";
#endif  
#ifdef MARCO_PIPE_TEST   
  char *program = "MARCO_PIPE";
#endif  
#ifdef MARCO_PIPE_TEST_2   
  char *program = "MARCO_PIPE_PREVIOUS";
#endif  
#ifdef SM_PIPE_TEST   
  char *program = "SM_PIPE";
#endif  
#ifdef GOTOS_TEST_3M   
  char *program = "GOTOS_3M";
#endif  
#ifdef SMUL_TEST
  char *program = "STRASSEN";
#endif
#ifdef MARCO_TEST   
  char *program = "MARCO-Winograd";
#endif  
#ifdef MARCO_TEST_2   
  char *program = "MARCO-Winograd previous";
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

#ifdef ADAPTIVE

#endif


#define ADDINTERVAL 5
#define MULINTERVAL 20

#include <omp.h>

#include <stdio.h>
//#include <scaling.h>

static int echo =1;

extern int debug;



int main() {
  double time_mul;
  double time_add, ops,mops_add,mops_add_2,mops_mul;
  double time_add_2;
  Matrix c,a,b,t;
  char _ps[1024];
  int sel;
  char d[100]={0, 0};
  char TRANSPOSE[3] = {'n', 't', 'c'};
  int mask=0;
  cpu_set_t mask_ts[256];
  cpu_set_t mask_t;
  cpu_set_t current_mask;
  int i;

#ifdef MYSCHED
  cpu_set_t *cpusetp;
  size_t size;
  int num_cpus, cpu;
#endif
#ifdef CLBLAS
  extern int gpus[4];
  extern int ngpus;
  extern int _sizes[4];
  
  int *intgpus;
  int left, right;
#endif
#ifdef SCALING
  // If Voltage and frequency Scaling is possible, we initialize the driver
  openCpuScalingDriver();
#endif

  printf("A [n/t/c]\n");
  SELECT(sel);
  printf("%d  A[%c]\n", sel, a.trans=TRANSPOSE[sel]);
  printf("B [n/t/c]\n");
  SELECT(sel);
  printf("%d  B[%c]\n", sel, b.trans=TRANSPOSE[sel]);
  c.trans  = 'n';
  t.trans  = 'n';


  strcpy(d,"1");
  printf("Beta A \n");
  scanf("%s",d);
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  a.beta=atof(d)+0*I;
  printf("B[%e+i%e]\n", creal(a.beta),cimag(a.beta));
#else
  a.beta=atof(d);
  printf("B[%e]\n", (double)a.beta);
#endif
  printf("Beta B \n");
  scanf("%s",d);
  printf("Beta C \n");
  scanf("%s",d);
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  b.beta=atof(d)+0*I;
  printf("B[%e+i%e]\n", creal(b.beta),cimag(b.beta));
#else
  b.beta=atof(d);
  printf("B[%e]\n",  (double)a.beta);
#endif
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  t.beta=c.beta=atof(d)+0*I;
  printf("B[%e+i%e]\n", creal(c.beta),cimag(c.beta));
#else
  t.beta=c.beta=atof(d);
  printf("C[%e]\n",  (double)c.beta);
#endif


  printf("Size %d float %d double %d complex %d z-complex %d cpu_set_t %d long %d int %d short %d\n", \
	 sizeof(Mat), sizeof(float),sizeof(double), sizeof(float complex) , sizeof(double complex),
	 sizeof(cpu_set_t), sizeof(long),sizeof(int), sizeof(short));
  
  printf("<a.m,a.n,b.m,b.n> ?\n");
  scanf("%d %d %d %d", &a.M,&a.N,&b.M,&b.N);

#if(PADDING)
#if(ROW_MAJOR)
  a.N = a.N+(a.N%64);
  b.N = b.N+(b.N%64);
  b.M = a.N;
#elif(COLUMN_MAJOR)
  a.M = a.M+(a.M%64);
  b.M = b.M+(b.M%64);
  a.N = b.M;
#endif  
#endif
#ifdef CLBLAS
  c.gpu = -1; b.gpu = -1; a.gpu =-1;
#endif
  
  a.m=a.M ; a.n=a.N ;
  b.m=b.M ; b.n=b.N ;
  if (a.trans=='n') {
    t.m =t.M= c.m=c.M =a.M; 
  }
  else {
    t.m =t.M= c.m=c.M =a.N;
  }
  if (b.trans=='n') {
    t.n =t.N= c.n=c.N =b.N;
  }
  else {
    t.n =t.N =c.n=c.N =b.M;
  }

  printf(" size of the matrix element %d\n", sizeof(Mat));
  printf(" You selected the following problem \n");
#if CLBLAS
  printf("      A %d x %d gpu %d\n",a.m,a.n,a.gpu);
  printf("      B %d x %d gpu %d\n",b.m,b.n,b.gpu);
  printf(" Thus C %d x %d gpu %d\n",c.m,c.n,c.gpu);
#else
  printf("      A %d x %d\n",a.m,a.n);
  printf("      B %d x %d\n",b.m,b.n);
  printf(" Thus C %d x %d\n",c.m,c.n);
#endif
  if (a.trans == 'n' && b.trans == 'n' && a.n != b.m ) { 
    printf(" N N wrong sizes ... a.n != b.m\n");
    return 0;
  }
  if (a.trans != 'n' && b.trans == 'n' && a.m != b.m ) { 
    printf("T N wrong sizes ... a.m != b.m\n");
    return 0;
  }
  if (a.trans != 'n' && b.trans != 'n' && a.m != b.n ) { 
    printf("T T wrong sizes ... a.m != b.n\n");
    return 0;
  }
  if (a.trans == 'n' && b.trans != 'n' && a.n != b.n ) { 
    printf("N T wrong sizes ... a.n != b.n\n");
    return 0;
  }
   
  printf("Creation ...\n");


#if(CLBLAS & PADDING)
  a.data    = (Mat *)   PALLOC(a);
  b.data    = (Mat *)   PALLOC(b);
  c.data    = (Mat *)   PALLOC(c);
#ifdef ADAPTIVE
  t.data    = (Mat *) PALLOC(t);
#endif
#else
  a.data    = (Mat *) CALLOC(a);
  b.data    = (Mat *) CALLOC(b);
  c.data    = (Mat *) CALLOC(c);
  t.data    = (Mat *) CALLOC(c);

#endif
	
  printf("Initialization ...\n");
  
  randomInitialization(a,rand(),rand());
  
  printf("A - \n");
  //  print(a);
  
  randomInitialization(b,rand(),rand());
  printf("B - \n");
  //print(b);
  randomInitialization(c,rand(),rand());
  printf("C - \n");
  //print(c);


#if(CLBLAS||FPGA)
  {
    printf(" size_t %d\n", sizeof(size_t));
    int platform=0;
    printf("platform ->");
    scanf("%d",&platform);
    printf(" %d\n", platform);
    set_platform_and_devices(platform);
  }
#endif

#if(FPGA)
  printf("Host\n");
  
  
  MakeFCNHost("../../../gemx/fcn/out_hw/gemx.xclbin", "gemxKernel_0", "vu9p");  
#endif 

  
#ifdef MYSCHED


  sched_getaffinity(0,sizeof(current_mask),&(current_mask));
  num_cpus = CPU_COUNT(&current_mask);
  printf("Counts before %d < %d \n",num_cpus,CPU_SETSIZE) ;
  for (cpu = 0; cpu < CPU_SETSIZE && cpu<num_cpus ; cpu += 1) {
    if (cpu%64==0) {printf("\n");}
    printf("%d",CPU_ISSET(cpu, &current_mask));
  }
  scanf("%d",&num_cpus);
  scanf("%s",_ps);
  
    
  printf("\nnum_cpus %d and strlen(_ps)=%d \n", num_cpus,strlen(_ps));

  /*
  cpusetp = __CPU_ALLOC(num_cpus);
  if (cpusetp == NULL) {
    perror("CPU_ALLOC");
    exit(EXIT_FAILURE);
  }
  
  size = __CPU_ALLOC_SIZE(num_cpus);
  */
  CPU_ZERO(&mask_t);
  for (cpu = 0; cpu < num_cpus && cpu < strlen(_ps); cpu += 1)
    if (_ps[cpu]=='1') CPU_SET(cpu, &mask_t);
  
  sched_setaffinity(0,sizeof(mask_t),&mask_t);
  printf("\nCounts after\n") ;
  //sched_setaffinity(0,sizeof(mask_t),&(mask_t));
  for (i=0;i<num_cpus && i < strlen(_ps);i++){
    printf("%d",CPU_ISSET(i, &mask_t));
  }
  printf("\nCounts after\n") ;
  for (i=0;i<strlen(_ps);i++){
    printf("%c",_ps[i]);
  }
  printf("\nSched done\n");
  sched_getaffinity(0,sizeof(current_mask),&(current_mask));
  num_cpus = CPU_COUNT(&current_mask);
  printf("Counts before %d < %d \n",num_cpus,CPU_SETSIZE) ;
  for (cpu = 0; cpu < CPU_SETSIZE && cpu<num_cpus ; cpu += 1) {
    if (cpu%64==0) {printf("\n");}
    printf("%d",CPU_ISSET(cpu, &current_mask));
  }
  
  
#endif

  
#ifdef ALPHA
  //  printf ("num threads %d\n", omp_get_num_threads());
  //printf ("dynamic  %d\n", omp_get_dynamic());


  printf("Addition ... \n");
  
  /*
  TIMING(CMC(c, =, a, mm_add, a),time_add,ADDINTERVAL);
  if (echo) printf(" Time %e \n", time_add);
  ops=(((double)(a.M))*(double)a.N);
  printf(" ADD OPS %e", ops);if (echo) printf("\n");
  mops_add = (ops/time_add)/(double)1000000;
  printf(" ADD MFLOPS %e", mops_add);if (echo) printf("\n");
  */

  print(a);
  print(b);
  print(c);
  TIMING(CMC(c, =, a, ptadd, b),time_add_2,ADDINTERVAL);
  if (echo) printf(" Time %e \n", time_add_2);
  ops=(((double)(b.M))*(double)b.N);
  printf(" ADD OPS %e", ops);if (echo) printf("\n");
  mops_add_2 = (ops/time_add_2)/(double)1000000000;
  printf(" PT  ADD GFLOPS %e", mops_add_2);if (echo) printf("\n");
  

  TIMING(CMC(c, =, a, add_amd, b),time_add,ADDINTERVAL);
  if (echo) printf(" Time %e \n", time_add);
  ops=(((double)(a.M))*(double)a.N);
  printf(" ADD OPS %e", ops);if (echo) printf("\n");
  mops_add = (ops/time_add)/(double)1000000000;
  printf(" ADD GFLOPS %e", mops_add);if (echo) printf("\n");

  
  mops_add = (mops_add>mops_add_2)?mops_add:mops_add_2; 

#endif


  

  printf("\n MUL ... \n");
#ifdef CLBLAS
#if(M23_TEST || M99_TEST || M343_TEST || M49_TEST || M7_TEST)
  {

    scanf("%d",&left);
    scanf("%d",&right);
    intgpus = gpus+left;
    right = right -left;
    printf("%d %d \n", left,right); 
  }
#else
  {
    scanf("%d",&c.gpu);
    if (ngpus == 1 || c.gpu != -1) {
      printf("GPU: %d\n", c.gpu); 
    }
    else {
      printf("GPUs: "); for (int i=0; i< ngpus; i++) printf(" %d", gpus[i]); printf("\n");
    }
    
  }
  
#endif
#endif
#ifdef M7_TEST
  
  TIMING_COLD({					\
      generate_queue(c,a,b,intgpus,right,2,_alpha2,_beta2,_gamma2,PP);
    }						\
    ,time_mul,MULINTERVAL);
#endif  
#ifdef M23_TEST
  
  TIMING_COLD({					\
      generate_queue(c,a,b,intgpus,right,3,_alpha3,_beta3,_gamma3,PP);
    }						\
    ,time_mul,MULINTERVAL);
#endif  
#ifdef M49_TEST
  
  TIMING_COLD({					\
      generate_queue(c,a,b,intgpus,right,4,_alpha4,_beta4,_gamma4,PP);
    }						\
    ,time_mul,MULINTERVAL);
#endif

#ifdef M99_TEST
  
  TIMING_COLD({					\
      generate_queue(c,a,b,intgpus,right,5,_alpha5,_beta5,_gamma5,PP);
    }						\
    ,time_mul,MULINTERVAL);
#endif  
#ifdef M343_TEST
  
  TIMING_COLD({					\
      generate_queue(c,a,b,intgpus,right,8,_alpha8,_beta8,_gamma8,PP);
    }						\
    ,time_mul,MULINTERVAL);
#endif  
#ifdef GOTOS_TEST   
  TIMING_COLD(CMC(c, =, a, mm_leaf_computation, b),time_mul,MULINTERVAL);
#endif  
#ifdef RMUL_TEST   
  TIMING_COLD(CMC(c, =, a, Rmul, b),time_mul,MULINTERVAL);
#endif  
#ifdef WM_PIPE_TEST   
  TIMING_COLD(wmpipe(c, a, b,0),time_mul,MULINTERVAL);
#endif  
#ifdef MARCO_PIPE_TEST   
  TIMING_COLD(BMOWR_PIPE (c, a, b,0),time_mul,MULINTERVAL);
#endif  
#ifdef MARCO_PIPE_TEST_2   
  TIMING_COLD(bmpipe (c, a, b,0),time_mul,MULINTERVAL);
#endif  
#ifdef MARCO_TEST   
  TIMING_COLD(BMOWR(c, a, b),time_mul,MULINTERVAL);
#endif  
#ifdef MARCO_TEST_2   
  TIMING_COLD(bm(c, a, b),time_mul,MULINTERVAL);
#endif  
#ifdef SM_PIPE_TEST   
  TIMING_COLD(smpipe(c, a, b,0),time_mul,MULINTERVAL);
#endif  
#ifdef GOTOS_TEST_3M
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)  
  TIMING_COLD(CMC(c, =, a, mm_leaf_computation_3m, b),time_mul,MULINTERVAL);
#endif  
#endif  
#ifdef SMUL_TEST
  TIMING_COLD(CMC(c, =, a,smul , b),time_mul,MULINTERVAL);
#endif
#ifdef WMUL_TEST
  TIMING_COLD(CMC(c, =, a,wmul , b),time_mul,MULINTERVAL);
#endif
#ifdef WMUL_OPT_TEST
  TIMING_COLD(CMC(c, =, a,wm , b),time_mul,MULINTERVAL);
#endif
#ifdef OMUL_TEST
  TIMING_COLD(CMC(c, =, a,omul , b),time_mul,MULINTERVAL);
#endif
#ifdef OWMUL_TEST
  TIMING_COLD(CMC(c, =, a,owmul , b),time_mul,MULINTERVAL);
#endif

  //  fastCPU();  

  if (echo) printf(" Time Cold %e \n", time_mul);
  ops = ((double)2*c.M)*((double)c.N*(double)((b.trans=='n')?b.M:b.N));
  printf(" MUL OPS %e", ops);if (echo) printf("\n");
  mops_mul=(ops/time_mul)/(double)1000000000;
  printf(" %s OPS %e GFLOPS COLD %e", program, ops, mops_mul);if (echo) printf("\n");

#ifdef M7_TEST
  TIMING_ITER({					\
      generate_queue(c,a,b,intgpus,right,2,_alpha2,_beta2,_gamma2,PP);
    }						\
    ,time_mul,MULINTERVAL,mask);
#endif  
#ifdef M23_TEST
  TIMING_ITER({					\
      generate_queue(c,a,b,intgpus,right,3,_alpha3,_beta3,_gamma3,PP);
    }						\
    ,time_mul,MULINTERVAL,mask);
#endif  
#ifdef M49_TEST
  TIMING_ITER({					\
      generate_queue(c,a,b,intgpus,right,4,_alpha4,_beta4,_gamma4,PP);
    }						\
    ,time_mul,MULINTERVAL,mask);
#endif  
#ifdef M99_TEST
  TIMING_ITER({					\
      generate_queue(c,a,b,intgpus,right,5,_alpha5,_beta5,_gamma5,PP);
    }						\
    ,time_mul,MULINTERVAL,mask);
#endif  
#ifdef M343_TEST
  TIMING_ITER({					\
      generate_queue(c,a,b,intgpus,right,8,_alpha8,_beta8,_gamma8,PP);
    }						\
    ,time_mul,MULINTERVAL,mask);
#endif  
#ifdef RMUL_TEST   
  TIMING_ITER(CMC(c, =, a, Rmul, b),time_mul,MULINTERVAL, mask);
#endif  
#ifdef GOTOS_TEST   
  TIMING_ITER(CMC(c, =, a, mm_leaf_computation, b),time_mul,MULINTERVAL, mask);
#endif  
#ifdef WM_PIPE_TEST   
  TIMING_ITER(wmpipe(c, a, b,0),time_mul,MULINTERVAL, mask);
#endif  
#ifdef SM_PIPE_TEST   
  TIMING_ITER(smpipe(c, a, b,0),time_mul,MULINTERVAL, mask);
#endif  
#ifdef GOTOS_TEST_3M
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)  
  TIMING_ITER(CMC(c, =, a, mm_leaf_computation_3m, b),time_mul,MULINTERVAL, mask);
#endif  
#endif  
#ifdef SMUL_TEST
  TIMING_ITER(CMC(c, =, a,smul , b),time_mul,MULINTERVAL, mask);
#endif
#ifdef MARCO_PIPE_TEST_2   
  TIMING_ITER(bmpipe(c, a, b,0),time_mul,MULINTERVAL, mask);
#endif  
#ifdef MARCO_PIPE_TEST   
  TIMING_ITER(BMOWR_PIPE(c, a, b,0),time_mul,MULINTERVAL, mask);
#endif  
#ifdef MARCO_TEST   
  TIMING_ITER(CMC(c, =, a,BMOWR , b),time_mul,MULINTERVAL, mask);
#endif  
#ifdef MARCO_TEST_2   
  TIMING_ITER(CMC(c, =, a, bm , b),time_mul,MULINTERVAL, mask);
#endif  
#ifdef WMUL_TEST
  TIMING_ITER(CMC(c, =, a,wmul , b),time_mul,MULINTERVAL, mask);
#endif
#ifdef WMUL_OPT_TEST
  TIMING_ITER(CMC(c, =, a,wm , b),time_mul,MULINTERVAL, mask);
#endif
#ifdef OMUL_TEST
  TIMING_ITER(CMC(c, =, a,omul , b),time_mul,MULINTERVAL, mask);
#endif
#ifdef OWMUL_TEST
  TIMING_ITER(CMC(c, =, a,owmul , b),time_mul,MULINTERVAL, mask);
#endif


  if (echo) printf(" Time HOT %e \n", time_mul);
  ops = ((double)2*c.M)*((double)c.N*(double)((b.trans=='n')?b.M:b.N));
  printf(" MUL OPS %e", ops);if (echo) printf("\n");
  mops_mul=(ops/time_mul)/(double)1000000000;
  printf(" %s OPS %e GFLOPS HOT  %e", program, ops, mops_mul);if (echo) printf("\n");


#ifdef ALPHA
  printf("22*pi/alpha = %e\n", (((double)22)*mops_mul)/mops_add);
#endif
#ifdef ADAPTIVE
  copy(t,c);
  printf("T - \n");
  //print(t);

  printf("Adaptive\n");
  //  TIMING_ITER(CMC(t, =, a,wm , b),time_mul,MULINTERVAL, mask);
  TIMING_ITER(adaptive_wm(t,a,b,(int)(mops_mul/mops_add)),time_mul,MULINTERVAL, mask)
    //  debug=1;
    //adaptive_smul(t,a,b,(int)(mops_mul/mops_add));
    //debug=0;
  //CMC(t, =, a,wm , b);
  if (echo) printf(" Time %e \n", time_mul);
  ops = ((double)2*c.M)*((double)c.N*(double)((b.trans=='n')?b.M:b.N));
  printf(" MUL OPS %e", ops);if (echo) printf("\n");
  mops_mul=(ops/time_mul)/(double)1000000000;
  printf(" %s OPS %e GFLOPS %e", program, ops, mops_mul);if (echo) printf("\n");

  printf("Comparison ... \n");
  if (comp(t, c)) 
    printf(" Failure  !!!\n");
  else 
    printf(" Success \n");



#endif


  FREE(a.data);
  FREE(b.data);
  FREE(c.data);

#ifdef SCALING
  closeCpuScalingDriver();
#endif

#ifdef CLBLAS
  relase_devices_names();
  //release_blas_context();
#endif
#ifdef MYSCHED
  
  //__CPU_FREE(cpusetp);
#endif
  
  return 0;
}
