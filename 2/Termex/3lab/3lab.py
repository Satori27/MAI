import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math
from scipy.integrate import odeint

Steps = 500
t_fin = 20
t = np.linspace(0, t_fin, Steps)


def odesys(y, t, m, c, l1, l2, g):
    dy = np.zeros(4)
    dy[0] = y[2]
    dy[1] = y[3]

    a11 = np.cos(y[0]-[1])*l2
    a12 = 2*l1
    a21 = l2
    a22 = np.cos(y[0]-y[1])*l1

    b1 = -(2*g+((c*l1)/m)*np.cos(y[1]))*np.sin(y[1])
    b2 = -y[3]**2*np.sin(y[0]-y[1])*l1-g*np.sin(y[0])

    dy[2] = (b1*a22 - b2*a12)/(a11*a22 - a12*a21)
    dy[3] = (b2*a11 - b1*a21)/(a11*a22 - a12*a21)

    return dy

m = 0.1
c = 5
l1 = 3
l2 = 4
g = 9.81

psi0 = math.pi/20
phi0 = 0
dpsi0 = 0
dphi0 = 0
y0 = [psi0, phi0, dpsi0, dphi0]

Y = odeint(odesys, y0, t, (m, c, l1, l2, g))


fig = plt.figure(figsize=[15, 7])
ax = fig.add_subplot(1, 1, 1)
ax.set(xlim=[-2, 18], ylim=[-4, 10])


psi = Y[:, 0]
phi = Y[:, 1]
dpsi = Y[:, 2]
dphi = Y[:, 3]
# ddx = [odesys(y, t, m, c, l1, l2, g)[2]]
ddphi = [odesys(y,t,m,c,l1,l2,g)[3] for y,t in zip(Y,t)]


N = m*(g*np.cos(psi) - l1*(ddphi*np.sin(psi-phi) - dphi**2*np.cos(psi-phi))+l2*dpsi**2)

fig_for_graphs = plt.figure(figsize=[13,7])
# В отдельном окне откроем графики функций
ax_for_graphs = fig_for_graphs.add_subplot(2, 2, 1)
ax_for_graphs.plot(t, phi, color='Blue')
ax_for_graphs.set_title("phi(t)")
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

ax_for_graphs = fig_for_graphs.add_subplot(2, 2, 3)
ax_for_graphs.plot(t, psi, color='Red')
ax_for_graphs.set_title("psi(t)")
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

ax_for_graphs = fig_for_graphs.add_subplot(2, 2, 2)
ax_for_graphs.plot(t, N, color='Red')
ax_for_graphs.set_title("N(t)")
ax_for_graphs.set(xlim=[0, t_fin])
ax_for_graphs.grid(True)

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


# Отрисовываем фигуры
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