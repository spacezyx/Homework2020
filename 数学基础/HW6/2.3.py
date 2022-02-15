#!/usr/bin/env python
# coding: utf-8

# In[ ]:





# In[27]:


import scipy
import numpy as np
from matplotlib import pyplot as plt

def matrix(N):
    A = np.arange(N * N).reshape(N, N)
    for i in range(N):
        for j in range(N):
            if i == j:
                A[i, j] = -2
            elif np.abs(i - j) == 1:
                A[i, j] = 1
            else:
                A[i, j] = 0
    return A


def func_fai(x, n):
    return np.sqrt(2) * np.sin(np.pi * n * x)

def func():
    N = 99
    h = 0.01
    x = np.arange(0, 1, h)
    x = np.delete(x, 0, None)
    y = func_fai(x, 1)
    A = matrix(N)
    M = np.power(h, -2) * A
    zero = np.linspace(0, 0, 99)
    return (np.allclose(zero, np.dot(M, y) + np.pi ** 2 * y, atol=1e-02))

print(func())


# In[ ]:





# In[ ]:





# In[ ]:




