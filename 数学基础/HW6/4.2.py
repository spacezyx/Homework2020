#!/usr/bin/env python
# coding: utf-8

# In[6]:


import numpy as np
from fractions import Fraction
from matplotlib import pyplot as plt

def func():
    p = np.poly1d([1, Fraction(-29, 20), Fraction(29, 36), Fraction(-31, 144), Fraction(1, 36), Fraction(-1, 720)])
    p2 = np.polyder(p)
    x0 = 0.45
    x1 = x0 - p(x0)/p2(x0)

    while abs(x1-x0) > 1e-10:
        x0 = x1
        x1 = x0 - p(x0)/p2(x0)

    print("The root for Newton method is ",x1)

func()


# In[ ]:




