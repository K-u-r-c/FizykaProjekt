import numpy  as np
import matplotlib.pyplot as plt

data = np.loadtxt('data.txt')

x = data[:, 0]
y1 = data[:, 1]
y2 = data[:, 2]

plt.xlabel('t - Time')
plt.ylabel('phi - angle')

plt.plot(x, y1)
plt.plot(x, y2)

plt.show()