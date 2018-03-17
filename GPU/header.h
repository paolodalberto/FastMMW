#include <pthread.h>      
#include <complex.h>

#define NUM_THREADS 6
#define NUM_THREADS_L NUM_THREADS*4

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
    j=1;						\
    X;							\
    do {						\
      j*=2;						\
      START_CLOCK;					\
      for (i=0;i<j;i++) { X;  }				\
      END_CLOCK;					\
      time = duration/j;				\
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
  

static const DATATYPE            alpha = ALPHA;  
static const DATATYPE            beta  = BETA;
static const clAmdBlasOrder      order = clAmdBlasRowMajor;
static const clAmdBlasTranspose transA = clAmdBlasNoTrans;
static const clAmdBlasTranspose transB = clAmdBlasNoTrans;

 
  
  
  
void checkErrors(cl_int status, char *label, int line)
{
  switch (status)
    {
    case CL_SUCCESS:
      return;
    case CL_BUILD_PROGRAM_FAILURE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_BUILD_PROGRAM_FAILURE\n", label, line);
      break;
    case CL_COMPILER_NOT_AVAILABLE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_COMPILER_NOT_AVAILABLE\n", label, line);
      break;
      case CL_DEVICE_NOT_AVAILABLE:
        fprintf(stderr, "OpenCL error (at %s, line %d): CL_DEVICE_NOT_AVAILABLE\n", label, line);
        break;
    case CL_DEVICE_NOT_FOUND:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_DEVICE_NOT_FOUND\n", label, line);
      break;
    case CL_IMAGE_FORMAT_MISMATCH:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_IMAGE_FORMAT_MISMATCH\n", label, line);
      break;
    case CL_IMAGE_FORMAT_NOT_SUPPORTED:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_IMAGE_FORMAT_NOT_SUPPORTED\n", label, line);
      break;
    case CL_INVALID_ARG_INDEX:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_ARG_INDEX\n", label, line);
      break;
    case CL_INVALID_ARG_SIZE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_ARG_SIZE\n", label, line);
      break;
    case CL_INVALID_ARG_VALUE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_ARG_VALUE\n", label, line);
      break;
    case CL_INVALID_BINARY:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_BINARY\n", label, line);
      break;
    case CL_INVALID_BUFFER_SIZE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_BUFFER_SIZE\n", label, line);
      break;
    case CL_INVALID_BUILD_OPTIONS:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_BUILD_OPTIONS\n", label, line);
      break;
    case CL_INVALID_COMMAND_QUEUE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_COMMAND_QUEUE\n", label, line);
      break;
    case CL_INVALID_CONTEXT:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_CONTEXT\n", label, line);
      break;
    case CL_INVALID_DEVICE:
        fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_DEVICE\n", label, line);
        break;
    case CL_INVALID_DEVICE_TYPE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_DEVICE_TYPE\n", label, line);
      break;
    case CL_INVALID_EVENT:
        fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_EVENT\n", label, line);
        break;
    case CL_INVALID_EVENT_WAIT_LIST:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_EVENT_WAIT_LIST\n", label, line);
      break;
    case CL_INVALID_GL_OBJECT:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_GL_OBJECT\n", label, line);
      break;
    case CL_INVALID_GLOBAL_OFFSET:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_GLOBAL_OFFSET\n", label, line);
      break;
    case CL_INVALID_HOST_PTR:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_HOST_PTR\n", label, line);
      break;
    case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_IMAGE_FORMAT_DESCRIPTOR\n", label, line);
      break;
    case CL_INVALID_IMAGE_SIZE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_IMAGE_SIZE\n", label, line);
      break;
    case CL_INVALID_KERNEL_NAME:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_KERNEL_NAME\n", label, line);
      break;
    case CL_INVALID_KERNEL:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_KERNEL\n", label, line);
      break;
    case CL_INVALID_KERNEL_ARGS:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_KERNEL_ARGS\n", label, line);
        break;
    case CL_INVALID_KERNEL_DEFINITION:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_KERNEL_DEFINITION\n", label, line);
        break;
    case CL_INVALID_MEM_OBJECT:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_MEM_OBJECT\n", label, line);
      break;
    case CL_INVALID_OPERATION:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_OPERATION\n", label, line);
      break;
    case CL_INVALID_PLATFORM:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_PLATFORM\n", label, line);
      break;
    case CL_INVALID_PROGRAM:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_PROGRAM\n", label, line);
      break;
    case CL_INVALID_PROGRAM_EXECUTABLE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_PROGRAM_EXECUTABLE\n", label, line);
      break;
    case CL_INVALID_QUEUE_PROPERTIES:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_QUEUE_PROPERTIES\n", label, line);
      break;
    case CL_INVALID_SAMPLER:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_SAMPLER\n", label, line);
      break;
    case CL_INVALID_VALUE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_VALUE\n", label, line);
      break;
    case CL_INVALID_WORK_DIMENSION:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_WORK_DIMENSION\n", label, line);
      break;
    case CL_INVALID_WORK_GROUP_SIZE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_WORK_GROUP_SIZE\n", label, line);
      break;
      case CL_INVALID_WORK_ITEM_SIZE:
        fprintf(stderr, "OpenCL error (at %s, line %d): CL_INVALID_WORK_ITEM_SIZE\n", label, line);
        break;
    case CL_MAP_FAILURE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_MAP_FAILURE\n", label, line);
      break;
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_MEM_OBJECT_ALLOCATION_FAILURE\n", label, line);
      break;
    case CL_MEM_COPY_OVERLAP:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_MEM_COPY_OVERLAP\n", label, line);
      break;
    case CL_OUT_OF_HOST_MEMORY:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_OUT_OF_HOST_MEMORY\n", label, line);
      break;
    case CL_OUT_OF_RESOURCES:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_OUT_OF_RESOURCES\n", label, line);
      break;
    case CL_PROFILING_INFO_NOT_AVAILABLE:
      fprintf(stderr, "OpenCL error (at %s, line %d): CL_PROFILING_INFO_NOT_AVAILABLE\n", label, line);
      break;
    }
  exit(status);
}

#ifndef POORPRECISION
struct mul_data { 
  cl_device_id id;
  cl_command_queue queue;
  cl_mem bufA,bufB,bufC;
  DATATYPE *A,*B,*C;
  int M,N,K;
  int result;
  int self;
  int sibling;
  int warmup;
};
#else
struct mul_data { 
  cl_device_id id;
  cl_command_queue queue;
  cl_mem bufAH,bufBH,bufCH;
  cl_mem bufA,bufB,bufC;
  DATATYPE *A,*B,*C;
  int M,N,K;
  int result;
  int self;
  int sibling;
  int warmup;
  cl_kernel split;
  cl_kernel combine;
};
#endif
typedef struct mul_data DCMul;
  
#ifndef DEBUG 
#define DEBUG 0 
#endif

int deviceInformation(cl_device_id *device, int ndevices) { 
  char* value;
  size_t valueSize;
  cl_uint maxComputeUnits;
  int j;
  for (j = 0; j <ndevices ; j++) {
    cl_ulong buf_ulong;

    // print device name
    clGetDeviceInfo(device[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
    value = (char*) malloc(valueSize);
    clGetDeviceInfo(device[j], CL_DEVICE_NAME, valueSize, value, NULL);
    printf("%d. Device: %s\n", j, value);
    free(value);
    
    
    

    // print hardware device version
    clGetDeviceInfo(device[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
    value = (char*) malloc(valueSize);
    clGetDeviceInfo(device[j], CL_DEVICE_VERSION, valueSize, value, NULL);
    printf(" %d.%d Hardware version: %s\n", j, 1, value);
    free(value);
    
    // print software driver version
    clGetDeviceInfo(device[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
    value = (char*) malloc(valueSize);
    clGetDeviceInfo(device[j], CL_DRIVER_VERSION, valueSize, value, NULL);
    printf(" %d.%d Software version: %s\n", j, 2, value);
    free(value);
    
    // print c version supported by compiler for device
    clGetDeviceInfo(device[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
    value = (char*) malloc(valueSize);
    clGetDeviceInfo(device[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
    printf(" %d.%d OpenCL C version: %s\n", j, 3, value);
    free(value);
    
    // print parallel compute units
    clGetDeviceInfo(device[j], CL_DEVICE_MAX_COMPUTE_UNITS,
		    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
    printf(" %d.%d Parallel compute units: %d\n", j, 4, maxComputeUnits);
    
    // print device memory size
    clGetDeviceInfo(device[j], CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(buf_ulong), &buf_ulong, NULL);
    printf(" %d.%d Global Memory: %lu KB\n", j, 5, buf_ulong/(1024));
    
    clGetDeviceInfo(device[j], CL_DEVICE_LOCAL_MEM_SIZE,sizeof(buf_ulong), &buf_ulong, NULL);
    printf(" %d.%d Local Memory: %lu KB\n", j, 5, buf_ulong/(1024));
    
    clGetDeviceInfo(device[j], CL_DEVICE_HOST_UNIFIED_MEMORY,sizeof(buf_ulong), &buf_ulong, NULL);
    printf(" %d.%d Unified Memory: %lu\n", j, 5, buf_ulong);
    
    

    
  }
  
  return 0;
}

void *basic_mul_computation_thread(void *arg) {  
  DCMul *d =  (DCMul *)arg;
  cl_int err;
  cl_event event[4];
  size_t ldc = d->N;        /* i.e. ldc = N */
  size_t ldb = d->N;        /* i.e. ldb = N */
  size_t lda = d->K;        /* i.e. lda = K */
  
  if (DEBUG) {
    printf("computing %f %f %f \n", d->A[0],d->B[0],d->C[0]);  
    deviceInformation(&(d->id),1);  
    printf("Qs %lu \n",(long unsigned int) d->queue);
    printf("bufA %lu bufB %lu bufC %lu\n",(long unsigned int)d->bufA,
	   (long unsigned int)d->bufB,(long unsigned int)d->bufC);
    printf("M %lu N %lu K %lu\n",(long unsigned int)d->M,(long unsigned int)d->N,(long unsigned int)d->K);
  }
  err = clEnqueueWriteBuffer(d->queue, d->bufA, CL_FALSE, 0,
			     d->M * d->K * sizeof(DATATYPE), d->A, 0, NULL, event+0);
  
  checkErrors(err, "write  failed",0); 
  err = clEnqueueWriteBuffer(d->queue, d->bufB, CL_FALSE, 0,
			     d->K * d->N * sizeof(DATATYPE), d->B, 0, NULL, event+1);
  checkErrors(err, "write  failed",0); 
  err = clEnqueueWriteBuffer(d->queue, d->bufC, CL_FALSE, 0,
			     d->M * d->N * sizeof(DATATYPE), d->C, 0, NULL, event+2);
  
  checkErrors(err, "write  failed",0); 
  if (DEBUG) printf("Sent Data \n");
  
  /* Call clblas extended function. Perform gemm for the lower right sub-matrices */
  
  err = GEMM(order, 
	     transA, 
	     transB, 
	     d->M, 
	     d->N, 
	     d->K, 
	     alpha, 
	     d->bufA, 
	     0,
	     lda, 
	     d->bufB, 
	     0,
	     ldb, 
	     beta, 
	     d->bufC,0,
	     ldc, 
	     1, 
	     &(d->queue),
	     3, 
	     event, 
	     event+3);
  
  
  if (DEBUG) printf("Sent kernel \n");
  checkErrors(err, "gemm  failed",0); 
  if (err != CL_SUCCESS) {
    printf("clblasSgemmEx() failed with %d\n", err);
    d->result = 1;
    return (void*)1;
  }
  
  if (DEBUG)  printf("read result \n");
  /* Fetch results of calculations from GPU memory. */
  err = clEnqueueReadBuffer(d->queue, d->bufC, CL_TRUE, 0,
			    d->M * d->N * sizeof(DATATYPE),
			    d->C, 1, event+3, NULL );
  
  if (err != CL_SUCCESS) {
    printf("clblasSgemmEx() failed with %d\n", err);
    d->result = 1;
    return  (void *)1;
  }

  if (DEBUG) printf("done \n");
  d->result =0;
  return (void *)0; 

}                                                                   


void *basic_mul_computation_shared(void *arg) {  
  DCMul *d =  (DCMul *)arg;
  cl_int err;
  int j;
  cl_event event_final[NUM_THREADS];
  cl_event event[NUM_THREADS];
  cl_event event_writes[NUM_THREADS_L];
  size_t ldc = d->N;        /* i.e. ldc = N */
  size_t ldb = d->N;        /* i.e. ldb = N */
  size_t lda = d->K;        /* i.e. lda = K */


  if ((d+0)->warmup == 1) {
    for (j=0; j<(d+0)->sibling;j++) {    

      printf("warm up %d\n",j);
      err = GEMM(order, 
		 transA, 
		 transB, 
		 (d+j)->M, 
		 (d+j)->N, 
		 (d+j)->K, 
		 alpha, 
		 (d+j)->bufA,
		 0,
		 lda, 
		 ((d+j)->result==1)?(d+0)->bufB:(d+j)->bufB,
		 0,
		 ldb, 
		 beta, 
		 (d+j)->bufC,
		 0,
		 ldc, 
		 1, 
		 &((d+j)->queue),
		 0, 
		 NULL, 
		 event + j*4);
        
      err = clWaitForEvents(1, event + j*4);
    }
    printf("end warm up %d\n",j);
    return (void*) 0;
  }
 
  
  if (DEBUG) {
    for (j=0; j<(d+0)->sibling;j++) {
      printf("%d computing %f %f %f \n",j, (d+j)->A[0],(d+j)->B[0],(d+j)->C[0]);  
      deviceInformation(&((d+j)->id),1);  
      printf("Qs %lu ",(long unsigned int)d->queue);
      printf("bufA %lu bufB %lu bufC %lu",
	     (long unsigned int)(d+j)->bufA,
	     (long unsigned int)(d+j)->bufB,
	     (long unsigned int)(d+j)->bufC);
      printf(" M %lu N %lu K %lu\n",(long unsigned int)(d+j)->M,
	     (long unsigned int)(d+j)->N,(long unsigned int)(d+j)->K);
    }
  }
  
  for (j=0; j<(d+0)->sibling;j++) {
    
    // B should be shared across all multiplications
    err = clEnqueueWriteBuffer((d+j)->queue, 
			       (d+j)->bufB, CL_FALSE, 0,
			       (d+j)->N * (d+j)->K * sizeof(DATATYPE), (d+j)->B, 
			       0, NULL, 
			       event_writes+2+3*j);
    checkErrors(err, "B write  failed",j); 


    // A 
    err = clEnqueueWriteBuffer((d+j)->queue, 
			       (d+j)->bufA, CL_FALSE, 0,
			       (d+j)->M * (d+j)->K * sizeof(DATATYPE), (d+j)->A, 
			       0, NULL, 
			       event_writes+0+3*j);
    checkErrors(err, "A write  failed",j); 
    
    // C 
    err = clEnqueueWriteBuffer((d+j)->queue, 
			       (d+j)->bufC, CL_FALSE, 0,
			       (d+j)->M * (d+j)->N * sizeof(DATATYPE), (d+j)->C, 0, NULL, 
			       event_writes+1+3*j);
    checkErrors(err, "C write  failed",j);   

    if (DEBUG) {
      printf("C[0] M %lu N %lu\n",(long unsigned int)(d+j)->M,(long unsigned int)(d+j)->N);
    }
    
  
    
    if (DEBUG) printf("Sent Data %d\n",j);
  
    /* Call clblas extended function. Perform gemm for the lower right sub-matrices */

    err = GEMM(order, 
	       transA, 
	       transB, 
	       (d+j)->M, 
	       (d+j)->N, 
	       (d+j)->K, 
	       alpha, 
	       (d+j)->bufA,
	       0,
	       lda, 
	       ((d+j)->result==1)?(d+0)->bufB:(d+j)->bufB,
	       0,
	       ldb, 
	       beta, 
	       (d+j)->bufC,
	       0,
	       ldc, 
	       1, 
	       &((d+j)->queue),
	       3, 
	       event_writes+j*3, 
	       event + j);
    

    checkErrors(err, "gemm failed",j); 
    if (err != CL_SUCCESS) {
      printf("clblasSgemmEx() failed with %d\n", err);
      //d->result = 1;
      return (void*) 1;
    }


  
    /* Fetch results of calculations from GPU memory. */
    err = clEnqueueReadBuffer((d+j)->queue, (d+j)->bufC, CL_FALSE, 0,
			      (d+j)->M * (d+j)->N * sizeof(DATATYPE),
			      (d+j)->C, 1, event+j, event_final+j);

    if (DEBUG)  printf("%d read result \n",j);
  }
  if (DEBUG)  printf("Wait for results %d \n",(d+0)->sibling);
  err = clWaitForEvents((d+0)->sibling, event_final);

  if (err != CL_SUCCESS) {
    printf("clblasSgemmEx() failed with %d\n", err);
    //d->result = 1;
    return  (void*)1;
  }

  if (DEBUG) printf("done \n");
  //d->result =0;
  return (void *)0; 

}                                                                   

		       


