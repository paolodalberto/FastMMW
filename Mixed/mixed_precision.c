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


#include <stdlib.h>
#include <stdio.h>

#include<mat-operands.h>
#include <math.h>
#include <complex.h>
#include <doubly_compensated_sumc.h>
#ifndef min
#define min(x,y) (((x)<=(y))?(x):(y))
#endif

// C != A 
int  comp_s_d(S_Matrix c,D_Matrix a) { 
  int i,j;
  int rows, cols;
  int equal =0;
  double temp;
  rows = min(c.m,a.m);
  cols = min(c.n,a.n);


  for (i=0;i<rows;i++) {
    for (j=0;j<cols;j++) { 
      temp = (E_(c.data,i,j,c.M,c.N) - E_(a.data,i,j,a.M,a.N));
      if (temp != 0) {
	equal++;
      }

    }
  }
  return equal;
}

// C != A 
int  comp_c_z(C_Matrix c,Z_Matrix a) { 
  int i,j;
  int diff;
  int rows, cols;
  int equal =0;
  double complex temp;
  rows = min(c.m,a.m);
  cols = min(c.n,a.n);

  for (i=0;i<rows;i++) {
    for (j=0;j<cols;j++) { 
      temp = (E_(c.data,i,j,c.M,c.N) - E_(a.data,i,j,a.M,a.N));
      diff = (cabs(temp)>0)?1:0;
      if (diff) {
	equal++;
      }
      
    }
    
  }
  
  return equal;
}



// C != A 
int  comp_s_c(S_Matrix RE, S_Matrix IM,C_Matrix a) { 
  int i,j;
  int diff;
  int rows, cols;
  int equal =0;
  float complex temp;
  float complex up;
  rows = min(a.m,RE.m);
  cols = min(a.n,RE.n);

  for (i=0;i<rows;i++) {
    for (j=0;j<cols;j++) { 
      up = E_(RE.data,i,j,RE.M,RE.N) + E_(IM.data,i,j,IM.M,IM.N)*I;
      temp = up - E_(a.data,i,j,a.M,a.N);
      diff = (cabs(temp)>0)?1:0;
      if (diff) {
	equal++;
      }
      
    }
    
  }

  return equal;
}
// C != A 
int  comp_d_z(D_Matrix RE, D_Matrix IM,Z_Matrix a) { 
  int i,j;
  int diff;
  int rows, cols;
  int equal =0;
  double complex temp;
  double complex up;
  rows = min(a.m,RE.m);
  cols = min(a.n,RE.n);

  for (i=0;i<rows;i++) {
    for (j=0;j<cols;j++) { 
      up = E_(RE.data,i,j,RE.M,RE.N) + E_(IM.data,i,j,IM.M,IM.N)*I;
      temp = up - E_(a.data,i,j,a.M,a.N);
      diff = (cabs(temp)>0)?1:0;
      if (diff) {
	equal++;
      }
      
    }
    
  }

  return equal;
}


// C != A 
C_Matrix  from_s_to_c(S_Matrix RE, S_Matrix IM) { 
  int i,j;
  int rows, cols;
  C_Matrix result; 

  rows = min(RE.m,IM.m);
  cols = min(RE.n,IM.n);
  
  result.trans = RE.trans;
  result.beta = RE.beta*IM.beta+0*I;
  result.m=result.M = rows;
  result.n=result.N = cols;
  
  result.data = (float complex *) calloc(rows*cols, sizeof(float complex));
  
  for (i=0;i<rows;i++) 
    for (j=0;j<cols;j++)  
      E_(result.data,i,j,result.M,result.N) = E_(RE.data,i,j,RE.M,RE.N) + E_(IM.data,i,j,IM.M,IM.N)*I;
    
    
  return result;
}
// C != A 
Z_Matrix  from_d_to_z(D_Matrix RE, D_Matrix IM) { 
  int i,j;
  int rows, cols;
  Z_Matrix result; 
  
  rows = min(RE.m,IM.m);
  cols = min(RE.n,IM.n);

  result.trans = RE.trans;
  result.beta = RE.beta*IM.beta+0*I;
  result.m=result.M = rows;
  result.n=result.N = cols;
  
  result.data = (double complex *) calloc(rows*cols, sizeof(double complex));
  
  for (i=0;i<rows;i++) 
    for (j=0;j<cols;j++) { 
      E_(result.data,i,j,result.M,result.N) = E_(RE.data,i,j,RE.M,RE.N) + E_(IM.data,i,j,IM.M,IM.N)*I;
    }
    
  return result;
}


