import matplotlib.pyplot as plt
# plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# fileData = np.loadtxt("ForwardEulerData_Class.txt")
fileData = np.loadtxt("VelocityVerletData_Class.txt")
# objectNames = np.array(['Sun', 'Earth', 'Jupiter'])
objectNames = np.array(['Sun', 'Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune', 'Pluto'])
x = fileData[:,3]
y = fileData[:,4]
z = fileData[:,5]

w = 13; h = 8
fig = plt.figure(figsize=(w,h))
ax = fig.ca(projection='3d')

f_size = 24

for i in range(np.size(objectNames)):
    plt.plot(fileData[:,i*3], fileData[:,i*3+1], fileData[:,i*3+2], label=objectNames[i])

# plt.rcParams.update({'font.size': f_size})


xLabel = ax.set_xlabel('\n \n $x$ [AU]',size=f_size)
yLabel = ax.set_ylabel('\n \n $y$ [AU]',size=f_size)
zLabel = ax.set_zlabel('\n $z$ [AU]',size=f_size)
plt.title('Solar system, Velocity Verlet',size=f_size)
plt.legend(['Sun', 'Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter',
 'Saturn', 'Uranus', 'Neptune', 'Pluto'],fontsize=f_size-3,loc='upper left')
# plot = ax.plot([1,2,3],[1,2,3])
# ax.dist = 5
# plt.xlabel('$x$ [AU]',size=f_size)
# plt.ylabel('$y$ [AU]',size=f_size)
# ax.set_zlabel('$z$ [AU]',size=f_size)
plt.xticks(size=f_size)
plt.yticks(size=f_size)
for t in ax.zaxis.get_major_ticks(): t.label.set_fontsize(f_size)
ax.axis('tight')
# ax.set_xlim3d(-4,4)
# ax.set_ylim3d(-4,4)
# ax.set_zlim3d(-1,1)
plt.tight_layout()
plt.show()
