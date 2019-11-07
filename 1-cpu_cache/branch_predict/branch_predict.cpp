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
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(int argc, char** argv) {
	int mode = 1;
	int ch;
	while((ch = getopt(argc, argv, "fsg")) != -1) {
		switch(ch)
		{
		   case 's':
			  mode = 1;
			  break;
		   case 'f':
			  mode = 2;
			  break;
		   case 'g':
			  mode = 3;
			  break;
		}
	}

	unsigned char* arr = new unsigned char[TESTN];

	if (3 == mode) {
		for (long i = 0; i < TESTN; i++) arr[i] = rand() % 256;
		ofstream ofs;
		ofs.open("rand.array", ios::out | ios::binary);
		ofs.write((const char*)arr, TESTN);
		ofs.close();
		sort(arr,arr+TESTN);
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

		clock_t start,end;
		start =clock();
		for(long i = 0; i < TESTN; i++) {
			if (arr[i] < 128) arr[i] = 0;
		}
		end =clock();
	    cout<<" "<<timediff(start,end)<<endl;
	}
}
