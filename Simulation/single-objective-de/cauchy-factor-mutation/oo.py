
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.path as path
import matplotlib.animation as animation
from scipy import stats
import numpy as np
def dcauchy(mu, gamma, N):
#  return np.random.normal(mu, gamma+0.001, size=N);
   return np.random.normal(mu, gamma, N)
   data = mu + gamma*np.tan(np.pi*( np.random.randn(N)-0.5 ))
   for i in range(len(data)):
	   while data[i] < 0.0:
	      data[i] = mu + gamma*np.tan(np.pi*( np.random.randn(1)-0.5 ))	
	   if data[i] > 1.0:
	      data[i] = 1.0
   return data

fig = plt.figure(figsize=(8, 6))
#fig,ax = plt.subplots()
ax = fig.add_subplot(111)

# histogram our data with numpy
#data =  dcauchy(0.5, 0.01, 1000)
#n, bins = np.histogram(data, 100)

# get the corners of the rectangles for the histogram
#left = np.array(bins[:-1])
#right = np.array(bins[1:])
#bottom = np.zeros(len(left))
#top = bottom + n
#nrects = len(left)

# here comes the tricky part -- we have to set up the vertex and path
# codes arrays using moveto, lineto and closepoly

# for each rect: 1 for the MOVETO, 3 for the LINETO, 1 for the
# CLOSEPOLY; the vert for the closepoly is ignored but we still need
## it to keep the codes aligned with the vertices
#nverts = nrects*(1 + 3 + 1)
#verts = np.zeros((nverts, 2))
#codes = np.ones(nverts, int) * path.Path.LINETO
#codes[0::5] = path.Path.MOVETO
#codes[4::5] = path.Path.CLOSEPOLY
#verts[0::5, 0] = left
#verts[0::5, 1] = bottom
#verts[1::5, 0] = left
#verts[1::5, 1] = top
#verts[2::5, 0] = right
#verts[2::5, 1] = top
#verts[3::5, 0] = right
#verts[3::5, 1] = bottom

#barpath = path.Path(verts, codes)
#patch = patches.PathPatch(
#    barpath, facecolor='green', edgecolor='yellow', alpha=0.5)
#ax.add_patch(patch)
#

total=30
N=10000


#ax.set_xlim(left[0], right[-1])
#ax.set_ylim(bottom.min(), top.max())
#x1 = np.array([-7, -5, 1, 4, 5], dtype=np.float)
#kde1 = stats.gaussian_kde(x1)
#ax.plot(x1, np.zeros(x1.shape), 'b+', ms=20)
#x_eval = np.linspace(-10, 10, num=N)
#ax.plot(x_eval, kde1(x_eval), 'k-', label="Scott's Rule")
data = dcauchy( 0.5 ,0.05 , N)#np.random.randn(1000)

ax.hist(data, bins=100, normed=True)

def animate(i):
    # simulate new data coming in
    print(0.5*i/total)
    data = dcauchy( 0.2 ,0.05 , N)#np.random.randn(1000)
    #data = dcauchy( 0.5 ,0.5*i/total , N)#np.random.randn(1000)
    #xs = np.linspace(data.min()-1, data.max()+1, N)
   # ax.plot(xs, stats.norm.pdf(xs), 'r--')
    ax.hist(data, bins=100, normed=True)
#    ax.plot(xs, kde1(xs), 'r--')

 #   n, bins = np.histogram(data, 100)
 #   top = bottom + n
 #   verts[1::5, 1] = top
 #   verts[2::5, 1] = top
    return ax,

ani = animation.FuncAnimation(fig, animate, total, repeat=False, blit=True)	
ani.save('Simulation_factor-mutation.mp4')
plt.show()
