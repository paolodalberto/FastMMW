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

#include <gpuCompute.h>

  



char *prettyPrintClStatus(cl_int status );

static int DEBUG=0;  
static int DEBUG2=0;  

/* ********************************************************
 *
 * platform and devices are common to all applications.
 *
 */ 


DeviceBookmark bookmarks[DEVICES];

cl_uint platformCount;
cl_platform_id *platforms;
cl_context *ctxs;
int platform=0;

cl_device_id device[DEVICES];
cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
cl_context ctx = 0;
cl_uint ndevices;


/* gpus = 0 in platform 1  is the only one I can use*/ 
int ngpus=4;
int gpus[4] = {0,1,2,3};
//                         Elle       Elle     Fiji         Fiji    


char *_names[DEVICES] =  { "fiji", "fiji", "ellesmere", "ellesmere" }; 
int   _sizes[DEVICES] =  {   3956940,     4148964,      16580608,  16580608};

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
  int i,j,d,k;
  cl_int err;
  int counts=0;
  

  /* we have platforms */
  
  clGetPlatformIDs(0, NULL, &platformCount);
  platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
  ctxs =      (cl_context *)    malloc(sizeof(cl_context) * platformCount);
  clGetPlatformIDs(platformCount, platforms, NULL);
  
  printf("platformCount %d\n",platformCount); 
  d=0;
  for (i = 0; i < platformCount; i++) {
    int GPU=1;
    printf("\n %d %d. Platform \n", i,platform);
    for (j = 0; j < attributeCount; j++) {
      // get platform attribute value size
      clGetPlatformInfo(platforms[i], attributeTypes[j], 0, NULL, &infoSize);
      info = (char*) malloc(infoSize);
      
      // get platform attribute value
      clGetPlatformInfo(platforms[i], attributeTypes[j], infoSize, info, NULL);
      printf("  %d.%d %-11s: %s\n", i+1, j+1, attributeNames[j], info);
      free(info);
    }

    // devices per platform
    
    err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, DEVICES-d, device + d, &k);
    if (err != CL_SUCCESS) {
      GPU=0;
      printf( "clGetDeviceIDs() failed with %d\n", err );
      err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ACCELERATOR, DEVICES-d, device + d, &k);
      if (err != CL_SUCCESS) {
	checkErrors(err,"clGetDeviceIDs",10);
	printf( "clGetDeviceIDs() failed with %d\n", err );
	return 1;
      }
      else {
	deviceInformation( device+d,k);  printf("N of ACCS %d \n",k);
      }
      
    } else {
      deviceInformation( device+d,k);  printf("N of GPUS %d \n",k);      // for each device print critical attributes
    }

    
    // context per platform
    props[1] = (cl_context_properties)platforms[i];
    printf(" context %i  %d at %d %d=%d GPU=%d \n", i, k,d,props[1],CL_CONTEXT_PLATFORM,GPU);
    //ctxs[i] = clCreateContext(props, k , device+d, NULL, NULL, &err);
    ctxs[i] = clCreateContextFromType(props, (GPU)?CL_DEVICE_TYPE_GPU:CL_DEVICE_TYPE_ACCELERATOR,NULL, NULL, &err);
    printf(" <> counts %d \n", counts);
    if (err != CL_SUCCESS) {
      checkErrors(err,"create context",158);
      printf( "clCreateContext() failed with %d\n", err );
      return 1;
    }
    
    for ( int m=0; m<k; m++) { // for each device in this platform
      {
	
	cl_ulong buf_ulong;
	size_t valueSize;
	// print device memory size
	cl_int err ;
	printf(" counts %d \n", counts);
	err = clGetDeviceInfo(device[d+m], CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(buf_ulong), &buf_ulong, NULL);
	switch (err) {
	case CL_INVALID_DEVICE:
	  printf(" CL_INVALID_DEVICE\n");
	case CL_INVALID_VALUE:
	  printf(" CL_INVALID_VALUE\n");
	case CL_SUCCESS:
	  break;
	}
	_sizes[counts] = buf_ulong/1024;
	printf(" %d %d Global Memory: %lu KB %d\n", device[m+d],m, buf_ulong/(1024),_sizes[counts]);
	
	// We change the buffer size so we can dynamic algorithm
	
      
	bookmarks[counts].platform = platforms+i;
	bookmarks[counts].ctx = ctxs +i;
	bookmarks[counts].device =  device +d+m ;
	bookmarks[counts].i =  counts ;
	
	err = clGetDeviceInfo(device[m+d], CL_DEVICE_NAME, 0, NULL, &valueSize);
	switch (err) {
	case CL_INVALID_DEVICE:
	  printf(" CL_INVALID_DEVICE\n");
	case CL_INVALID_VALUE:
	  printf(" CL_INVALID_VALUE\n");
	case CL_SUCCESS:
	  break;
	}
	bookmarks[counts].name = (char*) malloc(valueSize);
	err = clGetDeviceInfo(device[m+d], CL_DEVICE_NAME, valueSize, bookmarks[counts].name, NULL);
	switch (err) {
	case CL_INVALID_DEVICE:
	  printf(" CL_INVALID_DEVICE\n");
	case CL_INVALID_VALUE:
	  printf(" CL_INVALID_VALUE\n");
	case CL_SUCCESS:
	  break;
	}
	printf(" %d Name %s \n", valueSize,bookmarks[counts].name); 

	bookmarks[counts].size = _sizes[counts] ;
	bookmarks[counts].gpu = counts;
	gpus[counts] = counts;
	
	counts +=1;
      }
    }

    d += k;
    
  }
  
  
  

  //err = clAmdBlasSetup();
  if (err != CL_SUCCESS) {
    printf("clblasSetup() failed with %d\n", err);

    for (int m=0; m<platformCount; m++) 
      clReleaseContext(ctxs[m]);
    free(platforms);
    free(ctxs);
    
    return 1;
  }
  
  return 0;
}
int  relase_devices_names() {
  char* info;
  size_t infoSize;
  const char* attributeNames[5] = { "Name", "Vendor",
				    "Version", "Profile", "Extensions" };
  const cl_platform_info attributeTypes[5] = { CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,
					       CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE, CL_PLATFORM_EXTENSIONS };
  const int attributeCount = sizeof(attributeNames) / sizeof(char*);
  int i,j,d,k;
  cl_int err;
  int counts=0;
  

  /* we have platforms */
  
  
  d=0;
  for (i = 0; i < platformCount; i++) {
    err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, DEVICES, device + d, &k);
    if (err != CL_SUCCESS) {
      printf( "clGetDeviceIDs() failed with %d\n", err );
      err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ACCELERATOR, DEVICES, device + d, &k);
      if (err != CL_SUCCESS) {
	checkErrors(err,"clGetDeviceIDs",10);
	printf( "clGetDeviceIDs() failed with %d\n", err );
	return 1;
      }
    }
    for ( int m=0; m<k; m++) { // for each device in this platform
      {
	free(bookmarks[counts].name);
	counts +=1;
      }
    }

    d += k;
    
  }
  
  
  

  //err = clAmdBlasSetup();
  free(ctxs);
  free(platforms);

  
  
  return 0;
}


void release_blas_context() {

  //clAmdBlasTeardown();
  
  //  clReleaseContext(ctx);
  for (int m=0; m<platformCount; m++) 
    clReleaseContext(ctxs[m]);
  free(platforms);
  free(ctxs);
  

}








char *prettyPrintClStatus(cl_int status )
{
	switch( status )
	{
		case CL_INVALID_GLOBAL_WORK_SIZE:
			return "CL_INVALID_GLOBAL_WORK_SIZE";
		case CL_INVALID_MIP_LEVEL:
			return "CL_INVALID_MIP_LEVEL";
		case CL_INVALID_BUFFER_SIZE:
			return "CL_INVALID_BUFFER_SIZE";
		case CL_INVALID_GL_OBJECT:
			return "CL_INVALID_GL_OBJECT";
		case CL_INVALID_OPERATION:
			return "CL_INVALID_OPERATION";
		case CL_INVALID_EVENT:
			return "CL_INVALID_EVENT";
		case CL_INVALID_EVENT_WAIT_LIST:
			return "CL_INVALID_EVENT_WAIT_LIST";
		case CL_INVALID_GLOBAL_OFFSET:
			return "CL_INVALID_GLOBAL_OFFSET";
		case CL_INVALID_WORK_ITEM_SIZE:
			return "CL_INVALID_WORK_ITEM_SIZE";
		case CL_INVALID_WORK_GROUP_SIZE:
			return "CL_INVALID_WORK_GROUP_SIZE";
		case CL_INVALID_WORK_DIMENSION:
			return "CL_INVALID_WORK_DIMENSION";
		case CL_INVALID_KERNEL_ARGS:
			return "CL_INVALID_KERNEL_ARGS";
		case CL_INVALID_ARG_SIZE:
			return "CL_INVALID_ARG_SIZE";
		case CL_INVALID_ARG_VALUE:
			return "CL_INVALID_ARG_VALUE";
		case CL_INVALID_ARG_INDEX:
			return "CL_INVALID_ARG_INDEX";
		case CL_INVALID_KERNEL:
			return "CL_INVALID_KERNEL";
		case CL_INVALID_KERNEL_DEFINITION:
			return "CL_INVALID_KERNEL_DEFINITION";
		case CL_INVALID_KERNEL_NAME:
			return "CL_INVALID_KERNEL_NAME";
		case CL_INVALID_PROGRAM_EXECUTABLE:
			return "CL_INVALID_PROGRAM_EXECUTABLE";
		case CL_INVALID_PROGRAM:
			return "CL_INVALID_PROGRAM";
		case CL_INVALID_BUILD_OPTIONS:
			return "CL_INVALID_BUILD_OPTIONS";
		case CL_INVALID_BINARY:
			return "CL_INVALID_BINARY";
		case CL_INVALID_SAMPLER:
			return "CL_INVALID_SAMPLER";
		case CL_INVALID_IMAGE_SIZE:
			return "CL_INVALID_IMAGE_SIZE";
		case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
			return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
		case CL_INVALID_MEM_OBJECT:
			return "CL_INVALID_MEM_OBJECT";
		case CL_INVALID_HOST_PTR:
			return "CL_INVALID_HOST_PTR";
		case CL_INVALID_COMMAND_QUEUE:
			return "CL_INVALID_COMMAND_QUEUE";
		case CL_INVALID_QUEUE_PROPERTIES:
			return "CL_INVALID_QUEUE_PROPERTIES";
		case CL_INVALID_CONTEXT:
			return "CL_INVALID_CONTEXT";
		case CL_INVALID_DEVICE:
			return "CL_INVALID_DEVICE";
		case CL_INVALID_PLATFORM:
			return "CL_INVALID_PLATFORM";
		case CL_INVALID_DEVICE_TYPE:
			return "CL_INVALID_DEVICE_TYPE";
		case CL_INVALID_VALUE:
			return "CL_INVALID_VALUE";
		case CL_MAP_FAILURE:
			return "CL_MAP_FAILURE";
		case CL_BUILD_PROGRAM_FAILURE:
			return "CL_BUILD_PROGRAM_FAILURE";
		case CL_IMAGE_FORMAT_NOT_SUPPORTED:
			return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
		case CL_IMAGE_FORMAT_MISMATCH:
			return "CL_IMAGE_FORMAT_MISMATCH";
		case CL_MEM_COPY_OVERLAP:
			return "CL_MEM_COPY_OVERLAP";
		case CL_PROFILING_INFO_NOT_AVAILABLE:
			return "CL_PROFILING_INFO_NOT_AVAILABLE";
		case CL_OUT_OF_HOST_MEMORY:
			return "CL_OUT_OF_HOST_MEMORY";
		case CL_OUT_OF_RESOURCES:
			return "CL_OUT_OF_RESOURCES";
		case CL_MEM_OBJECT_ALLOCATION_FAILURE:
			return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
		case CL_COMPILER_NOT_AVAILABLE:
			return "CL_COMPILER_NOT_AVAILABLE";
		case CL_DEVICE_NOT_AVAILABLE:
			return "CL_DEVICE_NOT_AVAILABLE";
		case CL_DEVICE_NOT_FOUND:
			return "CL_DEVICE_NOT_FOUND";
		case CL_SUCCESS:
			return "CL_SUCCESS";
		default:
			return "Error code not defined";
		break;
	}
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
    printf(" %d.0 Device: %s\n", j, value);
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

    // We change the buffer size so we can dynamic algorithm
    //if (ndevices>1) _sizes[j] = buf_ulong;
    
    clGetDeviceInfo(device[j], CL_DEVICE_LOCAL_MEM_SIZE,sizeof(buf_ulong), &buf_ulong, NULL);
    printf(" %d.%d Local Memory: %lu KB\n", j, 6, buf_ulong/(1024));
    
    clGetDeviceInfo(device[j], CL_DEVICE_HOST_UNIFIED_MEMORY,sizeof(buf_ulong), &buf_ulong, NULL);
    printf(" %d.%d Unified Memory: %lu\n", j, 6, buf_ulong);
    
    

    
  }
  
  return 0;
}
