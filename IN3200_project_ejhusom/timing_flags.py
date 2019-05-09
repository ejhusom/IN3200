#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Plot time usage in IN3200 Project Image Denoising - by Erik Johannes Husom on 09.05.2019
import numpy as np

data_O2 = np.loadtxt('serial_code/timing_serial_O2.txt')
data_O3 = np.loadtxt('serial_code/timing_serial_O3.txt')
data_O4 = np.loadtxt('serial_code/timing_serial_O4.txt')
serial_timings = np.mean(serial_data)

print("Serial mean time: {:f}".format(serial_timings))
