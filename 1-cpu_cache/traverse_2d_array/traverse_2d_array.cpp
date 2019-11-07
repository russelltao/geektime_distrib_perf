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

#define TESTN 2048


int main(int argc, char** argv) {
	int ch;
	bool slowMode = true;
	
	while((ch = getopt(argc, argv, "fs")) != -1) {
		switch(ch)
		{
		   //-s: 使用arr[j][i]遍历数组
		   case 's':
			  slowMode = true;
			  break;
		   //-f: 使用arr[i][j]遍历数组
		   case 'f':
			  slowMode = false;
			  break;
		}
	}
	cout<<(slowMode?"arr[j][i]":"arr[i][j]")<<endl;

	//在栈上分配二维数组天然是内存连续的，需要注意TESTN的大小，不要超过栈的最大字节
	char arr[TESTN][TESTN];
	//使用clock比取系统时间能够更准确的看到消耗了多少CPU资源
	clock_t start, end;

	if (!slowMode) {
		start =clock();
		for(int i = 0; i < TESTN; i++) {
		    for(int j = 0; j < TESTN; j++) {
				//arr[i][j]是连续访问的
		        arr[i][j] = 0;
		    }
		}
		end =clock();
	    cout<<timediff(start,end)<<endl;
	}else {
		start =clock();
		for(int i = 0; i < TESTN; i++) {
		    for(int j = 0; j < TESTN; j++) {
				//arr[j][i]不是连续访问的
		        arr[j][i] = 0;
		    }
		}
		end =clock();
		cout<<timediff(start,end)<<endl;
	}
}
