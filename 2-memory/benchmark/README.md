### 编译tcmalloc库
#### 预安装库
autoconf、automake、libtool
CentOS下安装：yum install autoconf automake libtool
Ubuntu下安装：apt-get install autoconf、automake、libtool
#### 生成configure文件
./autogen.sh
#### 生成Makefile文件
./configure

*配置选项通过--help查询*

#### 编译
make
#### 安装
make install

### benchmark性能测试

#### 编译benchmark文件
g++ benchmark.cpp -o benchmark -lpthread

#### benchmark命令行选项
1. -s: 分配内存块大小，单位字节
2. -t: 线程数
3. -n: 每个线程循环分配内存的次数

#### 基于ptmalloc2测试
export LD_PRELOAD=""; ./benchmark -s 262144 -t 80 -n 1000000

#### 基于TcMalloc测试
*根据configure生成的libtcmalloc.so文件的位置填写LD_PRELOAD*

export LD_PRELOAD="/lib64/libtcmalloc.so"; ./benchmark -s 262144 -t 80