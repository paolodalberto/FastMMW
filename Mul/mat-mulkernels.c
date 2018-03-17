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
/*******************************************************************************
 *
 *  MM Kernels
 *
 *
 */

#define MODULO_MAT_MUL

//#define ADAPTIVE
static int LEAF_TEMP;


#include <architecture.h>
#include <mat-operands.h>
#include <mat-mulkernels.h>
#include <mat-addkernels.h>
#include <assert.h>
//#include <scaling.h>
#include <pt.h>

static int debug=0;

// C = A*B classic algorithm 
void mul(DEF(c), DEF(a), DEF(b)) { 
  int i,j;
  int k ;
  Mat temp;


  //  debug=0;
  if (debug) {
    printf(" Stage X \n");
    printf("A \n");
    print(USE(a));
    printf("B \n");
    print(USE(b));
    printf("result MM \n");
    print(USE(c));
  }
  
  if (a.trans=='n' && b.trans=='n') {
# pragma omp parallel for
    for (i=0;i<a.m;i++)
      for (j=0;j<b.n;j++) { 
	temp = 0;
	for (k=0;k<a.n; k++)
	  temp += E_(a.data,i,k,a.M,a.N) * E_(b.data,k,j,b.M,b.N);
	E_(c.data,i,j,c.M,c.N) = temp*a.beta*b.beta;
      }
  }
  if (a.trans=='t' && b.trans=='n') {
# pragma omp parallel for
    for (i=0;i<a.n;i++)
      for (j=0;j<b.n;j++) { 
	temp = 0;
	for (k=0;k<a.m; k++)
	  temp += E_(a.data,k,i,a.M,a.N) * E_(b.data,k,j,b.M,b.N);
	E_(c.data,i,j,c.M,c.N) = temp*a.beta*b.beta;
      }
  }
  if (a.trans=='n' && b.trans=='t') {
# pragma omp parallel for
    for (i=0;i<a.m;i++)
      for (j=0;j<b.m;j++) { 
	temp = 0;
	for (k=0;k<a.n; k++)
	  temp += E_(a.data,i,k,a.M,a.N) * E_(b.data,j,k,b.M,b.N);
	E_(c.data,i,j,c.M,c.N) = temp*a.beta*b.beta;
      }
  }
  if (a.trans=='t' && b.trans=='t') {
# pragma omp parallel for
    for (i=0;i<a.n;i++)
      for (j=0;j<b.m;j++) { 
	temp = 0;
	for (k=0;k<a.m; k++)
	  temp += E_(a.data,k,i,a.M,a.N) * E_(b.data,j,k,b.M,b.N);
	E_(c.data,i,j,c.M,c.N) = temp*a.beta*b.beta;
      }
  }



  if (debug) {

    printf("result C \n");
    print(USE(c));
  }
  //  debug=0;

}

static 
void *basic_mul_computation(void *arg) { 

  int i,j,k;
  DCMul_Data d =  *((DCMul_Data*)arg);
  Matrix c,a,b;
  Mat temp;
  cpu_set_t mask;
  a = d.a;
  b= d.b;
  c = d.c;
  //  printf("D.pi %d \n",d.pi); 
  //printf("D.l %d, D.u %d \n",d.l,d.u); 

  if (d.pi > 0)  {
    int p1;
    CPU_ZERO(&mask);
    CPU_SET(d.pi, &mask);
    //p1 = sched_setaffinity(0,sizeof(d.pi),&(d.pi));
    p1 = sched_setaffinity(0,sizeof(mask),&(mask));
    if (p1<0)  
      printf(" Fail processor setting m\n");
      
  }
  
  mul(USE(c),USE(a),USE(b));
  return 0;
}


void mulpt(DEF(c), DEF(a), DEF(b)) {

  int i,j,l;
  cpu_set_t current_mask; 
  pthread_t  p_thread[NUM_THREADS]; /* thread's structure */
  pthread_attr_t attr;
  int thr_id[NUM_THREADS];
  DCMul_Data d[NUM_THREADS];
  int upper;

  sched_getaffinity(0,sizeof(current_mask),&(current_mask));
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
  
  
#ifdef COLUMN_MAJOR
  upper = b.n;
#endif
#ifdef ROW_MAJOR
  upper = a.m;
#endif

  l = upper/NUM_THREADS;
  
  for (i = 0; i<NUM_THREADS-1 && l>0; i++){
    d[i].pi = _T[i];
    d[i].a = a;
    d[i].b = b;
    d[i].c = c;

    
#ifdef COLUMN_MAJOR
    d[i].c.n = d[i].b.n = l;
    d[i].c.data = c.data+c.M*(i*l);
    d[i].b.data = b.data+b.M*(i*l);
    
#endif
#ifdef ROW_MAJOR
    d[i].c.m = d[i].b.m = l;
    d[i].c.data = c.data+c.N*(i*l);
    d[i].b.data = b.data+b.N*(i*l);

#endif
    if (1) {
      printf(" dcmsum \n");
      print(d[i].c);
      print(d[i].a);
      print(d[i].b);
    }


    
    d[i].l = i*l;
    d[i].u =  (i+1)*l;

    
    //    printf("i %d  d.pi %d and  l %d - u %d\n",i,d[i].pi,d[i].l,d[i].u);
    thr_id[i] = pthread_create(&p_thread[i], 
			       &attr, 
			       basic_mul_computation, 
			       (void *)(&d[i]));
  }

  d[i].pi = _T[i];
  d[i].a = a;
  d[i].b = b;
  d[i].c = c;
  d[i].l = i*l;
#ifdef COLUMN_MAJOR
  if (upper%NUM_THREADS) 
    d[i].c.n = d[i].b.n =  upper - i*l;
  else 
    d[i].c.n = d[i].b.n =  l;
  d[i].c.data = c.data+c.M*(i*l);
  d[i].b.data = b.data+b.M*(i*l);
  
#endif
#ifdef ROW_MAJOR
  if (upper%NUM_THREADS) 
    d[i].c.m = d[i].b.m =  upper - i*l;
  else 
    d[i].c.m = d[i].b.m = l;
  d[i].c.data = c.data+c.N*(i*l);
  d[i].b.data = b.data+b.N*(i*l);

#endif
  if (1) {
    printf(" dcmsum \n");
    print(d[i].c);
    print(d[i].a);
    print(d[i].b);
  }
  

  //  printf("i %d  d.pi %d and  l %d - u %d\n",i,d[i].pi,d[i].l,d[i].u);
    
  basic_mul_computation((void*) &d[i]);
  
  for (i = 0; i<NUM_THREADS-1 && l>0; i++){
    pthread_join(p_thread[i], NULL);
  }
 

  sched_setaffinity(0,sizeof(current_mask),&(current_mask));
  
}


// C = A*B classic algorithm 
void madd(DEF(c), DEF(a), DEF(b)) { 
  int i,j;
  int k ;
  Mat temp;


  //  debug=0;
  if (debug) {
    printf(" Stage X \n");
    printf("A \n");
    print(USE(a));
    printf("B \n");
    print(USE(b));
    printf("result MM \n");
    print(USE(c));
  }
  
  if (a.trans=='n' && b.trans=='n') {
# pragma omp parallel for
    for (i=0;i<a.m;i++)
      for (j=0;j<b.n;j++) { 
	temp =  0; 
	for (k=0;k<a.n; k++)
	  temp += E_(a.data,i,k,a.M,a.N) * E_(b.data,k,j,b.M,b.N);
	E_(c.data,i,j,c.M,c.N) = temp*a.beta*b.beta + c.beta*E_(c.data,i,j,c.M,c.N);
      }
  }
  if (a.trans=='t' && b.trans=='n') {
# pragma omp parallel for
    for (i=0;i<a.n;i++)
      for (j=0;j<b.n;j++) { 
	temp =  0;
	for (k=0;k<a.m; k++)
	  temp += E_(a.data,k,i,a.M,a.N) * E_(b.data,k,j,b.M,b.N);
	E_(c.data,i,j,c.M,c.N) = temp*a.beta*b.beta+ c.beta*E_(c.data,i,j,c.M,c.N);
      }
  }
  if (a.trans=='n' && b.trans=='t') {
# pragma omp parallel for
    for (i=0;i<a.m;i++)
      for (j=0;j<b.m;j++) { 
	temp =  0;
	for (k=0;k<a.n; k++)
	  temp += E_(a.data,i,k,a.M,a.N) * E_(b.data,j,k,b.M,b.N);
	E_(c.data,i,j,c.M,c.N) = temp*a.beta*b.beta+ c.beta*E_(c.data,i,j,c.M,c.N);
      }
  }
  if (a.trans=='t' && b.trans=='t') {
# pragma omp parallel for
    for (i=0;i<a.n;i++)
      for (j=0;j<b.m;j++) { 
	temp =  0;
	for (k=0;k<a.m; k++)
	  temp += E_(a.data,k,i,a.M,a.N) * E_(b.data,j,k,b.M,b.N);
	E_(c.data,i,j,c.M,c.N) = temp*a.beta*b.beta+ c.beta*E_(c.data,i,j,c.M,c.N);
      }
  }

  if (debug) {

    printf("result C \n");
    print(USE(c));
  }
  //  debug=0;

}


static int recursive =0;
static int dept=0;



// Strassen C = A*B
int smul(DEF(c), DEF(a), DEF(b)) {
  
  c.beta =1;
  if (debug)
    printf("smul C[%c]=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);
#ifdef ADAPTIVE
  if (debug)
    printf("smul %d < %d  thus %d \n",(BR_LEFT(a.m,a.n,b.n,LEAF_TEMP)),(BR_RIGHT(a.m,a.n,b.n,LEAF_TEMP)),BR_P(a.m,a.n,b.n,LEAF_TEMP));
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation , USE(b));
#ifdef SCALING
    slowCPU();
#endif

  }
  else {
#ifndef CLBLAS
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta}; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),'n',0}; // temporary 
#else
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta,c.gpu}; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta,c.gpu}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),'n',0,c.gpu}; // temporary 
#endif
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c);
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    dept+=3;
    recursive = max(recursive,dept);

    // temporary allocation 
    t1.data = (Mat *) calloc(Size(t1.M,t1.N),sizeof(Mat));
    t2.data = (Mat *) calloc(Size(t2.M,t2.N),sizeof(Mat));
    m.data  =  (Mat *) calloc(Size(m.M,m.N), sizeof(Mat));


    /* T2  = B1-B3   */    CMC (RQ1(t2,b),=, tb1, s_sub,  tb3);
    /* MM3 = A0*T2   */    CMC (RQ1(m,c), =, ta0, smul, RQ1(t2,b));
    /* C1  = M3      */    copy(tc1, RQ1(m,c)); 
    /* C3  = M3      */    copy(tc3, RQ3(m,c));
    
    /* T1 = A2 - A0  */    CMC(t1,    =, ta2, s_sub,  ta0);
    /* T2 = B0 + B1  */    CMC(t2,    =, tb0, s_add,  tb1);
    /* MM6 = T1 * T2 */    CMC(m,     =, t1,  smul,   t2);
    /* C3  += M6     */    CMC(tc3,   =, tc3, s_add,  RQ3(m,c));
    
    /* T1  = A2 + A3 */    CMC(RQ2(t1,a),=, ta2,       s_add,   ta3);
    /* MM2 = T1 * B0 */    CMC(RQ2(m,c) ,=, RQ2(t1,a), smul ,   tb0);
    /* C3  -= M2     */    CMC(tc3,      =, tc3,       s_sub,   RQ3(m,c));
    /* C2  =  M2     */    copy(tc2, RQ2(m,c));
    
    /* T1  = A0 + A3 */    CMC(t1,    =, ta0, s_add,  ta3);
    /* T2  = B0 + B3 */    CMC(t2,    =, tb0, s_add,  tb3);
    /* MM1 = T1*T2   */    CMC(m,     =, t1,  smul, t2);
    /* C3  += M1     */    CMC(tc3,   =, tc3, s_add,  RQ3(m,c));
    /* C0  = M1      */    copy(tc0,m);
    
    /* T1 = A0 + A1 */     CMC(RQ1(t1,a),=, ta0,       s_add,   ta1);
    /* MM5 = T1 * B3 */    CMC(RQ1(m,c), =, RQ1(t1,a), smul,    tb3);
    /* C0  -= M5     */    CMC(tc0,      =, tc0,       s_sub,   RQ1(m,c));
    /* C1  += M5     */    CMC(tc1,      =, tc1,       s_add,   RQ1(m,c));
    
    /* T1 = A1 - A3 */     CMC(RQ1(t1,a),=, ta1,    s_sub,  ta3);
    /* T2 = B2 + B3 */     CMC(RQ2(t2,b),=, tb2,    s_add,  tb3);
    /* MM7 = T1*T2  */     CMC(m,        =, RQ1(t1,a),smul, RQ2(t2,b));
    /* C0  += M7    */     CMC(tc0,    =, tc0,    s_add,  m);
    
    /* T1 = B2 - B0 */     CMC(RQ2(t2,b),      =, tb2, s_sub,  tb0);
    /* MM4 = A3*T1  */     CMC(RQ2(m,c), =, ta3, smul, RQ2(t2,b));
    /* C0  += M4    */     CMC(tc0,             =, tc0, s_add,  RQ2(m,c)); 
    /* C2  += M4    */     CMC(tc2,             =, tc2, s_add,  RQ2(m,c));
    
    
    free(t1.data);
    free(t2.data);
    free(m.data);
  }
  dept-=3;
  return recursive;
}


  // Strassen C+=A*B 
int saddmul(DEF(c), DEF(a), DEF(b)) {

  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
#ifdef SCALING
    slowCPU();
#endif
    
  }
  else {
#ifndef CLBLAS
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta}  ; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),'n',1}; // temporary
#else
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta,c.gpu}  ; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta,c.gpu}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),'n',1,c.gpu}; // temporary
#endif
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c);
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    dept+=3;
    recursive = max(recursive,dept);
    
    // temporary allocation 
    t1.data = (Mat *) calloc(Size(t1.M,t1.N),sizeof(Mat));
    t2.data = (Mat *) calloc(Size(t2.M,t2.N),sizeof(Mat));
    m.data  =  (Mat *) calloc(Size(m.M,m.N), sizeof(Mat));
    
    
    /* T2  = B1-B3   */    CMC (RQ1(t2,b),=, tb1, s_sub,  tb3);
    /* MM3 = A0*T2   */    CMC (RQ1(m,c), =, ta0, smul,   RQ1(t2,b));
    /* *C1  += M3    */    CMC (tc1,      =, tc1, s_add_t,  RQ1(m,c)) ; tc1.beta=1;
    /* *C3  += M3    */    CMC (tc3,      =, tc3, s_add_t,  RQ3(m,c)) ; tc3.beta=1;
    
    /* T1 = A2 - A0  */    CMC(t1,   =, ta2, s_sub,  ta0);
    /* T2 = B0 + B1  */    CMC(t2,   =, tb0, s_add,  tb1);
    /* MM6 = T1 * T2 */    CMC(m,    =, t1,  smul,   t2);
    /* C3  += M6     */    CMC(tc3,  =, tc3, s_add,  RQ3(m,c));
    
    /* T1  = A2 + A3 */    CMC(RQ2(t1,a), =, ta2,       s_add,   ta3);
    /* MM2 = T1 * B0 */    CMC(RQ2(m,c) , =, RQ2(t1,a), smul ,   tb0);
    /* C3  -= M2     */    CMC(tc3,       =, tc3,       s_sub,   RQ3(m,c));
    /* *C2  += M2    */    CMC(tc2,       =, tc2,       s_add_t,   RQ2(m,c)); tc2.beta=1;
    
    /* T1  = A0 + A3 */    CMC(t1,  =, ta0, s_add,  ta3);
    /* T2  = B0 + B3 */    CMC(t2,  =, tb0, s_add,  tb3);
    /* MM1 = T1*T2   */    CMC(m,   =, t1,  smul,  t2);
    /* C3  += M1     */    CMC(tc3, =, tc3, s_add,  RQ3(m,c));
    /* *C0  += M1    */    CMC(tc0, =, tc0, s_add_t,  m);              tc0.beta=1;

    /* T1 = A0 + A1 */     CMC(RQ1(t1,a),=, ta0,       s_add,   ta1);
    /* MM5 = T1 * B3 */    CMC(RQ1(m,c), =, RQ1(t1,a), smul,    tb3);
    /* C0  -= M5     */    CMC(tc0,      =, tc0,       s_sub,   RQ1(m,c));
    /* C1  += M5     */    CMC(tc1,      =, tc1,       s_add,   RQ1(m,c));
    
    /* T1 = A1 - A3 */     CMC(RQ1(t1,a),=, ta1,       s_sub,  ta3);
    /* T2 = B2 + B3 */     CMC(RQ2(t2,b),=, tb2,       s_add,  tb3);
    /* MM7 = T1*T2  */     CMC(m,        =, RQ1(t1,a), smul,   RQ2(t2,b));
    /* C0  += M7    */     CMC(tc0,      =, tc0,       s_add,  m);
    
    /* T1 = B2 - B0 */     CMC(RQ2(t2,b), =, tb2, s_sub,  tb0);
    /* MM4 = A3*T1  */     CMC(RQ2(m,c),  =, ta3, smul,   RQ2(t2,b));
    /* C0  += M4    */     CMC(tc0,       =, tc0, s_add,  RQ2(m,c)); 
    /* C2  += M4    */     CMC(tc2,       =, tc2, s_add,  RQ2(m,c));

    
    free(t1.data);
    free(t2.data);
    free(m.data);
  }
  dept-=3;
  return recursive;
  
}





// Strassen Adaptive
 static 
int smul_ADA(DEF(c), DEF(a), DEF(b)) {
  c.beta = 0;
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation , USE(b));
#ifdef SCALING
    slowCPU();
#endif
    
  }
  else {
#ifndef CLBLAS
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta}  ; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,0}; // temporary
#else
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta,c.gpu}  ; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta,c.gpu}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,0,c.gpu}; // temporary
#endif
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c);
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);

    dept++;
    recursive = max(recursive,dept);
 
    // temporary allocation 
    t1.data = (Mat *) calloc(Size(t1.M,t1.N),sizeof(Mat));
    t2.data = (Mat *) calloc(Size(t2.M,t2.N),sizeof(Mat));
    m.data  = (Mat *) calloc(Size(m.M,m.N), sizeof(Mat));
    

    /* T2  = B1-B3   */    CMC (RQ1(t2,b),=, tb1, s_sub,  tb3);
    /* MM3 = A0*T2   */    CMC (RQ1(m,c), =, ta0, smul,   RQ1(t2,b));
    /* C1  = M3      */    copy(tc1, RQ1(m,c));
    /* C3  = M3      */    copy(tc3, RQ3(m,c));
    
    /* T1 = A2 - A0  */    CMC(t1,  =, ta2, s_sub,  ta0);
    /* T2 = B0 + B1  */    CMC(t2,  =, tb0, s_add,  tb1);
    /* MM6 = T1 * T2 */    CMC(m,   =, t1,  smul,   t2);
    /* C3  += M6     */    CMC(tc3, =, tc3, s_add,  RQ3(m,c));
    
    /* T1  = A2 + A3 */    CMC(RQ2(t1,a),=, ta2,       s_add,   ta3);
    /* MM2 = T1 * B0 */    CMC(RQ2(m,c) ,=, RQ2(t1,a), smul ,   tb0);
    /* C3  -= M2     */    CMC(tc3,      =, tc3,       s_sub,   RQ3(m,c));
    /* C2  =  M2     */    copy(tc2, RQ2(m,c));
    
    /* T1  = A0 + A3 */    CMC(t1,  =, ta0, s_add,  ta3);
    /* T2  = B0 + B3 */    CMC(t2,  =, tb0, s_add,  tb3);
    /* MM1 = T1*T2   */    CMC(m,   =, t1,   smul,  t2);
    /* C3  += M1     */    CMC(tc3, =, tc3, s_add,  RQ3(m,c));
    /* C0  = M1      */    copy(tc0,m);

    /* T1 = A0 + A1 */     CMC(RQ1(t1,a),=, ta0,       s_add,   ta1);
    /* MM5 = T1 * B3 */    CMC(RQ1(m,c), =, RQ1(t1,a), smul,    tb3);
    /* C0  -= M5     */    CMC(tc0,      =, tc0,       s_sub,   RQ1(m,c));
    /* C1  += M5     */    CMC(tc1,      =, tc1,       s_add,   RQ1(m,c));
    
    /* T1 = A1 - A3 */     CMC(RQ1(t1,a),=, ta1,       s_sub,  ta3);
    /* T2 = B2 + B3 */     CMC(RQ2(t2,b),=, tb2,       s_add,  tb3);
    /* MM7 = T1*T2  */     CMC(m,        =, RQ1(t1,a), smul,   RQ2(t2,b));
    /* C0  += M7    */     CMC(tc0,      =, tc0,       s_add,  m);
    
    /* T1 = B2 - B0 */     CMC(RQ2(t2,b), =, tb2, s_sub,  tb0);
    /* MM4 = A3*T1  */     CMC(RQ2(m,c),  =, ta3, smul,   RQ2(t2,b));
    /* C0  += M4    */     CMC(tc0,       =, tc0, s_add,  RQ2(m,c)); 
    /* C2  += M4    */     CMC(tc2,       =, tc2, s_add,  RQ2(m,c));
    
    
    free(t1.data);
    free(t2.data);
    free(m.data);
  }
  
  dept--;
  return recursive;
}

// Interface for the above
int adaptive_smul(DEF(c), DEF(a), DEF(b), int alpha_pi) {
  
  LEAF_TEMP=alpha_pi;
  recursive = 0;
  recursive = (CMC(USE(c), = , USE(a),  smul , USE(b)));
  return recursive;
  
}


// Winograd's matrix multiply 
// Notation and order taken from  
// http://www.cs.duke.edu/~alvy/papers/sc98/index.htm
 
int wmul(DEF(c), DEF(a), DEF(b)) {

  c.beta =1;

  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation , USE(b));
#ifdef SCALING
    slowCPU();
#endif
    
  }
  else {
#ifndef CLBLAS
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n)   ,a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n)   ,b.trans,b.beta}; 
    Matrix p  = {0, S0(c.m,c.n),S0(c.m,c.n)  ,'n',1}; // temporary
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n) ,'n',1}; // temporary
#else
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n)   ,a.trans,a.beta,c.gpu}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n)   ,b.trans,b.beta,c.gpu}; 
    Matrix p  = {0, S0(c.m,c.n),S0(c.m,c.n)  ,'n',1,c.gpu}; // temporary
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n) ,'n',1,c.gpu}; // temporary
#endif
    
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    p.data  =  (Mat *) CALLOC(p);
    u2.data  =  (Mat *) CALLOC(u2);
    
    /* P1 */
    /* P = A0*B0   */    CMC (RQ0(u2,c), =, ta0, wmul, tb0);
    /* C0  = P     */    copy(tc0    , u2);
    /* U2  = P        copy(u2, p); */
    
    /* P2 */
    /* P = A1 * B2 */    CMC(p,   =, ta1, wmul,   tb2);
    /* C0  += P    */    CMC(tc0, =, tc0, s_add,  p);
    
    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a), =, ta2,      s_add,   ta3);
    /* T = B1 - B0 */    CMC(t,        =, tb1,      s_sub,   tb0);
    /* P = S * T   */    CMC(RQ2(p,c) ,=, RQ2(s,a), wmul ,   t);
    /* C3  =  P    */    copy(tc3, RQ3(p,c));
    /* C1  =  P    */    copy(tc1, RQ3(p,c));
    
    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a),   s_sub,  ta0);
    /* T  = B3 - T */    CMC(t,    =, tb3,        s_sub,  t);
    /* P = S*T   */      CMC(p,    =, s,          wmul, t);
    /* U3 =U2 +=P */     CMC(u2,   =, u2,         s_add,  p);
    /* C1 +=U2, */       CMC(tc1,  =, RQ3(tc1,c), s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s,        =, ta1,       s_sub,   s);
    /* P = S * B3 */     CMC(RQ1(p,c), =, RQ1(s,a),  wmul,    tb3);
    /* C1  += P     */   CMC(tc1,      =, tc1,       s_add,   RQ1(p,c));
    
    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* P = A3*T  */      CMC(RQ2(p,c), =, ta3,    wmul,   RQ2(t,b));
    /* C2 = P    */      copy(tc2, RQ2(p,c));
    
    /* P5 */
    /* S = A0 - A2 */     CMC(s,        =, ta0,     s_sub,  ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b), =, tb3,     s_sub,  tb1);
    /* P = S*T     */     CMC(RQ1(p,c), =, s,  wmul,   RQ1(t,b));
    /* U3  += P    */     CMC(u2,       =, u2, s_add,  RQ1(p,c)); 
    /* C3  += U3   */     CMC(tc3,      =, tc3,     s_add,  RQ3(u2,c));
    /* C2  += U3   */     CMC(tc2,      =, RQ2(u2,c),     s_add,  tc2); 
    
    
    FREE(s.data);
    FREE(t.data);
    FREE(p.data);
    FREE(u2.data);
    
  }
  dept--;
  return recursive;
  
}


int waddmul(DEF(c), DEF(a), DEF(b)) {


  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
#ifdef SCALING
    slowCPU();
#endif
    
  }
  else {
#ifndef CLBLAS
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n)   ,a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n)   ,b.trans,b.beta}; 
    Matrix p  = {0, S0(c.m,c.n),S0(c.m,c.n)  ,'n',1}; // temporary
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n) ,'n',1}; // temporary
#else
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n)   ,a.trans,a.beta,c.gpu}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n)   ,b.trans,b.beta,c.gpu}; 
    Matrix p  = {0, S0(c.m,c.n),S0(c.m,c.n)  ,'n',1,c.gpu}; // temporary
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n) ,'n',1,c.gpu}; // temporary
#endif
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    p.data  =  (Mat *) CALLOC(p);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data && p.data && u2.data);
    
    /* P1 */
    /* P = A0*B0   */    CMC (u2,  =, ta0, wmul, tb0);
    /* *C0  += P   */    CMC (tc0, =, tc0, s_add_t , u2); tc0.beta =1;
    /* U2  = P     copy(u2, p); */
    
    /* P2 */
    /* P = A1 * B2 */    CMC(p,   =, ta1, wmul,   tb2);
    /* C0  += P    */    CMC(tc0, =, tc0, s_add,  p);
    
    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),=, ta2,      s_add,   ta3);
    /* T = B1 - B0 */    CMC(t,       =, tb1,      s_sub,   tb0);
    /* P = S * T   */    CMC(RQ2(p,c),=, RQ2(s,a), wmul ,   t);
    /* *C3  +=  P  */    CMC (tc3   , =, tc3,      s_add_t ,    RQ3(p,c));  tc3.beta =1;
    /* *C1  +=  P  */    CMC (tc1   , =, tc1,      s_add_t ,    RQ3(p,c));  tc1.beta =1;
    
    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a),   s_sub,  ta0); 
    /* T  = B3 - T */    CMC(t,    =, tb3,        s_sub,  t);
    /* P = S*T   */      CMC(p,    =, s,          wmul,   t);
    /* U3 =U2 +=P */     CMC(u2,   =, u2,         s_add,  p);
    /* C1 +=U2, */       CMC(tc1,  =, tc1, s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s,        =, ta1,      s_sub,   s);
    /* P = S * B3 */     CMC(RQ1(p,c), =, RQ1(s,a), wmul,    tb3);
    /* C1  += P     */   CMC(tc1,      =, tc1,      s_add,   RQ1(p,c));
    
    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* P = A3*T  */      CMC(RQ2(p,c), =, ta3,    wmul,   RQ2(t,b));
    /* *C2 += P  */      CMC (tc2   ,  =, tc2,    s_add_t ,   RQ2(p,c));  tc2.beta =1;
    
    /* P5 */
    /* S = A0 - A2 */     CMC(s,        =, ta0,       s_sub,  ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b), =, tb3,       s_sub,  tb1);
    /* P = S*T     */     CMC(RQ1(p,c), =, s,         wmul,   RQ1(t,b));
    /* U3  += P    */     CMC(u2,       =, u2,        s_add,  RQ1(p,c)); 
    /* C3  += U3   */     CMC(tc3,      =, tc3,       s_add,  RQ3(u2,c));
    /* C2  += U3   */     CMC(tc2,      =, RQ2(u2,c), s_add,  tc2); 
    
    
    FREE(s.data);
    FREE(t.data);
    FREE(p.data);
    FREE(u2.data);
    
  }
  dept--;
  return recursive;
  
}

//#define PAOLOISALWAYSWRONG 1

#ifdef PAOLOISALWAYSWRONG
  // Winograd's matrix multiply 
  // Notation and order taken from  
  // http://www.cs.duke.edu/~alvy/papers/sc98/index.htm
 
 
int wmadd(DEF(c), DEF(a), DEF(b)) {
  
  if (debug)  printf("wmadd C[%c]=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
#ifdef SCALING
    slowCPU();
#endif
    
  }
  else {
#ifndef CLBLAS
    Matrix s =   {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
    Matrix t =   {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix u3  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
#else
    Matrix s =   {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta,c.gpu};   
    Matrix t =   {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta,c.cpu};   
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1,c.cpu}; // temporary
    Matrix u3  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1,c.cpu}; // temporary
#endif
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    u3.data  =  (Mat *) CALLOC(u3);
    assert(s.data && t.data  && u2.data);
    
    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),  =, ta2,      s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,        =, tb1,      s_sub,   tb0);
    /* U2 = S * T   */   CMC(RQ2(u2,c) ,=, RQ2(s,a), wm ,     t);
    
    /* *C3 +=  U2 */     CMC(tc3 ,=, tc3, s_add_t ,   RQ3(u2,c)); tc3.beta = 1;
    /* *C1 +=  U2 */     CMC(tc1 ,=, tc1, s_add_t ,   RQ1(u2,c)); tc1.beta = 1;
    
    /* P1 */
    /* U2 = A0*B0   */    CMC (u2, =, ta0, wm, tb0);

    /* C0  += U2 +C0 */   CMC(tc0, =, tc0, s_add_t, u2); tc0.beta = 1;
    
    /* P2 */
    /* C0 += A1 * B2 */   CMC(tc0,  =, ta1, wmadd,   tb2);
    
    
    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a), s_sub,  ta0);
    /* T  = B3 - T */    CMC(t,    =, tb3,    s_sub,  t);
    
    /* U2 += S*T   */    CMC(u2,    =, s, wmadd, t);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
    /* C1 += S * B3 */   CMC(tc1, =, RQ1(s,a),  wmadd,    tb3);
    
    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* C2 += A3*T  */    CMC(tc2, =, ta3,    wmadd,   RQ2(t,b)); tc2.beta = 1;
    
    /* P5 */
    /* S = A0 - A2 */     CMC(s,         =, ta0,       s_sub,   ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b),  =, tb3,       s_sub,   tb1);
    /* U2 += S*T     */   CMC(RQ1(u2,c), =, s,         wmadd,   RQ1(t,b));
    /* C3  += U2   */     CMC(tc3,       =, tc3,       s_add,   RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,       =, RQ2(u2,c), s_add,   tc2); 
    
    
 
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);
    FREE(u3.data);
    
  }
  dept--;
  return recursive;
  
}



int wm(DEF(c), DEF(a), DEF(b)) {
  c.beta = 1;
  
  if (debug)  printf("wm C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
#ifdef SCALING
    slowCPU();
#endif
    
  }
  else {
#ifndef CLBLAS
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
#else
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta,c.gpu}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta,c.gpu}; 
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1,c.gpu}; // temporary
#endif
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data  && u2.data);
    
    
    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),=, ta2,     s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,=, tb1,     s_sub,   tb0);
    /* U2 = S * T   */   CMC(RQ2(u2,c) ,=, RQ2(s,a), wm ,   t);
    /* C1 +=  U2    */   copy(tc1 ,   RQ1(u2,c));
    /* C3 +=  U2    */   copy(tc3,  RQ3(u2,c));
    
    /* P1 */
    /* C0 = A0*B0   */    CMC (tc0, =, ta0, wm, tb0);
    /* U2  = C0     */    copy(u2,tc0);
    
    /* P2 */
    /* C0 += A1 * B2 */    CMC(tc0,  =, ta1, wmadd,   tb2);
    

    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a), s_sub,  ta0);
    /* T  = B3 - T */    CMC(t,    =, tb3,    s_sub,  t);
    /* U2 += S*T   */    CMC(u2,    =, s, wmadd, t);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
    /* C1 += S * B3 */   CMC(tc1, =, RQ1(s,a),  wmadd,    tb3);
    
    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* C2 = A3*T  */      CMC(tc2, =, ta3,    wm,   RQ2(t,b));
    
    /* P5 */
    /* S = A0 - A2 */     CMC(s,     =, ta0,     s_sub,  ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b),     =, tb3,     s_sub,  tb1);
    /* U2 += S*T     */   CMC(RQ1(u2,c),     =, s,  wmadd,   RQ1(t,b));
    /* C3  += U2   */     CMC(tc3,        =, tc3,     s_add,  RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,        =, RQ2(u2,c),     s_add,  tc2); 
    
    
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);
    
  }
  dept--;
  return recursive;
  
}

#endif



// Cache oblivious + Strassen C+=A*B
void oaddmul(DEF(c), DEF(a), DEF(b)) { 
  
  if (a.m>= DEFORM_FACTOR_AM*max(a.n,b.n)) { 
    /* A is tall */
    CMC( VD0(c), =, VD0(a), oaddmul, b);
    CMC( VD1(c), =, VD1(a), oaddmul, b);
    
  } else if (a.n >= DEFORM_FACTOR_AN*max(a.m,b.n)) { 
    /* A is fat and B is tall */
    CMC(c, =, HD0(a), oaddmul,    VD0(b));
    CMC(c, =, HD1(a), oaddmul, VD1(b));
    
  } else if (b.n>=DEFORM_FACTOR_BN*max(a.m,a.n)) {
    CMC( HD0(c), =, a, oaddmul, HD0(b));
    CMC( HD1(c), =, a, oaddmul, HD1(b));
    
  } else CMC(c,=, a, saddmul , b);
  
}

// Cache oblivious + Strassen C=A*B
void omul(DEF(c), DEF(a), DEF(b)) { 
   
  if (a.m>= DEFORM_FACTOR_AM*max(a.n,b.n)) {     /* A is tall */
    CMC( VD0(c), =, VD0(a), omul, b);
    CMC( VD1(c), =, VD1(a), omul, b);
    
  } else if (a.n >= DEFORM_FACTOR_AN*max(a.m,b.n)) {     /* A is fat and B is tall */
    CMC(c, =, HD0(a), omul,    VD0(b));
    CMC(c, =, HD1(a), oaddmul, VD1(b));
    
  } else if (b.n>=DEFORM_FACTOR_BN*max(a.m,a.n)) {    
    CMC( HD0(c), =, a, omul, HD0(b));
    CMC( HD1(c), =, a, omul, HD1(b));
  } else CMC(c,=, a, smul , b);
  
}
 
// Cache oblivious + Strassen C+=A*B
void owaddmul(DEF(c), DEF(a), DEF(b)) { 
  
  if (a.m>= DEFORM_FACTOR_AM*max(a.n,b.n)) { 
    /* A is tall */
    CMC( VD0(c), =, VD0(a), owaddmul, b);
    CMC( VD1(c), =, VD1(a), owaddmul, b);
    
  } else if (a.n >= DEFORM_FACTOR_AN*max(a.m,b.n)) { 
    /* A is fat and B is tall */
    CMC(c, =, HD0(a), owaddmul,    VD0(b));
    CMC(c, =, HD1(a), owaddmul, VD1(b));
    
  } else if (b.n>=DEFORM_FACTOR_BN*max(a.m,a.n)) {
    CMC( HD0(c), =, a, oaddmul, HD0(b));
    CMC( HD1(c), =, a, oaddmul, HD1(b));
    
  } else CMC(c,=, a, waddmul , b);
  
}

// Cache oblivious + Strassen C=A*B
void owmul(DEF(c), DEF(a), DEF(b)) { 

  if (a.m>= DEFORM_FACTOR_AM*max(a.n,b.n)) {     /* A is tall */
    CMC( VD0(c), =, VD0(a), owmul, b);
    CMC( VD1(c), =, VD1(a), owmul, b);
    
  } else if (a.n >= DEFORM_FACTOR_AN*max(a.m,b.n)) {     /* A is fat and B is tall */
    CMC(c, =, HD0(a), owmul,    VD0(b));
    CMC(c, =, HD1(a), owaddmul, VD1(b));
    
  } else if (b.n>=DEFORM_FACTOR_BN*max(a.m,a.n)) {    
    CMC( HD0(c), =, a, owmul, HD0(b));
    CMC( HD1(c), =, a, owmul, HD1(b));
  } else CMC(c,=, a, wmul , b);
  
}
 


// Winograd's matrix multiply 
// Notation and order taken from  
// http://www.cs.duke.edu/~alvy/papers/sc98/index.htm
 
#define PAOLOISALWAYSRIGHT 1




#ifdef PAOLOISALWAYSRIGHT

int wmadd(DEF(c), DEF(a), DEF(b)) {
  if (debug)  printf("wmadd C[%c]=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d (%d,%d) += (%d,%d) (%d,%d)\n",
		     c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n, c.M,c.N,a.M,a.N,b.M,b.N);
  
    
#ifdef ADAPTIVE
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
    if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
      fastCPU();
#endif
      CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
#ifdef SCALING
      slowCPU();
#endif
      
    }
    else {
#ifndef CLBLAS
      Matrix s =   {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
      Matrix t =   {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
      Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
#else
      Matrix s =   {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta,c.gpu};   
      Matrix t =   {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta,c.gpu};   
      Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1,c.gpu}; // temporary
#endif
      Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
      Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
      Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);

      // temporary allocation 
      s.data = (Mat *) CALLOC(s);
      t.data = (Mat *) CALLOC(t);
      u2.data  =  (Mat *) CALLOC(u2);
      assert(s.data && t.data  && u2.data);
      
      /* P3 */
      /* S = A2 + A3 */    CMC(RQ2(s,a),  =, ta2,      s_add,   ta3);
      /* T = B1 - B0 */    CMC(t ,        =, tb1,      s_sub,   tb0);
      /* U2 = S * T   */   CMC(RQ2(u2,c) ,=, RQ2(s,a), wm ,     t);
      /* *C3 +=  U2 */     CMC(tc3 ,=, tc3, s_add_t ,   RQ3(u2,c)); tc3.beta = 1;
      /* *C1 +=  U2 */     CMC(tc1 ,=, tc1, s_add_t ,   RQ1(u2,c)); tc1.beta = 1;
      
      /* P1 */
      /* U2 = A0*B0   */    CMC (u2, =, ta0, wm, tb0);
      /* C0  += U2    */   CMC(tc0, =, tc0, s_add_t, u2); tc0.beta = 1;
      
      /* P2 */
      /* C0 += A1 * B2 */   CMC(tc0,  =, ta1, wmadd,   tb2);
      
      /* P4 */
      /* S  = S - A0 */    CMC(s,    =, RQ2(s,a), s_sub,  ta0);
      /* T  = B3 - T */    CMC(t,    =, tb3,    s_sub,  t);
      /* U2 += S*T   */    CMC(u2,    =, s, wmadd, t);
      /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
      
      /* P6 */
      /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
      /* C1 += S * B3 */   CMC(tc1, =, RQ1(s,a),  wmadd,    tb3);
      
      /* P7 */
      /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
      /* C2 += A3*T  */    CMC(tc2, =, ta3,    wmadd,   RQ2(t,b)); tc2.beta = 1;
      
      /* P5 */
      /* S = A0 - A2 */     CMC(s,         =, ta0,       s_sub,   ta2);
      /* T = B3 - B1 */     CMC(RQ1(t,b),  =, tb3,       s_sub,   tb1);
      /* U2 += S*T     */   CMC(RQ1(u2,c), =, s,         wmadd,   RQ1(t,b));
      /* C3  += U2   */     CMC(tc3,       =, tc3,       s_add,   RQ3(u2,c));
      /* C2  += U2   */     CMC(tc2,       =, RQ2(u2,c), s_add,   tc2); 
      
      FREE(s.data);
      FREE(t.data);
      FREE(u2.data);
      
    }
    dept--;
    return recursive;
    
  }


    
int wm(DEF(c), DEF(a), DEF(b)) {
  
  c.beta = 1;
  if (debug)  printf("wm C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d (%d,%d) += (%d,%d) (%d,%d)\n",
		     c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n, c.M,c.N,a.M,a.N,b.M,b.N);
  
  
#ifdef ADAPTIVE
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
    //     printf("%d \n",BR_P(a.m,a.n,b.n,LEAF_TEMP));
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
#ifdef SCALING
    slowCPU();
#endif
      
  }
  else {
#ifndef CLBLAS      
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
#else
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta,c.gpu}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta,c.gpu}; 
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1,c.gpu}; // temporary
#endif
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data  && u2.data);
      
    
    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),=, ta2,     s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,=, tb1,     s_sub,   tb0);
    /* U2 = S * T   */   CMC(RQ2(u2,c) ,=, RQ2(s,a), wm ,   t);
    /* C1 +=  U2    */   copy(tc1 ,   RQ1(u2,c));
    /* C3 +=  U2    */   copy(tc3,  RQ3(u2,c));
    
    /* P1 */
    /* C0 = A0*B0   */    CMC (tc0, =, ta0, wm, tb0);
    /* U2  = C0     */    copy(u2,tc0);
    
    /* P2 */
    /* C0 += A1 * B2 */    CMC(tc0,  =, ta1, wmadd,   tb2);
    
    
    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a), s_sub,  ta0);
    /* T  = B3 - T */    CMC(t,    =, tb3,    s_sub,  t);
    /* U2 += S*T   */    CMC(u2,    =, s, wmadd, t);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
    /* C1 += S * B3 */   CMC(tc1, =, RQ1(s,a),  wmadd,    tb3);
    
    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* C2 = A3*T  */      CMC(tc2, =, ta3,    wm,   RQ2(t,b));
    
    /* P5 */
    /* S = A0 - A2 */     CMC(s,     =, ta0,     s_sub,  ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b),     =, tb3,     s_sub,  tb1);
    /* U2 += S*T     */   CMC(RQ1(u2,c),     =, s,  wmadd,   RQ1(t,b));
    /* C3  += U2   */     CMC(tc3,        =, tc3,     s_add,  RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,        =, RQ2(u2,c),     s_add,  tc2); 
    
    
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);
    
  }
  dept--;
  return recursive;
  
}
// Interface for the above
int adaptive_wm(DEF(c), DEF(a), DEF(b), int alpha_pi) {
  //debug=1;
  //  print(a);
  //print(b);
  //print(c);
  LEAF_TEMP=alpha_pi;
    if (debug) 
      printf("alpha/pi %d\n",LEAF_TEMP);
    
    recursive = 0;
    recursive = (CMC(USE(c), = , USE(a),  wm , USE(b)));
    // print(c);
    return recursive;
    
}
  
#endif





  // Bodrato's matrix multiply 
  // Notation taken from  
  // http://www.cs.duke.edu/~alvy/papers/sc98/index.htm
  // Sequence taken from
  // http://marco.bodrato.it/papers/Bodrato2008-StrassenLikeMatrixMultiplicationForSquares.pdf
  
  int bmadd(DEF(c), DEF(a), DEF(b)) {
    if (debug)  printf("bmadd C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d (%d,%d) += (%d,%d) (%d,%d)\n",
		       c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n, c.M,c.N,a.M,a.N,b.M,b.N);
    
    
#ifdef ADAPTIVE
    if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
      if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
	fastCPU();
#endif
	CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
#ifdef SCALING
	    slowCPU();
#endif
	    
      }
      else {
	Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
	Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
	Matrix u = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
	Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
	Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
	Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
	
	// temporary allocation 
	s.data = (Mat *) CALLOC(s);
	t.data = (Mat *) CALLOC(t);
	u.data = (Mat *) CALLOC(u);
	assert(s.data && t.data  && u.data);
	
	/* Partial matrices */
	Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
	Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
	Matrix u3 = RQ3(u,c);
	
	/* P2 */
	/* S = A3 - A2 */   CMC(s2,  =, ta3,  s_sub, ta2);
	/* T = B3 - B2 */   CMC(t2,  =, tb3,  s_sub, tb2);
	/* U =  S * T  */   CMC(u3,  =,  s3,  bm,  t3);
	/* *C3 +=  U */     CMC(tc3 ,=, tc3,s_add_t,  u3); tc3.beta = 1;
	/* *C1 -=  U */     CMC(tc1 ,=, tc1,s_sub_t,  u3); tc1.beta = 1;
	
	/* P5 */
	/* U = A1 * B2 */   CMC(u,   =, ta1,  bm, tb2);
	/* *C0 += U    */   CMC(tc0, =, tc0,s_add_t,   u); tc0.beta = 1;
	
	/* P4 */
	/* C0 += A0 * B0 */ CMC(tc0, =, ta0,  bmadd, tb0);
	
	/* P3 */
	/* S  = S + A1 */   CMC(s,   =,  s2,  s_add, ta1);
	/* T  = T + B1 */   CMC(t,   =,  t2,  s_add, tb1);
	
	/* U  += S * T */   CMC(u,   =,   s,  bmadd,   t);
	/* C1 += U     */   CMC(tc1, =, tc1,  s_add, RQ1(u,c));
	
	/* P6 */
	/* S = A0 - S   */  CMC(s,   =, ta0,  s_sub,   s);
	/* C1 += S * B1 */  CMC(tc1, =,   s,  bmadd, tb1);
	
	/* P7 */
	/* T = B0 - T   */  CMC(t  , =, tb0,  s_sub,   t);
	/* *C2 += A2* T */  CMC(tc2, =, ta2,  bmadd,   t); tc2.beta = 1;
	
	/* P1 */
	/* S = A3 + A1 */   CMC(s3,  =, ta3,  s_add, ta1);
	/* T = B3 + B1 */   CMC(t3,  =, tb3,  s_add, tb1);
	s3.beta = -s3.beta;
	/* U -= S*T    */   CMC(u3,  =,  s3,  bmadd,  t3);
	/* C3 -= U     */   CMC(tc3, =, tc3,  s_sub,  u3);
	/* C2 -= U     */   CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); 
	
	FREE(s.data);
	FREE(t.data);
	FREE(u.data);
	
      }
      dept--;
      return recursive;
      
    }
    
    
    
int bm(DEF(c), DEF(a), DEF(b)) {
  
  c.beta = 1;
  if (debug)  printf("bm C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d (%d,%d) += (%d,%d) (%d,%d)\n",
		     c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n, c.M,c.N,a.M,a.N,b.M,b.N);
  
      
#ifdef ADAPTIVE
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
    //     printf("%d \n",BR_P(a.m,a.n,b.n,LEAF_TEMP));
#else 
    if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
      fastCPU();
#endif
      CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
#ifdef SCALING
      slowCPU();
#endif
      
    }
    else {
      
      Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
      Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
      Matrix u  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
      Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
      Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
      Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
      // temporary allocation 
      s.data = (Mat *) CALLOC(s);
      t.data = (Mat *) CALLOC(t);
      u.data = (Mat *) CALLOC(u);
      assert(s.data && t.data  && u.data);
      
      /* Partial matrices */
      Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
      Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
      Matrix u3 = RQ3(u,c);
      
      /* P2 */
      /* S = A3 - A2 */   CMC(s2, =, ta3,  s_sub, ta2);
      /* T = B3 - B2 */   CMC(t2, =, tb3,  s_sub, tb2);
      /* C3 = S * T  */   CMC(tc3,=,  s3,  bm,  t3);
      
      /* P5 */
      /* U = A1 * B2 */   CMC(u,   =, ta1,  bm, tb2);
      
      /* P4 */
      /* C0 = A0 * B0 */  CMC(tc0, =, ta0,  bm, tb0);
      /* C0 += U      */  CMC(tc0, =, tc0,  s_add,   u);
      
      /* P3 */
      /* S  = S + A1 */   CMC( s,  =,  s2,  s_add, ta1);
      /* T  = T + B1 */   CMC( t,  =,  t2,  s_add, tb1);
      
      /* U  += S * T */   CMC( u,  =,   s,  bmadd,   t);
      /* C1 = U - C3 */   CMC(tc1,=,RQ1(u,c),s_sub,tc3);
      
      /* P6 */
      /* S = A0 - S   */  CMC( s,  =, ta0,  s_sub,   s);
      /* C1 += S * B1 */  CMC(tc1, =,   s,  bmadd, tb1);
      
      /* P7 */
      /* T = B0 - T   */  CMC( t,  =, tb0,  s_sub,   t);
      /*  C2 += A2* T */  CMC(tc2, =, ta2,  bm,   t);
      
      /* P1 */
      /* S = A3 + A1 */   CMC( s3, =, ta3,  s_add, ta1);
      /* T = B3 + B1 */   CMC( t3, =, tb3,  s_add, tb1);
      s3.beta = -s3.beta;
      /* U -= S*T    */   CMC( u3, =,  s3,  bmadd,  t3);
      /* C3 -= U     */   CMC(tc3, =, tc3,  s_sub,  u3);
      /* C2 -= U     */   CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); 
      
      FREE(s.data);
      FREE(t.data);
      FREE(u.data);
      
    }
    dept--;
    return recursive;
    
  }
  
  
 int BMADD(DEF(c), DEF(a), DEF(b)) {
   if (debug)  printf("bm C[%c]=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);
   
#ifdef ADAPTIVE
   if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
     if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
       CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
       
     }
     else {
       Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
       Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
       Matrix v = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
       Matrix z = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
       Matrix u = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
       Matrix w = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
       Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
       Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
       Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
       
       // temporary allocation 
       s.data = (Mat *) CALLOC(s);
       t.data = (Mat *) CALLOC(t);
       v.data = (Mat *) CALLOC(v);
       z.data = (Mat *) CALLOC(z);
       u.data = (Mat *) CALLOC(u);
       w.data = (Mat *) CALLOC(w);
       assert(s.data && t.data && v.data && z.data && u.data && w.data);
       
       /* Partial matrices */
       Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
       Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
       Matrix z3 = RQ3(z,b);
       Matrix u3 = RQ3(u,c);
       Matrix w3 = RQ3(w,c);
       
       /* P1 */
       /* U  = A1 * B2 */ CMC(u,   =, ta1,  BMOWR, tb2);
       
       /* P2 */
       /* *C0 += A0*B0 */ CMC(tc0, =, ta0,  BMADD, tb0); tc0.beta = 1;
       /* S  = A3 - A2 */ CMC(s2,  =, ta3,  s_sub, ta2);
       /* T  = B3 - B2 */ CMC(t2,  =, tb3,  s_sub, tb2);
       
       /* P3 */
       /* W  =  S * T  */ CMC(w3,  =,  s3,  BMOWR,  t3);
       /* C0 += U      */ CMC(tc0, =, tc0,  s_add,   u);
       /* V  = S  + A1 */ CMC(v,   =,  s2,  s_add, ta1);
       /* Z  = T  + B1 */ CMC(z,   =,  t2,  s_add, tb1);
       
       /* P4 */
       /* U  += V * Z  */ CMC(u,   =,   v,  BMADD,   z);
       /* S  = A3 + A1 */ CMC(s3,  =, ta3,  s_add, ta1);
       /* T  = B0 - Z  */ CMC(t,   =, tb0,  s_sub,   z);
       
       /* P5 */
       /* *C2 += A2* T */ CMC(tc2, =, ta2,  BMADD,   t); tc2.beta = 1;
       /* Z  = B3 + B1 */ CMC(z3,  =, tb3,  s_add, tb1);
       /* C1 += U      */ CMC(tc1, =, tc1,s_add_t, RQ1(u,c)); tc1.beta = 1;
       
       /* P6 */
       s3.beta = -s3.beta;
       /* U -=  S * Z  */ CMC(u3,  =,  s3,  BMADD,  z3);
       /* V  = A0 - V  */ CMC(v,   =, ta0,  s_sub,   v);
       /* *C3 +=  W    */ CMC(tc3, =, tc3,s_add_t,  w3); tc3.beta = 1;
       /* C1 -=  W     */ CMC(tc1, =, tc1,  s_sub,  w3);
       
       /* P7 */
       /* C1 += V * B1 */ CMC(tc1, =,   v,  BMADD, tb1);
       /* C3 -= U      */ CMC(tc3, =, tc3,  s_sub,  u3);
       /* C2 -= U      */ CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); 
       
       FREE(s.data);
       FREE(t.data);
       FREE(v.data);
       FREE(z.data);
       FREE(u.data);
       FREE(w.data);
       
     }
     dept--;
     return recursive;
     
   }
   

   
   int BMOWR(DEF(c), DEF(a), DEF(b)) {
	      
     c.beta = 1;
     if (debug)  printf("bm C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);
     
#ifdef ADAPTIVE
     if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
       //     printf("%d \n",BR_P(a.m,a.n,b.n,LEAF_TEMP));
#else 
       if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
	 
	 CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
	 
	 
    }
       else {
	 
	 Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
	 Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
	 Matrix v = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
	 Matrix z = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
	 Matrix u = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
	 Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
	 Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
	 Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
	 // temporary allocation 
	 s.data = (Mat *) CALLOC(s);
	 t.data = (Mat *) CALLOC(t);
	 v.data = (Mat *) CALLOC(v);
	 z.data = (Mat *) CALLOC(z);
	 u.data = (Mat *) CALLOC(u);
	 assert(s.data && t.data && v.data && z.data && u.data);
	 
	 /* Partial matrices */
	 Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
	 Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
	 Matrix z3 = RQ3(z,b);
	 Matrix u3 = RQ3(u,c);
	 
	 /* P1 */
	 /* U  = A1 * B2 */ CMC(u,   =, ta1,  BMOWR, tb2);
	 
	 /* P2 */
	 /* C0 = A0 * B0 */ CMC(tc0, =, ta0,  BMOWR, tb0);
	 /* S  = A3 - A2 */ CMC(s2,  =, ta3,  s_sub, ta2);
	 /* T  = B3 - B2 */ CMC(t2,  =, tb3,  s_sub, tb2);
	 
	 /* P3 */
	 /* C3 = S  * T  */ CMC(tc3, =,  s3,  BMOWR,  t3);
	 /* C0 += U      */ CMC(tc0, =, tc0,  s_add,   u);
	 /* V  = S  + A1 */ CMC(v,   =,  s2,  s_add, ta1);
	 /* Z  = T  + B1 */ CMC(z,   =,  t2,  s_add, tb1);
	 
	 /* P4 */
	 /* U  += V * Z  */ CMC(u,   =,   v,  BMADD,   z);
	 /* S  = A3 + A1 */ CMC(s3,  =, ta3,  s_add, ta1);
	 /* T  = B0 - Z  */ CMC(t,   =, tb0,  s_sub,   z);
	 
	 /* P5 */
	 /* C2 = A2 * T  */ CMC(tc2, =, ta2,  BMOWR,   t);
	 /* Z  = B3 + B1 */ CMC(z3,  =, tb3,  s_add, tb1);
	 /* C1 = U  - C3 */ CMC(tc1, =,RQ1(u,c),s_sub,tc3);
	 
	 /* P6 */
	 s3.beta = -s3.beta;
	 /* U -= S  * Z  */ CMC(u3,  =,  s3,  BMADD,  z3);
	 /* V  = A0 - V  */ CMC(v,   =, ta0,  s_sub,   v);
	 
	 /* P7 */
	 /* C1 += V * B1 */ CMC(tc1, =,   v,  BMADD, tb1);
	 /* C3 -= U      */ CMC(tc3, =, tc3,  s_sub,  u3);
	 /* C2 -= U      */ CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); 
	 
	 FREE(s.data);
	 FREE(t.data);
	 FREE(v.data);
	 FREE(z.data);
	 FREE(u.data);
		}
       dept--;
       return recursive;
       
     }
     

     /***** using permutation to randomize the errror */
     /*                                       _   */
#define CASE4 /* PCP = PABP   permutation    |     */   0  
#define CASE5 /* CP=ABP used for Strassen  |_     */    1  
#define CASE0 /* regular                   _|    */     2  
#define CASE3 /* C = APPB permutation    _        */    3  
#define CASE6 /* P*C = P*AB permutation   |       */    4  
#define CASE1 /* change algo                     */     5  
#define CASE2 /* change algo                     */     6  




static int tickr = CASE0; //regular
static int permutation[4] = { 0,1,1,0 };
static int PK  = 5; 



#define RANDOMCHANGE 0
#define ORTHOGONAL 1

static int orthogonal(int t, char a) { 
  if (a == 'w')  {
    if (t == CASE0)     return CASE4;
  } else if (a =='s') { 
    if (t == CASE0)      return CASE5;
  }
  return CASE0;
}


#define SWITCH_STATEMENT(STRASSEN,WINOGRAD) \    
 switch  (tickr%PK) {							\
 case CASE0:								\
 default:								\
   break;								\
 case CASE1:								\
   return STRASSEN(USE(c),USE(a),USE(b));				\
   break;								\
 case CASE2:								\
   return WINOGRAD(USE(c),USE(a),USE(b));				\
   break;								\
 case CASE3:								\
   { /* Permutation C = APPB */						\
     Matrix AX[4], BX[4];						\
     									\
     RP(a,AX,permutation,1);						\
     RP(b,BX,permutation,-1);						\
     									\
     ta0 = AX[0]; ta1 = AX[1];  ta2 =AX[2]; ta3=AX[3];			\
     tb0 = BX[0]; tb1 = BX[1];  tb2 =BX[2]; tb3=BX[3];			\
     									\
   }									\
   break;								\
 case CASE4:								\
   {									\
     /* Permutation PCP = PABP 	 */					\
     Matrix AX[4], BX[4],CX[4];						\
     									\
     RP(c,CX,permutation,0);						\
     RP(a,AX,permutation,-1);						\
     RP(b,BX,permutation,1);						\
     									\
     tc0 = CX[0]; tc1 = CX[1];  tc2 =CX[2]; tc3=CX[3];			\
     ta0 = AX[0]; ta1 = AX[1];  ta2 =AX[2]; ta3=AX[3];			\
     tb0 = BX[0]; tb1 = BX[1];  tb2 =BX[2]; tb3=BX[3];			\
     									\
   }									\
   break;								\
 case CASE5:								\
   {									\
     /* Permutation CP =ABP */						\
     Matrix AX[4], BX[4],CX[4];						\
     									\
     RP(c,CX,permutation,1);						\
     RP(b,BX,permutation,1);						\
     									\
     tc0 = CX[0]; tc1 = CX[1];  tc2 =CX[2]; tc3=CX[3];			\
     tb0 = BX[0]; tb1 = BX[1];  tb2 =BX[2]; tb3=BX[3];			\
   }									\
   break;								\
 case CASE6:								\
   {									\
     /* Permutation CP =PAB */						\
     Matrix AX[4], BX[4],CX[4];						\
     									\
     RP(c,CX,permutation,-1);						\
     RP(a,AX,permutation,-1);						\
     									\
     ta0 = AX[0]; ta1 = AX[1];  ta2 =AX[2]; ta3=AX[3];			\
     tc0 = CX[0]; tc1 = CX[1];  tc2 =CX[2]; tc3=CX[3];			\
   }									\
   break;								\
 }									\
 
	      



int BMADDR(DEF(c), DEF(a), DEF(b)) {
    if (debug)  printf("BMADDR C[%c]+=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);

#ifdef ADAPTIVE
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation_madd/*madd*/ , USE(b));

  }
  else {
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix v = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix z = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix w = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary

    Matrix tc0,tc1 , tc2 ,tc3,ta0,ta1 , ta2 ,ta3,tb0,tb1 , tb2 ,tb3; 
    int temptickr ;

    tc0 = Q0(c);tc1 = Q1(c); tc2 =Q2(c);tc3=Q3(c);    
    ta0 = Q0(a);ta1 = Q1(a); ta2 =Q2(a);ta3=Q3(a);			\
    tb0 = Q0(b);tb1 = Q1(b); tb2 =Q2(b);tb3=Q3(b);			\
    
    if (ORTHOGONAL) 
      temptickr = tickr;
    if (RANDOMCHANGE)
      tickr = rand();
    

    SWITCH_STATEMENT(saddmulR,wmaddR);

    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    v.data = (Mat *) CALLOC(v);
    z.data = (Mat *) CALLOC(z);
    u.data = (Mat *) CALLOC(u);
    w.data = (Mat *) CALLOC(w);
    assert(s.data && t.data && v.data && z.data && u.data && w.data);

    /* Partial matrices */
    Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
    Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
    Matrix z3 = RQ3(z,b);
    Matrix u3 = RQ3(u,c);
    Matrix w3 = RQ3(w,c);

    /* P1 */
    /* U  = A1 * B2 */ CMC(u,   =, ta1,  BMOWRR, tb2);

    if (ORTHOGONAL) tickr = orthogonal(tickr,'w'); 
    /* P2 */
    /* *C0 += A0*B0 */ CMC(tc0, =, ta0,  BMADDR, tb0); tc0.beta = 1;
    /* S  = A3 - A2 */ CMC(s2,  =, ta3,  s_sub, ta2);
    /* T  = B3 - B2 */ CMC(t2,  =, tb3,  s_sub, tb2);

    /* P3 */
    /* W  =  S * T  */ CMC(w3,  =,  s3,  BMOWRR,  t3);
    /* C0 += U      */ CMC(tc0, =, tc0,  s_add,   u);
    /* V  = S  + A1 */ CMC(v,   =,  s2,  s_add, ta1);
    /* Z  = T  + B1 */ CMC(z,   =,  t2,  s_add, tb1);

    /* P4 */
    /* U  += V * Z  */ CMC(u,   =,   v,  BMADDR,   z);
    /* S  = A3 + A1 */ CMC(s3,  =, ta3,  s_add, ta1);
    /* T  = B0 - Z  */ CMC(t,   =, tb0,  s_sub,   z);

    /* P5 */
    /* *C2 += A2* T */ CMC(tc2, =, ta2,  BMADDR,   t); tc2.beta = 1;
    /* Z  = B3 + B1 */ CMC(z3,  =, tb3,  s_add, tb1);
    /* C1 += U      */ CMC(tc1, =, tc1,s_add_t, RQ1(u,c)); tc1.beta = 1;

    if (ORTHOGONAL) tickr = orthogonal(tickr,'w');

    /* P6 */
    s3.beta = -s3.beta;
    /* U -=  S * Z  */ CMC(u3,  =,  s3,  BMADDR,  z3);
    /* V  = A0 - V  */ CMC(v,   =, ta0,  s_sub,   v);
    /* C3 +=  W     */ CMC(tc3, =, tc3,s_add_t,  w3); tc3.beta = 1;
    /* C1 -=  W     */ CMC(tc1, =, tc1,  s_sub,  w3);

    /* P7 */
    /* C1 += V * B1 */ CMC(tc1, =,   v,  BMADDR, tb1);
    /* C3 -= U      */ CMC(tc3, =, tc3,  s_sub,  u3);
    /* C2 -= U      */ CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); 

    FREE(s.data);
    FREE(t.data);
    FREE(v.data);
    FREE(z.data);
    FREE(u.data);
    FREE(w.data);



    if (ORTHOGONAL) 
      tickr = temptickr;
  }


  
  return tickr;

}



int BMOWRR(DEF(c), DEF(a), DEF(b)) {
  
  c.beta = 1;
  if (debug)  printf("BMOWRR C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);

#ifdef ADAPTIVE
   if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
     //     printf("%d \n",BR_P(a.m,a.n,b.n,LEAF_TEMP));
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif

    CMC(USE(c), = , USE(a),  mm_leaf_computation/*mul*/ , USE(b));


  }
  else {

    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix v = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix z = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix w = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary

    Matrix tc0,tc1 , tc2 ,tc3,ta0,ta1 , ta2 ,ta3,tb0,tb1 , tb2 ,tb3; 

    int temptickr ;
    tc0 = Q0(c);tc1 = Q1(c); tc2 =Q2(c);tc3=Q3(c);    
    ta0 = Q0(a);ta1 = Q1(a); ta2 =Q2(a);ta3=Q3(a);			\
    tb0 = Q0(b);tb1 = Q1(b); tb2 =Q2(b);tb3=Q3(b);			\


    if (ORTHOGONAL) 
      temptickr = tickr;

    if (RANDOMCHANGE)
      tickr = rand();


    if (debug)
      printf("tick %d \n",tickr);
    SWITCH_STATEMENT(smulR,wmR);



    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    v.data = (Mat *) CALLOC(v);
    z.data = (Mat *) CALLOC(z);
    u.data = (Mat *) CALLOC(u);
    assert(s.data && t.data && v.data && z.data && u.data);

    /* Partial matrices */
    Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
    Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
    Matrix z3 = RQ3(z,b);
    Matrix u3 = RQ3(u,c);

    /* P1 */
    /* U  = A1 * B2 */ CMC(u,   =, ta1,  BMOWRR, tb2);

    if (ORTHOGONAL) tickr = orthogonal(tickr,'w'); 
    /* P2 */
    /* C0 = A0 * B0 */ CMC(tc0, =, ta0,  BMOWRR, tb0);
    /* S  = A3 - A2 */ CMC(s2,  =, ta3,  s_sub, ta2);
    /* T  = B3 - B2 */ CMC(t2,  =, tb3,  s_sub, tb2);

    /* P3 */
    /* C3 = S  * T  */ CMC(tc3, =,  s3,  BMOWRR,  t3);
    /* C0 += U      */ CMC(tc0, =, tc0,  s_add,   u);
    /* V  = S  + A1 */ CMC(v,   =,  s2,  s_add, ta1);
    /* Z  = T  + B1 */ CMC(z,   =,  t2,  s_add, tb1);

    /* P4 */
    /* U  += V * Z  */ CMC(u,   =,   v,  BMADDR,   z);
    /* S  = A3 + A1 */ CMC(s3,  =, ta3,  s_add, ta1);
    /* T  = B0 - Z  */ CMC(t,   =, tb0,  s_sub,   z);

    /* P5 */
    /* C2 = A2 * T  */ CMC(tc2, =, ta2,  BMOWRR,   t);
    /* Z  = B3 + B1 */ CMC(z3,  =, tb3,  s_add, tb1);
    /* C1 = U  - C3 */ CMC(tc1, =,RQ1(u,c),s_sub,tc3);
    
    if (ORTHOGONAL) tickr = orthogonal(tickr,'w'); 

    /* P6 */
    s3.beta = -s3.beta;
    /* U -= S  * Z  */ CMC(u3,  =,  s3,  BMADDR,  z3);
    /* V  = A0 - V  */ CMC(v,   =, ta0,  s_sub,   v);

    /* P7 */
    /* C1 += V * B1 */ CMC(tc1, =,   v,  BMADDR, tb1);
    /* C3 -= U      */ CMC(tc3, =, tc3,  s_sub,  u3);
    /* C2 -= U      */ CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); 
 
    FREE(s.data);
    FREE(t.data);
    FREE(v.data);
    FREE(z.data);
    FREE(u.data);

    if (ORTHOGONAL)
      tickr = temptickr;
  }

  return tickr;

}


int wmaddR(DEF(c), DEF(a), DEF(b)) {
    if (debug)  printf("wmaddR C[%c]+=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d (%d,%d) += (%d,%d) (%d,%d)\n",
		       c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n, c.M,c.N,a.M,a.N,b.M,b.N);
  					  

#ifdef ADAPTIVE
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
#ifdef SCALING
    slowCPU();
#endif

  }
  else {
    Matrix s =   {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
    Matrix t =   {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0,tc1 , tc2 ,tc3,ta0,ta1 , ta2 ,ta3,tb0,tb1 , tb2 ,tb3; 
    int temptickr ;

    tc0 = Q0(c);tc1 = Q1(c); tc2 =Q2(c);tc3=Q3(c);    
    ta0 = Q0(a);ta1 = Q1(a); ta2 =Q2(a);ta3=Q3(a);			\
    tb0 = Q0(b);tb1 = Q1(b); tb2 =Q2(b);tb3=Q3(b);			\

    if (ORTHOGONAL) 
      temptickr = tickr;

    if (RANDOMCHANGE)
      tickr = rand();
    if (debug)
      printf("tick %d \n",tickr);

    SWITCH_STATEMENT(saddmulR,wmaddR) ;
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data  && u2.data);

    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),  =, ta2,      s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,        =, tb1,      s_sub,   tb0);
    /* U2 = S * T   */   CMC(RQ2(u2,c) ,=, RQ2(s,a), wmR ,     t);
    /* *C3 +=  U2 */     CMC(tc3 ,=, tc3, s_add_t ,   RQ3(u2,c)); tc3.beta = 1;
    /* *C1 +=  U2 */     CMC(tc1 ,=, tc1, s_add_t ,   RQ1(u2,c)); tc1.beta = 1;

    /* P1 */
    /* U2 = A0*B0   */    CMC (u2, =, ta0, wmR, tb0);
    /* C0  += U2 +C0 */   CMC(tc0, =, tc0, s_add_t, u2); tc0.beta = 1;

    if (ORTHOGONAL) tickr = orthogonal(tickr,'w');         
    /* P2 */
    /* C0 += A1 * B2 */   CMC(tc0,  =, ta1, wmaddR,   tb2);
    
    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a), s_sub,  ta0);
    /* T  = B3 - T */    CMC(t,    =, tb3,    s_sub,  t);
    /* U2 += S*T   */    CMC(u2,    =, s, wmaddR, t);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
    /* C1 += S * B3 */   CMC(tc1, =, RQ1(s,a),  wmaddR,    tb3);

    if (ORTHOGONAL) tickr = orthogonal(tickr,'w');         
    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* C2 += A3*T  */    CMC(tc2, =, ta3,    wmaddR,   RQ2(t,b)); tc2.beta = 1;

    if (ORTHOGONAL) tickr = orthogonal(tickr,'w');         
    /* P5 */
    /* S = A0 - A2 */     CMC(s,         =, ta0,       s_sub,   ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b),  =, tb3,       s_sub,   tb1);
    /* U2 += S*T     */   CMC(RQ1(u2,c), =, s,         wmaddR,   RQ1(t,b));
    /* C3  += U2   */     CMC(tc3,       =, tc3,       s_add,   RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,       =, RQ2(u2,c), s_add,   tc2); 


 
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);

    if (ORTHOGONAL) 
      tickr = temptickr;
  }
  dept--;
  return recursive;

}



int wmR(DEF(c), DEF(a), DEF(b)) {
  
  c.beta = 1;
  if (debug)  printf("wmR C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d (%d,%d) = (%d,%d) (%d,%d)\n",
		     c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n, c.M,c.N,a.M,a.N,b.M,b.N);


#ifdef ADAPTIVE
   if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
     //     printf("%d \n",BR_P(a.m,a.n,b.n,LEAF_TEMP));
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
#ifdef SCALING
    slowCPU();
#endif

  }
  else {

    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0,tc1 , tc2 ,tc3,ta0,ta1 , ta2 ,ta3,tb0,tb1 , tb2 ,tb3; 
    int temptickr;

    tc0 = Q0(c);tc1 = Q1(c); tc2 =Q2(c);tc3=Q3(c);    
    ta0 = Q0(a);ta1 = Q1(a); ta2 =Q2(a);ta3=Q3(a);			\
    tb0 = Q0(b);tb1 = Q1(b); tb2 =Q2(b);tb3=Q3(b);			\

    if (debug)
      printf("tick %d \n",tickr);

    if (ORTHOGONAL) 
      temptickr = tickr;
    if (RANDOMCHANGE)
      tickr = rand();

    SWITCH_STATEMENT(smulR,BMOWRR) ;
    
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data  && u2.data);



    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),=, ta2,     s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,=, tb1,     s_sub,   tb0);
    /* U2 = S * T   */   CMC(RQ2(u2,c) ,=, RQ2(s,a), wmR ,   t);
    /* C1 +=  U2    */   copy(tc1 ,   RQ1(u2,c));
    /* C3 +=  U2    */   copy(tc3,  RQ3(u2,c));

    /* P1 */
    /* C0 = A0*B0   */    CMC (tc0, =, ta0, wmR, tb0);
    /* U2  = C0     */    copy(u2,tc0);

    if (ORTHOGONAL) tickr = orthogonal(tickr,'w'); 
    /* P2 */
    /* C0 += A1 * B2 */    CMC(tc0,  =, ta1, wmaddR,   tb2);


    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a), s_sub,  ta0);
    /* T  = B3 - T */    CMC(t,    =, tb3,    s_sub,  t);
    /* U2 += S*T   */    CMC(u2,    =, s, wmaddR, t);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
    /* C1 += S * B3 */   CMC(tc1, =, RQ1(s,a),  wmaddR,    tb3);
    
    if (ORTHOGONAL) tickr = orthogonal(tickr,'w'); 

    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* C2 = A3*T  */      CMC(tc2, =, ta3,    wmR,   RQ2(t,b));
    if (ORTHOGONAL) tickr = orthogonal(tickr,'w'); 
    /* P5 */
    /* S = A0 - A2 */     CMC(s,     =, ta0,     s_sub,  ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b),     =, tb3,     s_sub,  tb1);
    /* U2 += S*T     */   CMC(RQ1(u2,c),     =, s,  wmaddR,   RQ1(t,b));
    /* C3  += U2   */     CMC(tc3,        =, tc3,     s_add,  RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,        =, RQ2(u2,c),     s_add,  tc2); 

 
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);
    

    if (ORTHOGONAL) 
      tickr = temptickr;
  }
  dept--;
  return recursive;

}




int wmaddTR(DEF(c), DEF(a), DEF(b)) {
    if (debug)  printf("wmaddTR C[%c]+=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d (%d,%d) += (%d,%d) (%d,%d)\n",
		       c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n, c.M,c.N,a.M,a.N,b.M,b.N);
  					  

#ifdef ADAPTIVE
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
#ifdef SCALING
    slowCPU();
#endif

  }
  else {
    Matrix s =   {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
    Matrix t =   {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0,tc1 , tc2 ,tc3,ta0,ta1 , ta2 ,ta3,tb0,tb1 , tb2 ,tb3; 
    int temptickr ;

    tc0 = Q0(c);tc1 = Q1(c); tc2 =Q2(c);tc3=Q3(c);    
    ta0 = Q0(a);ta1 = Q1(a); ta2 =Q2(a);ta3=Q3(a);			\
    tb0 = Q0(b);tb1 = Q1(b); tb2 =Q2(b);tb3=Q3(b);			\

    if (ORTHOGONAL) 
      temptickr = tickr;

    if (RANDOMCHANGE)
      tickr = rand();

    if (debug)
      printf("tick %d \n",tickr);

    SWITCH_STATEMENT(saddmulR,wmaddTR) ;
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data  && u2.data);

    if (ORTHOGONAL) tickr = CASE5;
    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),  =, ta2,      s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,        =, tb1,      s_sub,   tb0);
    /* U2 = S * T   */   CMC(RQ2(u2,c) ,=, RQ2(s,a), wmTR ,     t);
    /* *C3 +=  U2 */     CMC(tc3 ,=, tc3, s_add_t ,   RQ3(u2,c)); tc3.beta = 1;
    /* *C1 +=  U2 */     CMC(tc1 ,=, tc1, s_add_t ,   RQ1(u2,c)); tc1.beta = 1;

    if (ORTHOGONAL) tickr = CASE0;
    /* P1 */
    /* U2 = A0*B0   */    CMC (u2, =, ta0, wmTR, tb0);
    /* C0  += U2 +C0 */   CMC(tc0, =, tc0, s_add_t, u2); tc0.beta = 1;

    if (ORTHOGONAL) tickr = CASE4;         
    /* P2 */
    /* C0 += A1 * B2 */   CMC(tc0,  =, ta1, wmaddTR,   tb2);
    
    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a), s_sub,  ta0);
    /* T  = B3 - T */    CMC(t,    =, tb3,    s_sub,  t);
    /* U2 += S*T   */    CMC(u2,    =, s, wmaddTR, t);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    if (ORTHOGONAL) tickr = CASE6;
    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
    /* C1 += S * B3 */   CMC(tc1, =, RQ1(s,a),  wmaddTR,    tb3);

    if (ORTHOGONAL) tickr = CASE5;         
    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* C2 += A3*T  */    CMC(tc2, =, ta3,    wmaddTR,   RQ2(t,b)); tc2.beta = 1;

    if (ORTHOGONAL) tickr = CASE6;         
    /* P5 */
    /* S = A0 - A2 */     CMC(s,         =, ta0,       s_sub,   ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b),  =, tb3,       s_sub,   tb1);
    /* U2 += S*T     */   CMC(RQ1(u2,c), =, s,         wmaddTR,   RQ1(t,b));
    /* C3  += U2   */     CMC(tc3,       =, tc3,       s_add,   RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,       =, RQ2(u2,c), s_add,   tc2); 




 
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);

    if (ORTHOGONAL) 
      tickr = temptickr;
  }
  dept--;
  return recursive;

}



int wmTR(DEF(c), DEF(a), DEF(b)) {
  
  c.beta = 1;
  if (debug)  printf("wmTR C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d (%d,%d) = (%d,%d) (%d,%d)\n",
		     c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n, c.M,c.N,a.M,a.N,b.M,b.N);


#ifdef ADAPTIVE
   if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
     //     printf("%d \n",BR_P(a.m,a.n,b.n,LEAF_TEMP));
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
#ifdef SCALING
    slowCPU();
#endif

  }
  else {

    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0,tc1 , tc2 ,tc3,ta0,ta1 , ta2 ,ta3,tb0,tb1 , tb2 ,tb3; 
    int temptickr;

    tc0 = Q0(c);tc1 = Q1(c); tc2 =Q2(c);tc3=Q3(c);    
    ta0 = Q0(a);ta1 = Q1(a); ta2 =Q2(a);ta3=Q3(a);			\
    tb0 = Q0(b);tb1 = Q1(b); tb2 =Q2(b);tb3=Q3(b);			\


    if (ORTHOGONAL) 
      temptickr = tickr;
    if (RANDOMCHANGE)
      tickr = rand();

    if (debug)
      printf("tick %d \n",tickr);


    SWITCH_STATEMENT(smulR,BMOWRR) ;
    
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data  && u2.data);


    if (ORTHOGONAL) tickr = CASE5;

    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),=, ta2,     s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,=, tb1,     s_sub,   tb0);
    /* U2 = S * T   */   CMC(RQ2(u2,c) ,=, RQ2(s,a), wmTR ,   t);
    /* C1 +=  U2    */   copy(tc1 ,   RQ1(u2,c));
    /* C3 +=  U2    */   copy(tc3,  RQ3(u2,c));

    if (ORTHOGONAL) tickr = CASE0;
    /* P1 */
    /* C0 = A0*B0   */    CMC (tc0, =, ta0, wmTR, tb0);
    /* U2  = C0     */    copy(u2,tc0);

    if (ORTHOGONAL) tickr = CASE4;
    /* P2 */
    /* C0 += A1 * B2 */    CMC(tc0,  =, ta1, wmaddTR,   tb2);


    /* P4 */
    /* S  = S - A0 */    CMC(s,    =, RQ2(s,a), s_sub,  ta0);
    /* T  = B3 - T */    CMC(t,    =, tb3,    s_sub,  t);
    /* U2 += S*T   */    CMC(u2,    =, s, wmaddTR, t);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    if (ORTHOGONAL) tickr = CASE6;

    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
    /* C1 += S * B3 */   CMC(tc1, =, RQ1(s,a),  wmaddTR,    tb3);
    
    if (ORTHOGONAL) tickr = CASE5;

    /* P7 */
    /* T = B2 - T */     CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
    /* C2 = A3*T  */      CMC(tc2, =, ta3,    wmTR,   RQ2(t,b));
    if (ORTHOGONAL) tickr = CASE6;
    /* P5 */
    /* S = A0 - A2 */     CMC(s,     =, ta0,     s_sub,  ta2);
    /* T = B3 - B1 */     CMC(RQ1(t,b),     =, tb3,     s_sub,  tb1);
    /* U2 += S*T     */   CMC(RQ1(u2,c),     =, s,  wmaddTR,   RQ1(t,b));
    /* C3  += U2   */     CMC(tc3,        =, tc3,     s_add,  RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,        =, RQ2(u2,c),     s_add,  tc2); 

 
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);
    

    if (ORTHOGONAL) 
      tickr = temptickr;
  }
  dept--;
  return recursive;

}




