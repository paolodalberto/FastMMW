#include "stdio.h"
#include "stdlib.h"
#include "mat-operands_3.h"
#include "pt.h"
#include <architecture.h>
#include <mat-mulkernels.h>
#include "gpuCompute.h"

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



int addition_queue(Matrix R,
		   Matrix A,
		   float  *rows, int len,
		   TAddOperands *adds, int ladds,
		   int base, Matrix *ref,
		   MatrixComputation Add) {
  int j;
  int count=0;
  int Q = base*base;
  int l=0;
  int mr, mc;
  
  if (DEBUG) printf("addition_queue Q %d\n", Q); 
  for (j=0;j<Q;j++) {
    count += (rows[j]!=0)?1:0;
    if (DEBUG) printf("%d ", (int)rows[j]);
  }
  if (DEBUG) printf("\n count %d\n", count);

  if (count==1) {
    Matrix temp;
    for (j=0;j<Q;j++) 
      if (rows[j] !=0)
	break;
    if (DEBUG) printf("j=%d base=%d  A %d x %d %d %d \n",j,base,A.m, A.n,A.M, A.N);
    temp = PQQ(A,j,base);

    // This is actual size of the result matrix
    dimension(ref,temp);
      
    adds[l].pi = -1;
    adds[l].m = copy_matrix;
    adds[l].c = R;
    adds[l].a = temp;
    adds[l].b = zero;
    if (DEBUG) {
      printf("Queu 1 l=%d\n",l);
      printf("A %d x %d %d %d \n",adds[l].a.m, adds[l].a.n,adds[l].a.M, adds[l].a.N);
      printf("\t A %d x %d %d %d \n",A.m, A.n,A.M, A.N);
      printf("C %d x %d %d %d \n",adds[l].c.m, adds[l].c.n,adds[l].c.M, adds[l].c.N);
      printf("\t R %d x %d %d %d \n",R.m, R.n,R.M, R.N);
      printf("B %d x %d %d %d \n",adds[l].b.m, adds[l].b.n,adds[l].b.M, adds[l].b.N);
    }
    return 1;
  } else
    if (count>=2) {
      int c=0;
      int i[Q];
      int k;
      for (k=0;k<Q && c<2;k++) 
	if (rows[k] !=0)
	  i[c++] = k;
      
      adds[l].pi = -11;
      adds[l].m = Add; //_amd; //ptadd_t;
      adds[l].c = R;
      adds[l].a = PQQ(A,i[0],base); 
      adds[l].b = PQQ(A,i[1],base); 

      dimension(ref,adds[l].a);
      dimension(ref,adds[l].b);

#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      adds[l].a.beta = rows[i[0]];
      adds[l].b.beta = rows[i[1]];
#else
      adds[l].a.beta = rows[i[0]] +I*0;
      adds[l].b.beta = rows[i[1]] +I*0;
#endif      
      l ++;
      for (k=0;k<Q && c<count;k++) 
	if (rows[k] !=0) {
	  i[c] = k;
	  adds[l].pi = -1;
	  adds[l].m = Add; // add_amd; //ptadd_t;
	  adds[l].c = R;
	  adds[l].a = R;
	  adds[l].b = PQQ(A,i[c],base);
	  dimension(ref,adds[l].b);

#if(SINGLE_PRECISION || DOUBLE_PRECISION)
	  adds[l].b.beta = rows[i[c]];
#else
	  adds[l].b.beta = rows[i[c]]+I*0;
#endif
		  
	  c++;
	  l++;
	}
      
      return  l;
    }
  return 0;
}



extern  int _sizes[DEVICES];
extern  DeviceBookmark bookmarks[DEVICES];
		      




int generate_queue(Matrix C, Matrix A, Matrix B,
		   int *gpus, int ngpus, int base,
		   float *ALPHA, float *BETA, float *GAMMA,
		   int P
		   ) {
  int Q = base *base; 
  Matrix *Ps = (Matrix*)calloc(P,sizeof(Matrix));
  Matrix *Cs = (Matrix*)calloc(base*base,sizeof(Matrix));
  Matrix *As = (Matrix*)calloc(ngpus,sizeof(Matrix));
  Matrix *Bs = (Matrix*)calloc(ngpus,sizeof(Matrix)); 
  TAddOperands *Aadd = (TAddOperands*) calloc(base*base,sizeof(TAddOperands));
  TAddOperands *Badd = (TAddOperands*) calloc(base*base,sizeof(TAddOperands));;
  TAddOperands *products = (TAddOperands*) calloc(ngpus,sizeof(TAddOperands));
  int i=0;
  int step=0;

#if CLBLAS
  Matrix temp = { 'n', 0,0,0,0,0,0};
#else
  Matrix temp = { 'n', 0,0,0,0,0};
#endif


  if (DEBUG) {
    int i,j;
#if CLBLAS
    printf("M%d   C %d x %d %d x %d gpu %d\n",P,C.m, C.n,C.M, C.N, C.gpu);
    printf("      A %d x %d %d x %d gpu %d\n",A.m, A.n,A.M, A.N, A.gpu);
    printf("      B %d x %d %d x %d gpu %d\n",B.m, B.n,B.M, B.N, B.gpu);
    printf(" ngpus %d , base %d P %d\n", ngpus, base,P);
#else
    printf("M%d   C %d x %d %d x %d \n",P,C.m, C.n,C.n,C.M, C.N);
    printf("      A %d x %d %d x %d \n",A.m, A.n,A.n,A.M, A.N);
    printf("      B %d x %d %d x %d \n",B.m, B.n,B.n,B.M, B.N);
    printf(" ngpus %d , base %d P %d\n", ngpus, base,P);
#endif
    printf("GAMMA\n");
    for (i=0;i<P;i++) {
      printf("%d ",  i);
      for (j=0;j<Q;j++)
	printf("%d ",  (int)GAMMA[i*Q+j]);
      printf("\n");
    }
    printf("ALPHA\n");
    for (i=0;i<P;i++) {
      printf("%d ",  i);
      for (j=0;j<Q;j++)
	printf("%d ",  (int)ALPHA[i*Q+j]);
      printf("\n");
    }
    printf("BETA\n");
    for (i=0;i<P;i++) {
      printf("%d ",  i);
      for (j=0;j<Q;j++)
	printf("%d ",  (int)BETA[i*Q+j]);
      printf("\n");
    }

  }
  // allocate memory for the temporaries 
  for (i=0;i<ngpus;i++){
    
    Ps[i].data = (Mat*) calloc(HHH(C.m,base)*HHH(C.n,base),sizeof(Mat));
    {
#if CLBLAS
      Ps[i].gpu=gpus[i];
#endif
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
#if CLBLAS
      As[i].gpu=i;
#endif
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
#if CLBLAS
      Bs[i].gpu=i;
#endif
      Bs[i].trans = B.trans; 
      Bs[i].beta = B.beta;
      Bs[i].m = Bs[i].M = HHH(B.m,base);
      Bs[i].n = Bs[i].N = HHH(B.n,base);
      if (DEBUG)  printf("Bs[%d] %d x %d %d x %d \n",i,Bs[i].m, Bs[i].n,Bs[i].M, Bs[i].N);
	    
    }
    products[i].pi= 1;
#if CLBLAS
    if (DEBUG)  printf("GPU %d %c Problem size %d and Memory size %d\n",
		       Ps[i].gpu,bookmarks[Ps[i].gpu].name,
		       sizeof(Mat)*3*Ps[i].M*Ps[i].N/(1024),
		       bookmarks[Ps[i].gpu].size);
    if (Ps[i].gpu>=0 && Ps[i].gpu<=DEVICES && sizeof(Mat)*3*Ps[i].M*Ps[i].N/(1024) > bookmarks[Ps[i].gpu].size) { 
      if (DEBUG)  printf("%d too big we use wm \n",i);
      products[i].m  = wm ;
    }
#if FPGA
    else { 
      if (DEBUG)  printf("%s \n",bookmarks[Ps[i].gpu].name);
      if (strstr(bookmarks[Ps[i].gpu].name, "xilinx")  ) {
	if (DEBUG)  printf("%s \n",bookmarks[Ps[i].gpu].name);
	products[i].m  = mm_leaf_computation  ;
      }
      else
	products[i].m  = mm_leaf_computation_gpu  ;
    }
#else
    else
      products[i].m  = mm_leaf_computation  ;

#endif
#else
    products[i].m  = wm;
#endif
  }

  for (i=0;i<Q;i++) {
    Cs[i] = PQQ(C,i,base);
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
    Cs[i].beta = 0;
#else
    Cs[i].beta = 0+0*I;
#endif
  }
	 
  for (step=0; step < P;step += ngpus) {
    int a=0;
    int b=0;
    temp.m = temp.n = 0;
    if (DEBUG) printf("Step %d gpus %d P %d Q %d\n", step/ngpus, ngpus,P,Q );
    // prep computation
    for (i=0; i<ngpus && step+i<P; i++) {
      int counta = 0;
      int countb = 0;
      
      counta = addition_queue(As[i],A,ALPHA+(step+i)*Q,Q,Aadd,Q,base,&temp, ptadd_t);
      if (DEBUG) printf("length of As  %d\n", counta);
      MatrixComputationsSequential(Aadd,counta);
      As[i].m = temp.m; 
      As[i].n = temp.n;
      temp.m = temp.n = 0;
      
      countb = addition_queue(Bs[i],B,BETA+(step+i)*Q,Q,Badd,Q,base,&temp, ptadd_t);
      if (DEBUG) printf("length of Bs  %d\n", countb);
      MatrixComputationsSequential(Badd,countb);
      Bs[i].m = temp.m;
      Bs[i].n = temp.n;

      if (DEBUG) {
	printf("i %d A %d x %d %d %d \n",i,As[i].m, As[i].n,As[i].M, As[i].N);
	printf("i %d B %d x %d %d %d \n",i,Bs[i].m, Bs[i].n,Bs[i].M, Bs[i].N);
	printf("i %d R %d x %d %d %d \n",i,Ps[i].m, Ps[i].n,Ps[i].M, Ps[i].N);
      }

      if (As[i].n > Bs[i].m)
	As[i].n = Bs[i].m;
      else if (As[i].n < Bs[i].m) 
	Bs[i].m =As[i].n;

      Ps[i].m = As[i].m;
      Ps[i].n = Bs[i].n;

      if (DEBUG) {
	printf("adding to products\n");
	printf("## gpu %d\n", i);
	printf("i %d A %d x %d %d %d \n",i,As[i].m, As[i].n,As[i].M, As[i].N);
	printf("i %d B %d x %d %d %d \n",i,Bs[i].m, Bs[i].n,Bs[i].M, Bs[i].N);
	printf("i %d R %d x %d %d %d \n",i,Ps[i].m, Ps[i].n,Ps[i].M, Ps[i].N);
      }
      
      products[i].c  = Ps[i]; 
      products[i].a  = As[i];
      products[i].b  = Bs[i];
    }

    // Parallel computation
    MatrixComputations(products,i);

    for (i=0; i<ngpus && step+i<P; i++) {
      for (int j=0;j<Q; j++) {
	if (GAMMA[(step+i)*Q+j]!=0)
	  if (Cs[i].beta ==0) {
	    copy(Cs[i],Ps[i]);
	    Cs[i].beta = 1.0;
	  }
	  else {
	    Ps[i].beta = GAMMA[(step+i)*Q+j];
	    ptadd_t(Cs[i],Cs[i],Ps[i]);
	    
	  }
	
      }
    }

  } 
  if (DEBUG) {
    printf(" Freeing the temporaries\n");
  }
  // clean up temporaries
  for (i=0;i<ngpus;i++){
    FREE(Ps[i].data);
    FREE(As[i].data);
    FREE(Bs[i].data);
  }
  free(products);
  free(Badd);
  free(Aadd);
  free(Bs);
  free(As);
  free(Cs);
  free(Ps);
  return 0;
}






 
