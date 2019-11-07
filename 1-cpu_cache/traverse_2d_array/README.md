## 1. C++程序traverse_2d_array.cpp
### a. 编译程序
#### 安装编译依赖的软件
如Linux中需要安装gcc-c++，CentOS中可用`yum install gcc-c++`安装，Ubuntu中可用`apt-get install gcc-c++`
#### 编译程序
`g++ traverse_2d_array.cpp -o traverse_2d_array`
### b. 运行验证
#### 验证环境
* 操作系统: CentOS7.0
* CPU: Intel(R) Xeon(R) CPU E5-2620 v4 @ 2.10GHz
#### 使用array[i][j]遍历数组
`./traverse_2d_array -f`
消耗时间（毫秒）：10
#### 使用array[j][i]遍历数组
`./traverse_2d_array -s`
消耗时间（毫秒）：70
### c. 使用perf验证缓存命中率
#### 使用array[i][j]遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_2d_array -f`
输出结果：
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
输出结果：
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
## 2. python程序traverse_2d_array.py