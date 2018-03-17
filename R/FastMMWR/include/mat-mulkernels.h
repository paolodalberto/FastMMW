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
/*******************************************************************************
 *
 *  Paolo D'Alberto
 *  Feb 20 2006 
 *  
 *
 *
 *
 */

#ifndef MATRIXEXTRA
#define MATRIXEXTRA

#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>
#include <mat-operands.h>
#include <pt.h>
#include <doubly_compensated_sumc.h>

/**********************************8
 * Matrix Type Definition
 *
 */


#define CMC(X, equal, Y, FUNCTION, Z)    FUNCTION(X,Y,Z)

// 3M multiplication algorithm
#define MM3_PIPE(c1,c2,a1,a2,b1,b2,t1,t2, MM, MADD, MA, MA_t) {		\
    TAddOperands *argslocal = (TAddOperands *) calloc(3,sizeof(TAddOperands)); \
    argslocal[0].m = add_amd; argslocal[0].c = t1; argslocal[0].a = a1; argslocal[0].b = a2; \
    argslocal[1].m = add_amd; argslocal[1].c = t2; argslocal[1].a = b1; argslocal[1].b = b2; \
    MM(c1, a1, b1, argslocal);						\
    MM(c2, a2, b2, 0);							\
    MA(c2, c2, c1);							\
    c2.beta *= -1;							\
    c1.beta *=2;							\
    MA_t(c1, c1, c2);							\
    c1.beta = 1;							\
    /*MA(t1, a1,  a2);	*/						\
    /*MA(t2, b1,  b2);	*/						\
    MADD(c2, t1,  t2,0);						\
    free(argslocal);							\
  }

#define MM3(c1,c2,a1,a2,b1,b2,t1,t2, MM, MADD, MA, MA_t) 	\
  { 								\
    CMC(c1, =, a1, MM, b1);					\
    CMC(c2, =, a2, MM, b2);					\
    CMC(c2, =,  c2, MA, c1);					\
    c2.beta *= -1;						\
    c1.beta *=2;						\
    CMC(c1, =, c1, MA_t, c2);					\
    c1.beta = 1;						\
    CMC(t1, =, a1, MA, a2);					\
    CMC(t2, =, b1, MA, b2);					\
    CMC(c2, =, t1, MADD, t2);					\
    c2.beta =1;							\
    c1.beta =1; }   







					 
#ifdef GETTIME
#include <sys/time.h>
struct timeval _t1,_t2;
double duration;

#define START_CLOCK   gettimeofday(&_t1,NULL ); 
#define END_CLOCK   gettimeofday(&_t2,NULL);   duration = (_t2.tv_sec-_t1.tv_sec)+ (double)(_t2.tv_usec-_t1.tv_usec)/1000000;    printf("----------> get time %e sec<------\n",duration); 
#endif /*  GETTIME */


#ifdef CLOCK
#include <time.h>
clock_t _t1,_t2;
double duration;

#define START_CLOCK   _t1 = clock(); 
#define END_CLOCK     _t2 = clock(); duration =  ((double)(_t2-_t1))/CLOCKS_PER_SEC; \
  printf("clock time %e s \n", duration); 
#endif

#define TEMP temp,  cM, cN, cM, cN
#define INTERVAL (45)   /* two minutes */


/************************************************
 * This is a timing procedure very common in CMU
 * Notice that we execute X once before we start timing.
 *
 */
 
#define TIMING(X,time, interval) { int i,j;	\
    j=1;					\
    X;						\
    do {					\
      j*=2;					\
      START_CLOCK;				\
      for (i=0;i<j;i++) { X;  }			\
      END_CLOCK;				\
      time = duration/j;			\
      printf(" average %f\n",time);		\
    } while (duration<interval);		\
  }
#define TIMING_ITER(X,time, interval,times) { int i,j;	\
    j=1;					\
    X;						\
    do {					\
      j*=2;					\
      START_CLOCK;				\
      for (i=0;i<j;i++) { X;  }			\
      END_CLOCK;				\
      time = duration/j;			\
      printf(" average %f times %d \n",time,j);		\
    } while (duration <interval || j<times);		\
  }

#define TIMING_COLD(X,time, interval) {		\
    START_CLOCK;				\
    X;						\
    END_CLOCK;					\
    time = duration;				\
    printf(" average %f\n",time);		\
  }


#define BR_LEFT(am,an,bn,L)  (HH(bn)*HH(an))
#define BR_RIGHT(am,an,bn,L) (((L)/2)*(5*(HH(an))*(1+(HH(bn))/(HL(am))) + 6*(bn)))
#define BR_P(am, an, bn, L)  ((BR_LEFT(am,an,bn,L))< (BR_RIGHT(am,an,bn,L)))
#define L_VALUE(am, an, bn, L)  (2*(5*(HH(an))*(1+(HH(bn))/(HL(am))) + 6*(bn)))/(HH(bn)*HH(an))


//#define ERROR
#ifndef  ERROR
 
#if(SINGLE_PRECISION)
#define LEAF 3900
//#define LEAF 32

#endif
#if(DOUBLE_PRECISION)
#define LEAF 2000
#endif
#if(SINGLE_COMPLEX)
#define LEAF 1800
#endif
#if(DOUBLE_COMPLEX)
#define LEAF 1500
#endif
#else
#define LEAF 32

#endif


#if(LIBRARY_PACKAGE)

#if(SINGLE_PRECISION )
#define mul             s_mul            
#define madd            s_madd            
#define saddmul         s_saddmul        
#define smul            s_smul            
#define wmul            s_wmul           
#define waddmul         s_waddmul        
#define wm              s_wm             
#define wmadd           s_wmadd          
#define smul_time_time_ s_smul_time_time_
#define adaptive_smul   s_adaptive_smul  
#define omul            s_omul           
#define oaddmul         s_oaddmul        
#define owmul           s_owmul          
#define owaddmul        s_owaddmul       
#define bm              s_bm             
#define bmadd           s_bmadd          
#define ptaddmul        s_ptaddmul       
#define wmpipe          s_wmpipe         
#define wmaddpipe       s_wmaddpipe      
#define bmpipe          s_bmpipe         
#define bmaddpipe       s_bmaddpipe      
#define smpipe          s_smpipe         
#define smaddpipe       s_smaddpipe      
#define Rmul            s_Rmul           
#define rmul            s_rmul           
#define adaptive_wm     s_adaptive_wm           
#define mulpt           s_mulpt
#define BMOWR_PIPE      s_BMOWR_PIPE
#define BMOWR	  	s_BMOWR	  
#define BMADD_PIPE	s_BMADD_PIPE
#define BMADD     	s_BMADD     


#endif
#if(DOUBLE_PRECISION )
#define mul             d_mul            
#define madd            d_madd            
#define saddmul         d_saddmul        
#define smul            d_smul            
#define wmul            d_wmul           
#define waddmul         d_waddmul        
#define wm              d_wm             
#define wmadd           d_wmadd          
#define smul_time_time_ d_smul_time_time_
#define adaptive_smul   d_adaptive_smul  
#define omul            d_omul           
#define oaddmul         d_oaddmul        
#define owmul           d_owmul          
#define owaddmul        d_owaddmul       
#define bm              d_bm             
#define bmadd           d_bmadd          
#define ptaddmul        d_ptaddmul       
#define wmpipe          d_wmpipe         
#define wmaddpipe       d_wmaddpipe      
#define bmpipe          d_bmpipe         
#define bmaddpipe       d_bmaddpipe      
#define smpipe          d_smpipe         
#define smaddpipe       d_smaddpipe      
#define Rmul            d_Rmul           
#define rmul            d_rmul           
#define adaptive_wm     d_adaptive_wm           
#define mulpt           d_mulpt
#define BMOWR_PIPE      d_BMOWR_PIPE
#define BMOWR	  	d_BMOWR	  
#define BMADD_PIPE	d_BMADD_PIPE
#define BMADD     	d_BMADD     

#endif
#if(SINGLE_COMPLEX )
#define mul             c_mul            
#define madd            c_madd            
#define saddmul         c_saddmul        
#define smul            c_smul            
#define wmul            c_wmul           
#define waddmul         c_waddmul        
#define wm              c_wm             
#define wmadd           c_wmadd          
#define smul_time_time_ c_smul_time_time_
#define adaptive_smul   c_adaptive_smul  
#define omul            c_omul           
#define oaddmul         c_oaddmul        
#define owmul           c_owmul          
#define owaddmul        c_owaddmul       
#define bm              c_bm             
#define bmadd           c_bmadd          
#define ptaddmul        c_ptaddmul       
#define wmpipe          c_wmpipe         
#define wmaddpipe       c_wmaddpipe      
#define bmpipe          c_bmpipe         
#define bmaddpipe       c_bmaddpipe      
#define smpipe          c_smpipe         
#define smaddpipe       c_smaddpipe      
#define Rmul            c_Rmul           
#define rmul            c_rmul           
#define adaptive_wm     c_adaptive_wm           
#define mulpt           c_mulpt
#define BMOWR_PIPE      c_BMOWR_PIPE
#define BMOWR	  	c_BMOWR	  
#define BMADD_PIPE	c_BMADD_PIPE
#define BMADD     	c_BMADD     
           
#endif
#if(DOUBLE_COMPLEX )
#define mul             z_mul            
#define madd            z_madd            
#define saddmul         z_saddmul        
#define smul            z_smul            
#define wmul            z_wmul           
#define waddmul         z_waddmul        
#define wm              z_wm             
#define wmadd           z_wmadd          
#define smul_time_time_ z_smul_time_time_
#define adaptive_smul   z_adaptive_smul  
#define omul            z_omul           
#define oaddmul         z_oaddmul        
#define owmul           z_owmul          
#define owaddmul        z_owaddmul       
#define bm              z_bm             
#define bmadd           z_bmadd          
#define ptaddmul        z_ptaddmul       
#define wmpipe          z_wmpipe         
#define wmaddpipe       z_wmaddpipe      
#define bmpipe          z_bmpipe         
#define bmaddpipe       z_bmaddpipe      
#define smpipe          z_smpipe         
#define smaddpipe       z_smaddpipe      
#define Rmul            z_Rmul
#define rmul            z_rmul           
#define adaptive_wm     z_adaptive_wm           
#define mulpt           z_mulpt
#define BMOWR_PIPE      z_BMOWR_PIPE
#define BMOWR	  	z_BMOWR	  
#define BMADD_PIPE	z_BMADD_PIPE
#define BMADD     	z_BMADD     
           
#endif


#ifndef MODULO_MAT_MUL

void mul            (DEF(c), DEF(a), DEF(b));
void mulpt          (DEF(c), DEF(a), DEF(b));
void madd           (DEF(c), DEF(a), DEF(b));
int  saddmul        (DEF(c), DEF(a), DEF(b));
int  smul           (DEF(c), DEF(a), DEF(b));
int  wmul           (DEF(c), DEF(a), DEF(b));
int  waddmul        (DEF(c), DEF(a), DEF(b));
int  wm             (DEF(c), DEF(a), DEF(b));
int  wmadd          (DEF(c), DEF(a), DEF(b));
int  smul_time_time_(DEF(c), DEF(a), DEF(b));
int  adaptive_smul  (DEF(c), DEF(a), DEF(b), int leaf);
void omul           (DEF(c), DEF(a), DEF(b));
void oaddmul        (DEF(c), DEF(a), DEF(b));
void owmul          (DEF(c), DEF(a), DEF(b));
void owaddmul       (DEF(c), DEF(a), DEF(b));
int  bm             (DEF(c), DEF(a), DEF(b));
int  bmadd          (DEF(c), DEF(a), DEF(b));
void ptaddmul       (DEF(c), DEF(a), DEF(b));
int  wmpipe         (DEF(c), DEF(a), DEF(b),TAddOperands *args); 
int  wmaddpipe      (DEF(c), DEF(a), DEF(b),TAddOperands *args);
int  bmpipe         (DEF(c), DEF(a), DEF(b),TAddOperands *args); 
int  bmaddpipe      (DEF(c), DEF(a), DEF(b),TAddOperands *args);
int  smpipe         (DEF(c), DEF(a), DEF(b),TAddOperands *args); 
int  smaddpipe      (DEF(c), DEF(a), DEF(b),TAddOperands *args);
int  Rmul           (DEF(c), DEF(a), DEF(b));
int  adaptive_wm    (DEF(c), DEF(a), DEF(b), int alpha_pi);
void mulpt          (DEF(c), DEF(a), DEF(b));
int BMADD_PIPE(DEF(c), DEF(a), DEF(b),TAddOperands *args);
int BMADD(DEF(c), DEF(a), DEF(b));
int BMOWR_PIPE(DEF(c), DEF(a), DEF(b),TAddOperands *args);
int BMOWR(DEF(c), DEF(a), DEF(b));


#endif

#elif(APPLICATION)

