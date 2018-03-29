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
//#include <cblas.h>
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


#ifndef  AUTOMATIC

#if(HALF_PRECISION)
//#define LEAF 2000
#define LEAF 20
#endif
#if(SINGLE_PRECISION)
//#define LEAF 2000
#define LEAF 20
#endif
#if(DOUBLE_PRECISION)
#define LEAF 2000
//#define LEAF 2
#endif
#if(SINGLE_COMPLEX)
#define LEAF 1800
#endif
#if(DOUBLE_COMPLEX)
#define LEAF 1500
#endif

#endif


#if(LIBRARY_PACKAGE)

#if(HALF_PRECISION )
#define mul             h_mul            
#define madd            h_madd            
#define saddmul         h_saddmul        
#define smul            h_smul            
#define saddmulR         h_saddmulR        
#define smulR            h_smulR            
#define wmul            h_wmul           
#define waddmul         h_waddmul        
#define wm              h_wm             
#define wmadd           h_wmadd          
#define wmR             h_wmR             
#define wmaddR          h_wmaddR          
#define wmTR             h_wmTR             
#define wmaddTR          h_wmaddTR          
#define adaptive_smul   h_adaptive_smul  
#define omul            h_omul           
#define oaddmul         h_oaddmul        
#define owmul           h_owmul          
#define owaddmul        h_owaddmul       
#define bm              h_bm             
#define bmadd           h_bmadd          
#define ptaddmul        h_ptaddmul       
#define wmpipe          h_wmpipe         
#define wmaddpipe       h_wmaddpipe      
#define bmpipe          h_bmpipe         
#define bmaddpipe       h_bmaddpipe      
#define smpipe          h_smpipe         
#define smaddpipe       h_smaddpipe      
#define Rmul            h_Rmul           
#define rmul            h_rmul           
#define adaptive_wm     h_adaptive_wm           
#define mulpt           h_mulpt
#define BMOWR_PIPE      h_BMOWR_PIPE
#define BMOWR	  	h_BMOWR	  
#define BMOWRR	  	h_BMOWRR	  
#define BMADD_PIPE	h_BMADD_PIPE
#define BMADD     	h_BMADD     
#define BMADDR     	h_BMADDR     


#endif
#if(SINGLE_PRECISION )
#define mul             s_mul            
#define madd            s_madd            
#define saddmul         s_saddmul        
#define smul            s_smul            
#define saddmulR         s_saddmulR        
#define smulR            s_smulR            
#define wmul            s_wmul           
#define waddmul         s_waddmul        
#define wm              s_wm             
#define wmadd           s_wmadd          
#define wmR             s_wmR             
#define wmaddR          s_wmaddR          
#define wmTR             s_wmTR             
#define wmaddTR          s_wmaddTR          
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
#define BMOWRR	  	s_BMOWRR	  
#define BMADD_PIPE	s_BMADD_PIPE
#define BMADD     	s_BMADD     
#define BMADDR     	s_BMADDR     


#endif
#if(DOUBLE_PRECISION )
#define mul             d_mul            
#define madd            d_madd            
#define saddmul         d_saddmul        
#define smul            d_smul            
#define saddmulR         d_saddmulR        
#define smulR            d_smulR            
#define wmul            d_wmul           
#define waddmul         d_waddmul        
#define wm              d_wm             
#define wmadd           d_wmadd          
#define wmR              d_wmR             
#define wmaddR           d_wmaddR          
#define wmTR             d_wmTR             
#define wmaddTR          d_wmaddTR          
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
#define BMOWRR	  	d_BMOWRR	  
#define BMADD_PIPE	d_BMADD_PIPE
#define BMADD     	d_BMADD     
#define BMADDR     	d_BMADDR     

#endif
#if(SINGLE_COMPLEX )
#define mul             c_mul            
#define madd            c_madd            
#define saddmul         c_saddmul        
#define smul            c_smul            
#define saddmulR         c_saddmulR        
#define smulR            c_smulR            
#define wmul            c_wmul           
#define waddmul         c_waddmul        
#define wm              c_wm             
#define wmadd           c_wmadd          
#define wmR              c_wmR             
#define wmaddR           c_wmaddR          
#define wmTR             c_wmTR             
#define wmaddTR          c_wmaddTR          
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
#define BMOWRR	  	c_BMOWRR	  
#define BMADD_PIPE	c_BMADD_PIPE
#define BMADD     	c_BMADD     
#define BMADDR     	c_BMADDR     
           
