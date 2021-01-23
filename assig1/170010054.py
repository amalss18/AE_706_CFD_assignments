import numpy as np
import matplotlib.pyplot as plt
import csv
import sys

def generate_plots(x, schemes, in_conds, mu_values):
    for scheme_key in schemes:
        for ickey in in_conds:
            for mu in mu_values:
                file_name = 'data/scheme' + str(scheme_key) + '-IC' + str(ickey) + '-mu' + str(mu)  + '.csv'
                if mu == 0.5:
                    s_mu = '0_5'
                elif mu == 1.0:
                    s_mu = '1_0'
                else:
                    s_mu = '1_5'

                img_name = 'plots/scheme' + str(scheme_key) + '-IC' + str(ickey) + '-mu' + s_mu  + '.png'
                u_final = []
                u_initial = []
                line_count = 0
                with open(file_name) as file:
                    reader = csv.reader(file, delimiter=",")
                    for row in reader:
                        if line_count == 0:
                            for i in range(len(row)):
                                u_initial.append(float(row[i]))
                        else:
                            for i in range(len(row)):
                                u_final.append(float(row[i]))
                        line_count += 1

                plt.plot(x, u_initial, '--', label='Initial Condition')
                plt.plot(x, u_final, label='40 timesteps')
                title = "Scheme - " + schemes[scheme_key] + ", mu = " + str(mu)
                plt.title(title)
                plt.ylim(-1.5, 1.5)
                plt.legend()
                plt.savefig(img_name)
                plt.clf()


def get_plots(file_name = None):
    x = np.linspace(0, 1, 101)

    in_conds = {1:'step', 2:'two periods', 3:'4 periods', 4:'6 periods', 5:'Gaussian'}
    schemes = {1:'FTFS', 2:'FTCS', 3:'FTBS', 4:'Lax-Wendroff', 5:'Beam-Warming', 6:'Fromm'}
    mu_values = [0.5, 1.0, 1.5]

    if file_name is not None:
        schemes = {int(file_name[6]): schemes[int(file_name[6])]}
        in_conds = {int(file_name[10]): in_conds[int(file_name[10])]}
        if file_name[14:17] == '0.5':
            mu_values = [0.5]
        elif file_name[14:17] == '1.0':
            mu_values = [1.0]
        else:
            mu_values = [1.5]

    generate_plots(x, schemes, in_conds, mu_values)


if __name__=="__main__":
    if len(sys.argv) == 1:
        get_plots()
    else:
        get_plots(sys.argv[1])