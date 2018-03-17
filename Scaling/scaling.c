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


#include <stdio.h>
#include <stdlib.h>
#include <architecture.h>



#ifdef ATHLON 
#include <stdlib.h>
FILE *frequencyScaling;
FILE *MaxFile, *MinFile;
int MaxFrequency, MinFrequency;
int result;
int fastCPU() {
  int l;
  //rewind(frequencyScaling);
  //  printf("fast\n");
  //  l = fprintf(frequencyScaling,"2000000\n");
  // rewind(frequencyScaling);
  l = fprintf(MaxFile,"%d\n",MaxFrequency);
  rewind(MaxFile);
  return l;
  //fprintf(frequencyScaling,"%d",MaxFrequency);
  //system("echo 2000000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed");
}

int slowCPU() { 

  int l;
  //system("echo 1800000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed");
  //rewind(frequencyScaling);
  //  l=fprintf(frequencyScaling,"%d\n",MinFrequency);
  // rewind(frequencyScaling);
  l=fprintf(MaxFile,"%d\n",MinFrequency);
  rewind(MaxFile);


  //  printf("slow\n");
  return l;
}

inline int freqScaling(int i) {
  int l;

  l=fprintf(frequencyScaling,"%d",i);
  rewind(frequencyScaling);
  return l;
  
}

void openCpuScalingDriver() { 
  system("/usr/sbin/cpufreq-selector -g userspace\n");
  frequencyScaling=fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed","w+");
  MaxFile=fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq","r");
  MinFile=fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq","r");
  
  fscanf(MaxFile,"%d",&MaxFrequency);
  fscanf(MinFile,"%d",&MinFrequency);
}



void closeCpuScalingDriver(){
  fclose(frequencyScaling);
  fclose(MaxFile);
  fclose(MinFile);
  system("/usr/sbin/cpufreq-selector -g ondemand\n");
}
#endif

#ifdef XSCALE

FILE *frequencyScaling;
int result;


int fastCPU() { 
  int l=fprintf(frequencyScaling,"%d",10);
  rewind(frequencyScaling);
  return l;
  //system("echo 10 > /proc/cpu_freq_current");
}

int slowCPU() { 
  //system("echo 11 > /proc/cpu_freq_current");
  int l=fprintf(frequencyScaling,"%d",11);rewind(frequencyScaling);
  return l;
}

inline int freqScaling(int i) { 
  int l=fprintf(frequencyScaling,"%d",i);rewind(frequencyScaling);
  return l;
  //  char temp[30];  
  //sprintf(temp,"echo %d >  /proc/cpu_freq_current", i);
  //system(temp);

}

void openCpuScalingDriver() { 
  frequencyScaling=fopen("/proc/cpu_freq_current","r+");
   MaxFile=fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq","r");
  MinFile=fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq","r");
  
  fscanf(MaxFile,"%d",&MaxFrequency);
  fscanf(MinFile,"%d",&MinFrequency);
}



void closeCpuScalingDriver(){
  fclose(frequencyScaling);
  fclose(MaxFile);
  fclose(MinFile);
}

#endif
