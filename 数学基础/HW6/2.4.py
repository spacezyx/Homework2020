#!/usr/bin/env python
# coding: utf-8

# In[ ]:





# In[50]:


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

def func():
    h = 0.01
    N = 99
    x = np.arange(0, 1, h)
    x = np.delete(x, 0, None)
    A = matrix(N)
    M = np.power(h, -2) * A
    v, my_vector = np.linalg.eig(M)

    func_x = np.argsort(v)
    v.sort()
    func_y = [ my_vector[:,func_x[-1]],  my_vector[:,func_x[-2]],  my_vector[:,func_x[-3]]]
    print("The result is : \n")
    print(v[::-1][0:3])
    plt.plot(x, func_y[0], 'g', label= '-Π^2')
    plt.plot(x, func_y[1], 'b', label= '-4Π^2')
    plt.plot(x, func_y[2], 'r', label= '-9Π^2')
    plt.legend()
    plt.show()

func()


# In[ ]:





# In[ ]:





# In[ ]:




