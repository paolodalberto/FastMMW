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
#include "rocblas.h"
#include <hip/hip_runtime_api.h>

#include <gpuRocmCompute.h>


static inline
void CHECK_HIP_ERROR( hipError_t error) {		
  if(error != hipSuccess)  {
    fprintf(stderr,					
	    "Hip error: '%s'(%d) at %s:%d\n",	
	    hipGetErrorString(error),		
	    error,					
	    __FILE__,				
	    __LINE__);				
    exit(EXIT_FAILURE);				
  }
}


static inline
void CHECK_ROCBLAS_ERROR(rocblas_status  error) { }
/*
static inline
void CHECK_ROCBLAS_ERROR(rocblas_status  error)
{
  if(error != rocblas_status_success)				
    {                                                           
      fprintf(stderr, "rocBLAS error: ");			
      if(error == rocblas_status_invalid_handle)  fprintf(stderr, "rocblas_status_invalid_handle");	
      if(error == rocblas_status_not_implemented) fprintf(stderr, " rocblas_status_not_implemented");	
      if(error == rocblas_status_invalid_pointer) fprintf(stderr, "rocblas_status_invalid_pointer");	
      if(error == rocblas_status_invalid_size)	  fprintf(stderr, "rocblas_status_invalid_size");		
      if(error == rocblas_status_memory_error)	  fprintf(stderr, "rocblas_status_memory_error");		
      if(error == rocblas_status_internal_error)  fprintf(stderr, "rocblas_status_internal_error");	
      fprintf(stderr, "\n");				
      exit(EXIT_FAILURE);					
    }
}

int k() {
return 9;
}
*/

/* gpus = 0 in platform 1  is the only one I can use*/ 
int ngpus=4;
int gpus[4] = {0,1,2,3};
//                         Elle       Elle     Fiji         Fiji    


char *_names[DEVICES] =  { "fiji", "fiji", "ellesmere", "ellesmere","" }; 
int   _sizes[DEVICES] =  {   3956940,     4148964,      16580608,  16580608,16580608};

static int DEBUG=0;  
static int DEBUG2=0;  


static inline
void  ROCROWAAR(DEF(X), Mat *buf)
{				
  if (X.n == X.N)	/* continuous row major  */	{		
    if (DEBUG) printf("Row Continuous %d %d %d %lu M \n",		
		      X.n,X.N,					
		      sizeof(Mat),(size_t)X.m * X.N * sizeof(Mat)/1024/1024); 
    CHECK_HIP_ERROR(hipMemcpy(buf,
			      X.data,			
			      (size_t)X.m * X.n * sizeof(Mat), 
			      hipMemcpyHostToDevice
			      )); 
  }									
  else {								
    int i = 0;	/* move row stripes */				
    if (DEBUG) printf("Row Striding %d %d %d %d %d \n", X.n,X.m,X.N,X.M, sizeof(Mat));	
    for (i=0; i< X.m; i ++) {
      CHECK_HIP_ERROR(hipMemcpy(buf + i*X.n,
				X.data+ i*X.N,			
				(size_t)X.n*sizeof(Mat),
				hipMemcpyHostToDevice
				)); 
      
    }
  }									
}									


static void  
ROCCOLAAR(DEF(X), Mat *buf)
{
  if (X.m == X.M)	/* continuous column major  */ {		
    if (DEBUG) printf("Col Continuous %d %d %d %lu Mn",		
		      X.n,X.N,sizeof(Mat),(size_t)X.m * X.n * sizeof(Mat)/1024/1024); 
    
    CHECK_HIP_ERROR(hipMemcpy(buf,
			      X.data,			
			      (size_t)X.m * X.n * sizeof(Mat), 
			      hipMemcpyHostToDevice
			      )); 
  } else {								
    int i = 0;	/* move column stripes */			
    if (DEBUG) printf("Col Striding %d %d n", X.m, sizeof(Mat));	
    for (i=0; i< X.n; i ++)	{
      CHECK_HIP_ERROR(hipMemcpy(buf + i*X.m,
				X.data + i*X.M,
				(size_t)X.m*sizeof(Mat),		
				hipMemcpyHostToDevice
				));
    }									
  }
}

