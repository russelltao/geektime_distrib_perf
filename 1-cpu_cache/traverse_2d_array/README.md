# C++程序traverse_2d_array.cpp
## 编译程序
### 安装编译依赖的软件
如Linux中需要安装gcc-c++，CentOS中可用yum install gcc-c++安装，Ubuntu中可用apt-get install gcc-c++
### 编译程序
`g++ traverse_2d_array.cpp -o traverse_2d_array`
### 运行验证
#### 使用array[i][j]遍历数组
`./traverse_2d_array -f`
#### 使用array[j][i]遍历数组
`./traverse_2d_array -s`
### 使用perf验证缓存命中率
#### 使用array[i][j]遍历数组
perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_2d_array -f
#### 使用array[j][i]遍历数组
perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads ./traverse_2d_array -s
# python程序traverse_2d_array.py