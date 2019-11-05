perf stat -e cache-references,cache-misses,instructions,cycles,L1-dcache-load-misses,L1-dcache-loads,L1-icache-load-misses,branch-load-misses,branch-loads ./branch -f
g++ branch.cpp -o branch