void s_mul            (DEF_S(c), DEF_S(a), DEF_S(b));
void s_mulpt          (DEF_S(c), DEF_S(a), DEF_S(b));
void s_madd           (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_saddmul        (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_smul           (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmul           (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_waddmul        (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wm             (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmadd          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_smul_time_time_(DEF_S(c), DEF_S(a), DEF_S(b));
int  s_adaptive_smul  (DEF_S(c), DEF_S(a), DEF_S(b), int leaf);
void s_omul           (DEF_S(c), DEF_S(a), DEF_S(b));
void s_oaddmul        (DEF_S(c), DEF_S(a), DEF_S(b));
void s_owmul          (DEF_S(c), DEF_S(a), DEF_S(b));
void s_owaddmul       (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_bm             (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_bmadd          (DEF_S(c), DEF_S(a), DEF_S(b));
void s_ptaddmul       (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmpipe         (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args); 
int  s_wmaddpipe      (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_bmpipe         (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args); 
int  s_bmaddpipe      (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_smpipe         (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args); 
int  s_smaddpipe      (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_Rmul           (DEF_S(c), DEF_S(a), DEF_S(b));
//int  s_rmul           (DEF_S(c), DEF_S(a), DEF_S(b), S_MatrixComputations leaf);
int  s_adaptive_wm    (DEF_S(c), DEF_S(a), DEF_S(b), int alpha_pi);
void s_mulpt          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_BMADD_PIPE     (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_BMADD          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_BMOWR_PIPE     (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_BMOWR          (DEF_S(c), DEF_S(a), DEF_S(b));



void d_mul            (DEF_D(c), DEF_D(a), DEF_D(b));
void d_mulpt          (DEF_D(c), DEF_D(a), DEF_D(b));
void d_madd           (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_saddmul        (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_smul           (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmul           (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_waddmul        (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wm             (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmadd          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_smul_time_time_(DEF_D(c), DEF_D(a), DEF_D(b));
int  d_adaptive_smul  (DEF_D(c), DEF_D(a), DEF_D(b), int leaf);
void d_omul           (DEF_D(c), DEF_D(a), DEF_D(b));
void d_oaddmul        (DEF_D(c), DEF_D(a), DEF_D(b));
void d_owmul          (DEF_D(c), DEF_D(a), DEF_D(b));
void d_owaddmul       (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_bm             (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_bmadd          (DEF_D(c), DEF_D(a), DEF_D(b));
void d_ptaddmul       (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmpipe         (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args); 
int  d_wmaddpipe      (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_bmpipe         (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args); 
int  d_bmaddpipe      (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_smpipe         (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args); 
int  d_smaddpipe      (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_Rmul           (DEF_D(c), DEF_D(a), DEF_D(b));
//int  d_rmul           (DEF_D(c), DEF_D(a), DEF_D(b), D_MatrixComputations leaf);
int  d_adaptive_wm    (DEF_D(c), DEF_D(a), DEF_D(b), int alpha_pi);
void d_mulpt          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_BMADD_PIPE     (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_BMADD          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_BMOWR_PIPE     (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_BMOWR          (DEF_D(c), DEF_D(a), DEF_D(b));

void c_mul            (DEF_C(c), DEF_C(a), DEF_C(b));
void c_mulpt          (DEF_C(c), DEF_C(a), DEF_C(b));
void c_madd           (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_saddmul        (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_smul           (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmul           (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_waddmul        (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wm             (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmadd          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_smul_time_time_(DEF_C(c), DEF_C(a), DEF_C(b));
int  c_adaptive_smul  (DEF_C(c), DEF_C(a), DEF_C(b), int leaf);
void c_omul           (DEF_C(c), DEF_C(a), DEF_C(b));
void c_oaddmul        (DEF_C(c), DEF_C(a), DEF_C(b));
void c_owmul          (DEF_C(c), DEF_C(a), DEF_C(b));
void c_owaddmul       (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_bm             (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_bmadd          (DEF_C(c), DEF_C(a), DEF_C(b));
void c_ptaddmul       (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmpipe         (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args); 
int  c_wmaddpipe      (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_bmpipe         (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args); 
int  c_bmaddpipe      (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_smpipe         (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args); 
int  c_smaddpipe      (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_Rmul           (DEF_C(c), DEF_C(a), DEF_C(b));
//int  c_rmul           (DEF_C(c), DEF_C(a), DEF_C(b), C_MatrixComputations leaf);
int  c_adaptive_wm    (DEF_C(c), DEF_C(a), DEF_C(b), int alpha_pi);
void c_mulpt            (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_BMADD_PIPE     (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_BMADD          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_BMOWR_PIPE     (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_BMOWR          (DEF_C(c), DEF_C(a), DEF_C(b));

void z_mul            (DEF_Z(c), DEF_Z(a), DEF_Z(b));
void z_mulpt          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
void z_madd           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_saddmul        (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_smul           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmul           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_waddmul        (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wm             (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmadd          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_smul_time_time_(DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_adaptive_smul  (DEF_Z(c), DEF_Z(a), DEF_Z(b), int leaf);
void z_omul           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
void z_oaddmul        (DEF_Z(c), DEF_Z(a), DEF_Z(b));
void z_owmul          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
void z_owaddmul       (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_bm             (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_bmadd          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
void z_ptaddmul       (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmpipe         (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args); 
int  z_wmaddpipe      (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_bmpipe         (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args); 
int  z_bmaddpipe      (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_smpipe         (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args); 
int  z_smaddpipe      (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_Rmul           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
//int  z_rmul           (DEF_Z(c), DEF_Z(a), DEF_Z(b), Z_MatrixComputations leaf);
int  z_adaptive_wm    (DEF_Z(c), DEF_Z(a), DEF_Z(b), int alpha_pi);
void z_mulpt          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_BMADD_PIPE     (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_BMADD          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_BMOWR_PIPE     (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_BMOWR          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
		       
#endif // if  LIBRARY else APPLICATION
#endif // MODULE 
