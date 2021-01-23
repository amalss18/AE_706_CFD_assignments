#include<iostream>
#include<fstream>
#include<stdio.h>
#include<array>
#include<math.h>
#include<string>
#include<sstream>
#include<stdlib.h>

using namespace std;


array<float, 101> update_u(int scheme_no, array<float, 101> u, float mu){
    // Function containing schemes to update u
    array<float, 101> updated_u;

    switch (scheme_no)
    {
    // Scheme 1 : FTFS
    case 1:
        for (int i = 1; i < 100; i++)
            updated_u[i] = u[i] - mu * (u[i+1] - u[i]);
        break;

    // Scheme 2 : FTCS
    case 2:
        for (int i = 1; i < 100; i++)
            updated_u[i] = u[i] - 0.5 * mu * (u[i+1] - u[i-1]);
        break;

    // Scheme 3 : FTBS
    case 3:
        for (int i = 1; i < 100; i++)
            updated_u[i] = u[i] - mu * (u[i] - u[i-1]);
        break;

    // Scheme 4 : Lax-Wendroff
    case 4:
        for (int i = 1; i < 100; i++)
            updated_u[i] = u[i] - 0.5 * mu * (u[i+1] - u[i-1]) + 0.5 * mu * mu * (u[i+1] - 2 * u[i] + u[i-1]);
        break;

    // Scheme 5 : Beam-Warming
    case 5:
        for (int i = 2; i < 99; i++)
            updated_u[i] = u[i] - 0.5 * mu * (3*u[i] - 4*u[i-1] + u[i-2]) + 0.5 * mu * mu * (u[i] - 2*u[i-1] + u[i-2]);
        break;

    // Scheme 6 : Fromm
    case 6:
        for (int i = 1; i < 100; i++)
            updated_u[i] = 0.5 * ( u[i] - 0.5 * mu * (u[i+1] - u[i-1]) + 0.5 * mu * mu * (u[i+1] - 2 * u[i] + u[i-1]) + \
                                   u[i] - 0.5 * mu * (3*u[i] - 4*u[i-1] + u[i-2]) + 0.5 * mu * mu * (u[i] - 2*u[i-1] + u[i-2]));
        break;

    }

    updated_u[0] = updated_u[1];
    updated_u[100] = updated_u[99];
    return updated_u;
}


array<float, 101> initial_condition(int no, array<float, 101> x){
    // Function which returns initial condition
    array<float, 101> u;
    switch (no)
    {
    // Initial Condition 1: Step function
    case 1:
        for (int i = 0; i <= 100; i++){
            if (x[i] <= 0.2) u[i] = 1.0;
            else u[i] = 0.0;
        }
        break;

    // Initial Condition 2: 2 periods
    case 2:
        for (int i = 0; i <= 100; i++){
            if (x[i] >= 0.05 && x[i] <= 0.35)
                u[i] = sin(4 * M_PI * (x[i] - 0.05) / 0.3);
            else
                u[i] = 0.0;
        }
        break;

    // Initial Condition 3: 4 periods
    case 3:
        for (int i = 0; i <= 100; i++){
            if (x[i] >= 0.05 && x[i] <= 0.35)
                u[i] = sin(8 * M_PI * (x[i] - 0.05) / 0.3);
            else
                u[i] = 0.0;
        }
        break;

    // Initial Condition 4: 6 periods
    case 4:
        for (int i = 0; i <= 100; i++){
            if (x[i] >= 0.05 && x[i] <= 0.35)
                u[i] = sin(12 * M_PI * (x[i] - 0.05) / 0.3);
            else
                u[i] = 0.0;
        }
        break;

    // Initial Condition 5: Gaussian
    case 5:
        for (int i = 0; i <= 100; i++){
            u[i] = exp(-50.0 * (x[i] - 0.2) * (x[i] - 0.2) / (0.4 * 0.4));
        }
        break;
    }

    return u;
}


void run_simulation(int scheme_no, int ic_no, float mu){
    // Function to generate .csv file of end solution
    array<float, 101> x, u;

    for (float i = 0; i <= 100; i++)
        x[i] = i/100;

    u = initial_condition(ic_no, x);

    // generating the file name of the .csv file
    string file_name = "data/scheme", fic = "-IC", fmu = "-mu", ext = ".csv";
    stringstream sno, icno, muno;
    sno << scheme_no;
    icno << ic_no;
    muno << mu;
    if (mu == 1.0)
        file_name = file_name + sno.str() + fic + icno.str() + fmu + string("1.0") + ext;
    else
        file_name = file_name + sno.str() + fic + icno.str() + fmu + muno.str() + ext;

    ofstream myfile;
    myfile.open (file_name);

    // writing initial condition to file
    for (int i = 0; i < 101; i++)
    {
        if (i < 100)
            myfile << u[i] <<",";
        else
            myfile << u[i] <<"\n";
    }

    // Running simulation for 40 timesteps
    for (int t = 0; t < 40; t++)
        u = update_u(scheme_no, u, mu);

    // Writing final solution to file
    for (int i = 0; i < 101; i++)
    {
        if (i < 100)
            myfile << u[i] <<",";
        else
            myfile << u[i];
    }
    myfile.close();
}


int main(int argc, char** argv){
    int scheme_no = atoi(argv[1]);

    // all combinations of initial conditions and schemes.
    if (scheme_no == 0){
        for (int i=1; i<=6; i++){
            for (int j=1; j<=5; j++){
                run_simulation(i, j, 0.5);
                run_simulation(i, j, 1.0);
                run_simulation(i, j, 1.5);
            }
        }
    }

    else{
        int icno = atoi(argv[2]);
        float mu = atof(argv[3]);
        run_simulation(scheme_no, icno, mu);
    }
}