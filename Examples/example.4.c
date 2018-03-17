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
/************************************************************
 *
 * This the example for parallel implementation. With the right macro
 * defined, I can test any MM algorithm.
 * 
 * Mother -> one_level  -> cpu_computation
 *       |             \-> cpu_computation
 *       |
 *        -> one_level  -> cpu_computation
 *                     \-> cpu_computation
 *
 */



#define GETTIME
#include <architecture.h>
#include <mat-operands.h>
#include <mat-mulkernels.h>
#include <mat-addkernels.h>
#include <stdlib.h>

#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <pthread.h>


#define _GNU_SOURCE
#include <sched.h>

long
sched_setaffinity(pid_t pid, unsigned int len, 
                  unsigned long *user_mask_ptr);
long
sched_getaffinity(pid_t pid, unsigned int len,
                  unsigned long *user_mask_ptr);



#define _P(x) (1<<(x))



#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>


#define SIZE_M 10000
#define SIZE_N 10000
#define SIZE_P 10000

#define TIMES 0

#define ASSERT(x,t) if (!(x)) { printf("Malloc Failed %d\n",t); return 0; }


struct  first_level{ 
  int processor;
  unsigned long mask;
  int shift;
  Matrix C0,C1;
  Matrix A0,A1;
  Matrix B;
}; 

static volatile int barrier = 0; 

sem_t *beef;
sem_t *alloc;

struct leaf_computation { 
  int processor;
  unsigned long mask;
  int shift;
  int times;

  Matrix C;
  Matrix A0,A1;
  Matrix B0,B2;
}; 




//#define ATLAS_TEST 1
// #define SMUL_TEST 1
// #define WMUL_TEST 1
//#define OMUL_TEST 1
#define OWMUL_TEST 1
#define INNER_TIMING 1



#ifdef ATLAS_TEST   
  char *program = "ATLAS";
#endif  
#ifdef SMUL_TEST
  char *program = "STRASSEN";
#endif
#ifdef WMUL_TEST 
  char *program = "WINOGRAD";
#endif
#ifdef OMUL_TEST
  char *program = "Oblivious STRASSEN";
#endif
#ifdef OWMUL_TEST
  char *program = "Oblivious WINO";
#endif


int COMPUTATION_0(struct leaf_computation *t) {
  int i;

  // WARM UP 
#ifdef ATLAS_TEST   
  CMC((t->C), =, (t->A0),  mm_leaf_computation, (t->B0));  
  CMC((t->C), =, (t->A1),  mm_leaf_computation_madd, (t->B2));  
#endif  
#ifdef SMUL_TEST
  CMC((t->C), =, (t->A0),  smul, (t->B0));
  CMC((t->C), =, (t->A1),  saddmul, (t->B2));
#endif
#ifdef WMUL_TEST
  CMC((t->C), =, (t->A0),  wmul, (t->B0));
  CMC((t->C), =, (t->A1),  waddmul, (t->B2));
#endif
#ifdef OMUL_TEST
  CMC((t->C), =, (t->A0),  omul, (t->B0));
  CMC((t->C), =, (t->A1),  oaddmul, (t->B2));
#endif
#ifdef OWMUL_TEST
  CMC((t->C), =, (t->A0),  owmul, (t->B0));
  CMC((t->C), =, (t->A1),  owaddmul, (t->B2));
#endif


  return 1;
}



int COMPUTATION_1(struct leaf_computation *t) {
  int i;
  
#ifdef ATLAS_TEST   
  CMC((t->C), =, (t->A1),  mm_leaf_computation, (t->B2));  
  CMC((t->C), =, (t->A0),  mm_leaf_computation_madd, (t->B0));  
#endif  
#ifdef SMUL_TEST
  CMC((t->C), =, (t->A1),  smul, (t->B2));
  CMC((t->C), =, (t->A0),  saddmul, (t->B0));
#endif
#ifdef WMUL_TEST
  CMC((t->C), =, (t->A1),  wmul, (t->B2));
  CMC((t->C), =, (t->A0),  waddmul, (t->B0));
#endif
#ifdef OMUL_TEST
  CMC((t->C), =, (t->A1),  omul, (t->B2));
  CMC((t->C), =, (t->A0),  oaddmul, (t->B0));
#endif
#ifdef OWMUL_TEST
  CMC((t->C), =, (t->A1),  owmul, (t->B2));
  CMC((t->C), =, (t->A0),  owaddmul, (t->B0));
#endif

 
  return 1;
}


#define PROC(t) (((int)(((t->mask)>>(t->shift))&(t->processor)))+t->shift - 1 )

int cpu_computation(void *temp) { 
  struct leaf_computation *t = (struct leaf_computation *) temp;
  int proc = PROC(t);
  int i;
#ifdef INNER_TIMING
  struct timeval  _t1,_t2;
  double duration,ops;
#endif
  //  sem_init(beef,1,4);
  //  beef=sem_open("BEEF",0,0,4);
  //  sem_t *beef;

  printf("Computation CPU %d M%x S %d P %d\n",proc,(int)t->mask,t->shift,t->processor);

  sem_wait(beef);
  //printf("Semaphore passed\n");

#ifdef INNER_TIMING
   gettimeofday(&_t1,NULL);
#endif


  if (proc&1) 
    COMPUTATION_0(t);
  else 
    COMPUTATION_1(t);

#ifdef INNER_TIMING
  gettimeofday(&_t2,NULL);
  //  printf("Done CPU %d \n",proc); 

  duration = ((_t2.tv_sec-_t1.tv_sec)+ (double)(_t2.tv_usec-_t1.tv_usec)/1000000)/(TIMES+1);     
  printf("Proc(%d) Time %e ",proc,duration); 
  ops = ((double)2*(t->A0.m))*t->B0.n*(t->A0.n + t->A1.n);
  printf("MFLOPS %e \n",(ops/duration)/(double)1000000); 
#endif

  sem_post(beef);
  return 0;

}






int one_level(void *temp ) {
  struct first_level *t = (struct first_level *) temp; 
  int *st0, *st1;
  struct leaf_computation cpu0,cpu1;
  int pid0,pid1;
  int status;

  printf(" P \n"); 

  beef = sem_open("BEEF",O_CREAT,S_IRWXU/*|S_IRWXG|S_IRWXO*/,4);
  if (beef == SEM_FAILED) { 
    exit(0);

  }

  alloc = sem_open("allocation",O_CREAT,S_IRWXU/*|S_IRWXG|S_IRWXO*/,4);
  if (beef == SEM_FAILED) { 
    exit(0);

  }

  sem_wait(alloc);

  
  // stack space for the children
  st0 = malloc(1024*1024*sizeof(int));
  st1 = malloc(1024*1024*sizeof(int));
  
  //sleep(1);  
  // Data Layout Preparation
  t->A0.data    = (Mat *) calloc(t->A0.M*t->A0.N,sizeof(Mat));
  ASSERT(t->A0.data,0);
  t->A1.data    = (Mat *) calloc(t->A1.M*t->A1.N,sizeof(Mat));
  ASSERT(t->A1.data,1);
  t->C0.data    = (Mat *) calloc(t->C0.M*t->C0.N,  sizeof(Mat));
  ASSERT(t->C0.data,2);  
  t->C1.data    = (Mat *) calloc(t->C1.M*t->C1.N,  sizeof(Mat));
  ASSERT(t->C1.data,3);  
  // we duplICATE B
  t->B.data     = (Mat *) calloc(t->B.M*t->B.N,sizeof(Mat));
  ASSERT(t->B.data,4);
  
  //  data initialization 
  
  
  // Spawn computation processes 

  cpu0.processor = 1;
  cpu0.mask = t->mask;
  cpu0.shift = t->shift;
  cpu0.times = TIMES ;
  cpu0.C = t->C0;
  cpu0.A0 = t->A0;
  cpu0.A1 = t->A1;
  cpu0.B0 = Q0(t->B);
  cpu0.B2 = Q2(t->B);
  
  
  cpu1.processor = 2;
  cpu1.mask = t->mask;
  cpu1.shift = t->shift;
  cpu1.times = TIMES ;
  cpu1.C =  t->C1;
  cpu1.A0 = t->A0;
  cpu1.A1 = t->A1;
  cpu1.B0 = Q1(t->B);
  cpu1.B2 = Q3(t->B);
  


  
  pid0 = clone(cpu_computation,st0,CLONE_FS|CLONE_VM|CLONE_SIGHAND|CLONE_PTRACE|CLONE_SYSVSEM , (void*)&cpu0 );
  pid1 = clone(cpu_computation,st1,CLONE_FS|CLONE_VM|CLONE_SIGHAND|CLONE_PTRACE|CLONE_SYSVSEM  , (void*)&cpu1 );

  
  waitpid(pid1,&status,0);
  printf(" Leaves PIDS %d %d \n",pid0,pid1);
  
  
  
  return 0;
}




