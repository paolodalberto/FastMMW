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
#define ALPHA 10.0
#define BETA  10.0
#define GEMM  clblasSgemm
#endif

#define DEVICES 6

#include <header.h>
   



// turk PCI-E 16  0 
// Fiji 1
// Fiji 2  ProDuo into PCIE-2 (4)
// Hawaii 3
// Hawaii 4 295x2 PCIE-1 16

                     
int weights[DEVICES] = {1,1,1,1,0,0};
int sizes[DEVICES]   = {1,1,1,1,1,1};
int indexes[DEVICES]   = {1,1,1,1,1,1};
int  shapes(int start, int end, int M, 
	    int l,int *weights,  int *size, int *indexes) {
  
  int i;
  int n = 0;
  
  for (i=start; i<l && i< end; i++)
    n += weights[i]; // number of partitions.

  for (i=start; i<l && i< end; i++)
    size[i] = M*weights[i]/n;

  if (M%n!= 0 ) 
    size[i-1] = M*weights[i-1]/n+ (M%n); 

  indexes[start] =0 ;
  for (i=start+1; i<l && i< end; i++)
    indexes[i] = indexes[i-1] + size[i-1];

  printf("M mod n = %d M=%d n=%d \n",M%n,M,n);
  for (i=start; i<l && i< end;i++)
    printf("s[%d] = %d and i[%d] = %d \n",i,size[i],i,indexes[i]);
  


  return n;
}

int
main(int argc, char **argv)
{
    cl_int err;
    cl_uint platformCount;
    cl_platform_id *platforms;
    int platform=0;
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
    DCMul    d[NUM_THREADS];
    int REUSEB = 0;
    int gpu2=DEVICES;
    cl_uint NN;
    char* info;
    size_t infoSize;
    const char* attributeNames[5] = { "Name", "Vendor",
        "Version", "Profile", "Extensions" };
    const cl_platform_info attributeTypes[5] = { CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,
        CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE, CL_PLATFORM_EXTENSIONS };
    const int attributeCount = sizeof(attributeNames) / sizeof(char*);


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
      REUSEB= atoi(argv[8]);
    }

      

    /* Setup OpenCL environment. */
        // get all platforms
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
    if (gpu2 > ndevices) gpu2= ndevices;
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return 1;
    } else { 

      deviceInformation( device,ndevices);


      printf("N of GPUS %d \n",ndevices);
      // for each device print critical attributes


    }
    
    

    printf("initialize matrices\n");
 
    DATATYPE *A = (DATATYPE*) malloc(M*K*sizeof(DATATYPE));
    DATATYPE *B  = (DATATYPE*) malloc(N*K*sizeof(DATATYPE));
    DATATYPE *C = (DATATYPE*) malloc(M*N*sizeof(DATATYPE));
    
#ifndef COMPLEX
    
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

    NN = shapes(gpu,gpu2,M,DEVICES, weights,sizes,indexes);


    for (j =gpu; j<gpu2;j++){ 
      
      printf("M = %d, N = %d, K = %d \n", sizes[j],N,K);
      queue[j] = clCreateCommandQueue(ctx, device[j], 0, &err);
      
      bufA[j] = clCreateBuffer(ctx, CL_MEM_READ_ONLY, sizes[j] * K * sizeof(*A),
			       NULL, &err);
      

      bufB[j] = clCreateBuffer(ctx, CL_MEM_READ_ONLY, K * N * sizeof(*B),      
				 NULL, &err);
      
      bufC[j] = clCreateBuffer(ctx, CL_MEM_READ_WRITE, sizes[j] * N * sizeof(*C),
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
        for (j =1; j<gpu2;j++)
	  clReleaseCommandQueue(queue[j]);
        clReleaseContext(ctx);
        return 1;
    }
    printf("Start %f %f %f \n",*A,*B,*C);
    for (j=gpu; j<gpu2; j++)  {
      printf("Qs %lu \n",(long unsigned int) queue[j]);
      printf("bufA %lu bufB %lu bufC %lu \n",(long unsigned int)bufA[j],
	     (long unsigned int)bufB[j],
	     (long unsigned int)bufC[j]);
    }

    
    START_CLOCK;
    


    /* Prepare OpenCL memory objects and place matrices inside them. */


    for (j =gpu; j<gpu2;j++) {
      d[j].id = device[j]; 
      d[j].queue = queue[j];
      d[j].bufA=bufA[j];
      d[j].bufB=bufB[j];
      d[j].bufC=bufC[j];
      d[j].A=A+indexes[j];
      d[j].B=B;
      d[j].C=C+indexes[j];
      d[j].M=sizes[j];
      d[j].N=N;
      d[j].K=K;
      d[j].result = REUSEB;
      d[j].self = j;
      d[j].sibling = gpu2-j;
    }

    d[gpu].warmup = 1;
    basic_mul_computation_shared(d+gpu);
    d[gpu].warmup = 0;
 
    for (i=0; i<Times; i++) {
  
      if (DEBUG) printf("basic computation\n");
      basic_mul_computation_shared(d+gpu);

    }
    
    
    END_CLOCK;
    
    printf("N %d-%d GFLOPS %f \n", gpu,gpu2, Times*(M/1000.0)*(N/1000.0)*(K/1000.0)*2/duration );
    /* Release OpenCL memory objects. */
    
    for (j=gpu;j<gpu2;j++) { 
      clReleaseMemObject(bufC[j]);
      clReleaseMemObject(bufB[j]);
      clReleaseMemObject(bufA[j]);
    }	   


    /* Finalize work with clblas. */
    printf("clAmdBlasTeardown\n");
    clAmdBlasTeardown();
    
    
    printf("release queue\n");
    /* Release OpenCL working objects. */
    for (j=gpu;j<gpu2;j++) { 
      clReleaseCommandQueue(queue[j]);
    }
    clReleaseContext(ctx);
    printf("done\n");
    return ret;
}
