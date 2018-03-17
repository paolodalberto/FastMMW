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
#define  DOUBLY_COMPENSATED_SUM_MODULE 1


#include <mat-operands.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#include <pt.h>
#include <assert.h>
#include <doubly_compensated_sumc.h>

static int debug=0;






Mat sum(Mat *x, int n) {
  Mat s,s0,s1,s2,s3; 
  int i;           

  if (n<4) {       
    s = x[0];
    for (i=1;i<n;i++) {  
      s+=x[i]; 
    }
    return s; 
  } else { 
    s=0;   
    s0 = x[0]; 
    s1 = x[1];
    s2 = x[2];
    s3 = x[3]; 
    for (i=4;i<n-8;i+=4) { 
      s += s0+s1+s2+s3; 
      s0 = x[i];
      s1 = x[i+1];
      s2 = x[i+2];
      s3 = x[i+3];
    }
    s += s0+s1+s2+s3;
    for (;i<n;i++) {
      s+=x[i];
    }

    return s;
  }

}

 
Mat dcsum(Mat *x, int n) {
  Mat s_k,c_k,y_k,u_k,t_k,v_k,z_k,x_k;
  int k;
  COREDCSUM(n,k,s_k,c_k,y_k,u_k,t_k,v_k,z_k,x_k,x[0],x[k]);

  return s_k;
}

Mat sorted_dcsum(Mat *x, int n) {
  int k=0;
  SORT(x,n);
  if (debug)  { 
    k =orderTest(x,n,0);
    if (k)  {
      printf("Error increasing order array element %d\n",k);
      printV(x,n);
    }
    
    
  }
  return dcsum(x,n);
  
}
Mat sorted_sum(Mat *x, int n) {
  int k = 0;
  SORTI(x,n);
  if (debug)  { 
    k =orderTest(x,n,1);
    if (k)  {
      printf("Error decreasing order array element %d\n",k);
      printV(x,n);
    }

  }
  return sum(x,n);

}

static 
Mat regsum(Mat *x, int n) { 
  Mat res;
  int k;
  res =  x[0];
  for (k = 1; k <n; k++) {
    res += x[0];
  }

  return res;
}

Mat* partialdcsum(Mat *x, int n) {
  Mat c_k,s_k,y_k,u_k,t_k,v_k,z_k,x_k;
  int k=0;

  Mat *s = (Mat*) calloc(n,sizeof(Mat));
  assert(s);

  COREDCSUMK(n,k,s_k,c_k,y_k,u_k,t_k,v_k,z_k,x_k,x[0],x[k],s[0],s[k]);

  return s;
}



void dotproduct(Mat *z, DEF(a), DEF(b), int i, int j) { 

  int k;
  //printf("dotproduct\n");
  for (k=0;k<a.n;k++) {
    
    z[k] = E_(a.data,i,k,a.M,a.N)* E_(b.data,k,j,b.M,b.N);
    //printf("%e = %e * %e \n",z[k],E_(a.data,i,k,a.M,a.N) ,E_(b.data,k,j,b.M,b.N)); 
  }
    /*    z[k+1] = E_(a.data,i,k+1,a.M,a.N)* E_(b.data,k+1,j,b.M,b.N);
    z[k+2] = E_(a.data,i,k+2,a.M,a.N)* E_(b.data,k+2,j,b.M,b.N);
    z[k+3] = E_(a.data,i,k+3,a.M,a.N)* E_(b.data,k+3,j,b.M,b.N);
  }
  for (;k<a.n;k++) { 
    z[k+0] = E_(a.data,i,k,a.M,a.N)* E_(b.data,k,j,b.M,b.N);
    }*/
}

void dotdiff_ABS(Mat *z, Mat *a, Mat *b, int n) { 

  int k;
  //  printf("dotdiff\n");
  for (k=0;k<n;k++) { 
    z[k] =ABS(a[k]-b[k]);
    //    printf("%e = abs(%e - %e) \n",z[k], a[k],b[k]); 
  }
}

void dotmul(Mat *z, Mat *a, Mat *b, int n) { 

  int k;

  for (k=0;k<n-4;k+=4) { 
    z[k  ] =a[k  ]*b[k  ] ;
    z[k+1] =a[k+1]*b[k+1] ;
    z[k+2] =a[k+2]*b[k+2] ;
    z[k+3] =a[k+3]*b[k+3] ;
  }
  for (;k<n;k++) { 
    z[k  ] =a[k  ]*b[k  ] ;
  }  

}


