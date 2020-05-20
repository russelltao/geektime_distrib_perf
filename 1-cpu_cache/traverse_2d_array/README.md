## 1. 验证环境
* 操作系统: CentOS7.0
* CPU: Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz
* GCC-C++: 4.8.5
* JAVA: 1.8.0
* Python: 2.7.5
## 2. C++程序traverse_2d_array.cpp
### a. 编译程序
#### 安装编译依赖的软件
如Linux中需要安装gcc-c++，CentOS中可用`yum install gcc-c++`安装，Ubuntu中可用`apt-get install gcc-c++`
#### 编译程序
`g++ traverse_2d_array.cpp -o traverse_2d_array`
### b. 运行验证
#### 使用array[i][j]遍历数组
`./traverse_2d_array -f`
消耗时间（毫秒）：10
#### 使用array[j][i]遍历数组
`./traverse_2d_array -s`
消耗时间（毫秒）：70
### c. 使用perf验证缓存命中率
#### 使用array[i][j]遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_2d_array -f`
* 输出结果：
```
 Performance counter stats for './traverse_2d_array -f':

           147,927      cache-references                                              (80.14%)
            13,215      cache-misses              #    8.933 % of all cache refs      (65.49%)
        54,454,827      instructions              #    1.43  insn per cycle           (85.11%)
        38,197,267      cycles                                                        (85.09%)
           161,503      L1-dcache-load-misses     #    0.90% of all L1-dcache hits    (85.09%)
        18,035,307      L1-dcache-loads                                               (84.19%)

       0.020651344 seconds time elapsed

       0.018625000 seconds user
       0.002069000 seconds sys
```
#### 使用array[j][i]遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_2d_array -s`
* 输出结果：
```
 Performance counter stats for './traverse_2d_array -s':

         4,341,186      cache-references                                              (83.01%)
            13,974      cache-misses              #    0.322 % of all cache refs      (66.03%)
        55,245,646      instructions              #    0.25  insn per cycle           (83.01%)
       218,787,967      cycles                                                        (83.00%)
         4,308,394      L1-dcache-load-misses     #   23.79% of all L1-dcache hits    (83.86%)
        18,112,753      L1-dcache-loads                                               (84.10%)

       0.082950118 seconds time elapsed

       0.079066000 seconds user
       0.003953000 seconds sys
```
## 3. Java程序
### a. 编译程序
`javac traverse_2d_array.java`
### b.运行验证
#### 使用array[i][j]遍历数组
`java traverse_2d_array -f`
消耗时间（毫秒）：20
#### 使用array[j][i]遍历数组
`java traverse_2d_array -s`
消耗时间（毫秒）：100
### c. 使用perf验证缓存命中率
#### 使用array[i][j]遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads java traverse_2d_array -f`
* 输出结果：
```
 Performance counter stats for 'java traverse_2d_array -f':

         6,379,138      cache-references                                              (80.62%)
           866,578      cache-misses              #   13.585 % of all cache refs      (68.93%)
       459,726,039      instructions              #    1.51  insn per cycle           (85.22%)
       303,673,757      cycles                                                        (85.69%)
         5,270,707      L1-dcache-load-misses     #    3.96% of all L1-dcache hits    (81.64%)
       133,211,743      L1-dcache-loads                                               (83.13%)

       0.126089887 seconds time elapsed

       0.122353000 seconds user
       0.047877000 seconds sys
```
#### 使用array[j][i]遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads java traverse_2d_array -s`
* 输出结果：
```
 Performance counter stats for 'java traverse_2d_array -s':

        42,441,956      cache-references                                              (80.21%)
           872,336      cache-misses              #    2.055 % of all cache refs      (66.61%)
       386,326,280      instructions              #    0.71  insn per cycle           (84.29%)
       544,411,061      cycles                                                        (85.01%)
        38,884,991      L1-dcache-load-misses     #   32.48% of all L1-dcache hits    (85.24%)
       119,711,464      L1-dcache-loads                                               (82.94%)

       0.192838747 seconds time elapsed

       0.200693000 seconds user
       0.052919000 seconds sys
```