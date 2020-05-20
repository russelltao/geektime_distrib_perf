## 1. 验证环境
* 操作系统: CentOS7.0
* CPU: Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz
* GCC-C++: 4.8.5
* JAVA: 1.8.0
* Python: 2.7.5
## 2. C++程序traverse_1d_array.cpp
### a. 编译程序
#### 安装编译依赖的软件
如Linux中需要安装gcc-c++，CentOS中可用`yum install gcc-c++`安装，Ubuntu中可用`apt-get install gcc-c++`
#### 编译程序
`g++ traverse_1d_array.cpp -o traverse_1d_array`
### b. 运行验证
#### 以步长为1遍历数组
`./traverse_1d_array -s 1`
消耗时间（毫秒）：20
#### 以步长为128遍历数组
`./traverse_1d_array -s 128`
消耗时间（毫秒）：280
#### 以步长为1024遍历数组
`./traverse_1d_array -s 1024`
消耗时间（毫秒）：1850
### c. 使用perf验证缓存命中率
#### 以步长为1遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_1d_array -s 1`
* 输出结果：
```
 Performance counter stats for './traverse_1d_array -s 1':

           332,787      cache-references                                              (82.95%)
            26,230      cache-misses              #    7.882 % of all cache refs      (67.17%)
       111,702,471      instructions              #    1.61  insn per cycle           (83.59%)
        69,498,357      cycles                                                        (83.57%)
           250,109      L1-dcache-load-misses     #    0.43% of all L1-dcache hits    (83.58%)
        58,115,659      L1-dcache-loads                                               (82.72%)

       0.030938059 seconds time elapsed

       0.026916000 seconds user
       0.004098000 seconds sys
```
#### 以步长为128遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_1d_array -s 128`
* 输出结果：
```
        34,246,770      cache-references                                              (83.16%)
           912,881      cache-misses              #    2.666 % of all cache refs      (66.44%)
       137,729,629      instructions              #    0.16  insn per cycle           (83.27%)
       844,462,327      cycles                                                        (83.51%)
        25,917,035      L1-dcache-load-misses     #   38.92% of all L1-dcache hits    (83.51%)
        66,593,669      L1-dcache-loads                                               (83.39%)

       0.291569229 seconds time elapsed

       0.066179000 seconds user
       0.225442000 seconds sys

```
#### 以步长为1024遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_1d_array -s 1024`
* 输出结果：
```
       148,684,923      cache-references                                              (83.32%)
         8,213,600      cache-misses              #    5.524 % of all cache refs      (66.64%)
       312,534,826      instructions              #    0.06  insn per cycle           (83.32%)
     5,593,728,896      cycles                                                        (83.32%)
       148,953,141      L1-dcache-load-misses     #  133.42% of all L1-dcache hits    (83.37%)
       111,642,681      L1-dcache-loads                                               (83.35%)

       1.894789074 seconds time elapsed

       0.158064000 seconds user
       1.736704000 seconds sys
```