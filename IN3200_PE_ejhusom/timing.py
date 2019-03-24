#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Plot time usage in IN3200 Partial exam - by Erik Johannes Husom on 24.03.2019
# Code is run 10 times for each test.
import matplotlib.pyplot as plt
import numpy as np


notredame_threads1 = np.array([])
notredame_threads2 = np.array([])
notredame_threads3 = np.array([])
notredame_threads4 = np.array([])

stanford_threads1 = np.array([])
stanford_threads2 = np.array([])
stanford_threads3 = np.array([])
stanford_threads4 = np.array([])

berkstan_threads1 = np.array([])
berkstan_threads2 = np.array([])
berkstan_threads3 = np.array([])
berkstan_threads4 = np.array([])


notredame_read = np.array([])
notredame_top = np.array([])

stanford_threads1 = np.array([])
stanford_top = np.array([])

berkstan_read = np.array([])
berkstan_top = np.array([])

# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 8})
plt.rc("text", usetex=True)
plt.rc('font', family='serif')
w = 5; h = 2.5

#plt.figure(figsize=(w,h))
#plt.xlabel("")
#plt.ylabel("No. of iterations")
#plt.legend()
#plt.tight_layout()
#plt.savefig("runtime.pdf",dpi=300)
#plt.show()
