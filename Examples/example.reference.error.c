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
#define GETTIME
#include <architecture.h>
#include <mat-operands.h>
#include <mat-mulkernels.h>
#include <mat-addkernels.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include <stdio.h>

#define ERROR_K 
#ifdef ERROR_K
#define RAND0 (((rand()%2)?1:-1)*drand48())
#define RAND1 (drand48())
#endif
#ifndef ERROR_K
#define RAND0 (rand()%99)
#define RAND1 (fabs(rand()%99))
#endif


void append_to_file(char *filename, Matrix a,Matrix b, Matrix c) { 


  FILE *rep  = fopen(filename,"a");
  print_to_file(rep,a);
  print_to_file(rep,b);
  print_to_file(rep,c);
  fclose(rep);
}



int main() { 

  int m,n,p,s;
  int i,j,k ;
  int ii,jj;
  double t;
  Matrix c,a,b;
  struct timeval _t1,_t2;
  double current_time;
  char filename[100];

  gettimeofday(&_t2,NULL);   
  current_time= (_t2.tv_sec)+ (double)(_t2.tv_usec)/1000000;    


  printf(" <m,n,p> ?\n");
  scanf("%d %d %d", &m,&n,&p);
  
  printf("-1,1 (0) or 0--1 (1)?\n");
  scanf("%d", &s);

  printf("Destination file\n");
  scanf("%s", filename);


  i=m;
  j=n;
  k=p;

  printf(" You selected the following problem \n");
  printf("      A %d x %d \n",i,j);
  printf("      B %d x %d \n",j,k);
  printf(" Thus C %d x %d \n",i,k);
  if (s==0) { printf(" -1,1 interval\n"); }
  else  { printf(" 0-1 interval\n"); }
  
  a.m=a.M = i; a.n=a.N = j;
  b.m=b.M = j; b.n=b.N = k;
  c.m=c.M = i; c.n=c.N = k;
  
  a.trans = b.trans = c.trans = 'n';


  a.beta = 1;
  b.beta = 1;
  c.beta = 0;



  printf("Creation ...\n");
  
  a.data    = (Mat *) CALLOC(a);
  b.data    = (Mat *) CALLOC(b);
  c.data    = (Mat *) CALLOC(c);
	
  printf("Initialization ...\n");
  srand48((long int)current_time);

  for (ii=0; ii<a.M; ii++) 
    for (jj=0; jj<a.N; jj++) {
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      E_(a.data,ii,jj,a.M,a.N) =((s==0)? RAND0:RAND1);
#else
      E_(a.data,ii,jj,a.M,a.N) =((s==0)? RAND0:RAND1) + I*((s==0)? RAND0:RAND1);
#endif
    }

  
  for (ii=0; ii<b.M; ii++) 
    for (jj=0; jj<b.N; jj++) { 
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      E_(b.data,ii,jj,b.M,b.N) = ((s==0)? RAND0:RAND1);
#else
      E_(b.data,ii,jj,b.M,b.N) =((s==0)? RAND0:RAND1)+I*((s==0)? RAND0:RAND1);
#endif
    }

  printf("Doubly compensated mm \n");
  START_CLOCK;
  CMC(c, =, a, dcmul, b);
  END_CLOCK;

  append_to_file(filename,a,b,c);

  
  
  FREE(a.data);
  FREE(b.data);
  FREE(c.data);


return 0;
}
