#!/usr/bin/env python
# coding: utf-8

# In[55]:


import math
import numpy as np
import scipy.linalg as spla

from __future__ import division
from scipy import linalg as la
from scipy import optimize
import sympy
sympy.init_printing()
import matplotlib.pyplot as plt


N=8
M=16
N1=4

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
    
F_A=np.ones((M,N))
V_A=np.ones((M,N))
F_A1=np.ones((M,N1))
V_A1=np.ones((M,N1))
f_A=np.ones(M)

for i in range(M):
    for j in range(N):
        X_i=x_i(i,M-1)
        F_x=F(X_i,(j+1),N)
        F_A[i,j]=F_x
        
for i in range(M):
    for j in range(N1):
        X_i=x_i(i,M-1)
        F_x=F(X_i,(j+1),N1)
        F_A1[i,j]=F_x

for i in range(M):
    for j in range(N):
        X_i=x_i(i,M-1)
        V_x=V(X_i,j)
        V_A[i,j]=V_x
        
for i in range(M):
    for j in range(N1):
        X_i=x_i(i,M-1)
        V_x=V(X_i,j)
        V_A1[i,j]=V_x
            
for i in range(M):
    X_i=x_i(i,M-1)
    f_x=f(X_i)
    f_A[i]=f_x

Q1,R1 = np.linalg.qr(F_A)
Q2,R2 = np.linalg.qr(V_A)
XV = spla.solve_triangular(R2, Q2.T.dot(f_A), lower=False)
# print("The answer for V matrix when M=16,N=8 is \n",XV)
XF = spla.solve_triangular(R1, Q1.T.dot(f_A), lower=False)
# print("The answer for F matrix when M=16,N=8 is \n",XF)

Q11,R11 = np.linalg.qr(F_A1)
Q21,R21 = np.linalg.qr(V_A1)
XV1 = spla.solve_triangular(R21, Q21.T.dot(f_A), lower=False)
# print("The answer for V matrix when M=16,N=4 is \n",XV1)
XF1 = spla.solve_triangular(R11, Q11.T.dot(f_A), lower=False)
# print("The answer for F matrix when M=16,N=4 is \n",XF1)

TTXF1= [x_i(i,15) for i in range(M)]
TXF1 =[x_i(i,15) for i in range (N)]
TYF1 = np.matmul(F_A,TXF1)

TTXV1= [x_i(i,15) for i in range(M)]
TXV1 =[x_i(i,15) for i in range (N)]
TYV1 = np.matmul(V_A,TXV1)

TTXF2 = [x_i(i,15) for i in range(M)]
TXF2 =[x_i(i,7) for i in range (N1)]
TYF2 = np.matmul(F_A1,TXF2)

TTXV2= [x_i(i,15) for i in range(M)]
TXV2 =[x_i(i,7) for i in range (N1)]
TYV2 = np.matmul(V_A1,TXV2)

plt.plot(TTXF1,TYF1,'r',label='M=16,N=8 for gF')
plt.plot(TTXV1,TYV1,'b',label='M=16,N=8 for gV')
plt.plot(TTXF2,TYF2,'g',label='M=16,N=4 for gF')
plt.plot(TTXV2,TYV2,'y',label='M=16,N=4 for gV')
plt.legend()
plt.show()


# In[ ]:





# In[ ]:




