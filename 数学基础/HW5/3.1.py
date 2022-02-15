#!/usr/bin/env python
# coding: utf-8

# In[30]:


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
        
# 建立矩阵(M=N=16)
F_A1=np.ones((M,M))
V_A1=np.ones((M,M))
f_A1=np.ones(M)

for i in range(M):
    for j in range(M):
        X_i=x_i(i,M-1)
        F_x=F(X_i,(j+1),M)
        F_A1[i,j]=F_x

for i in range(M):
    for j in range(M):
        X_i=x_i(i,M-1)
        V_x=V(X_i,j)
        V_A1[i,j]=V_x
        
for i in range(M):
        X_i=x_i(i,M-1)
        f_x=f(X_i)
        f_A1[i]=f_x
        

# LU分解(M=N=8)
P, L, U = la.lu(V_A)
# print('L,U = ',L,U)
# print('L * U = ',L * U)
x = la.solve(V_A,f_A)
z = np.matmul(V_A,x)
x_norm1 = np.linalg.norm((z-f_A), ord=None, axis=None, keepdims=False)
print('When N is 8, the solution of VC=f is x = \n',x)
print('The norm is',x_norm1)

P, L, U = la.lu(F_A)
x = la.solve(F_A,f_A)
z = np.matmul(F_A,x)
x_norm2 = np.linalg.norm((z-f_A), ord=None, axis=None, keepdims=False)
print('When N is 8, the solution of FC=f is x = \n',x)
print('The norm is',x_norm2)

# LU分解(M=N=16)
P, L, U = la.lu(V_A1)
# print('L,U = ',L,U)
# print('L * U = ',L * U)
x = la.solve(V_A1,f_A1)
print('When N is 16, the solution of VC=f is x = \n',x)
z = np.matmul(V_A1,x)
x_norm3 = np.linalg.norm((z-f_A1), ord=None, axis=None, keepdims=False)
print('The norm is',x_norm3)

P, L, U = la.lu(F_A1)
x = la.solve(F_A1,f_A1)
print('When N is 16, the solution of FC=f is x = \n',x)
z = np.matmul(F_A1,x)
x_norm4 = np.linalg.norm((z-f_A1), ord=None, axis=None, keepdims=False)
print('The norm is',x_norm4)


# In[ ]:





# In[ ]:




