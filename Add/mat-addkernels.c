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

#define MAT_ADD_MODULE 	 1
#include <mat-operands.h>
#include <mat-addkernels.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <pt.h>
#include <math.h>

// Global matrix sizes

static int debug=0;



#define ASSIGNC(X,a,b) {			\
    X = (a)+  (b)*I;				\
  }						
 


void randomInitialization(DEF(a), int seed1, int seed2) { 
  int i,j;
  
#ifdef ROW_MAJOR
  for (i=0;i<a.M;i++)
    for (j=0;j<a.N;j++) 
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      a.data[i*a.N+j] = (((rand()+i+j)&1)?1:-1)*(rand()*seed1*(i+1)*(j+1)*11+i*7*seed2-j+3)%11;
#else
  ASSIGNC(a.data[i*a.N+j],
	  (((rand()+i+j)&1)?1:-1)*((seed1*rand()*(i+1)*(j+1)*11+i*7-j+3)%11),
	  (((rand()+i+j)&1)?1:-1)*((rand()*(i+1)*(j+1)*11*seed2+i*7-j+3)%11));
#endif
#else
  // Column Major
  for (i=0;i<a.N;i++)
    for (j=0;j<a.M;j++) 
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      a.data[i*a.M+j] = (((rand()+i+j)&1)?1:-1)*((rand()*seed1*(i+1)*(j+1)*11+i*7*seed2-j+3)%11);
#else
  ASSIGNC(a.data[i*a.M+j],
	  (((rand()+i+j)&1)?1:-1)*((seed1*rand()*(i+1)*(j+1)*11+i*7-j+3)%11),
	  (((rand()+i+j)&1)?1:-1)*((rand()*(i+1)*(j+1)*11*seed2+i*7-j+3)%11));
#endif
#endif

}
  
#define RAND0 (((rand()%2)?1:-1)*drand48())
#define RAND1 (drand48())




void randomInitializationError(DEF(a), int k) { 
  int i,j;
  
#ifdef ROW_MAJOR
  for (i=0;i<a.M;i++)
    for (j=0;j<a.N;j++) 
#if(SINGLE_PRECISION)
      a.data[i*a.N+j] = (float)((k==1)?RAND1:RAND0); 
#elif(DOUBLE_PRECISION)
      a.data[i*a.N+j] = (k==1)?RAND1:RAND0; 
#elif(SINGLE_COMPLEX)
      ASSIGNC(a.data[i*a.N+j],
	      (float)((k==1)?RAND1:RAND0),
	      (float)((k==1)?RAND1:RAND0));
#else
      ASSIGNC(a.data[i*a.N+j],
	      ((k==1)?RAND1:RAND0),
	      ((k==1)?RAND1:RAND0));
#endif
#else
for (i=0;i<a.N;i++)
  for (j=0;j<a.M;j++)  
#if(SINGLE_PRECISION)
    a.data[i*a.M+j] = (float)(k==1)?RAND1:RAND0; 
#elif (DOUBLE_PRECISION)
    a.data[i*a.M+j] = (k==1)?RAND1:RAND0; 
#elif(SINGLE_COMPLEX)
    ASSIGNC(a.data[i*a.M+j],
	    (float)((k==1)?RAND1:RAND0),
	    (float)((k==1)?RAND1:RAND0));
#else
    ASSIGNC(a.data[i*a.M+j],
	    ((k==1)?RAND1:RAND0),
	    ((k==1)?RAND1:RAND0));
#endif
#endif
}    



// C = A
void  copy(DEF(c),DEF(a)) { 
  int i,j;
  int rows, cols;
  
  rows = min(c.m,a.m);
  cols = min(c.n,a.n);

  if (debug) printf("Copy Rows %d Cols %d\n", rows, cols); 
  
#ifdef ROW_MAJOR
  for (i=0;i<rows;i++)
    for (j=0;j<cols;j++) 
      c.data[i*c.N+j] = a.data[i*a.N+j];
#endif
#ifdef COLUMN_MAJOR
  for (j=0;j<cols;j++) 
    for (i=0;i<rows;i++)
      c.data[i+j*c.M] = a.data[i+j*a.M];
#endif


}


int copy_matrix(DEF(c),DEF(a),DEF(b)) { 

  if (a.data!=0) { 
    copy(USE(c),USE(a));
  }
  else if (b.data!=0)  { 
    copy(USE(c),USE(b));
  } 
  return 0;
}


#define DIFF(D, A,B) D = A-B
#define CABS(A) cabs(A)


// C != A 
int  comp(DEF(c),DEF(a)) { 
  int i,j;
  int diff;
  int rows, cols;
  int equal =0;
  Mat temp;
  rows = min(c.m,a.m);
  cols = min(c.n,a.n);
  debug=1;


  for (i=0;i<rows;i++) {
    for (j=0;j<cols;j++) { 
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      diff = (fabs(E_(c.data,i,j,c.M,c.N) - E_(a.data,i,j,a.M,a.N))>0)?1:0;
#else
      DIFF(temp,E_(c.data,i,j,c.M,c.N),E_(a.data,i,j,a.M,a.N));
      diff = (CABS(temp)>0)?1:0;
#endif

      if (diff) {
	equal++;
      }
      if (debug ) {
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
	printf("%d ",(int) (diff));
#else
	printf("(%d,%d) ",(int) creal(temp),(int)cimag(temp));
#endif
      }	    
    }
    
    if (debug)
      printf("\n");
    
  }
  debug=0;
  return equal;
}
 

// print 
void  print(DEF(c)) { 
  int i,j;
  
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  printf("b%1.3f-%dx%d-%c\n",(double)creal(c.beta),c.m,c.n,c.trans);
#else
  printf("b=%1.3f-%dx%d-%c\n",(double)c.beta,c.m,c.n,c.trans);
#endif
  if (c.m <= 20 && c.n <=20) {
  for (i=0;i<c.m;i++) {
  for (j=0;j<c.n;j++) { 
  
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  printf("(%e,%e)",
	 creal(E_(c.data,i,j,c.M,c.N)),
	 cimag(E_(c.data,i,j,c.M,c.N)));
#else
  printf("%d ", (int)E_(c.data,i,j,c.M,c.N));
#endif
  
  
  }
  printf("\n");
  }
  }
}


#ifdef ROW_MAJOR

int add_t(DEF(c), DEF(a), DEF(b)) { 
  
  int i,j,x,y;

  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
   
  //# pragma omp parallel for
  for (i=0; i<x; i++) {
    /* core of the computation */
    for (j=0;j<y;j++)  E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) + b.beta*E_(b.data,i,j,b.M,b.N);

    if (c.n>y)
      /* A is larger than B  or B is otherwise*/
      if (y<a.n)      for (;j<min(c.n,a.n);j++) E_(c.data,i,j,c.M,c.N) =  a.beta*E_(a.data,i,j,a.M,a.N) ; 
      else if (y<b.n) for (;j<min(c.n,b.n);j++) E_(c.data,i,j,c.M,c.N) =  b.beta*E_(b.data,i,j,b.M,b.N); /* B is larger than A */
  }
  
  if (c.m>x) {
    /* last rows */
    if (x<a.m)
      for (; i<min(c.m,a.m); i++) for (j=0;j<min(a.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N);
    
    else if (x<b.m)  
      for (; i<min(c.m,b.m); i++) for (j=0;j<min(b.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = b.beta*E_(b.data,i,j,b.M,b.N);
    
  }
  //   c.beta = 1;
  return 0;
}

int sub_t(DEF(c), DEF(a), DEF(b)) { 

  DEF(B);
  B = b;
  B.beta = - b.beta;
  return add_t(c,a,B);
}



int add(DEF(c), DEF(a), DEF(b)) { 
  
  int i,j,x,y;

  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
   
  //# pragma omp parallel for
  for (i=0; i<x; i++) {
    /* core of the computation */
    for (j=0;j<y;j++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) + E_(b.data,i,j,b.M,b.N);

    if (c.n>y)
      /* A is larger than B  or B is otherwise*/
      if (y<a.n)      for (;j<min(c.n,a.n);j++) E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) ; 
      else if (y<b.n) for (;j<min(c.n,b.n);j++) E_(c.data,i,j,c.M,c.N) = E_(b.data,i,j,b.M,b.N); /* B is larger than A */
  }
  
  if (c.m>x) {
    /* last rows */
    if (x<a.m)
      for (; i<min(c.m,a.m); i++) for (j=0;j<min(a.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N);
    
    else if (x<b.m)  
      for (; i<min(c.m,b.m); i++) for (j=0;j<min(b.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = E_(b.data,i,j,b.M,b.N);
    
  }
  //   c.beta = 1;
  return 0;
}
int sub(DEF(c), DEF(a), DEF(b)) { 
  
  int i,j,x,y;

  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
   
  //# pragma omp parallel for
  for (i=0; i<x; i++) {
    /* core of the computation */
    for (j=0;j<y;j++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) - E_(b.data,i,j,b.M,b.N);

    if (c.n>y)
      /* A is larger than B  or B is otherwise*/
      if (y<a.n)      for (;j<min(c.n,a.n);j++) E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) ; 
      else if (y<b.n) for (;j<min(c.n,b.n);j++) E_(c.data,i,j,c.M,c.N) = -E_(b.data,i,j,b.M,b.N); /* B is larger than A */
  }
  
  if (c.m>x) {
    /* last rows */
    if (x<a.m)
      for (; i<min(c.m,a.m); i++) for (j=0;j<min(a.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N);
    
    else if (x<b.m)  
      for (; i<min(c.m,b.m); i++) for (j=0;j<min(b.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = -E_(b.data,i,j,b.M,b.N);
    
  }
  //   c.beta = 1;
  return 0;
}



/*****************************************************************
 *
 * We will specialize this routine for cases such as A taller and
 * larger than B, because most of the time we know the size of the
 * operands before hand.
 */

int add_amd(DEF(c), DEF(a), DEF(b)) { 

  int i,j,x,y;
  DEFREGISTERS;

  if (debug) {printf(" add_amd operands size %d\n",sizeof(c.data));}
  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);

  //# pragma omp parallel for
  for (i=0; i<x; i++) {
    
    /* j=0 to y-2*UNROLL */
    UNROLLKERNEL(c,a,b,i,j,y,UNLOOPCOMPUTE);
    
    /* j=y(R) to  y */
    for (;j<y;j++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) + E_(b.data,i,j,b.M,b.N);
    if (c.n>y)
      /* A is larger than B  or B is otherwise*/
      if (y<a.n)      for (;j<min(c.n,a.n);j++) E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) ; 
      else if (y<b.n) for (;j<min(c.n,b.n);j++) E_(c.data,i,j,c.M,c.N) = E_(b.data,i,j,b.M,b.N); /* B is larger than A */
  }
  if (c.m>x) {
    /* last rows */
    if (x<a.m)
      for (; i<min(c.m,a.m); i++) for (j=0;j<min(a.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N);
    
    else if (x<b.m)  
      for (; i<min(c.m,b.m); i++) for (j=0;j<min(b.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = E_(b.data,i,j,b.M,b.N);
    
  }
  return 0;

}
int sub_amd(DEF(c), DEF(a), DEF(b)) { 
  
  int i,j,x,y;
  DEFREGISTERS;
  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
  
  //# pragma omp parallel for
  for (i=0; i<x; i++) {
    
    /* j=0 to y-2*UNROLL */
    UNROLLKERNEL(c,a,b,i,j,y,UNLOOPCOMPUTESUB);
    
    /* j=y(R) to  y */
    for (;j<y;j++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) - E_(b.data,i,j,b.M,b.N);
    if (c.n>y)
      /* A is larger than B  or B is otherwise*/
      if (y<a.n)      for (;j<min(c.n,a.n);j++) E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) ; 
      else if (y<b.n) for (;j<min(c.n,b.n);j++) E_(c.data,i,j,c.M,c.N) = -E_(b.data,i,j,b.M,b.N); /* B is larger than A */
  }
  if (c.m>x) {
    /* last rows */
    if (x<a.m)
      for (; i<min(c.m,a.m); i++) for (j=0;j<min(a.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N);
    
    else if (x<b.m)  
      for (; i<min(c.m,b.m); i++) for (j=0;j<min(b.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = -E_(b.data,i,j,b.M,b.N);
    
  }
  return 0;

}
int add_amd_t(DEF(c), DEF(a), DEF(b)) { 

  int i,j,x,y;
  DEFREGISTERS;
  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
  //# pragma omp parallel for
  for (i=0; i<x; i++) {
    
    /* j=0 to y-2*UNROLL */
    UNROLLKERNEL_t(c,a,b,i,j,y,UNLOOPCOMPUTE_t);
    
    /* j=y(R) to  y */
    for (;j<y;j++)  E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) + b.beta*E_(b.data,i,j,b.M,b.N);
    if (c.n>y)
      /* A is larger than B  or B is otherwise*/
      if (y<a.n)      for (;j<min(c.n,a.n);j++) E_(c.data,i,j,c.M,c.N) =  a.beta*E_(a.data,i,j,a.M,a.N) ; 
      else if (y<b.n) for (;j<min(c.n,b.n);j++) E_(c.data,i,j,c.M,c.N) =  b.beta*E_(b.data,i,j,b.M,b.N); /* B is larger than A */
  }
  
  if (c.m>x) {
    /* last rows */
    if (x<a.m)
      for (; i<min(c.m,a.m); i++) for (j=0;j<min(a.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N);
    
    else if (x<b.m)  
      for (; i<min(c.m,b.m); i++) for (j=0;j<min(b.n,c.n);j++)  E_(c.data,i,j,c.M,c.N) = b.beta*E_(b.data,i,j,b.M,b.N);
    
  }
  
  return 0;
     
}
int sub_amd_t(DEF(c), DEF(a), DEF(b)) { 
  
  DEF(B);
  B = b;
  B.beta = - b.beta;
  return add_amd_t(c,a,B);

}

#endif



#ifdef COLUMN_MAJOR

// C = A + B 
int add(DEF(c), DEF(a), DEF(b)) { 
  print("######### WANING  WRONG CODE \n");
  int i,j,x,y;

   /* minimum sizes */
   x = min(a.m,b.m); y = min(a.n,b.n);
   //# pragma omp parallel for
   /* core of the computation */
   for (j=0;j<y;j++) {
     for (i=0; i<x; i++) E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) + E_(b.data,i,j,b.M,b.N);

     if (c.m>x)
       /* last row */
       if (x<a.m)  {/* A is taller than B */
         E_(c.data,i,j,c.M,c.N)  = E_(a.data,i,j,a.M,a.N);
       }
       else if (x<b.m)  {/* B is taller than A */
	 E_(c.data,i,j,c.M,c.N) = E_(b.data,i,j,b.M,b.N);
       }
   }
   // last column
   if (c.n>y)
     if (y<a.n)	for (i=0;i<a.m;i++) E_(c.data,i,j,c.M,c.N) =  E_(a.data,i,j,a.M,a.N) ; /* A is larger than B */
     else if (y<b.n) for (i=0;i<b.m;i++) E_(c.data,i,j,c.M,c.N) = E_(b.data,i,j,b.M,b.N); /* B is larger than A */
   return 0;
}
// C = A - B 
int sub(DEF(c), DEF(a), DEF(b)) { 

  int i,j,x,y;

   /* minimum sizes */
   x = min(a.m,b.m); y = min(a.n,b.n);
   //# pragma omp parallel for
   for (j=0;j<y;j++) {
     for (i=0; i<x; i++) E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) - E_(b.data,i,j,b.M,b.N);
     
     /* last row */
     if (c.m>x)
       if (x<a.m)  {/* A is taller than B */
         E_(c.data,i,j,c.M,c.N)  = E_(a.data,i,j,a.M,a.N);
       }
       else if (x<b.m)  {/* B is taller than A */
	 E_(c.data,i,j,c.M,c.N) = - E_(b.data,i,j,b.M,b.N);
       }
   }
   // last column
   if (c.n>y)
     if (y<a.n)	for (i=0;i<a.m;i++) E_(c.data,i,j,c.M,c.N) =  E_(a.data,i,j,a.M,a.N) ; /* A is larger than B */
     else if (y<b.n) for (i=0;i<b.m;i++) E_(c.data,i,j,c.M,c.N) = - E_(b.data,i,j,b.M,b.N); /* B is larger than A */
   return 0;
}

// C = A + B 
int add_t(DEF(c), DEF(a), DEF(b)) { 

  int i,j,x,y;
  
   /* minimum sizes */
   x = min(a.m,b.m); y = min(a.n,b.n);
   //# pragma omp parallel for
   /* core of the computation */
   for (j=0;j<y;j++) {
     for (i=0; i<x; i++) E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) + b.beta*E_(b.data,i,j,b.M,b.N);
     
     /* last row */
     if (c.m>x)
       if (x<a.m)  {/* A is taller than B */
         E_(c.data,i,j,c.M,c.N)  = a.beta*E_(a.data,i,j,a.M,a.N);
       }
       else if (x<b.m)  {/* B is taller than A */
	 E_(c.data,i,j,c.M,c.N) = b.beta*E_(b.data,i,j,b.M,b.N);
       }
   }
   // last column
   if (c.n>y)
     if (y<a.n)	for (i=0;i<a.m;i++) E_(c.data,i,j,c.M,c.N) =  a.beta*E_(a.data,i,j,a.M,a.N) ; /* A is larger than B */
     else if (y<b.n) for (i=0;i<b.m;i++) E_(c.data,i,j,c.M,c.N) = b.beta*E_(b.data,i,j,b.M,b.N); /* B is larger than A */
   
   //c.beta = 1;
   return 0;
}
// C = A - B 
int sub_t(DEF(c), DEF(a), DEF(b)) { 

  int i,j,x,y;

   /* minimum sizes */
   x = min(a.m,b.m); y = min(a.n,b.n);
   //# pragma omp parallel for
   for (j=0;j<y;j++) {
     for (i=0; i<x; i++) E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) - b.beta*E_(b.data,i,j,b.M,b.N);
     
     if (c.m>x)
       /* last row */
       if (x<a.m)  {/* A is taller than B */
         E_(c.data,i,j,c.M,c.N)  = a.beta*E_(a.data,i,j,a.M,a.N);
       }
       else if (x<b.m)  {/* B is taller than A */
	 E_(c.data,i,j,c.M,c.N) = - b.beta*E_(b.data,i,j,b.M,b.N);
       }
   }
   // last column
   if (c.n>y)
     if (y<a.n)	for (i=0;i<a.m;i++) E_(c.data,i,j,c.M,c.N) =  a.beta*E_(a.data,i,j,a.M,a.N) ; /* A is larger than B */
     else if (y<b.n) for (i=0;i<b.m;i++) E_(c.data,i,j,c.M,c.N) = - b.beta*E_(b.data,i,j,b.M,b.N); /* B is larger than A */
 
   //c.beta = 1;
   return 0;
}


/*****************************************************************
 *
 * We will specialize this routine for cases such as A taller and
 * larger than B, because most of the time we know the size of the
 * operands before hand.
 */

int add_amd(DEF(c), DEF(a), DEF(b)) { 

  int i,j,x,y;
  DEFREGISTERS;
  

  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
  //# pragma omp parallel for
  for (j=0; j<y; j++) {
    
    /* j=0 to y-2*UNROLL */
    UNROLLKERNEL(c,a,b,i,j,y,UNLOOPCOMPUTE);
    
    /* j=y(R) to  y */
    for (;i<x;i++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) + E_(b.data,i,j,b.M,b.N);
    
    if (c.m>x)
      if (x<a.m)	 E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) ;   /* A is taller than B */
      else if (x<b.m) E_(c.data,i,j,c.M,c.N) =  E_(b.data,i,j,b.M,b.N);  /* B is taller than A */
  }
  /* last COLUMN */
  if (c.n>y)
    if (y<a.n)  /* A is larger than B */
      for (i=0;i<a.m;i++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N);
    else if (y<b.n)  /* B is larger than A */
      for (i=0;i<b.m;i++)   E_(c.data,i,j,c.M,c.N) =  E_(b.data,i,j,b.M,b.N); 
  
  
  return 0;
     
}
int sub_amd(DEF(c), DEF(a), DEF(b)) { 
  
  int i,j,x,y;
  DEFREGISTERS;
  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
  //# pragma omp parallel for
  for (j=0; j<y; j++) {
    
    UNROLLKERNEL(c,a,b,i,j,y,UNLOOPCOMPUTESUB);
        
    /* j=y(R) to  y */
    for (;i<x;i++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) - E_(b.data,i,j,b.M,b.N);
    
    if (c.m>x)
      if (x<a.m)	 E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N) ;   /* A is taller than B */
      else if (x<b.m) E_(c.data,i,j,c.M,c.N) =  - E_(b.data,i,j,b.M,b.N);  /* B is taller than A */
  }
  /* last COLUMN */

  if (c.n>y)
    if (y<a.n)  /* A is larger than B */
      for (i=0;i<a.m;i++)  E_(c.data,i,j,c.M,c.N) = E_(a.data,i,j,a.M,a.N);
    else if (y<b.n)  /* B is larger than A */
      for (i=0;i<b.m;i++)   E_(c.data,i,j,c.M,c.N) = - E_(b.data,i,j,b.M,b.N); 
  return 0;

}
int add_amd_t(DEF(c), DEF(a), DEF(b)) { 

  int i,j,x,y;
  DEFREGISTERS;


  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
  //# pragma omp parallel for
  for (j=0; j<y; j++) {
    
    /* j=0 to y-2*UNROLL */
    UNROLLKERNEL_t(c,a,b,i,j,y,UNLOOPCOMPUTE_t);
    
    /* j=y(R) to  y */
    for (;i<x;i++)  E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) + b.beta*E_(b.data,i,j,b.M,b.N);
    if (c.m>x)
      if (x<a.m)	 E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) ;   /* A is taller than B */
      else if (x<b.m) E_(c.data,i,j,c.M,c.N) =  b.beta*E_(b.data,i,j,b.M,b.N);  /* B is taller than A */
  }
  /* last COLUMN */
  if (c.n>y)
    
    if (y<a.n)  /* A is larger than B */
      for (i=0;i<a.m;i++)  E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N);
    else if (y<b.n)  /* B is larger than A */
      for (i=0;i<b.m;i++)   E_(c.data,i,j,c.M,c.N) =  b.beta*E_(b.data,i,j,b.M,b.N); 
  
  //c.beta = 1;  
  return 0;

}
int sub_amd_t(DEF(c), DEF(a), DEF(b)) { 
  
  int i,j,x,y;
  DEFREGISTERS;
  /* minimum sizes */
  x = min(a.m,b.m); y = min(a.n,b.n);
  //# pragma omp parallel for
  for (j=0; j<y; j++) {
    
    UNROLLKERNEL_t(c,a,b,i,j,y,UNLOOPCOMPUTESUB_t);
        
    /* j=y(R) to  y */
    for (;i<x;i++)  E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) - b.beta*E_(b.data,i,j,b.M,b.N);
    if (c.m>x)
      
      if (x<a.m)	 E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) ;   /* A is taller than B */
      else if (x<b.m) E_(c.data,i,j,c.M,c.N) =  - b.beta*E_(b.data,i,j,b.M,b.N);  /* B is taller than A */
  }
  /* last COLUMN */
  if (c.n>y)
    if (y<a.n)  /* A is larger than B */
      for (i=0;i<a.m;i++)  E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N);
    else if (y<b.n)  /* B is larger than A */
      for (i=0;i<b.m;i++)   E_(c.data,i,j,c.M,c.N) = - b.beta*E_(b.data,i,j,b.M,b.N); 
  return 0;

  //c.beta = 1;
}

#endif


static  int  divide_matrix_computation( DEF(c), DEF(a), DEF(b),
					TAddOperands *args,
					MatrixComputation m,
					int p,
					int t,
					int l) { 
  /*  
      printf("-\n");
      PRINTMATRIX("c",c);
      PRINTMATRIX("a",a);
      PRINTMATRIX("b",b);
  */
  if (t==1) { 
    args[0].pi = _A[l];//1<<l;
    args[0].m = m;
    args[0].c = c; 
    args[0].a = a; 
    args[0].b = b;
    //printf("PI %d--------\n",args[0].pi);
    l += p;
  }
  else { 
    int nc,na,nb,max;
    nc = HH(c.n);
    na = HH(a.n);
    nb = HH(b.n);
    
    max = (nc>na) ?nc :na;
    max = (max>nb) ?max :nb;


    l = divide_matrix_computation( HDK0(c,max), HDK0(a,max),HDK0(b,max), args, m, p/2+(p&1),t/2+(t&1),l);
    //    printf("t/2+t&1 %d--------\n",+t/2+(t&1));

    l = divide_matrix_computation( HDK1(c,c.n -max), HDK1(a,a.n-max),HDK1(b,b.n-max), args+t/2+(t&1), m,p/2,t/2 ,l);
  }

  return l;
} 



static 
TAddOperands * divideAdditions (DEF(c), DEF(a), DEF(b),
				MatrixComputation m,
				int *k) {

  TAddOperands *args = (TAddOperands *) malloc(NUM_THREADS*sizeof(TAddOperands));

  divide_matrix_computation(USE(c),USE(a),USE(b), args, m, NUM_CORES, NUM_THREADS,0);
  *k = NUM_THREADS;

  /*
  if (NUM_THREADS==2) {
    *k = 2;
    args[0].pi = 1;
    args[0].m = m;
    args[0].c = HD0(c); 
    args[0].a = HD0(a); 
    args[0].b = HD0(b); 
    args[1].pi = 4;
    args[1].m = m;
    args[1].c = HD1(c); 
    args[1].a = HD1(a); 
    args[1].b = HD1(b); 

  } else if (NUM_THREADS==4) {
    *k = 4;
    //print(c);
    args[0].m = m;
    args[0].pi =1;
    args[0].c = HD0(HD0(c)); 
    //print(args[0].c);
    args[0].a = HD0(HD0(a)); 
    args[0].b = HD0(HD0(b)); 

    args[1].m = m;
    args[1].pi =2;
    args[1].c = HD1(HD0(c));
    //print(args[1].c);
    //printf("%d \n",(int)(args[1].c.data - args[0].c.data));
    args[1].a = HD1(HD0(a)); 
    args[1].b = HD1(HD0(b));
    
    args[2].m = m;
    args[2].pi =4; 
    args[2].c = HD0(HD1(c)); 
    //print(args[2].c);
    //printf("%d \n",(int)(args[2].c.data - args[1].c.data));
    args[2].a = HD0(HD1(a)); 
    args[2].b = HD0(HD1(b)); 
    
    args[3].m = m;
    args[3].pi =8; 
    args[3].c = HD1(HD1(c));
    //print(args[3].c);
    //printf("%d \n",(int)(args[3].c.data - args[2].c.data));
    args[3].a = HD1(HD1(a)); 
    args[3].b = HD1(HD1(b)); 

  }
  */
  return args;
}


