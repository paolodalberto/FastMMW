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
#define GETTIME
#include <architecture.h>
#include <mat-operands.h>
#include <mat-mulkernels.h>
#include <mat-addkernels.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#include <stdio.h>

#define ERROR_K 
#ifdef ERROR_K
#define RAND0 (((rand()%2)?1:-1)*drand48())
#define RAND1 (drand48())
#endif
#ifndef ERROR_K
#define RAND0 (rand()%99)
#define RAND1 (fabs(rand()%99))
#endif

extern Matrix read_from_file(FILE *);

int main() { 

  int m,n,p,s;
  int i,j,k ;
  int ii,jj;
  double t;
  Matrix c,a,b,temp,g;
  int mask = 4|8;
  struct timeval _t1,_t2;
  double current_time;
  char filename[100];
  FILE *rep;

  gettimeofday(&_t2,NULL);   
  current_time= (_t2.tv_sec)+ (double)(_t2.tv_usec)/1000000;    


  printf("Destination file\n");
  scanf("%s", filename);
  rep = fopen(filename,"r");

  printf("Creation ...\n");
  
	
  printf("Initialization ...\n");

  
  a = read_from_file(rep);
  b = read_from_file(rep);
  temp = g = c = read_from_file(rep);

  print(a);
  print(b);
  print(c);

  while (c.data) { 

  
    temp.data = (Mat *) CALLOC(temp);
    g.data    = (Mat *) CALLOC(g);
	

    printf("RBC \n");
    START_CLOCK; 
    CMC(temp , =, a, mulpt, b);
    END_CLOCK;
    printf("multiplications row by column vs DCS"); error_analysis(temp,c);printf("\n");
    
    printf("Goto \n");
    START_CLOCK;
    CMC(g , =, a,  mm_leaf_computation, b);
    END_CLOCK;
    

    printf("\n ATLAS/GOTO w.r.t. DCS ");  error_analysis(c,g);printf("\n");
    printf(" ATLAS/GOTO w.r.t. RBC ");  error_analysis(c,temp);printf("\n");
    
    printf("Winograd mm \n");
    START_CLOCK; 
    CMC(temp , =, a,  wm, b);
    END_CLOCK;
    printf("\n Winograd w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
    printf(" Winograd w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");
  
    printf("Winograd-Marco mm \n");
    START_CLOCK; 
    CMC(temp , =, a,  bm, b);
    END_CLOCK;
    printf("\n Winograd-marco w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
    printf(" Winograd-marco w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");


    printf("Winograd mm pipe \n");
    START_CLOCK; 
    wmpipe(temp , a, b,0);
    END_CLOCK;
    printf("\n Winograd w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
    printf(" Winograd w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");
    
    printf("Winograd-Marco mm pipe\n");
    START_CLOCK; 
    bmpipe(temp , a, b,0);
    END_CLOCK;
    printf("\n Winograd-marco w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
    printf(" Winograd-marco w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");
    
    printf("Strassen mm \n");
    START_CLOCK; 
    CMC(temp , =, a,  smul, b);
    END_CLOCK;
    printf("\n Strassen w.r.t. DCS  ");  error_analysis(temp,c);printf("\n");
    printf(" Strassen w.r.t. GOTO ");  error_analysis(temp,g);printf("\n");
    //  printf("\n multiplications row by column ");
    
  
#if(SINGLE_COMPLEX || DOUBLE_COMPLEX)
    printf("3M Gotos mm \n");
    START_CLOCK; 
    CMC(temp , =, a,  mm_leaf_computation_3m, b);
    END_CLOCK; 
    printf("\n Gotos' 3M w.r.t. DCS   ");  error_analysis(temp,c);printf("\n");
    printf(" Gotos' 3M w.r.t. GOTO  ");  error_analysis(temp,g);printf("\n");
#endif
   

  
  
    FREE(a.data);
    FREE(b.data);
    FREE(c.data);
    FREE(temp.data);
    
    a = read_from_file(rep);
    b = read_from_file(rep);
    temp = g = c = read_from_file(rep);


  }

return 0;
}
