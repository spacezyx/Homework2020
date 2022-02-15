#!/usr/bin/env python
# coding: utf-8

# In[64]:



import math
import numpy as np

from __future__ import division
from scipy import linalg as la
from scipy import optimize
import sympy
sympy.init_printing()
import matplotlib.pyplot as plt

N=8

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
    
# 建立矩阵(M=N=8)
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
        
for i in range(N):
        X_i=x_i(i,N-1)
        f_x=f(X_i)
        f_A[i]=f_x
        
        
# VT = np.transpose(V_A) 
# FT = np.transpose(F_A)

MV = np.matmul(V_A.T,V_A)
MF = np.matmul(F_A.T,F_A)

array1 = np.matmul(V_A.T,f_A)
array2 = np.matmul(F_A.T,f_A)

L1 = la.cholesky(MV,lower=True)
y1 = la.solve(L1, array1)
c1 = la.solve(L1.T,y1)
normV = la.norm(np.matmul(MV,c1)-array1)
print("c of Vc=f is\n",c1)
print("norm for V is",normV)

L2 = la.cholesky(MF,lower=True)
y2 = la.solve(L2, array2)
c2 = la.solve(L2.T,y2)
normF = la.norm(np.matmul(MF,c2)-array2)
print("c of Vc=f is\n",c2)
print("norm for F is",normF)


# In[ ]:





# In[ ]:





# In[ ]:




