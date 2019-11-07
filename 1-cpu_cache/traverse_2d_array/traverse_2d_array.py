import time

TESTN = 10240
arr = [[0 for col in range(TESTN)] for row in range(TESTN)]
t1 = time.time()
for i in range(TESTN):
    for j in range(TESTN):
        arr[i][j] = 1
t2 = time.time()
print t2-t1

t1 = time.time()
for i in range(TESTN):
    for j in range(TESTN):
        arr[j][i] = 1
t2 = time.time()
print t2-t1
