



#ifndef ROCGPUCOMPUTE
#define ROCGPUCOMPUTE


/* Include CLBLAS header. It automatically includes needed OpenCL header,
   * so we can drop out explicit inclusion of cl.h header.
   */

#include <pt.h>
  
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

  
#define DEVICES    5
#define PLATFORMS  2

/// Assume we can define a gemm function that is specific to the type,
/// device and opencl

struct rocm_device_structure {
  char name[256];
  int size;
  int gpu;
};

typedef struct rocm_device_structure RocmDeviceBookmark;

  


#include <architecture.h>

#if(HALF_PRECISION)
#define DATATYPE rocblas_half
static const DATATYPE            alpha_zero = 0.0;  
static const DATATYPE            alpha_one = 1.0;  
static const DATATYPE            beta  = 1.0;
#elif(SINGLE_PRECISION)
#define DATATYPE float
static const DATATYPE            alpha_zero = 0.0;  
static const DATATYPE            alpha_one = 1.0;  
static const DATATYPE            beta  = 1.0;
#elif(DOUBLE_PRECISION)
#define DATATYPE double
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



#endif
