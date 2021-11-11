import numpy  as np
import matplotlib.pyplot as plt
import time
from matplotlib.animation import FuncAnimation

def animate(i):
    data = np.loadtxt('data.txt')
    x = data[:, 0]
    y1 = data[:, 1]
    y2 = data[:, 2]
    
    plt.cla()
    plt.plot(x, y1)
    plt.plot(x, y2)

ani = FuncAnimation(plt.gcf(), animate, interval=100)

plt.show()