// Strassen C = A*B
int smulR(DEF(c), DEF(a), DEF(b)) {

  c.beta =1;
  if (debug)  printf("smulR C[%c]=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);
#ifdef ADAPTIVE
  if (debug)  printf("smulR %d < %d  thus %d \n",(BR_LEFT(a.m,a.n,b.n,LEAF_TEMP)),(BR_RIGHT(a.m,a.n,b.n,LEAF_TEMP)),BR_P(a.m,a.n,b.n,LEAF_TEMP));
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation , USE(b));
#ifdef SCALING
    slowCPU();
#endif

  }
  else {
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta}; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),'n',0}; // temporary 

    Matrix tc0,tc1 , tc2 ,tc3,ta0,ta1 , ta2 ,ta3,tb0,tb1 , tb2 ,tb3; 
    int temptickr;

    tc0 = Q0(c);tc1 = Q1(c); tc2 =Q2(c);tc3=Q3(c);    
    ta0 = Q0(a);ta1 = Q1(a); ta2 =Q2(a);ta3=Q3(a);			\
    tb0 = Q0(b);tb1 = Q1(b); tb2 =Q2(b);tb3=Q3(b);			\

    
    if (ORTHOGONAL) 
      temptickr = tickr;
    if (RANDOMCHANGE)
      tickr = rand();
    if (debug)
      printf("tick %d \n",tickr);

    SWITCH_STATEMENT(smulR,wmR) ;
    

    dept+=3;
    recursive = max(recursive,dept);

    // temporary allocation 
    t1.data = (Mat *) calloc(Size(t1.M,t1.N),sizeof(Mat));
    t2.data = (Mat *) calloc(Size(t2.M,t2.N),sizeof(Mat));
    m.data  =  (Mat *) calloc(Size(m.M,m.N), sizeof(Mat));


    /* T2  = B1-B3   */    CMC (RQ1(t2,b),=, tb1, s_sub,  tb3);
    /* MM3 = A0*T2   */    CMC (RQ1(m,c), =, ta0, smulR, RQ1(t2,b));
    /* C1  = M3      */    copy(tc1, RQ1(m,c)); 
    /* C3  = M3      */    copy(tc3, RQ3(m,c));

    if (ORTHOGONAL) tickr = orthogonal(tickr,'s'); 
    /* T1 = A2 - A0  */    CMC(t1,    =, ta2, s_sub,  ta0);
    /* T2 = B0 + B1  */    CMC(t2,    =, tb0, s_add,  tb1);
    /* MM6 = T1 * T2 */    CMC(m,     =, t1,  smulR,   t2);
    /* C3  += M6     */    CMC(tc3,   =, tc3, s_add,  RQ3(m,c));
    
    /* T1  = A2 + A3 */    CMC(RQ2(t1,a),=, ta2,       s_add,   ta3);
    /* MM2 = T1 * B0 */    CMC(RQ2(m,c) ,=, RQ2(t1,a), smulR ,   tb0);
    /* C3  -= M2     */    CMC(tc3,      =, tc3,       s_sub,   RQ3(m,c));
    /* C2  =  M2     */    copy(tc2, RQ2(m,c));
    
    if (ORTHOGONAL) tickr = orthogonal(tickr,'s'); 
    /* T1  = A0 + A3 */    CMC(t1,    =, ta0, s_add,  ta3);
    /* T2  = B0 + B3 */    CMC(t2,    =, tb0, s_add,  tb3);
    /* MM1 = T1*T2   */    CMC(m,     =, t1,  smulR, t2);
    /* C3  += M1     */    CMC(tc3,   =, tc3, s_add,  RQ3(m,c));
    /* C0  = M1      */    copy(tc0,m);

    if (ORTHOGONAL) tickr = orthogonal(tickr,'s'); 
    /* T1 = A0 + A1 */     CMC(RQ1(t1,a),=, ta0,       s_add,   ta1);
    /* MM5 = T1 * B3 */    CMC(RQ1(m,c), =, RQ1(t1,a), smulR,    tb3);
    /* C0  -= M5     */    CMC(tc0,      =, tc0,       s_sub,   RQ1(m,c));
    /* C1  += M5     */    CMC(tc1,      =, tc1,       s_add,   RQ1(m,c));

    /* T1 = A1 - A3 */     CMC(RQ1(t1,a),=, ta1,    s_sub,  ta3);
    /* T2 = B2 + B3 */     CMC(RQ2(t2,b),=, tb2,    s_add,  tb3);
    /* MM7 = T1*T2  */     CMC(m,        =, RQ1(t1,a),smulR, RQ2(t2,b));
    /* C0  += M7    */     CMC(tc0,    =, tc0,    s_add,  m);

    if (ORTHOGONAL) tickr = orthogonal(tickr,'s'); 
    /* T1 = B2 - B0 */     CMC(RQ2(t2,b),      =, tb2, s_sub,  tb0);
    /* MM4 = A3*T1  */     CMC(RQ2(m,c), =, ta3, smulR, RQ2(t2,b));
    /* C0  += M4    */     CMC(tc0,             =, tc0, s_add,  RQ2(m,c)); 
    /* C2  += M4    */     CMC(tc2,             =, tc2, s_add,  RQ2(m,c));

 
    free(t1.data);
    free(t2.data);
    free(m.data);


    if (ORTHOGONAL) 
      temptickr = tickr;
  }
  dept-=3;
  return recursive;
}


// Strassen C+=A*B 
int saddmulR(DEF(c), DEF(a), DEF(b)) {

  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#ifdef SCALING
    fastCPU();
#endif
    CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
#ifdef SCALING
    slowCPU();
#endif

  }
  else {
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta}  ; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),'n',1}; // temporary

    Matrix tc0,tc1 , tc2 ,tc3,ta0,ta1 , ta2 ,ta3,tb0,tb1 , tb2 ,tb3; 
    int temptickr;

    tc0 = Q0(c);tc1 = Q1(c); tc2 =Q2(c);tc3=Q3(c);    
    ta0 = Q0(a);ta1 = Q1(a); ta2 =Q2(a);ta3=Q3(a);			\
    tb0 = Q0(b);tb1 = Q1(b); tb2 =Q2(b);tb3=Q3(b);			\

    if (ORTHOGONAL) 
      temptickr = tickr;
    if (RANDOMCHANGE)
      tickr = rand();

    if (debug)
      printf("tick %d \n",tickr);

    SWITCH_STATEMENT(saddmulR,wmaddR) ;


    dept+=3;
    recursive = max(recursive,dept);

    // temporary allocation 
    t1.data = (Mat *) calloc(Size(t1.M,t1.N),sizeof(Mat));
    t2.data = (Mat *) calloc(Size(t2.M,t2.N),sizeof(Mat));
    m.data  =  (Mat *) calloc(Size(m.M,m.N), sizeof(Mat));


    /* T2  = B1-B3   */    CMC (RQ1(t2,b),=, tb1, s_sub,  tb3);
    /* MM3 = A0*T2   */    CMC (RQ1(m,c), =, ta0, smulR,   RQ1(t2,b));
    /* *C1  += M3    */    CMC (tc1,      =, tc1, s_add_t,  RQ1(m,c)) ; tc1.beta=1;
    /* *C3  += M3    */    CMC (tc3,      =, tc3, s_add_t,  RQ3(m,c)) ; tc3.beta=1;

    if (ORTHOGONAL) tickr = orthogonal(tickr,'s'); 
    /* T1 = A2 - A0  */    CMC(t1,   =, ta2, s_sub,  ta0);
    /* T2 = B0 + B1  */    CMC(t2,   =, tb0, s_add,  tb1);
    /* MM6 = T1 * T2 */    CMC(m,    =, t1,  smulR,   t2);
    /* C3  += M6     */    CMC(tc3,  =, tc3, s_add,  RQ3(m,c));

    /* T1  = A2 + A3 */    CMC(RQ2(t1,a), =, ta2,       s_add,   ta3);
    /* MM2 = T1 * B0 */    CMC(RQ2(m,c) , =, RQ2(t1,a), smulR ,   tb0);
    /* C3  -= M2     */    CMC(tc3,       =, tc3,       s_sub,   RQ3(m,c));
    /* *C2  += M2    */    CMC(tc2,       =, tc2,       s_add_t,   RQ2(m,c)); tc2.beta=1;
    
    if (ORTHOGONAL) tickr = orthogonal(tickr,'s'); 
    /* T1  = A0 + A3 */    CMC(t1,  =, ta0, s_add,  ta3);
    /* T2  = B0 + B3 */    CMC(t2,  =, tb0, s_add,  tb3);
    /* MM1 = T1*T2   */    CMC(m,   =, t1,  smulR,  t2);
    /* C3  += M1     */    CMC(tc3, =, tc3, s_add,  RQ3(m,c));
    /* *C0  += M1    */    CMC(tc0, =, tc0, s_add_t,  m);              tc0.beta=1;

    if (ORTHOGONAL) tickr = orthogonal(tickr,'s'); 
    /* T1 = A0 + A1 */     CMC(RQ1(t1,a),=, ta0,       s_add,   ta1);
    /* MM5 = T1 * B3 */    CMC(RQ1(m,c), =, RQ1(t1,a), smulR,    tb3);
    /* C0  -= M5     */    CMC(tc0,      =, tc0,       s_sub,   RQ1(m,c));
    /* C1  += M5     */    CMC(tc1,      =, tc1,       s_add,   RQ1(m,c));

    /* T1 = A1 - A3 */     CMC(RQ1(t1,a),=, ta1,       s_sub,  ta3);
    /* T2 = B2 + B3 */     CMC(RQ2(t2,b),=, tb2,       s_add,  tb3);
    /* MM7 = T1*T2  */     CMC(m,        =, RQ1(t1,a), smulR,   RQ2(t2,b));
    /* C0  += M7    */     CMC(tc0,      =, tc0,       s_add,  m);

    if (ORTHOGONAL) tickr = orthogonal(tickr,'s'); 
    /* T1 = B2 - B0 */     CMC(RQ2(t2,b), =, tb2, s_sub,  tb0);
    /* MM4 = A3*T1  */     CMC(RQ2(m,c),  =, ta3, smulR,   RQ2(t2,b));
    /* C0  += M4    */     CMC(tc0,       =, tc0, s_add,  RQ2(m,c)); 
    /* C2  += M4    */     CMC(tc2,       =, tc2, s_add,  RQ2(m,c));

 
    free(t1.data);
    free(t2.data);
    free(m.data);


    if (ORTHOGONAL) 
      tickr = temptickr;

  }
  dept-=3;
  return recursive;

}













/***** using permutation to randomize the errror end*/

int rmul(DEF(c), DEF(a), DEF(b), MatrixComputation leaf) { 

  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {

    
    CMC(USE(c), = , USE(a),  leaf , USE(b));
    return 0;
  }
  else {


    rmul(Q0(c),Q0(a),Q0(b),leaf);
    rmul(Q1(c),Q0(a),Q1(b),leaf);
    rmul(Q2(c),Q2(a),Q0(b),leaf);
    rmul(Q3(c),Q2(a),Q1(b),leaf);
    
    rmul(Q0(c),Q1(a),Q2(b),leaf);
    rmul(Q1(c),Q1(a),Q3(b),leaf);
    rmul(Q2(c),Q3(a),Q2(b),leaf);
    rmul(Q3(c),Q3(a),Q3(b),leaf);
    
  }

  return 1;
}










 
static inline  
void gotmul(DEF(c), DEF(a), DEF(b)) {
 
  mm_leaf_computation(USE(c),USE(a),USE(b)); 
}
static inline 
void gotmadd(DEF(c), DEF(a), DEF(b)) {
 
  mm_leaf_computation_madd(USE(c),USE(a),USE(b)); 
}
 
 
static inline  
TAddOperands * divideMul (DEF(c), DEF(a), DEF(b),
			  MatrixComputation m,
			  int *k) {

  TAddOperands *args = (TAddOperands *) malloc(3*sizeof(TAddOperands));
  
  *k = 3;
  

  {
    args[0].m = sub_amd;
    args[0].c = Q2(c); 
    args[0].a = Q2(a); 
    args[0].b = Q2(b); 

    args[1].m = add_amd;
    args[1].c = Q1(c); 
    args[1].a = Q1(a);  
    args[1].b = Q1(b); 
    
    args[2].m = gotmul;
    args[2].c = Q0(c); 
    //print(args[2].c);
    //printf("%d \n",(int)(args[2].c.data - args[1].c.data));
    args[2].a = Q0(a); 
    args[2].b = Q0(b); 
    
  }
  
  return args;
}
 
 
void ptaddmul(DEF(c), DEF(a), DEF(b)) {
  
  
  
  pThreadedMatrixComputation(gotmul,divideMul, USE(c),USE(a),USE(b)); 
  
  
}
 
#define PIPELINE 1
 
#ifdef PIPELINE 
 
int wmaddpipe(DEF(c), DEF(a), DEF(b),TAddOperands *args ) {
   
  TAddOperands *argslocal = (TAddOperands *) calloc(3,sizeof(TAddOperands));
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
    if (args) { 
      TAddOperands *temp = argslocal;
      int len=0;
      while (args && args[len].m) { 
	temp[len] = args[len];
	len++;
      }
      //      temp[len].pi = _A[1]|8; 
      temp[len].m = gotmadd;
      temp[len].c = c;
      temp[len].a = a;
      temp[len].b = b;
      
      MatrixComputations(temp,len+1);
    } 
    else { 
      CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
    }

  }
  else {
    Matrix s =   {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
    Matrix t =   {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    

    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data  && u2.data);

    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),  =, ta2,      s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,        =, tb1,      s_sub,   tb0);
    /* U2 = S * T   */   wmpipe(RQ2(u2,c), RQ2(s,a),     t,args);


    
    /* *C3 +=  U2 */     CMC(tc3 ,=, tc3, s_add_t ,   RQ3(u2,c)); tc3.beta = 1;
    /* *C1 +=  U2 */     CMC(tc1 ,=, tc1, s_add_t ,   RQ1(u2,c)); tc1.beta = 1;

    
    /* P1 */
    /* U2 = A0*B0   */    wmpipe (u2, ta0, tb0, 0);
    /* C0  += U2 +C0 */   CMC(tc0, =, tc0, s_add_t, u2); tc0.beta = 1;
    
    /* P2 */
    argslocal[0].pi = _A[0];           argslocal[1].pi = _A[1];  
    argslocal[0].m = sub_amd;	   argslocal[1].m = sub_amd; 
    argslocal[0].c = s; 	   argslocal[1].c = t;   
    argslocal[0].a = RQ2(s,a); 	   argslocal[1].a = tb3; 
    argslocal[0].b = ta0; 	   argslocal[1].b = t;   

    /* C0 += A1 * B2 */   wmaddpipe(tc0,ta1,tb2,argslocal);    
    
    /* P4 */
    /* S  = S - A0     CMC(s,    =, RQ2(s,a), s_sub,  ta0);
       T  = B3 - T     CMC(t,    =, tb3,    s_sub,  t);
    */

    /* U2 += S*T   */    wmaddpipe(u2, s, t,0);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);

    argslocal[0].m = sub_amd;
    argslocal[0].c = RQ2(t,b); 
    argslocal[0].a = tb2; 
    argslocal[0].b = RQ2(t,b); 

    argslocal[1].m = 0;
    
    /* C1 += S * B3 */   wmaddpipe(tc1, RQ1(s,a), tb3,argslocal);

    /* P7 */
    /* T = B2 - T      CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
     */

    argslocal[0].m = sub_amd;
    argslocal[0].c = s; 
    argslocal[0].a = ta0; 
    argslocal[0].b = ta2; 

    /* C2 += A3*T  */    wmaddpipe(tc2, ta3,       RQ2(t,b),argslocal); 
    tc2.beta = 1;

    /* P5 */
    /* S = A0 - A2      CMC(s,         =, ta0,       s_sub,   ta2);
     */
    /* T = B3 - B1 */     CMC(RQ1(t,b),  =, tb3,       s_sub,   tb1);
    /* U2 += S*T     */   wmaddpipe(RQ1(u2,c), s,   RQ1(t,b),0);
    /* C3  += U2   */     CMC(tc3,       =, tc3,       s_add,   RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,       =, RQ2(u2,c), s_add,   tc2); 

 
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);

  }

  free(argslocal);
  
  dept--;
  return recursive;
}



int wmpipe(DEF(c), DEF(a), DEF(b),TAddOperands *args 	     ) {
  
  c.beta = 1;
  TAddOperands *argslocal = (TAddOperands *) calloc(3,sizeof(TAddOperands));

  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {

    if (args) { 

      TAddOperands *temp = argslocal;
      int len=0;
      while (args && args[len].m) { 
	temp[len] = args[len];
	len++;
      }
      //      temp[len].pi = 4|8; 
      temp[len].m = gotmul;
      temp[len].c = c;
      temp[len].a = a;
      temp[len].b = b;
      
      MatrixComputations(temp,len+1);
    }
    else { 
      CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
    }

  }
  else {
    
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u2  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);

    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u2.data  =  (Mat *) CALLOC(u2);
    assert(s.data && t.data  && u2.data);


    /* P3 */
    /* S = A2 + A3 */    CMC(RQ2(s,a),=, ta2,     s_add,   ta3);
    /* T = B1 - B0 */    CMC(t ,=, tb1,     s_sub,   tb0);
    /* U2 = S * T   */   wmpipe(RQ2(u2,c), RQ2(s,a),     t,args);

    /* C1 +=  U2       ptcopy(tc1 ,   RQ1(u2,c),RQ1(u2,c));
       C3 +=  U2        ptcopy(tc3,  RQ3(u2,c),RQ3(u2,c)); */

    
    argslocal[0].pi= 1;                 argslocal[1].pi = _A[1];  
    argslocal[0].m = copy_matrix;	argslocal[1].m = copy_matrix; 
    argslocal[0].c = tc1; 		argslocal[1].c = tc3;   
    argslocal[0].a = RQ1(u2,c); 	argslocal[1].a = RQ3(u2,c); 
    argslocal[0].b = RQ1(u2,c);  	argslocal[1].b = RQ3(u2,c);   
    

    /* P1 */
    /* C0 = A0*B0   */    wmpipe(tc0, ta0, tb0,argslocal);
    /* U2  = C0     */    ptcopy(u2,tc0,tc0);

    /* P2 */
    argslocal[0].pi= 1;             argslocal[1].pi= 2;	   
    argslocal[0].m = sub_amd;	    argslocal[1].m = sub_amd;  
    argslocal[0].c = s; 	    argslocal[1].c = t;    
    argslocal[0].a = RQ2(s,a); 	    argslocal[1].a = tb3;  
    argslocal[0].b = ta0; 	    argslocal[1].b = t;    

    /* C0 += A1 * B2 */    wmaddpipe(tc0, ta1, tb2,argslocal);


    /* P4 */
    /* S  = S - A0     CMC(s,    =, RQ2(s,a), s_sub,  ta0);
       T  = B3 - T     CMC(t,    =, tb3,    s_sub,  t);
    */

    /* U2 += S*T   */    wmaddpipe(u2, s, t,0);
    /* C1 +=U2, */       CMC(tc1,=, tc1, s_add,  RQ1(u2,c));
    
    /* P6 */
    /* S = A1 - S */     CMC(s, =, ta1,     s_sub,   s);
    
    argslocal[0].m = sub_amd;
    argslocal[0].c = RQ2(t,b); 
    argslocal[0].a = tb2; 
    argslocal[0].b = RQ2(t,b); 

    argslocal[1].m = 0;
    
    /* C1 += S * B3 */   wmaddpipe(tc1, RQ1(s,a), tb3,argslocal);

    /* P7 */
    /* T = B2 - T      CMC(RQ2(t,b), =, tb2,    s_sub,  RQ2(t,b));
     */
    argslocal[0].m = sub_amd;
    argslocal[0].c = s; 
    argslocal[0].a = ta0; 
    argslocal[0].b = ta2; 

    /* C2 = A3*T  */    wmpipe(tc2, ta3,       RQ2(t,b),argslocal); 

    /* P5 */
    /* S = A0 - A2      CMC(s,     =, ta0,     s_sub,  ta2);
     */
    /* T = B3 - B1 */     CMC(RQ1(t,b),     =, tb3,     s_sub,  tb1);
    /* U2 += S*T     */   wmaddpipe(RQ1(u2,c), s,   RQ1(t,b),0);
    /* C3  += U2   */     CMC(tc3,        =, tc3,     s_add,  RQ3(u2,c));
    /* C2  += U2   */     CMC(tc2,        =, RQ2(u2,c),     s_add,  tc2); 

    
    FREE(s.data);
    FREE(t.data);
    FREE(u2.data);
    
  }
  
  free(argslocal);
  
  dept--;
  return recursive;
  
}

// Strassen C = A*B
int smpipe(DEF(c), DEF(a), DEF(b), TAddOperands *args 
	      ) {
  
     // We make a copy of the parallel computation and we are going to add 
  TAddOperands *argslocal ;
  c.beta =1;
  int len=0;
  while (args  && args[len].m) { 
    len++;
  }
  
  argslocal = (TAddOperands *) calloc(len + 3,sizeof(TAddOperands));
  if (args) { 
    TAddOperands *temp = argslocal;
    len=0;
    while (args  && args[len].m) { 
      temp[len] = args[len];
      len++;
    }
  }
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
    if (args) { 
      //      argslocal[len].pi = 4|8; 
      argslocal[len].m = gotmul;
      argslocal[len].c = c;
      argslocal[len].a = a;
      argslocal[len].b = b;
      
      MatrixComputations(argslocal,len+1);
    }
    else { 
      CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
    }
    
  }
  else {
    Mat *t;
    Matrix t1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta}; 
    Matrix t2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta}; 
    Matrix z1 = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta}  ; 
    Matrix z2 = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta}; 
    Matrix m  = {0, S0(c.m,c.n),S0(c.m,c.n),'n',0}; // temporary 
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c);
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);

    dept+=3;
    recursive = max(recursive,dept);

    // temporary allocation 
    t = (Mat *) calloc(2*Size(t1.M,t1.N)+2*Size(t2.M,t2.N)+Size(m.M,m.N),sizeof(Mat));
    
    t1.data = t;
    t2.data = t1.data+ Size(t1.M,t1.N);
    z1.data = t2.data +Size(t2.M,t2.N);
    z2.data = z1.data +Size(z1.M,z1.N);
    m.data  = z2.data + Size(z2.M,z2.N);

    /* T2  = B1-B3   */    CMC (RQ1(t2,b),=, tb1, s_sub,  tb3);

    argslocal[len].pi= 1;      argslocal[len+1].pi= 2;	 
    argslocal[len].m = sub_amd;    argslocal[len+1].m = add_amd;
    argslocal[len].c = z1;     argslocal[len+1].c = z2; 
    argslocal[len].a = ta2;    argslocal[len+1].a = tb0;
    argslocal[len].b = ta0;    argslocal[len+1].b = tb1;
   
    
    /* MM3 = A0*T2   */    smpipe(RQ1(m,c), ta0,  RQ1(t2,b), argslocal);
    /* C1  = M3  */        ptcopy(tc1, RQ1(m,c),RQ1(m,c)); 
    /* C3  = M3          ptcopy(tc3, RQ3(tc1,c),RQ3(tc1,c)); */

    argslocal[0].pi= 1;              argslocal[1].pi= 2;		 
    argslocal[0].m = add_amd;	     argslocal[1].m = copy_matrix;
    argslocal[0].c = RQ2(t1,a);      argslocal[1].c = tc3; 	 
    argslocal[0].a = ta2; 	     argslocal[1].a = RQ3(tc1,c); 
    argslocal[0].b = ta3; 	     argslocal[1].b = RQ3(tc1,c); 

    argslocal[2].m= 0;

    /* T1 = A2 - A0      CMC(z1,    =, ta2, s_sub,  ta0);
     * T2 = B0 + B1      CMC(z2,    =, tb0, s_add,  tb1); */
    /* MM6 = T1 * T2 */   smpipe(m, z1,   z2, argslocal);
    /* C3  += M6     */    CMC(tc3,   =, tc3, s_add,  RQ3(m,c));
    
    /* T1  = A2 + A3     CMC(RQ2(t1,a),=, ta2,       s_add,   ta3);*/
    argslocal[0].pi= 1;              argslocal[1].pi= 2;	 
    argslocal[0].m = add_amd;	     argslocal[1].m = add_amd;
    argslocal[0].c = z1; 	     argslocal[1].c = z2; 
    argslocal[0].a = ta0; 	     argslocal[1].a = tb0;
    argslocal[0].b = ta3; 	     argslocal[1].b = tb3;


    /* MM2 = T1 * B0 */    smpipe(tc2 , RQ2(t1,a),    tb0, argslocal);
    /* C3  -= M2         CMC(tc3,      =, tc3,       s_sub,   RQ3(m,c)); */
    /* C2  =  M2        ptcopy(tc2, RQ2(m,c),RQ2(m,c));*/
    argslocal[0].pi= 1;                argslocal[1].pi= 2;		
    argslocal[0].m = sub_amd;	       argslocal[1].m = add_amd;	
    argslocal[0].c = tc3; 	       argslocal[1].c = RQ1(t1,a); 
    argslocal[0].a = tc3; 	       argslocal[1].a = ta0;  	
    argslocal[0].b = RQ3(tc2,c);       argslocal[1].b = ta1;     

    
    /* T1  = A0 + A3    CMC(z1,    =, ta0, s_add,  ta3);
     * T2  = B0 + B3     CMC(z2,    =, tb0, s_add,  tb3);*/
    /* MM1 = T1*T2   */    smpipe(tc0, z1,   z2, argslocal);
    /* C3  += M1     */    CMC(tc3,   =, tc3, s_add,  RQ3(tc0,c));
    /* C0  = M1         ptcopy(tc0,m,m); */

    argslocal[0].pi= 1;             argslocal[1].pi= 2;		
    argslocal[0].m = sub_amd;	    argslocal[1].m = add_amd;	
    argslocal[0].c = RQ1(z1,a);     argslocal[1].c = RQ2(z2,b); 
    argslocal[0].a = ta1; 	    argslocal[1].a = tb2;  	
    argslocal[0].b = ta3; 	    argslocal[1].b = tb3;       

    /* T1 = A0 + A1      CMC(RQ1(t1,a),=, ta0,       s_add,   ta1);*/ 
    /* MM5 = T1 * B3 */    smpipe(RQ1(m,c), RQ1(t1,a),    tb3, argslocal);
    /* C0  -= M5     */    CMC(tc0,      =, tc0,       s_sub,   RQ1(m,c));
    /* C1  += M5     */    CMC(tc1,      =, tc1,       s_add,   RQ1(m,c));

    argslocal[0].pi= 1;
    argslocal[0].m = sub_amd;
    argslocal[0].c = RQ2(t2,b); 
    argslocal[0].a = tb2; 
    argslocal[0].b = tb0; 

    argslocal[1].m = 0;


    /* T1 = A1 - A3      CMC(RQ1(z1,a),=, ta1,    s_sub,  ta3);
     * T2 = B2 + B3      CMC(RQ2(z2,b),=, tb2,    s_add,  tb3); */
    /* MM7 = T1*T2  */     smpipe(m,  RQ1(z1,a), RQ2(z2,b),argslocal);
    /* C0  += M7    */     CMC(tc0,    =, tc0,    s_add,  m);

    /* T1 = B2 - B0      CMC(RQ2(t2,b),      =, tb2, s_sub,  tb0); */
    /* MM4 = A3*T1  */     smpipe(RQ2(m,c), ta3, RQ2(t2,b),0);
    /* C0  += M4    */     CMC(tc0,             =, tc0, s_add,  RQ2(m,c)); 
    /* C2  += M4    */     CMC(tc2,             =, tc2, s_add,  RQ2(m,c));

 
    free(t1.data);
  }
  free(argslocal);
  dept-=3;
  return recursive;
}


// Strassen C = A*B
int smaddpipe(DEF(c), DEF(a), DEF(b), TAddOperands *args ) {

  Matrix temp = c;
  temp.data =  (Mat *) CALLOC(temp);
  smpipe(temp,USE(a),USE(b),args);
  s_add_t(c,c,temp);

  return recursive;
  

  
}



int Rmul(DEF(c), DEF(a), DEF(b)) { 
  TAddOperands *args ;
  args = (TAddOperands *) calloc(5,sizeof(TAddOperands));
  
  // MM(Q0(c),Q0(a),Q0(b));   // MM(Q1(c),Q0(a),Q1(b))  //MM(Q2(c),Q2(a),Q0(b))   //MADD(Q3(c),Q2(a),Q1(b)) 
  args[0].pi =1;	      args[1].pi =2;	    	args[2].pi =4;	   	  args[3].pi =8;	    
  args[0].m = wm;	      args[1].m = wm;	    	args[2].m = wm;	   	  args[3].m = wm;	    
  args[0].c = Q0(c);	      args[1].c = Q1(c);	args[2].c = Q2(c);	  args[3].c = Q3(c);	         
  args[0].a = Q0(a);	      args[1].a = Q0(a);	args[2].a = Q2(a);	  args[3].a = Q2(a);	         
  args[0].b = Q0(b);	      args[1].b = Q1(b);        args[2].b = Q0(b);        args[3].b = Q1(b);        

  MatrixComputations(args,4);

  //MADD(Q0(c),Q1(a),Q2(b))   //MADD(Q1(c),Q1(a),Q3(b))  //MADD(Q2(c),Q3(a),Q2(b))  //MADD(Q3(c),Q3(a),Q3(b)) 
  args[0].pi =1;	      args[1].pi =2;	     	 args[2].pi =4;	    	    args[3].pi =8;	    
  args[0].m = wmadd;	      args[1].m = wmadd;	     	 args[2].m = wmadd;	    args[3].m = wmadd;	    
  args[0].c = Q0(c);	      args[1].c = Q1(c);	 args[2].c = Q2(c);	    args[3].c = Q3(c);	        
  args[0].a = Q1(a);	      args[1].a = Q1(a);	 args[2].a = Q3(a);	    args[3].a = Q3(a);	        
  args[0].b = Q2(b);	      args[1].b = Q3(b);         args[2].b = Q2(b);         args[3].b = Q3(b);        
  
  MatrixComputations(args,4);
    
  return 1;
}

