### 1 在栈中分配内存速度更快
heap_stack.java验证在栈中分配内存比堆中更快
#### 1.1 编译
javac heap_stack.java
#### 1.2 运行
java heap_stack
### 2 编译tcmalloc库
使用TCMalloc库前，需要下载编译它
#### 预安装库
autoconf、automake、libtool
CentOS下安装：yum install autoconf automake libtool
Ubuntu下安装：apt-get install autoconf、automake、libtool
#### 2.1 下载gperftool
https://github.com/gperftools/gperftools.git
#### 2.2 生成configure文件
./autogen.sh
#### 2.3 生成Makefile文件
./configure

*配置选项通过--help查询*

#### 2.4 编译
make
#### 2.5 安装
make install

### 3 benchmark性能测试
对比测试tcmalloc与ptmalloc2的性能
#### 3.1 编译benchmark文件
g++ benchmark.cpp -o benchmark -lpthread

#### 3.2 benchmark命令行选项
1. -s: 分配内存块大小，单位字节
2. -t: 线程数
3. -n: 每个线程循环分配内存的次数

#### 3.3 基于ptmalloc2测试

##### 单线程分配256KB
export LD_PRELOAD=""; ./benchmark -s 262144 -t 1
##### 2线程分配256KB
export LD_PRELOAD=""; ./benchmark -s 262144 -t 2
##### 40线程分配256KB
export LD_PRELOAD=""; ./benchmark -s 262144 -t 40
##### 单线程分配256KB+1字节
export LD_PRELOAD=""; ./benchmark -s 262145 -t 1
##### 10线程分配256KB+1字节
export LD_PRELOAD=""; ./benchmark -s 262145 -t 10

#### 3.4 基于TcMalloc测试
*根据configure生成的libtcmalloc.so文件的位置填写LD_PRELOAD*
##### 单线程分配256KB
export LD_PRELOAD="/lib64/libtcmalloc.so"; ./benchmark -s 262144 -t 1
##### 2线程分配256KB
export LD_PRELOAD="/lib64/libtcmalloc.so"; ./benchmark -s 262144 -t 2
##### 40线程分配256KB
export LD_PRELOAD="/lib64/libtcmalloc.so"; ./benchmark -s 262144 -t 40 
##### 单线程分配256KB+1字节
export LD_PRELOAD="/lib64/libtcmalloc.so"; ./benchmark -s 262145 -t 1
##### 10线程分配256KB+1字节
export LD_PRELOAD="/lib64/libtcmalloc.so"; ./benchmark -s 262145 -t 10 -n 100000