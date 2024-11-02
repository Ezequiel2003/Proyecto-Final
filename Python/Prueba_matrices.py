# -*- coding: utf-8 -*-
"""
Created on Wed Feb 28 09:55:43 2024

@author: Eze
"""

import numpy as np

A_45 = np.array([[],[],[]],dtype=np.uint8)
A = np.empty((0, 3), int)

for i in range (0,5):
    pt1 = (10+i,5+i)
    pt2 = (20+i,4+i)
    m0 = 40+i #pendiente de la recta    
    P = np.array([[m0,0],pt1,pt2])
    A_45 = np.append(A_45,P,1)
    
print(A_45[1][8:10]) #imprime pt1
print(tuple(A_45[1][8:10]))

