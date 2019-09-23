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
 * This the core example for purpose measure. With the right macro
 * defined, I can test any MM algorithm.
 * 
 *
 *
 *
 */
//#define APPLICATION

#define GETTIME

#include <architecture.h>
#include <mat-operands.h>
#include <mat-mulkernels.h>
#include <mat-addkernels.h>
#include <string.h>
#include <mixed_precision.h>
#include <omp.h>

#include <stdio.h>
//#include <scaling.h>

static int echo =1;

int debug;
#define MULINTERVAL 10


#define DIST(a,b,c,t)				\
  c.trans=t.trans='n';				\
  a.m=a.M ; a.n=a.N ;				\
  b.m=sb.M ; b.n=b.N ;				\
  if (a.trans=='n') {				\
    t.m =t.M=c.m=c.M =a.M;			\
  }						\
  else {					\
    t.m =t.M= c.m=c.M =a.N;			\
  }						\
  if (b.trans=='n') {				\
    t.n =t.N= c.n=c.N =b.N;			\
  }						\
  else {					\
    t.n =t.N =c.n=c.N =b.M;			\
  }						\



int main() {
  double time_mul;
  double time_add, ops,mops_add,mops_add_2,mops_mul;
  double time_add_2;
  S_Matrix sc,sa,sb,st;
  D_Matrix dc,da,db,dt;
  S_Matrix sr;
  D_Matrix dr;
  int i,j;
  int sign;
  int diff;
  double timemul;

  int sel;
  char d[100]={0, 0};
  char TRANSPOSE[3] = {'n', 't', 'c'};
  int mask = 4|8;


  printf("A [n/t/c]\n");
  SELECT(sel);
  printf("%d  A[%c]\n", sel, sa.trans=TRANSPOSE[sel]);
  printf("B [n/t/c]\n");
  SELECT(sel);
  printf("%d  B[%c]\n", sel, sb.trans=TRANSPOSE[sel]);
  sc.trans  = 'n';
  st.trans  = 'n';

  da.trans = sa.trans;
  db.trans = sb.trans;

  strcpy(d,"1");
  printf("Beta A \n");
  scanf("%s",d);

  sa.beta=atof(d);
  da.beta = (double) sa.beta;


  printf("Beta B \n");
  scanf("%s",d);
  printf("Beta C \n");
  scanf("%s",d);

  sb.beta=atof(d);
  db.beta = (double) sb.beta;


  
  st.beta=sc.beta=1;
  dt.beta=dc.beta=1;
  
  printf(" <a.m,a.n,b.m,b.n> ?\n");
  scanf("%d %d %d %d", &sa.M,&sa.N,&sb.M,&sb.N);

  printf("0: [-1,1] 1: [0,1]\n");
  scanf("%d", &sign);
  
  da.M  = sa.M;
  da.N  = sa.N;
  db.M  = sb.M;
  db.N  = sb.N;


  DIST(sa,sb,sc,st);
  DIST(da,db,dc,dt);

  dr = dc;
  sr = sc;

  printf(" size of the matrix element %ld\n", sizeof(Mat));
  printf(" You selected the following problem \n");
  printf("      A %d x %d \n",sa.m,sa.n);
  printf("      B %d x %d \n",sb.m,sb.n);
  printf(" Thus C %d x %d \n",sc.m,sc.n);
  
  if (sa.trans == 'n' && sb.trans == 'n' && sa.n != sb.m ) { 
    printf(" N N wrong sizes ... a.n != b.m\n");
    return 0;
  }
  if (sa.trans != 'n' && sb.trans == 'n' && sa.m != sb.m ) { 
    printf("T N wrong sizes ... a.m != b.m\n");
    return 0;
  }
  if (sa.trans != 'n' && sb.trans != 'n' && sa.m != sb.n ) { 
    printf("T T wrong sizes ... a.m != b.n\n");
    return 0;
  }
  if (sa.trans == 'n' && sb.trans != 'n' && sa.n != sb.n ) { 
    printf("N T wrong sizes ... a.n != b.n\n");
    return 0;
  }
  
  printf("Creation ...\n");
  
  sa.data    = (float *) calloc(sa.M*sa.N,sizeof(float));
  sb.data    = (float *) calloc(sb.M*sb.N,sizeof(float));
  sc.data    = (float *) calloc(sc.M*sc.N,sizeof(float));
  sr.data    = (float *) calloc(sr.M*sr.N,sizeof(float));

  
  da.data    = (double *) calloc(da.M*da.N,sizeof(double));
  db.data    = (double *) calloc(db.M*db.N,sizeof(double));
  dc.data    = (double *) calloc(dc.M*dc.N,sizeof(double));
  dr.data    = (double *) calloc(dr.M*dr.N,sizeof(double));


  
  printf("Initialization ...\n");
  
  d_randomInitializationError(da,sign);
  d_randomInitializationError(db,sign);
  d_randomInitializationError(dc,sign);
  
  for (i=0;i<sa.M;i++) 
    for(j=0;j<sa.N;j++) {
      E_(sa.data,i,j,sa.M,sa.N) = (float) E_(da.data,i,j,da.M,da.N); 
      
    }
  for (i=0;i<sb.M;i++) 
    for(j=0;j<sb.N;j++) {
      E_(sb.data,i,j,sb.M,sb.N) = (float) E_(db.data,i,j,db.M,db.N); 
      
    }
  for (i=0;i<sc.M;i++) 
    for(j=0;j<sc.N;j++) {
      E_(sr.data,i,j,sr.M,dr.N) = E_(sc.data,i,j,sc.M,sc.N) = 
      E_(dr.data,i,j,dr.M,dr.N) = E_(dc.data,i,j,dc.M,dc.N); 
      
    }



  for (i=0;i<NUM_THREADS;i++) 
    mask = mask | _T[i];
  sched_setaffinity(0,sizeof(mask),&(mask));


  printf("DCS MUL single\n");
  //TIMING_COLD(CMC(sr, =, sa, s_dcmul, sb),time_mul,10);
  TIMING_COLD(CMC(sr, =, sa, mm_leaf_computation_s, sb),time_mul,10);
  END_CLOCK;
  
  printf("DCS MUL double\n");
  //TIMING_COLD(CMC(dr, =, da, d_dcmul, db),time_mul,10);
  TIMING_COLD(CMC(dr, =, da, mm_leaf_computation_d, db),time_mul,10);
  
  printf("\n S DCS w.r.t. D_DCS              \n");
  error_analysis_s_d(sr,dr);printf("\n");

  printf("RBC MUL single\n");
  TIMING_COLD(CMC(sc, =, sa, s_mulpt , sb),time_mul,10);
  printf("S_MM RBC   w.r.t. S_DCS   ");s_error_analysis(sc,sr);printf("\n");
  printf("S_MM RBC   w.r.t. D_DCS   ");error_analysis_s_d(sc,dr);printf("\n");

  printf("MM single\n");
  TIMING_COLD(CMC(sc, =, sa, mm_leaf_computation_s, sb),time_mul,10);
  printf("S_MM       w.r.t. S_DCS         ");s_error_analysis(sc,sr);printf("\n");
  printf("S_MM       w.r.t. D_DCS         ");error_analysis_s_d(sc,dr);printf("\n");

  printf("Winograd single\n");
  TIMING_COLD(CMC(sc, =, sa, s_wm, sb),time_mul,10);
  printf("S_Winograd w.r.t. S_DCS         "); s_error_analysis(sc,sr);printf("\n");
  printf("S_Winograd w.r.t. D_DCS         "); error_analysis_s_d(sc,dr);printf("\n");

  printf("Strassen single\n");
  TIMING_COLD(CMC(sc, =, sa, s_smul, sb),time_mul,10);
  printf("S_Strassen w.r.t. S_DCS         "); s_error_analysis(sc,sr);printf("\n");
  printf("S_Strassen w.r.t. D_DCS         "); error_analysis_s_d(sc,dr);printf("\n");

  printf("Winograd Marco single\n");
  TIMING_COLD(CMC(sc, =, sa, s_bm , sb),time_mul,10);
  
  printf("S_Winograd-M w.r.t. S_DCS       "); s_error_analysis(sc,sr);printf("\n");
  printf("S_Winograd-M w.r.t. D_DCS       "); error_analysis_s_d(sc,dr);printf("\n");

  printf("RBC Double\n"); 
  TIMING_COLD(CMC(dc, =, da, d_mulpt, db),time_mul,10);
  printf("D_MM RBC   w.r.t. D_DCS   ");       d_error_analysis(dc,dr);printf("\n");


  printf("MM double\n");
  TIMING_COLD(CMC(dc, =, da, mm_leaf_computation_d, db),time_mul,10);
  printf("D_MM    w.r.t. D_DCS   ");  d_error_analysis(dc,dr);printf("\n");

  printf("Winograd double\n");
  TIMING_COLD(CMC(dc, =, da, d_wm , db),time_mul,10);
  printf("D_Winograd    w.r.t. D_DCS   ");  d_error_analysis(dc,dr);printf("\n");


  printf("Strassen double\n");
  TIMING_COLD(CMC(dc, =, da, d_smul, db),time_mul,10);
  printf("D_Strassen    w.r.t. D_DCS   ");  d_error_analysis(dc,dr);printf("\n");


  printf("Winograd-Marco double\n");
  TIMING_COLD(CMC(dc, =, da, d_bm                 , db),time_mul,10);
  printf("D_Winograd-Marco   w.r.t. D_DCS   ");  d_error_analysis(dc,dr);printf("\n");

  

  free(sa.data);
  free(sb.data);
  free(sc.data);
  free(sr.data);

  free(da.data);
  free(db.data);
  free(dc.data);
  free(dr.data);

  return 0;
} 



