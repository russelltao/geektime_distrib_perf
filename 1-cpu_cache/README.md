### traverse_2d_array
验证连续内存的二维数组是否采用顺序访问以致性能不同。array[i][j]性能优于array[j][i]。
* 特别是C++程序中的数组相比python的list容器内存更加连续，故性能表现更优 
### traverse_1d_array
 验证cpu cache line批量载入缓存带来的性能提升时，traverse_2d_array存放了指针导致性能提升有上限。
 traverse_1d_array一维数组没有存放8字节的指针，性能提升更大。
### branch_predict
 验证了分支预测的作用
### cpu_migrate
 不考虑多核时，该程序在循环中反复使用有限内存中的数据，缓存命中率非常高。
 当开启多个线程时，由于发生了CPU迁移，导致缓存命中率下降，性能也有明显的下降。