// C != A 
S_Matrix *from_c_to_s(C_Matrix a) { 
  int i,j;
  int rows, cols;
  S_Matrix *result; 

  rows = a.m;
  cols = a.n;
  
  result = (S_Matrix *) calloc(2,sizeof(S_Matrix)); 
  
  result[0].trans = a.trans;
  result[0].beta = creal(a.beta);
  result[1].trans = a.trans;
  result[1].beta = creal(a.beta);
  result[0].m=result[0].M = rows;
  result[0].n=result[0].N = cols;
  result[1].m=result[1].M = rows;
  result[1].n=result[1].N = cols;
  
  result[0].data = (float *) calloc(rows*cols, sizeof(float ));
  result[1].data = (float *) calloc(rows*cols, sizeof(float ));
  
  for (i=0;i<rows;i++) 
    for (j=0;j<cols;j++) {
      E_(result[0].data,i,j,result[0].M,result[0].N) = creal(E_(a.data,i,j,a.M,a.N));
      E_(result[1].data,i,j,result[1].M,result[1].N) = cimag(E_(a.data,i,j,a.M,a.N));
    }
    
  return result;
}
// C != A 
D_Matrix *from_z_to_d(Z_Matrix a) { 
  int i,j;
  int rows, cols;
  D_Matrix *result; 

  rows = a.m;
  cols = a.n;
  
  result = (D_Matrix *) calloc(2,sizeof(D_Matrix)); 
  
  result[0].trans = a.trans;
  result[0].beta = creal(a.beta);
  result[1].trans = a.trans;
  result[1].beta = creal(a.beta);
  result[0].m=result[0].M = rows;
  result[0].n=result[0].N = cols;
  result[1].m=result[1].M = rows;
  result[1].n=result[1].N = cols;
  
  result[0].data = (double *) calloc(rows*cols, sizeof(double ));
  result[1].data = (double *) calloc(rows*cols, sizeof(double ));
  
  for (i=0;i<rows;i++) 
    for (j=0;j<cols;j++) {
      E_(result[0].data,i,j,result[0].M,result[0].N) = creal(E_(a.data,i,j,a.M,a.N));
      E_(result[1].data,i,j,result[1].M,result[1].N) = cimag(E_(a.data,i,j,a.M,a.N));
    }
    
  return result;
}




void dotdiff_ABS_S_D(double  *z, float *a, double *b, int n) { 

  int k;
  //  printf("dotdiff\n");
  for (k=0;k<n;k++) { 
    z[k] =fabs(((double)a[k])-b[k]);
    //    printf("%e = abs(%e - %e) \n",z[k], a[k],b[k]); 
  }
  //  printf(" k=%d\n",k);
}
void dotdiff_ABS_C_Z(double *z, float complex *a, double complex *b, int n) { 

  int k;
  //  printf("dotdiff\n");
  for (k=0;k<n;k++) { 
    z[k] =cabs(((double complex)a[k])-b[k]);
    //    printf("%e = abs(%e - %e) \n",z[k], a[k],b[k]); 
  }

}


void error_analysis_s_d(S_Matrix a,D_Matrix b) { 

  int size = a.m*a.n;
  int pos; 
  double me,mre;
  double ae,pe;
  D_Matrix D;

  
  D.m =D.M = a.m;
  D.n =D.N = a.n;
  D.trans = a.trans;
  s_print(a); printf("%f\n", a.data[0]);
  d_print(b); printf("%e\n", b.data[0]);
  printf("size %d\n",size);
  D.data = (double *) calloc(size,sizeof(double));
  dotdiff_ABS_S_D(D.data,a.data,b.data,size);
  //for (int i=0;i<size;i++) 
  //  printf("%f %e %e \n",a.data[i],b.data[i],D.data[i]) ;
  //printf(" computing max error %d %d %d \n",size, a.M*a.M,b.M*b.N);
  me = d_max_error(D.data,size,&pos);
  printf("Maximum-absolute-error  %e ", fabs(me)); 
#if(COLUMN_MAJOR) 
  printf("row %d col %d %d ",pos%D.M,pos/D.M,pos);
#endif
#if(ROW_MAJOR) 
  printf("row %d col %d %d ",pos/D.N,pos%D.N,pos);
#endif

  pos = 0;
  //printf(" computing max relative error\n");
  mre = d_max_relative_error(D.data,b.data,size,&pos);
  printf(" Maximum-absolute-relative-error  %e ", fabs(mre)); 
#if(COLUMN_MAJOR) 
  printf("row %d col %d",pos%D.M,pos/D.M);
#endif
#if(ROW_MAJOR) 
  printf("row %d col %d",pos/D.N,pos%D.N);
#endif
  printf("\n");
  free(D.data);
}
void error_analysis_c_z(C_Matrix a,Z_Matrix b) { 

  int size = a.m*a.n;
  int pos; 
  double me,mre;
  double ae,pe;
  D_Matrix D;
  D.m =D.M = a.m;
  D.n =D.N = a.n;
  D.trans = a.trans;

  D.data = (double complex *) calloc(size,sizeof(double complex));
  dotdiff_ABS_C_Z(D.data,a.data,b.data,size);
  //printf(" computing max error ");
  for (int i=0;i<size;i++) 
    printf("%f %e %e \n",a.data[i],b.data[i],D.data[i]) ;
  
  me = d_max_error(D.data,size,&pos);
  printf("Maximum-absolute-error  %e ", fabs(me)); 
#if(COLUMN_MAJOR) 
  printf("row %d col %d ",pos%D.M,pos/D.M);
#endif
#if(ROW_MAJOR) 
  printf("row %d col %d ",pos/D.N,pos%D.N);
#endif
  pos = 0;
  //printf(" computing max relative error\n");
  mre = d_max_relative_error(D.data,b.data,size,&pos);
  printf(" Maximum-absolute-relative-error  %e ", fabs(mre)); 
#if(COLUMN_MAJOR) 
  printf("row %d col %d",pos%D.M,pos/D.M);
#endif
#if(ROW_MAJOR) 
  printf("row %d col %d",pos/D.N,pos%D.N);
#endif
  
  free(D.data);
}
