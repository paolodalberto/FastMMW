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
#include <string.h>


#include <stdio.h>

char d[100]={0, 0};
char TRANSPOSE[3] = {'n', 't', 'c'};
int main() { 

  int m,n,p;
  int i,j,k ;
  int ii,jj;
  int sel;
  Matrix c,a,b,temp;

  printf("A [n/t/c]\n");
  SELECT(sel);
  printf("%d  A[%c]\n", sel, a.trans=TRANSPOSE[sel]);
  printf("B [n/t/c]\n");
  SELECT(sel);
  printf("%d  B[%c]\n", sel, b.trans=TRANSPOSE[sel]);
  c.trans = temp.trans = 'n';


  strcpy(d,"1");
  printf("Beta A \n");
  scanf("%s",d);
  a.beta=atof(d);
  printf("A[%e]\n", a.beta);
  printf("Beta B \n");
  scanf("%s",d);
  b.beta=atof(d);
  printf("B[%e]\n", b.beta);
  printf("Beta C \n");
  scanf("%s",d);
  c.beta=atof(d);
  temp.beta=c.beta;
  printf("C[%e]\n", c.beta);


  printf(" <a.m,a.n,b.m,b.n> ?\n");
  scanf("%d %d %d %d", &a.M,&a.N,&b.M,&b.N);

  a.m=a.M ; a.n=a.N ;
  b.m=b.M ; b.n=b.N ;
  if (a.trans=='n') {
    c.m=c.M =a.M; 
  }
  else {
    c.m=c.M =a.N;
  }
  if (b.trans=='n') {
    c.n=c.N =b.N;
  }
  else {
    c.n=c.N =b.M;
  }

  temp.m=temp.M=c.M; temp.n=temp.N=c.N;

  printf(" You selected the following problem \n");
  printf("      A %d x %d \n",a.m,a.n);
  printf("      B %d x %d \n",b.m,b.n);
  printf(" Thus C %d x %d \n",c.m,c.n);
  printf(" Thus t %d x %d \n",temp.m,temp.n);
  

   

  printf("Creation ...\n");
  
  a.data    = (Mat *) CALLOC(a);
  b.data    = (Mat *) CALLOC(b);
  c.data    = (Mat *) CALLOC(c);
  temp.data = (Mat *) CALLOC(temp);
	
	
  printf("Initialization ...\n");
  
  printf("Initialization ...\n");
  randomInitialization(a,rand(),rand());
  printf("A - \n");
  //print(a);
  
  randomInitialization(b,rand(),rand());
  randomInitialization(c,rand(),rand());
  copy(temp,c);


  CMC(c, =, a, add, b);
  

  CMC(temp, =, a, ptadd, b);

  if (comp(temp, c)) 
    printf(" Failure  !!!\n");
  else 
    printf(" Success \n");

  
  FREE(a.data);
  FREE(b.data);
  FREE(c.data);
  FREE(temp.data);


return 0;
}
