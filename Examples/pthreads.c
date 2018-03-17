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
#include <pthread.h>

int N=10000;
int M=10000;

#define ALPHA 2

double *POLD;
double *PNEW;
double *P;

int PART_BOUND;


#define GETTIME
#ifdef GETTIME
#include <sys/time.h>
struct timeval _t1,_t2;
double duration;

#define START_CLOCK   gettimeofday(&_t1,NULL ); 
#define END_CLOCK   gettimeofday(&_t2,NULL);   duration = (_t2.tv_sec-_t1.tv_sec)+ (double)(_t2.tv_usec-_t1.tv_usec)/1000000;    printf("----------> get time %e sec<------\n",duration); 
#endif /*  GETTIME */


#ifdef CLOCK
#include <time.h>
clock_t _t1,_t2;
double duration;

#define START_CLOCK   _t1 = clock(); 
#define END_CLOCK     _t2 = clock(); duration =  ((double)(_t2-_t1))/CLOCKS_PER_SEC; \
  printf("clock time %e s \n", duration); 
#endif





void *subroutine(void *thread_id)
{
 int I, J;
 printf("soubroutin 1:\n");

 for (J=0; J<PART_BOUND; J++) {
   for (I=0; I<M; I++) {
     
     P[J*M+I] = PNEW[J*M+I] + POLD[J*M+I];
   }
 }

 return 0;
}

void *subroutine1(void *thread_id)
{
 int I, J;
 printf("soubroutin 2:\n");
 for (J=PART_BOUND; J<N; J++) {
   for (I=0; I<M; I++) {
     P[J*M+I] = PNEW[J*M+I] + POLD[J*M+I];
    
   }
 }

 return 0;
}

#define NUM_THREADS 2



int main(int argc , char **argv)
{
 int i, j;
 int* thr_id;  /* Stores thread IDs for the newly created threads */
 pthread_t*  p_thread; /* thread's structure */
 pthread_attr_t attr;
 
 N = atoi(argv[1]);
 M = atoi(argv[2]);
 PART_BOUND = N/2;

 printf("N = %d, M = %d, PART_BOUND = %d \n", N,M,PART_BOUND);

 P = calloc(M*N, sizeof(double));
 POLD = calloc(M*N, sizeof(double));
 PNEW = calloc(M*N, sizeof(double));

 thr_id = malloc(NUM_THREADS * sizeof(int) );
 p_thread = malloc(NUM_THREADS * sizeof(pthread_t) );
 pthread_attr_init(&attr);

 START_CLOCK;
 for (j=0; j<N; j++) {
   for (i=0; i<M; i++) {
     P[j*M+i] =  POLD[j*M+i] =  PNEW[j*M+i]=1.0;
   }
 }
 END_CLOCK;

 START_CLOCK;
 for (j=0; j<N; j++) {
   for (i=0; i<M; i++) {
     P[j*M+i] =  POLD[j*M+i] +  PNEW[j*M+i] ;
   }
 }
 END_CLOCK;


 pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
 START_CLOCK;

 thr_id[0] = pthread_create(&p_thread[0], &attr, subroutine, (void *)0);
 thr_id[1] = pthread_create(&p_thread[1], &attr, subroutine1, (void *)1);
 // END_CLOCK;

 //START_CLOCK;
 /* wait for the threads to complete */
 for (i = 0; i<NUM_THREADS; i++){
   pthread_join(p_thread[i], NULL);
 }


 END_CLOCK;
 return 0;
}
