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
`g++ cpu_migrate.cpp -o cpu_migrate -lpthread`
* 注意，多线程依赖pthread库，编译时需要链接
### b. 运行验证
#### 使用14个（共28个CPU核心）并发线程测试，不绑定CPU
`./cpu_migrate -t 14 -s`
平均每线程消耗时间（毫秒）：1083
#### 使用14个（共28个CPU核心）并发线程测试，绑定CPU
`./cpu_migrate -t 14 -f`
平均每线程消耗时间（毫秒）：926
### c. 使用perf验证缓存命中率
#### 使用14个（共28个CPU核心）并发线程测试，不绑定CPU
`perf stat -e cpu-migrations,cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads,L1-icache-load-misses,branch-load-misses,branch-loads ./cpu_migrate -t 14 -s`
* 输出结果：
```
 Performance counter stats for './cpu_migrate -t 14 -s':

                10      cpu-migrations
         8,193,825      cache-references                                              (44.40%)
           175,792      cache-misses              #    2.145 % of all cache refs      (44.34%)
    45,480,238,906      instructions              #    1.30  insn per cycle           (55.47%)
    35,111,144,560      cycles                                                        (55.47%)
        11,997,428      L1-dcache-load-misses     #    0.05% of all L1-dcache hits    (55.57%)
    26,407,960,253      L1-dcache-loads                                               (55.60%)
         2,459,766      L1-icache-load-misses                                         (55.66%)
         2,136,304      branch-load-misses                                            (44.53%)
     3,825,848,726      branch-loads                                                  (44.43%)

       1.251076337 seconds time elapsed

      14.630618000 seconds user
       0.459616000 seconds sys
```
#### 使用14个（共28个CPU核心）并发线程测试，绑定CPU
`perf stat -e cpu-migrations,cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads,L1-icache-load-misses,branch-load-misses,branch-loads ./cpu_migrate -t 14 -f`
* 输出结果：
```
 Performance counter stats for './cpu_migrate -t 14 -f':

                14      cpu-migrations
         4,983,541      cache-references                                              (44.42%)
         1,611,627      cache-misses              #   32.339 % of all cache refs      (44.34%)
    45,523,818,723      instructions              #    1.52  insn per cycle           (55.43%)
    29,972,627,158      cycles                                                        (55.46%)
         5,812,831      L1-dcache-load-misses     #    0.02% of all L1-dcache hits    (55.53%)
    26,388,005,477      L1-dcache-loads                                               (55.58%)
         1,262,533      L1-icache-load-misses                                         (55.66%)
         1,363,376      branch-load-misses                                            (44.54%)
     3,828,570,015      branch-loads                                                  (44.47%)

       0.948650967 seconds time elapsed

      12.489932000 seconds user
       0.456253000 seconds sys
```
