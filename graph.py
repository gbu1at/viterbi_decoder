import sys
import os
import numpy as np
import matplotlib.pyplot as plt


os.system("make clean")
os.system("make")


X = np.linspace(0, 1, 100)
y = []

for x in X:
    os.system(f"./main {x} input.txt")
    diff = float(open("input.txt").read())
    y.append(diff)

os.system("rm -f input.txt")
os.system("make clean")
plt.plot(X, y)
plt.title("Вероятность ошибки на бит на выходе декодера от веролятности ошибки в канале");
plt.xlabel("вероятность ошибки в канале")
plt.ylabel("вероятность ошибки на выходе декодера")
plt.savefig("graph.png")
plt.show()

