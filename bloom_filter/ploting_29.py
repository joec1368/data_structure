import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator
import numpy
import sys

plot_filename = sys.argv[1]
n = sys.argv[2]
u = sys.argv[3]
with open(plot_filename) as f:
    lines = f.readlines()
    x = [line.split()[0] for line in lines]
    y = [line.split()[1] for line in lines]

last = y[-1]
y_crop = list(map(lambda d: float(d), list(filter(lambda d: d != last, y)) + [last]))
x_crop = list(map(lambda d: int(d), x[:len(y_crop)]))

min_index = numpy.argmin(y_crop)
min_coor = (x_crop[min_index], y_crop[min_index])
plt.title(f'Bloom Filter error rate. (N, U) = ({n}, {u})')
#plt.figure().gca().xaxis.set_major_locator(MaxNLocator(integer=True))
plt.plot(x_crop, y_crop, marker = 'o')
plt.ylabel('error rate')
plt.xlabel('# of hash functions')
plt.annotate(f'min: {min_coor}', min_coor)
plt.xticks([1, x_crop[-1]])
plt.show()
