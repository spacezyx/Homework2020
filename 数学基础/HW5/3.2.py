#!/usr/bin/env python
# coding: utf-8

# In[68]:


import math
import numpy as np

from __future__ import division
from scipy import linalg as la
from scipy import optimize
import sympy
sympy.init_printing()
import matplotlib.pyplot as plt


N=8
M=16

def f(x):
    return (1/(1+(x**2)))

def x_i(i,m):
    return (i/(m))

def V(x_i,j):
    return ((x_i)**j)

def F(x_i,j,N):
    if((1<=j)and(j<=(N/2))):
        return np.sin(j*(math.pi)*(x_i))
    if((((N/2)+1)<=j)and(j<=N)):
        return np.cos((j-(N/2))*(math.pi)*(x_i))
    
def func(N,type):
    F_A=np.ones((N,N))
    V_A=np.ones((N,N))
    f_A=np.ones(N)

    for i in range(N):
        for j in range(N):
            X_i=x_i(i,N-1)
            F_x=F(X_i,(j+1),N)
            F_A[i,j]=F_x

    for i in range(N):
        for j in range(N):
            X_i=x_i(i,N-1)
            V_x=V(X_i,j)
            V_A[i,j]=V_x

    if type==F:
        return np.linalg.cond(F_A)

    if type==V:
        return np.linalg.cond(V_A)

x = np.linspace(4,32,15)
x = x.astype(np.uint8)
y = [func(i,F) for i in x]

x = np.linspace(4,32,15)
x = x.astype(np.uint8)
y1 = [func(i,V) for i in x]
print(x)
print(y1)

plt.yscale('log')
plt.plot(x,y,'r',label='N vs. cond(F)')
plt.plot(x,y1,'b',label='N vs. cond(V)')
plt.legend()
plt.show()


# In[ ]:





# In[ ]:




