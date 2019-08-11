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

#define MODULE_PTMATRIXCOMPUTATION 1
#include <pt.h>

static int debug=0;

/*
int sched_setaffinity(pid_t pid, size_t cpusetsize,
		      cpu_set_t *mask);

int sched_getaffinity(pid_t pid, size_t cpusetsize,
		      cpu_set_t *mask);

void CPU_CLR(int cpu, cpu_set_t *set);
int CPU_ISSET(int cpu, cpu_set_t *set);
void CPU_SET(int cpu, cpu_set_t *set);
void CPU_ZERO(cpu_set_t *set);
*/




static void *basicComputation( void *s) {
  TAddOperands mc = *(TAddOperands *)s;
  int p1;
  cpu_set_t mask;
#if CLBLAS
  if (debug){
      
    printf("Basic pi%d  C %d x %d gpu %d\n",mc.pi,mc.c.m, mc.c.n, mc.c.gpu);
    printf("      A %d x %d gpu %d\n",mc.a.m, mc.a.n, mc.a.gpu);
    printf("      B %d x %d gpu %d\n",mc.b.m, mc.b.n, mc.b.gpu);
  }
#else
  if (debug){
    printf("Basic pi %d  C %d x %d\n",mc.pi,mc.c.m, mc.c.n);
    printf("      A %d x %d\n",mc.a.m, mc.a.n);
    printf("      B %d x %d\n",mc.b.m, mc.b.n);
  }
#endif

  if (mc.pi > 0)  {

    CPU_ZERO(&mask);
    CPU_SET(mc.pi, &mask);

    //p1 = sched_setaffinity(0,sizeof(mc.pi),&(mc.pi));
    p1 = sched_setaffinity(0,sizeof(mask),&(mask));
    if (p1<0) { 
      printf(" Fail processor setting pt %d \n",mc.pi);
    }
  }
  mc.m(mc.c,mc.a,mc.b);
  return 0;
}

void pThreadedMatrixComputation(MatrixComputation m, 
				DivideOperands d,
				DEF(c), 
				DEF(a), 
				DEF(b)) {
  
  cpu_set_t current_mask; 
  pthread_t*  p_thread; /* thread's structure */
  pthread_attr_t attr;
  int* thr_id;
  int i;
  int k;

  TAddOperands *args = d(USE(c),USE(a),USE(b),m,&k);

  sched_getaffinity(0,sizeof(current_mask),&(current_mask));
  
  thr_id = malloc(k * sizeof(int) );
  p_thread = malloc(k * sizeof(pthread_t) );
  pthread_attr_init(&attr);
  

  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
  
  for (i = 0; i<k-1; i++){
    //printf("k %d \n",k);
    thr_id[i] = pthread_create(&p_thread[i], 
			       &attr, 
			       basicComputation, 
			       (void *)(args+i));
  }
 
  
  // MM multiplication
  basicComputation((void *)(args+i));


  
 //START_CLOCK;
 /* wait for the threads to complete */
 for (i = 0; i<k-1; i++){
   pthread_join(p_thread[i], NULL);
 }
 

 sched_setaffinity(0,sizeof(current_mask),&(current_mask));

 free(thr_id);
 free(p_thread);
 free(args);
 //printf(" Done pthreading \n");
}

void MatrixComputations(TAddOperands *args, int len)  {
  
  pthread_t*  p_thread; /* thread's structure */
  pthread_attr_t attr;
  int* thr_id;
  int i;
  int k=len;
  
  thr_id = malloc(k * sizeof(int) );
  p_thread = malloc(k * sizeof(pthread_t) );
  pthread_attr_init(&attr);


  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
  
  for (i = 0; i<k-1; i++){
    //printf("k %d \n",k);
    thr_id[i] = pthread_create(&p_thread[i], 
			       &attr, 
			       basicComputation, 
			       (void *)(args+i));
  }

  basicComputation((void *)(args+i));
  
 //START_CLOCK;
 /* wait for the threads to complete */
 for (i = 0; i<k-1; i++){
   pthread_join(p_thread[i], NULL);
 }
 if (debug) printf(" Done pthreading \n");

 free(thr_id);
 free(p_thread);


}

void MatrixComputationsSequential(TAddOperands *args, int len)  {
  
  int i;
  if (debug)   printf("MatrixComputationsSequential < %d \n", len);
  for (i = 0; i<len; i++){
    basicComputation((void *)(args+i));
  }

}


