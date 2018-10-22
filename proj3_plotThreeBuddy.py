import matplotlib.pyplot as plt
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import numpy as np

verletData = np.loadtxt("velocityVerlet_data.txt")

fileData = np.loadtxt("VelocityVerletData_Class.txt")
objectNames = np.array(['Sun', 'Earth', 'Jupiter'])

x = fileData[:,3]
y = fileData[:,4]
z = fileData[:,5]

f_size = 24

# for i in range(np.size(objectNames)):
#     plt.plot(fileData[:,i*3], fileData[:,i*3+1], label=objectNames[i])
# plt.plot(0,0,'yo')
plt.plot(fileData[:,0*3], fileData[:,0*3+1],'y')
plt.plot(fileData[:,1*3], fileData[:,1*3+1],'b')
plt.plot(fileData[:,2*3], fileData[:,2*3+1],'r')

plt.plot(fileData[-1,0],fileData[-1,1], 'yo')
plt.plot(fileData[-1,3],fileData[-1,4], 'bo')
plt.plot(fileData[-1,6],fileData[-1,7], 'ro')

plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.xlabel('$x$ [AU]', size=f_size)
plt.ylabel('$y$ [AU]', size=f_size)
plt.title(r'Sun, Earth, Jupiter$\times1000$', size=f_size)
plt.legend(['Sun','Earth','Jupiter'],fontsize=f_size-7,loc='upper right')
plt.axis('scaled')
plt.tight_layout()
# plt.savefig('SunFixedJupiter0.png')
plt.show()
