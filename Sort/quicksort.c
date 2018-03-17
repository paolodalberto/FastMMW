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
#define QUICKSORT_MODULE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>
#include <assert.h>


#include <sort.h>
#include <quicksort.h>
#include <pt.h>

static int debug =0;


#define DECREASING_ORDER 1

#define MAX(x,y) ((x<y)?y:x)
#define MIN(x,y) ((x<y)?x:y)

//#define DECREASING_ORDER 1                                                                                                                                 

#if(DECREASING_ORDER)
#define BB(i,j,src,pivot,lower,upper) { \
    do (i)++; \
    while ((i)<=(upper) && GT(ABS(((src)[(i)])), ABS(pivot)));  \
    do (j)--; \
    while ((j>=lower) && LT(ABS((src)[(j)]), ABS(pivot))); \
  }
#define BBI(i,j,src,pivot,lower,upper) { \
    do (i)++; \
    while ((i)<=(upper) && LT(ABS(((src)[(i)])), ABS(pivot)));  \
    do (j)--; \
    while ((j>=lower) && GT(ABS((src)[(j)]), ABS(pivot))); \
  }
#else
#define BB(i,j,src,pivot,lower,upper) { \
    do (i)++; \
    while ((i)<=(upper) && LT(ABS((src)[(i)]), ABS(pivot))); \
    do (j)--; \
    while ((j>=lower) && GT(ABS((src)[(j)]), ABS(pivot))); \
  }
#define BBI(i,j,src,pivot,lower,upper) { \
    do (i)++; \
    while ((i)<=(upper) && GT(ABS((src)[(i)]), ABS(pivot))); \
    do (j)--; \
    while ((j>=lower) && LT(ABS((src)[(j)]), ABS(pivot))); \
  }
#endif


void printV(Mat *m, int n){
  int i;
  for (i=0;i<n;i++) {
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
    printf("%e ",ABS(m[i]));
#else
    printf("%e+i%e ",creal(m[i]),cimag(m[i]));
#endif
  }

  printf("\n");


}
int orderTest(Mat *m, int n, int j){
  int i;


  if (n<1) return 0;
  
  
  for (i=1;i<n;i++) {
    if (j==0 && LT(ABS(m[i-1]),ABS(m[i])))
      return i;
    if (j==1 && GT(ABS(m[i-1]),ABS(m[i])))
      return i;
  }
  return 0;
}



void  insort (register Mat *array, register int len)
{
        register int    i, j;
        register Mat  temp;
        if (debug) {
          printf("insort\n") ;
          printV(array,len);
        }
        for (i = 1; i < len; i++) {
		/* invariant:  array[0..i-1] is sorted */
                j = i;
                /* customization bug: SWAP is not used here */
                temp = array[j];
#if(DECREASING)
                while (j > 0 && GT(ABS(array[j-1]), ABS(temp)))
#else
                while (j > 0 && LT(ABS(array[j-1]), ABS(temp)))
#endif
                  {
                        array[j] = array[j-1];
                        j--;
                }
                array[j] = temp;
                if (debug) {
                  printf("i %d j %d ",i,j);
                  printV(array,len);
                }
        }
        if (debug) {
          printf("insort final\n");
          printV(array,len);
          printf("\n");
        }
}


