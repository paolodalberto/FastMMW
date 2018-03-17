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

#ifndef MAT_OPERANDS_3
#define MAT_OPERANDS_3

#include<mat-operands.h>

static inline int HHH(int n, int b) {
  if ((n%b)==0)
    return n/b;
  else
    return n/b+1;
}

static inline int LLL(int n, int b) {
  return (n - HHH(n,b)*(b-1));
}


static inline int width(Matrix A,int i, int j, int base) {
  return (j==base-1)? (LLL(A.n,base)) : (HHH(A.n,base));
}
static inline int hight(Matrix A,int i, int j, int base) {
  return (i==base-1)? (LLL(A.m,base)) : (HHH(A.m,base));
}
static inline int prevwidth(Matrix A,int i, int j, int base) {
  return (j==base-1)? (A.n - LLL(A.n,base)) : ((j)*HHH(A.n,base));
}
static inline int prevhight(Matrix A,int i, int j, int base) {
  return (i==base-1)? (A.m-LLL(A.m,base)) : ((i)*HHH(A.m,base));
}




static inline 
Matrix PQQ(Matrix A, int pos, int base) {

  int W,H;
  int i, j;

  i = pos/base;
  j = pos % base;
  
  W = width(A,i,j,base);
  H = hight(A,i,j,base);

  printf(""); 
  
  Matrix x0 = {
    A.data+
#if(ROW_MAJOR)
    prevhight(A,i,j,base)*A.N+prevwidth(A,i,j,base),
#elif(COLUMN_MAJOR)
    prevhight(A,i,j,base)+prevwidth(A,i,j,base)*A.M,
#endif
    H,W,
    A.M, A.N, A.trans,A.beta
#if(CLBLAS)
    , A.gpu
#endif
  };
 
  return x0;
}

static inline 
Matrix PQQ2(Matrix A, int m, int n, int basem, int basen) {

  int W,H;
  W = width(A,m,n,basem);
  H = hight(A,m,n,basen);
  
  Matrix x0 = {
    A.data+
#if(ROW_MAJOR)
    prevhight(A,m,n,basen)*A.N+prevwidth(A,m,n,basem),
#elif(COLUMN_MAJOR)
    prevhight(A,m,n,basen)+prevwidth(A,m,n,basem)*A.M,
#endif
    H,W,
    A.M, A.N, A.trans,A.beta
#if(CLBLAS)
    , A.gpu
#endif
  };
  return x0;
}





#endif