static 
void *basic_dc_computation(void *arg) { 

  int i,j;
  DCMul_Data d =  *((DCMul_Data*)arg);
  Matrix c,a,b;
  Mat *temp;
  a = d.a;
  b = d.b;
  c = d.c;
  


  //  printf("D.pi %d \n",d.pi); 
  //printf("D.l %d, D.u %d \n",d.l,d.u); 

  if (d.pi > 0)  {
    int p1;
    /*    CPU_ZERO(&mask);
	  CPU_SET(mc.pi, &mask);
    */
    p1 = sched_setaffinity(0,sizeof(d.pi),&(d.pi));
    if (p1<0) { 
      printf(" Fail processor setting 1 \n");
    }
  }
  

  dcmsum(USE(c), USE(a), USE(b));
  
  return 0;
}


void dcmul(DEF(c), DEF(a), DEF(b)) {

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
			       basic_dc_computation, 
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
    
  basic_dc_computation((void*) &d[i]);
  
  for (i = 0; i<NUM_THREADS-1 && l>0; i++){
    pthread_join(p_thread[i], NULL);
  }
 

  sched_setaffinity(0,sizeof(current_mask),&(current_mask));
  

  




}




void dcmadd(DEF(c), DEF(a), DEF(b)) {

  int i,j;
  Mat *temp = (Mat*) malloc(sizeof(Mat)*a.n);
  
  for (i=0;i<a.m;i++)
    for (j=0;j<b.n;j++) { 
      dotproduct(temp,USE(a),USE(b),i,j);
      //SORT(temp,a.n);
      E_(c.data,i,j,c.M,c.N) += a.beta*b.beta*sorted_dcsum(temp,a.n);
    }
  
}

void dcmsum(DEF(c), DEF(a), DEF(b)) {

  int i,j;
  Mat *temp = (Mat*) malloc(sizeof(Mat)*a.n);

  for (i=0;i<a.m;i++)
    for (j=0;j<b.n;j++) { 
      dotproduct(temp,USE(a),USE(b),i,j);
      //SORT(temp,a.n);
      E_(c.data,i,j,c.M,c.N) = a.beta*b.beta*sorted_dcsum(temp,a.n);
    }

  
}
  
Mat max_error(Mat *diff, int size, int *k) {

  int i;
  Mat max = diff[0];
  Mat c_i;
   
  *k = 0;
  for (i=1;i<size;i++) {
    c_i = diff[i];
    if (LT(ABS(max),ABS(c_i))) { 

      max = c_i;
      *k = i;
      if (debug) printf("%e at %d\n", (double)ABS(max),i);
    }
  }
  return max;

}

Mat max_relative_error(Mat *diff, Mat *ref, int size, int *k) {

  int i;
  Mat max = diff[0]/ABS(ref[0]);
  Mat c_i;
  *k=0;
  for (i=1;i<size;i++) { 
    if (ABS(ref[i])>0) {
      c_i = diff[i]/ABS(ref[i]);
      if (LT(ABS(max),ABS(c_i))) { 
	max = c_i;
	*k = i;
	if (debug) printf("%e at %d\n", (double)ABS(max),i);
      }
    }
  }
  return max;

}


Mat average_error(Mat *diff, int size) {

  SORT(diff,size);
  return (double)(dcsum(diff,size)/(double)size);
}

double power_error(Mat *diff, int size) {

  Mat *temp = (Mat*) malloc(sizeof(Mat)*size);
  dotmul(temp,diff,diff,size);
  return sqrt(dcsum(temp,size))/((double)size);
}


void error_analysis(DEF(a),DEF(b)) { 

  int size = a.m*a.n;
  int pos; 
  double me,mre;
  double ae,pe;
  Matrix D;
  D = a;
  D.data = (Mat*) calloc(size,sizeof(Mat));
  //  printf("Computing the difference\n");
  //print(a);
  //print(b);
  dotdiff_ABS(D.data,a.data,b.data,size);
  //printf(" dot error matrix \n");
  //print(D);
  //SORT(D.data,D.m*D.n);
  //printf(" dot error matrix sorted \n");
  //print(D);
  //printf(" computing max error\n");
  me = max_error(D.data,size,&pos);
  printf("Maximum-absolute-error  %e ", ABS(me)); 
#if(COLUMN_MAJOR) 
  printf("row %d col %d ",pos%D.M,pos/D.M);
#endif
#if(ROW_MAJOR) 
  printf("row %d col %d ",pos/D.N,pos%D.N);
#endif
  pos = 0;
  //printf(" computing max relative error\n");
  mre = max_relative_error(D.data,b.data,size,&pos);
  printf(" Maximum-absolute-relative-error  %e ", ABS(mre)); 
#if(COLUMN_MAJOR) 
  printf("row %d col %d",pos%D.M,pos/D.M);
#endif
#if(ROW_MAJOR) 
  printf("row %d col %d",pos/D.N,pos%D.N);
#endif
  
  
  //  printf(" computing average error\n");
  //  ae = average_error(D.data,size);
  //printf(" Average error  %e ", ae); 
  //  printf(" computing power error\n");
  //pe = power_error(D.data,size);

  //printf(" Power error  %e \n", pe); 
  
  free(D.data);
}