// Bodrato's matrix multiply 
// Notation taken from  
// http://www.cs.duke.edu/~alvy/papers/sc98/index.htm
// Sequence taken from
// http://marco.bodrato.it/papers/Bodrato2008-StrassenLikeMatrixMultiplicationForSquares.pdf
 
 int bmaddpipe(DEF(c), DEF(a), DEF(b), TAddOperands *args ) {

   TAddOperands *argslocal = (TAddOperands *) calloc(3,sizeof(TAddOperands));
   if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
     if (args) { 
       TAddOperands *temp = argslocal;
       int len=0;
       while (args && args[len].m) { 
	 temp[len] = args[len];
	 len++;
       }
       //      temp[len].pi = _A[1]|8; 
       temp[len].m = gotmadd;
       temp[len].c = c;
       temp[len].a = a;
       temp[len].b = b;
       
       MatrixComputations(temp,len+1);
     } 
     else { 
       CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
     }
     
     
   }
   else {
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
    Matrix u = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);

    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u.data = (Mat *) CALLOC(u);
    assert(s.data && t.data  && u.data);

    /* Partial matrices */
    Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
    Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
    Matrix u3 = RQ3(u,c);

    /* P2 */
    /* S = A3 - A2 */   CMC(s2,  =, ta3,  s_sub, ta2);
    /* T = B3 - B2 */   CMC(t2,  =, tb3,  s_sub, tb2);
    /* U =  S * T  */   bmpipe(u3,s3,t3,args);
    /* *C3 +=  U */     CMC(tc3 ,=, tc3,s_add_t,  u3); tc3.beta = 1;
    /* *C1 -=  U */     CMC(tc1 ,=, tc1,s_sub_t,  u3); tc1.beta = 1;

    /* P5 */
    /* U = A1 * B2 */   bmpipe(u,  ta1,   tb2, 0);
    /* *C0 += U    */   CMC(tc0, =, tc0,s_add_t,   u); tc0.beta = 1;

    /* P4 */

    /* P2 */
    argslocal[0].pi = _A[0];           argslocal[1].pi = _A[1];  
    argslocal[0].m = add_amd;	   argslocal[1].m = add_amd; 
    argslocal[0].c = s; 	   argslocal[1].c = t;   
    argslocal[0].a = s2; 	   argslocal[1].a = t2; 
    argslocal[0].b = ta1; 	   argslocal[1].b = tb1;   

    argslocal[2].m= 0;

    /* C0 += A0 * B0 */ bmaddpipe(tc0, ta0, tb0,argslocal);
    
    /* P3 */
    /* S  = S + A1    CMC(s,   =,  s2,  s_add, ta1);*/
    /* T  = T + B1    CMC(t,   =,  t2,  s_add, tb1);*/

    /* U  += S * T */   bmaddpipe(u,   s,   t,0);


    /* C1 += U     */   CMC(tc1, =, tc1,  s_add, RQ1(u,c));
    
    /* P6 */
    /* S = A0 - S   */  CMC(s,   =, ta0,  s_sub,   s);

    argslocal[0].pi = _A[0];        
    argslocal[0].m = sub_amd;	
    argslocal[0].c = t; 	
    argslocal[0].a = tb0; 	
    argslocal[0].b = t; 	

    argslocal[1].m= 0;

    /* C1 += S * B1 */  bmaddpipe(tc1,s, tb1,argslocal);

    /* P7 */
    /* T = B0 - T     CMC(t  , =, tb0,  s_sub,   t); */
    argslocal[0].pi = _A[0];       /*    argslocal[1].pi = _A[1];   */
    argslocal[0].m = add_amd;  /*	   argslocal[1].m = add_amd; */
    argslocal[0].c = s3;       /*	   argslocal[1].c = t3;   */
    argslocal[0].a = ta3;      /*	   argslocal[1].a = tb3; */
    argslocal[0].b = ta1;      /*	    argslocal[1].b = tb1;  */ 

    argslocal[1].m= 0;
    /* *C2 += A2* T */  bmaddpipe(tc2, ta2, t, argslocal); tc2.beta = 1;

    /* P1 */
    /* S = A3 + A1    CMC(s3,  =, ta3,  s_add, ta1);    */
    /* T = B3 + B1 */   CMC(t3,  =, tb3,  s_add, tb1);	
    s3.beta = -s3.beta;
    /* U -= S*T    */   bmaddpipe(u3,  s3,  t3,0);
    /* C3 -= U     */   CMC(tc3, =, tc3,  s_sub,  u3);
    /* C2 -= U     */   CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); 

    FREE(s.data);
    FREE(t.data);
    FREE(u.data);

  }
  dept--;
  free(argslocal);
  return recursive;

}



 int bmpipe(DEF(c), DEF(a), DEF(b),TAddOperands *args) {
  
  TAddOperands *argslocal = (TAddOperands *) calloc(3,sizeof(TAddOperands));
  c.beta = 1;


  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
    if (args) { 

      TAddOperands *temp = argslocal;
      int len=0;
      while (args && args[len].m) { 
	temp[len] = args[len];
	len++;
      }
      //      temp[len].pi = 4|8; 
      temp[len].m = gotmul;
      temp[len].c = c;
      temp[len].a = a;
      temp[len].b = b;
      
      MatrixComputations(temp,len+1);
    }
    else { 
      CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
    }

  }
  else {

    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u  = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    u.data = (Mat *) CALLOC(u);
    assert(s.data && t.data  && u.data);

    /* Partial matrices */
    Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
    Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
    Matrix u3 = RQ3(u,c);

    /* P2 */
    /* S = A3 - A2 */   CMC(s2, =, ta3,  s_sub, ta2);
    /* T = B3 - B2 */   CMC(t2, =, tb3,  s_sub, tb2);
    /* C3 = S * T  */   bmpipe(tc3,  s3,   t3,args);

    /* P5 */
    /* U = A1 * B2 */   bmpipe(u,   ta1,  tb2,0);

    /* P4 */
    argslocal[0].pi = _A[0];           argslocal[1].pi = _A[1];  
    argslocal[0].m = add_amd;	   argslocal[1].m = add_amd; 
    argslocal[0].c = s; 	   argslocal[1].c = t;   
    argslocal[0].a = s2; 	   argslocal[1].a = t2; 
    argslocal[0].b = ta1; 	   argslocal[1].b = tb1;   

    argslocal[2].m= 0; 
    /* C0 = A0 * B0 */  bmpipe(tc0, ta0,   tb0, argslocal);
    /* C0 += U      */  CMC(tc0, =, tc0,  s_add,   u);

    /* P3 */
    /* S  = S + A1    CMC( s,  =,  s2,  s_add, ta1);  */
    /* T  = T + B1    CMC( t,  =,  t2,  s_add, tb1);  */

    /* U  += S * T */   bmaddpipe( u,   s,    t, 0);
    /* C1 = U - C3 */   CMC(tc1,=,RQ1(u,c),s_sub,tc3);
    
    /* P6 */
    /* S = A0 - S  */   CMC( s,  =, ta0,  s_sub,   s); 
    argslocal[0].pi = _A[0];        
    argslocal[0].m = sub_amd;	
    argslocal[0].c = t; 	
    argslocal[0].a = tb0; 	
    argslocal[0].b = t; 	
    
    argslocal[1].m= 0;
    /* C1 += S * B1 */  bmaddpipe(tc1,  s, tb1,argslocal);

    /* P7 */
    /* T = B0 - T     CMC( t,  =, tb0,  s_sub,   t);  */
    argslocal[0].pi = _A[0];      /*   argslocal[1].pi = _A[1];*/  
    argslocal[0].m = add_amd; /*   argslocal[1].m = add_amd;*/ 
    argslocal[0].c = s3;      /*   argslocal[1].c = t3;   */
    argslocal[0].a = ta3;     /*   argslocal[1].a = tb3; */
    argslocal[0].b = ta1;     /*   argslocal[1].b = tb1;   */

    argslocal[1].m= 0;
    /*  C2 += A2* T */  bmpipe(tc2, ta2,   t, argslocal);

    /* P1 */
    /* S = A3 + A1   CMC( s3, =, ta3,  s_add, ta1); */
    /* T = B3 + B1 */   CMC( t3, =, tb3,  s_add, tb1);  
    s3.beta = -s3.beta;
    /* U -= S*T    */   bmaddpipe( u3,  s3,   t3,0);
    /* C3 -= U     */   CMC(tc3, =, tc3,  s_sub,  u3);
    /* C2 -= U     */   CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); 
 
    FREE(s.data);
    FREE(t.data);
    FREE(u.data);

  }
  dept--;
  return recursive;

}

 int BMADD_PIPE(DEF(c), DEF(a), DEF(b),TAddOperands *args) {
   TAddOperands *argslocal = (TAddOperands *) calloc(4,sizeof(TAddOperands));
   c.beta = 1;

  if (debug)  printf("bm C[%c]=%dx%d += A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);

#ifdef ADAPTIVE
  if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
    if (args) { 

      TAddOperands *temp = argslocal;
      int len=0;
      while (args && args[len].m) { 
	temp[len] = args[len];
	len++;
      }
      //      temp[len].pi = 4|8; 
      temp[len].m = gotmadd;
      temp[len].c = c;
      temp[len].a = a;
      temp[len].b = b;
      
      MatrixComputations(temp,len+1);
    }
    else {
      CMC(USE(c), = , USE(a),  mm_leaf_computation_madd , USE(b));
    }
  }
  else {
    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
    Matrix v = {0, S0(a.m,a.n),S0(a.m,a.n),a.trans,a.beta};   
    Matrix z = {0, S0(b.m,b.n),S0(b.m,b.n),b.trans,b.beta};   
    Matrix u = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix w = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);

    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    v.data = (Mat *) CALLOC(v);
    z.data = (Mat *) CALLOC(z);
    u.data = (Mat *) CALLOC(u);
    w.data = (Mat *) CALLOC(w);
    assert(s.data && t.data && v.data && z.data && u.data && w.data);

    /* Partial matrices */
    Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
    Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
    Matrix z3 = RQ3(z,b);
    Matrix u3 = RQ3(u,c);
    Matrix w3 = RQ3(w,c);

    /* P1 */
    /* U  = A1 * B2 */ BMOWR_PIPE(u,ta1, tb2,args);

    /* P2 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];  
    argslocal[0].m = sub_amd;	   argslocal[1].m = sub_amd; 
    argslocal[0].c = s2; 	   argslocal[1].c = t2;   
    argslocal[0].a = ta3; 	   argslocal[1].a = tb3; 
    argslocal[0].b = ta2; 	   argslocal[1].b = tb2;   

    /* *C0 += A0*B0 */  BMADD_PIPE(tc0,ta0, tb0,argslocal); tc0.beta = 1;
    /* S  = A3 - A2  CMC(s2,  =, ta3,  s_sub, ta2); */
    /* T  = B3 - B2  CMC(t2,  =, tb3,  s_sub, tb2); */

    /* P3 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      argslocal[2].pi = _A[2];  
    argslocal[0].m = add_amd;	   argslocal[1].m = add_amd; 	 argslocal[2].m = add_amd; 
    argslocal[0].c = tc0; 	   argslocal[1].c = v;   	 argslocal[2].c = z;      
    argslocal[0].a = tc0; 	   argslocal[1].a = s2; 	 argslocal[2].a = t2;     
    argslocal[0].b = u; 	   argslocal[1].b = ta1;     	 argslocal[2].b = tb1;     

    /* W  =  S * T  */ BMOWR_PIPE(w3,  s3,    t3,argslocal);
    /* C0 += U       CMC(tc0, =, tc0,  s_add,   u); */
    /* V  = S  + A1  CMC(v,   =,  s2,  s_add, ta1); */
    /* Z  = T  + B1  CMC(z,   =,  t2,  s_add, tb1); */

    /* P4 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      
    argslocal[0].m = add_amd;	   argslocal[1].m = sub_amd; 	 argslocal[2].m = 0;
    argslocal[0].c = s3; 	   argslocal[1].c = t;   	      
    argslocal[0].a = ta3; 	   argslocal[1].a = tb0; 	 
    argslocal[0].b = ta1; 	   argslocal[1].b = z;     	 

    /* U  += V * Z  */ BMADD_PIPE(u,   v,   z, argslocal);
    /* S  = A3 + A1  CMC(s3,  =, ta3,  s_add, ta1);*/
    /* T  = B0 - Z   CMC(t,   =, tb0,  s_sub,   z);*/

    /* P5 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      
    argslocal[0].m = add_amd;	   argslocal[1].m = add_amd_t; 	
    argslocal[0].c = z3; 	   argslocal[1].c = tc1;   	      
    argslocal[0].a = tb3; 	   argslocal[1].a = tc1; 	 
    argslocal[0].b = tb1; 	   argslocal[1].b = RQ1(u,c);     	 
    /* *C2 += A2* T */ BMADD_PIPE(tc2, ta2,  t, argslocal);    tc2.beta = 1; tc1.beta = 1;
    /* Z  = B3 + B1  CMC(z3,  =, tb3,  s_add, tb1);*/
    /* C1 += U       CMC(tc1, =, tc1,s_add_t, RQ1(u,c)); */

    /* P6 */
    s3.beta = -s3.beta;
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      argslocal[2].pi = _A[2];  
    argslocal[0].m = sub_amd;	   argslocal[1].m = add_amd_t; 	 argslocal[2].m = sub_amd; 
    argslocal[0].c = v; 	   argslocal[1].c = tc3;   	 argslocal[2].c = tc1;      
    argslocal[0].a = ta0; 	   argslocal[1].a = tc3; 	 argslocal[2].a = tc1;     
    argslocal[0].b = v; 	   argslocal[1].b = w3;     	 argslocal[2].b = w3;     

    /* U -=  S * Z  */  BMADD_PIPE(u3, s3, z3,  argslocal);
    /* V  = A0 - V  CMC(v,   =, ta0,  s_sub,   v); */
    /* *C3 +=  W    CMC(tc3, =, tc3,s_add_t,  w3); */tc3.beta = 1;
    /* C1 -=  W     CMC(tc1, =, tc1,  s_sub,  w3); */

    /* P7 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      
    argslocal[0].m = sub_amd;	   argslocal[1].m = sub_amd;  argslocal[2].m = 0;
    argslocal[0].c = tc3; 	   argslocal[1].c = tc2;   	      
    argslocal[0].a = tc3; 	   argslocal[1].a = tc2; 	 
    argslocal[0].b = u3; 	   argslocal[1].b = RQ2(u,c);
     	 
    /* C1 += V * B1 */ BMADD_PIPE(tc1, v,   tb1,argslocal);
    /* C3 -= U       CMC(tc3, =, tc3,  s_sub,  u3);      */
    /* C2 -= U       CMC(tc2, =, tc2,  s_sub, RQ2(u,c)); */

    FREE(s.data);
    FREE(t.data);
    FREE(v.data);
    FREE(z.data);
    FREE(u.data);
    FREE(w.data);

  }
  dept--;
  return recursive;

}



int BMOWR_PIPE(DEF(c), DEF(a), DEF(b),TAddOperands *args) {
   TAddOperands *argslocal = (TAddOperands *) calloc(4,sizeof(TAddOperands));
   c.beta = 1;
  
  c.beta = 1;
  if (debug)  printf("bm C[%c]=%dx%d = A[%c]=%dx%d * B[%c]=%dx%d \n",c.trans,c.m,c.n,a.trans,a.m, a.n,b.trans,b.m,b.n);

#ifdef ADAPTIVE
   if (BR_P(a.m,a.n,b.n,LEAF_TEMP)) {
     //     printf("%d \n",BR_P(a.m,a.n,b.n,LEAF_TEMP));
#else 
  if (a.m<= LEAF || a.n<= LEAF || b.n<=LEAF) {
#endif
    if (args) { 

      TAddOperands *temp = argslocal;
      int len=0;
      while (args && args[len].m) { 
	temp[len] = args[len];
	len++;
      }
      //      temp[len].pi = 4|8; 
      temp[len].m = gotmul;
      temp[len].c = c;
      temp[len].a = a;
      temp[len].b = b;
      
      MatrixComputations(temp,len+1);
    }
    else {
      CMC(USE(c), = , USE(a),  mm_leaf_computation/* mul*/ , USE(b));
    }



  }
  else {

    Matrix s = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix t = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix v = {0, S0(a.m,a.n),S0(a.m,a.n),  a.trans,a.beta}; 
    Matrix z = {0, S0(b.m,b.n),S0(b.m,b.n),  b.trans,b.beta}; 
    Matrix u = {0, S0(c.m,c.n),S0(c.m,c.n),c.trans,1}; // temporary
    Matrix tc0 = Q0(c),tc1 = Q1(c), tc2 =Q2(c),tc3=Q3(c); 
    Matrix ta0 = Q0(a),ta1 = Q1(a), ta2 =Q2(a),ta3=Q3(a);
    Matrix tb0 = Q0(b),tb1 = Q1(b), tb2 =Q2(b),tb3=Q3(b);
    // temporary allocation 
    s.data = (Mat *) CALLOC(s);
    t.data = (Mat *) CALLOC(t);
    v.data = (Mat *) CALLOC(v);
    z.data = (Mat *) CALLOC(z);
    u.data = (Mat *) CALLOC(u);
    assert(s.data && t.data && v.data && z.data && u.data);

    /* Partial matrices */
    Matrix s2 = RQ2(s,a), s3 = RQ3(s,a);
    Matrix t2 = RQ2(t,b), t3 = RQ3(t,b);
    Matrix z3 = RQ3(z,b);
    Matrix u3 = RQ3(u,c);

    /* P1 */
    /* U  = A1 * B2 */ BMOWR_PIPE(u,ta1, tb2,args);

    /* P2 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      
    argslocal[0].m = sub_amd;	   argslocal[1].m = sub_amd; 	 
    argslocal[0].c = s2; 	   argslocal[1].c = t2;   	 
    argslocal[0].a = ta3; 	   argslocal[1].a = tb3; 	 
    argslocal[0].b = ta2; 	   argslocal[1].b = tb2;     	 
    /* C0 = A0 * B0 */ BMOWR_PIPE(tc0, ta0,   tb0,argslocal);
    /* S  = A3 - A2  CMC(s2,  =, ta3,  s_sub, ta2); */
    /* T  = B3 - B2  CMC(t2,  =, tb3,  s_sub, tb2); */

    /* P3 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      argslocal[2].pi = _A[2];  
    argslocal[0].m = add_amd;	   argslocal[1].m = add_amd; 	 argslocal[2].m = add_amd; 
    argslocal[0].c = tc0; 	   argslocal[1].c = v;   	 argslocal[2].c = z;      
    argslocal[0].a = tc0; 	   argslocal[1].a = s2; 	 argslocal[2].a = t2;     
    argslocal[0].b = u; 	   argslocal[1].b = ta1;     	 argslocal[2].b = tb1;     

    /* C3 = S  * T  */ BMOWR_PIPE(tc3, s3,  t3,argslocal);
    /* C0 += U       CMC(tc0, =, tc0,  s_add,   u);*/
    /* V  = S  + A1  CMC(v,   =,  s2,  s_add, ta1);*/
    /* Z  = T  + B1  CMC(z,   =,  t2,  s_add, tb1);*/

    /* P4 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      
    argslocal[0].m = add_amd;	   argslocal[1].m = sub_amd; 	 argslocal[2].m = 0;
    argslocal[0].c = s3; 	   argslocal[1].c = t;   	 
    argslocal[0].a = ta3; 	   argslocal[1].a = tb0; 	 
    argslocal[0].b = ta1; 	   argslocal[1].b = z;     	 

    /* U  += V * Z  */  BMADD_PIPE(u,  v,  z,argslocal);
    /* S  = A3 + A1  CMC(s3,  =, ta3,  s_add, ta1);  */
    /* T  = B0 - Z   CMC(t,   =, tb0,  s_sub,   z);  */

    /* P5 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      
    argslocal[0].m = add_amd;	   argslocal[1].m = sub_amd; 	 
    argslocal[0].c = z3; 	   argslocal[1].c = tc1;   	 
    argslocal[0].a = tb3; 	   argslocal[1].a = RQ1(u,c); 	 
    argslocal[0].b = tb1; 	   argslocal[1].b = tc3; 
    	 
    /* C2 = A2 * T  */ BMOWR_PIPE(tc2,ta2, t,argslocal);
    /* Z  = B3 + B1  CMC(z3,  =, tb3,  s_add, tb1);  */
    /* C1 = U  - C3  CMC(tc1, =,RQ1(u,c),s_sub,tc3); */
    
    /* P6 */
    s3.beta = -s3.beta;
    argslocal[0].pi = _A[0];       
    argslocal[0].m = sub_amd;	   argslocal[1].m = 0; 	 
    argslocal[0].c = v; 	   
    argslocal[0].a = ta0; 	   
    argslocal[0].b = v; 	   

    /* U -= S  * Z  */ BMADD_PIPE(u3, s3, z3,argslocal);
    /* V  = A0 - V   CMC(v,   =, ta0,  s_sub,   v);*/

    /* P7 */
    argslocal[0].pi = _A[0];       argslocal[1].pi = _A[1];      
    argslocal[0].m = sub_amd;	   argslocal[1].m = sub_amd; 	 
    argslocal[0].c = tc3; 	   argslocal[1].c = tc2;   	 
    argslocal[0].a = tc3; 	   argslocal[1].a = tc2;
    argslocal[0].b = u3; 	   argslocal[1].b =  RQ2(u,c);
 
    /* C1 += V * B1 */ BMADD_PIPE(tc1, v,  tb1,argslocal);
    /* C3 -= U       CMC(tc3, =, tc3,  s_sub,  u3);       */
    /* C2 -= U       CMC(tc2, =, tc2,  s_sub, RQ2(u,c));  */
 
    FREE(s.data);
    FREE(t.data);
    FREE(v.data);
    FREE(z.data);
    FREE(u.data);
  }
  dept--;
  return recursive;

}


#endif
