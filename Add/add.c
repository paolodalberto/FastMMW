/* 
   Copyright 2011 Paolo D'Alberto, Marco Bodrato, and Alexandru
   Nicolau

`   This file is part of the Fast Matrix Multiply library (FMM).
      
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

// C = A + B 
void add_t(DEF(c), DEF(a), DEF(b)) { 

  int i,j,x,y;

   /* minimum sizes */
   x = min(a.m,b.m); y = min(a.n,b.n);

   for (i=0; i<x; i++) {
     /* core of the computation */
     for (j=0;j<y;j++)  
       E_(c.data,i,j,c.M,c.N) = a.beta*E_(a.data,i,j,a.M,a.N) 
	                      + b.beta*E_(b.data,i,j,b.M,b.N);

     if (y<a.n)	 /* A is larger than B */
       E_(c.data,i,j,c.M,c.N) =  a.beta*E_(a.data,i,j,a.M,a.N) ; 
     else 
       if (y<b.n) /* B is larger than A */
	 E_(c.data,i,j,c.M,c.N) = b.beta*E_(b.data,i,j,b.M,b.N); 
   }
   /* last row */
   if (x<a.m)  {/* A is taller than B */
     for (j=0;j<a.n;j++)  
       E_(c.data,i,j,c.M,c.N)  = a.beta*E_(a.data,i,j,a.M,a.N);
   }
   if (x<b.m)  {/* B is taller than A */
     for (j=0;j<b.n;j++)   
       E_(c.data,i,j,c.M,c.N) = b.beta*E_(b.data,i,j,b.M,b.N);
   }
   //   c.beta = 1;
}
