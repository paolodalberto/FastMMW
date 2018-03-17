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
#define GETTIME 1
#include <architecture.h>
#include <mat-operands.h>
#include <sort.h>
#include <quicksort.h>
#include <stdlib.h>
#include <stdio.h>
#include <doubly_compensated_sumc.h>
#include <mat-mulkernels.h>


Mat *randomTimeseries(int N) { 

  int i;
  Mat *x = (Mat *) calloc(N,sizeof(Mat));

  for (i=0;i<N;i++) { 
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
    x[i] = (Mat) drand48()*((rand()%2)?1:-1);
#else
    x[i] = drand48()*((rand()%2)?1:-1) + drand48()*((rand()%2)?1:-1)*I;
#endif
  }

  return x;
} 

static int debug =0;

#define MAX(x,y) (((x)<(y))?(y):(x))


int main() {

  int N,T; 
  int n,t; 
  Mat s0,s1,s2,s3;
  Mat ms0,ms1,ms2,ms3;
  double mms0,mms1,mms2,mms3;
  Mat *x;
  ms0 = ms1 = ms2 = ms3 = 0;

  printf("Introduce N\n");
  scanf("%d",&N);


  printf("Introduce T\n");
  scanf("%d",&T);

  for (t=0;t<T;t++) { 
    
    x = randomTimeseries(N) ;
    s0 = sum(x,N);
    s1 = dcsum(x,N);
    if (debug) printV(x,N);
    s2 = sorted_dcsum(x,N);
    if (debug) printV(x,N);
    s3 = sorted_sum(x,N);
    if (debug) printV(x,N);
    if (debug) printf("sum %e dcsum %e sdcsum %e ssum %e\n",(double)s0,(double)s1,(double)s2,(double)s3);

    ms0 += ABS(s0-s1);
    ms1 += ABS(s0-s2);
    ms2 += ABS(s0-s3);
    ms3 += ABS(s1-s2);
    
    mms0 = MAX(ABS(s0-s1),mms0);
    mms1 = MAX(ABS(s0-s2),mms1);
    mms2 = MAX(ABS(s0-s3),mms2);
    mms3 = MAX(ABS(s2-s3),mms3);
    
    
     
    free(x);
  }
  
  ms0 /=T;
  ms1 /=T;
  ms2 /=T;
  ms3 /=T;

  printf("\n sum-dcsum %e sum-sdcsum %e sum-ssum %e dsum-sdsum %e\n",(double)ms0,(double)ms1,(double)ms2,(double)ms3);
  printf("\n max sum-dcsum %e max sum-sdcsum %e max sum-ssum %e max sdsum-ssum %e\n",(double)mms0,(double)mms1,(double)mms2,(double)mms3);

  

  x = randomTimeseries(N) ;
  printf("Sum");
  TIMING(s0 = sum(x,N),mms0,1);
  printf("DCSum");
  TIMING(s1 = dcsum(x,N),mms0,1);
  printf("SDCSum");
  START_CLOCK;
  s2 = sorted_dcsum(x,N);
  END_CLOCK;
  free(x);
  x = randomTimeseries(N) ;
  printf("SSum");
  START_CLOCK;
  s3 = sorted_sum(x,N);
  END_CLOCK;




  return 0;

}
