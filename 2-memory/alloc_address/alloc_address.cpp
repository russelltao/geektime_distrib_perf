#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void* threadFunc(void* arg) {
	printf("在子线程调用malloc前，还未分配线程的heap堆栈\n");
    getchar();
    char* addr = (char*) malloc(1);
    printf("子线程调用malloc后，此1字节的内存起始地址：0X%x\n", addr);
	printf("当然，addr变量是在线程栈中分配的，它的地址：0X%x\n", &addr);
    getchar();
    free(addr);
    printf("释放了1字节的线程堆内存，但heap堆并不会释放\n");
    getchar();
}

int main() {
    pthread_t t1;
    void* s;
    int ret;
    char* addr;

    printf("使用cat /proc/%d/maps查看内存分配\n",getpid());
    printf("在主线程调用malloc前，还未分配heap堆栈\n");
    getchar();
    addr = (char*) malloc(1);
    printf("主线程调用malloc后，此1字节的内存起始地址：0X%x\n", addr);
	printf("当然，addr变量是在栈中分配的，它的地址：0X%x\n", &addr);
    getchar();
    free(addr);
    printf("释放了1字节的内存，但heap堆并不会释放\n");
	printf("接下来分配8MB内存\n");
	getchar();
	addr = (char*) malloc(1*1024*1024);
	printf("分配了8MB内存\n");
	getchar();
	free(addr);
	printf("接下来分配1GB内存\n");
    getchar();
	addr = (char*) malloc(1024*1024*1024);
	printf("分配1GB内存后，可以看到heap堆已经申请到，但用top命令可以看到物理内存并没有增长\n");
	getchar();
	free(addr);
    ret = pthread_create(&t1, NULL, threadFunc, NULL);
    if(ret)
    {
        printf("Thread creation error\n");
        return -1;
    }
    ret = pthread_join(t1, &s);
    if(ret)
    {
        printf("Thread join error\n");
        return -1;
    }
    return 0;
}
