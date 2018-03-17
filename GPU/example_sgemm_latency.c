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

#include <header.h>



int
main(int argc, char **argv)
{
    cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device[4];
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_mem bufA, bufB, bufC,bufCA,bufCB;

    int ret = 0;
    int i,j;
    cl_uint ndevices;
    int Times = 10;

    int M =  500;
    int N = 500;
    int K = 500;
    int gpu = 1;

    //printf("ARGC %d \n", argc);
    //for (i=0; i<argc;i++) 
    //  printf("%s \n ", argv[i]);
      
    if (argc==6) {

      gpu = atoi(argv[1]);
      M = atoi(argv[2]);
      N = atoi(argv[3]);
      K = atoi(argv[4]);
      Times = atoi(argv[5]);
    }
    size_t ldc = N;        /* i.e. ldc = N */
    size_t ldb = N;        /* i.e. ldb = N */
    size_t lda = K;        /* i.e. lda = K */


      

    
#ifndef COMPLEX
    DATATYPE *A = (DATATYPE*) malloc(M*K*sizeof(DATATYPE));
    DATATYPE *B  = (DATATYPE*) malloc(N*K*sizeof(DATATYPE));
    DATATYPE *C = (DATATYPE*) malloc(M*N*sizeof(DATATYPE));
    DATATYPE *result  = (DATATYPE*) malloc(M*N*sizeof(DATATYPE));
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
    MDATATYPE *result  = (MDATATYPE*) malloc(M*N*sizeof(DATATYPE));
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
	  


    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return 1;
    }

    
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 4, device,&ndevices);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return 1;
    } 
    

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, ndevices , device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return 1;
    }

    queue = clCreateCommandQueue(ctx, device[gpu], 0, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return 1;
    }

    /* Setup clblas. */
    err = clAmdBlasSetup();
    if (err != CL_SUCCESS) {
        printf("clblasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return 1;
    }
    printf("Start \n");
    START_CLOCK;
    /* Prepare OpenCL memory objects and place matrices inside them. */
    bufA = clCreateBuffer(ctx, CL_MEM_READ_ONLY, M * K * sizeof(*A),
			  NULL, &err);
    bufB = clCreateBuffer(ctx, CL_MEM_READ_ONLY, K * N * sizeof(*B),
			  NULL, &err);

    bufC  = clCreateBuffer(ctx, CL_MEM_READ_WRITE, M * N * sizeof(*C),
			   NULL, &err);
    bufCA = clCreateBuffer(ctx, CL_MEM_READ_WRITE, M * N * sizeof(*C),
			   NULL, &err);
    bufCB = clCreateBuffer(ctx, CL_MEM_READ_WRITE, M * (N-N/2) * sizeof(*C),
			   NULL, &err);
 
    for (i=0; i<Times; i++) {
      cl_event event[4*2];

      // first 

      err = clEnqueueWriteBuffer(queue, bufC, CL_FALSE, 0,M * N * sizeof(*C), C, 0, NULL, event +2);

      err = clEnqueueWriteBuffer(queue, bufB, CL_FALSE, 0,
				 K * N/2 * sizeof(*B), B, 0, NULL, event +1);

      err = clEnqueueWriteBuffer(queue, bufA, CL_FALSE, 0,
				 M * K * sizeof(*A), A, 0, NULL, event+0);
      
      
      checkErrors(err, "write  failed",0); 
      /* Call clblas extended function. Perform gemm for the lower right sub-matrices */
      err = GEMM(order, transA, transB, M, N/2, K, alpha, bufA, 0,
		 lda, bufB, 0,ldb, beta, bufC, 0,ldc, 1, &queue,
		 2, event, event+3);
      
      checkErrors(err, "gemm  failed",0); 
      // We try to hide the latency of this second half of B
      err = clEnqueueWriteBuffer(queue, bufB, CL_FALSE, K * (N/2) * sizeof(*B),
				 K * (N-N/2) * sizeof(*B), B+K * (N/2) * sizeof(*B), 0, NULL, event +2);
      
      err = GEMM(order, transA, transB, M, N, K, alpha, bufA, 0,
		 lda, bufB, K * (N/2) * sizeof(*B),ldb, beta, bufCA,  (N/2) * sizeof(*B),ldc, 1, &queue,
		 1, event+2, event+4);
      /* 
       err = clAmdBlasDgemm(order, transA, transB, M - off, N - off, K - off,
       alpha, bufA, offA, lda,
       bufB, offB, ldb, beta,
       bufC, offC, ldc,
       1, &queue, 0, NULL, &event); */
      
      if (err != CL_SUCCESS) {
        printf("clblasSgemmEx() failed with %d\n", err);
        ret = 1;
      }
      else {

	
        /* Wait for calculations to be finished. */
        err = clWaitForEvents(2, event+4);
	
        /* Fetch results of calculations from GPU memory. */
	
	err = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0,
				  M * N * sizeof(*result),
				  result, 0, NULL, NULL);
	
        /* At this point you will get the result of SGEMM placed in 'result' array. */
        //puts("");
        //printResult("clblasSgemmEx result");
    }
      
      
    }
    END_CLOCK;
    
    printf("%d GFLOPS %f \n", gpu, Times*(M/1000.0)*(N/1000.0)*(K/1000.0)*2/duration );
    /* Release OpenCL memory objects. */

    clReleaseMemObject(bufC);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufA);
	   
    
    /* Finalize work with clblas. */
    clAmdBlasTeardown();


    /* Release OpenCL working objects. */
    clReleaseCommandQueue(queue);
    clReleaseContext(ctx);
    printf("done\n");
    return ret;
}
