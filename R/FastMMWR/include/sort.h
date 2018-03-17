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
#ifndef __SORT_H__
#define __SORT_H__



#include <math.h>
#include <float.h>
#include <mat-operands.h>

typedef struct processor_pool Processor_Pool;
typedef struct sort_bundle    Sort_Datum;


struct processor_pool {
  int *p;
  int l;
  int u;

};
struct sort_bundle {
  Processor_Pool p;
  Mat *array;
  int l;
  int u;
};






#define GT(x, y) ((x) > (y))
#define LT(x, y) ((x) < (y))
#define GE(x, y) ((x) >= (y))
#define LE(x, y) ((x) <= (y))
#define EQ(x, y) ((x) == (y))
#define NE(x, y) ((x) != (y))

#define SWAP(x, y)    {				\
    Mat temp;					\
    temp = (x);					\
    (x) = (y);					\
    (y) = temp;					\
  }


#endif


