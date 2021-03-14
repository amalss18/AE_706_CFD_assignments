#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define IM 81 /* Number of rows */
#define JM 41 /* Number of columns */

void print_T(double phi[][JM]){
    for (int i=0; i<IM; i++){
        for (int j=0; j<JM; j++){
            printf("%f", phi[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void setup_bcs(double phi[][JM]){
    // Function to setup up boundary conditions

    // Bottom and top boundaries
    for (int j=0; j<JM; j++){
        phi[IM-1][j] = 250;
        phi[0][j] = 0;
    }

    // Left and Right boundaries
    for (int i=0; i<IM; i++){
        phi[i][0] = 0;
        phi[i][JM-1] = 0;
    }

}

void setup_ic(double phi[][JM]){
    // Initializing all points to 0 initially.

    for (int i=1; i<IM-1; i++){
        for (int j=1; j<JM-1; j++){
            phi[i][j] = 0;
        }
    }
}

void update_point_jacobi(double phi[][JM], double updated_phi[][JM], double beta){
    // Point Jacobi method
    double factor = 1 / (2 * (1 + beta * beta));

    for (int i=IM-2; i>=1; i--){
        for (int j=1; j<JM-1; j++){
            updated_phi[i][j] = factor * (phi[i+1][j] + phi[i-1][j] + \
                                beta * beta * phi[i][j+1] + beta * beta *phi[i][j-1]);
        }
    }
}

void update_point_gauss_seidel(double phi[][JM], double updated_phi[][JM], double beta){
    // Point gauss Seidel method
    double factor = 1 / (2 * (1 + beta * beta));

    for (int i=IM-2; i>=1; i--){
        for (int j=1; j<JM-1; j++){
            updated_phi[i][j] = factor * (phi[i-1][j] + updated_phi[i+1][j] + \
                                          beta * beta * phi[i][j+1] + beta * beta *updated_phi[i][j-1]);
        }
    }
}

double get_omega(double beta){
    // Function to obtain optimum omega for SOR
    double a = (cos(M_PI/(IM-1)) + (beta * beta * cos(M_PI/(JM-1)) ) ) / (1 + (beta * beta));
    a = pow(a, 2);

    double omega_opt = (2 - (2 * sqrt(1 - a)) ) / a;
    return omega_opt;
}


void update_point_SOR(double phi[][JM], double updated_phi[][JM], double beta){
    // Point Successive over relaxation method
    double factor = 1 / (2 * (1 + beta * beta));
    double omega;

    omega = get_omega(beta);

    for (int i=IM-2; i>=1; i--){
        for (int j=1; j<JM-1; j++){
            double term1 = (1 - omega) * phi[i][j];
            double term2 = omega * factor * (phi[i-1][j] + updated_phi[i+1][j] + \
                                             beta * beta * phi[i][j+1] + beta * beta *updated_phi[i][j-1]);

            updated_phi[i][j] = term1 + term2;
        }
    }
}




double calc_error(double phi[][JM], double updated_phi[][JM]){
    // Function to compute error between successive iterations

    double error = 0.0;

    for (int i=IM-2; i>=1; i--){
        for (int j=1; j<JM-1; j++){
            error = error + fabs(updated_phi[i][j] - phi[i][j]);
        }
    }


}

int main(int argc, char** argv){
    /* Determining the solution method to use */
    int method = atoi(argv[1]);

    /* Files to store data */
    FILE *fptr, *xptr, *yptr, *final_ptr;

    double Lx, Ly, dx, dy, beta;
    Lx = 1;
    Ly = 2;

    dx = Lx / (JM-1);
    dy = Ly / (IM-1);

    beta = dx / dy;

    double T[IM][JM], updated_T[IM][JM]; /* Array to store current and updated temperature */
    setup_bcs(T); /* Setting up the boundary conditions */
    setup_ic(T); /* Setting up the initial condition to being iteration */

    for (int i=0; i<IM; i++){
        for (int j=0; j<JM; j++){
                updated_T[i][j] = T[i][j];
        }
    }

    /* Generating files to store the data*/
    switch (method)
        {
        case 1:
                fptr = fopen("error_jacobi.csv","w");
                xptr = fopen("x_mid_jacobi.csv","w");
                yptr = fopen("y_mid_jacobi.csv","w");
                final_ptr = fopen("converged_jacobi.csv","w");

            break;

        case 2:
                fptr = fopen("error_gauss_seidel.csv","w");
                xptr = fopen("x_mid_gauss_seidel.csv","w");
                yptr = fopen("y_mid_gauss_seidel.csv","w");
                final_ptr = fopen("converged_gauss_seidel.csv","w");

            break;

        case 3:
                fptr = fopen("error_SOR.csv","w");
                xptr = fopen("x_mid_SOR.csv","w");
                yptr = fopen("y_mid_SOR.csv","w");
                final_ptr = fopen("converged_SOR.csv","w");

            break;
        }


    double error = 1000;

    int itr = 0;

    while(error > pow(10, -3)){ /* convergence criteria */
        itr++;

        /* updating temperature */
        switch (method)
        {
        case 1:
            update_point_jacobi(T, updated_T, beta);
            break;

        case 2:
            update_point_gauss_seidel(T, updated_T, beta);
            break;

        case 3:
            update_point_SOR(T, updated_T, beta);
            break;
        }

        error = calc_error(T, updated_T); /* error calculation */

       fprintf(fptr,"%f, %d \n", log(error), itr);

        for (int i=IM-2; i>=1; i--){
            for (int j=1; j<JM-1; j++){
                T[i][j] = updated_T[i][j];
            }
        }
    }

    int x_mid = IM * 0.5;
    int y_mid = JM * 0.5;

    /* Storing data at x = 0.5 */
    for (int j=0; j<JM; j++){
       fprintf(xptr,"%f \n", T[x_mid][j]);
    }

    /* Storing data at y= 1.0 */
    for (int i=IM-1; i>=0; i--){
       fprintf(yptr,"%f \n", T[i][y_mid]);
    }

    /*Storing final converged data*/
    fprintf(final_ptr,"x coord, y coord, z coord, T\n");
    for (int i=IM-1; i>=0; i--){
        for (int j=0; j<JM; j++){
           fprintf(final_ptr,"%f, %f, %f, %f \n", dx*j, dy*((IM-1)-i), 0.0, T[i][j]);
        }
    }

    fclose(fptr);
    fclose(xptr);
    fclose(yptr);

    // printf("\n %d", itr);
    // printf("\n");
}