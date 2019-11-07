## 1. C++程序traverse_1d_array.cpp
### a. 编译程序
#### 安装编译依赖的软件
如Linux中需要安装gcc-c++，CentOS中可用`yum install gcc-c++`安装，Ubuntu中可用`apt-get install gcc-c++`
#### 编译程序
`g++ traverse_1d_array.cpp -o traverse_1d_array`
### b. 运行验证
#### 使用array[i][j]遍历数组
`./traverse_1d_array -f`
#### 使用array[j][i]遍历数组
`./traverse_1d_array -s`
### c. 使用perf验证缓存命中率
#### 使用array[i][j]遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_1d_array -f`
#### 使用array[j][i]遍历数组
`perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_1d_array -s`
## 2. python程序traverse_1d_array.py