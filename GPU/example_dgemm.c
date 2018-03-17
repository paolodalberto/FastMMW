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

#ifdef GETTIME
#include <sys/time.h>
struct timeval _t1,_t2;
double duration;

#define START_CLOCK   gettimeofday(&_t1,NULL ); 
#define END_CLOCK   gettimeofday(&_t2,NULL);   duration = (_t2.tv_sec-_t1.tv_sec)+ (double)(_t2.tv_usec-_t1.tv_usec)/1000000;    printf("----------> get time %e sec<------\n",duration); 
#endif /*  GETTIME */


#ifdef CLOCK
#include <time.h>
clock_t _t1,_t2;
double duration;

#define START_CLOCK   _t1 = clock(); 
#define END_CLOCK     _t2 = clock(); duration =  ((double)(_t2-_t1))/CLOCKS_PER_SEC; \
  printf("clock time %e s \n", duration); 
#endif

#define TEMP temp,  cM, cN, cM, cN
#define INTERVAL (45)   /* two minutes */


/************************************************
 * This is a timing procedure very common in CMU
 * Notice that we execute X once before we start timing.
 *
 */
 
#define TIMING(X,time, interval) { int i,j;	\
    j=1;					\
    X;						\
    do {					\
      j*=2;					\
      START_CLOCK;				\
      for (i=0;i<j;i++) { X;  }			\
      END_CLOCK;				\
      time = duration/j;			\
      printf(" average %f\n",time);		\
    } while (duration<interval);		\
  }
#define TIMING_ITER(X,time, interval,times) { int i,j;	\
    j=1;					\
    X;						\
    do {					\
      j*=2;					\
      START_CLOCK;				\
      for (i=0;i<j;i++) { X;  }			\
      END_CLOCK;				\
      time = duration/j;			\
      printf(" average %f times %d \n",time,j);		\
    } while (duration <interval || j<times);		\
  }

#define TIMING_COLD(X,time, interval) {		\
    START_CLOCK;				\
    X;						\
    END_CLOCK;					\
    time = duration;				\
    printf(" average %f\n",time);		\
  }

#include <sys/types.h>
#include <stdio.h>
#include <string.h>

/* Include CLBLAS header. It automatically includes needed OpenCL header,
 * so we can drop out explicit inclusion of cl.h header.
 */
#include <clAmdBlas.h>

/* This example uses predefined matrices and their characteristics for
 * simplicity purpose.
 */

#define M  2000
#define N  2000
#define K  2000

static const clAmdBlasOrder order = clAmdBlasRowMajor;

static const cl_double alpha = 10;

static const clAmdBlasTranspose transA = clAmdBlasNoTrans;
cl_double A[M*K];

static const size_t lda = K;        /* i.e. lda = K */

static const clAmdBlasTranspose transB = clAmdBlasNoTrans;
cl_double B[K*N];

static const size_t ldb = N;        /* i.e. ldb = N */

static const cl_double beta = 20;

cl_double C[M*N];
static const size_t ldc = N;        /* i.e. ldc = N */

static cl_double result[M*N];

static const size_t off  = 1;
static const size_t offA = K + 1;   /* K + off */
static const size_t offB = N + 1;   /* N + off */
static const size_t offC = N + 1;   /* N + off */

static void
printResult(const char* str)
{
    size_t i, j, nrows;

    printf("%s:\n", str);

    nrows = (sizeof(result) / sizeof(cl_double)) / ldc;
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ldc; j++) {
            printf("%f ", result[i * ldc + j]);
        }
        printf("\n");
    }
}

int
main(void)
{
    cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue = 0;
    cl_mem bufA, bufB, bufC;
    cl_event event = NULL;
    int ret = 0;

    int i,j;
    for (i=0;i<M;i++)
      for (j=0;j<K;j++) 
	A[i*K+j] = 1.0/(i+j+1);
    for (i=0;i<K;i++)
      for (j=0;j<N;j++) 
	B[i*N+j] = 1.0/(i+j+1);
    for (i=0;i<M;i++)
      for (j=0;j<N;j++) 
	C[i*N+j] = 1.0/(i+j+1);
    
	  
    printf("Start \n");

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return 1;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return 1;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return 1;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
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

    START_CLOCK


    /* Prepare OpenCL memory objects and place matrices inside them. */
    bufA = clCreateBuffer(ctx, CL_MEM_READ_ONLY, M * K * sizeof(*A),
                          NULL, &err);
    bufB = clCreateBuffer(ctx, CL_MEM_READ_ONLY, K * N * sizeof(*B),
                          NULL, &err);
    bufC = clCreateBuffer(ctx, CL_MEM_READ_WRITE, M * N * sizeof(*C),
                          NULL, &err);

    err = clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0,
        M * K * sizeof(*A), A, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0,
        K * N * sizeof(*B), B, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0,
        M * N * sizeof(*C), C, 0, NULL, NULL);


    /* Call clblas extended function. Perform gemm for the lower right sub-matrices */
    err = clAmdBlasDgemm(order, transA, transB, M, N, K, alpha, bufA,
                         lda, bufB, ldb, beta, bufC, ldc, 1, &queue,
                         0, NULL, &event);
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
        err = clWaitForEvents(1, &event);

        /* Fetch results of calculations from GPU memory. */
        err = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0,
                                  M * N * sizeof(*result),
                                  result, 0, NULL, NULL);

        /* At this point you will get the result of SGEMM placed in 'result' array. */
        puts("");
        //printResult("clblasSgemmEx result");
    }

    /* Release OpenCL memory objects. */
    clReleaseMemObject(bufC);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufA);

    /* Finalize work with clblas. */
    clAmdBlasTeardown();

    END_CLOCK;
    
    printf("GFLOPS %f \n", (M/1000.0)*(N/1000.0)*(K/1000.0)*2/duration );
	   
      


    /* Release OpenCL working objects. */
    clReleaseCommandQueue(queue);
    clReleaseContext(ctx);
    printf("done\n");
    return ret;
}