int mother() { 

  int *st0, *st1;
  struct first_level t0,t1;
  int status;
  int pid0,pid1;
  int p0,p1;
  unsigned long mask=0x000E;
  Matrix c,a,b;
  struct timeval  _t1,_t2;
  double duration,ops;
  int times;



  int m, n,p;


  printf(" <m,n,p> ?\n");
  scanf("%d %d %d", &m,&n,&p);

  a.m=a.M = m; a.n=a.N = n;
  b.m=b.M = n; b.n=b.N = p;
  c.m=c.M = m; c.n=c.N = p;

  a.beta = b.beta = c.beta = 1;
  a.trans = b.trans = c.trans = 'n';

  //static DECLARE_SEMAPHORE_GENERIC(beef);
  beef = sem_open("BEEF",O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO,4);
  if (beef == SEM_FAILED) 
    exit(0);

  alloc = sem_open("allocation",O_CREAT,S_IRWXU/*|S_IRWXG|S_IRWXO*/,1);
  if (alloc == SEM_FAILED) { 
    exit(0);

  }

  // cpu computation 
  sem_init(beef,1,4);
  // processor computation
  sem_init(alloc,1,1);


  printf(" You selected the following problem \n");
  printf("A %d x %d; ",m,n);  printf("\n");
  printf("B %d x %d; ",n,p);  printf("\n");

 
  // first level division 
  t0.processor =1;
  t0.mask = 0x0000000c;
  t0.shift = 2;
  t0.C0 = Q0(c); t0.C0.M = t0.C0.m;t0.C0.N = t0.C0.n;  
  t0.C1 = Q1(c); t0.C1.M = t0.C1.m;t0.C1.N = t0.C1.n;  
  t0.A0 = Q0(a); t0.A0.M = t0.A0.m;t0.A0.N = t0.A0.n;  
  t0.A1 = Q1(a); t0.A1.M = t0.A1.m;t0.A1.N = t0.A1.n;  
  t0.B  = b;
   
  // first level division 
  t1.processor =2;
  t1.mask = 0x00000003;
  t1.shift = 0;
  t1.C0 = Q2(c); t1.C0.M = t1.C0.m;t1.C0.N = t1.C0.n;
  t1.C1 = Q3(c); t1.C1.M = t1.C1.m;t1.C1.N = t1.C1.n;
  t1.A0 = Q2(a); t1.A0.M = t1.A0.m;t1.A0.N = t1.A0.n;
  t1.A1 = Q3(a); t1.A1.M = t1.A1.m;t1.A1.N = t1.A1.n;
  t1.B  = b;


  printf("mother  \n"); 

  // stacks for the processors tasks 
  st0 = malloc(1024*1024*sizeof(int));
  st1 = malloc(1024*1024*sizeof(int));

  p0 = sched_getaffinity(0,sizeof(mask),&mask);
  if (p0<0) { 
    return 0;
  }
  printf(" M PIDS %d P(%x) \n",0, (int) mask);


  gettimeofday(&_t1,NULL);


  pid0 = clone(one_level,st0,CLONE_FS|CLONE_SYSVSEM, (void*)&t0 );

  mask = 0x000C;
  p1 = sched_setaffinity(pid0,sizeof(mask),&mask);
  if (p1<0) { 
    printf(" Fail processor setting 1 \n");
  }
  sem_post(alloc);

  pid1 = clone(one_level,st1,CLONE_FS|CLONE_SYSVSEM, (void*)&t1);

  mask = 0x0003;
  p1 = sched_setaffinity(pid1,sizeof(mask),&mask);
  if (p1<0) { 
    printf(" Fail processor setting 2 \n");
  }
  sem_post(alloc);


  mask = 0x0000000E;
  p0 = sched_getaffinity(pid0,sizeof(mask),&mask);
  if (p0<0) { 
    return 0;
  }
  printf(" child 0 PIDS %d P(%x) \n",pid0, (int) mask);


  p0 = sched_getaffinity(pid1,sizeof(mask),&mask);
  if (p0<0) { 
    return 0;
  }
  printf(" child 1 PIDS %d P(%x) \n",pid1, (int) mask);







  sleep(1);
  sem_wait(beef);
  sem_wait(beef);
  sem_wait(beef);
  sem_wait(beef);


  gettimeofday(&_t2,NULL);
  //  printf("Done CPU %d \n",proc); 

  duration = ((_t2.tv_sec-_t1.tv_sec)+ (double)(_t2.tv_usec-_t1.tv_usec)/1000000)/(TIMES+1);     

  



  printf("Overall %s %d %d %d ",program, m,n,p);
  printf(" Time %e ",duration); 
  ops = ((double)2*m)*n*p;
  printf("MFLOPS %e \n",(ops/duration)/(double)1000000); 



  sem_close(beef);
  sem_close(alloc);
  return 0;
}














int main() { 

  return mother();

}
