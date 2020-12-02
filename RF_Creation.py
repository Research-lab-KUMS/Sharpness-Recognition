# Simulation mechanoreceptor grid and receptive fields of afferents
# ADEL PARVIZI-FARD

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy import signal
import random
from IPython import get_ipython
from scipy.signal import find_peaks
get_ipython().run_line_magic('matplotlib', 'qt')

# %%
#   (Parameters) #####################

n = 5  # patch of skin dimension
m = 5
un_in = []

rrr = [1, 3, 7, 9]  # on average innervated taxels
nnn = [1, 3, 5, 9]
rrr = [3]
nnn = [3]

for rr, nn in zip(rrr, nnn):
    N_MR = rr
    #
    R = nn
    #
    N = 18

    # create receptive field for afferents ######################################

    RF = np.zeros((n, m, N))
    random.seed(6227)
    np.random.seed(144457)

    index1 = np.arange(N)
    random.shuffle(index1)
    random.shuffle(index1)

    print(index1)
    center = []
    jiter = 1
    space = 1
    for j in range(5):
        for t1 in range(4):
            center.append([t1 * space + n / 5] + [j * space + m / 5])
    x0_y0_SA = np.array(center)

    RR = 5
    for i in range(N):
        x1 = np.random.normal(int(x0_y0_SA[i, 0]), R / RR, N_MR)
        y = np.random.normal(int(x0_y0_SA[i, 1]), R / RR, N_MR)
        x1 = x1.astype(int)
        y = y.astype(int)
        iii = np.where((x1 < 0))
        x1[iii] = 0
        iii = np.where((x1 > m - 1))
        x1[iii] = m - 1
        iii = np.where((y < 0))
        y[iii] = 0
        iii = np.where((y > n - 1))
        y[iii] = n - 1
        for j in range(len(x1)):
            RF[y[j], x1[j], index1[i]] = random.uniform(0.1, 0.8)

    random.seed(42123)
    numbers = np.arange(N)

    SA_index = numbers[0:int(1 * N / 3)]
    RA_index = numbers[int(1 * N / 3):N]
    RF_1 = np.zeros((n, m))

#%% plot individual receptive field of each afferent
    for j in range(N):
        plt.subplot(4, 5, j + 1)
        RF_1 += RF[:, :, j]
        plt.imshow(RF[:, :, j], extent=([0, n, 0, m]), vmin=0, vmax=1)
        plt.title('#{}'.format(j + 1))
plt.figure(2)
plt.imshow(RF_1, extent=([0, n, 0, m]),vmin=0,vmax=max(RF_1.ravel()))
plt.show()

# %% convert Receptive fields to text file for interface board
f = open("RF_Arduino_6.txt", "w")
for j in range(N):
    f.write('float RF{0}[25]={{{1}}};\n'.format(j + 1, str(list(np.array(RF[:, :, j]).flatten()))[1:-1]))
f.close()