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
  C_Matrix cc,ca,cb,ct;
  Z_Matrix zc,za,zb,zt;
  int i,j;
  int diff;

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

  za.trans= ca.trans=da.trans = sa.trans;
  zb.trans= cb.trans=db.trans = sb.trans;
  zc.trans= zc.trans=dc.trans = sc.trans;
  zt.trans= ct.trans=dt.trans = st.trans;

  strcpy(d,"1");
  printf("Beta A \n");
  scanf("%s",d);

  sa.beta=atof(d);
  da.beta = (double) sa.beta;
  ca.beta = sa.beta+I*0;
  za.beta = da.beta+I*0;

  printf("Beta B \n");
  scanf("%s",d);
  printf("Beta C \n");
  scanf("%s",d);

  sb.beta=atof(d);
  db.beta = (double) sb.beta;
  cb.beta = sb.beta+I*0;
  zb.beta = db.beta+I*0;

  
  st.beta=sc.beta=1;
  dt.beta=dc.beta=1;
  ct.beta=cc.beta=1+I*0;
  zt.beta=zc.beta=1+I*0;
  
  printf(" <a.m,a.n,b.m,b.n> ?\n");
  scanf("%d %d %d %d", &sa.M,&sa.N,&sb.M,&sb.N);
  
  da.M =ca.M = za.M = sa.M;
  da.N =ca.N = za.N = sa.N;
  db.M =cb.M = zb.M = sb.M;
  db.N =cb.N = zb.N = sb.N;

  DIST(sa,sb,sc,st);
  DIST(da,db,dc,dt);
  DIST(ca,cb,cc,ct);
  DIST(za,zb,zc,zt);

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
  st.data    = (float *) calloc(st.M*st.N,sizeof(float));
  
  da.data    = (double *) calloc(da.M*da.N,sizeof(double));
  db.data    = (double *) calloc(db.M*db.N,sizeof(double));
  dc.data    = (double *) calloc(dc.M*dc.N,sizeof(double));
  dt.data    = (double *) calloc(dt.M*dt.N,sizeof(double));
  
  ca.data    = (float complex *) calloc(ca.M*ca.N,sizeof(float complex));
  cb.data    = (float complex *) calloc(cb.M*cb.N,sizeof(float complex));
  cc.data    = (float complex *) calloc(cc.M*cc.N,sizeof(float complex));
  ct.data    = (float complex *) calloc(ct.M*ct.N,sizeof(float complex));
  
  za.data    = (double complex*) calloc(za.M*za.N,sizeof(double complex));
  zb.data    = (double complex*) calloc(zb.M*zb.N,sizeof(double complex));
  zc.data    = (double complex*) calloc(zc.M*zc.N,sizeof(double complex));
  zt.data    = (double complex*) calloc(zt.M*zt.N,sizeof(double complex));
  
  
  printf("Initialization ...\n");
  
  s_randomInitialization(sa,rand(),rand());
  s_randomInitialization(sb,rand(),rand());
  s_randomInitialization(sc,rand(),rand());
  
  for (i=0;i<sa.M;i++) 
    for(j=0;j<sa.N;j++) {
      E_(da.data,i,j,da.M,da.N) = E_(sa.data,i,j,sa.M,da.N); 
      
    }
  for (i=0;i<sb.M;i++) 
    for(j=0;j<sb.N;j++) {
      E_(db.data,i,j,db.M,db.N) = E_(sb.data,i,j,sb.M,db.N); 
      
    }
  for (i=0;i<sc.M;i++) 
    for(j=0;j<sc.N;j++) {
      E_(dt.data,i,j,dt.M,dt.N) = E_(dc.data,i,j,da.M,da.N) = E_(sc.data,i,j,sa.M,da.N); 
      
    }


  c_randomInitialization(ca,rand(),rand());
  c_randomInitialization(cb,rand(),rand());
  c_randomInitialization(cc,rand(),rand());

  for (i=0;i<ca.M;i++) 
    for(j=0;j<ca.N;j++) {
      E_(za.data,i,j,za.M,za.N) = E_(ca.data,i,j,ca.M,ca.N); 
      
    }
  for (i=0;i<cb.M;i++) 
    for(j=0;j<cb.N;j++) {
      E_(zb.data,i,j,zb.M,zb.N) = E_(cb.data,i,j,cb.M,db.N); 
      
    }
  for (i=0;i<cc.M;i++) 
    for(j=0;j<cc.N;j++) {
      E_(zt.data,i,j,zt.M,zt.N) = E_(zc.data,i,j,za.M,za.N) 
	= E_(cc.data,i,j,ca.M,da.N); 
      
    }


  for (i=0;i<NUM_THREADS;i++) 
    mask = mask | _T[i];
  sched_setaffinity(0,sizeof(mask),&(mask));


  
  printf("Gotos single");
  TIMING(CMC(sc, =, sa, mm_leaf_computation_s, sb),time_mul,MULINTERVAL);
  printf("Winograd single");
  TIMING(CMC(st, =, sa, s_wm                 , sb),time_mul,MULINTERVAL);

  printf("Gotos double");
  TIMING(CMC(dc, =, da, mm_leaf_computation_d, db),time_mul,MULINTERVAL);
  printf("Winograd double");
  TIMING(CMC(dt, =, da, d_wm                 , db),time_mul,MULINTERVAL);
  
  printf("Gotos complex");
  TIMING(CMC(cc, =, ca, mm_leaf_computation_c, cb),time_mul,MULINTERVAL);
  printf("Winograd complex");
  TIMING(CMC(ct, =, ca, c_wm                 , cb),time_mul,MULINTERVAL);

  
  printf("Gotos complex double");
  TIMING(CMC(zc, =, za, mm_leaf_computation_z, zb),time_mul,MULINTERVAL);
  printf("Winograd complex double");
  TIMING(CMC(zt, =, za, z_wm                 , zb),time_mul,MULINTERVAL);

 
  if ((diff = s_comp(sc,st))) { 
    printf("Error single MM != single WM %d\n",diff);
  }
  if ((diff = comp_s_d(sc,dc))) { 
    printf("Error single MM != double MM %d\n",diff);
  }
  if ((diff = comp_s_d(st,dt))) { 
    printf("Error single WM != double WM %d\n",diff);
  }
  if ((diff = d_comp(dc,dt))) { 
    printf("Error double MM != double WM %d\n",diff);
  }

  if ((diff = c_comp(cc,ct))) { 
    printf("Error single complex MM != single complex WM %d\n",diff);
  }
  if ((diff = comp_c_z(cc,zc))) { 
    printf("Error single complex MM != double complex MM %d\n",diff);
  }
  if ((diff = comp_c_z(ct,zt))) { 
    printf("Error single complex WM != double complex WM %d\n",diff);
  }
  if ((diff = z_comp(zc,zt))) { 
    printf("Error double complex MM != double complex WM %d\n",diff);
  }



  free(sa.data);
  free(sb.data);
  free(sc.data);
  free(st.data);

  free(da.data);
  free(db.data);
  free(dc.data);
  free(dt.data);

  free(ca.data);
  free(cb.data);
  free(cc.data);
  free(ct.data);

  free(za.data);
  free(zb.data);
  free(zc.data);
  free(zt.data);

  return 0;
} 



