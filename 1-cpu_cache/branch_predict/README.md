## 1. 验证环境
* 操作系统: CentOS7.0
* CPU: Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz
* GCC-C++: 4.8.5
* JAVA: 1.8.0
* Python: 2.7.5
## 2. C++程序branch_predict.cpp
### a. 编译程序
#### 安装编译依赖的软件
如Linux中需要安装gcc-c++，CentOS中可用`yum install gcc-c++`安装，Ubuntu中可用`apt-get install gcc-c++`
#### 编译程序
`g++ branch_predict.cpp -o branch_predict`
### b. 运行验证
#### 准备随机数组与排序好的数组
`./branch_predict -g`
该命令会在当前目录下生成随机数组rand.array文件和有序数组sort.array文件
#### 遍历随机数组
`./branch_predict -s`
消耗时间（毫秒）：1000
#### 遍历有序数组
`./branch_predict -f`
消耗时间（毫秒）：350
### c. 使用perf验证缓存命中率
#### 遍历随机数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./branch_predict -`
```
 Performance counter stats for './branch_predict -s':

     1,504,222,463      instructions              #    0.49  insn per cycle
     3,084,103,065      cycles   
            84,992      L1-icache-load-misses
        67,153,573      branch-load-misses                                          
       273,893,334      branch-loads                                                

       1.040296121 seconds time elapsed

       0.987243000 seconds user
       0.053060000 seconds sys
```
#### 遍历有序数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./branch_predict -f`
* 输出结果：
```
     1,501,478,360      instructions              #    1.27  insn per cycle         
     1,180,637,963      cycles                                                      
            49,351      L1-icache-load-misses
            27,282      branch-load-misses
       273,404,227      branch-loads

       0.404512198 seconds time elapsed

       0.352686000 seconds user  
       0.051845000 seconds sys   
```
