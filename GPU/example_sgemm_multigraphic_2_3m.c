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
  



// turk PCI-E 16  0 
// Fiji 1
// Fiji 2  ProDuo into PCIE-2 (4)
// Hawaii 3
// Hawaii 4 295x2 PCIE-1 16

                     
int weights[DEVICES] = {0,1,1,2,2,0};
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
    cl_platform_id platform = 0;
    cl_device_id device[DEVICES];
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context ctx = 0;
    cl_command_queue queue[DEVICES];
    cl_mem bufA[DEVICES], bufB[DEVICES], bufC[DEVICES];
    cl_mem bufAL[DEVICES], bufBL[DEVICES], bufCL[DEVICES];
    cl_mem bufCLL[DEVICES];
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

    /// Split Kernel 
    const char split[] = "

#define SPLIT(Z,high,low)          {  high = (float)Z; low = (float) ((Z-(double)high)); }    
#define COMBINE(Z,high,medium,low) {  Z = ((double)low) + ((double)medium)+((double)high); }  


__kernel  void split_double_into_float(
			     __global double* C,  // output
			     int order,           // everything below here are inputs: order =1 rowmajor 
			     __global float*  CH, // regular  
			     __global float*  CL, // *2^(-h)
			     int M,               // rows
			     int N,               // columns 
			     int T                //  tiles         
			     ) {
  
  long i;
  int id  = get_global_id(0);
  int k ;
  

  if (order) // by row computation full all the way to the end of the
	     // rows
    for (i=; i<T && i+id<M; i++)
      for (j=0;j<N; j++){
	k =((i+id)*N +j) 
        SPLIT(C[k],CH[k],CL[k] 

      }
  else  // by column, as above 
    for (j=0;j<T && j+id<N; j++)
      for (i=;i<M;i++){
	k =(i +(j+id)*M);
        SPLIT(C[k],CH[k],CL[k] 
      }
} 

__kernel void combine_floats_into_double(
					 __global double* C,   // output 
					 int order,            // 1 row major       
					 __global float*  CH,  // 
					 __global float*  CL,  // 2^(-h)
					 __global float*  CLL, // 2^(-2h)
					 int M,                // row
					 int N,                // columns  
					 int T                 // tiles
					 ) { 

  int i,j;
  double temp, sum;
  int id = get_global_id(0);
  int k ;
  double c;

  if (order) 
    for (i=;i<T && i+id<M;i++)
      for (j=0;j<N; j++){
	k =((i+id)*N +j);
        COMBINE(C[k],CH[k],CL[k],CLL[k])
      }
  else
    for (j=0;j<T && j+id<N; j++)
      for (i=;i<M;i++) {
	k = (i +(j+id)*M);
        COMBINE(C[k],CH[k],CL[k],CLL[k])
      }
    
}
";


    //printf("ARGC %d \n", argc);
    //for (i=0; i<argc;i++) 
    //  printf("%s \n ", argv[i]);
      
    if (argc==6) {
      gpu = atoi(argv[1]);
      M = atoi(argv[2]);
      N = atoi(argv[3]);
      K = atoi(argv[4]);
      Times = atoi(argv[5]);
    } else   if (argc==7) {
      gpu = atoi(argv[1]);
      M = atoi(argv[2]);
      N = atoi(argv[3]);
      K = atoi(argv[4]);
      Times = atoi(argv[5]);
      gpu2 = atoi(argv[6]);
    } else if (argc==8) {
      gpu = atoi(argv[1]);
      M = atoi(argv[2]);
      N = atoi(argv[3]);
      K = atoi(argv[4]);
      Times = atoi(argv[5]);
      gpu2 = atoi(argv[6]);
      REUSEB= atoi(argv[7]);
    }

      

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, &NN);
    
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return 1;
    }
    printf("Number of platforms %d", NN);
    
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, DEVICES, device,&ndevices);
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
    //if (M%(gpu2-gpu) != 0) {
    //  M = M +(M%(gpu2-gpu));
    //}
    printf("initialize matrices\n");

    

    
    // this is the poor double precision using complex computation
    // ideas. we use double for precision and not for range and we
    // will loose 7 bits conversion out of the bat (poor double
    // precision)
    
      
    


    DATATYPE *A = (DATATYPE*) malloc(M*K*sizeof(DATATYPE));
    DATATYPE *B = (DATATYPE*) malloc(N*K*sizeof(DATATYPE));
    DATATYPE *C  = (CDATATYPE*) malloc(M*N*sizeof(DATATYPE));
    
    
    for (i=0;i<M;i++)
      for (j=0;j<K;j++)  
	A[i*K+j] = 1.0/(i+j+1);
    for (i=0;i<K;i++)
      for (j=0;j<N;j++) 
	B[i*N+j] = 1.0/(i+j+1);
    for (i=0;i<M;i++)
      for (j=0;j<N;j++) 
	C[i*M+j] = 1.0/(i+j+1);
	
       
    printf("initialize done \n");



    props[1] = (cl_context_properties)platform;
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
      
      bufC[j] = clCreateBuffer(ctx, CL_MEM_READ_WRITE, sizes[j] * N * sizeof(*A),
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

    int ls =strlen(split);
    cl_program spl = clCreateProgramWithSource(ctx, 1, &split, &ls, &ret);
    ret = clBuildProgram(spl, gpu2-gpu1, device + gpu, NULL, NULL, NULL);

   
    for (j =gpu; j<gpu2;j++) {
      cl_int ret;


      d[j].split =  clCreateKernel(spl, "split_double_into_float", &ret);
      d[j].combine =  clCreateKernel(spl, "combine_floats_into_double", &ret);
      
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
    basic_mul_computation_shared_pd(d+gpu);
    d[gpu].warmup = 0;
 
    for (i=0; i<Times; i++) {
  
      if (DEBUG) printf("basic computation\n");
      basic_mul_computation_shared_pd(d+gpu);
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


