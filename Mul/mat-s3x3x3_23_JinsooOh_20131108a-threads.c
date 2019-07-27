#include "stdio.h"
#include "stdlib.h"
#include "mat-operands_3.h"
#include "pt.h"
#include <architecture.h>
#include <mat-mulkernels.h>
#include "gpuCompute.h"
#include <pthread.h>  
#include "thpool.h"

#if(CLBLAS||FPGA)
int GEMMFPGA  (DEF(c), DEF(a), DEF(b));
int GEMM      (DEF(c), DEF(a), DEF(b));
#endif


//extern void mm_leaf_computation(DEF(C),DEF(A),DEF(B));


/*
product Gamma                        Alpha                        Beta
  1 ;   0  1  1  0  0  0  0 -1  0 ;  0  0 -1  0  0  0  0  0  0 ;  0  0  0  0  0  0  0 -1  0
  2 ;   0  0  0  0 -1  0  0  0  0 ;  0  1  0  0 -1  0  0  0  0 ;  0  1  0  0  1  0  0  0  0
  3 ;   0  0  0 -1  0 -1  0  0  0 ;  0 -1  0  0  1  0  0  0  0 ;  0  0 -1  0  0 -1  0  0  0
  4 ;   0  0 -1  0  0 -1  0  0  0 ;  0  0  0  1 -1  1  0  0  0 ;  0  0  0 -1  0  1  0  0  0
  5 ;  -1  0 -1 -1  0 -1  0  0  0 ;  0  1  0  0  0  0  0  0  0 ;  0  0  0 -1  0  0  0  0  0
  6 ;   0  0 -1  0  1  0  0  0  0 ; -1  1  0  1 -1  1  0  0  0 ;  0  0  1  0  0  0  0  1 -1
  7 ;   0  0 -1 -1  0 -1  0  0  0 ;  0 -1  0 -1  1 -1  0  0  0 ;  0  0  1 -1  0  1  0  0  0
  8 ;   0  0  0  0  1  1  0  0  1 ;  0  0  0  0  0 -1  0  0  0 ;  0  0  1  0  0  0  0  0 -1
  9 ;   0  0  0 -1  0  0  0  0  1 ;  0  0  0  0  0 -1 -1  0  0 ;  0  0 -1  1  0 -1  1  0  0
 10 ;   1  0  0  0  0  0 -1  0 -1 ;  0  0  0  0  0  0  1  0  1 ;  0  0  0  0  0  0 -1  0  0
 11 ;   0  0  0  0  1  0  0  0  0 ; -1  1  0  1 -1  0  0  0  0 ;  0  1 -1  0  0  0  0 -1  1
 12 ;   0  0  0  1  0  0  1 -1  0 ;  0  0  0  0  0  0 -1  0  0 ; -1  0  0  0  0  0  1  0  0
 13 ;   0  0 -1  0  0  0  0  0  0 ; -1  1 -1  1 -1  1  0  0  0 ;  0  0  0  0  0  0  0 -1  1
 14 ;   1  0  0  0  0  0  0 -1  0 ;  0  0 -1  0  0  0 -1  0 -1 ;  1  1  0  0  0  0 -1  0  0
 15 ;   0  0  0  0  0  0  0  0 -1 ;  0  0  0  0  0  1  0  0 -1 ;  0  0  0  0  0  0 -1  0  1
 16 ;   0  0  0  0  0  0  0 -1  0 ;  0  1  0  0  0  0  0  1  0 ;  0  0  0  0 -1  0  0  0  0
 17 ;   0  0  0 -1  0  0  0  0  0 ;  0  0  0 -1  0  0  1  0  0 ;  1  0 -1  1  0 -1  0  0  0
 18 ;  -1  0  0  0  0  0  0  0  0 ; -1  0 -1  0  0  0 -1  0 -1 ;  1  1  0  0  0  0  0  0  0
 19 ;   0  1  0  0  1  0  0 -1  0 ;  0  1  0  0  0  0  0  0  0 ;  0  0  0  0  1  0  0  0  0
 20 ;   1 -1  0  0 -1  0  0  0  0 ; -1  0  0  0  0  0  0  0  0 ;  0  1  0  0  0  0  0  0  0
 21 ;   0  0  0  0  0  0  0 -1  0 ;  0  0 -1  0  0  0  0  0 -1 ; -1 -1  0  0  0  0  1  1  0
 22 ;   0  0  0  0  0  0  0  0  1 ;  0  0  0  0  0 -1 -1  1  0 ;  0  0  0 -1  0  1  0  0  0
 23 ;   0  0  0  0  0  0  1  0  1 ;  0  0  0  0  0  0  0  1  0 ;  0  0  0  1  0  0  0  0  0

        c  c  c  c  c  c  c  c  c    a  a  a  a  a  a  a  a  a    b  b  b  b  b  b  b  b  b
	0  0  0  1  1  1  2  2  2    0  0  0  1  1  1  2  2  2	  0  0  0  1  1  1  2  2  2
	0  1  2  0  1  2  0  1  2    0  1  2  0  1  2  0  1  2	  0  1  2  0  1  2  0  1  2
*/


static int DEBUG= 0;
void single_accumulation(void *A);
void single_product(void *A);

#if CLBLAS
static const Matrix zero = { 0, 0,0,0,0,0,0};
#else
static const Matrix zero = { 0, 0,0,0,0,0};
#endif

static inline
int  dimension(Matrix *temp, Matrix r) {

  if (temp->m < r.m)
    temp->m = r.m;
  if (temp->n < r.n)
    temp->n =r.n;

  return 0;
}


extern int
addition_queue(
	       Matrix R,
	       Matrix A,
	       float  *rows, int len,
	       TAddOperands *adds, int ladds,
	       int base, Matrix *ref
	       );


extern  int _sizes[DEVICES];
extern  DeviceBookmark bookmarks[DEVICES];
		      




int
generate_queue_threads(
		      Matrix C, Matrix A, Matrix B,
		      int *gpus, int ngpus, int base,
		      float *ALPHA, float *BETA, float *GAMMA,
		      int P
		      ) {
  int Q = base *base; 
  Matrix *Cs = (Matrix*)calloc(base*base,sizeof(Matrix));
  Matrix *Ps = (Matrix*)calloc(ngpus,sizeof(Matrix));
  Matrix *As = (Matrix*)calloc(ngpus,sizeof(Matrix));
  Matrix *Bs = (Matrix*)calloc(ngpus,sizeof(Matrix)); 
  TComposedOperands *args = (TComposedOperands* )calloc(P,sizeof(TComposedOperands));
  threadpool thpool = thpool_init(ngpus);  
  int i=0;
  int step=0;

#if CLBLAS
  Matrix temp = { 'n', 0,0,0,0,0,0};
#else
  Matrix temp = { 'n', 0,0,0,0,0};
#endif

  for (i=0;i<Q;i++) {
    Cs[i] = PQQ(C,i,base);
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
    Cs[i].beta = 0;
#else
    Cs[i].beta = 0+0*I;
#endif
    if (DEBUG) 
      printf("i %d Cs %d x %d %d %d \n",i,Cs[i].m, Cs[i].n,Cs[i].M, Cs[i].N);
  }

  // allocate memory for the temporaries 
  for (i=0;i<ngpus;i++){
    
    Ps[i].data = (Mat*) calloc(HHH(C.m,base)*HHH(C.n,base),sizeof(Mat));
    {
      Ps[i].trans = C.trans;
      Ps[i].beta = _zero; // there is n real accumulation thus we save
			  // some communication
      Ps[i].m = Ps[i].M = HHH(C.m,base);
      Ps[i].n = Ps[i].N = HHH(C.n,base);
      if (DEBUG) printf("Ps[%d] %d x %d %d x %d HHH(%d,%d)=%d %d\n",
			i,Ps[i].m, Ps[i].n,Ps[i].M, Ps[i].N,
			C.m,base,HHH(C.m,base), LLL(C.m,base));
      
    }
    As[i].data = (Mat*) calloc(HHH(A.m,base)*HHH(A.n,base),sizeof(Mat));
    {
      As[i].trans = A.trans;
      As[i].beta = A.beta;
      As[i].m = As[i].M = HHH(A.m,base);
      As[i].n = As[i].N = HHH(A.n,base);
      if (DEBUG)  printf("As[%d] %d x %d %d x %d HHH(%d,%d) =%d %d \n",
			 i,As[i].m, As[i].n,As[i].M, As[i].N,
			 A.m,base,HHH(A.m,base), LLL(A.m,base));
    }
    Bs[i].data = (Mat*) calloc(HHH(B.m,base)*HHH(B.n,base),sizeof(Mat));
    {
      Bs[i].trans = B.trans; 
      Bs[i].beta = B.beta;
      Bs[i].m = Bs[i].M = HHH(B.m,base);
      Bs[i].n = Bs[i].N = HHH(B.n,base);
      if (DEBUG)  printf("Bs[%d] %d x %d %d x %d \n",i,Bs[i].m, Bs[i].n,Bs[i].M, Bs[i].N);
	    
    }
    args[i].P = P;
    args[i].Q = Q;
    args[i].base = base;
    args[i].C = C;
    args[i].A = A;
    args[i].B = B;
    args[i].Ps = Ps[i];
    args[i].As = As[i];
    args[i].Bs = Bs[i];
    args[i].Cs = Cs;
    args[i].GAMMA = GAMMA;
    args[i].BETA = BETA;
    args[i].ALPHA = ALPHA;
    args[i].sync = single_accumulation;
  }

	 
  for (step=0; step < P;step ++) {
    args[step] = args[step%ngpus];
    args[step].step = step;
  
    thpool_add_work(thpool, (void*)single_product, (void*) (args + step)); 

  }
  thpool_wait(thpool);
  thpool_destroy(thpool);
  
  if (DEBUG) {
    printf(" Freeing the temporaries\n");
  }
  // clean up temporaries
  for (i=0;i<ngpus;i++){
    FREE(Ps[i].data);
    FREE(As[i].data);
    FREE(Bs[i].data);
  }
  free(args);
  free(Bs);
  free(As);
  free(Ps);
  free(Cs);
  return 0;
}



void single_accumulation(void *A) {
  
  TComposedOperands T = *(TComposedOperands*)A;
  if (DEBUG) printf("ACCUMULATION Step %d is done on GPU %d Q %d\n",T.step,T.gpu,T.Q);
  
  for (int j=0;j<T.Q; j++) {
    if (DEBUG) printf("j = %d \n", j); 
    if (T.GAMMA[(T.step)*T.Q+j]!=0)
      if (T.Cs[j].beta ==0) {
	if (DEBUG) printf("Copy \n"); 
	copy(T.Cs[j],T.Ps);
	T.Cs[j].beta = 1.0;
      }
      else {
	if (DEBUG) printf("Add \n");
	if (DEBUG) {
	  printf("i %d Cs[%d] %d x %d %d %d \n",T.step,j,T.Cs[j].m, T.Cs[j].n,T.Cs[j].M, T.Cs[j].N);
	  printf("i %d Ps %d x %d %d %d \n",T.step,T.Ps.m, T.Ps.n,T.Ps.M, T.Ps.N);
	}
	
	T.Ps.beta = T.GAMMA[(T.step)*T.Q+j];
	ptadd_t(T.Cs[j],T.Cs[j],T.Ps);
	
      }
      
  }

  if (DEBUG) printf("Step %d is done on GPU %d\n",T.step,T.gpu);

}


 
void single_product(void *A) {
  
  TComposedOperands T = *(TComposedOperands*)A;
  TAddOperands products;
  int counta = 0;
  int countb = 0;
  int P = T.P;
  int Q = T.Q;
  int base = T.base;
  TAddOperands *Aadd = (TAddOperands*) calloc(T.Q,sizeof(TAddOperands));
  TAddOperands *Badd = (TAddOperands*) calloc(T.Q,sizeof(TAddOperands));;


  
#if CLBLAS
  Matrix temp = { 'n', 0,0,0,0,0,0};
#else
  Matrix temp = { 'n', 0,0,0,0,0};
#endif
  
#if CLBLAS
  T.Ps.gpu=T.gpu;
#endif
  
#if CLBLAS
  T.As.gpu=T.gpu;
#endif
  
#if CLBLAS
  T.Bs.gpu=T.gpu;
#endif
  products.pi= T.gpu;
#if CLBLAS
  if ( DEBUG)  printf("GPU %d %s Problem size %d and Memory size %d\n",
		     T.Ps.gpu,bookmarks[T.Ps.gpu].name,
		     sizeof(Mat)*3*T.Ps.M*T.Ps.N/(1024),
		     bookmarks[T.Ps.gpu].size);
  if (T.Ps.gpu>=0 && T.Ps.gpu<=DEVICES && sizeof(Mat)*3*T.Ps.M*T.Ps.N/(1024) > bookmarks[T.Ps.gpu].size) { 
    if (DEBUG)  printf("%d too big we use wm \n",T.gpu);
    products.m  = wm ;
  }
#if FPGA
  else { 
    if (DEBUG)  printf("%s \n",bookmarks[T.Ps.gpu].name);
    if (strstr(bookmarks[T.Ps.gpu].name, "xilinx")  ) {
      if (DEBUG)  printf("%s \n",bookmarks[T.Ps.gpu].name);
      products.m  = mm_leaf_computation  ;
    }
    else
      products.m  = mm_leaf_computation_gpu  ;
  }
#else
  else
    products.m  = mm_leaf_computation  ;
  
#endif
#else
  products.m  = wm;
#endif
  temp.m = temp.n = 0;
  if (DEBUG) printf("Step %d  P %d Q %d base %d\n", T.step, T.P,T.Q,T.base );
  // prep computation
  
      
  counta = addition_queue(T.As,T.A,T.ALPHA+(T.step)*Q,Q,Aadd,Q,base,&temp);
  if (DEBUG) printf("length of As  %d\n", counta);
  MatrixComputationsSequential(Aadd,counta);
  T.As.m = temp.m; 
  T.As.n = temp.n;
  temp.m = temp.n = 0;
      
  countb = addition_queue(T.Bs,T.B,T.BETA+(T.step)*Q,Q,Badd,Q,base,&temp);
  if (DEBUG) printf("length of Bs  %d\n", countb);
  MatrixComputationsSequential(Badd,countb);
  T.Bs.m = temp.m;
  T.Bs.n = temp.n;

  if (DEBUG) {
    printf("i %d A %d x %d %d %d \n",T.step,T.As.m, T.As.n,T.As.M, T.As.N);
    printf("i %d B %d x %d %d %d \n",T.step,T.Bs.m, T.Bs.n,T.Bs.M, T.Bs.N);
    printf("i %d R %d x %d %d %d \n",T.step,T.Ps.m, T.Ps.n,T.Ps.M, T.Ps.N);
  }

  if (T.As.n > T.Bs.m)
    T.As.n = T.Bs.m;
  else if (T.As.n < T.Bs.m) 
    T.Bs.m =T.As.n;

  T.Ps.m = T.As.m;
  T.Ps.n = T.Bs.n;

  if (DEBUG) {
    printf("adding to products\n");
    printf("## gpu %d\n", T.gpu);
    printf("i %d A %d x %d %d %d \n",T.step,T.As.m, T.As.n,T.As.M, T.As.N);
    printf("i %d B %d x %d %d %d \n",T.step,T.Bs.m, T.Bs.n,T.Bs.M, T.Bs.N);
    printf("i %d R %d x %d %d %d \n",T.step,T.Ps.m, T.Ps.n,T.Ps.M, T.Ps.N);
  }
      
  products.c  = T.Ps; 
  products.a  = T.As;
  products.b  = T.Bs;


  // MM Computation
  products.m(products.c,products.a,products.b);
  if (DEBUG) printf("done product GPU %d step %d \n",T.gpu, T.step);
  
  
  free(Aadd);
  free(Badd);

}