static void  
ROCROWWWR(DEF(X), Mat *buf)
{
  
  if (X.n == X.N)	/* continuous row major  */{			
    if (DEBUG) printf("Row Continuous %d %d %d %lu n",			
		      X.n,X.N,sizeof(Mat), (size_t)X.m * X.n * sizeof(Mat)); 
    CHECK_HIP_ERROR(hipMemcpy(X.data,
			      buf,
			      (size_t)X.m * X.n * sizeof(Mat),	
			      hipMemcpyDeviceToHost));
    
  } else {								
    int i = 0;	/* move row stripes */				
    for (i=0; i< X.m; i ++)	{					
      CHECK_HIP_ERROR(hipMemcpy(X.data+ i*X.N,
				buf + i*X.n,
				(size_t)X.n*sizeof(Mat),
				hipMemcpyDeviceToHost
				)); 
    }									
  }									
}

static void  
ROCCOLWWR(DEF(X), Mat *buf)
{
  if (X.m == X.M)	/* continuous column major  */		{	
    CHECK_HIP_ERROR(hipMemcpy(X.data,
			      buf,
			      (size_t)X.m * X.n * sizeof(Mat),	
			      hipMemcpyDeviceToHost));
  } else {								
    int i = 0;	/* move column stripes */			
    for (i=0; i< X.n; i ++) {
      
      CHECK_HIP_ERROR(hipMemcpy(X.data+ i*X.M,
				buf + i*X.m,
				(size_t)X.m*sizeof(Mat),
				hipMemcpyDeviceToHost
				)); 
    }									
  }
}
static inline
void set_device(int device_id)
{
  rocblas_status status = (rocblas_status)hipSetDevice((rocblas_int)device_id);
    if(status != rocblas_status_success)
    {
        printf("Set device error: cannot set device ID %d, there may not be such device ID\n",
               (int)device_id);
    }
}


