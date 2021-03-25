import numpy as np
import matplotlib.pyplot as plt
import csv
import sys

def u_plots():
    # file_name = "FTCS.csv"
    file_name = "crank.csv"


    u = []


    with open(file_name) as file:
        reader = csv.reader(file, delimiter=",")
        for row in reader:
            print(row)

            # print(row[::-1])
            # u.append([float(point) for point in row[1::-1]])
            for point in row[:-1]:
                u.append(float(point))

    print(len(u))
    x = np.linspace(0, 0.04, len(u))
    # print(u)

    plt.plot(np.array(u[0])/40, x/0.04)
    plt.plot(np.array(u[1])/40, x/0.04)
    plt.plot(np.array(u[2])/40, x/0.04)

    plt.xlabel("Velocity")
    plt.ylabel("y")
    plt.show()

if __name__=='__main__':
    u_plots()