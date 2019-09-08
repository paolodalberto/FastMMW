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

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif
#include <gpuCompute.h>

  



extern char *prettyPrintClStatus(cl_int status );
extern DeviceBookmark bookmarks[DEVICES];
extern int ngpus;
extern int gpus[DEVICES];
extern cl_device_id device[DEVICES];

static int DEBUG=0;  
static int DEBUG2=0;  

/* ********************************************************
 *
 * platform and devices are common to all applications.
 *
 */ 



int  shapes(int start, int end, int M,
	    int l,int *weights,  int *size, int *indexes) {
  
  int i;
  int n = 0;

  int parts = 0;
  
  for (i=start; i<l && i<= end; i++,parts++)
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

  
  return parts;
}








void *basic_mul_computation_gpugemm(void *arg) {  
  cl_int err;
  cl_event events[6];
  Mat tempalpha, tempbeta;  // in complex format these are double complex or float complex 
  DATATYPE alpha, beta;     // to use OpenCL these can be DoubleComplex and FloatComplex 
  GPUData *d =  (GPUData *)arg;
  int skipc = (d->C.beta == _zero)?0:1;
  
  if (DEBUG2) {
    printf("GPU %d \n",d->C.gpu);
    printf("Name %s GPU %d\n", bookmarks[gpus[d->C.gpu]].name,d->C.gpu);
    //deviceName( &(d->id),d->C.gpu);
  }
  
  if (DEBUG) {
    size_t r;
    cl_int e = clGetMemObjectInfo (d->bufA,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("GPU %d BUF A size %ld M %d %ldM\n",d->C.gpu,r/1024/1024,e,(long)d->A.m*d->A.n*sizeof(Mat)/1024/1024);
    checkErrors(e, "read A",0);
    e = clGetMemObjectInfo (d->bufB,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("GPU %d BUF B size %d %ld M %ldM\n",d->C.gpu,r/1024/1024,e,(long)d->B.m*d->B.n*sizeof(Mat)/1024/1024);
    checkErrors(e, "read B",0);
    e = clGetMemObjectInfo (d->bufC,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("GPU %d BUF C size %d %ld %ldM\n",d->C.gpu,r/1024/1024,e,(long)d->C.m*d->C.n*sizeof(Mat)/1024/1024);
    checkErrors(e, "read C",0);
    printf("GPU %d       A %d x %d %d x %d %c- \n",d->C.gpu,d->A.m, d->A.n,d->A.M,d->A.N, d->A.trans);
    printf("GPU %d       B %d x %d %d x %d %c- \n",d->C.gpu,d->B.m, d->B.n,d->B.M,d->B.N, d->B.trans);
    printf("GPU %d s%d  C %d x %d %d x %d %c- \n",d->C.gpu,skipc,d->C.m, d->C.n,d->C.M,d->C.N, d->C.trans);
  }
  
#if(ROW_MAJOR)
  if (DEBUG) printf("GPU %d Sending Row Data \n",d->C.gpu);
  if ((d->skip)&1) { ROWAAR(d->A,d->queue, d->bufA,&events[0],0);}
  if (DEBUG) printf("GPU %d Sending Row Data \n",d->C.gpu);
  if ((d->skip)&2) { ROWAAR(d->B,d->queue, d->bufB,&events[1],1);}
  if (DEBUG) printf("GPU %d Sending Row Data \n",d->C.gpu);
  if (skipc && (d->skip)&4) { ROWAAR(d->C,d->queue, d->bufC,&events[2],2);}
#elif(COLUMN_MAJOR)
  if (DEBUG) printf("GPU %d Sending Col Data \n",d->C.gpu);
  if ((d->skip)&1) {COLAAR(d->A,d->queue, d->bufA,&events[0],0);}
  if ((d->skip)&2) {COLAAR(d->B,d->queue, d->bufB,&events[1],1); }
  if (skipc && (d->skip)&4) {COLAAR(d->C,d->queue, d->bufC,&events[2],2);}
#endif

  
  
  if (DEBUG) printf("GPU %d Wait for read kernel \n",d->C.gpu);
  err = clWaitForEvents((skipc==0)?2:3, events);
  if (err !=CL_SUCCESS) { 
    checkErrors(err, "write  failed",0);
    if (DEBUG) printf("GPU %d Wait for read kernel \n",d->C.gpu);
    
  }
  if (DEBUG) printf("GPU %d Sent Data \n",d->C.gpu);
    
  
 
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)  
  if (1) { 
    DATATYPE al = {creal(d->A.beta*d->B.beta),cimag(d->A.beta*d->B.beta)};
    DATATYPE bl = {creal(d->C.beta),cimag(d->C.beta)};
    alpha= al;
    beta = bl;
    
    if (DEBUG) {
      printf("GPU %d Sending  kernel \n",d->C.gpu);
      printf("GPU %d  Alpha %f %f Beta %f %f \n",d->C.gpu, alpha.s[0], alpha.s[1], beta.s[0], beta.s[1]);
      
    }
    /*  alpha.s[0]= creal(d->A.beta*d->B.beta);
	alpha.s[1]= cimag(d->A.beta*d->B.beta);
	beta.s[0] = creal(d->C.beta);
	beta.s[1] = cimag(d->C.beta); */
  }
#else
  alpha = d->A.beta*d->B.beta;
  beta  = d->C.beta;
  if (DEBUG) {
    printf("GPU %d Sending  kernel \n",d->C.gpu);
    printf("GPU %d  Alpha %f  Beta  %f \n",d->C.gpu, alpha,  beta);
    
  }
#endif  

#if(ROW_MAJOR)
  err = GEMMCL(
	       order, // 1  
	       (d->A.trans =='n')?notransA:transA,  //2 
	       (d->B.trans =='n')?notransA:transA,
	       d->A.m, //4 
	       d->B.n, //5
	       d->A.n, //6
	       alpha, //7
	       d->bufA,
	       0, // 8,9
	       d->A.n, //10
	       d->bufB,
	       0, //11 12
	       d->B.n, //13
	       beta, // 14
	       d->bufC,
	       0,// 15 16
	       d->C.n, //17
	       &(d->queue),
	       events+3);
#elif(COLUMN_MAJOR)
  err = GEMMCL(order, // 1  
	       (d->A.trans =='n')?notransA:transA,  //2 
	       (d->B.trans =='n')?notransA:transA,  //3
	       d->A.m, //4 
	       d->B.n, //5
	       d->A.n, //6
	       alpha, //7
	       d->bufA, 0, // 8,9
	       d->A.m, //10 
	       d->bufB,0, //11 12
	       d->B.m, // 13
	       beta, // 14
	       d->bufC, 0,// 15 16
	       d->C.m, 
	       &(d->queue),
	       events+3);
#endif
  
  if (DEBUG) printf("GPU %d Sent kernel \n",d->C.gpu);
  if (err != CL_SUCCESS) {
    size_t r;
    cl_int e = clGetMemObjectInfo (d->bufA,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("GPU %d BUF A size %ld M %ld %d \n",d->C.gpu,r/1024/1024,(long)(d->A.m)*(d->A.n)*sizeof(Mat),e);
    checkErrors(e, "read A",0);
    e = clGetMemObjectInfo (d->bufB,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("GPU %d BUF B size %ld M %ld %d \n",d->C.gpu,r/1024/1024,(long)d->B.m*d->B.n*sizeof(Mat),e);
    checkErrors(e, "read B",0);
    e = clGetMemObjectInfo (d->bufC,CL_MEM_SIZE,sizeof(r),&r,NULL);
    printf("GPU %d BUF C size %ld M %ld %d \n",d->C.gpu,r/1024/1024,(long)d->C.m*d->C.n*sizeof(Mat),e);
    
#if(ROW_MAJOR)
    printf("GPU %d Row Major and order %d %d %d \n",d->C.gpu,order,
	   (d->A.trans =='n')?notransA:transA,(d->B.trans =='n')?notransA:transA);
#elif(COLUMN_MAJOR)
    printf("GPU %d Column Major and order %d %d %d ",d->C.gpu,order,
	   (d->A.trans =='n')?notransA:transA,
	   (d->B.trans =='n')?notransA:transA);
#endif
    
    checkErrors(e, "read C",0);
    printf("GPU %d     A m=%d x n=%d from %d x %d gpu %d\n",d->C.gpu,d->A.m, d->A.n,d->A.M,d->A.N,d->A.gpu);
    printf("GPU %d     B m=%d x n=%d from %d x %d gpu %d\n",d->C.gpu,d->B.m, d->B.n,d->B.M,d->B.N,d->B.gpu);
    printf("GPU %d     C m=%d x n=%d from %d x %d gpu %d\n",d->C.gpu,d->C.m, d->C.n,d->C.M,d->C.N,d->C.gpu);
    printf("GPU %d     A.n %d   B.n %d   C.n %d \n",d->C.gpu,d->A.n, d->B.n,d->C.n);
    printf("GPU %d     A.m %d   B.m %d   C.m %d \n",d->C.gpu,d->A.m, d->B.m,d->C.m);
    printf("GPU %d   A.m m=%d B.n n=%d B.m k=%d \n",d->C.gpu,d->A.m, d->B.n,d->B.m);
    printf("GPU %d clblasSgemmEx() failed with %d\n",d->C.gpu, err);
    printf("GPU %d %s\n",d->C.gpu, prettyPrintClStatus(err));
    printf("GPU %d \n",d->C.gpu);
    deviceInformation( &(d->id),1);
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
  if (DEBUG)  printf("GPU %d read result \n",d->C.gpu);
  /* Fetch results of calculations from GPU memory. */

  /* Wait for calculations to be finished. */
  if (DEBUG) printf("GPU %d Wait for Write kernel \n",d->C.gpu);
  err = clWaitForEvents(1, events+4);

  
  if (err != CL_SUCCESS) {
    printf("GPU %d clblasSgemmEx() failed with %d\n",d->C.gpu, err);
    d->result = 1;
    return  1;
  }

  if (DEBUG) printf("GPU %d done \n",d->C.gpu);
  d->result =0;
  return 0; 

}                                                                   


int PARALLEL = 0;

static inline int TEMPLATE(DEF(C),DEF(A), DEF(B),int ngpus, int *gpus) {
  INITIALIZE;			
  
  if (DEBUG) {
    printf("GPU %d  TEMPLATE size of the matrix element %d\n",gpus[0], sizeof(A.beta));
    printf("GPU %d  You selected the following problem \n",gpus[0]);
    printf("GPU %d       A %d x %d %f\n",gpus[0], A.m,A.n, A.beta);
    printf("GPU %d       B %d x %d %f \n",gpus[0],B.m,B.n,B.beta);
    printf("GPU %d  Thus C %d x %d %f \n",gpus[0],C.m, C.n, C.beta);
    printf("GPU %d Shape %d - %d  ",gpus[0],gpus[0],gpus[ngpus-1]);	
  }
#if(COLUMN_MAJOR)						
  NN = shapes(gpus[0],gpus[ngpus-1],C.m,DEVICES, weights,sizes,indexes); 
  if (DEBUG) printf("GPU %d QUEUE CM %d \n",gpus[0], NN);				
  QUEUEIT(1,NN,NN);							
#elif(ROW_MAJOR)							
  NN = shapes(gpus[0],gpus[ngpus-1],C.n,DEVICES, weights,sizes,indexes);  
  if (DEBUG) printf("GPU %d QUEUE RM %d \n",gpus[0], NN);				
  QUEUEIT((NN),(1),(NN));							
#endif								
									
  if (DEBUG) {
    printf("GPU %d Partition GEMM\n",gpus[0]);
    printf("GPU %d Weights:",gpus[0]);for  (int i=0; i< DEVICES; i++) printf("%d ",weights[i]); printf("\n");
    printf("GPU %d Sizes  :",gpus[0]);for  (int i=0; i< DEVICES; i++) printf("%d ",sizes[i]); printf("\n");
    printf("GPU %d Indexes:",gpus[0]);for  (int i=0; i< DEVICES; i++) printf("%d ",indexes[i]); printf("\n");
  }
  /* Prepare OpenCL memory objects and place matrices inside them. */	

  if (NN>1) { 
    for (j=0; j<NN;j++) {
      if (DEBUG) printf("basic computation %d %d \n", j,gpus[j]);
      
      d[j].id = bookmarks[gpus[j]].device; 
      d[j].queue = queue[gpus[j]];
      d[j].bufA=bufA[gpus[j]];    d[j].bufB=bufB[gpus[j]];    d[j].bufC=bufC[gpus[j]];
      
#if(COLUMN_MAJOR)
      d[j].A=A;
      d[j].B=B; d[j].B.n = sizes[gpus[j]];
      d[j].B.data=B.data+indexes[gpus[j]];
      d[j].C=C; d[j].C.n =sizes[j];  d[j].C.data= C.data+indexes[gpus[j]];
      d[j].result = 0;
#elif(ROW_MAJOR)
      d[j].A=A; d[j].A.m =sizes[gpus[j]];  d[j].A.data= A.data+indexes[gpus[j]];
      d[j].B=B; 
      d[j].C=C; d[j].C.m =sizes[gpus[j]];  d[j].C.data= C.data+indexes[gpus[j]];
      d[j].result = 0;
#endif
    }   
  } else {
    j=0;
    d[j].id = bookmarks[gpus[j]].device; 
    d[j].queue = queue[gpus[j]];
    d[j].bufA=bufA[gpus[j]];    d[j].bufB=bufB[gpus[j]];    d[j].bufC=bufC[gpus[j]];
    d[j].A=A;
    d[j].B=B; 
    d[j].C=C; 
    d[j].result = 0;
  }
  
  if (DEBUG) printf("GPU %d %d basic computation %d\n",gpus[0],i,j);
  
  if (PARALLEL) {
    for (j=0; j<NN;j++) {
      thr_id[j] = pthread_create(&p_thread[j],
				 NULL, //&attr,
				 basic_mul_computation_gpugemm,
				 (void *)(&d[j]));
      if(thr_id[j]) {
	
	printf("GPU %d Error creating thread %d %d\n",gpus[0],j, thr_id[j]);
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
  if (DEBUG) printf("GPU %d Wait and release \n ",gpus[0]);
  WAIT_AND_RELEASE;

  if (DEBUG) printf("GPU %d done\n",gpus[0]);
  return ret;
}  


// MUL with the basic interface. We will customize the name as
// function of the type and device.

int
GEMM(DEF(C),DEF(A),DEF(B))
{
  int NN;
  C.beta = _zero;
  if (C.gpu>=0 && C.gpu<DEVICES) {
    //printf("gpu %d \n",C.gpu); 
    return TEMPLATE(C,A,B,1,&(C.gpu));
  } else
    return TEMPLATE(C,A,B,ngpus,gpus);
}

// MADD
int
GEMMA(DEF(C),DEF(A),DEF(B))
{
  int NN;  
  C.beta = _one;
  if (C.gpu>=0 && C.gpu<DEVICES)
    return TEMPLATE(C,A,B,1,&(C.gpu));
  else
    return TEMPLATE(C,A,B,ngpus,gpus);
}