static inline
int TEMPLATE(DEF(C),DEF(A), DEF(B)) {
  
  int gpus[1] = {C.gpu};
  rocblas_handle handle;
  rocblas_status err;
  int skipc = (C.beta == _zero)?0:1;
  Mat *bufA, *bufB, *bufC;
  hipStream_t stream;
  Mat alpha, beta;
  
  if (DEBUG) {
    printf("GPU %d  TEMPLATE size of the matrix element %d\n",gpus[0], sizeof(A.beta));
    printf("GPU %d  You selected the following problem \n",gpus[0]);
    printf("GPU %d       A %d x %d %f\n",gpus[0], A.m,A.n, A.beta);
    printf("GPU %d       B %d x %d %f \n",gpus[0],B.m,B.n,B.beta);
    printf("GPU %d  Thus C %d x %d %f \n",gpus[0],C.m, C.n, C.beta);
  }
									

  // because memory data movemement use the default device
  set_device(C.gpu);
  CHECK_HIP_ERROR(hipStreamCreate(&stream));
  
  CHECK_ROCBLAS_ERROR(rocblas_create_handle(&handle));
  CHECK_ROCBLAS_ERROR(rocblas_set_stream(handle, stream));

  CHECK_HIP_ERROR(hipMalloc(&bufA, A.m*A.n * sizeof(Mat)));
  CHECK_HIP_ERROR(hipMalloc(&bufB, B.n*B.m * sizeof(Mat)));
  CHECK_HIP_ERROR(hipMalloc(&bufC, C.n*C.m * sizeof(Mat)));
  
  
  if (DEBUG2) {
    printf("GPU %d \n",C.gpu);
  }
  
  if (DEBUG) {
    printf("GPU %d       A %d x %d %d x %d %c- \n",C.gpu,A.m, A.n,A.M,A.N, A.trans);
    printf("GPU %d       B %d x %d %d x %d %c- \n",C.gpu,B.m, B.n,B.M,B.N, B.trans);
    printf("GPU %d s%d  C %d x %d %d x %d %c- \n",C.gpu,skipc,C.m, C.n,C.M,C.N, C.trans);
  }
  
#if(ROW_MAJOR)
  if (DEBUG) printf("GPU %d Sending Row Data \n",C.gpu);
  if ((skipc)&1) { ROCROWAAR(A,bufA);}
  if (DEBUG) printf("GPU %d Sending Row Data \n",C.gpu);
  if ((skipc)&2) { ROCROWAAR(B,bufB);}
  if (DEBUG) printf("GPU %d Sending Row Data \n",C.gpu);
  if (skipc && (skipc)&4) { ROCROWAAR(C,bufC);}
#elif(COLUMN_MAJOR)
  if (DEBUG) printf("GPU %d Sending Col Data \n",C.gpu);
  if ((skipc)&1) {ROCCOLAAR(A, bufA);}
  if ((skipc)&2) {ROCCOLAAR(B, bufB); }
  if (skipc && (skipc)&4) {ROCCOLAAR(C,bufC);}
#endif
  
  
  if (DEBUG) printf("GPU %d Sent Data \n",C.gpu);
    
  
 
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)  
  if (1) { 
    DATATYPE al = {creal(A.beta*B.beta),cimag(A.beta*B.beta)};
    DATATYPE bl = {creal(C.beta),cimag(C.beta)};
    alpha= al;
    beta = bl;
    
    if (DEBUG) {
      printf("GPU %d Sending  kernel \n",C.gpu);
      printf("GPU %d  Alpha %f %f Beta %f %f \n",C.gpu, alpha.s[0], alpha.s[1], beta.s[0], beta.s[1]);
      
    }
    /*  alpha.s[0]= creal(A.beta*B.beta);
	alpha.s[1]= cimag(A.beta*B.beta);
	beta.s[0] = creal(C.beta);
	beta.s[1] = cimag(C.beta); */
  }
#else
  alpha = A.beta*B.beta;
  beta  = C.beta;
  if (DEBUG) {
    printf("GPU %d Sending  kernel \n",C.gpu);
    printf("GPU %d  Alpha %f  Beta  %f \n",C.gpu, alpha,  beta);
    
  }
#endif  

#if(ROW_MAJOR)
  err = GEMMROCM( handle,
		 (A.trans =='n')?rocblas_operation_none:rocblas_operation_transpose,  //2 
		 (B.trans =='n')?rocblas_operation_none:rocblas_operation_transpose,  //2 
		 A.m, //4 
		 B.n, //5
		 A.n, //6
		 &alpha, //7
		 bufB,
		 B.n, //10
		 bufA,
		 A.n, //13
		 &beta, // 14
		 bufC,
		 C.n //17
		 );
#elif(COLUMN_MAJOR)
  err = GEMMROCM(handle,
		 (A.trans =='n')?rocblas_operation_none:rocblas_operation_transpose,  //2 
		 (B.trans =='n')?rocblas_operation_none:rocblas_operation_transpose,  //2 
		 A.m, //4 
		 B.n, //5
		 A.n, //6
		 &alpha, //7
		 bufA,  // 8,9
		 A.m, //10 
		 bufB, //11 12
		 B.m, // 13
		 &beta, // 14
		 bufC,// 15 16
		 C.m
		 );
#endif
  CHECK_ROCBLAS_ERROR(err);
  if (DEBUG2) {
#if(ROW_MAJOR)
    printf("GPU %d Row Major and %d %d \n",C.gpu,
	   (A.trans =='n')?rocblas_operation_none:rocblas_operation_transpose,
	   (B.trans =='n')?rocblas_operation_none:rocblas_operation_transpose);
#elif(COLUMN_MAJOR)
    printf("GPU %d Column Major and order %d %d %d ",C.gpu,order,
	   (A.trans =='n')?rocblas_operation_none:rocblas_operation_transpose,
	   (B.trans =='n')?rocblas_operation_none:rocblas_operation_transpose);
#endif
  }
    
