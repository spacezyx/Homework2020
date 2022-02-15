#!/usr/bin/env python
# coding: utf-8

# In[7]:


import numpy as np
import PIL
import PIL.Image
from matplotlib import pyplot as plt


def func():
    # open image in grey-scale
    img = PIL.Image.open("lena.jpg").convert('L')
    img_seq = img.getdata()
    # reshape and normalize to [0,1]
    img_arr = np.array(img_seq).reshape(256, 256) * (1.0 / 255)
    u, sig, vt = np.linalg.svd(img_arr)
    print(sig)

func()


# In[ ]:




