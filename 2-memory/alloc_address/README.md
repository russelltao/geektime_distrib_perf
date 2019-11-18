### 编译
g++ alloc_address.cpp -o alloc_address -lpthread

### 执行测试
./alloc_address
*在进程等待输入时，用新的窗口查看内存分配情况（cat /proc/进程ID/maps），敲击回车继续*
