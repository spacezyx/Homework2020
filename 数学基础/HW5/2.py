#!/usr/bin/env python
# coding: utf-8

# In[51]:


from scipy import integrate
import numpy as np
import matplotlib.pyplot as plt
import math
 
def func(x, mu, sigma):
    return np.exp( -1 * ( (x-mu) ** 2) / ( 2 * (sigma ** 2)) ) / (math.sqrt( 2 * np.pi ) * sigma)

mu, sigma = 0, 1
x = np.linspace( mu - 6 * sigma, mu + 6 * sigma, 100)
y = func(x, mu, sigma)

mu1, sigma1 = 1, 0.5
x1 = np.linspace( mu1 - 6 * sigma1, mu1 + 6 * sigma1, 100)
y1 = func(x1, mu1, sigma1)

mu2, sigma2 = 2, 1
x2 = np.linspace( mu2 - 6 * sigma2, mu2 + 6 * sigma2, 100)
y2 = func(x2, mu2, sigma2)

mu3, sigma3 = 0.5, 2
x3 = np.linspace( mu3 - 6 * sigma3, mu3 + 6 * sigma3, 100)
y3 = func(x3, mu3, sigma3)

plt.plot(x, y, 'r', label='mu = 0,sigma = 1')
plt.plot(x1, y1, 'b', label='mu = 1,sigma = 0.5')
plt.plot(x2, y2, 'y', label='mu = 2,sigma = 1')
plt.plot(x3, y3, 'g', label='mu = 0.5,sigma = 2')

plt.legend()
plt.grid()
plt.show()

v, err = integrate.quad(func, -60, 60, args = (0, 1)) 
print ("mu=0,sigma=1.0,the integral is%10.3f" %v) 

v, err = integrate.quad(func, -60, 60, args = (1, 0.5)) 
print ("mu=1,sigma=0.5,the integral is%10.3f" %v) 

v, err = integrate.quad(func, -60, 60, args = (2, 1)) 
print ("mu=2,sigma=1.0,the integral is%10.3f" %v) 

v, err = integrate.quad(func, -60, 60, args = (0.5, 2)) 
print ("mu=0.5,sigma=2,the integral is%10.3f" %v) 


# In[ ]:




