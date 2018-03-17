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




  
#if(SINGLE_PRECISION)
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
#define DATATYPE FloatComplex
static const DATATYPE            alpha_zero = { 0.0, 0.0};  
static const DATATYPE            alpha_one =  {1.0, 1.1} ;  
static const DATATYPE            beta  = {1.0, 1.0 };
#elif(DOUBLE_PRECISION)
#define DATATYPE DoubleComplex
static const DATATYPE            alpha_zero = { 0.0, 0.0};  
static const DATATYPE            alpha_one =  {1.0, 1.1} ;  
static const DATATYPE            beta  = {1.0, 1.0 };
#endif


#if(COLUMN_MAJOR)
static const clAmdBlasOrder     order  = clAmdBlasColumnMajor;
#elif(ROW_MAJOR)
static const clAmdBlasOrder     order  = clAmdBlasRowMajor;
#endif

static const clAmdBlasTranspose transA = clAmdBlasNoTrans;
static const clAmdBlasTranspose transB = clAmdBlasNoTrans;



static int DEBUG=1;  

/* ********************************************************
 *
 * platform and devices are common to all applications.
 *
 */ 

cl_uint platformCount;
cl_platform_id *platforms;
int platform=0;
cl_device_id device[DEVICES];
cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
cl_context ctx = 0;
cl_uint ndevices;


/* gpus = 0 in platform 1  is the only one I can use*/ 
int ngpus=1;
int gpus[1] = {1};

/* *********************
 * We activate the platform we want and collect the set of devices availables
 *
 */ 


int  set_platform_and_devices(int platform) {
  char* info;
  size_t infoSize;
  const char* attributeNames[5] = { "Name", "Vendor",
				    "Version", "Profile", "Extensions" };
  const cl_platform_info attributeTypes[5] = { CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,
					       CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE, CL_PLATFORM_EXTENSIONS };
  const int attributeCount = sizeof(attributeNames) / sizeof(char*);
  int i,j;
  cl_int err;
  
  clGetPlatformIDs(0, NULL, &platformCount);
  platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
  clGetPlatformIDs(platformCount, platforms, NULL);

  for (i = 0; i < platformCount; i++) {
    
    printf("\n %d %d. Platform \n", i,platform);
    if (i != platform) continue;
    for (j = 0; j < attributeCount; j++) {
      
      // get platform attribute value size
      clGetPlatformInfo(platforms[i], attributeTypes[j], 0, NULL, &infoSize);
      info = (char*) malloc(infoSize);
      
      // get platform attribute value
      clGetPlatformInfo(platforms[i], attributeTypes[j], infoSize, info, NULL);
      
      printf("  %d.%d %-11s: %s\n", i+1, j+1, attributeNames[j], info);
      free(info);
      
    }
    
    printf("\n");
    
  }
  
  
  err = clGetDeviceIDs(platforms[platform], CL_DEVICE_TYPE_GPU, DEVICES, device,&ndevices);
  if (err != CL_SUCCESS) {
    checkErrors(err,"clGetDeviceIDs",10);
    printf( "clGetDeviceIDs() failed with %d\n", err );
    return 1;
  } else {
    
    deviceInformation( device,ndevices);
    
    
    printf("N of GPUS %d \n",ndevices);
    // for each device print critical attributes

  }

  props[1] = (cl_context_properties)platforms[platform];
  ctx = clCreateContext(props, ndevices , device, NULL, NULL, &err);
  if (err != CL_SUCCESS) {
    checkErrors(err,"create context",158);
    printf( "clCreateContext() failed with %d\n", err );
    return 1;
  }

  err = clAmdBlasSetup();
  if (err != CL_SUCCESS) {
    printf("clblasSetup() failed with %d\n", err);
    clReleaseContext(ctx);
    return 1;
  }
  
  return 0;
}


void release_blas_context() {

  clAmdBlasTeardown();
  clReleaseContext(ctx);
}

int weights[DEVICES] = {1,1,1,1,1,1};
int sizes[DEVICES]   = {1,1,1,1,1,1};
int indexes[DEVICES]   = {1,1,1,1,1,1};
int  shapes(int start, int end, int M,
	    int l,int *weights,  int *size, int *indexes) {
  
  int i;
  int n = 0;

  
  
  for (i=start; i<l && i<= end; i++)
    n += weights[i]; // number of partitions.
  
  for (i=start; i<l && i<= end; i++)
    size[i] = M*weights[i]/n;
  
  if (M%n!= 0 )
    size[i-1] = M*weights[i-1]/n+ (M%n);
  
  indexes[start] =0 ;
  for (i=start+1; i<l && i<= end; i++)
    indexes[i] = indexes[i-1] + size[i-1];
  
  if (DEBUG) {
    printf("M mod n = %d M=%d n=%d \n",M%n,M,n);
    for (i=start; i<l && i<= end;i++)
      printf("s[%d] = %d and i[%d] = %d \n",i,size[i],i,indexes[i]);
  }

  
  return n;
}








void *basic_mul_computation_gpugemm(void *arg) {  
  GPUData *d =  (GPUData *)arg;
  cl_int err;
  cl_event events[12];

  if (DEBUG) {
    printf("GPU \n");
    deviceInformation( &(d->id),1);
  }
  
  if (DEBUG) {
    size_t r;
    cl_int e = clGetMemObjectInfo (d->bufA,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("BUF A size %d %d\n",r,e);
    checkErrors(e, "read A",0);
    e = clGetMemObjectInfo (d->bufB,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("BUF B size %d %d \n",r,e);
    checkErrors(e, "read B",0);
    e = clGetMemObjectInfo (d->bufC,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("BUF C size %d %d \n",r,e);
    checkErrors(e, "read C",0);
  }
  
#if(ROW_MAJOR)
  if (DEBUG) printf("Sending Row Data \n");
  if ((d->skip)&1) { ROWAAR(d->A,d->queue, d->bufA,events+0);}
  if ((d->skip)&2) { ROWAAR(d->B,d->queue, d->bufB,events+1);}
  if ((d->skip)&4) { ROWAAR(d->C,d->queue, d->bufC,events+2);}
#elif(COLUMN_MAJOR)
  if (DEBUG) printf("Sending Col Data \n");
  if ((d->skip)&1) {COLAAR(d->A,d->queue, d->bufA,events+0);}
  if ((d->skip)&2) {COLAAR(d->B,d->queue, d->bufB,events+1); }
  if ((d->skip)&4) {COLAAR(d->C,d->queue, d->bufC,events+2);}
#endif

  
  /*
  if (DEBUG) printf("Wait for read kernel \n");
  err = clWaitForEvents(3, events);
      
  if (err !=CL_SUCCESS) { 
    checkErrors(err, "write  failed",0);
    if (DEBUG) printf("Wait for read kernel \n");
    
  }
  */

  
  if (DEBUG) printf("Sent Data \n");
  
  /* Call clblas extended function. Perform gemm for the lower right sub-matrices */
  
  // does not matter the order  at this point because I always translate to column major

  /**
   * @brief Matrix-matrix product of general rectangular matrices with float
   *        elements. Extended version.
   *
   * Matrix-matrix products:
   *   - \f$ C \leftarrow \alpha A B + \beta C \f$
   *   - \f$ C \leftarrow \alpha A^T B + \beta C \f$
   *   - \f$ C \leftarrow \alpha A B^T + \beta C \f$
   *   - \f$ C \leftarrow \alpha A^T B^T + \beta C \f$
   *
   * 1  @param[in] order     Row/column order.
   * 2  @param[in] transA    How matrix \b A is to be transposed.
   * 3  @param[in] transB    How matrix \b B is to be transposed.
   * 4  @param[in] M         Number of rows in matrix \b A.
   * 5  @param[in] N         Number of columns in matrix \b B.
   * 6  @param[in] K         Number of columns in matrix \b A and rows in matrix \b B.
   * 7  @param[in] alpha     The factor of matrix \b A.
   * 8  @param[in] A         Buffer object storing matrix \b A.
   * 9  @param[in] offA      Offset of the first element of the matrix \b A in the
   *                         buffer object. Counted in elements.
   *10  @param[in] lda       Leading dimension of matrix \b A. It cannot be less
   *                      than \b K when the \b order parameter is set to
   *                      \b clblasRowMajor,\n or less than \b M when the
   *                      parameter is set to \b clblasColumnMajor.
   *11  @param[in] B         Buffer object storing matrix \b B.
   *12  @param[in] offB      Offset of the first element of the matrix \b B in the
   *                      buffer object. Counted in elements.
   *13  @param[in] ldb       Leading dimension of matrix \b B. It cannot be less
   *                      than \b N when the \b order parameter is set to
   *                      \b clblasRowMajor,\n or less than \b K
   *                      when it is set to \b clblasColumnMajor.
   *14  @param[in] beta      The factor of matrix \b C.
   *15  @param[out] C        Buffer object storing matrix \b C.
   *16   @param[in]  offC     Offset of the first element of the matrix \b C in the
   *                      buffer object. Counted in elements.
   *17  @param[in] ldc       Leading dimension of matrix \b C. It cannot be less
   *                      than \b N when the \b order parameter is set to
   *                      \b clblasRowMajor,\n or less than \b M when
   *                      it is set to \b clblasColumnMajorOrder.
   *18  @param[in] numCommandQueues    Number of OpenCL command queues in which the
   *                                task is to be performed.
   *19  @param[in] commandQueues       OpenCL command queues.
   *20  @param[in] numEventsInWaitList Number of events in the event wait list.
   *21  @param[in] eventWaitList       Event wait list.
   *22  @param[in] events     Event objects per each command queue that identify
   *                       a particular kernel execution instance.
   *
   * @return
   *   - \b clblasSuccess on success;
   *   - \b clblasInvalidValue if either \b offA, \b offB or \b offC exceeds
   *        the size of the respective buffer object;
   *   - the same error codes as clblasSgemm() otherwise.
   *
   * @ingroup GEMM
   */
  


  /**
     clblasOrder order,
     clblasTranspose transA,
     clblasTranspose transB,
     size_t M,
     size_t N,
     size_t K,
     cl_float alpha,
     const cl_mem A,
     size_t lda,
     const cl_mem B,
     size_t ldb,
     cl_float beta,
     cl_mem C,
     size_t ldc,
     cl_uint numCommandQueues,
     cl_command_queue *commandQueues,
     cl_uint numEventsInWaitList,
     const cl_event *eventWaitList,
     cl_event *events)
  **/

  
#if(ROW_MAJOR)
  err = GEMMCL(
	       order, // 1  
	       (d->A.trans =='n')?clAmdBlasNoTrans:clAmdBlasTrans,  //2 
	       (d->B.trans =='n')?clAmdBlasNoTrans:clAmdBlasTrans,  //3
	       d->A.m, //4 
	       d->B.n, //5
	       d->A.n, //6
	       d->A.beta*d->B.beta, //7
	       d->bufA,
	       0, // 8,9
	       d->A.n, //10
	       d->bufB,
	       0, //11 12
	       d->B.n, //13
	       d->C.beta, // 14
	       d->bufC,
	       0,// 15 16
	       d->C.n, //17
	       1, 
	       &(d->queue),
	       3, 
	       events, 
	       events+3);
#elif(COLUMN_MAJOR)
  err = GEMMCL(order, // 1  
	       (d->A.trans =='n')?clAmdBlasNoTrans:clAmdBlasTrans,  //2 
	       (d->B.trans =='n')?clAmdBlasNoTrans:clAmdBlasTrans,  //3
	       d->A.m, //4 
	       d->B.n, //5
	       d->A.n, //6
	       d->A.beta*d->B.beta, //7
	       d->bufA, 0, // 8,9
	       d->A.m, //10 
	       d->bufB,0, //11 12
	       d->B.m, // 13
	       d->C.beta, // 14
	       d->bufC, 0,// 15 16
	       d->C.m, 
	       1, 
	       &(d->queue),
	       3, 
	       events, 
	       events+3);
#endif
  
  if (DEBUG) printf("Sent kernel \n");
  if (err != CL_SUCCESS) {
    printf("clblasSgemmEx() failed with %d\n", err);
    checkErrors(err, "gemm  failed",0); 
    d->result = 1;
    return 1;
  }

  /* Wait for calculations to be finished. */
  //if (DEBUG) printf("Wait for kernel \n");
  //err = clWaitForEvents(1, &event);

#if(ROW_MAJOR)
  if ((d->skip)&8) {ROWWWR(d->C,d->queue, d->bufC,events+3,events+4);}

#elif(COLUMN_MAJOR)
  if ((d->skip)&8) {COLWWR(d->C,d->queue, d->bufC,event+3,events+4);}
#endif
  if (DEBUG)  printf("read result \n");
  /* Fetch results of calculations from GPU memory. */

  /* Wait for calculations to be finished. */
  if (DEBUG) printf("Wait for Write kernel \n");
  err = clWaitForEvents(1, events+4);

  
  if (err != CL_SUCCESS) {
    printf("clblasSgemmEx() failed with %d\n", err);
    d->result = 1;
    return  1;
  }

  if (DEBUG) printf("done \n");
  d->result =0;
  return 0; 

}                                                                   


int PARALLEL = 0;


int
GEMM(DEF(C),DEF(A),DEF(B))
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

int
GEMMA(DEF(C),DEF(A),DEF(B))
{
  int NN;  
  C.beta = _one;
  INITIALIZE;

#if(COLUMN_MAJOR)
  NN = shapes(gpus[0],gpus[ngpus-1],C.m,DEVICES, weights,sizes,indexes);
  if (DEBUG) printf("QUEUE %d \n ", NN);
  QUEUEIT(NN,1,NN);

#elif(ROW_MAJOR)
  NN = shapes(gpus[0],gpus[ngpus-1],C.n,DEVICES, weights,sizes,indexes);
  if (DEBUG) printf("QUEUE %d \n ", NN);
  QUEUEIT(NN,NN,1);
#endif
  
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
    d[j].A=A; d[j].A.m /=NN;  d[j].A.data=A.data+j*d[j].A.m*A.N;
    d[j].B=B; 
    d[j].C=C; d[j].C.n /=NN;  d[j].C.data= C.data+(j-1)*C.N*d[j].C.m;
    d[j].result = 0;
#endif
      
    
    if (DEBUG) printf("%d basic computation %d\n",i,j);
    thr_id[j] = pthread_create(&p_thread[j],
			       NULL, //&attr,
			       basic_mul_computation_gpugemm,
			       (void *)(&d[j]));                                                                                                                                                if(thr_id[j]) {
      
      printf("Error creating thread %d %d\n",j, thr_id[j]);
      return 1;
      
    }
    
  }
  
  for (j = 0; j<NN; j++){						
    pthread_join(p_thread[j], NULL);					
  }									
  WAIT_AND_RELEASE;
  

  if (DEBUG) printf("done\n");
  return ret;
}
 
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
