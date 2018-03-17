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
#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include <stdlib.h>
#include <mat-operands.h>


#ifndef CUTOFF
#define CUTOFF 64
#endif


#if(SINGLE_PRECISION)
#define ABS(x) fabsf((x))
#endif
#if(DOUBLE_PRECISION)
#define ABS(x) fabs((x))
#endif
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
#include <complex.h>
#define ABS(x) cabs((x))
#endif


#ifdef LIBRARY_PACKAGE

#if(SINGLE_PRECISION)
#define  printV                         s_printV			     
#define  parallel_quickersort 		s_parallel_quickersort 	     
#define  orderTest			s_orderTest		     
#define  partial_quickersort 		s_partial_quickersort 	     
#define  insort 			s_insort 		     
#define  partial_quickersort_inverse 	s_partial_quickersort_inverse 
#define  insort_inverse              	s_insort_inverse              
#endif
#if(DOUBLE_PRECISION)
#define  printV                         d_printV			     
#define  parallel_quickersort 		d_parallel_quickersort 	     
#define  orderTest			d_orderTest		     
#define  partial_quickersort 		d_partial_quickersort 	     
#define  insort 			d_insort 		     
#define  partial_quickersort_inverse 	d_partial_quickersort_inverse 
#define  insort_inverse              	d_insort_inverse              
#endif
#if(SINGLE_COMPLEX)
#define  printV                         c_printV			     
#define  parallel_quickersort 		c_parallel_quickersort 	     
#define  orderTest			c_orderTest		     
#define  partial_quickersort 		c_partial_quickersort 	     
#define  insort 			c_insort 		     
#define  partial_quickersort_inverse 	c_partial_quickersort_inverse 
#define  insort_inverse              	c_insort_inverse              
#endif
#if(DOUBLE_COMPLEX)
#define  printV                         z_printV			     
#define  parallel_quickersort 		z_parallel_quickersort 	     
#define  orderTest			z_orderTest		     
#define  partial_quickersort 		z_partial_quickersort 	     
#define  insort 			z_insort 		     
#define  partial_quickersort_inverse 	z_partial_quickersort_inverse 
#define  insort_inverse              	z_insort_inverse              
#endif
#ifndef QUICKSORT_MODULE
extern void  printV(Mat *m, int n);
extern void* parallel_quickersort (void *d);
extern int   orderTest(Mat *m, int n, int j);
extern void  partial_quickersort (register Mat *array, register int lower, register int upper);
extern void  insort (register Mat * array, register int len);
extern void  partial_quickersort_inverse (register Mat *array, register int lower, register int upper);
extern void  insort_inverse (register Mat * array, register int len);
#endif

#elif(APPLICATION)

extern void  s_printV(float *m, int n);
extern void* s_parallel_quickersort (void *d);
extern int   s_orderTest(float *m, int n, int j);
extern void  s_partial_quickersort (register float *array, register int lower, register int upper);
extern void  s_insort (register float * array, register int len);
extern void  s_partial_quickersort_inverse (register float *array, register int lower, register int upper);
extern void  s_insort_inverse (register float * array, register int len);

extern void  d_printV(double *m, int n);
extern void* d_parallel_quickersort (void *d);
extern int   d_orderTest(double *m, int n, int j);
extern void  d_partial_quickersort (register double *array, register int lower, register int upper);
extern void  d_insort (register double * array, register int len);
extern void  d_partial_quickersort_inverse (register double *array, register int lower, register int upper);
extern void  d_insort_inverse (register double * array, register int len);

extern void  c_printV(float complex *m, int n);
extern void* c_parallel_quickersort (void *d);
extern int   c_orderTest(float complex *m, int n, int j);
extern void  c_partial_quickersort (register float complex *array, register int lower, register int upper);
extern void  c_insort (register float complex * array, register int len);
extern void  c_partial_quickersort_inverse (register float complex *array, register int lower, register int upper);
extern void  c_insort_inverse (register float complex * array, register int len);

extern void  z_printV(double complex *m, int n);
extern void* z_parallel_quickersort (void *d);
extern int   z_orderTest(double complex *m, int n, int j);
extern void  z_partial_quickersort (register double complex *array, register int lower, register int upper);
extern void  z_insort (register double complex * array, register int len);
extern void  z_partial_quickersort_inverse (register double complex *array, register int lower, register int upper);
extern void  z_insort_inverse (register double complex * array, register int len);


#endif  // if LIBRARY else APPLCATION
//extern void  insort (register Mat * array, register int len);


#endif