#endif
#if(DOUBLE_COMPLEX )
#define mul             z_mul            
#define madd            z_madd            
#define saddmul         z_saddmul        
#define smul            z_smul            
#define saddmulR         z_saddmulR        
#define smulR            z_smulR            
#define wmul            z_wmul           
#define waddmul         z_waddmul        
#define wm              z_wm             
#define wmadd           z_wmadd          
#define wmR              z_wmR             
#define wmaddR           z_wmaddR          
#define wmTR             z_wmTR             
#define wmaddTR          z_wmaddTR          
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
#define BMOWRR	  	z_BMOWRR	  
#define BMADD_PIPE	z_BMADD_PIPE
#define BMADD     	z_BMADD     
#define BMADDR     	z_BMADDR     
           
#endif


#ifndef MODULO_MAT_MUL

int mul            (DEF(c), DEF(a), DEF(b));
int mulpt          (DEF(c), DEF(a), DEF(b));
int madd           (DEF(c), DEF(a), DEF(b));
int  saddmul        (DEF(c), DEF(a), DEF(b));
int  smul           (DEF(c), DEF(a), DEF(b));
int  saddmulR        (DEF(c), DEF(a), DEF(b));
int  smulR           (DEF(c), DEF(a), DEF(b));
int  wmul           (DEF(c), DEF(a), DEF(b));
int  waddmul        (DEF(c), DEF(a), DEF(b));
int  wm             (DEF(c), DEF(a), DEF(b));
int  wmadd          (DEF(c), DEF(a), DEF(b));
int  wmR             (DEF(c), DEF(a), DEF(b));
int  wmaddR          (DEF(c), DEF(a), DEF(b));
int  wmTR             (DEF(c), DEF(a), DEF(b));
int  wmaddTR          (DEF(c), DEF(a), DEF(b));
int  adaptive_smul  (DEF(c), DEF(a), DEF(b), int leaf);
int omul           (DEF(c), DEF(a), DEF(b));
int oaddmul        (DEF(c), DEF(a), DEF(b));
int owmul          (DEF(c), DEF(a), DEF(b));
int owaddmul       (DEF(c), DEF(a), DEF(b));
int  bm             (DEF(c), DEF(a), DEF(b));
int  bmadd          (DEF(c), DEF(a), DEF(b));
int ptaddmul       (DEF(c), DEF(a), DEF(b));
int  wmpipe         (DEF(c), DEF(a), DEF(b),TAddOperands *args); 
int  wmaddpipe      (DEF(c), DEF(a), DEF(b),TAddOperands *args);
int  bmpipe         (DEF(c), DEF(a), DEF(b),TAddOperands *args); 
int  bmaddpipe      (DEF(c), DEF(a), DEF(b),TAddOperands *args);
int  smpipe         (DEF(c), DEF(a), DEF(b),TAddOperands *args); 
int  smaddpipe      (DEF(c), DEF(a), DEF(b),TAddOperands *args);
int  Rmul           (DEF(c), DEF(a), DEF(b));
int  adaptive_wm    (DEF(c), DEF(a), DEF(b), int alpha_pi);
int mulpt          (DEF(c), DEF(a), DEF(b));
int BMADD_PIPE(DEF(c), DEF(a), DEF(b),TAddOperands *args);
int BMADD(DEF(c), DEF(a), DEF(b));
int BMADDR(DEF(c), DEF(a), DEF(b));
int BMOWR_PIPE(DEF(c), DEF(a), DEF(b),TAddOperands *args);
int BMOWR(DEF(c), DEF(a), DEF(b));
int BMOWRR(DEF(c), DEF(a), DEF(b));


#endif

#elif(APPLICATION)

