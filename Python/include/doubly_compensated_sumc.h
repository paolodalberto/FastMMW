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
#ifndef DOUBLY_COMPENSATED_SUM

#define DOUBLY_COMPENSATED_SUM 1

#include <mat-operands.h>
#include <sort.h>

#include <quicksort.h>


#if(APPLICATION)

struct dcmul_data_f { 
  int pi;
  float  c,a,b;
  int l,u;
};

typedef struct dcmul_data_f S_DCMul_Data;

struct dcmul_data_d { 
  int pi;
  double c,a,b;
  int l,u;
};

typedef struct dcmul_data_d D_DCMul_Data;

struct dcmul_data_c { 
  int pi;
  float complex  c,a,b;
  int l,u;
};

typedef struct dcmul_data_c C_DCMul_Data;
struct dcmul_data_z { 
  int pi;
  double complex c,a,b;
  int l,u;
};

typedef struct dcmul_data_z Z_DCMul_Data;

#else


#if  SINGLE_PRECISION &&  LIBRARY_PACKAGE
#define DCMul_Data S_DCMul_Data
#elif  DOUBLE_PRECISION &&  LIBRARY_PACKAGE
#define DCMul_Data D_DCMul_Data
#elif  SINGLE_COMPLEX &&  LIBRARY_PACKAGE
#define DCMul_Data C_DCMul_Data
#elif  DOUBLE_COMPLEX &&  LIBRARY_PACKAGE
#define DCMul_Data Z_DCMul_Data
#endif


struct dcmul_data { 
  int pi;
  Matrix c,a,b;
  int l,u;
};

typedef struct dcmul_data DCMul_Data;



#endif




#define COREDCSUM(n,k,s_k,c_k,y_k,u_k,t_k,v_k,z_k,x_k,F0,Fk)  { \
    x_k = F0;                                                   \
    s_k =  x_k;                                                 \
    c_k = 0;                                                    \
    for (k = 1; k <n; k++) {                                    \
      x_k = Fk;                                                 \
      y_k = c_k +  x_k;                                         \
      u_k = x_k - (y_k-c_k);                                    \
      t_k = y_k + s_k;                                          \
      v_k = y_k-(t_k-s_k);                                      \
      z_k = u_k+v_k;                                            \
      s_k = t_k+z_k;                                            \
      c_k = z_k-(s_k-t_k);                                      \
    }                                                           \
}



#define COREDCSUMK(n,k,s_k,c_k,y_k,u_k,t_k,v_k,z_k,x_k,F0,Fk,D0,Dk)  {  \
    x_k = F0;                                                   \
    D0 = s_k =  x_k;                                            \
    c_k = 0;                                                    \
    for (k = 1; k <n; k++) {                                    \
      x_k = Fk;                                                 \
      y_k = c_k +  x_k;                                         \
      u_k = x_k - (y_k-c_k);                                    \
      t_k = y_k  + s_k;                                         \
      v_k = y_k-(t_k-s_k);                                      \
      z_k = u_k+v_k;                                            \
      s_k = t_k+z_k;                                            \
      Dk = s_k;                                                 \
      c_k = z_k-(s_k-t_k);                                      \
    }                                                           \
}






#define SORTI(x,y) partial_quickersort_inverse((x),0,((y)-1))

#define SORT(x,y) partial_quickersort((x),0,((y)-1))
#define SORT_P(x,y) {				  \
    Processor_Pool PP = {_P,0,3};		  \
    Sort_Datum S;				  \
    S.array =(x);				  \
    S.l=0;					  \
    S.u=(y-1);					  \
    S.p = PP;					  \
    parallel_quickersort((void*)&S);		  \
  }

#ifdef LIBRARY_PACKAGE

#if(SINGLE_PRECISION)
#define sum		   s_sum		   
#define dcsum		   s_dcsum		   
#define partialdcsum	   s_partialdcsum	   
#define sorted_dcsum	   s_sorted_dcsum	   
#define sorted_sum	   s_sorted_sum	   
#define dotproduct	   s_dotproduct	   
#define dotdiff_ABS	   s_dotdiff_ABS	   
#define dotmul		   s_dotmul		   
#define dcmul		   s_dcmul		   
#define dcmadd		   s_dcmadd		   
#define max_error	   s_max_error	   
#define max_relative_error s_max_relative_error 
#define average_error	   s_average_error	   
#define power_error	   s_power_error	   
#define error_analysis     s_error_analysis     
#define dcmsum             s_dcmsum
#endif
#if(DOUBLE_PRECISION)
#define sum		   d_sum		   
#define dcsum		   d_dcsum		   
#define partialdcsum	   d_partialdcsum	   
#define sorted_dcsum	   d_sorted_dcsum	   
#define sorted_sum	   d_sorted_sum	   
#define dotproduct	   d_dotproduct	   
#define dotdiff_ABS	   d_dotdiff_ABS	   
#define dotmul		   d_dotmul		   
#define dcmul		   d_dcmul		   
#define dcmadd		   d_dcmadd		   
#define max_error	   d_max_error	   
#define max_relative_error d_max_relative_error 
#define average_error	   d_average_error	   
#define power_error	   d_power_error	   
#define error_analysis     d_error_analysis     
#define dcmsum             d_dcmsum

#endif
#if(SINGLE_COMPLEX)
#define sum		   c_sum		   
#define dcsum		   c_dcsum		   
#define partialdcsum	   c_partialdcsum	   
#define sorted_dcsum	   c_sorted_dcsum	   
#define sorted_sum	   c_sorted_sum	   
#define dotproduct	   c_dotproduct	   
#define dotdiff_ABS	   c_dotdiff_ABS	   
#define dotmul		   c_dotmul		   
#define dcmul		   c_dcmul		   
#define dcmadd		   c_dcmadd		   
#define max_error	   c_max_error	   
#define max_relative_error c_max_relative_error 
#define average_error	   c_average_error	   
#define power_error	   c_power_error	   
#define error_analysis     c_error_analysis     
#define dcmsum             c_dcmsum

#endif
#if(DOUBLE_COMPLEX)
#define sum		   z_sum		   
#define dcsum		   z_dcsum		   
#define partialdcsum	   z_partialdcsum	   
#define sorted_dcsum	   z_sorted_dcsum	   
#define sorted_sum	   z_sorted_sum	   
#define dotproduct	   z_dotproduct	   
#define dotdiff_ABS	   z_dotdiff_ABS	   
#define dotmul		   z_dotmul		   
#define dcmul		   z_dcmul		   
#define dcmadd		   z_dcmadd		   
#define max_error	   z_max_error	   
#define max_relative_error z_max_relative_error 
#define average_error	   z_average_error	   
#define power_error	   z_power_error	   
#define error_analysis     z_error_analysis     
#define dcmsum             z_dcmsum


#endif			   


#ifndef DOUBLY_COMPENSATED_SUM_MODULE
extern Mat    sum(Mat *x, int n);
extern Mat    dcsum(Mat *x, int n);
extern Mat    *partialdcsum(Mat *x, int n);
extern Mat    sorted_dcsum(Mat *x, int n);
extern Mat    sorted_sum(Mat *x, int n);
extern void   dotproduct(Mat *z, DEF(a), DEF(b), int i, int j);
extern void   dotdiff_ABS(Mat *z, Mat *a, Mat *b, int n);
extern void   dotmul(Mat *z, Mat *a, Mat *b, int n);
extern void   dcmul(DEF(c), DEF(a), DEF(b)); 
extern void   dcmadd(DEF(c), DEF(a), DEF(b));
extern Mat    max_error(Mat *diff, int size, int *k);
extern Mat    max_relative_error(Mat *diff, Mat *ref, int size, int *k);
extern Mat    average_error(Mat *diff, int size);
extern double power_error(Mat *diff, int size);
extern void   error_analysis(DEF(a),DEF(b));
extern void dcmsum(DEF(c), DEF(a), DEF(b));

#endif

#elif APPLICATION 

extern float    s_sum(float *x, int n);
extern float    s_dcsum(float *x, int n);
extern float   *s_partialdcsum(float *x, int n);
extern float    s_sorted_dcsum(float *x, int n);
extern float    s_sorted_sum(float *x, int n);
extern void     s_dotproduct(float *z, DEF_S(a), DEF_S(b), int i, int j);
extern void     s_dotdiff_ABS(float *z, float *a, float *b, int n);
extern void     s_dotmul(float *z, float *a, float *b, int n);
extern void     s_dcmul(DEF_S(c), DEF_S(a), DEF_S(b)); 
extern void     s_dcmadd(DEF_S(c), DEF_S(a), DEF_S(b));
extern float    s_max_error(float *diff, int size, int *k);
extern float    s_max_relative_error(float *diff, float *ref, int size, int *k);
extern float    s_average_error(float *diff, int size);
extern double   s_power_error(float *diff, int size);
extern void     s_error_analysis(DEF_S(a),DEF_S(b));
extern void     s_dcmsum(DEF_S(c), DEF_S(a), DEF_S(b));



extern double    d_sum(double *x, int n);
extern double    d_dcsum(double *x, int n);
extern double   *d_partialdcsum(double *x, int n);
extern double    d_sorted_dcsum(double *x, int n);
extern double    d_sorted_sum(double *x, int n);
extern void      d_dotproduct(double *z, DEF_D(a), DEF_D(b), int i, int j);
extern void      d_dotdiff_ABS(double *z, double *a, double *b, int n);
extern void      d_dotmul(double *z, double *a, double *b, int n);
extern void      d_dcmul(DEF_D(c), DEF_D(a), DEF_D(b)); 
extern void      d_dcmadd(DEF_D(c), DEF_D(a), DEF_D(b));
extern double    d_max_error(double *diff, int size, int *k);
extern double    d_max_relative_error(double *diff, double *ref, int size, int *k);
extern double    d_average_error(double *diff, int size);
extern double    d_power_error(double *diff, int size);
extern void      d_error_analysis(DEF_D(a),DEF_D(b));
extern void      d_dcmsum(DEF_D(c), DEF_D(a), DEF_D(b));


extern float complex    c_sum(float complex *x, int n);
extern float complex    c_dcsum(float complex *x, int n);
extern float complex   *c_partialdcsum(float complex *x, int n);
extern float complex    c_sorted_dcsum(float complex *x, int n);
extern float complex    c_sorted_sum(float complex *x, int n);
extern void             c_dotproduct(float complex *z, DEF_C(a), DEF_C(b), int i, int j);
extern void             c_dotdiff_ABS(float complex *z, float complex *a, float complex *b, int n);
extern void             c_dotmul(float complex *z, float complex *a, float complex *b, int n);
extern void             c_dcmul(DEF_C(c), DEF_C(a), DEF_C(b)); 
extern void             c_dcmadd(DEF_C(c), DEF_C(a), DEF_C(b));
extern float complex    c_max_error(float complex *diff, int size, int *k);
extern float complex    c_max_relative_error(float complex *diff, float complex *ref, int size, int *k);
extern float complex    c_average_error(float complex *diff, int size);
extern double           c_power_error(float complex *diff, int size);
extern void             c_error_analysis(DEF_C(a),DEF_C(b));
extern void             c_dcmsum(DEF_C(c), DEF_C(a), DEF_C(b));


extern double complex    z_sum(double complex *x, int n);
extern double complex    z_dcsum(double complex *x, int n);
extern double complex   *z_partialdcsum(double complex *x, int n);
extern double complex    z_sorted_dcsum(double complex *x, int n);
extern double complex    z_sorted_sum(double complex *x, int n);
extern void              z_dotproduct(double complex *z, DEF_Z(a), DEF_Z(b), int i, int j);
extern void              z_dotdiff_ABS(double complex *z, double complex *a, double complex *b, int n);
extern void              z_dotmul(double complex *z, double complex *a, double complex *b, int n);
extern void              z_dcmul(DEF_Z(c), DEF_Z(a), DEF_Z(b)); 
extern void              z_dcmadd(DEF_Z(c), DEF_Z(a), DEF_Z(b));
extern double complex    z_max_error(double complex *diff, int size, int *k);
extern double complex    z_max_relative_error(double complex *diff, double complex *ref, int size, int *k);
extern double complex    z_average_error(double complex *diff, int size);
extern double            z_power_error(double complex  *diff, int size);
extern void              z_dcmsum(DEF_Z(c), DEF_Z(a), DEF_Z(b));
extern void              z_error_analysis(DEF_Z(a),DEF_Z(b));


#endif

#endif
