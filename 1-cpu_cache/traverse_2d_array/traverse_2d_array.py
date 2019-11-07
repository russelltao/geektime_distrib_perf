import time
import sys, getopt


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

TESTN = 10240
arr = [[0 for col in range(TESTN)] for row in range(TESTN)]
t1 = time.time()
if slowMode:
    for i in range(TESTN):
        for j in range(TESTN):
            arr[j][i] = 1
else:
    for i in range(TESTN):
        for j in range(TESTN):
            arr[i][j] = 1
t2 = time.time()
print t2-t1

