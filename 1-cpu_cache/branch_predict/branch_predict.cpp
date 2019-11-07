#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

#define TESTN 128*1024*1024L

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
	//使用clock统计与取系统时间不同，它表示从进程启动到当下所消耗的CPU计时单元数
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(int argc, char** argv) {
	int mode = 1;
	int ch;
	while((ch = getopt(argc, argv, "fsg")) != -1) {
		switch(ch)
		{
			//遍历随机数组
		   case 's':
			  mode = 1;
			  break;
		   //遍历有序数组
		   case 'f':
			  mode = 2;
			  break;
		   //生成数组至文件中，不影响遍历过程时的perf统计
		   case 'g':
			  mode = 3;
			  break;
		}
	}

	unsigned char* arr = new unsigned char[TESTN];

	if (3 == mode) {
		//构造随机数组
		for (long i = 0; i < TESTN; i++) arr[i] = rand() % 256;
		ofstream ofs;
		//随机数组写入文件
		ofs.open("rand.array", ios::out | ios::binary);
		ofs.write((const char*)arr, TESTN);
		ofs.close();
		//数组排序
		sort(arr,arr+TESTN);
		//有序数组写入文件
		ofs.open("sort.array", ios::out | ios::binary);
		ofs.write((const char*)arr, TESTN);
		ofs.close();
	} else {
		const char* fname;
		if ( 1 == mode) {
			fname = "rand.array";
		}else if (2 == mode) {
			fname = "sort.array";
		}
		ifstream ifs;
		ifs.open(fname);
		ifs.read((char *)arr, TESTN);

		//使用clock比取系统时间能够更准确的看到消耗了多少CPU资源
		clock_t start,end;
		start =clock();
		for(long i = 0; i < TESTN; i++) {
			//条件分支预测在这里发生作用
			if (arr[i] < 128) arr[i] = 0;
		}
		end =clock();
	    cout<<" "<<timediff(start,end)<<endl;
	}
}
