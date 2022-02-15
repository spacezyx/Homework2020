#!/usr/bin/env python
# coding: utf-8

# In[11]:


import numpy as np
from fractions import Fraction
from matplotlib import pyplot as plt

def func():
    p = np.poly1d([1, Fraction(-29, 20), Fraction(29, 36), Fraction(-31, 144), Fraction(1, 36), Fraction(-1, 720)])
    
    x_1 = 0
    x0 = 0.45
    while True:
        a = (p(x0) - p(x_1))/(x0 - x_1)
        b = p(x_1) - a*x_1
        x = -b/a
        if abs(p(x)) < 1e-11:
            break
        if (p(x) > 0 and p(x_1) > 0) or (p(x) < 0 and p(x_1 < 0)):
            x_1 = x
        else:
            x0 = x

    print("The root for Secant method is:",x)

func()


# In[ ]:




