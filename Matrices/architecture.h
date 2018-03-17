/* 
   Copyright 2011 Paolo D'Alberto, Marco Bodrato, and Alexandru
   Nicolau

   This file is part of the Fast Matrix Multiply library (FMM).
      
   FMM is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   FMM is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General
   Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with FMM.  If not, see
   <http://www.gnu.org/licenses/>.

*/
#ifndef ARCHITECTURE_SPECIFIC
#define ARCHITECTURE_SPECIFIC 1
#include <mat-operands.h>
//#define XSCALE 1
#define ATHLON 1
//#define ATLAS  1

//#define GOTO_BLAS 1

#ifdef ATLAS
#include <cblas.h>

// TYPE of the matrix and the MM

#ifdef SINGLE_PRECISION
#define GEMM cblas_sgemm
#define GEMA cblas_sgema
#endif

#ifdef DOUBLE_PRECISION
#define GEMM cblas_dgemm
#define GEMA cblas_dgema
#endif

#ifdef SINGLE_COMPLEX
#define GEMM cblas_cgemm
#define GEMA cblas_cgema
#endif

#ifdef DOUBLE_COMPLEX
#define GEMM cblas_zgemm
#define GEMA cblas_zgema
#endif
#endif // def ATLAS

#ifdef GOTO_BLAS
#ifdef SINGLE_PRECISION
#define GEMM sgemm_
#define GEMA sgema_
#endif

#ifdef DOUBLE_PRECISION
#define GEMM dgemm_
#define GEMA dgema_
#endif

#ifdef SINGLE_COMPLEX
#define GEMM cgemm_
#define GEMA cgema_
#define GEMM3M cgemm3m_
#endif

#ifdef DOUBLE_COMPLEX
#define GEMM zgemm_
#define GEMA zgema_
#define GEMM3M zgemm3m_
#endif
#endif // def GOTOS


#ifdef CLBLAS
// GPU interface

#include <clblast_c.h>
//#include <clAmdBlas.h>

// TYPE of the matrix and the MM



#ifdef SINGLE_PRECISION
#define GEMMCL                   CLBlastSgemm  //clblasSgemm
#define GEMM                     s_gpuGEMM
#define GEMMA                    s_gpuGEMMA

#define mm_leaf_computation      s_gpuGEMM
#define mm_leaf_computation_madd s_gpuGEMMA

#endif

#ifdef DOUBLE_PRECISION
#define GEMMCL                   CLBlastDgemm //clblasDgemm
#define GEMM                     d_gpuGEMM
#define GEMMA                    d_gpuGEMMA
#define mm_leaf_computation      d_gpuGEMM
#define mm_leaf_computation_madd d_gpuGEMMA
#endif

#ifdef SINGLE_COMPLEX
#define GEMMCL                   CLBlastCgemm //clblasCgemm
#define GEMM                     c_gpuGEMM
#define GEMMA                    c_gpuGEMMA
#define mm_leaf_computation      c_gpuGEMM
#define mm_leaf_computation_madd c_gpuGEMMA

#endif

#ifdef DOUBLE_COMPLEX
#define GEMMCL                   CLBlastZgemm //clblasZgemm
#define GEMM                     z_gpuGEMM
#define GEMMA                    z_gpuGEMMA
#define mm_leaf_computation      z_gpuGEMM
#define mm_leaf_computation_madd z_gpuGEMMA
#endif
#endif // def CLBLAS





#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
static char _n = 'N';
static Mat _one = 1+0*I;
static Mat _zero =0+0*I;
#else
static char _n = 'N';
static Mat _one = 1;
static Mat _zero =0;
#endif


#ifdef APPLICATION
// These are constants, safe to use in parallel
static float _zero_f=0;
static double _zero_d=0;
static float complex _zero_c=0+0*I;
static double complex _zero_z=0+0*I;
static float _one_f=1;
static double _one_d=1;
static float complex _one_c=1+0*I;
static double complex _one_z=1+0*I;
#endif


/****************************************************************
 * ATLAS
 */

#ifdef ATLAS
#define GTOA(x) (((x.trans=='n' )?CblasNoTrans:((x.trans=='t' )?CblasTrans:CblasConjTrans)))

#ifdef ROW_MAJOR
#define LAYOUT CblasRowMajor
#define LDA(a) a.N
#define LDB(b) b.N
#define LDC(c) c.N
#endif
#ifdef COLUMN_MAJOR
#define LAYOUT CblasColMajor
#define LDA(a) a.M
#define LDB(b) b.M
#define LDC(c) c.M
#endif

#ifndef APPLICATION

#if(SINGLE_PRECISION || DOUBLE_PRECISION) 
#define atlas_gemm(c,a,b)      GEMM(LAYOUT,GTOA(a),GTOA(b), \
				    ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
				    a.beta*b.beta, a.data, LDA(a), b.data, LDB(b), _zero, c.data, LDC(c))

#define atlas_addgemm(c,a,b)   GEMM(LAYOUT,GTOA(a),GTOA(b), \
				    ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
				    a.beta*b.beta, a.data, LDA(a), b.data, LDB(b), c.beta, c.data, LDC(c))
/*
#define atlas_gema(c,a,b)      GEMA(LAYOUT,GTOA(a.trans),GTOA(b.trans), ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m),  a.beta, a.data, a.N, b.beta, b.data, b.N, c.data, c.N)
*/
#endif

#if(SINGLE_COMPLEX || DOUBLE_COMPLEX) 
#define atlas_gemm(c,a,b)      {					\
    Mat _one = a.beta*b.beta;						\
    GEMM(LAYOUT,GTOA(a),GTOA(b),				\
	 ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
	 (void *)&_one, a.data, LDA(a), b.data, LDB(b), (void *) &_zero, c.data,LDC(c)); \
  }
#define atlas_addgemm(c,a,b) {						\
    Mat _one = a.beta*b.beta;						\
    GEMM(LAYOUT,GTOA(a),GTOA(b),				\
	 ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
	 (void *)&_one, a.data, LDA(a), b.data, LDB(b), (void *)&c.beta, c.data, LDC(c));	\
  }
/*
#define atlas_gema(c,a,b)      GEMA(LAYOUT,GTOA(a.trans),GTOA(b.trans), \
				    ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
				    a.beta, a.data, a.N, b.beta, b.data, b.N, c.data, c.N)
#define atlas_gems(c,a,b)      GEMA(LAYOUT,GTOA(a.trans),GTOA(b.trans), \
				    ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
				    a.beta, a.data, a.N, -b.beta, b.data, b.N, c.data, c.N)
*/
#endif
#endif // ndef APPLICATION

#ifdef APPLICATION
// all routines 
#define mm_leaf_computation_s(c,a,b)  cblas_sgemm(LAYOUT,GTOA(a),GTOA(b), \
						  ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
						  a.beta*b.beta, a.data, LDA(a), b.data, LDB(b), 0, c.data, LDC(c));
#define mm_leaf_computation_d(c,a,b) cblas_dgemm(LAYOUT,GTOA(a),GTOA(b), \
						 ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
						 a.beta*b.beta, a.data, LDA(a), b.data, LDB(b), 0, c.data, LDC(c));
#define mm_leaf_computation_c(c,a,b) {					\
    float complex temp = a.beta*b.beta;					\
    cblas_cgemm(LAYOUT,GTOA(a),GTOA(b),			\
		((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
		(void *)&temp, a.data, LDA(a), b.data, LDB(b), (void *)&_zero_c, c.data, LDC(c));	\
  }
#define mm_leaf_computation_z(c,a,b) {					\
    double complex temp = a.beta*b.beta;				\
    cblas_zgemm(LAYOUT,GTOA(a),GTOA(b),					\
		((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
		(void *)&temp, a.data, LDA(a), b.data, LDB(b), (void *)&_zero_z, c.data, LDC(c)); \
  }


#define mm_leaf_computation_madd_s(c,a,b)   cblas_sgemm(LAYOUT,GTOA(a),GTOA(b), \
							((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
							a.beta*b.beta, a.data, LDA(a), b.data, LDB(b), c.beta, c.data, LDC(c));
#define mm_leaf_computation_madd_d(c,a,b)   cblas_dgemm(LAYOUT,GTOA(a),GTOA(b), \
							((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
							a.beta*b.beta, a.data, LDA(a), b.data, LDB(b), c.beta, c.data, LDC(c));
#define mm_leaf_computation_madd_c(c,a,b)   {				\
    float complex temp = a.beta*b.beta;					\
    cblas_cgemm(LAYOUT,GTOA(a),GTOA(b),			\
		((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
		(void *)&temp, a.data, LDA(a), b.data, LDB(b), (void *)&c.beta, c.data, LDC(c)); \
  }
#define mm_leaf_computation_madd_z(c,a,b)   {				\
    double complex temp = a.beta*b.beta;				\
    cblas_zgemm(LAYOUT,GTOA(a),GTOA(b),					\
		((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
		(void *)&temp, a.data, LDA(a), b.data, LDB(b), &c.beta, (void *)c.data, LDC(c)); \
  }
#endif // def APPLICATION

#endif // def ATLAS


/****************************************************************
 * GOTO BLAS
 */


#ifdef GOTO_BLAS


#ifndef APPLICATION
#define goto_gemm(c,a,b)     {Mat _one=a.beta*b.beta;			\
    GEMM(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one, a.data, &a.M, b.data, &b.M, &_zero , c.data, &c.M); \
  }
#define goto_addgemm(c,a,b)  {Mat _one=a.beta*b.beta; \
    GEMM(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one, a.data, &a.M, b.data, &b.M, &c.beta, c.data, &c.M); \
  }

#if(SINGLE_COMPLEX || DOUBLE_COMPLEX) 
#define goto_gemm3m(c,a,b)     {Mat _one=a.beta*b.beta; \
    GEMM3M(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one, a.data, &a.M, b.data, &b.M, &_zero , c.data, &c.M); \
  }
#define goto_addgemm3m(c,a,b)  {Mat _one=a.beta*b.beta; \
    GEMM3M(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one, a.data, &a.M, b.data, &b.M, &c.beta, c.data, &c.M); \
  }
#endif // 3M
#endif // ndef APPLICATION
#ifdef APPLICATION
#define mm_leaf_computation_s(c,a,b) {float _one_f=a.beta*b.beta;		\
    sgemm_(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one_f, a.data, &a.M, b.data, &b.M, &_zero_f , c.data, &c.M);	\
  }
#define mm_leaf_computation_d(c,a,b) {double _one_d=a.beta*b.beta;		\
    dgemm_(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one_d, a.data, &a.M, b.data, &b.M, &_zero_d , c.data, &c.M);	\
  }
#define mm_leaf_computation_c(c,a,b) {float complex _one_c=a.beta*b.beta;		\
    cgemm_(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one_c, a.data, &a.M, b.data, &b.M, &_zero , c.data, &c.M);	\
  }
#define mm_leaf_computation_z(c,a,b) {double complex _one=a.beta*b.beta;		\
    zgemm_(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one, a.data, &a.M, b.data, &b.M, &c.beta , c.data, &c.M);	\
  }
#define mm_leaf_computation_madd_s(c,a,b) {float _one_f=a.beta*b.beta;		\
    sgemm_(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one_f, a.data, &a.M, b.data, &b.M, &c.beta , c.data, &c.M);	\
  }
#define mm_leaf_computation_madd_d(c,a,b) {double _one_d=a.beta*b.beta;		\
    dgemm_(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one_d, a.data, &a.M, b.data, &b.M, &c.beta , c.data, &c.M);	\
  }
#define mm_leaf_computation_madd_c(c,a,b) {float complex _one_c=a.beta*b.beta;		\
    cgemm_(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one_c, a.data, &a.M, b.data, &b.M, &c.beta , c.data, &c.M);	\
  }
#define mm_leaf_computation_madd_z(c,a,b) {double complex _one=a.beta*b.beta;		\
    zgemm_(&a.trans,&b.trans,((a.trans=='n')?&a.m:&a.n), ((b.trans=='n')?&b.n:&b.m), ((a.trans=='n')?&a.n:&a.m), \
	   &_one, a.data, &a.M, b.data, &b.M, &c.beta , c.data, &c.M);	\
  }

#endif // def APPLICATION
#endif // def GOTOBLAS

/*
#define goto_gema(c,a,b)  GEMA(GTOA(a.trans),GTOA(b.trans),	\
			       ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
			       a.beta, a.data, a.N, b.beta, b.data, b.N, c.data, c.N)
#define goto_gems(c,a,b)  GEMA(GTOA(a.trans),GTOA(b.trans),	\
			       ((a.trans=='n')?a.m:a.n), ((b.trans=='n')?b.n:b.m), ((a.trans=='n')?a.n:a.m), \
			       a.beta, a.data, a.N, -b.beta, b.data, b.N, c.data, c.N)
*/




// Introduce here the MM and ADD and SUB that suites you !

#ifdef XSCALE

/* atlas_gemm */
#define mm_leaf_computation gemm_xscale//_long 

/* atlas_addgemm */
#define mm_leaf_computation_madd gemm_xscale 

/* add */
#define s_add add_xscale
/* sub */
#define s_sub sub_xscale
#endif //XSCALE


#ifdef ATHLON 

/* atlas_gemm */

#ifdef ATLAS
#define mm_leaf_computation      atlas_gemm 
#define mm_leaf_computation_madd atlas_addgemm
//#define mm_add                   atlas_gema
//#define mm_sub                   atlas_gems
#endif // ATLAS

#ifdef GOTO_BLAS
#define mm_leaf_computation      goto_gemm 
#define mm_leaf_computation_madd goto_addgemm
#define mm_leaf_computation_3m      goto_gemm3m 
#define mm_leaf_computation_madd_3m goto_addgemm3m

//#define mm_add                   goto_gema
//#define mm_sub                   goto_gems
#endif // GOTO



/* add */

#define s_add_t ptadd_t
#define s_add   ptadd

//#define s_add_t add_amd_t
//#define s_add   add_amd
//#define s_add add
//#define s_add_t add_t
/* sub */
#define s_sub_t ptsub_t
#define s_sub   ptsub
//#define s_sub_t sub_amd_t
//#define s_sub   sub_amd
//#define s_sub sub
//#define s_sub_t sub_t


#endif // ATHLON
#include <stdlib.h>


static void* PALLOC(DEF(x)) {
  void *pointer;

  if (posix_memalign(&pointer, 64, (x).M*(x).N*sizeof(Mat)) != 0) {	
    printf(" MALLOC ERROR\n");					
    return 0;							
  } else {
    printf("Allocated at %lu matrix of size %d by  %d for total %d\n", pointer,(x).M,(x).N,(x).M*(x).N*sizeof(Mat));  
    return pointer;
  }
}

    
#define ALLOC(x)  malloc((x).M*(x).N*sizeof(Mat))
#define CALLOC(x) calloc((x).M*(x).N,sizeof(Mat))
#define FREE(x) {if (x) {free(x);} x=(Mat*)0; }




#endif // ARCHITECTURE_SPECIFIC
