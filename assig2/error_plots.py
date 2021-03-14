import numpy as np
import matplotlib.pyplot as plt
import sys
import csv


def generate_error_plot(method):
    if method == 1:
        file_name = "error_jacobi.csv"
        title = "Point Jacobi error"
    if method == 2:
        file_name = "error_gauss_seidel.csv"
        title = "Point Gauss Seidel error"
    if method == 3:
        file_name = "error_SOR.csv"
        title = "Point SOR error"


    error = []
    iteration_no = []

    with open(file_name) as file:
        reader = csv.reader(file, delimiter=",")
        for row in reader:
            error.append(float(row[0]))
            iteration_no.append(float(row[1]))

    plt.plot(iteration_no, error)
    plt.ylabel("log(Error)")
    plt.xlabel("Number of iterations")
    plt.title(title)
    plt.savefig("plots/"+title+".png")
    plt.show()


def generate_error_plots_all():
    file_name_1 = "error_jacobi.csv"
    file_name_2 = "error_gauss_seidel.csv"
    file_name_3 = "error_SOR.csv"

    title = "All Error plots"

    error_1, error_2, error_3 = [], [], []
    iteration_no_1, iteration_no_2, iteration_no_3 = [], [] ,[]

    with open(file_name_1) as file:
        reader = csv.reader(file, delimiter=",")
        for row in reader:
            error_1.append(float(row[0]))
            iteration_no_1.append(float(row[1]))

    with open(file_name_2) as file:
        reader = csv.reader(file, delimiter=",")
        for row in reader:
            error_2.append(float(row[0]))
            iteration_no_2.append(float(row[1]))

    with open(file_name_3) as file:
        reader = csv.reader(file, delimiter=",")
        for row in reader:
            error_3.append(float(row[0]))
            iteration_no_3.append(float(row[1]))

    plt.plot(iteration_no_1, error_1, label="Point Jacobi")
    plt.plot(iteration_no_2, error_2, label="Point Gauss Seidel")
    plt.plot(iteration_no_3, error_3, label="Point SOR")

    # plt.ylim(0, 50)
    plt.ylabel("log(Error)")
    plt.xlabel("Number of iterations")
    plt.legend()
    plt.title(title)
    plt.savefig("plots/"+title+".png")
    plt.show()



if __name__=='__main__':
    method = float(sys.argv[1])

    if method == 0:
        generate_error_plots_all()
    else:
        generate_error_plot(method)

