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
		//获取线程的序列号
		int *thread_num = (int *)args; 

		//将当前线程绑定至特定CPU
		CPU_ZERO(&mask);  
	    CPU_SET(*thread_num,&mask); 
		if (sched_setaffinity(0, sizeof(mask), &mask) == -1)
		{
			cout<<"warning: could not set CPU affinity, continuing...\n";
		}
	}
	timeval tStart,tEnd;
	//这里不再使用clock，因为clock表示的进程所占用过的CPU周期，它将所有CPU都计入了，不适合示例中的统计
	gettimeofday(&tStart, 0);

	//这个循环中由于反复访问有限的数组，CPU缓存命中率非常高
	unsigned char* arr = new unsigned char[TESTN];
	for (long i = 0; i < TESTN; i++) arr[i] = rand() % 256;
	for (int j = 1; j < TESTN; j++) {
		for (long i = 0; i < TESTN; i++) arr[i] += 1;
	}

	gettimeofday(&tEnd, 0);

	//将消耗时间传出到timecost数组中对应的元素上
	*(long*)args = (1000000LL * (tEnd.tv_sec-tStart.tv_sec) + (tEnd.tv_usec-tStart.tv_usec))/1000;
}

int main(int argc, char** argv) {
	int threadnum = 2;
	int ch;
	while((ch = getopt(argc, argv, "t:fs")) != -1) {
		switch(ch)
		{
			//设置测试的并发线程数，注意不要超过机器上的CPU核数
		   case 't':
			  threadnum = atoi(optarg);
			  break;
		   //将线程绑定至特定CPU上
		   case 'f':
		      setaffinity = true;
			  break;
		   //不绑定CPU
		   case 's':
		   	  setaffinity = false;
			  break;
		}
	}

	pthread_t* id = new pthread_t[threadnum];
	//统计每个线程计算所需要的时间
	long* timecost = new long[threadnum];
	for(int i = 0; i < threadnum; i++) {
		//最初timecost用于传递线程号，用于绑定CPU
		timecost[i] = i;
		int ret=pthread_create(&id[i],NULL,loopcalc,&timecost[i]); 
		
		if(ret!=0){ 
			cout<<"Create pthread error!\n"; 
			exit (1); 
		} 
	}

	long costsum = 0;
	//等待所有线程结束 
	for(int i = 0; i < threadnum; i++) {
		pthread_join(id[i],NULL);
		costsum += timecost[i];
	}
	//比较平均每线程所用时间
	cout<<"costsum: "<<costsum<<", avg: "<<costsum/threadnum<<endl;
}

