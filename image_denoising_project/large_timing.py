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

iterations = 100
num_procs = 12
    
procs = np.linspace(1,num_procs, num_procs, dtype=int)
parallel_timings = np.zeros(num_procs)
parallel_std = np.zeros(num_procs)



serial_data = np.loadtxt('serial_code/large_{:d}_timing_serial.txt'.format(iterations))
serial_mean = np.mean(serial_data)
serial_timings = np.ones(num_procs)*serial_mean
plt.plot(procs, serial_timings, '--', label='serial')

for i in procs:
    parallel_data = np.loadtxt('parallel_code/large_{:d}_timing_parallel_{:d}_procs.txt'.format(iterations, i))
    mean_time = np.mean(parallel_data)
    parallel_timings[(i-1)] = mean_time
    parallel_std[(i-1)] = np.std(parallel_data)

    plt.plot(procs, parallel_timings, '.-', label='parallel')



plt.xlabel("number of MPI processes")
plt.ylabel("time usage [s]")
plt.xticks(procs)
plt.legend(loc='lower left', bbox_to_anchor=(0,1.02,1,0.2), ncol=2, mode="expand")
#plt.tight_layout()
plt.show()



#print("Serial mean time: {:f}".format(serial_timings))
#print("Parallel minimum time: {:f}".format(np.min(parallel_timings)))
