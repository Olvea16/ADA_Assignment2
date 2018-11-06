# -*- coding: utf-8 -*-
"""
Created on Tue Nov  6 16:12:31 2018

@author: SimonLBS
"""
import matplotlib.pyplot as plt
import json
file = input("File path to JSON: ")
with open(file) as f:
    data = json.load(f)

plt.figure()
plt.plot(data["xdata"], data["ydata"])
plt.xlabel(data["xlabel"])
plt.ylabel(data["ylabel"])
plt.title(data["titel"])
plt.show()