#if(ROW_MAJOR)
  if ((skipc)&8) {ROCROWWWR(C, bufC);}

#elif(COLUMN_MAJOR)
  if ((skipc)&8) {ROCCOLWWR(C, bufC);}
#endif
  if (DEBUG)  printf("GPU %d read result \n",C.gpu);
  /* Fetch results of calculations from GPU memory. */


  if (DEBUG) printf("GPU %d done \n",C.gpu);



  CHECK_HIP_ERROR(hipFree(bufA));
  CHECK_HIP_ERROR(hipFree(bufB));
  CHECK_HIP_ERROR(hipFree(bufC));
  CHECK_HIP_ERROR(hipStreamDestroy(stream));
  CHECK_ROCBLAS_ERROR(rocblas_destroy_handle(handle));
  if (DEBUG) printf("GPU %d done \n",C.gpu);
  
  return 0;
}  


// MUL with the basic interface. We will customize the name as
// function of the type and device.

extern "C" int ROCGEMM(DEF(C),DEF(A),DEF(B));
extern "C" int ROCGEMMA(DEF(C),DEF(A),DEF(B));

int
ROCGEMM(DEF(C),DEF(A),DEF(B))
{
  C.beta = _zero;
  return TEMPLATE(C,A,B);
}

// MADD
int
ROCGEMMA(DEF(C),DEF(A),DEF(B))
{
  C.beta = _one;
  return TEMPLATE(C,A,B);
}




RocmDeviceBookmark bookmarks[DEVICES];


/* *********************
 * We activate the platform we want and collect the set of devices availables
 *
 */ 



extern "C" rocblas_int query_and_set_device_property();
/* ============================================================================================ */
/*  device query and print out their ID and name; return number of compute-capable devices. */
rocblas_int query_and_set_device_property()
{
  int            device_count;
  rocblas_status status = (rocblas_status)hipGetDeviceCount(&device_count);
  int valid = 0;
  if(status != rocblas_status_success)
    {
      printf("Query device error: cannot get device count \n");
      return -1;
    }
  else
    {
      printf("Query device success: there are %d devices \n", device_count);
    }
  
  for(rocblas_int i = 0; i< device_count; i++)
    {
      printf("-------------------------------------------------------------------------------\n");
      
      hipDeviceProp_t props;
      rocblas_status  status = (rocblas_status)hipGetDeviceProperties(&props, i);
      
      if(status != rocblas_status_success)
	{
	  printf("Query device error: cannot get device ID %d's property\n", i);
	}
      else
	{

	  bookmarks[valid].gpu = i;
	  strcpy(bookmarks[valid].name,props.name);
	  _sizes[valid] = props.totalGlobalMem/1024;
	  bookmarks[valid].size = props.totalGlobalMem/1024;
	  valid ++;
	  printf("Device ID %d : %s\n", i, props.name);
	  printf("with %3.1f GB memory, clock rate %dMHz @ computing capability %d.%d \n",
		 props.totalGlobalMem / 1e9,
		 (int)(props.clockRate / 1000),
		 props.major,
		 props.minor);
	  printf(
		 "maxGridDimX %d, sharedMemPerBlock %3.1f KB, maxThreadsPerBlock %d, warpSize %d\n",
		 props.maxGridSize[0],
		 props.sharedMemPerBlock / 1e3,
		 props.maxThreadsPerBlock,
		 props.warpSize);
	}
    }

  for(int i = 0; i< valid; i++) {
    printf("Device ID %d Name %s Size %d: \n", bookmarks[i].gpu,bookmarks[i].name,bookmarks[i].size);
    
    
  }
  
  return device_count;
}

