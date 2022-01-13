import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
import numpy
import sys


n = []
insert = []
quick = []
merge = []
heap = []
com = []

with open('output') as f:
    file_input = f.read()

cases = file_input.split('\n\n\n')
for case in cases:
    if not case:
        continue
    print('case: ', case)
    lines = case.split('\n')
    print('line: ', lines[0])
    n += [int(lines[0].split('= ')[1])]
    insert += [float((lines[1].split('=> ')[1]).split(' ')[0])]
    quick += [float((lines[2].split('=> ')[1]).split(' ')[0])]
    merge += [float((lines[3].split('=> ')[1]).split(' ')[0])]
    heap += [float((lines[4].split('=> ')[1]).split(' ')[0])]
    com += [float((lines[5].split('=> ')[1]).split(' ')[0])]

f1 = plt.figure(1)
plt.plot(n, insert, label='insertion')
plt.plot(n, quick, label='quicksort')
plt.plot(n, merge, label='mergesort')
plt.plot(n, heap, label='heapsort')
plt.plot(n, com, label='composite')
plt.legend()

f2 = plt.figure(2)
plt.plot(n, quick, label='quicksort')
plt.plot(n, merge, label='mergesort')

plt.plot(n, heap, label='heapsort')
plt.plot(n, com , label='composite')
plt.legend()


plt.show()
