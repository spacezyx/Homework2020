#!/usr/bin/env python
# coding: utf-8

# In[4]:


import numpy as np
from fractions import Fraction
from matplotlib import pyplot as plt

def func():
    p = np.poly1d([1, Fraction(-29, 20), Fraction(29, 36), Fraction(-31, 144), Fraction(1, 36), Fraction(-1, 720)])
    print(p.roots)
    x = np.linspace(0, 1, 1001)
    plt.plot(x, p(x))
    plt.show()

func()


# In[ ]:




