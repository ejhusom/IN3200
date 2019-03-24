#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Plot time usage in IN3200 Partial exam - by Erik Johannes Husom on 24.03.2019
# Code is run 5 times for each test.
import matplotlib.pyplot as plt
import numpy as np


notredame_threads1 = np.array([1.660366, 1.611475, 1.492251, 1.514054, 1.635661])
notredame_threads2 = np.array([1.144967, 1.146439, 1.171869, 1.221594, 1.148341])
notredame_threads3 = np.array([1.074792, 1.155493, 1.112271, 1.069995, 1.071155])
notredame_threads4 = np.array([1.129281, 1.216000, 1.158350, 1.135586, 1.131051])

stanford_threads1 = np.array([2.950018, 3.254515, 3.178825, 3.056444, 3.017733])
stanford_threads2 = np.array([1.717559, 1.749409, 1.761823, 1.700695, 1.925599])
stanford_threads3 = np.array([2.108439, 2.053987, 2.058087, 2.009013, 2.127920])
stanford_threads4 = np.array([])

berkstan_threads1 = np.array([8.632797, 8.621575, 8.586063, 8.082310, 8.501536])
berkstan_threads2 = np.array([6.754331, 4.343911, 4.081742, 5.861859, 4.259250])
berkstan_threads3 = np.array([5.195232, 5.585364, 4.704594])
berkstan_threads4 = np.array([])


notredame_read = np.array([0.412195, 0.397453, 0.404293, 0.395382, 0.396027])
notredame_top = np.array([0.008180, 0.008684, 0.007819, 0.007779, 0.008089])

stanford_read = np.array([0.674724, 0.681683, 0.671328, 0.673130, 0.686087])
stanford_top = np.array([0.006808, 0.007417, 0.006791, 0.006777, 0.006785])

berkstan_read = np.array([3.153049, 3.215710, 3.131762, 3.137375, 3.131903])
berkstan_top = np.array([0.017123, 0.017431, 0.017285, 0.037139, 0.017071])

threads1 = np.array([1, 1, 1, 1, 1])
threads2 = np.array([2, 2, 2, 2, 2])
threads3 = np.array([3, 3, 3, 3, 3])
threads4 = np.array([4, 4, 4, 4, 4])

# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 8})
plt.rc("text", usetex=True)
plt.rc('font', family='serif')
w = 5; h = 2.5

# TIME USAGE VS NUMBEROF THREADS
plt.figure(figsize=(w,h))

plt.plot(threads1, notredame_threads1, 'bo', label="web-NotreDame")
plt.plot(threads2, notredame_threads2, 'bo', label="web-NotreDame")
plt.plot(threads3, notredame_threads3, 'bo', label="web-NotreDame")
plt.plot(threads4, notredame_threads4, 'bo', label="web-NotreDame")

plt.plot(threads1, stanford_threads1, 'ro', label="web-Stanford")
plt.plot(threads2, stanford_threads2, 'ro', label="web-Stanford")
plt.plot(threads3, stanford_threads3, 'ro', label="web-Stanford")
#plt.plot(threads4, stanford_threads4, 'bo', label="web-Stanford")

plt.xlabel("number of threads")
plt.ylabel("time usage [s]")
plt.legend()
plt.tight_layout()
plt.savefig("runtime.pdf",dpi=300)
plt.show()
