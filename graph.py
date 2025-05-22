import sys
import os
import numpy as np
import matplotlib.pyplot as plt


os.system("make clean")
os.system("make")


X = np.linspace(0, 0.2, 100)
y = []

for x in X:
    os.system(f"./main {x} input.txt")
    diff = float(open("input.txt").read())
    y.append(diff)

os.system("rm -f input.txt")
os.system("make clean")
plt.plot(X, y)
plt.savefig("graph.png")
plt.show()

