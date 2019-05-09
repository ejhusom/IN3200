#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Plot time usage in IN3200 Project Image Denoising - by Erik Johannes Husom on 09.05.2019
import matplotlib.pyplot as plt
import numpy as np


# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 8})
plt.rc("text", usetex=True)
plt.rc('font', family='serif')
w = 5; h = 4

# TIME USAGE VS NUMBER OF THREADS
plt.figure(figsize=(w,h))


num_procs = np.array([2, 3, 4, 5, 6])
parallel_timings = np.zeros(5)
parallel_data = np.loadtxt('parallel_code/timing_parallel_4_procs.txt')

for i in num_procs:
    parallel_data = np.loadtxt('parallel_code/timing_parallel_{:d}_procs.txt'.format(i))
    mean_time = np.mean(parallel_data)
    parallel_timings[(i-2)] = mean_time


plt.plot(num_procs, parallel_timings, '.-', label='parallel code')

plt.xlabel("number of threads")
plt.ylabel("time usage [s]")
plt.xticks([2,3,4,5,6])
plt.tight_layout()
plt.savefig("runtime.pdf",dpi=300)
plt.show()


serial_data = np.loadtxt('serial_code/timing_serial.txt')
serial_timings = np.mean(serial_data)

print("Serial mean time: {:f}".format(serial_timings))
print("Parallel minimum time: {:f}".format(np.min(parallel_timings)))
