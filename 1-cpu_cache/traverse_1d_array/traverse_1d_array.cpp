#include <time.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
	//使用clock统计与取系统时间不同，它表示从进程启动到当下所消耗的CPU计时单元数
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(int argc, char** argv) {
	int step = 1,ch;
	bool slowMode = true;
	long TESTN = 1024*1024*1024*8L;
	while((ch = getopt(argc, argv, "s:")) != -1) {
		switch(ch)
		{
		   case 's':
			  step = atoi(optarg);
			  break;
		}
	}

	char* arr = new char[TESTN];
	clock_t start, end;
	long total = TESTN/1024,cnt = 0;
	long i = 0;
	start =clock();
	while (++cnt < total) {
	    arr[i] = 0;
		i += step;
	}
	end =clock();
    cout<<timediff(start,end)<<",access count:"<<cnt<<endl;
}

