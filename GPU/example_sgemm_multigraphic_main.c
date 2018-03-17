/* ************************************************************************
 * Copyright 2013 Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ************************************************************************/


#define GETTIME
#include <architecture.h>
#include <mat-operands.h>
#include <mat-mulkernels.h>
#include <mat-addkernels.h>
#include <string.h>
#include <clAmdBlas.h>
#include <gpuCompute.h>
#include <dgemm_multigraphic.h>
#include <stdlib.h>

/*
extern int gpus[1];
extern int ngpus;
extern int weights[DEVICES] ,sizes[DEVICES], indexes[DEVICES];
extern cl_context ctx;
extern cl_device_id device[DEVICES];

extern int PARALLEL;
void *basic_mul_computation_gpugemm(void *arg);

static int DEBUG = 1; 
*/
  
static void randomInitialization(DEF(a), int seed1, int seed2) { 
  int i,j;

#ifdef ROW_MAJOR
  for (i=0;i<a.M;i++)
    for (j=0;j<a.N;j++) 
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      a.data[i*a.N+j] = (((rand()+i+j)&1)?1:-1)*(rand()*seed1*(i+1)*(j+1)*11+i*7*seed2-j+3)%11;
#else
  a.data[i*a.N+j] = (((rand()+i+j)&1)?1:-1)*((seed1*rand()*(i+1)*(j+1)*11+i*7-j+3)%11) +
    (((rand()+i+j)&1)?1:-1)*((rand()*(i+1)*(j+1)*11*seed2+i*7-j+3)%11)*I;
#endif
#else
  for (i=0;i<a.N;i++)
    for (j=0;j<a.M;j++) 
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      a.data[i*a.M+j] = (((rand()+i+j)&1)?1:-1)*((rand()*seed1*(i+1)*(j+1)*11+i*7*seed2-j+3)%11);
#else
  a.data[i*a.M+j] = (((rand()+i+j)&1)?1:-1)*((seed1*rand()*(i+1)*(j+1)*11+i*7-j+3)%11) 
    +(((rand()+i+j)&1)?1:-1)*((rand()*(i+1)*(j+1)*11*seed2+i*7-j+3)%11)*I;
#endif
#endif
  
}


int
main(int argc, char **argv)
{
    cl_int err;
    int platform=0;
    int ret = 0;
    int i,j; 
    int Times = 10;
    int M =  500;
    int N = 500;
    int K = 500;
    int gpu =1, gpu2 = 1;

    Matrix A,B,C;





    
    printf("ARGC %d \n", argc);
    for (i=0; i<argc;i++) 
      printf("%s \n ", argv[i]);

    platform = atoi(argv[1]);
    if (argc==7) {
      gpu = atoi(argv[2]);
      M = atoi(argv[3]);
      N = atoi(argv[4]);
      K = atoi(argv[5]);
      Times = atoi(argv[6]);
    } else   if (argc==8) {
      gpu = atoi(argv[2]);
      M = atoi(argv[3]);
      N = atoi(argv[4]);
      K = atoi(argv[5]);
      Times = atoi(argv[6]);
      gpu2 = atoi(argv[7]);
    } else if (argc==9) {
      gpu = atoi(argv[2]);
      M = atoi(argv[3]);
      N = atoi(argv[4]);
      K = atoi(argv[5]);
      Times = atoi(argv[6]);
      gpu2 = atoi(argv[7]);
    }

    

    set_platform_and_devices(platform);
    gpus[0] = gpu;

    A.trans = B.trans = C.trans = 'n';
    

    printf("initialize matrices\n");
    A.m=A.M=M ; A.n=A.N=N ;
    B.m=B.M=N ; B.n=B.N=K ;
    if (A.trans=='n') {
      C.m=C.M =A.M; 
    }
    else {
      C.m=C.M =A.N;
    }
    if (B.trans=='n') {
      C.n=C.N =B.N;
    }
    else {
      C.n=C.N =B.M;
    }

    printf(" size of the matrix element %d\n", sizeof(Mat));
    printf(" You selected the following problem \n");
    printf("      A %d x %d \n",A.m,A.n);
    printf("      B %d x %d \n",B.m,B.n);
    printf(" Thus C %d x %d \n",C.m,C.n);

    
    A.data = (Mat*) malloc(M*K*sizeof(Mat));
    B.data = (Mat*) malloc(N*K*sizeof(Mat));
    C.data = (Mat*) malloc(M*N*sizeof(Mat));

    randomInitialization(A,rand(),rand());
    
    printf("A - \n");
    //  print(a);
    
    randomInitialization(B,rand(),rand());
    printf("B - \n");
    //print(b);
    randomInitialization(C,rand(),rand());
    printf("C - \n");
    
    
    Times=1;
    
    START_CLOCK;

    {
      int NN;
      C.beta = _zero;
      
      if (DEBUG) printf("Initialize \n ");
      INITIALIZE;

      if (DEBUG) printf("Shape %d - %d  ",gpus[0],gpus[ngpus-1]);
      
#if(COLUMN_MAJOR)
      NN = shapes(gpus[0],gpus[ngpus-1],C.m,DEVICES, weights,sizes,indexes);
      if (DEBUG) printf("QUEUE %d \n ", NN);
      QUEUEIT(1,NN,NN);
#elif(ROW_MAJOR)
      NN = shapes(gpus[0],gpus[ngpus-1],C.n,DEVICES, weights,sizes,indexes);
      if (DEBUG) printf("QUEUE %d \n ", NN);
      QUEUEIT(NN,1,NN);
#endif
      
      if (DEBUG) printf("Partition GEMM\n ");
      /* Prepare OpenCL memory objects and place matrices inside them. */
      

      for (j=0; j<NN;j++) {
	if (DEBUG) printf("basic computation %d %d \n", j,gpus[j]);

      
	d[j].id = device[gpus[j]]; 
	d[j].queue = queue[gpus[j]];
	d[j].bufA=bufA[gpus[j]];    d[j].bufB=bufB[gpus[j]];    d[j].bufC=bufC[gpus[j]];
	
#if(COLUMN_MAJOR)
	d[j].A=A;
	d[j].B=B; d[j].B.n /=NN;
	d[j].B.data=B.data+j*B.M*B.n/NN;
	d[j].C=C; d[j].C.n /=NN;  d[j].C.data= C.data+(j-1)*C.M*d[j].C.n/NN;
	d[j].result = 0;
#elif(ROW_MAJOR)
	d[j].A=A; d[j].A.m /=NN;  d[j].A.data= A.data+j*d[j].A.m*A.N;
	d[j].B=B; 
	d[j].C=C; d[j].C.m /=NN;  d[j].C.data= C.data+j*d[j].C.m*C.N;
	d[j].result = 0;
#endif
      }   

      if (DEBUG) printf("%d basic computation %d\n",i,j);
      
      if (PARALLEL) {
	for (j=0; j<NN;j++) {
	  thr_id[j] = pthread_create(&p_thread[j],
				     NULL, //&attr,
				     basic_mul_computation_gpugemm,
				     (void *)(&d[j]));
	  if(thr_id[j]) {
	    
	    printf("Error creating thread %d %d\n",j, thr_id[j]);
	    return 1;
	  }
	} 
	
	for (j = 0; j<NN; j++){						
	  pthread_join(p_thread[j], NULL);					
	}									
      }
      else { // not PARALLEL
	for (j=0; j<NN;j++) 
	  basic_mul_computation_gpugemm((void *)(&d[j]));
      }
      if (DEBUG) printf("Wait and release \n ");
      WAIT_AND_RELEASE;
      

      if (DEBUG) printf("done\n");
      return ret;
    }
    
    END_CLOCK;
    
    printf("N %d-%d GFLOPS %f \n", gpu,gpu2, Times*(M/1000.0)*(N/1000.0)*(K/1000.0)*2/duration );
    /* Release OpenCL memory objects. */
    
    FREE(A.data);
    FREE(B.data);
    FREE(C.data);
    


    release_blas_context();



    printf("done\n");
    return ret;
}
