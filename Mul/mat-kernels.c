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
/****************************************************
 *
 *
 *
 *
 *
 *
 */

#define MODULE_MATKERNEL 1
#include <mat-kernels.h>




inline void gemm_RF_32K(DEFC, DEFA, DEFB) { 
  int i,j,k;
  register Mat c00, c01, c02, c03;
  register Mat c10, c11, c12, c13;
  Mat a00, a10;
  Mat b00, b01;

  for (i=0;i<cm;i+=2) {
   
    for (j=0;j<cn;j+=4) {
      READC_2x4(i,j);
      READA_2x1(i,0);
      READB_1x1(b00,0,j);
      READB_1x1(b01,0,j+1);
    
    
      for (k=0;k<an-1;k++) {
	
	c00 += a00*b00; c10 +=a10*b00; 
	READB_1x1(b00,k,j+2);
	c01 += a00*b01; c11 +=a10*b01; 
	READB_1x1(b01,k,j+3);
	c02 += a00*b00; c12 +=a10*b00; 
	READB_1x1(b00,k+1,j);
	c03 += a00*b01; c13 +=a10*b01; 
	READB_1x1(b01,k+1,j+1);
	READA_2x1(i,k+1);
	
      }
      c00 += a00*b00; c10 +=a10*b00; 
      READB_1x1(b00,k,j+2);
      c01 += a00*b01; c11 +=a10*b01; 
      READB_1x1(b01,k,j+3);
      c02 += a00*b00; c12 +=a10*b00; 
      c03 += a00*b01; c13 +=a10*b01; 
      WRITEC_2x4(i,j);
      
    }
  }
}

inline void gemm_RF_32K_8(DEFC, DEFA, DEFB) { 
  int i,j,k;
  register Mat c00, c01;
  register Mat c10, c11;
  register Mat a00, a10;
  register Mat b00, b01;

  for (i=0;i<cm;i+=2) {
   
    for (j=0;j<cn;j+=2) {
      READC_2x2(i,j);
      READA_2x1(i,0);
      READB_1x1(b00,0,j);
      READB_1x1(b01,0,j+1);
    
    
      for (k=0;k<an-1;k++) {
	
	c00 += a00*b00; c10 +=a10*b00; 
	READB_1x1(b00,k+1,j);
	c01 += a00*b01; c11 +=a10*b01; 
	READB_1x1(b01,k+1,j);
	READA_2x1(i,k+1);
	
      }
      c00 += a00*b00; c10 +=a10*b00; 
      READB_1x1(b00,k+1,j);
      c01 += a00*b01; c11 +=a10*b01; 
      READB_1x1(b01,k+1,j);
      READA_2x1(i,k+1);
      WRITEC_2x2(i,j);
      
    }
  }
}
inline void gemm_RF_32K_10(DEFC, DEFA, DEFB) { 
  int i,j,k;
  register Mat c00, c01,c02;
  register Mat c10, c11,c12;
  register Mat a00, a10;
  register Mat b00, b01;

  for (i=0;i<cm;i+=2) {
   
    for (j=0;j<cn;j+=3) {
      READC_2x3(i,j);
      READA_2x1(i,0);
      READB_1x1(b00,0,j);
      READB_1x1(b01,0,j+1);
    
    
      for (k=0;k<an-1;k++) {
	
	c00 += a00*b00; c10 +=a10*b00; 
	READB_1x1(b00,k,j+2);
	c01 += a00*b01; c11 +=a10*b01; 
	c02 += a00*b00; c12 +=a10*b00; 
	READB_1x1(b00,k+1,j);
	READB_1x1(b01,k+1,j+1);
	READA_2x1(i,k+1);
	
      }
      c00 += a00*b00; c10 +=a10*b00; 
      READB_1x1(b00,k+1,j);
      c01 += a00*b01; c11 +=a10*b01; 
      READB_1x1(b01,k+1,j);
      READA_2x1(i,k+1);
      WRITEC_2x3(i,j);
      
    }
  }
  
}

#define TILE 16


inline void gemm_xscale(DEFC, DEFA, DEFB) { 
  int i,j,k;
  Mat temp;
  i=0;
 

  for (i=0;i<cm-TILE;i+=TILE) {
    j=0;
    for (j=0;j<cn-TILE;j+=TILE) {
      for (k=0;k<an-TILE;k+=TILE) {
	gemm_RF_32K_8(c+i*cN+j,TILE,TILE,cM,cN, 
		      a+i*aN+k,TILE,TILE,aM,aN,
		      b+k*bN+j,TILE,TILE,bM,bN);
      }
      temp = c[i*cN+j];
      for (;k<an;k++)
	temp +=a[i*aN+k]*b[k*bN+j];
      c[i*cN+j] = temp;
    }
    for (;j<cn;j++) {
      temp = c[i*cN+j];
      for (k=0;k<an;k++) {
	temp +=a[i*aN+k]*b[k*bN+j];
      }
      c[i*cN+j] = temp;
    }

  }
  for (;i<cm;i++) {
    for (j=0;j<cn;j++) {
      temp = c[i*cN+j];
      for (k=0;k<an;k++) {
	temp +=a[i*aN+k]*b[k*bN+j];
      }
      c[i*cN+j] = temp;
    }
  }

}



