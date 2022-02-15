#!/usr/bin/env python
# coding: utf-8

# In[9]:


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
    
    p = 256
    k = 2
    while k <= p:
        new_arr = np.dot(np.dot(u[:, :k], np.diag(sig[:k])), vt[:k, :])
        y = np.asarray(new_arr * 255, dtype=np.uint8)
        w = PIL.Image.fromarray(y, mode='L')
        w.save(str(k) + ".png")
        k = k * 2

func()


# In[ ]:




