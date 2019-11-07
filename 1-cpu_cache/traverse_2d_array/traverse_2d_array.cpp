#include <time.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

#define TESTN 2048


int main(int argc, char** argv) {
	int ch;
	bool slowMode = true;
	while((ch = getopt(argc, argv, "fsn:")) != -1) {
		switch(ch)
		{
		   case 's':
			  slowMode = true;
			  break;
		   case 'f':
			  slowMode = false;
			  break;
		}
	}
	cout<<(slowMode?"arr[j][i]":"arr[i][j]")<<endl;

	char arr[TESTN][TESTN];
	clock_t start, end;

	if (!slowMode) {
		start =clock();
		for(int i = 0; i < TESTN; i++) {
		    for(int j = 0; j < TESTN; j++) {
		        arr[i][j] = 0;
		    }
		}
		end =clock();
	    cout<<timediff(start,end)<<endl;
	}else {
		start =clock();
		for(int i = 0; i < TESTN; i++) {
		    for(int j = 0; j < TESTN; j++) {
		        arr[j][i] = 0;
		    }
		}
		end =clock();
		cout<<timediff(start,end)<<endl;
	}
}
