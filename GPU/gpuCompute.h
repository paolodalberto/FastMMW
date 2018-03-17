#include <architecture.h>



#ifndef GPUCOMPUTE
#define GPUCOMPUTE


/* Include CLBLAS header. It automatically includes needed OpenCL header,
   * so we can drop out explicit inclusion of cl.h header.
   */

#include <clblast_c.h>

//#include <clAmdBlas.h>


//#include <pthread.h>      
#include <pt.h>
  
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

  
#define DEVICES    4
#define PLATFORMS  2

/// Assume we can define a gemm function that is specific to the type,
/// device and opencl

struct device_structure {
  cl_platform_id *platform;
  cl_context *ctx;
  cl_device_id *device;
  int i;
  char *name;
  int size;
  MatrixComputation gemm;
  int gpu;
  
};

typedef struct device_structure DeviceBookmark;

  
#define ROWAAR(X,queue, buf, readevent,k) {				\
    if ((X).n == (X).N)	/* continuous row major  */	{		\
      if (DEBUG) printf("Row Continuous %d %d %d %d \n",		\
			(X).n,(X).N,					\
			sizeof(Mat),(X).m * (X).N * sizeof(Mat));	\
      err = clEnqueueWriteBuffer((queue), (buf), CL_FALSE, 0,		\
				 (X).m * (X).n * sizeof(Mat),		\
				 (X).data,0, NULL, readevent);		\
      if (err!= CL_SUCCESS) checkErrors(err, "row write  failed",k);	\
    }									\
    else {								\
      int i = 0;	/* move row stripes */				\
      if (DEBUG) printf("Row Striding %d %d %d %d %d \n", (X).n,(X).m,(X).N,(X).M, sizeof(Mat));	\
      for (i=0; i< (X).m; i ++) {					\
	err = clEnqueueWriteBuffer(queue, buf, CL_FALSE,		\
				   i*(X).n*sizeof(Mat),		\
				   (X).n*sizeof(Mat),		\
				   (X).data + i*(X).N,  0, NULL, readevent); \
	if (err!= CL_SUCCESS) checkErrors(err, "row write  failed",i);				\
      }									\
    }									\
  }									\
  

#define COLAAR(X,queue, buf,readevent,k) {				\
    if ((X).m == (X).M)	/* continuous column major  */ {		\
      if (DEBUG) printf("Col Continuous %d %d %d %d \n",		\
			(X).n,(X).N,sizeof(Mat),(X).m * (X).n * sizeof(Mat)); \
      err = clEnqueueWriteBuffer(queue, buf, CL_FALSE, 0,		\
				 (X).m * (X).n * sizeof(Mat),	\
				 (X).data,0, NULL, readevent);		\
      if (err!= CL_SUCCESS) checkErrors(err, "col write  failed",k);		\
    } else {								\
      int i = 0;	/* move column stripes */			\
      if (DEBUG) printf("Col Striding %d %d \n", (X).m, sizeof(Mat));	\
      for (i=0; i< (X).n; i ++)	{					\
	err = clEnqueueWriteBuffer(queue, buf, CL_FALSE,		\
				   i*(X).m*sizeof(Mat),		\
				   (X).m*sizeof(Mat),		\
				   (X).data + i*(X).M,  0, NULL, readevent); \
	if (err!= CL_SUCCESS) checkErrors(err, "write  failed",k); }	\
    }									\
  }

#define ROWWWR(X,queue, buf, readevent,writeevent) {			\
    if ((X).n == (X).N)	/* continuous row major  */{			\
      if (DEBUG) printf("Row Continuous %d %d %d %d \n",			\
			(X).n,(X).N,sizeof(Mat), (X).m * (X).n * sizeof(Mat)); \
      err = clEnqueueReadBuffer(queue, buf, CL_FALSE, 0,		\
				(X).m * (X).n * sizeof(Mat),	\
				(X).data,1, readevent, writeevent);	\
      if (err!= CL_SUCCESS) checkErrors(err, "C write  failed",0);		\
    } else {								\
      int i = 0;	/* move row stripes */				\
      for (i=0; i< (X).m; i ++)	{					\
	err = clEnqueueReadBuffer(queue, buf, CL_FALSE,			\
				  i*(X).n*sizeof(Mat),			\
				  (X).n*sizeof(Mat),			\
				  (X).data + i*(X).N,  1,  readevent,writeevent); \
	if (err!= CL_SUCCESS) checkErrors(err, "C col  write  failed",0);	\
      }									\
    }									\
  }

#define COLWWR(X,queue, buf,readevent,writeevent) {			\
    if ((X).m == (X).M)	/* continuous column major  */		{	\
      err = clEnqueueReadBuffer(queue, buf, CL_FALSE, 0,		\
				(X).m * (X).n * sizeof(Mat),		\
				(X).data,1, readevent,writeevent);	\
      if (err!= CL_SUCCESS) checkErrors(err, "C write  failed",0);	\
    } else {								\
      int i = 0;	/* move column stripes */			\
      for (i=0; i< (X).n; i ++) {					\
	err = clEnqueueReadBuffer(queue, buf, CL_FALSE,			\
				  i*(X).m*sizeof(Mat),			\
				  (X).m*sizeof(Mat),			\
				  (X).data + i*(X).M,  1, readevent,writeevent); \
      }									\
      if (err!= CL_SUCCESS) checkErrors(err, "C col  write  failed",0);	\
    }									\
    checkErrors(err, "write  failed",0);				\
  }


 




#define INITIALIZE							\
  cl_int err;								\
  int ret = 0;								\
  int i,j,NN;								\
  pthread_t  p_thread[DEVICES]; /* thread's structure */			\
  int thr_id[DEVICES];							\
  GPUData    d[DEVICES];						\
  cl_command_queue queue[DEVICES];					\
  cl_mem bufA[DEVICES], bufB[DEVICES], bufC[DEVICES];			\
  int weights[DEVICES] = {1,1,1,1,};					\
  int sizes[DEVICES]   = {1,1,1,1,};					\
  int indexes[DEVICES]   = {1,1,1,1,};  				\
    {int jj; for (jj=0;jj<DEVICES;jj++) d[jj].skip = 15;}		\
    

#define QUEUEIT(an,bn,cn)						\
  for (j =0; j<ngpus;j++){						\
    int size = 0;							\
    if (DEBUG) printf("%d Queue creation %d %d %s %d vs %d \n",DEVICES,j,gpus[j],bookmarks[gpus[j]].name,*bookmarks[gpus[j]].device,device[gpus[j]]); \
    queue[gpus[j]] = clCreateCommandQueue(*(bookmarks[gpus[j]].ctx), *bookmarks[gpus[j]].device, 0, &err); \
    if (err != CL_SUCCESS) {						\
      printf( "clCreateCommandQueue() failed with A %d\n", gpus[j] );	\
      checkErrors(err, "Queue failed",0);				\
      clReleaseContext(*(bookmarks[gpus[j]].ctx));			\
      return 1;								\
    }									\
    if (DEBUG) printf("A Buffer %d %d %d\n",A.m,A.n, A.m * A.n/an * sizeof(Mat)); \
    bufA[gpus[j]] = clCreateBuffer(*(bookmarks[gpus[j]].ctx), CL_MEM_READ_ONLY, \
				   A.m * A.n/an * sizeof(Mat), NULL, &err); \
    if (err != CL_SUCCESS) {						\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufA[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF A size %d %d\n",r,e);					\
      printf("A Buffer %d %d %d\n",A.m,A.n, A.m * A.n/an * sizeof(Mat)); \
      printf( "clCreateBuffer() failed with A %d\n", gpus[j] );		\
      checkErrors(err, "buffer A  failed",0);				\
      clReleaseContext(*(bookmarks[gpus[j]].ctx));			\
      return 1;								\
    }									\
    if (DEBUG) {							\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufA[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF A size %d %d\n",r,e);					\
    }									\
    if (DEBUG) printf("B Buffer %d %d %d\n",B.m,B.n, B.m * B.n/bn * sizeof(Mat)); \
    bufB[gpus[j]] = clCreateBuffer(*(bookmarks[gpus[j]].ctx), CL_MEM_READ_ONLY, \
				   B.m * B.n/bn * sizeof(Mat),	\
				   NULL, &err);				\
    if (err != CL_SUCCESS) {						\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufB[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("B Buffer %d %d %d\n",B.m,B.n, B.m * B.n/bn * sizeof(Mat)); \
      printf( "clCreateBuffer() failed with B %d\n", gpus[j] );	\
      checkErrors(err, "failed",0);				\
      clReleaseContext(*(bookmarks[gpus[j]].ctx));			\
      printf("BUF B size %d %d\n",r,e);					\
      return 1;								\
    }									\
    if (DEBUG) {							\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufB[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF B size %d %d\n",r,e);					\
    }									\
    if (DEBUG) printf("C Buffer %d %d %d\n",C.m,C.n, C.m * C.n/cn * sizeof(Mat)); \
    bufC[gpus[j]] = clCreateBuffer(*(bookmarks[gpus[j]].ctx), CL_MEM_READ_WRITE,	\
				   C.m * C.n/cn * sizeof(Mat),	\
				   NULL, &err);				\
    if (err != CL_SUCCESS) {						\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufC[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF C size %d %d\n",r,e);					\
      printf("C Buffer %d %d %d\n",C.m,C.n, C.m * C.n/cn * sizeof(Mat)); \
      printf( "clCreateCommandQueue() failed with C %d\n", gpus[j] );	\
      checkErrors(err, "failed",0);					\
      clReleaseContext(*(bookmarks[gpus[j]].ctx));			\
      return 1;								\
    }									\
    if (DEBUG) {							\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufC[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF C size %d %d\n",r,e);					\
    }									\
  }									\
  
#define WAIT_AND_RELEASE     /* wait for the threads to complete */	\
  									\
  for (j=0;j<NN;j++) {							\
    clReleaseMemObject(bufC[gpus[j]]);					\
    clReleaseMemObject(bufB[gpus[j]]);					\
    clReleaseMemObject(bufA[gpus[j]]);					\
  }									\
  									\
  /* Release OpenCL working objects. */					\
  for (j=0;j<NN;j++) {							\
    clReleaseCommandQueue(queue[gpus[j]]);				\
  }									\


/* This example uses predefined matrices and their characteristics for
 * simplicity purpose.
 */
struct mul_data { 
  cl_device_id id;
  cl_command_queue queue;
  cl_mem bufA,bufB,bufC;
  Matrix A, B,C;
  int skip;
  int result;
};

typedef struct mul_data GPUData;
#endif
