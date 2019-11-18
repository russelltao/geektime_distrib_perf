#include "stdio.h"
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int TESTN = 128*1024*1024;
int size = 64;

void* loopalloc(void* args) {
	timeval tStart,tEnd;
	void* addr;
	//这里不再使用clock，因为clock表示的进程所占用过的CPU周期，它将所有CPU都计入了，不适合示例中的统计
	gettimeofday(&tStart, 0);

	for (int i = 0; i < TESTN; i++) {
		addr = malloc(size);
		free(addr);
	}

	gettimeofday(&tEnd, 0);

	//将消耗时间传出到timecost数组中对应的元素上
	*(long*)args = (1000000LL * (tEnd.tv_sec-tStart.tv_sec) + (tEnd.tv_usec-tStart.tv_usec));
}

int main(int argc, char** argv) {
	int threadnum = 1;
	int ch;
	while((ch = getopt(argc, argv, "t:s:n:")) != -1) {
		switch(ch)
		{
			//设置测试的并发线程数，注意不要超过机器上的CPU核数
			case 't':
				threadnum = atoi(optarg);
				break;
			//指定分配内存块的大小 
			case 's':
				size = atoi(optarg);
				break;
			//循环次数
			case 'n':
				TESTN = atoi(optarg);
				break;
		}
	}

	//统计每个线程计算所需要的时间
	long* timecost = new long[threadnum];
	long costsum = 0;

	if (1 == threadnum) {
		loopalloc(&costsum);
	} else {
		pthread_t* id = new pthread_t[threadnum];

		for(int i = 0; i < threadnum; i++) {
			int ret=pthread_create(&id[i],NULL,loopalloc,&timecost[i]);
			
			if(ret!=0){ 
				cout<<"Create pthread error!\n"; 
				exit (1); 
			} 
		}
		//等待所有线程结束 
		for(int i = 0; i < threadnum; i++) {
			pthread_join(id[i],NULL);
			costsum += timecost[i];
		}
	}
	//比较平均每线程所用时间
	printf("%d线程 %d字节： %.2f纳秒\n", threadnum,size,(double)costsum/threadnum/TESTN*1000);
}


