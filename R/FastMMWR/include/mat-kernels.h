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
#ifndef MATKERNEL 
#define MATKERNEL 1
#include <matrixExtra.h>
#define XSCALE 1

#define READC_2x4(i,j) \
  c00 = c[i*cN+j+0];      c01 = c[i*cN+j+1];         c02 = c[i*cN+j+2];        c03 = c[i*cN+j+3]; \
  c10 = c[(i+1)*cN+j+0];  c11 = c[(i+1)*cN+j+cN+1];  c02 = c[(i+1)*cN+j+cN+2]; c03 = c[(i+1)*cN+j+cN+3];  

#define WRITEC_2x4(i,j) \
    c[i*cN+j+0]     = c00;  c[i*cN+j+1]        = c01;  c[i*cN+j+2]        = c02; c[i*cN+j+3]        = c03; \
    c[(i+1)*cN+j+0] = c10;  c[(i+1)*cN+j+cN+1] = c11;  c[(i+1)*cN+j+cN+2] = c02; c[(i+1)*cN+j+cN+3] = c03; \

#define READC_2x3(i,j) \
  c00 = c[i*cN+j+0];      c01 = c[i*cN+j+1];         c02 = c[i*cN+j+2];        \
  c10 = c[(i+1)*cN+j+0];  c11 = c[(i+1)*cN+j+cN+1];  c02 = c[(i+1)*cN+j+cN+2];   

#define WRITEC_2x3(i,j) \
    c[i*cN+j+0]     = c00;  c[i*cN+j+1]        = c01;  c[i*cN+j+2]        = c02; \
    c[(i+1)*cN+j+0] = c10;  c[(i+1)*cN+j+cN+1] = c11;  c[(i+1)*cN+j+cN+2] = c02; \

#define READC_2x2(i,j) \
  c00 = c[i*cN+j+0];      c01 = c[i*cN+j+1];         \
  c10 = c[(i+1)*cN+j+0];  c11 = c[(i+1)*cN+j+cN+1];    

#define WRITEC_2x2(i,j) \
    c[i*cN+j+0]     = c00;  c[i*cN+j+1]        = c01;  \
    c[(i+1)*cN+j+0] = c10;  c[(i+1)*cN+j+cN+1] = c11;  \


#define READA_2x1(i,k) \
  a00 = a[i*aN+k];\
  a10 = a[(i+1)*aN+k];

#define READB_1x1(B,k,j)  B = b[k*aN+j];


#ifndef MODULE_MATKERNEL

void gemm_xscale(DEFC, DEFA, DEFB);
void gemm_RF_32K(DEFC, DEFA, DEFB); 

#endif
#endif