int ptcopy(DEF(c), DEF(a), DEF(b)) {
  
  

  pThreadedMatrixComputation(copy_matrix,divideAdditions, USE(c),USE(a),USE(b)); 
  return 0;


}
int ptadd(DEF(c), DEF(a), DEF(b)) {
  
  

  pThreadedMatrixComputation(add_amd,divideAdditions, USE(c),USE(a),USE(b)); 
  //pThreadedMatrixComputation(add,divideAdditions, USE(c),USE(a),USE(b)); 
  return 0;


}

int ptadd_t(DEF(c), DEF(a), DEF(b)) {
  
  

  pThreadedMatrixComputation(add_amd_t,divideAdditions, USE(c),USE(a),USE(b)); 
  // pThreadedMatrixComputation(add_t,divideAdditions, USE(c),USE(a),USE(b)); 

   return 0;

}

int ptsub(DEF(c), DEF(a), DEF(b)) {
  
  

  pThreadedMatrixComputation(sub_amd,divideAdditions, USE(c),USE(a),USE(b)); 
  //pThreadedMatrixComputation(sub,divideAdditions, USE(c),USE(a),USE(b)); 

   return 0;

}

int ptsub_t(DEF(c), DEF(a), DEF(b)) {
  
  

  pThreadedMatrixComputation(sub_amd_t,divideAdditions, USE(c),USE(a),USE(b)); 
  //pThreadedMatrixComputation(sub_t,divideAdditions, USE(c),USE(a),USE(b)); 

  return 0;

}



