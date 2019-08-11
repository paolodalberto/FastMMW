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

  
#define DEVICES    5
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
      if (DEBUG) printf("Row Continuous %d %d %d %lu M \n",		\
			(X).n,(X).N,					\
			sizeof(Mat),(size_t)(X).m * (X).N * sizeof(Mat)/1024/1024); \
      err = clEnqueueWriteBuffer((queue), (buf), CL_FALSE, 0,		\
				 (size_t)(X).m * (X).n * sizeof(Mat),	\
				 (X).data,0, NULL, readevent);		\
      if (err!= CL_SUCCESS) checkErrors(err, "row write  failed",k);	\
    }									\
    else {								\
      int i = 0;	/* move row stripes */				\
      if (DEBUG) printf("Row Striding %d %d %d %d %d \n", (X).n,(X).m,(X).N,(X).M, sizeof(Mat));	\
      for (i=0; i< (X).m; i ++) {					\
	err = clEnqueueWriteBuffer(queue, buf, CL_FALSE,		\
				   (size_t)i*(X).n*sizeof(Mat),		\
				   (size_t)(X).n*sizeof(Mat),		\
				   (X).data + i*(X).N,  0, NULL, readevent); \
	if (err!= CL_SUCCESS) checkErrors(err, "row write  failed",i);				\
      }									\
    }									\
  }									\
  

#define COLAAR(X,queue, buf,readevent,k) {				\
    if ((X).m == (X).M)	/* continuous column major  */ {		\
      if (DEBUG) printf("Col Continuous %d %d %d %lu M\n",		\
			(X).n,(X).N,sizeof(Mat),(size_t)(X).m * (X).n * sizeof(Mat)/1024/1024); \
      err = clEnqueueWriteBuffer(queue, buf, CL_FALSE, 0,		\
				 (size_t)(X).m * (X).n * sizeof(Mat),	\
				 (X).data,0, NULL, readevent);		\
      if (err!= CL_SUCCESS) checkErrors(err, "col write  failed",k);		\
    } else {								\
      int i = 0;	/* move column stripes */			\
      if (DEBUG) printf("Col Striding %d %d \n", (X).m, sizeof(Mat));	\
      for (i=0; i< (X).n; i ++)	{					\
	err = clEnqueueWriteBuffer(queue, buf, CL_FALSE,		\
				   (size_t)i*(X).m*sizeof(Mat),		\
				   (size_t)(X).m*sizeof(Mat),		\
				   (X).data + i*(X).M,  0, NULL, readevent); \
	if (err!= CL_SUCCESS) checkErrors(err, "write  failed",k); }	\
    }									\
  }

#define ROWWWR(X,queue, buf, readevent,writeevent) {			\
    if ((X).n == (X).N)	/* continuous row major  */{			\
      if (DEBUG) printf("Row Continuous %d %d %d %lu \n",			\
			(X).n,(X).N,sizeof(Mat), (size_t)(X).m * (X).n * sizeof(Mat)); \
      err = clEnqueueReadBuffer(queue, buf, CL_FALSE, 0,		\
				(size_t)(X).m * (X).n * sizeof(Mat),	\
				(X).data,1, readevent, writeevent);	\
      if (err!= CL_SUCCESS) checkErrors(err, "C write  failed",0);		\
    } else {								\
      int i = 0;	/* move row stripes */				\
      for (i=0; i< (X).m; i ++)	{					\
	err = clEnqueueReadBuffer(queue, buf, CL_FALSE,			\
				  (size_t)i*(X).n*sizeof(Mat),		\
				  (size_t)(X).n*sizeof(Mat),		\
				  (X).data + i*(X).N,  1,  readevent,writeevent); \
	if (err!= CL_SUCCESS) checkErrors(err, "C col  write  failed",0);	\
      }									\
    }									\
  }

#define COLWWR(X,queue, buf,readevent,writeevent) {			\
    if ((X).m == (X).M)	/* continuous column major  */		{	\
      err = clEnqueueReadBuffer(queue, buf, CL_FALSE, 0,		\
				(size_t)(X).m * (X).n * sizeof(Mat),	\
				(X).data,1, readevent,writeevent);	\
      if (err!= CL_SUCCESS) checkErrors(err, "C write  failed",0);	\
    } else {								\
      int i = 0;	/* move column stripes */			\
      for (i=0; i< (X).n; i ++) {					\
	err = clEnqueueReadBuffer(queue, buf, CL_FALSE,			\
				  (size_t)i*(X).m*sizeof(Mat),		\
				  (size_t)(X).m*sizeof(Mat),		\
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
  int weights[DEVICES] = {1,1,1,1,1};					\
  int sizes[DEVICES]   = {1,1,1,1,1};					\
  int indexes[DEVICES]   = {1,1,1,1,1};  				\
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
    if (DEBUG) printf("A Buffer %d %d %lu M\n",A.m,A.n, (size_t)A.m * A.n/an * sizeof(Mat)/1024/1024); \
    bufA[gpus[j]] = clCreateBuffer(*(bookmarks[gpus[j]].ctx), CL_MEM_READ_ONLY, \
				   (size_t)A.m * A.n/an * sizeof(Mat), NULL, &err); \
    if (err != CL_SUCCESS) {						\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufA[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF A size %d %d\n",r,e);					\
      printf("A Buffer %d %d %lu\n",A.m,A.n, (size_t)A.m * A.n/an * sizeof(Mat)/1024/1024); \
      printf( "clCreateBuffer() failed with A %d\n", gpus[j] );		\
      checkErrors(err, "buffer A  failed",0);				\
      clReleaseContext(*(bookmarks[gpus[j]].ctx));			\
      return 1;								\
    }									\
    if (DEBUG) {							\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufA[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF A size %ld M %d\n",r/1024/1024,e);					\
    }									\
    if (DEBUG) printf("B Buffer %d %d %lu\n",B.m,B.n, (size_t)B.m * B.n/bn * sizeof(Mat)/1024/1024); \
    bufB[gpus[j]] = clCreateBuffer(*(bookmarks[gpus[j]].ctx), CL_MEM_READ_ONLY, \
				   (size_t)B.m * B.n/bn * sizeof(Mat),	\
				   NULL, &err);				\
    if (err != CL_SUCCESS) {						\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufB[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("B Buffer %d %d %lu M\n",B.m,B.n, (size_t)B.m * B.n/bn * sizeof(Mat)/1024/1024); \
      printf( "clCreateBuffer() failed with B %d\n", gpus[j] );	\
      checkErrors(err, "failed",0);				\
      clReleaseContext(*(bookmarks[gpus[j]].ctx));			\
      printf("BUF B size %d %d\n",r,e);					\
      return 1;								\
    }									\
    if (DEBUG) {							\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufB[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF B size %ld M %d\n",r/1024/1024,e);					\
    }									\
    if (DEBUG) printf("C Buffer %d %d %lu M\n",C.m,C.n, (size_t)C.m * C.n/cn * sizeof(Mat)/1024/1024); \
    bufC[gpus[j]] = clCreateBuffer(*(bookmarks[gpus[j]].ctx), CL_MEM_READ_WRITE,	\
				   (size_t)C.m * C.n/cn * sizeof(Mat),	\
				   NULL, &err);				\
    if (err != CL_SUCCESS) {						\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufC[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF C size %d %d\n",r,e);					\
      printf("C Buffer %d %d %luM\n",C.m,C.n, (size_t)C.m * C.n/cn * sizeof(Mat)/1024/1024); \
      printf( "clCreateCommandQueue() failed with C %d\n", gpus[j] );	\
      checkErrors(err, "failed",0);					\
      clReleaseContext(*(bookmarks[gpus[j]].ctx));			\
      return 1;								\
    }									\
    if (DEBUG) {							\
      size_t r;								\
      cl_int e = clGetMemObjectInfo (bufC[gpus[j]],CL_MEM_SIZE,sizeof(r),&r,NULL); \
      printf("BUF C size %ld M %d\n",r/1024/1024,e);					\
    }									\
  }									\
  
#define WAIT_AND_RELEASE     /* wait for the threads to complete */	\
  									\
  for (j=0;j<NN;j++) {							\
    cl_int res;								\
    res = clReleaseMemObject(bufC[gpus[j]]); 				\
    if (res !=CL_SUCCESS) {printf("not release buff c for gpu[%d] = %d \n",j,gpus[j]); } \
    res = clReleaseMemObject(bufB[gpus[j]]);				\
    if (res !=CL_SUCCESS) {printf("not release buff B for gpu[%d] = %d \n",j,gpus[j]); } \
    res = clReleaseMemObject(bufA[gpus[j]]);				\
    if (res !=CL_SUCCESS) {printf("not release buff A for gpu[%d] = %d \n",j,gpus[j]); } \
  }									\
  									\
  /* Release OpenCL working objects. */					\
  for (j=0;j<NN;j++) {							\
    cl_int res;                                                         \
    clReleaseCommandQueue(queue[gpus[j]]);				\
    if (res !=CL_SUCCESS) {printf("not release Queue for gpu[%d] = %d \n",j,gpus[j]); } \
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



#if(HALF_PRECISION)
#define DATATYPE cl_half
static const DATATYPE            alpha_zero = 0.0;  
static const DATATYPE            alpha_one = 1.0;  
static const DATATYPE            beta  = 1.0;
#elif(SINGLE_PRECISION)
#define DATATYPE cl_float
static const DATATYPE            alpha_zero = 0.0;  
static const DATATYPE            alpha_one = 1.0;  
static const DATATYPE            beta  = 1.0;
#elif(DOUBLE_PRECISION)
#define DATATYPE cl_double
static const DATATYPE            alpha_zero = 0.0;  
static const DATATYPE            alpha_one = 1.0;  
static const DATATYPE            beta  = 1.0;
#elif(SINGLE_COMPLEX)
#define DATATYPE cl_float2
static const DATATYPE            alpha_zero = { 0.0, 0.0};  
static const DATATYPE            alpha_one =  {1.0, 1.1} ;  
static const DATATYPE            beta  = {1.0, 1.0 };
#elif(DOUBLE_COMPLEX)
#define DATATYPE cl_double2
static const DATATYPE            alpha_zero = { 0.0, 0.0};  
static const DATATYPE            alpha_one =  {1.0, 1.1} ;  
static const DATATYPE            beta  = {1.0, 1.0 };
#endif


#if(AMDCLBLAS)
#if(COLUMN_MAJOR)
static const clAmdBlasOrder     order  = clAmdBlasColumnMajor;
#elif(ROW_MAJOR)
static const clAmdBlasOrder     order  = clAmdBlasRowMajor;
#endif

static const clAmdBlasTranspose transA   = clAmdBlasTrans;
static const clAmdBlasTranspose notransA = clAmdBlasNoTrans;
#else
#if(COLUMN_MAJOR)
static const int     order  = CLBlastLayoutColumnMajor,;
#elif(ROW_MAJOR)
static const int     order  = CLBlastLayoutRowMajor;
#endif

static const int notransA = CLBlastTransposeNo;
static const int transA   = CLBlastTransposeYes;

#endif