void  partial_quickersort (register Mat * array, register int lower, register int upper)
{
    register int        i, j;
    register Mat        pivot;

    if (debug) {
      printf(" quick sort %d\n",upper-lower+1);
      printV(array+lower,upper-lower+1);

    }
    if (upper - lower > CUTOFF) {
        SWAP(array[lower], array[(upper+lower)/2]);
        i = lower;  j = upper+1;  pivot = array[lower];
        while (1) {
          BB(i,j,array,pivot,lower,upper);
          if (j < i) break;
          if (debug) printf("swap %d %d\n",i, j);
          SWAP(array[i], array[j]);
        }
        if (debug) { printf("split \n"); printV(array+lower,upper-lower+1);}
        if (debug) printf("swap %d %d j %d i\n",lower, j,i);
        SWAP(array[lower], array[j]);

        if (debug) { printf("after \n"); printV(array+lower,upper-lower+1);}
        partial_quickersort (array, lower, j - 1);
        if (debug) printV(array+lower,j-lower);
        partial_quickersort (array, i, upper);
        if (debug) printV(array+i,upper-i+1);

    }
    else {
      insort( array+lower,upper - lower+1);

    }
    if (debug) {printf("result quicksort\n"); printV(array+lower,upper-lower+1); printf("\n");}

}
void  insort_inverse (register Mat *array, register int len)
{
        register int    i, j;
        register Mat  temp;

        if (debug) {
          printf("insort I \n") ;
          printV(array,len);
        }
        for (i = 1; i < len; i++) {
                /* invariant:  array[0..i-1] is sorted */
                j = i;
                /* customization bug: SWAP is not used here */
                temp = array[j];

#if(DECREASING)
                while (j > 0 && LT(ABS(array[j-1]), ABS(temp)))
#else
                while (j > 0 && GT(ABS(array[j-1]), ABS(temp)))

#endif
                  {
                    array[j] = array[j-1];
                    j--;
                }
                array[j] = temp;
        }
}



void  partial_quickersort_inverse (register Mat * array, register int lower, register int upper)
{
    register int        i, j;
    register Mat        pivot;

    if (debug) {
      printf(" quick sort  I %d\n",upper-lower+1);
      printV(array+lower,upper-lower+1);

    }


    if (upper - lower > CUTOFF) {
        SWAP(array[lower], array[(upper+lower)/2]);
        i = lower;  j = upper+1;  pivot = array[lower];
        while (1) {
          BBI(i,j,array,pivot,lower,upper);
          if (j < i) break;
          SWAP(array[i], array[j]);
        }
        SWAP(array[lower], array[j]);
        partial_quickersort_inverse (array, lower, j - 1);
        partial_quickersort_inverse (array, i, upper);
    }
    else {
      insort_inverse( array+lower,upper - lower+1);

    }
    if (debug) {printf("result quicksort I \n"); printV(array+lower,upper-lower+1); printf("\n");}
}


void  *parallel_quickersort (void *arg)
{
  cpu_set_t current_mask; 
  pthread_t  p_thread; /* thread's structure */
  pthread_attr_t attr;
  int thr_id;
  int        i, j;
  Mat        pivot;
  int p1; 
  Sort_Datum d,rs;
  Mat *array;
  int lower,upper;

  rs = d = *((Sort_Datum*)arg);
  array = d.array;
  upper =d.u;
  lower = d.l;

  if (debug) { 
    printf("Array  %d-%d \n",d.l,d.u);
    printf("Pool   %d-%d \n",d.p.l,d.p.u);
    printf("Processor %d\n",d.p.p[d.p.l]);
  }


  
  
  
  if (upper - lower > CUTOFF) {
    SWAP(array[lower], array[(upper+lower)/2]);
    i = lower;  j = upper+1;  pivot = array[lower];
    
    while (1) {
      BB(i,j,array,pivot,lower,upper);
      if (j < i) break;
      SWAP(array[i], array[j]);
    }
    SWAP(array[lower], array[j]);
    
    
    if (d.p.u>d.p.l) { 
      p1 = sched_setaffinity(0,sizeof(d.p.p[d.p.l]),&(d.p.p[d.p.l]));
      if (p1<0) { 
	printf(" Fail processor setting 1 \n");
      }

      rs.l = i;
      rs.u = upper;
      rs.p.l = d.p.u/2 + d.p.u%2;
      pthread_attr_init(&attr);
      pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
      thr_id = pthread_create(&p_thread, 
			      &attr, 
			      parallel_quickersort, 
			      (void *)(&rs));
    
      
      d.l = lower;
      d.u = j-1;
      d.p.u = d.p.u/2;
      parallel_quickersort((void *)&d);
      
      pthread_join(p_thread, NULL);
      
      
    }  else {
      
      partial_quickersort (array, lower, j - 1);
      partial_quickersort (array, i, upper);
      
    }
  }  
  else { 
    insort( array+lower,upper - lower);
    
  }

  return 0;
  
}

