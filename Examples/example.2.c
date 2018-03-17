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
/************************************************************
 *
 * This test is for the verification that any MM algorithm is equivalent to GotoBLAS/ATLAS in Integer arithmetics. 
 * 
 *
 *
 *
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
extern int debug;

#ifdef GOTOS_TEST   
  char *program = "GOTOS";
#endif  
#ifdef WM_PIPE_TEST   
  char *program = "WM_PIPE";
#endif  
#ifdef SM_PIPE_TEST   
  char *program = "S_PIPE";
#endif  
#ifdef MARCO_PIPE_TEST   
  char *program = "MARCO_PIPE";
#endif  
#ifdef MARCO_TEST   
  char *program = "MARCO-Winograd";
#endif  
#ifdef GOTOS_TEST_3M   
  char *program = "GOTOS_3M";
#endif  
#ifdef SMUL_TEST
  char *program = "STRASSEN";
#endif
#ifdef WMUL_TEST 
  char *program = "WINOGRAD";
#endif
#ifdef WMUL_OPT_TEST 
  char *program = "WINOGRAD-OPT";
#endif
#ifdef OMUL_TEST
  char *program = "Oblivious STRASSEN";
#endif
#ifdef OWMUL_TEST
  char *program = "Oblivious WINO";
#endif
#ifdef DCMUL_TEST
  char *program = "DCSUM MM";
#endif
#ifdef PERMUTATION
  char *program = "PERMUTE WM";
#endif



int main() { 

  int m,n,p;
  int i,j,k ;
  int ii,jj;
  int sel;
  Matrix c,a,b,temp;


  printf("sizeof(float) = %d \n", sizeof(float));
  printf("sizeof(double) = %d \n", sizeof(double));
  printf("sizeof(float complex) = %d \n", sizeof(float complex));
  printf("sizeof(complex) = %d \n", sizeof(complex));
  printf("sizeof(double complex) = %d \n", sizeof(double complex));

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
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  a.beta=atof(d)+0*I;
  printf("B[%e+i%e]\n", creal(a.beta),cimag(a.beta));
#else
  a.beta=atof(d);
  printf("B[%e]\n", (double)a.beta);
#endif
  printf("Beta B \n");
  scanf("%s",d);
  printf("Beta C \n");
  scanf("%s",d);
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  b.beta=atof(d)+0*I;
  printf("B[%e+i%e]\n", creal(b.beta),cimag(b.beta));
#else
  b.beta=atof(d);
  printf("B[%e]\n",  (double)a.beta);
#endif
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
  c.beta=atof(d)+0*I;
  printf("B[%e+i%e]\n", creal(c.beta),cimag(c.beta));
#else
  c.beta=atof(d);
  printf("C[%e]\n",  (double)c.beta);
#endif
  temp.beta = c.beta;

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
  
  if (a.trans == 'n' && b.trans == 'n' && a.n != b.m ) { 
    printf(" N N wrong sizes ... a.n != b.m\n");
    return 0;
  }
  if (a.trans != 'n' && b.trans == 'n' && a.m != b.m ) { 
    printf("T N wrong sizes ... a.m != b.m\n");
    return 0;
  }
  if (a.trans != 'n' && b.trans != 'n' && a.m != b.n ) { 
    printf("T T wrong sizes ... a.m != b.n\n");
    return 0;
  }
  if (a.trans == 'n' && b.trans != 'n' && a.n != b.n ) { 
    printf("N T wrong sizes ... a.n != b.n\n");
    return 0;
  }
   

  printf("Creation ...\n");
  
  a.data    = (Mat *) CALLOC(a);
  b.data    = (Mat *) CALLOC(b);
  c.data    = (Mat *) CALLOC(c);
  temp.data = (Mat *) CALLOC(temp);
	
	
  printf("Initialization ...\n");
  randomInitialization(a,rand(),rand());
  printf("A - \n");
  //print(a);
  
  randomInitialization(b,rand(),rand());
  randomInitialization(c,rand(),rand());
  copy(temp,c);


  printf("B - \n");
  //  print(b);
  //  print(c);
  printf("Strassen/Winograd ... %s \n",program);


    START_CLOCK;
#ifdef DCMUL_TEST
  CMC(c, =, a, dcmsum, b);
#endif  
#ifdef GOTOS_TEST   
  CMC(c, =, a, mm_leaf_computation, b);
#endif  
#ifdef MARCO_PIPE_TEST   
  BMOWR_PIPE (c, a, b,0);
#endif  
#ifdef MARCO_TEST   
  BMOWR (c, a, b);
#endif  
#ifdef WM_PIPE_TEST   
  wmpipe(c, a, b,0);
#endif  
#ifdef SM_PIPE_TEST   
  smpipe(c, a, b,0);
#endif  
#ifdef GOTOS_TEST_3M
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)  
  CMC(c, =, a, mm_leaf_computation_3m, b);
#endif  
#endif  
#ifdef SMUL_TEST
  CMC(c, =, a,smul , b);
#endif
#ifdef WMUL_OPT_TEST
  CMC(c, =, a,wm , b);
#endif
#ifdef OMUL_TEST
  CMC(c, =, a,omul , b);
#endif
#ifdef OWMUL_TEST
  CMC(c, =, a,owmul , b);
#endif
#ifdef PERMUTATION
  CMC(c, =, a,wmR , b);
#endif
    END_CLOCK;

    /*
  printf("Fast regular mul ... \n");
  
  START_CLOCK;

  CMC(temp , =, a,mm_leaf_computation, b);
  //print(temp);
  END_CLOCK;



  printf("Comparison ... \n");
  //  if (c.M*c.N<100) debug=1;
  //else debug = 0;
  if (comp(temp, c)) 
    printf(" Failure  !!!\n");
  else 
    printf(" Success \n");
    */
  
  printf("RBC \n");
  CMC(temp, =, a, mul , b);
  printf("Comparison ... \n");
  //  if (c.M*c.N<100) debug=1;
  //else debug = 0;
  if (comp(temp, c)) 
    printf(" Failure  !!!\n");
  else 
    printf(" Success \n");
  print(c);
  print(temp);
  
  
  FREE(a.data);
  FREE(b.data);
  FREE(c.data);
  FREE(temp.data);


return 0;
}
