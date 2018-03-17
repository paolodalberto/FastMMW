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



int main() { 

  int m,n,p,s;
  int i,j,k ;
  int ii,jj;
  double t;
  Matrix c,a,b,temp,g;
  int mask = 4|8;
  struct timeval _t1,_t2;
  double current_time;
  

  gettimeofday(&_t2,NULL);   
  current_time= (_t2.tv_sec)+ (double)(_t2.tv_usec)/1000000;    


  printf(" <m,n,p> ?\n");
  scanf("%d %d %d", &m,&n,&p);
  
  printf("-1,1 (0) or 0--1 (1)?\n");
  scanf("%d", &s);
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
  
  g.m=g.M=temp.m=temp.M = i; g.n=g.N=temp.n=temp.N = k;

  a.trans = b.trans = c.trans = g.trans = temp.trans = 'n';


  a.beta = 1;
  b.beta = 1;
  c.beta = g.beta = temp.beta =  0;



  printf("Creation ...\n");
  
  a.data    = (Mat *) CALLOC(a);
  b.data    = (Mat *) CALLOC(b);
  c.data    = (Mat *) CALLOC(c);
  temp.data = (Mat *) CALLOC(temp);
  g.data    = (Mat *) CALLOC(g);
	
	
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

  
  printf("A - \n");
  print(a);
  
  for (ii=0; ii<b.M; ii++) 
    for (jj=0; jj<b.N; jj++) { 
#if(SINGLE_PRECISION || DOUBLE_PRECISION)
      E_(b.data,ii,jj,b.M,b.N) = ((s==0)? RAND0:RAND1);
#else
      E_(b.data,ii,jj,b.M,b.N) =((s==0)? RAND0:RAND1)+I*((s==0)? RAND0:RAND1);
#endif
    }
  // print(b);
  


  printf("Doubly compensated mm \n");
  START_CLOCK;
  CMC(c, =, a, dcmul, b);
  //  CMC(c, =, a, dcmsum, b);
  END_CLOCK;
  //  mask = 4|8;
  //sched_setaffinity(0,sizeof(mask),&(mask));

  printf("RBC \n");
  START_CLOCK; 
  CMC(temp , =, a, mulpt, b);
  END_CLOCK;
  printf("multiplications row by column vs DCS"); error_analysis(temp,c);printf("\n");



  printf("Goto \n");
  START_CLOCK;
  CMC(g , =, a,  mm_leaf_computation, b);
  END_CLOCK;


  printf("\n ATLAS/GOTO w.r.t. DCS ");  error_analysis(c,g);printf("\n");
  printf(" ATLAS/GOTO w.r.t. RBC ");  error_analysis(c,temp);printf("\n");




  printf("Winograd mm \n");
  START_CLOCK; 
  CMC(temp , =, a,  wm, b);
  END_CLOCK;
  printf("\n Winograd w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
  printf(" Winograd w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");
  
  printf("Winograd-Marco mm \n");
  START_CLOCK; 
  CMC(temp , =, a,  bm, b);
  END_CLOCK;
  printf("\n Winograd-marco w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
  printf(" Winograd-marco w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");


  printf("Winograd mm pipe \n");
  START_CLOCK; 
  wmpipe(temp , a, b,0);
  END_CLOCK;
  printf("\n Winograd w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
  printf(" Winograd w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");
  
  printf("Winograd-Marco mm pipe\n");
  START_CLOCK; 
  bmpipe(temp , a, b,0);
  END_CLOCK;
  printf("\n Winograd-marco w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
  printf(" Winograd-marco w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");

  printf("Strassen mm \n");
  START_CLOCK; 
  CMC(temp , =, a,  smul, b);
  END_CLOCK;
  printf("\n Strassen w.r.t. DCS  ");  error_analysis(temp,c);printf("\n");
  printf(" Strassen w.r.t. GOTO ");  error_analysis(temp,g);printf("\n");
  //  printf("\n multiplications row by column ");
  
  
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  printf("3M Gotos mm \n");
  START_CLOCK; 
  CMC(temp , =, a,  mm_leaf_computation_3m, b);
  END_CLOCK; 
  printf("\n Gotos' 3M w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
  printf(" Gotos' 3M w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");


#endif
   

  
  
  FREE(a.data);
  FREE(b.data);
  FREE(c.data);
  FREE(temp.data);


return 0;
}
