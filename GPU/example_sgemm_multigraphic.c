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

#ifndef DATATYPE 
#define DATATYPE cl_float
#define ALPHA 10.0
#define BETA  10.0
#define GEMM  clblasSgemm
#endif



#define DEVICES 6
#include <header.h>




int
main(int argc, char **argv)
{
    cl_int err;
    int  platform = 0;
    cl_device_id device[DEVICES];
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue[DEVICES];
    cl_mem bufA[DEVICES], bufB[DEVICES], bufC[DEVICES];
    int ret = 0;
    int i,j;
    cl_uint ndevices;
    int Times = 10;
    int M =  500;
    int N = 500;
    int K = 500;
    int gpu =1;
    pthread_t  p_thread[NUM_THREADS]; /* thread's structure */
    pthread_attr_t attr;
    DCMul    d[NUM_THREADS];
    int gpu2 = DEVICES;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    int REUSEB;
    cl_uint platformCount;
    cl_platform_id* platforms;
    
    


    //printf("ARGC %d \n", argc);
    //for (i=0; i<argc;i++) 
    //  printf("%s \n ", argv[i]);

    platform = atoi(argv[1]);
    if (argc==7) {
      gpu = atoi(argv[2]);
      M = atoi(argv[3]);
      N = atoi(argv[4]);
      K = atoi(argv[5]);
      Times = atoi(argv[6]);
    } else 
    if (argc==8) {
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
      REUSEB= atoi(argv[8]);
    }
      
    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);

    
    err = clGetDeviceIDs(platforms[platform], CL_DEVICE_TYPE_GPU, 6, device,&ndevices);
    if (gpu2 > ndevices) gpu2= ndevices;
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return 1;
    } else { 

      deviceInformation( device,ndevices);
      printf("N of GPUS %d \n",ndevices);
      // for each device print critical attributes


    }

    if (M%(gpu2-gpu) != 0) {
      M = M +(M%(gpu2-gpu));
    }
    printf("initialize matrices\n");

    
#ifndef COMPLEX
    DATATYPE *A = (DATATYPE*) malloc(M*K*sizeof(DATATYPE));
    DATATYPE *B  = (DATATYPE*) malloc(N*K*sizeof(DATATYPE));
    DATATYPE *C = (DATATYPE*) malloc(M*N*sizeof(DATATYPE));
    for (i=0;i<M;i++)
      for (j=0;j<K;j++) 
	A[i*K+j] = 1.0/(i+j+1);
    for (i=0;i<K;i++)
      for (j=0;j<N;j++) 
	B[i*N+j] = 1.0/(i+j+1);
    for (i=0;i<M;i++)
      for (j=0;j<N;j++) 
	C[i*N+j] = 1.0/(i+j+1);
#else
    MDATATYPE *A       = (MDATATYPE*) malloc(M*K*sizeof(DATATYPE));
    MDATATYPE *B       = (MDATATYPE*) malloc(N*K*sizeof(DATATYPE));
    MDATATYPE *C       = (MDATATYPE*) malloc(M*N*sizeof(DATATYPE));
    { int n;
      
#ifndef QF
      for (n=0;n<M;n++)
	for (j=0;j<K;j++) 
	  A[n*K+j] = 1.0/(n+j+1)+i*1.0/(n+j+1);
      for (n=0;n<K;n++)
	for (j=0;j<N;j++) 
	  B[n*N+j] = 1.0/(n+j+1)+i*1.0/(n+j+1);
      for (n=0;n<M;n++)
	for (j=0;j<N;j++) 
	  C[n*N+j] = 1.0/(n+j+1)+i*1.0/(n+j+1);
#else
      for (n=0;n<M;n++)
	for (j=0;j<K;j++) 
	  A[n*K+j] = QF(1.0/(n+j+1),i*1.0/(n+j+1));
      for (n=0;n<K;n++)
	for (j=0;j<N;j++) 
	  B[n*N+j] = QF(1.0/(n+j+1),i*1.0/(n+j+1));
      for (n=0;n<M;n++)
	for (j=0;j<N;j++) 
	  C[n*N+j] = QF(1.0/(n+j+1),i*1.0/(n+j+1));
#endif
      
    }
