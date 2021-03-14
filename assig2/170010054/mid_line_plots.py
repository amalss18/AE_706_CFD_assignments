import numpy as np
import matplotlib.pyplot as plt
import sys
import csv

def get_exact_solution(x, y):
    max_int = 50
    sum = 0
    H = 2
    L = 1
    for n in range(1, max_int):
        term1 = (1 - (-1)**n) / (n * np.pi)
        term2 = np.sinh(n * np.pi * (H -y ) / L) * np.sin(n* np.pi * x / L) / (np.sinh(n * np.pi * H / L))
        sum += 500 * term1 * term2

    return sum


def generate_mid_x_plot(method):
    if method == 1:
        file_name = "x_mid_jacobi.csv"
        title = "Point Jacobi, y = 1.0"
    if method == 2:
        file_name = "x_mid_gauss_seidel.csv"
        title = "Point Gauss Seidel, y = 1.0"
    if method == 3:
        file_name = "x_mid_SOR.csv"
        title = "Point SOR, y = 1.0"


    T = []
    x = np.linspace(0, 1, 41)
    y = np.ones_like(x) * 1.0

    with open(file_name) as file:
        reader = csv.reader(file, delimiter=",")
        for row in reader:
            T.append(float(row[0]))

    soln = get_exact_solution(x, y)
    plt.scatter(x, T, label="computed", color='red')
    plt.plot(x, soln, label="exact solution")
    plt.title(title)
    plt.xlabel('x')
    plt.ylabel('T')
    plt.legend()
    plt.savefig("plots/"+title+".png")
    plt.show()


def generate_mid_y_plot(method):
    if method == 1:
        file_name = "y_mid_jacobi.csv"
        title = "Point jacobi, x = 0.5"
    if method == 2:
        file_name = "y_mid_gauss_seidel.csv"
        title = "Point Gauss seidel, x = 0.5"
    if method == 3:
        file_name = "y_mid_SOR.csv"
        title = "Point SOR, x = 0.5"

    T = []
    y = np.linspace(0, 2, 81)
    x = np.ones_like(y) * 0.5


    with open(file_name) as file:
        reader = csv.reader(file, delimiter=",")
        for row in reader:
            T.append(float(row[0]))

    soln = get_exact_solution(x, y)
    plt.scatter(y, T, label="computed", color='red')
    plt.plot(y, soln, label="exact solution")
    plt.legend()
    plt.title(title)
    plt.xlabel('y')
    plt.ylabel('T')
    plt.savefig("plots/"+title+".png")
    plt.show()


if __name__=='__main__':
    method = float(sys.argv[1])
    if method == 0:
        generate_mid_x_plot(1)
        generate_mid_y_plot(1)
        generate_mid_x_plot(2)
        generate_mid_y_plot(2)
        generate_mid_x_plot(3)
        generate_mid_y_plot(3)

    else:
        generate_mid_x_plot(method)
        generate_mid_y_plot(method)

