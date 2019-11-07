import time
import sys, getopt
import numpy as np

try:
   opts, args = getopt.getopt(sys.argv,"fs")
except getopt.GetoptError:
   print 'test.py -i <inputfile> -o <outputfile>'
   sys.exit(2)

slowMode = True
for opt, arg in opts:
    if opt in ("-f"):
        slowMode = False
    elif opt in ("-s"):
        slowMode = True

TESTN = 1024*10
arr = np.empty((TESTN, TESTN))
t1 = time.time()
if slowMode:
    sum = np.sum(arr,axis=1)
    for i in range(TESTN):
        for j in range(TESTN):
            arr[j][i] = 1
else:
    sum = np.sum(arr,axis=0)
    for i in range(TESTN):
        for j in range(TESTN):
            arr[i][j] = 1
t2 = time.time()
print t2-t1

