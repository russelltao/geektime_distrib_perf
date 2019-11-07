#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>


using namespace std;

#define TESTN 16*1024L

bool setaffinity = false;

void* loopcalc(void* args) {
	if (setaffinity) {
		cpu_set_t mask;  //CPU核的集合
		cpu_set_t get;	 //获取在集合中的CPU
		int *thread_num = (int *)args; 

		CPU_ZERO(&mask);    //置空
	    CPU_SET(*thread_num,&mask);   //设置亲和力值
		if (sched_setaffinity(0, sizeof(mask), &mask) == -1)//设置线程CPU亲和力
		{
			cout<<"warning: could not set CPU affinity, continuing...\n";
		}
	}
	timeval tStart,tEnd;
	gettimeofday(&tStart, 0);

	unsigned char* arr = new unsigned char[TESTN];
	for (long i = 0; i < TESTN; i++) arr[i] = rand() % 256;
	for (int j = 1; j < 16*1024; j++) {
		for (long i = 0; i < TESTN; i++) arr[i] += 1;
	}

	gettimeofday(&tEnd, 0);
	
	*(long*)args = (1000000LL * (tEnd.tv_sec-tStart.tv_sec) + (tEnd.tv_usec-tStart.tv_usec))/1000;
}

int main(int argc, char** argv) {
	int threadnum = 2;
	int ch;
	while((ch = getopt(argc, argv, "t:fs")) != -1) {
		switch(ch)
		{
		   case 't':
			  threadnum = atoi(optarg);
			  break;
		   case 'f':
		      setaffinity = true;
			  break;
		   case 's':
		   	  setaffinity = false;
			  break;
		}
	}

	pthread_t* id = new pthread_t[threadnum];
	long* timecost = new long[threadnum];
	for(int i = 0; i < threadnum; i++) {
		timecost[i] = i;
		int ret=pthread_create(&id[i],NULL,loopcalc,&timecost[i]); 
		
		if(ret!=0){ 
			cout<<"Create pthread error!\n"; 
			exit (1); 
		} 
	}

	long costsum = 0;
	for(int i = 0; i < threadnum; i++) {
		pthread_join(id[i],NULL);
		costsum += timecost[i];
	}
	cout<<"costsum: "<<costsum<<", avg: "<<costsum/threadnum<<endl;
}

