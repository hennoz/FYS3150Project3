import matplotlib.pyplot as plt
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import numpy as np

verletData = np.loadtxt("velocityVerlet_data.txt")

t = verletData[:,0]

xVerlet = verletData[:,1]
yVerlet = verletData[:,2]

energyVerlet = np.loadtxt("energy_verlet_data.txt")

Kv  = energyVerlet[:,0]
Pv  = energyVerlet[:,1]
dKv = energyVerlet[:,2]
dPv = energyVerlet[:,3]

eulerData = np.loadtxt("ForwardEuler_data.txt")

xEuler = eulerData[:,1]
yEuler = eulerData[:,2]

energyEuler = np.loadtxt("energy_euler_data.txt")

Ke  = energyEuler[:,0]
Pe  = energyEuler[:,1]
dKe = energyEuler[:,2]
dPe = energyEuler[:,3]

f_size = 28
# plt.plot(xVerlet,yVerlet, label=r'$v(0) > 2\pi\sqrt{2}$')
# plt.plot(0,0,'yo')
# plt.plot(xVerlet[-1],yVerlet[-1], 'bo')
# plt.xticks(size=f_size, rotation=30)
# plt.yticks(size=f_size, rotation=30)
# plt.xlabel('$x$ [AU]', size=f_size)
# plt.ylabel('$y$ [AU]', size=f_size)
# plt.title('Escape velocity', size=f_size)
# plt.legend(fontsize=f_size-5)
# plt.axis('scaled')
# plt.tight_layout()
# plt.savefig('VelVerlet2D_escape2.png')
# plt.show()

plt.plot(xVerlet,yVerlet)
plt.plot(0,0,'yo')
plt.plot(xVerlet[-1],yVerlet[-1], 'bo')
plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.xlabel('$x$ [AU]', size=f_size)
plt.ylabel('$y$ [AU]', size=f_size)
plt.title('VelocityVerlet', size=f_size)
plt.axis('scaled')
plt.tight_layout()
plt.savefig('VelVerlet2D.png')
plt.show()
#
plt.plot(xEuler,yEuler)
plt.plot(0,0,'yo')
plt.plot(xEuler[-1],yEuler[-1], 'bo')
plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.xlabel('$x$ [AU]', size=f_size)
plt.ylabel('$y$ [AU]', size=f_size)
plt.title('ForwardEuler', size=f_size)
plt.axis('scaled')
plt.tight_layout()
plt.savefig('ForEuler2D.png')
plt.show()

plt.plot(xVerlet,yVerlet)
plt.plot(0,0,'yo')
plt.plot(xVerlet[-1],yVerlet[-1], 'bo')
plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.xlabel('$x$ [AU]', size=f_size)
plt.ylabel('$y$ [AU]', size=f_size)
plt.title('VelocityVerlet', size=f_size)
plt.axis('scaled')
plt.tight_layout()
plt.xlim(0.8,1.2)
plt.ylim(-0.2,0.2)
plt.savefig('VelVerlet2D_zoom.png')
plt.show()

plt.plot(xEuler,yEuler)
plt.plot(0,0,'yo')
plt.plot(xEuler[-1],yEuler[-1], 'bo')
plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.xlabel('$x$ [AU]', size=f_size)
plt.ylabel('$y$ [AU]', size=f_size)
plt.title('ForwardEuler', size=f_size)
plt.axis('scaled')
plt.tight_layout()
plt.xlim(0.8,1.2)
plt.ylim(-0.2,0.2)
plt.savefig('ForEuler2D_zoom.png')
plt.show()

plt.plot(t,Pv)
plt.plot(t,Kv)
plt.title('VelocityVerlet', size=f_size)
plt.legend(['Potential energy', 'Kinetic energy'], fontsize=f_size)
plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.xlabel('Time [years]', size=f_size)
plt.ylabel('Energy (rel)', size=f_size)
plt.tight_layout()
plt.savefig('EnergyVerlet2D.png')
plt.show()


plt.plot(t,Pe)
plt.plot(t,Ke)
plt.title('ForwardEuler', size=f_size)
plt.legend(['Potential energy', 'Kinetic energy'], fontsize=f_size)
plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.xlabel('Time [years]', size=f_size)
plt.ylabel('Energy (rel)', size=f_size)
plt.tight_layout()
plt.savefig('EnergyEuler2D.png')
plt.show()
