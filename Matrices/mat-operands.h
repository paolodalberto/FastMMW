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
#ifndef MAT_OPERANDS
#define MAT_OPERANDS
#include <complex.h> 


/*************************************************
 * 
 * Select the type of the matrix
 * 
 */

//#define SINGLE_PRECISION 1
//#define DOUBLE_PRECISION 1
//#define SINGLE_COMPLEX 1
//#define DOUBLE_COMPLEX 1

/*************************************************
 * 
 * Define the type of the matrix
 * 
 */


/*************************************************
 *
 * An Application may need different precision functions calls
 * thus we may have different declaration of matrices.
 */




#ifdef APPLICATION

struct matrix_h {
  short       *data; // pointer to the location in the matrix
  int m,  n, M, N;   // logical size mxn inside a real matrix size MxN
  char trans;        // either 'n' no, 't' transpose or 'c' conjugate for complex matrices 
  float beta;        // multiplicative coefficients
#if(CLBLAS||ROCMBLAS)
  int gpu;          // destination computation
#endif
};
typedef struct matrix_h H_Matrix;

struct matrix_f {
  float       *data; // pointer to the location in the matrix
  int m,  n, M, N;   // logical size mxn inside a real matrix size MxN
  char trans;        // either 'n' no, 't' transpose or 'c' conjugate for complex matrices 
  float beta;        // multiplicative coefficients
#if(CLBLAS||ROCMBLAS)
  int gpu;          // destination computation
#endif
};
typedef struct matrix_f S_Matrix;



struct matrix_d {
  double       *data; // pointer to the location in the matrix
  int m,  n, M, N; // logical size mxn inside a real matrix size MxN
  char trans;      // either 'n' no, 't' transpose or 'c' conjugate for complex matrices 
  double beta;        // multiplicative coefficients
#if(CLBLAS||ROCMBLAS)
  int gpu;          // destination computation
#endif
          // destination computation
};

typedef struct matrix_d D_Matrix;


struct matrix_sc {
  float complex       *data; // pointer to the location in the matrix
  int m,  n, M, N; // logical size mxn inside a real matrix size MxN
  char trans;      // either 'n' no, 't' transpose or 'c' conjugate for complex matrices 
  float complex beta;        // multiplicative coefficients
#if(CLBLAS||ROCMBLAS)
  int gpu;          // destination computation
#endif
          // destination computation
};

typedef struct matrix_sc C_Matrix;


struct matrix_dc {
  double complex   *data; // pointer to the location in the matrix
  int m,  n, M, N; // logical size mxn inside a real matrix size MxN
  char trans;      // either 'n' no, 't' transpose or 'c' conjugate for complex matrices 
  double complex  beta;        // multiplicative coefficients
#if(CLBLAS||ROCMBLAS)
  int gpu;          // destination computation
#endif
          // destination computation
};

typedef struct matrix_dc Z_Matrix;


#define DEF_H(x) H_Matrix x
#define DEF_S(x) S_Matrix x
#define DEF_D(x) D_Matrix x
#define DEF_C(x) C_Matrix x
#define DEF_Z(x) Z_Matrix x
#endif




#if(HALF_PRECISION &&  LIBRARY_PACKAGE)
#define Matrix H_Matrix
#elif(SINGLE_PRECISION &&  LIBRARY_PACKAGE)
#define Matrix S_Matrix
#elif(DOUBLE_PRECISION &&  LIBRARY_PACKAGE)
#define Matrix D_Matrix
#elif(SINGLE_COMPLEX &&  LIBRARY_PACKAGE)
#define Matrix C_Matrix
#elif (DOUBLE_COMPLEX &&  LIBRARY_PACKAGE)
#define Matrix Z_Matrix
#endif


#ifdef CLBLAS
#include <clblast_c.h>

#if(HALF_PRECISION && LIBRARY_PACKAGE)
typedef cl_half Mat;
#elif(SINGLE_PRECISION && LIBRARY_PACKAGE)
typedef cl_float Mat;
#elif(DOUBLE_PRECISION && LIBRARY_PACKAGE)
typedef cl_double Mat;
#elif(SINGLE_COMPLEX && LIBRARY_PACKAGE)
typedef float complex  Mat;
typedef cl_float Mat_element;
#elif(DOUBLE_COMPLEX && LIBRARY_PACKAGE)
typedef double complex  Mat;
typedef cl_double Mat_element;
#else
typedef cl_float Mat;
#endif
#endif

#ifndef CLBLAS
#if(HALF_PRECISION && LIBRARY_PACKAGE)
typedef short Mat;
#elif(SINGLE_PRECISION && LIBRARY_PACKAGE)
typedef float Mat;
#elif(DOUBLE_PRECISION && LIBRARY_PACKAGE)
typedef double Mat;
#elif(SINGLE_COMPLEX && LIBRARY_PACKAGE)
typedef float complex Mat;
typedef float Mat_element;
#elif(DOUBLE_COMPLEX && LIBRARY_PACKAGE)
typedef double complex  Mat;
typedef double Mat_element;
#else
typedef float Mat;
#endif
#endif

#ifndef APPLICATION

struct matrix {
  Mat       *data; // pointer to the location in the matrix
  int m,  n, M, N; // logical size mxn inside a real matrix size MxN
  char trans;      // either 'n' no, 't' transpose or 'c' conjugate for complex matrices 
  Mat beta;        // multiplicative coefficients
  #if(CLBLAS||ROCMBLAS)
  int gpu;          // destination computation
#endif
          // destination computation
};

typedef struct matrix Matrix;

#define DEF(a) Matrix a

#endif





#define PRINTMATRIX(x,a) {						\
    /* printf("a start %x end %x\n",(unsigned int)a.data,(unsigned int)(a.data + Size(a.M,a.N)));*/ \
  printf("%s mxn (%dx%d) and MxN (%dx%d)and trans=%c and beta=%f \n",x, a.m, a.n,a.M,a.N,a.trans,a.beta); \
}


/*************************************************
 * 
 * Select the layout of the matrix
 * 
 */

//#define COLUMN_MAJOR 1
#define ROW_MAJOR 1



/*************************************************
 * 
 * MACRO for the division process 
 * 
 */




#define USE(a) a


#define min(x,y) (((x)<=(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))

#define HL(n)   ((n)>>1)
#define HH(n)   ((HL(n))+((n)&1))

#define Size(x,y) ((x)*(y))

// A_0 domininant
#define S0(m,n)  (HH(m)),(HH(n))
#define S1(m,n)  (HH(m)),(HL(n))  
#define S2(m,n)  (HL(m)),(HH(n))  
#define S3(m,n)  (HL(m)),(HL(n))  

// A_1 domininant
#define SR0(m,n)  (HH(m)),(HL(n))
#define SR1(m,n)  (HH(m)),(HH(n))  
#define SR2(m,n)  (HL(m)),(HL(n))  
#define SR3(m,n)  (HL(m)),(HH(n))  

// A_2 domininant
#define ST0(m,n)  (HL(m)),(HH(n))
#define ST1(m,n)  (HL(m)),(HL(n))  
#define ST2(m,n)  (HH(m)),(HH(n))  
#define ST3(m,n)  (HH(m)),(HL(n))  

// A_3 domininant
#define SV0(m,n)  (HL(m)),(HL(n))
#define SV1(m,n)  (HL(m)),(HH(n))  
#define SV2(m,n)  (HH(m)),(HL(n))  
#define SV3(m,n)  (HH(m)),(HH(n))  



#define S1K(m,n,k)  (k),((n)-(k))  
#define S2K(m,n,k)  ((m)-(k)),(k)  
#define S3K(m,n,k)  ((m)-(k)), ((n)-(k))


#ifdef ROW_MAJOR

// A_0 dominant
#define M0(X,m,n,M,N)    (X)
#define M1(X,m,n,M,N)    ((X)+(HH(n)))
#define M2(X,m,n,M,N)    ((X)+(N)*(HH(m)))
#define M3(X,m,n,M,N)    ((X)+((N)*HH(m))+HH(n))

// A_1 dominant
#define MR0(X,m,n,M,N)    (X)
#define MR1(X,m,n,M,N)    ((X)+(HL(n)))
#define MR2(X,m,n,M,N)    ((X)+(N)*(HH(m)))
#define MR3(X,m,n,M,N)    ((X)+((N)*HH(m))+HL(n))

// A_2 dominant
#define MT0(X,m,n,M,N)    (X)
#define MT1(X,m,n,M,N)    ((X)+(HH(n)))
#define MT2(X,m,n,M,N)    ((X)+(N)*(HL(m)))
#define MT3(X,m,n,M,N)    ((X)+((N)*HL(m))+HH(n))

// A_3 dominant
#define MV0(X,m,n,M,N)    (X)
#define MV1(X,m,n,M,N)    ((X)+(HL(n)))
#define MV2(X,m,n,M,N)    ((X)+(N)*(HL(m)))
#define MV3(X,m,n,M,N)    ((X)+((N)*HL(m))+HL(n))



#define M1K(X,m,n,M,N,k)    ((X)+(k))
#define M2K(X,m,n,M,N,k)    ((X)+(N)*(k))
#define M3K(X,m,n,M,N,k)    ((X)+(N)*(k)+(k))


#define VD1_(X,m,n,M,N)  ((X)+(HH(m))*(N))
#define HD1_(X,m,n,M,N)  ((X)+(HH(n)))

#define VD1_k(X,m,n,M,N)  ((X)+(m)*(N))
#define HD1_k(X,m,n,M,N)  ((X)+(n))

#define E_(X,i,j,M,N)    ((X)[(i)*(N)+(j)])


#endif

#ifdef COLUMN_MAJOR
// A_0 dominant
#define M0(X,m,n,M,N)    (X)
#define M1(X,m,n,M,N)    ((X)+((M)*HH(n)))
#define M2(X,m,n,M,N)    ((X)+(HH(m)))
#define M3(X,m,n,M,N)    ((X)+((M)*HH(n))+HH(m))

// A_1 dominant
#define MR0(X,m,n,M,N)    (X)			
#define MR1(X,m,n,M,N)    ((X)+((M)*HL(n)))	
#define MR2(X,m,n,M,N)    ((X)+(HH(m)))		
#define MR3(X,m,n,M,N)    ((X)+((M)*HL(n))+HH(m))

// A_2 dominant
#define MT0(X,m,n,M,N)    (X)			
#define MT1(X,m,n,M,N)    ((X)+((M)*HH(n)))	
#define MT2(X,m,n,M,N)    ((X)+(HL(m)))		
#define MT3(X,m,n,M,N)    ((X)+((M)*HH(n))+HL(m))

// A_3 dominant
#define MV0(X,m,n,M,N)    (X)
#define MV1(X,m,n,M,N)    ((X)+((M)*HL(n)))
#define MV2(X,m,n,M,N)    ((X)+(HL(m)))
#define MV3(X,m,n,M,N)    ((X)+((M)*HL(n))+HL(m))


#define M1K(X,m,n,M,N,k)    ((X)+((M)*(k)))
#define M2K(X,m,n,M,N,k)    ((X)+(k))
#define M3K(X,m,n,M,N,k)    ((X)+(M)*(k)+(k))

#define VD1_(X,m,n,M,N)  ((X)+(HH(m)))
#define HD1_(X,m,n,M,N)  ((X)+(HH(n))*(M))

#define VD1_k(X,m,n,M,N)  ((X)+(m))
#define HD1_k(X,m,n,M,N)  ((X)+(n)*(M))



#define E_(X,i,j,M,N)    ((X)[(i)+(j)*(M)])

#endif





static inline int SIZE(int x, int y) { return ((x)*(y)); }



#define DEFORM_FACTOR_AM 2
#define DEFORM_FACTOR_AN 2
#define DEFORM_FACTOR_BN 2


#ifndef APPLICATION


// A0 is a quadrant of a matrix A, Q0(A) does the trick 
static inline Matrix Q0(Matrix x) {
  Matrix x0 = { M0(x.data,x.m,x.n,x.M,x.N), S0(x.m,x.n), x.M, x.N, x.trans, x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
  };
  return x0;
}
static inline Matrix Q1(Matrix x) {

  if (x.trans=='c' || x.trans =='t') { 
    Matrix x0 = { M2(x.data,x.m,x.n,x.M,x.N), S2(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else {
    Matrix x0 = { M1(x.data,x.m,x.n,x.M,x.N), S1(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
}
static inline Matrix Q2(Matrix x) {
  if (x.trans=='c' || x.trans =='t') {
    Matrix x0 = { M1(x.data,x.m,x.n,x.M,x.N), S1(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else { 
    Matrix x0 = { M2(x.data,x.m,x.n,x.M,x.N), S2(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
   }  
}
static inline Matrix Q3(Matrix x) {
  Matrix x0 = { M3(x.data,x.m,x.n,x.M,x.N), S3(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
  return x0;
}






static inline Matrix R0(Matrix x) {
  Matrix x0 = { MR0(x.data,x.m,x.n,x.M,x.N), SR0(x.m,x.n), x.M, x.N, x.trans, x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
  return x0;
}
static inline Matrix R1(Matrix x) {

  if (x.trans=='c' || x.trans =='t') { 
    Matrix x0 = { MR2(x.data,x.m,x.n,x.M,x.N), SR2(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else {
    Matrix x0 = { MR1(x.data,x.m,x.n,x.M,x.N), SR1(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
}
static inline Matrix R2(Matrix x) {
  if (x.trans=='c' || x.trans =='t') {
    Matrix x0 = { MR1(x.data,x.m,x.n,x.M,x.N), SR1(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else { 
    Matrix x0 = { MR2(x.data,x.m,x.n,x.M,x.N), SR2(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
   }  
}
static inline Matrix R3(Matrix x) {
  Matrix x0 = { MR3(x.data,x.m,x.n,x.M,x.N), SR3(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
  return x0;
}


static inline Matrix T0(Matrix x) {
  Matrix x0 = { MT0(x.data,x.m,x.n,x.M,x.N), ST0(x.m,x.n), x.M, x.N, x.trans, x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
  return x0;
}
static inline Matrix T1(Matrix x) {

  if (x.trans=='c' || x.trans =='t') { 
    Matrix x0 = { MT2(x.data,x.m,x.n,x.M,x.N), ST2(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else {
    Matrix x0 = { MT1(x.data,x.m,x.n,x.M,x.N), ST1(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
}
static inline Matrix T2(Matrix x) {
  if (x.trans=='c' || x.trans =='t') {
    Matrix x0 = { MT1(x.data,x.m,x.n,x.M,x.N), ST1(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else { 
    Matrix x0 = { MT2(x.data,x.m,x.n,x.M,x.N), ST2(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
   }  
}
static inline Matrix T3(Matrix x) {
  Matrix x0 = { MT3(x.data,x.m,x.n,x.M,x.N), ST3(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
  return x0;
}



static inline Matrix W0(Matrix x) {
  Matrix x0 = { MV0(x.data,x.m,x.n,x.M,x.N), SV0(x.m,x.n), x.M, x.N, x.trans, x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
  return x0;
}
static inline Matrix W1(Matrix x) {

  if (x.trans=='c' || x.trans =='t') { 
    Matrix x0 = { MV2(x.data,x.m,x.n,x.M,x.N), SV2(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else {
    Matrix x0 = { MV1(x.data,x.m,x.n,x.M,x.N), SV1(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
}
static inline Matrix W2(Matrix x) {
  if (x.trans=='c' || x.trans =='t') {
    Matrix x0 = { MV1(x.data,x.m,x.n,x.M,x.N), SV1(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else { 
    Matrix x0 = { MV2(x.data,x.m,x.n,x.M,x.N), SV2(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
   }  
}
static inline Matrix W3(Matrix x) {
  Matrix x0 = { MV3(x.data,x.m,x.n,x.M,x.N), SV3(x.m,x.n), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
  return x0;
}





static inline Matrix Q1K(Matrix x, int k) {

  if (x.trans=='c' || x.trans =='t') { 
    Matrix x0 = { M2K(x.data,x.m,x.n,x.M,x.N,k), S2K(x.m,x.n,k), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else {
    Matrix x0 = { M1K(x.data,x.m,x.n,x.M,x.N,k), S1K(x.m,x.n,k), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
}
static inline Matrix Q2K(Matrix x,int k) {
  if (x.trans=='c' || x.trans =='t') {
    Matrix x0 = { M1K(x.data,x.m,x.n,x.M,x.N,k), S1K(x.m,x.n,k), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
  else { 
    Matrix x0 = { M2K(x.data,x.m,x.n,x.M,x.N,k), S2K(x.m,x.n,k), x.M, x.N, x.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
   }  
}





// this is for the oblivious algorithm, as above to determine
// quadrants of the matrices but for pure rectangular matrices
static inline Matrix VD0(Matrix x) {
  Matrix x0 = x;
  x0.m = HH(x.m); 
  return x0;
}
static inline Matrix VD1(Matrix x) {
  Matrix x0 = x;
  x0.m = HL(x.m); 
  x0.data = VD1_(x.data,x.m,x.n,x.M,x.N);
  return x0;
}
static inline Matrix HD0(Matrix x) {
  Matrix x0 = x;
  x0.n = HH(x.n); 
  return x0;
}
static inline  Matrix HD1(Matrix x) {
  Matrix x0 = x;
  x0.n = HL(x.n); 
  x0.data = HD1_(x.data,x.m,x.n,x.M,x.N);
  return x0;
}


static inline Matrix VDK0(Matrix x, int k) {
  Matrix x0 = x;
  x0.m = k; 
  return x0;
}
static inline Matrix VDK1(Matrix x, int k) {
  Matrix x0 = x;
  x0.m = k; 
  x0.data = VD1_k(x.data,x.m-k,x.n,x.M,x.N);
  return x0;
}
static inline Matrix HDK0(Matrix x, int k) {
  Matrix x0 = x;
  x0.n = k; 
  return x0;
}
static inline  Matrix HDK1(Matrix x, int k) {
  Matrix x0 = x;
  x0.n = k      ; 
  x0.data = HD1_k(x.data,x.m,x.n-k,x.M,x.N);
  return x0;
}


/****************************************************************
 * These are used for the temporaries variables.
 * These are the restrictions how to access the matrices ...
 */

static inline Matrix RQ0(Matrix x, Matrix ref) {
  Matrix x0 = { x.data, S0(ref.m,ref.n), x.M, x.N, ref.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
  return x0;
}
static inline Matrix RQ1(Matrix x, Matrix ref) {
  if (ref.trans=='c' || ref.trans =='t') { 
    Matrix x0 = { x.data, S2(ref.m,ref.n), x.M, x.N, ref.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};   
    return x0;
  }
  else {
    Matrix x0 = { x.data, S1(ref.m,ref.n), x.M, x.N, ref.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
}
static inline Matrix RQ2(Matrix x, Matrix ref) {
  if (ref.trans=='c' || ref.trans =='t') { 
    Matrix x0 = { x.data, S1(ref.m,ref.n), x.M, x.N, ref.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};   
    return x0;
  }
  else {
    Matrix x0 = { x.data, S2(ref.m,ref.n), x.M, x.N, ref.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
};
    return x0;
  }
}
static inline Matrix RQ3(Matrix x, Matrix ref) {
  Matrix x0 = { x.data, S3(ref.m,ref.n), x.M, x.N, ref.trans,x.beta
#if(CLBLAS||ROCMBLAS)
		, x.gpu
#endif
  };
  return x0;
}


/********************************************
 * Permutation operations 
 *
 */


#define multiplyXp(X,p) X*p


static inline void RP(Matrix x, Matrix *XP, int *p, int tick) {
  
  
  //printf("Permutation tick %d ",tick);  
  


  switch (tick) {
  case 1:
    XP[0] = R1(x);XP[0].beta = multiplyXp(XP[0].beta ,p[2]);//printf("1 ");
    XP[1] = R0(x);XP[1].beta = multiplyXp(XP[1].beta ,p[1]);//printf("0 ");
    XP[2] = R3(x);XP[2].beta = multiplyXp(XP[2].beta ,p[2]);//printf("3 ");
    XP[3] = R2(x);XP[3].beta = multiplyXp(XP[3].beta ,p[1]);//printf("2 ");
    break;		     	            
  case -1:		     	            
    XP[0] = T2(x);XP[0].beta = multiplyXp(XP[0].beta ,p[1]);//printf("2 ");
    XP[1] = T3(x);XP[1].beta = multiplyXp(XP[1].beta ,p[1]);//printf("3 ");
    XP[2] = T0(x);XP[2].beta = multiplyXp(XP[2].beta ,p[2]);//printf("0 ");
    XP[3] = T1(x);XP[3].beta = multiplyXp(XP[3].beta ,p[2]);//printf("1 ");
    break;		     	            
  case 0:		     	            
    XP[0] = W3(x);XP[0].beta = multiplyXp(XP[0].beta ,p[2]*p[1]);
    XP[1] = W2(x);XP[1].beta = multiplyXp(XP[1].beta ,p[2]*p[1]);
    XP[2] = W1(x);XP[2].beta = multiplyXp(XP[2].beta ,p[2]*p[1]);
    XP[3] = W0(x);XP[3].beta = multiplyXp(XP[3].beta ,p[2]*p[1]);
    break;
  }

  //  printf("\n");


}




#endif
// Toy 
#define SELECT(x) { do {  scanf("%d",&sel); } while (sel<0 || sel>2); }
#endif
