# coding=utf-8
"""
Description:
		Animation Two objectives convergence individuals
author: Joel Chacon Castillo
"""
import numpy as np
from scipy.spatial.distance import pdist, squareform
from numpy import linspace, meshgrid
from matplotlib.mlab import griddata
import matplotlib.pyplot as plt
import scipy.integrate as integrate
import matplotlib.animation as animation


##------------------------------------------
#Read the input file whose is composed of first general header
#and each individuals in objective space
#strf='1_10_dat'
#Files = [strf]
#
#
#names = ['DE']
#colr =['black']
#Instance = 'Problem 1'
#SizePool=100
#NumberSamples = 1000
#Generation = 1
#X = []
#Y = []
#Z = []
#def FilterData(filename, SizePool):
#	with open(filename) as f:
#	    data = f.read()
#	data = data.split('\n')
#	AjustData = list()
#	for line in data:
#           tmp = line.split()
#	   if len(tmp) == 0:
#	     break
#	   X.append(float(tmp[0]))
#           Y.append(float(tmp[1]))
#           Z.append(float(tmp[2]))
#	return data
#
#def getObjectives(indexSample, data, SizePool):
#    Population = data[indexSample*(SizePool):(indexSample+1)*(SizePool)]
#    v1 = []
#    v2 = []
#    f = []
#    for Str in Population:
#       tmp = Str.split()
#       v1.append(float(tmp[0]))
#       v2.append(float(tmp[1]))
#       f.append(float(tmp[2]))
#    return v1, v2, f
#data = {}
#def grid(x, y, z, resX=100, resY=100):
#    "Convert 3 column data to matplotlib grid"
#    xi = linspace(min(x), max(x), resX)
#    yi = linspace(min(y), max(y), resY)
#    Z = griddata(x, y, z, xi, yi)
#    X, Y = meshgrid(xi, yi)
#    return X, Y, Z
#for NameFile in Files:
#   data[NameFile] = FilterData(NameFile, SizePool)

##X,Y,Z = grid(X,Y,Z)
minregion = -1
maxregion = 10
#------------------------------------------------------------
# set up figure and animation
#delta = 0.025
#x = np.arange(minregion, maxregion, delta)
#y = np.arange(minregion, maxregion, delta)
#X, Y = np.meshgrid(x, y)
## difference of Gaussians
#Z = 10.0 * (Y - X)
fig = plt.figure(figsize=(15,10))
#CS = plt.contour(X,Y, Z)
#plt.clabel(CS, fontsize=9, inline=1)
#fig.set_size_inches(100, 100)
#mng = plt.get_current_fig_manager()
#fig.frame.Maximize(True)

dataSpace = fig.add_subplot(121)

CS = dataSpace.contour(X,Y, Z)
dataSpace.clabel(CS, fontsize=9, inline=1)
y = 0.95
i = 0
for tmp in Files:
   dataSpace.set_ylim(-110, 110)
   dataSpace.set_xlim(-110, 110)
   dataSpace.text(0.95, y, names[i],
        verticalalignment='bottom', horizontalalignment='right',
        transform=dataSpace.transAxes,
        color=colr[i], fontsize=15)
   dataSpace.grid()
   time_text = dataSpace.text(0.02, 0.92, '', transform=dataSpace.transAxes)
   y = y - 0.05
   i = i+1
y = 0.95
i = 0
#for tmp in VariablesFiles:
#   VariableSpace.set_ylim(-0.2, 5)
#   VariableSpace.set_xlim(0, 3)
#   VariableSpace.text(0.95, y, names[i],
#        verticalalignment='bottom', horizontalalignment='right',
#        transform=VariableSpace.transAxes,
#        color=colr[i], fontsize=15)
#   VariableSpace.plot([0, 2.2], [1.4, 1.4], color='r')
#   VariableSpace.plot([0, 2.2], [4, 4], color='b')
#   VariableSpace.plot([0, 2.2], [0, 0], color='b')
#   VariableSpace.grid()
#   time_textVar = VariableSpace.text(0.02, 0.92, '', transform=VariableSpace.transAxes)
#   y = y - 0.05
#   i = i+1



IndexPop=0
individualsdata = {}
#Colours = ['bo','ro', 'go', 'mo', 'co', 'wo', 'ko']
Colours = ['bo']
i = 0
for NameFile in Files:
	individualsdata[NameFile], = dataSpace.plot([], [], Colours[i], ms=7)
	i = i+1

def init():
    """initialize animation"""
    for NameFile in Files:
       individualsdata[NameFile].set_data([], [])
    time_text.set_text(Instance)
    return individualsdata[strf], time_text,


def animate(i):
    """perform animation step"""
    global Generation
    #Read the second header....
    for NameFile in Files:
       vi, vj, f = getObjectives(i, data[NameFile], SizePool)
       individualsdata[NameFile].set_data(vi, vj)

#       color = [str(item/255.) for item in f]
    Generation = i
    gn = Generation + 1
    time_text.set_text(u'Espacio objetivo \nGeneración: %d \n' % gn )
    return individualsdata[strf], time_text,

ani = animation.FuncAnimation(fig, animate, frames= NumberSamples,
                              interval=50, blit=True, init_func=init)

animate(1)
# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html
#ani.save('particle_box.mp4', fps=30, extra_args=['-vcodec', 'libx264'])
#ani.save('Simulation_P10.mp4')
#plt.savefig('Simulacion_Algoritmo_4.eps', format='eps', dpi=1000)
plt.show()
