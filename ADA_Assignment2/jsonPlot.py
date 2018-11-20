#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  6 16:12:31 2018
@author: SimonLBS
"""
import sys
import pandas as pd
import matplotlib.pyplot as plt
import json
import tkinter as tk
from tkinter.filedialog import askopenfilename
root = tk.Tk()
root.withdraw()

def rooling(l, alfa):
    tl = [l[0]]
    for v in l[1:]:
        tl.append(alfa*v + (1-alfa)*tl[-1])
    return tl

file = askopenfilename(title = "JSON file")
if len(file) == 0:
    sys.exit()
    
with open(file) as f:
    data = json.load(f)

legend = []
plotString = "("
count = 0
if data["plotType"] == "hist":
    plotString+="""data["data"]"""
    if "bins" in data:
        plotString+=""", data["bins"]"""
elif data["plotType"] == "plot":
    while True:
        if "xdata_{}".format(count) in data:
            if "legend_{}".format(count) in data:
                p = plt.plot(data["xdata_{}".format(count)], rooling(data["ydata_{}".format(count)],0.15), label=data["legend_{}".format(count)]+" - moving avg")
                plt.plot(data["xdata_{}".format(count)], data["ydata_{}".format(count)], label=data["legend_{}".format(count)], color=p[0].get_color(), alpha=.3)
                
                
            else:
                plt.plot(data["xdata_{}".format(count)], data["ydata_{}".format(count)])
            count += 1
        else:
            break
    if "xlabel" in data: plt.xlabel(data["xlabel"])
    if "ylabel" in data: plt.ylabel(data["ylabel"])
    plt.legend()#bbox_to_anchor=(1,0.5), loc="center left"
    #plt.legend()
    plt.title(data["titel"])
    plt.show()
elif data["plotType"] == "plot_surface":
    while True:
        if "xdata_{}".format(count) in data:
            if "legend_{}".format(count) in data:
                plt.plot(data["xdata_{}".format(count)], data["ydata_{}".format(count)], data["zdata_{}".format(count)], label=data["legend_{}".format(count)])
            else:
                plt.plot(data["xdata_{}".format(count)], data["ydata_{}".format(count)], data["zdata_{}".format(count)])
            count += 1
        else:
            break
    
    if "xlabel" in data: plt.xlabel(data["xlabel"])
    if "ylabel" in data: plt.ylabel(data["ylabel"])
    plt.legend()
    plt.title(data["titel"])
    plt.show()
else:
    while True:
        if "xdata_{}".format(count) in data:
            if count != 0:
                plotString+=", "
            plotString+="""data["xdata_{}"], data["ydata_{}"]""".format(count,count,count)
            if "legend_{}".format(count) in data: 
                legend.append(data["legend_{}".format(count)])
            count += 1
        else:
            break
        
if data["plotType"] != "plot" and data["plotType"] != "plot_surface":
    plotString += ")"
        
    print(plotString)
    plt.figure()
    exec("plt."+data["plotType"]+plotString)
    if "xlabel" in data: plt.xlabel(data["xlabel"])
    if "ylabel" in data: plt.ylabel(data["ylabel"])
    if len(legend): plt.legend(legend)
    plt.title(data["titel"])
    plt.show()