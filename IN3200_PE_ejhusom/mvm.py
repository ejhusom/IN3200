import numpy as np

def mvm(A, x, it):
    for i in range(it):
        x = np.dot(A,x)
    return x

A = np.array([[0, 0, 0.5], [0.5, 0, 0.5], [0.5, 0, 0]])
a = 1.0/3
x = np.array([a, a, a])


print(mvm(A,x,2))
