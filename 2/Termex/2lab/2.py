import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math

fig = plt.figure(figsize=[15, 7])
ax = fig.add_subplot(1, 1, 1)
ax.set(xlim=[-1, 18], ylim=[-4, 10])


Steps = 500
t_fin = 20
t = np.linspace(0, t_fin, Steps)


phi = 0.6*np.sin(1*t)
psi = 0.4*np.sin(1.5*t)
l1 = 3
l2 = 4

X_A = 2.5
Y_A = 6

X_B = X_A+l1*np.sin(phi)
Y_B = Y_A-l1*np.cos(phi)

X_C = X_B+l2*np.sin(psi)
Y_C = Y_B-l2*np.cos(psi)

BoxX = 1
BoxY = 2

X_Box = np.array([-2*BoxX, 0, 0, -2*BoxX, -2*BoxX])
Y_Box = np.array([Y_B[0]/3, Y_B[0]/3, -Y_B[0]/3, -Y_B[0]/3, Y_B[0]/3])

X_Triangle = np.array([2, 3, 2.5, 2])
Y_Triangle = np.array([6.5, 6.5, 6.05, 6.5])

X_Ground = [-2, -2, 12]
Y_Ground = [8, -3, -3]
X_Ground1 = np.array([0, 0])
Y_Ground1 = np.array([0, 6])


K = 17
Sh = 0.4
b = 1/(K-2)
X_Spr = np.zeros(K)
Y_Spr = np.zeros(K)
X_Spr[0] = 0
Y_Spr[0] = 0
X_Spr[K-1] = 1
Y_Spr[K-1] = 0
for i in range(K-2):
    X_Spr[i+1] = b*((i+1) - 1/2)
    Y_Spr[i+1] = Sh*(-1)**i

L_SprX = X_B
L_SprY = Y_B


Drawed_Spring = ax.plot(X_Spr*L_SprX[0], (Y_Spr+Y_A)+L_SprY[0]-l1)[0]
Drawed_Box = ax.plot(X_Box, Y_Box, linewidth=3)[0]
Drawed_Triangle = ax.plot(X_Triangle, Y_Triangle)[0]


Drawed_AB = ax.plot([X_A, X_B[0]], [Y_A, Y_B[0]], linewidth=2)[0]
Point_A = ax.plot(X_A, Y_A, marker='o', markersize=5)[0]
Drawed_BC = ax.plot([X_B[0], X_C[0]], [Y_B[0], Y_C[0]], linewidth=2)[0]
Point_B = ax.plot(X_B[0], Y_B[0], marker='o', markersize=15)[0]
Point_C = ax.plot(X_C[0], Y_C[0], marker='o', markersize=15)[0]
ax.plot(X_Ground, Y_Ground, color='Black', linewidth=2)
ax.plot(X_Ground1, Y_Ground1, color='Black', linewidth=2)

def anima(i):
    Drawed_AB.set_data([X_A, X_B[i]], [Y_A, Y_B[i]])
    Drawed_BC.set_data([X_B[i], X_C[i]], [Y_B[i], Y_C[i]])
    Drawed_Spring.set_data(X_Spr*L_SprX[i], (Y_Spr+L_SprY[i]+Y_A)-l1-l1)
    Drawed_Box.set_data(X_Box, Y_Box+Y_B[i])
    Point_B.set_data(X_B[i], Y_B[i])
    Point_C.set_data(X_C[i], Y_C[i])

    return [Drawed_AB, Point_B, Drawed_Spring, Drawed_BC]

anim = FuncAnimation(fig, anima, frames=len(t), interval=40, repeat=False)

plt.show()