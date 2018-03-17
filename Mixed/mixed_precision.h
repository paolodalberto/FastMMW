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
#ifndef MIXED_PRECISION_OPERATION
#define MIXED_PRECISION_OPERATION
// C != A 
extern int  comp_s_d(S_Matrix c,D_Matrix a);
extern int  comp_c_z(C_Matrix c,Z_Matrix a) ;
extern int  comp_s_c(S_Matrix RE, S_Matrix IM,C_Matrix a);
extern int  comp_d_z(D_Matrix RE, D_Matrix IM,Z_Matrix a);
extern C_Matrix  from_s_to_c(S_Matrix RE, S_Matrix IM);
extern Z_Matrix  from_d_to_z(D_Matrix RE, D_Matrix IM);
extern S_Matrix *from_c_to_s(C_Matrix a);
extern D_Matrix *from_z_to_d(Z_Matrix d);
extern void      error_analysis_s_d(S_Matrix a, D_Matrix b);
extern void      error_analysis_c_z(C_Matrix a, Z_Matrix b);


#endif
