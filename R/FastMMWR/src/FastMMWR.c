#include <R.h>
//#include <cdl.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#define GETTIME

#define FASTMMWRINTERFACE_MODULE
#define APPLICATION 1

#include <FastMMWR.h>
#include <pthread.h>
#define _GNU_SOURCE
#include <sched.h>

//# define CPU_ZERO(cpusetp) __CPU_ZERO_S (sizeof (cpu_set_t), cpusetp)
//# define CPU_SET(cpu, cpusetp) __CPU_SET_S (cpu, sizeof (cpu_set_t), cpusetp)


void
R_init_mylib(DllInfo *info)
{
  Rprintf(" FastMMW \n");
  R_FlushConsole();

}
void
R_unload_mylib(DllInfo *info)
{
  /* Release resources. */
}

// to make the parameters copy free, we encode the transposition and conjucation caracter.
static char flags[3]="ntc";
static int timing=1;

#define TEXECUTE(X) \
  { if (timing) {START_CLOCK;}			\
    X;						\
    if (timing) {END_CLOCK;}			\
  }


#include "FastMMWRcode.h"
