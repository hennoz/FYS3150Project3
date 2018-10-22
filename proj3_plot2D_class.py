import matplotlib.pyplot as plt
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import numpy as np

verletData = np.loadtxt("velocityVerlet_data.txt")

t = verletData[:,0]

x = verletData[:,1]
y = verletData[:,2]

f_size = 24
plt.plot(x,y, label=r'$F_G = \frac{GMm}{r^\beta}$')
plt.plot(0,0,'yo')
plt.plot(x[-1],y[-1], 'bo')
plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.xlabel('$x$ [AU]', size=f_size)
plt.ylabel('$y$ [AU]', size=f_size)
plt.title('Escape velocity', size=f_size)
plt.legend(fontsize=f_size-5, loc='lower right')
plt.axis('scaled')
plt.tight_layout()
plt.savefig('VelVerlet2D_beta.png')
plt.show()
