# -*- coding: utf-8 -*-
"""
Created on Tue Nov  6 16:12:31 2018

@author: SimonLBS
"""
import matplotlib.pyplot as plt
import json
import tkinter as tk
from tkinter.filedialog import askopenfilename
root = tk.Tk()
root.withdraw()

file = askopenfilename(title = "JSON file")

with open(file) as f:
    data = json.load(f)

legend = []
plotString = "("
count = 0
while True:
    if "xdata_{}".format(count) in data:
        if count != 0:
            plotString+=", "
        plotString+="""data["xdata_{}"], data["ydata_{}"]""".format(count,count)
        legend.append(data["legend_{}".format(count)])
        count += 1
    else:
        break
plotString += ")"
    
print(plotString)
plt.figure()
exec("plt."+data["plotType"]+plotString)
plt.xlabel(data["xlabel"])
plt.ylabel(data["ylabel"])
plt.legend(legend)
plt.title(data["titel"])
plt.show()
