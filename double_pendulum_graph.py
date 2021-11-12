import numpy  as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

plt.xlabel('Time')
plt.ylabel('Theta')

def animate(i):
    data = np.loadtxt('/Users/jakubkurc/Desktop/Studia/Fizyka-Studia/FizykaProjekt/data.txt')
    x = data[:, 0]
    y1 = data[:, 1]
    y2 = data[:, 2]
    
    plt.cla()
    plt.plot(x, y1)
    plt.plot(x, y2)

ani = FuncAnimation(plt.gcf(), animate, interval=50)

plt.show()