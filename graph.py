import numpy  as np
import matplotlib.pyplot as plt
import time

data = np.loadtxt('data.txt')

x = data[:, 0]
y1 = data[:, 1]
y2 = data[:, 2]

plt.title('green = theta1    red = theta2')
plt.plot(x, y1, color='green')
plt.xlabel('time')
plt.ylabel('theta')
plt.plot(x, -y2, color='red')
plt.xlabel('time')
plt.ylabel('theta')

plt.savefig('result.png')
plt.show()