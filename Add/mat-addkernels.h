/* arguments 2 unroll 16 */
/* This file has been automatically generated  */
#ifndef MAT_ADD_KERNELS 
#define MAT_ADD_KERNELS 1 
#include <mat-operands.h> 
#define fpmul(frac,a,b)  ((int)((((long long )(a))*((long long )(b)))>>(frac))) 
#define fpmadd(c, a, b)  c+=(a)*(b) //c+=fpmul((FRAC),(a),(b)) 
#define UNLOOPREADAT(a,j) { \
a0 = a[j+0]; \
a1 = a[j+1]; \
a2 = a[j+2]; \
a3 = a[j+3]; \
a4 = a[j+4]; \
a5 = a[j+5]; \
a6 = a[j+6]; \
a7 = a[j+7]; \
a8 = a[j+8]; \
a9 = a[j+9]; \
a10 = a[j+10]; \
a11 = a[j+11]; \
a12 = a[j+12]; \
a13 = a[j+13]; \
a14 = a[j+14]; \
a15 = a[j+15]; \
}
#define UNLOOPWRITEAT(a,j) { \
a[j+0] = a0; \
a[j+1] = a1; \
a[j+2] = a2; \
a[j+3] = a3; \
a[j+4] = a4; \
a[j+5] = a5; \
a[j+6] = a6; \
a[j+7] = a7; \
a[j+8] = a8; \
a[j+9] = a9; \
a[j+10] = a10; \
a[j+11] = a11; \
a[j+12] = a12; \
a[j+13] = a13; \
a[j+14] = a14; \
a[j+15] = a15; \
}
#define UNLOOPCOMPUTE(b,j) { \
a0 += b[j+0]; \
a1 += b[j+1]; \
a2 += b[j+2]; \
a3 += b[j+3]; \
a4 += b[j+4]; \
a5 += b[j+5]; \
a6 += b[j+6]; \
a7 += b[j+7]; \
a8 += b[j+8]; \
a9 += b[j+9]; \
a10 += b[j+10]; \
a11 += b[j+11]; \
a12 += b[j+12]; \
a13 += b[j+13]; \
a14 += b[j+14]; \
a15 += b[j+15]; \
}
#define UNLOOPCOMPUTESUB(b,j) { \
a0 -= b[j+0]; \
a1 -= b[j+1]; \
a2 -= b[j+2]; \
a3 -= b[j+3]; \
a4 -= b[j+4]; \
a5 -= b[j+5]; \
a6 -= b[j+6]; \
a7 -= b[j+7]; \
a8 -= b[j+8]; \
a9 -= b[j+9]; \
a10 -= b[j+10]; \
a11 -= b[j+11]; \
a12 -= b[j+12]; \
a13 -= b[j+13]; \
a14 -= b[j+14]; \
a15 -= b[j+15]; \
}
#define UNLOOPREADAT_t(a,j,beta) { \
a0 = beta*a[j+0]; \
a1 = beta*a[j+1]; \
a2 = beta*a[j+2]; \
a3 = beta*a[j+3]; \
a4 = beta*a[j+4]; \
a5 = beta*a[j+5]; \
a6 = beta*a[j+6]; \
a7 = beta*a[j+7]; \
a8 = beta*a[j+8]; \
a9 = beta*a[j+9]; \
a10 = beta*a[j+10]; \
a11 = beta*a[j+11]; \
a12 = beta*a[j+12]; \
a13 = beta*a[j+13]; \
a14 = beta*a[j+14]; \
a15 = beta*a[j+15]; \
}
#define UNLOOPCOMPUTE_t(b,j,beta) { \
a0 += beta*b[j+0]; \
a1 += beta*b[j+1]; \
a2 += beta*b[j+2]; \
a3 += beta*b[j+3]; \
a4 += beta*b[j+4]; \
a5 += beta*b[j+5]; \
a6 += beta*b[j+6]; \
a7 += beta*b[j+7]; \
a8 += beta*b[j+8]; \
a9 += beta*b[j+9]; \
a10 += beta*b[j+10]; \
a11 += beta*b[j+11]; \
a12 += beta*b[j+12]; \
a13 += beta*b[j+13]; \
a14 += beta*b[j+14]; \
a15 += beta*b[j+15]; \
}
#define UNLOOPCOMPUTESUB_t(b,j,beta) { \
a0 -= beta*b[j+0]; \
a1 -= beta*b[j+1]; \
a2 -= beta*b[j+2]; \
a3 -= beta*b[j+3]; \
a4 -= beta*b[j+4]; \
a5 -= beta*b[j+5]; \
a6 -= beta*b[j+6]; \
a7 -= beta*b[j+7]; \
a8 -= beta*b[j+8]; \
a9 -= beta*b[j+9]; \
a10 -= beta*b[j+10]; \
a11 -= beta*b[j+11]; \
a12 -= beta*b[j+12]; \
a13 -= beta*b[j+13]; \
a14 -= beta*b[j+14]; \
a15 -= beta*b[j+15]; \
}
#ifdef ROW_MAJOR
#define UNROLLKERNEL(c,a,b,i,j,y,COMPUTATION)\
UNLOOPREADAT((a.data+i*a.N),0);\
  for (j=0;j<y-2*16;j+=16) {\
      COMPUTATION((b.data+i*b.N),j);	\
      UNLOOPWRITEAT((c.data+i*c.N),j);\
      UNLOOPREADAT((a.data+i*a.N),j+16);\
    }\
  COMPUTATION((b.data+i*b.N),j);\
  UNLOOPWRITEAT((c.data+i*c.N),j);\
  j+=16;
#define UNROLLKERNEL_t(c,a,b,i,j,y,COMPUTATION)\
  UNLOOPREADAT_t((a.data+i*a.N),0,a.beta);\
\
    for (j=0;j<y-2*16;j+=16) { \
      COMPUTATION((b.data+i*b.N),j,b.beta);	 \
      UNLOOPWRITEAT((c.data+i*c.N),j); \
      UNLOOPREADAT_t((a.data+i*a.N),j+16,a.beta);	\
    }\
  COMPUTATION((b.data+i*b.N),j,b.beta);    \
  UNLOOPWRITEAT((c.data+i*c.N),j); \
  j+=16;
#endif
#ifdef COLUMN_MAJOR
#define UNROLLKERNEL(c,a,b,i,j,y,COMPUTATION)	\
  UNLOOPREADAT((a.data+j*a.M),0); \
\
    for (i=0;i<x-2*16;i+=16) { \
      COMPUTATION((b.data+j*b.M),i);				\
      UNLOOPWRITEAT((c.data+j*c.M),i); \
      UNLOOPREADAT((a.data+j*a.M),i+16);\
    }\
  COMPUTATION((b.data+j*b.M),i);     \
  UNLOOPWRITEAT((c.data+j*c.M),i); \
  i+=16;
#define UNROLLKERNEL_t(c,a,b,i,j,y,COMPUTATION)	\
  UNLOOPREADAT_t((a.data+j*a.M),0,a.beta);			\
\
  for (i=0;i<x-2*16;i+=16) { \
      COMPUTATION((b.data+j*b.M),i,b.beta);	 \
      UNLOOPWRITEAT((c.data+j*c.M),i); \
      UNLOOPREADAT_t((a.data+j*a.M),i+16,a.beta);	\
    }\
  COMPUTATION((b.data+j*b.M),i,b.beta);    \
  UNLOOPWRITEAT((c.data+j*c.M),i); \
  i+=16;
#endif
 
#if (LIBRARY_PACKAGE)						        
								        
#if(SINGLE_PRECISION)			        
#define add 	      s_add 	      				        
#define sub 	      s_sub 	      				        
#define add_amd       s_add_amd       				        
#define sub_amd       s_sub_amd       				        
#define add_t 	      s_add_t 	      				        
#define sub_t 	      s_sub_t 	      				        
#define add_amd_t     s_add_amd_t     				        
#define sub_amd_t     s_sub_amd_t     				        
#define copy	      s_copy	      				        
#define copy_matrix   s_copy_matrix   				        
#define comp	      s_comp	      				        
#define print	      s_print	      				        
#define ptadd	      s_ptadd	      				        
#define ptadd_t	      s_ptadd_t	      				        
#define ptsub	      s_ptsub	      				        
#define ptsub_t	      s_ptsub_t	      				        
#define ptcopy        s_ptcopy        				        
#define randomInitialization        s_randomInitialization        				        
#define randomInitializationError   s_randomInitializationError        				        
#endif								        
#if(DOUBLE_PRECISION)			        
#define add 	      d_add 	      				        
#define sub 	      d_sub 	      				        
#define add_amd       d_add_amd       				        
#define sub_amd       d_sub_amd       				        
#define add_t 	      d_add_t 	      				        
#define sub_t 	      d_sub_t 	      				        
#define add_amd_t     d_add_amd_t     				        
#define sub_amd_t     d_sub_amd_t     				        
#define copy	      d_copy	      				        
#define copy_matrix   d_copy_matrix   				        
#define comp	      d_comp	      				        
#define print	      d_print	      				        
#define ptadd	      d_ptadd	      				        
#define ptadd_t	      d_ptadd_t	      				        
#define ptsub	      d_ptsub	      				        
#define ptsub_t	      d_ptsub_t	      				        
#define ptcopy        d_ptcopy        				        
#define randomInitialization        d_randomInitialization        				        
#define randomInitializationError   d_randomInitializationError        				        
								        
#endif								        
#if(SINGLE_COMPLEX)				        
#define add 	      c_add 	      				        
#define sub 	      c_sub 	      				        
#define add_amd       c_add_amd       				        
#define sub_amd       c_sub_amd       				        
#define add_t 	      c_add_t 	      				        
#define sub_t 	      c_sub_t 	      				        
#define add_amd_t     c_add_amd_t     				        
#define sub_amd_t     c_sub_amd_t     				        
#define copy	      c_copy	      				        
#define copy_matrix   c_copy_matrix   				        
#define comp	      c_comp	      				        
#define print	      c_print	      				        
#define ptadd	      c_ptadd	      				        
#define ptadd_t	      c_ptadd_t	      				        
#define ptsub	      c_ptsub	      				        
#define ptsub_t	      c_ptsub_t	      				        
#define ptcopy        c_ptcopy        				        
#define randomInitialization        c_randomInitialization        		  	        
								        
#define randomInitializationError   c_randomInitializationError        				        
#endif								        
#if(DOUBLE_COMPLEX)				        
#define add 	      z_add 	      				        
#define sub 	      z_sub 	      				        
#define add_amd       z_add_amd       				        
#define sub_amd       z_sub_amd       				        
#define add_t 	      z_add_t 	      				        
#define sub_t 	      z_sub_t 	      				        
#define add_amd_t     z_add_amd_t     				        
#define sub_amd_t     z_sub_amd_t     				        
#define copy	      z_copy	      				        
#define copy_matrix   z_copy_matrix   				        
#define comp	      z_comp	      				        
#define print	      z_print	      				        
#define ptadd	      z_ptadd	      				        
#define ptadd_t	      z_ptadd_t	      				        
#define ptsub	      z_ptsub	      				        
#define ptsub_t	      z_ptsub_t	      				        
#define ptcopy        z_ptcopy        				        
#define randomInitialization        z_randomInitialization        				        
#define randomInitializationError   z_randomInitializationError        				        
#endif								        
								        
								        
#ifndef MAT_ADD_MODULE 						        
int add (DEF(c), DEF(a), DEF(b));				        
int sub (DEF(c), DEF(a), DEF(b));				        
int add_amd (DEF(c), DEF(a), DEF(b));				        
int sub_amd (DEF(c), DEF(a), DEF(b));				        
int add_t (DEF(c), DEF(a), DEF(b));				        
int sub_t (DEF(c), DEF(a), DEF(b));				        
int add_amd_t (DEF(c), DEF(a), DEF(b));			        
int sub_amd_t (DEF(c), DEF(a), DEF(b));			        
void copy(DEF(c), DEF(a));					        
int copy_matrix(DEF(c), DEF(a),DEF(b));			        
int  comp(DEF(c), DEF(a));					        
void print(DEF(c));						        
int ptadd(DEF(c), DEF(a), DEF(b));				        
int ptadd_t(DEF(c), DEF(a), DEF(b));				        
int ptsub(DEF(c), DEF(a), DEF(b));				        
int ptsub_t(DEF(c), DEF(a), DEF(b));				        
void ptcopy(DEF(c), DEF(a), DEF(b));				        
void randomInitialization(DEF(a), int seed1, int seed2);				        
void randomInitializationError(DEF(a), int seed1);				        
#endif								        
								        
								        
#elif(APPLICATION)						        
								        
int s_add (S_Matrix c, S_Matrix a, S_Matrix b);				        
int s_sub (S_Matrix c, S_Matrix a, S_Matrix b);				        
int s_add_amd (S_Matrix c, S_Matrix a, S_Matrix b);			        
int s_sub_amd (S_Matrix c, S_Matrix a, S_Matrix b);			        
int s_add_t (S_Matrix c, S_Matrix a, S_Matrix b);				        
int s_sub_t (S_Matrix c, S_Matrix a, S_Matrix b);				        
int s_add_amd_t (S_Matrix c, S_Matrix a, S_Matrix b);			        
int s_sub_amd_t (S_Matrix c, S_Matrix a, S_Matrix b);			        
void s_copy(S_Matrix c, S_Matrix a);					        
int s_copy_matrix(S_Matrix c, S_Matrix a, S_Matrix b);			        
int  s_comp(S_Matrix c, S_Matrix a);					        
void s_print(S_Matrix c);						        
int s_ptadd(S_Matrix c, S_Matrix a, S_Matrix b);				        
int s_ptadd_t(S_Matrix c, S_Matrix a, S_Matrix b);				        
int s_ptsub(S_Matrix c, S_Matrix a, S_Matrix b);				        
int s_ptsub_t(S_Matrix c, S_Matrix a, S_Matrix b);				        
int s_ptcopy(S_Matrix c, S_Matrix a, S_Matrix b);				        
void s_randomInitialization(S_Matrix a, int seed1, int seed2);				        
void s_randomInitializationError(S_Matrix a, int seed1);				        
								        
int d_add (D_Matrix c, D_Matrix a, D_Matrix b);				        
int d_sub (D_Matrix c, D_Matrix a, D_Matrix b);				        
int d_add_amd (D_Matrix c, D_Matrix a, D_Matrix b);			        
int d_sub_amd (D_Matrix c, D_Matrix a, D_Matrix b);			        
int d_add_t (D_Matrix c, D_Matrix a, D_Matrix b);				        
int d_sub_t (D_Matrix c, D_Matrix a, D_Matrix b);				        
int d_add_amd_t (D_Matrix c, D_Matrix a, D_Matrix b);			        
int d_sub_amd_t (D_Matrix c, D_Matrix a, D_Matrix b);			        
void d_copy(D_Matrix c, D_Matrix a);					        
int d_copy_matrix(D_Matrix c, D_Matrix a, D_Matrix b);			        
int  d_comp(D_Matrix c, D_Matrix a);					        
void d_print(D_Matrix c);						        
int d_ptadd(D_Matrix c, D_Matrix a, D_Matrix b);				        
int d_ptadd_t(D_Matrix c, D_Matrix a, D_Matrix b);				        
int d_ptsub(D_Matrix c, D_Matrix a, D_Matrix b);				        
int d_ptsub_t(D_Matrix c, D_Matrix a, D_Matrix b);				        
int d_ptcopy(D_Matrix c, D_Matrix a, D_Matrix b);				        
void d_randomInitialization(D_Matrix a, int seed1, int seed2);				        
void d_randomInitializationError(D_Matrix a, int seed1);				        
								        
int c_add (C_Matrix c, C_Matrix a, C_Matrix b);				        
int c_sub (C_Matrix c, C_Matrix a, C_Matrix b);				        
int c_add_amd (C_Matrix c, C_Matrix a, C_Matrix b);			        
int c_sub_amd (C_Matrix c, C_Matrix a, C_Matrix b);			        
int c_add_t (C_Matrix c, C_Matrix a, C_Matrix b);				        
int c_sub_t (C_Matrix c, C_Matrix a, C_Matrix b);				        
int c_add_amd_t (C_Matrix c, C_Matrix a, C_Matrix b);			        
int c_sub_amd_t (C_Matrix c, C_Matrix a, C_Matrix b);			        
void c_copy(C_Matrix c, C_Matrix a);					        
int c_copy_matrix(C_Matrix c, C_Matrix a, C_Matrix b);			        
int  c_comp(C_Matrix c, C_Matrix a);					        
void c_print(C_Matrix c);						        
int c_ptadd(C_Matrix c, C_Matrix a, C_Matrix b);				        
int c_ptadd_t(C_Matrix c, C_Matrix a, C_Matrix b);				        
int c_ptsub(C_Matrix c, C_Matrix a, C_Matrix b);				        
int c_ptsub_t(C_Matrix c, C_Matrix a, C_Matrix b);				        
int c_ptcopy(C_Matrix c, C_Matrix a, C_Matrix b);				        
void c_randomInitialization(C_Matrix a, int seed1, int seed2);				        
void c_randomInitializationError(C_Matrix a, int seed1);				        
								        
int z_add (Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
int z_sub (Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
int z_add_amd (Z_Matrix c, Z_Matrix a, Z_Matrix b);			        
int z_sub_amd (Z_Matrix c, Z_Matrix a, Z_Matrix b);			        
int z_add_t (Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
int z_sub_t (Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
int z_add_amd_t (Z_Matrix c, Z_Matrix a, Z_Matrix b);			        
int z_sub_amd_t (Z_Matrix c, Z_Matrix a, Z_Matrix b);			        
void z_copy(Z_Matrix c, Z_Matrix a);					        
int z_copy_matrix(Z_Matrix c, Z_Matrix a, Z_Matrix b);			        
int z_comp(Z_Matrix c, Z_Matrix a);					        
void z_print(Z_Matrix c);						        
int z_ptadd(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
int z_ptadd_t(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
int z_ptsub(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
int z_ptsub_t(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
int z_ptcopy(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        
void z_randomInitialization(Z_Matrix a, int seed1, int seed2);				        
void z_randomInitializationError(Z_Matrix a, int seed1);				        
#endif  // if LIBRARY else APPLICATION                                                                
#define DEFREGISTERS Mat a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15;
#endif // MODULE 