int h_mul            (DEF_H(c), DEF_H(a), DEF_H(b));
int h_mulpt          (DEF_H(c), DEF_H(a), DEF_H(b));
int h_madd           (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_saddmul        (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_smul           (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_saddmulR        (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_smulR           (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_wmul           (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_waddmul        (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_wm             (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_wmadd          (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_wmR             (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_wmaddR          (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_wmTR             (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_wmaddTR          (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_adaptive_smul  (DEF_H(c), DEF_H(a), DEF_H(b), int leaf);
int h_omul           (DEF_H(c), DEF_H(a), DEF_H(b));
int h_oaddmul        (DEF_H(c), DEF_H(a), DEF_H(b));
int h_owmul          (DEF_H(c), DEF_H(a), DEF_H(b));
int h_owaddmul       (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_bm             (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_bmadd          (DEF_H(c), DEF_H(a), DEF_H(b));
int h_ptaddmul       (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_wmpipe         (DEF_H(c), DEF_H(a), DEF_H(b),TAddOperands *args); 
int  h_wmaddpipe      (DEF_H(c), DEF_H(a), DEF_H(b),TAddOperands *args);
int  h_bmpipe         (DEF_H(c), DEF_H(a), DEF_H(b),TAddOperands *args); 
int  h_bmaddpipe      (DEF_H(c), DEF_H(a), DEF_H(b),TAddOperands *args);
int  h_smpipe         (DEF_H(c), DEF_H(a), DEF_H(b),TAddOperands *args); 
int  h_smaddpipe      (DEF_H(c), DEF_H(a), DEF_H(b),TAddOperands *args);
int  h_Rmul           (DEF_H(c), DEF_H(a), DEF_H(b));
//int  h_rmul           (DEF_H(c), DEF_H(a), DEF_H(b), H_MatrixComputations leaf);
int  h_adaptive_wm    (DEF_H(c), DEF_H(a), DEF_H(b), int alpha_pi);
int h_mulpt          (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_BMADD_PIPE     (DEF_H(c), DEF_H(a), DEF_H(b),TAddOperands *args);
int  h_BMADD          (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_BMADDR          (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_BMOWR_PIPE     (DEF_H(c), DEF_H(a), DEF_H(b),TAddOperands *args);
int  h_BMOWR          (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_BMOWRR         (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_gpuGEMM        (DEF_H(c), DEF_H(a), DEF_H(b));
int  h_fpgaGEMM        (DEF_H(c), DEF_H(a), DEF_H(b));



int s_mul            (DEF_S(c), DEF_S(a), DEF_S(b));
int s_mulpt          (DEF_S(c), DEF_S(a), DEF_S(b));
int s_madd           (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_saddmul        (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_smul           (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_saddmulR        (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_smulR           (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmul           (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_waddmul        (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wm             (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmadd          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmR             (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmaddR          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmTR             (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmaddTR          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_adaptive_smul  (DEF_S(c), DEF_S(a), DEF_S(b), int leaf);
int s_omul           (DEF_S(c), DEF_S(a), DEF_S(b));
int s_oaddmul        (DEF_S(c), DEF_S(a), DEF_S(b));
int s_owmul          (DEF_S(c), DEF_S(a), DEF_S(b));
int s_owaddmul       (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_bm             (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_bmadd          (DEF_S(c), DEF_S(a), DEF_S(b));
int s_ptaddmul       (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_wmpipe         (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args); 
int  s_wmaddpipe      (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_bmpipe         (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args); 
int  s_bmaddpipe      (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_smpipe         (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args); 
int  s_smaddpipe      (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_Rmul           (DEF_S(c), DEF_S(a), DEF_S(b));
//int  s_rmul           (DEF_S(c), DEF_S(a), DEF_S(b), S_MatrixComputations leaf);
int  s_adaptive_wm    (DEF_S(c), DEF_S(a), DEF_S(b), int alpha_pi);
int s_mulpt          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_BMADD_PIPE     (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_BMADD          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_BMADDR          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_BMOWR_PIPE     (DEF_S(c), DEF_S(a), DEF_S(b),TAddOperands *args);
int  s_BMOWR          (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_BMOWRR         (DEF_S(c), DEF_S(a), DEF_S(b));
int  s_gpuGEMM        (DEF_S(c), DEF_S(a), DEF_S(b));


int d_mul            (DEF_D(c), DEF_D(a), DEF_D(b));
int d_mulpt          (DEF_D(c), DEF_D(a), DEF_D(b));
int d_madd           (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_saddmul        (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_smul           (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_saddmulR        (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_smulR           (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmul           (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_waddmul        (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wm             (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmadd          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmR             (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmaddR          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmTR             (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmaddTR          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_adaptive_smul  (DEF_D(c), DEF_D(a), DEF_D(b), int leaf);
int d_omul           (DEF_D(c), DEF_D(a), DEF_D(b));
int d_oaddmul        (DEF_D(c), DEF_D(a), DEF_D(b));
int d_owmul          (DEF_D(c), DEF_D(a), DEF_D(b));
int d_owaddmul       (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_bm             (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_bmadd          (DEF_D(c), DEF_D(a), DEF_D(b));
int d_ptaddmul       (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_wmpipe         (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args); 
int  d_wmaddpipe      (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_bmpipe         (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args); 
int  d_bmaddpipe      (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_smpipe         (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args); 
int  d_smaddpipe      (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_Rmul           (DEF_D(c), DEF_D(a), DEF_D(b));
//int  d_rmul           (DEF_D(c), DEF_D(a), DEF_D(b), D_MatrixComputations leaf);
int  d_adaptive_wm    (DEF_D(c), DEF_D(a), DEF_D(b), int alpha_pi);
int d_mulpt          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_BMADD_PIPE     (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_BMADD          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_BMADDR          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_BMOWR_PIPE     (DEF_D(c), DEF_D(a), DEF_D(b),TAddOperands *args);
int  d_BMOWR          (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_BMOWRR         (DEF_D(c), DEF_D(a), DEF_D(b));
int  d_gpuGEMM       (DEF_D(c), DEF_D(a), DEF_D(b));


int c_mul            (DEF_C(c), DEF_C(a), DEF_C(b));
int c_mulpt          (DEF_C(c), DEF_C(a), DEF_C(b));
int c_madd           (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_saddmul        (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_smul           (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_saddmulR        (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_smulR           (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmul           (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_waddmul        (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wm             (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmadd          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmR             (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmaddR          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmTR             (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmaddTR          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_adaptive_smul  (DEF_C(c), DEF_C(a), DEF_C(b), int leaf);
int c_omul           (DEF_C(c), DEF_C(a), DEF_C(b));
int c_oaddmul        (DEF_C(c), DEF_C(a), DEF_C(b));
int c_owmul          (DEF_C(c), DEF_C(a), DEF_C(b));
int c_owaddmul       (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_bm             (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_bmadd          (DEF_C(c), DEF_C(a), DEF_C(b));
int c_ptaddmul       (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_wmpipe         (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args); 
int  c_wmaddpipe      (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_bmpipe         (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args); 
int  c_bmaddpipe      (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_smpipe         (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args); 
int  c_smaddpipe      (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_Rmul           (DEF_C(c), DEF_C(a), DEF_C(b));
//int  c_rmul           (DEF_C(c), DEF_C(a), DEF_C(b), C_MatrixComputations leaf);
int  c_adaptive_wm    (DEF_C(c), DEF_C(a), DEF_C(b), int alpha_pi);
int c_mulpt            (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_BMADD_PIPE     (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_BMADD          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_BMADDR          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_BMOWR_PIPE     (DEF_C(c), DEF_C(a), DEF_C(b),TAddOperands *args);
int  c_BMOWR          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_BMOWRR          (DEF_C(c), DEF_C(a), DEF_C(b));
int  c_gpuGEMM       (DEF_C(c), DEF_C(a), DEF_C(b));


int z_mul            (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int z_mulpt          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int z_madd           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_saddmul        (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_smul           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_saddmulR        (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_smulR           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmul           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_waddmul        (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wm             (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmadd          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmR             (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmaddR          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmTR             (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmaddTR          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_adaptive_smul  (DEF_Z(c), DEF_Z(a), DEF_Z(b), int leaf);
int z_omul           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int z_oaddmul        (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int z_owmul          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int z_owaddmul       (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_bm             (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_bmadd          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int z_ptaddmul       (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_wmpipe         (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args); 
int  z_wmaddpipe      (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_bmpipe         (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args); 
int  z_bmaddpipe      (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_smpipe         (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args); 
int  z_smaddpipe      (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_Rmul           (DEF_Z(c), DEF_Z(a), DEF_Z(b));
//int  z_rmul           (DEF_Z(c), DEF_Z(a), DEF_Z(b), Z_MatrixComputations leaf);
int  z_adaptive_wm    (DEF_Z(c), DEF_Z(a), DEF_Z(b), int alpha_pi);
int z_mulpt          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_BMADD_PIPE     (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_BMADD          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_BMADDR          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_BMOWR_PIPE     (DEF_Z(c), DEF_Z(a), DEF_Z(b),TAddOperands *args);
int  z_BMOWR          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_BMOWRR          (DEF_Z(c), DEF_Z(a), DEF_Z(b));
int  z_gpuGEMM       (DEF_Z(c), DEF_Z(a), DEF_Z(b));		       
#endif // if  LIBRARY else APPLICATION
#endif // MODULE 
