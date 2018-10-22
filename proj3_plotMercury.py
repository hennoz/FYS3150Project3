import matplotlib.pyplot as plt
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import numpy as np

# precession = np.loadtxt("precession_GR.dat")
precession = np.loadtxt("MercuryData.txt")
# objectNames = np.array(['Sun', 'Mercury'])

t = precession[:,0] # stepsize h
y = precession[:,1] # precession

arcsec = 3600*np.arctan(precession[:,1])*180/np.pi

coeff = np.polyfit(t,arcsec,1)
p = np.poly1d(coeff)


f_size = 24

print("Perihelion precession per century: ", p(t[-1])-p(t[0]))

plt.title('Perihelion precession of Mercury',size=f_size)

plt.plot(t, 3600*np.arctan(y)*180/np.pi,'r')
plt.plot(t,p(t),'k')
plt.xlabel('Time [years]',size=f_size)
plt.ylabel('Arcseconds',size=f_size)
plt.xticks(size=f_size, rotation=30)
plt.yticks(size=f_size, rotation=30)
plt.legend(['Linefit', 'Precession'],fontsize=f_size-4)
# plt.axis('scaled')
plt.tight_layout()
plt.show()


#
# w = 13; h = 8
# fig = plt.figure(figsize=(w,h))
# ax = fig.gca(projection='3d')
#
# f_size = 24
#
# for i in range(np.size(objectNames)):
#     plt.plot(fileData[:,i*3], fileData[:,i*3+1], fileData[:,i*3+2], label=objectNames[i])
#
# xLabel = ax.set_xlabel('$x$ [AU]',size=f_size)
# yLabel = ax.set_ylabel('$y$ [AU]',size=f_size)
# zLabel = ax.set_zlabel('$z$ [AU]',size=f_size)
# plt.title('Mercury perihelion',size=f_size)
# plt.legend(['Sun', 'Mercury'],fontsize=f_size-3,loc='upper left')
# # plot = ax.plot([1,2,3],[1,2,3])
# # ax.dist = 5
# # plt.xlabel('$x$ [AU]',size=f_size)
# # plt.ylabel('$y$ [AU]',size=f_size)
# # ax.set_zlabel('$z$ [AU]',size=f_size)
# plt.xticks(size=f_size)
# plt.yticks(size=f_size)
# for t in ax.zaxis.get_major_ticks(): t.label.set_fontsize(f_size)
# ax.axis('tight')
# # ax.set_xlim3d(-4,4)
# # ax.set_ylim3d(-4,4)
# # ax.set_zlim3d(-1,1)
# plt.tight_layout()
# plt.show()
