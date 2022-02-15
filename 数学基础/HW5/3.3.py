#!/usr/bin/env python
# coding: utf-8

# In[24]:



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
    
for N in range(2,34,2):
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


    VT = np.transpose(V_A) 
    FT = np.transpose(F_A)
    MV = np.matmul(VT,V_A)
    MF = np.matmul(FT,F_A)
    print (np.all(np.linalg.eigvals(MV) > 0))
    print (np.all(np.linalg.eigvals(MF) > 0))


# In[ ]:





# In[ ]:





# In[ ]:




