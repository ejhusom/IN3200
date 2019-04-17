#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Plot time usage in IN3200 Partial exam - by Erik Johannes Husom on 24.03.2019
# Code is run 5 times for each test.
import matplotlib.pyplot as plt
import numpy as np


notredame_threads1 = np.array([1.660366, 1.611475, 1.492251, 1.514054, 1.635661])
notredame_threads2 = np.array([1.144967, 1.146439, 1.171869, 1.221594, 1.148341])
notredame_threads3 = np.array([1.074792, 1.155493, 1.112271, 1.069995, 1.071155])
notredame_threads4 = np.array([1.129281, 1.180224, 1.158350, 1.135586, 1.131051])
notredame = np.array([
        np.mean(notredame_threads1),
        np.mean(notredame_threads2),
        np.mean(notredame_threads3),
        np.mean(notredame_threads4)])
notredame_std = np.array([
        np.std(notredame_threads1),
        np.std(notredame_threads2),
        np.std(notredame_threads3),
        np.std(notredame_threads4)])

stanford_threads1 = np.array([2.950018, 3.254515, 3.178825, 3.056444, 3.017733])
stanford_threads2 = np.array([1.717559, 1.749409, 1.761823, 1.700695, 1.925599])
stanford_threads3 = np.array([1.990699, 1.979894, 1.974490, 1.973875, 2.127920])
stanford_threads4 = np.array([1.809684, 1.822082, 1.684422, 1.689830, 1.716332])
stanford = np.array([
        np.mean(stanford_threads1),
        np.mean(stanford_threads2),
        np.mean(stanford_threads3),
        np.mean(stanford_threads4)])

berkstan_threads1 = np.array([8.632797, 8.621575, 8.586063, 8.082310, 8.501536])
berkstan_threads2 = np.array([6.754331, 4.343911, 4.081742, 5.861859, 4.259250])
berkstan_threads3 = np.array([5.195232, 5.585364, 4.704594, 4.635240, 5.406529])
berkstan_threads4 = np.array([4.042900, 3.957007, 4.381022, 5.084178, 4.699359])
berkstan_threads5 = np.array([3.848768, 3.878695, 3.864901, 4.040139, 4.149730])
berkstan_threads6 = np.array([3.793445, 3.866507, 4.163662, 3.867370, 3.795713])
berkstan = np.array([
        np.mean(berkstan_threads1),
        np.mean(berkstan_threads2),
        np.mean(berkstan_threads3),
        np.mean(berkstan_threads4),
        np.mean(berkstan_threads5),
        np.mean(berkstan_threads6)])


notredame_read = np.array([0.412195, 0.397453, 0.404293, 0.395382, 0.396027])
notredame_top = np.array([0.008180, 0.008684, 0.007819, 0.007779, 0.008089])

stanford_read = np.array([0.674724, 0.681683, 0.671328, 0.673130, 0.686087])
stanford_top = np.array([0.006808, 0.007417, 0.006791, 0.006777, 0.006785])

berkstan_read = np.array([3.153049, 3.215710, 3.131762, 3.137375, 3.131903])
berkstan_top = np.array([0.017123, 0.017431, 0.017285, 0.037139, 0.017071])

threads = np.array([1, 2, 3, 4])
threads_expand = np.array([1, 2, 3, 4, 5, 6])
threads1 = np.array([1, 1, 1, 1, 1])
threads2 = np.array([2, 2, 2, 2, 2])
threads3 = np.array([3, 3, 3, 3, 3])
threads4 = np.array([4, 4, 4, 4, 4])
threads5 = np.array([5, 5, 5, 5, 5])
threads6 = np.array([6, 6, 6, 6, 6])

# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 8})
plt.rc("text", usetex=True)
plt.rc('font', family='serif')
w = 5; h = 4

# TIME USAGE VS NUMBER OF THREADS
plt.figure(figsize=(w,h))

#plt.plot(threads, notredame, 'b-x')
#plt.plot(threads1, notredame_threads1, 'b.', label="web-NotreDame")
#plt.plot(threads2, notredame_threads2, 'b.', label="web-NotreDame")
#plt.plot(threads3, notredame_threads3, 'b.', label="web-NotreDame")
#plt.plot(threads4, notredame_threads4, 'b.', label="web-NotreDame")
#
#plt.plot(threads, stanford, 'r-x')
#plt.plot(threads1, stanford_threads1, 'r.', label="web-Stanford")
#plt.plot(threads2, stanford_threads2, 'r.', label="web-Stanford")
#plt.plot(threads3, stanford_threads3, 'r.', label="web-Stanford")
#plt.plot(threads4, stanford_threads4, 'r.', label="web-Stanford")
#
plt.plot(threads_expand, berkstan, 'g-x')
plt.plot(threads1, berkstan_threads1, 'g.', label="web-BerkStan")
plt.plot(threads2, berkstan_threads2, 'g.', label="web-BerkStan")
plt.plot(threads3, berkstan_threads3, 'g.', label="web-BerkStan")
plt.plot(threads4, berkstan_threads4, 'g.', label="web-BerkStan")
plt.plot(threads5, berkstan_threads5, 'g.', label="web-BerkStan")
plt.plot(threads6, berkstan_threads6, 'g.', label="web-BerkStan")

plt.xlabel("number of threads")
plt.ylabel("time usage [s]")
plt.xticks([1,2,3,4,5,6])
plt.legend()
plt.tight_layout()
plt.savefig("runtime.pdf",dpi=300)
plt.show()

# TIME USAGE FOR SERIAL FUNCTIONS
print(np.mean(notredame_read))
print(np.mean(notredame_top))
print(np.mean(stanford_read))
print(np.mean(stanford_top))
print(np.mean(berkstan_read))
print(np.mean(berkstan_top))

