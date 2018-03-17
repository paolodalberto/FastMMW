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
  C_Matrix sc,sa,sb,st;
  Z_Matrix dc,da,db,dt;
  C_Matrix sr;
  Z_Matrix dr;
  int i,j;
  int sign;
  int diff;

  S_Matrix *sctemp,*sttemp, *srtemp;
  D_Matrix *dctemp,*dttemp, *drtemp;
  
  S_Matrix *ssc,*ssa,*ssb;
  D_Matrix *dsc,*dsa,*dsb;



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
  
  sa.data    = (float complex *) calloc(sa.M*sa.N,sizeof(float complex));
  sb.data    = (float complex *) calloc(sb.M*sb.N,sizeof(float complex));
  sc.data    = (float complex *) calloc(sc.M*sc.N,sizeof(float complex));
  sr.data    = (float complex *) calloc(sr.M*sr.N,sizeof(float complex));
  
  da.data    = (double complex *) calloc(da.M*da.N,sizeof(double complex));
  db.data    = (double complex *) calloc(db.M*db.N,sizeof(double complex));
  dc.data    = (double complex *) calloc(dc.M*dc.N,sizeof(double complex));
  dr.data    = (double complex *) calloc(dr.M*dr.N,sizeof(double complex));

  
  printf("Initialization ...\n");
  
  z_randomInitializationError(da,sign);
  z_randomInitializationError(db,sign);
  z_randomInitializationError(dc,sign);
  
  for (i=0;i<sa.M;i++) 
    for(j=0;j<sa.N;j++) {
      E_(sa.data,i,j,sa.M,sa.N) = (float complex) E_(da.data,i,j,da.M,da.N); 
      
    }
  for (i=0;i<sb.M;i++) 
    for(j=0;j<sb.N;j++) {
      E_(sb.data,i,j,sb.M,sb.N) = (float complex) E_(db.data,i,j,db.M,db.N); 
      
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
  
  TIMING_COLD(CMC(sr, =, sa, c_dcmul, sb),time_mul,10); 
  
  printf("DCS MUL double\n");
  TIMING_COLD(CMC(dr, =, da, z_dcmul, db),time_mul,10);

  srtemp = from_c_to_s(sr);
  drtemp = from_z_to_d(dr);
  
  free(sr.data);
  free(dr.data);

  printf("\n C_DCS MM R w.r.t. Z_DCS MM R  "); 
  error_analysis_s_d(srtemp[0],drtemp[0]);
  printf("\n");
  printf("\n C_CDS MM I w.r.t. Z_DCS MM I  "); error_analysis_s_d(srtemp[1],drtemp[1]);printf("\n");

  printf("MM single\n");
  TIMING_COLD(CMC(sc, =, sa, mm_leaf_computation_c, sb),time_mul,10)
    
  sctemp = from_c_to_s(sc);

  printf("\n C MM R w.r.t. C_DCS MM R  "); s_error_analysis(sctemp[0],srtemp[0]);printf("\n");
  printf("\n C MM I w.r.t. C_DCS MM I  "); 
  s_error_analysis(sctemp[1],srtemp[1]);
  printf("\n");
  printf("\n C MM R w.r.t. Z_DCS MM R  "); error_analysis_s_d(sctemp[0],drtemp[0]);printf("\n");
  printf("\n C MM I w.r.t. Z_DCS MM I  "); error_analysis_s_d(sctemp[1],drtemp[1]);printf("\n");
  
  free(sctemp[0].data);
  free(sctemp[1].data);
  free(sctemp);
  
  printf("Winograd single\n");
  TIMING_COLD(CMC(sc, =, sa, c_wm                 , sb),time_mul,10)
  sctemp = from_c_to_s(sc);

  printf("\n C Winograd R w.r.t. C_DCS MM R  "); s_error_analysis(sctemp[0],srtemp[0]);printf("\n");
  printf("\n C Winograd I w.r.t. C_DCS MM I  "); s_error_analysis(sctemp[1],srtemp[1]);printf("\n");
  printf("\n C Winograd R w.r.t. Z_DCS MM R  "); error_analysis_s_d(sctemp[0],drtemp[0]);printf("\n");
  printf("\n C Winograd I w.r.t. Z_DCS MM I  "); error_analysis_s_d(sctemp[1],drtemp[1]);printf("\n");
  
  free(sctemp[0].data);
  free(sctemp[1].data);
  free(sctemp);


  printf("Winograd Marco single\n");
  TIMING_COLD(CMC(sc, =, sa, c_bm                , sb),time_mul,10)  ;
  sctemp = from_c_to_s(sc);

  printf("\n C Winograd-M R w.r.t. C_DCS MM R  "); s_error_analysis(sctemp[0],srtemp[0]);printf("\n");
  printf("\n C Winograd-M I w.r.t. C_DCS MM I  "); s_error_analysis(sctemp[1],srtemp[1]);printf("\n");
  printf("\n C Winograd-M R w.r.t. Z_DCS MM R  "); error_analysis_s_d(sctemp[0],drtemp[0]);printf("\n");
  printf("\n C Winograd-M I w.r.t. Z_DCS MM I  "); error_analysis_s_d(sctemp[1],drtemp[1]);printf("\n");
  
  free(sctemp[0].data);
  free(sctemp[1].data);
  free(sctemp);


  printf("RBC single\n");
  TIMING_COLD(CMC(sc, =, sa, c_mulpt                 , sb),time_mul,10);
  sctemp = from_c_to_s(sc);

  printf("\n C RBC MM R w.r.t. C_DCS MM R  "); s_error_analysis(sctemp[0],srtemp[0]);printf("\n");
  printf("\n C RBC MM I w.r.t. C_DCS MM I  "); s_error_analysis(sctemp[1],srtemp[1]);printf("\n");
  printf("\n C RBC MM R w.r.t. Z_DCS MM R  "); error_analysis_s_d(sctemp[0],drtemp[0]);printf("\n");
  printf("\n C RBC MM I w.r.t. Z_DCS MM I  "); error_analysis_s_d(sctemp[1],drtemp[1]);printf("\n");
  
  
  ssc = from_c_to_s(sc);
  ssa = from_c_to_s(sa);
  ssb = from_c_to_s(sb);

  printf("3M single\n");
  TIMING_COLD(MM3(sctemp[0],sctemp[1],ssa[0],ssa[1],ssb[0],ssb[1],ssc[0],ssc[1],mm_leaf_computation_s, mm_leaf_computation_madd_s, s_ptadd, s_ptadd_t),time_mul,10);
  printf("\n C_3M GT R  w.r.t. C_DCS R  ");s_error_analysis(sctemp[0],srtemp[0]);printf("\n");
  printf("\n C_3M GT I  w.r.t. C_DCS I  ");s_error_analysis(sctemp[1],srtemp[1]);printf("\n");
  printf("\n C 3M MM R w.r.t. Z_DCS MM R  "); error_analysis_s_d(sctemp[0],drtemp[0]);printf("\n");
  printf("\n C 3M MM I w.r.t. Z_DCS MM I  "); error_analysis_s_d(sctemp[1],drtemp[1]);printf("\n");


  printf("3M Winograd single\n");
  TIMING_COLD(MM3(sctemp[0],sctemp[1],ssa[0],ssa[1],ssb[0],ssb[1],ssc[0],ssc[1],s_wm, s_wmadd, s_ptadd, s_ptadd_t),time_mul,10);
  printf("\n C_3M W R w.r.t. C_DCS R  ");s_error_analysis(sctemp[0],srtemp[0]);printf("\n");
  printf("\n C_3M W I w.r.t. C_DCS I  ");s_error_analysis(sctemp[1],srtemp[1]);printf("\n"); 
  printf("\n C 3M W R w.r.t. Z_DCS MM R  "); error_analysis_s_d(sctemp[0],drtemp[0]);printf("\n");
  printf("\n C 3M W I w.r.t. Z_DCS MM I  "); error_analysis_s_d(sctemp[1],drtemp[1]);printf("\n");

  free(ssc[0].data); free(ssc[1].data); free(ssc);
  free(ssa[0].data); free(ssa[1].data); free(ssa);
  free(ssb[0].data); free(ssb[1].data); free(ssb);

  free(sctemp[0].data);  free(sctemp[1].data); free(sctemp);
  free(srtemp[0].data);  free(srtemp[1].data); free(srtemp);

  
  printf("MM double\n");
  TIMING_COLD(CMC(dc, =, da, mm_leaf_computation_z, db),time_mul,10);
  dctemp = from_z_to_d(dc);

  printf("\n Z MM R w.r.t. Z_DCS MM R  "); d_error_analysis(dctemp[0],drtemp[0]);printf("\n");
  printf("\n Z MM I w.r.t. Z_DCS MM I  "); d_error_analysis(dctemp[1],drtemp[1]);printf("\n");
  
  free(dctemp[0].data);  free(dctemp[1].data);  free(dctemp);


  printf("Winograd double\n");
  TIMING_COLD(CMC(dc, =, da, z_wm                 , db),time_mul,10);
  
  dctemp = from_z_to_d(dc);

  printf("\n Z Winograd R w.r.t. Z_DCS MM R  "); d_error_analysis(dctemp[0],drtemp[0]);printf("\n");
  printf("\n Z Winograd I w.r.t. Z_DCS MM I  "); d_error_analysis(dctemp[1],drtemp[1]);printf("\n");
  
  free(dctemp[0].data);  free(dctemp[1].data);  free(dctemp);

  printf("Winograd-Marco double\n");
  TIMING_COLD(    CMC(dc, =, da, z_bm                 , db),time_mul,10);

  dctemp = from_z_to_d(dc);

  printf("\n Z Winograd-M R w.r.t. Z_DCS MM R  "); d_error_analysis(dctemp[0],drtemp[0]);printf("\n");
  printf("\n Z Winograd-M I w.r.t. Z_DCS MM I  "); d_error_analysis(dctemp[1],drtemp[1]);printf("\n");
  
  free(dctemp[0].data);  free(dctemp[1].data);  free(dctemp);



  printf("DCS MUL double\n");
  TIMING_COLD(CMC(dc, =, da, z_mulpt                , db),time_mul,10);
  dctemp = from_z_to_d(dc);

  printf("\n Z RBC R w.r.t. Z_DCS MM R  "); d_error_analysis(dctemp[0],drtemp[0]);printf("\n");
  printf("\n Z RBC I w.r.t. Z_DCS MM I  "); d_error_analysis(dctemp[1],drtemp[1]);printf("\n");
  
  //  free(dctemp[0].data);  free(dctemp[1].data);  free(dctemp);

  dsc = from_z_to_d(dc);
  dsa = from_z_to_d(da);
  dsb = from_z_to_d(db);

  printf("3M single\n");
  TIMING_COLD(MM3(dctemp[0],dctemp[1],dsa[0],dsa[1],dsb[0],dsb[1],dsc[0],dsc[1],mm_leaf_computation_d, mm_leaf_computation_madd_d, d_ptadd, d_ptadd_t),time_mul,10);
  printf("\n Z_3M GT R  w.r.t. Z_DCS R  ");d_error_analysis(dctemp[0],drtemp[0]);printf("\n");
  printf("\n Z_3M GT I  w.r.t. Z_DCS I  ");d_error_analysis(dctemp[1],drtemp[1]);printf("\n");


  printf("3M Winograd single\n");
  TIMING_COLD(MM3(dctemp[0],dctemp[1],dsa[0],dsa[1],dsb[0],dsb[1],dsc[0],dsc[1],d_wm, d_wmadd, d_ptadd, d_ptadd_t),time_mul,10) ;
  printf("\n Z_3M W GT R  w.r.t. Z_DCS R  ");d_error_analysis(dctemp[0],drtemp[0]);printf("\n");
  printf("\n Z_3M W GT I  w.r.t. Z_DCS I  ");d_error_analysis(dctemp[1],drtemp[1]);printf("\n");


  free(dsc[0].data); free(dsc[1].data); free(dsc);
  free(dsa[0].data); free(dsa[1].data); free(dsa);
  free(dsb[0].data); free(dsb[1].data); free(dsb);




  free(sa.data);
  free(sb.data);
  free(sc.data);

  free(da.data);
  free(db.data);
  free(dc.data);

  return 0;
} 



