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

flags = np.array([2, 3])
iterations = 300
num_procs = 8
    
procs = np.linspace(1,num_procs, num_procs, dtype=int)
parallel_timings = np.zeros(num_procs)
parallel_std = np.zeros(num_procs)


for flag in flags:
    for i in procs:
        parallel_data = np.loadtxt('parallel_code/flagO{:d}_{:d}_timing_parallel_{:d}_procs.txt'.format(flag, iterations, i))
        mean_time = np.mean(parallel_data)
        parallel_timings[(i-1)] = mean_time
        parallel_std[(i-1)] = np.std(parallel_data)

    if (flag == 0):
        plt.plot(procs, parallel_timings, label='no flag')
    elif (flag == 100):
        plt.plot(procs, parallel_timings, label='new algo')
    else:
        plt.plot(procs, parallel_timings, label='flag=O{:d}'.format(flag))
    #plt.errorbar(procs, parallel_timings, yerr=parallel_std, barsabove=True)

#for i in procs:
#    parallel_data = np.loadtxt('parallel_code/timing_parallel_{:d}_procs.txt'.format(i))
#    mean_time = np.mean(parallel_data)
#    parallel_timings[(i-1)] = mean_time
#    parallel_std[(i-1)] = np.std(parallel_data)

plt.xlabel("number of threads")
plt.ylabel("time usage [s]")
plt.xticks(procs)
plt.legend()
plt.tight_layout()
plt.savefig("runtime.pdf",dpi=300)
plt.show()


serial_data = np.loadtxt('serial_code/timing_serial.txt')
serial_timings = np.mean(serial_data)

print("Serial mean time: {:f}".format(serial_timings))
print("Parallel minimum time: {:f}".format(np.min(parallel_timings)))