#endif


    
    printf("initialize done \n");


    

    props[1] = (cl_context_properties)platforms[platform];
    ctx = clCreateContext(props, ndevices , device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return 1;
    }

    
    for (j =gpu; j<gpu2;j++){ 

      queue[j] = clCreateCommandQueue(ctx, device[j], 0, &err);
      
      bufA[j] = clCreateBuffer(ctx, CL_MEM_READ_ONLY, M/(gpu2-gpu) * K * sizeof(*A),
			       NULL, &err);
      bufB[j] = clCreateBuffer(ctx, CL_MEM_READ_ONLY, K * N * sizeof(*B),      
			       NULL, &err);
      bufC[j] = clCreateBuffer(ctx, CL_MEM_READ_WRITE, M/(gpu2-gpu) * N * sizeof(*C),
			       NULL, &err);
      if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return 1;
      }
    }

    /* Setup clblas. */
    err = clAmdBlasSetup();
    if (err != CL_SUCCESS) {
        printf("clblasSetup() failed with %d\n", err);
        for (j =gpu; j<gpu2;j++)
	  clReleaseCommandQueue(queue[j]);
        clReleaseContext(ctx);
        return 1;
    }
    printf("Start %f %f %f \n",*A,*B,*C);
    for (j=gpu; j<gpu2; j++)  {
      printf("Qs %lu \n",(long unsigned int)queue[j]);
      printf("bufA %lu bufB %lu bufC %lu \n",(long unsigned int)bufA[j],(long unsigned int)bufB[j],
	     (long unsigned int)bufC[j]);
    }

    
    START_CLOCK;
    


    /* Prepare OpenCL memory objects and place matrices inside them. */
 
    for (i=0; i<Times; i++) {
  
      if (DEBUG) printf("basic computation\n");
      for (j=gpu; j<gpu2;j++) {

	d[j].id = device[j]; 
	d[j].queue = queue[j];
	d[j].bufA=bufA[j];
	d[j].bufB=bufB[j];
	d[j].bufC=bufC[j];
	d[j].A=A+(j-gpu)*M/(gpu2-gpu)*K;
	d[j].B=B;
	d[j].C=C+(j-gpu)*M/(gpu2-gpu)*N;
	d[j].M=M/(gpu2-gpu);
	d[j].N=N;
	d[j].K=K;
	d[j].result = REUSEB;
	d[j].self = j;
	d[j].sibling = gpu2-j;
	


      
	if (DEBUG) printf("%d basic computation %d\n",i,j);
	pthread_create(&p_thread[j],
		       &attr,
		       basic_mul_computation_thread,
		       (void *)(&d[j]));                                                                                                                                               
      }

      /* wait for the threads to complete */
      for (j = 1; j<gpu2; j++){
	pthread_join(p_thread[j], NULL);
      }
      
    }
    
    END_CLOCK;
    
    printf("T %d-%d GFLOPS %f \n", gpu,gpu2, Times*(M/1000.0)*(N/1000.0)*(K/1000.0)*2/duration );
    /* Release OpenCL memory objects. */
    
    for (j=gpu;j<gpu2;j++) { 
      clReleaseMemObject(bufC[j]);
      clReleaseMemObject(bufB[j]);
      clReleaseMemObject(bufA[j]);
    }	   
    
    /* Finalize work with clblas. */
    clAmdBlasTeardown();
    
    
    /* Release OpenCL working objects. */
    for (j=gpu;j<gpu2;j++) { 
      clReleaseCommandQueue(queue[j]);
    }
    clReleaseContext(ctx);
    printf("done\n");
    return ret;
}
