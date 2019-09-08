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
/*****************************************************
 *
 * This is a code generator for the mad-addkernel.h file. 
 * I specify the unrolling to be used in the inner kernel of the MA.
 *
 */ 


#include <stdio.h>

int main(int argc, char **argv) { 

  int unroll;
  int i;

  printf("/* arguments %d unroll %s */\n",argc,argv[1]);  
  printf("/* This file has been automatically generated  */\n");  

  if (argc<2) unroll=16; 
  else unroll = atoi(argv[1]);


  printf("#ifndef MAT_ADD_KERNELS \n"); 
  printf("#define MAT_ADD_KERNELS 1 \n");
  printf("#include <mat-operands.h> \n");

  printf("#define fpmul(frac,a,b)  ((int)((((long long )(a))*((long long )(b)))>>(frac))) \n");
  printf("#define fpmadd(c, a, b)  c+=(a)*(b) //c+=fpmul((FRAC),(a),(b)) \n");




  // read
  printf("#define UNLOOPREADAT(a,j) { \\\n");
  for(i=0;i<unroll;i++) {  
    printf("a%d = a[j+%d]; \\\n",i,i);
  }
  printf("}\n");
  // write
  printf("#define UNLOOPWRITEAT(a,j) { \\\n");		
  for(i=0;i<unroll;i++) {  
    printf("a[j+%d] = a%d; \\\n",i,i);
  }
  printf("}\n");
  // read and add
  printf("#define UNLOOPCOMPUTE(b,j) { \\\n");		
  for(i=0;i<unroll;i++) {  
    printf("a%d += b[j+%d]; \\\n",i,i);
  }
  printf("}\n");
  // read and subtract
  printf("#define UNLOOPCOMPUTESUB(b,j) { \\\n");	
  for(i=0;i<unroll;i++) {  
    printf("a%d -= b[j+%d]; \\\n",i,i);
  }
  printf("}\n");

  // read * beta
  printf("#define UNLOOPREADAT_t(a,j,beta) { \\\n");		
  for(i=0;i<unroll;i++) {  
    printf("a%d = beta*a[j+%d]; \\\n",i,i);
  }
  printf("}\n");
  // read and add
  printf("#define UNLOOPCOMPUTE_t(b,j,beta) { \\\n");		
  for(i=0;i<unroll;i++) {  
    printf("a%d += beta*b[j+%d]; \\\n",i,i);
  }
  printf("}\n");
  // read and subtract
  printf("#define UNLOOPCOMPUTESUB_t(b,j,beta) { \\\n");	
  for(i=0;i<unroll;i++) {  
    printf("a%d -= beta*b[j+%d]; \\\n",i,i);
  }
  printf("}\n");

  printf("#ifdef ROW_MAJOR\n");
  printf("#define UNROLLKERNEL(c,a,b,i,j,y,COMPUTATION)\\\n");
  printf("if (2*%d<y) {\\\n",unroll);
  printf("UNLOOPREADAT((a.data+i*a.N),0);\\\n");
  printf("  for (j=0;j<y-2*%d;j+=%d) {\\\n",unroll,unroll);
  printf("      COMPUTATION((b.data+i*b.N),j);	\\\n");
  printf("      UNLOOPWRITEAT((c.data+i*c.N),j);\\\n");
  printf("      UNLOOPREADAT((a.data+i*a.N),j+%d);\\\n",unroll);
  printf("    }\\\n");
  printf("  COMPUTATION((b.data+i*b.N),j);\\\n");
  printf("  UNLOOPWRITEAT((c.data+i*c.N),j);\\\n");
  printf("  j+=%d;}\n",unroll);

  printf("#define UNROLLKERNEL_t(c,a,b,i,j,y,COMPUTATION)\\\n");
  printf("if (2*%d<y) {\\\n",unroll);
  printf("  UNLOOPREADAT_t((a.data+i*a.N),0,a.beta);\\\n");
  printf("\\\n");
  printf("    for (j=0;j<y-2*%d;j+=%d) { \\\n",unroll,unroll);
  printf("      COMPUTATION((b.data+i*b.N),j,b.beta);	 \\\n");
  printf("      UNLOOPWRITEAT((c.data+i*c.N),j); \\\n");
  printf("      UNLOOPREADAT_t((a.data+i*a.N),j+%d,a.beta);	\\\n",unroll);
  printf("    }\\\n");
  printf("  COMPUTATION((b.data+i*b.N),j,b.beta);    \\\n");
  printf("  UNLOOPWRITEAT((c.data+i*c.N),j); \\\n");
  printf("  j+=%d;}\n",unroll);
  printf("#endif\n");

  printf("#ifdef COLUMN_MAJOR\n");
  printf("#define UNROLLKERNEL(c,a,b,i,j,y,COMPUTATION)	\\\n");
  printf("if (2*%d<x) {\\\n",unroll);
  printf("  UNLOOPREADAT((a.data+j*a.M),0); \\\n");
  printf("\\\n");
  printf("    for (i=0;i<x-2*%d;i+=%d) { \\\n",unroll,unroll);
  printf("      COMPUTATION((b.data+j*b.M),i);				\\\n");
  printf("      UNLOOPWRITEAT((c.data+j*c.M),i); \\\n");
  printf("      UNLOOPREADAT((a.data+j*a.M),i+%d);\\\n",unroll);
  printf("    }\\\n");
  printf("  COMPUTATION((b.data+j*b.M),i);     \\\n");
  printf("  UNLOOPWRITEAT((c.data+j*c.M),i); \\\n");
  printf("  i+=%d;}\n",unroll);
  printf("#define UNROLLKERNEL_t(c,a,b,i,j,y,COMPUTATION)	\\\n");
  printf("if (2*%d<x) {\\\n",unroll);
  printf("  UNLOOPREADAT_t((a.data+j*a.M),0,a.beta);			\\\n");
  printf("\\\n");
  printf("  for (i=0;i<x-2*%d;i+=%d) { \\\n",unroll,unroll);
  printf("      COMPUTATION((b.data+j*b.M),i,b.beta);	 \\\n");
  printf("      UNLOOPWRITEAT((c.data+j*c.M),i); \\\n");
  printf("      UNLOOPREADAT_t((a.data+j*a.M),i+%d,a.beta);	\\\n",unroll);
  printf("    }\\\n");
  printf("  COMPUTATION((b.data+j*b.M),i,b.beta);    \\\n");
  printf("  UNLOOPWRITEAT((c.data+j*c.M),i); \\\n");
  printf("  i+=%d;}\n",unroll);
  printf("#endif\n");
  printf(" \n");
  printf("#if (LIBRARY_PACKAGE)						        \n");
  printf("								        \n");
  printf("#if(SINGLE_PRECISION)			        \n");
  printf("#define add 	      s_add 	      				        \n");
  printf("#define sub 	      s_sub 	      				        \n");
  printf("#define add_amd       s_add_amd       				        \n");
  printf("#define sub_amd       s_sub_amd       				        \n");
  printf("#define add_t 	      s_add_t 	      				        \n");
  printf("#define sub_t 	      s_sub_t 	      				        \n");
  printf("#define add_amd_t     s_add_amd_t     				        \n");
  printf("#define sub_amd_t     s_sub_amd_t     				        \n");
  printf("#define copy	      s_copy	      				        \n");
  printf("#define copy_matrix   s_copy_matrix   				        \n");
  printf("#define comp	      s_comp	      				        \n");
  printf("#define print	      s_print	      				        \n");
  printf("#define ptadd	      s_ptadd	      				        \n");
  printf("#define ptadd_t	      s_ptadd_t	      				        \n");
  printf("#define ptsub	      s_ptsub	      				        \n");
  printf("#define ptsub_t	      s_ptsub_t	      				        \n");
  printf("#define ptcopy        s_ptcopy        				        \n");
  printf("#define randomInitialization        s_randomInitialization        				        \n");
  printf("#define randomInitializationError   s_randomInitializationError        				        \n");
  printf("#endif								        \n");
  printf("#if(DOUBLE_PRECISION)			        \n");
  printf("#define add 	      d_add 	      				        \n");
  printf("#define sub 	      d_sub 	      				        \n");
  printf("#define add_amd       d_add_amd       				        \n");
  printf("#define sub_amd       d_sub_amd       				        \n");
  printf("#define add_t 	      d_add_t 	      				        \n");
  printf("#define sub_t 	      d_sub_t 	      				        \n");
  printf("#define add_amd_t     d_add_amd_t     				        \n");
  printf("#define sub_amd_t     d_sub_amd_t     				        \n");
  printf("#define copy	      d_copy	      				        \n");
  printf("#define copy_matrix   d_copy_matrix   				        \n");
  printf("#define comp	      d_comp	      				        \n");
  printf("#define print	      d_print	      				        \n");
  printf("#define ptadd	      d_ptadd	      				        \n");
  printf("#define ptadd_t	      d_ptadd_t	      				        \n");
  printf("#define ptsub	      d_ptsub	      				        \n");
  printf("#define ptsub_t	      d_ptsub_t	      				        \n");
  printf("#define ptcopy        d_ptcopy        				        \n");
  printf("#define randomInitialization        d_randomInitialization        				        \n");
  printf("#define randomInitializationError   d_randomInitializationError        				        \n");
  printf("								        \n");
  printf("#endif								        \n");
  printf("#if(SINGLE_COMPLEX)				        \n");
  printf("#define add 	      c_add 	      				        \n");
  printf("#define sub 	      c_sub 	      				        \n");
  printf("#define add_amd       c_add_amd       				        \n");
  printf("#define sub_amd       c_sub_amd       				        \n");
  printf("#define add_t 	      c_add_t 	      				        \n");
  printf("#define sub_t 	      c_sub_t 	      				        \n");
  printf("#define add_amd_t     c_add_amd_t     				        \n");
  printf("#define sub_amd_t     c_sub_amd_t     				        \n");
  printf("#define copy	      c_copy	      				        \n");
  printf("#define copy_matrix   c_copy_matrix   				        \n");
  printf("#define comp	      c_comp	      				        \n");
  printf("#define print	      c_print	      				        \n");
  printf("#define ptadd	      c_ptadd	      				        \n");
  printf("#define ptadd_t	      c_ptadd_t	      				        \n");
  printf("#define ptsub	      c_ptsub	      				        \n");
  printf("#define ptsub_t	      c_ptsub_t	      				        \n");
  printf("#define ptcopy        c_ptcopy        				        \n");
  printf("#define randomInitialization        c_randomInitialization        		  	        \n");  printf("								        \n");
  printf("#define randomInitializationError   c_randomInitializationError        				        \n");
  printf("#endif								        \n");
  printf("#if(DOUBLE_COMPLEX)				        \n");
  printf("#define add 	      z_add 	      				        \n");
  printf("#define sub 	      z_sub 	      				        \n");
  printf("#define add_amd       z_add_amd       				        \n");
  printf("#define sub_amd       z_sub_amd       				        \n");
  printf("#define add_t 	      z_add_t 	      				        \n");
  printf("#define sub_t 	      z_sub_t 	      				        \n");
  printf("#define add_amd_t     z_add_amd_t     				        \n");
  printf("#define sub_amd_t     z_sub_amd_t     				        \n");
  printf("#define copy	      z_copy	      				        \n");
  printf("#define copy_matrix   z_copy_matrix   				        \n");
  printf("#define comp	      z_comp	      				        \n");
  printf("#define print	      z_print	      				        \n");
  printf("#define ptadd	      z_ptadd	      				        \n");
  printf("#define ptadd_t	      z_ptadd_t	      				        \n");
  printf("#define ptsub	      z_ptsub	      				        \n");
  printf("#define ptsub_t	      z_ptsub_t	      				        \n");
  printf("#define ptcopy        z_ptcopy        				        \n");
  printf("#define randomInitialization        z_randomInitialization        				        \n");
  printf("#define randomInitializationError   z_randomInitializationError        				        \n");
  printf("#endif								        \n");
  printf("								        \n");
  printf("								        \n");
  printf("#ifndef MAT_ADD_MODULE 						        \n");
  printf("int add (DEF(c), DEF(a), DEF(b));				        \n");
  printf("int sub (DEF(c), DEF(a), DEF(b));				        \n");
  printf("int add_amd (DEF(c), DEF(a), DEF(b));				        \n");
  printf("int sub_amd (DEF(c), DEF(a), DEF(b));				        \n");
  printf("int add_t (DEF(c), DEF(a), DEF(b));				        \n");
  printf("int sub_t (DEF(c), DEF(a), DEF(b));				        \n");
  printf("int add_amd_t (DEF(c), DEF(a), DEF(b));			        \n");
  printf("int sub_amd_t (DEF(c), DEF(a), DEF(b));			        \n");
  printf("void copy(DEF(c), DEF(a));					        \n");
  printf("int copy_matrix(DEF(c), DEF(a),DEF(b));			        \n");
  printf("int  comp(DEF(c), DEF(a));					        \n");
  printf("void print(DEF(c));						        \n");
  printf("int ptadd(DEF(c), DEF(a), DEF(b));				        \n");
  printf("int ptadd_t(DEF(c), DEF(a), DEF(b));				        \n");
  printf("int ptsub(DEF(c), DEF(a), DEF(b));				        \n");
  printf("int ptsub_t(DEF(c), DEF(a), DEF(b));				        \n");
  printf("void ptcopy(DEF(c), DEF(a), DEF(b));				        \n");
  printf("void randomInitialization(DEF(a), int seed1, int seed2);				        \n");
  printf("void randomInitializationError(DEF(a), int seed1);				        \n");
  printf("#endif								        \n");
  printf("								        \n");
  printf("								        \n");
  printf("#elif(APPLICATION)						        \n");
  printf("								        \n");
  printf("int s_add (S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("int s_sub (S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("int s_add_amd (S_Matrix c, S_Matrix a, S_Matrix b);			        \n");
  printf("int s_sub_amd (S_Matrix c, S_Matrix a, S_Matrix b);			        \n");
  printf("int s_add_t (S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("int s_sub_t (S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("int s_add_amd_t (S_Matrix c, S_Matrix a, S_Matrix b);			        \n");
  printf("int s_sub_amd_t (S_Matrix c, S_Matrix a, S_Matrix b);			        \n");
  printf("void s_copy(S_Matrix c, S_Matrix a);					        \n");
  printf("int s_copy_matrix(S_Matrix c, S_Matrix a, S_Matrix b);			        \n");
  printf("int  s_comp(S_Matrix c, S_Matrix a);					        \n");
  printf("void s_print(S_Matrix c);						        \n");
  printf("int s_ptadd(S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("int s_ptadd_t(S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("int s_ptsub(S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("int s_ptsub_t(S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("int s_ptcopy(S_Matrix c, S_Matrix a, S_Matrix b);				        \n");
  printf("void s_randomInitialization(S_Matrix a, int seed1, int seed2);				        \n");
  printf("void s_randomInitializationError(S_Matrix a, int seed1);				        \n");
  printf("								        \n");
  printf("int d_add (D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("int d_sub (D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("int d_add_amd (D_Matrix c, D_Matrix a, D_Matrix b);			        \n");
  printf("int d_sub_amd (D_Matrix c, D_Matrix a, D_Matrix b);			        \n");
  printf("int d_add_t (D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("int d_sub_t (D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("int d_add_amd_t (D_Matrix c, D_Matrix a, D_Matrix b);			        \n");
  printf("int d_sub_amd_t (D_Matrix c, D_Matrix a, D_Matrix b);			        \n");
  printf("void d_copy(D_Matrix c, D_Matrix a);					        \n");
  printf("int d_copy_matrix(D_Matrix c, D_Matrix a, D_Matrix b);			        \n");
  printf("int  d_comp(D_Matrix c, D_Matrix a);					        \n");
  printf("void d_print(D_Matrix c);						        \n");
  printf("int d_ptadd(D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("int d_ptadd_t(D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("int d_ptsub(D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("int d_ptsub_t(D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("int d_ptcopy(D_Matrix c, D_Matrix a, D_Matrix b);				        \n");
  printf("void d_randomInitialization(D_Matrix a, int seed1, int seed2);				        \n");
  printf("void d_randomInitializationError(D_Matrix a, int seed1);				        \n");
  printf("								        \n");
  printf("int c_add (C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("int c_sub (C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("int c_add_amd (C_Matrix c, C_Matrix a, C_Matrix b);			        \n");
  printf("int c_sub_amd (C_Matrix c, C_Matrix a, C_Matrix b);			        \n");
  printf("int c_add_t (C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("int c_sub_t (C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("int c_add_amd_t (C_Matrix c, C_Matrix a, C_Matrix b);			        \n");
  printf("int c_sub_amd_t (C_Matrix c, C_Matrix a, C_Matrix b);			        \n");
  printf("void c_copy(C_Matrix c, C_Matrix a);					        \n");
  printf("int c_copy_matrix(C_Matrix c, C_Matrix a, C_Matrix b);			        \n");
  printf("int  c_comp(C_Matrix c, C_Matrix a);					        \n");
  printf("void c_print(C_Matrix c);						        \n");
  printf("int c_ptadd(C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("int c_ptadd_t(C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("int c_ptsub(C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("int c_ptsub_t(C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("int c_ptcopy(C_Matrix c, C_Matrix a, C_Matrix b);				        \n");
  printf("void c_randomInitialization(C_Matrix a, int seed1, int seed2);				        \n");
  printf("void c_randomInitializationError(C_Matrix a, int seed1);				        \n");
  printf("								        \n");
  printf("int z_add (Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("int z_sub (Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("int z_add_amd (Z_Matrix c, Z_Matrix a, Z_Matrix b);			        \n");
  printf("int z_sub_amd (Z_Matrix c, Z_Matrix a, Z_Matrix b);			        \n");
  printf("int z_add_t (Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("int z_sub_t (Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("int z_add_amd_t (Z_Matrix c, Z_Matrix a, Z_Matrix b);			        \n");
  printf("int z_sub_amd_t (Z_Matrix c, Z_Matrix a, Z_Matrix b);			        \n");
  printf("void z_copy(Z_Matrix c, Z_Matrix a);					        \n");
  printf("int z_copy_matrix(Z_Matrix c, Z_Matrix a, Z_Matrix b);			        \n");
  printf("int z_comp(Z_Matrix c, Z_Matrix a);					        \n");
  printf("void z_print(Z_Matrix c);						        \n");
  printf("int z_ptadd(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("int z_ptadd_t(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("int z_ptsub(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("int z_ptsub_t(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("int z_ptcopy(Z_Matrix c, Z_Matrix a, Z_Matrix b);				        \n");
  printf("void z_randomInitialization(Z_Matrix a, int seed1, int seed2);				        \n");
  printf("void z_randomInitializationError(Z_Matrix a, int seed1);				        \n");
  printf("#endif  // if LIBRARY else APPLICATION                                                                \n");

  printf("#define DEFREGISTERS Mat ");
  for(i=0;i<unroll-1;i++) {
    printf("a%d,",i);
  }
  printf("a%d;\n",i);


  printf("#endif // MODULE \n");



  return 0;
}
