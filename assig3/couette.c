#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define N 61

void print_u(double u[N]){
    for (int i=0; i<N; i++){
            printf("%f ", u[i]);
            printf(" ");
        }
        printf("\n");
}


void setup_bcs(double u[N], double U0){
    // Function to setup up boundary conditions

    u[0] = U0;

    u[N-1] = 0;
}

void setup_ic(double u[N]){
    // Initializing all points except boundary to 0 initially.

    for (int i=1; i<N-1; i++){
            u[i] = 0;
    }
}

void FTCS(double u[N], double u_updated[N], double dx, double dt, double mu){
    double a = mu * dt / pow(dx, 2);

    for (int i=1; i<N-1; i++){
        u_updated[i] = u[i] + a * (u[i+1] - 2*u[i] + u[i-1]);
    }

}

void solve_tridiagonal_in_place_destructive(float * restrict const x, const size_t X, const float * restrict const a, const float * restrict const b, float * restrict const c) {
    /*
     solves Ax = v where A is a tridiagonal matrix consisting of vectors a, b, c
     x - initially contains the input vector v, and returns the solution x. indexed from 0 to X - 1 inclusive
     X - number of equations (length of vector x)
     a - subdiagonal (means it is the diagonal below the main diagonal), indexed from 1 to X - 1 inclusive
     b - the main diagonal, indexed from 0 to X - 1 inclusive
     c - superdiagonal (means it is the diagonal above the main diagonal), indexed from 0 to X - 2 inclusive

     Note: contents of input vector c will be modified, making this a one-time-use function (scratch space can be allocated instead for this purpose to make it reusable)
     Note 2: We don't check for diagonal dominance, etc.; this is not guaranteed stable
     */

    c[0] = c[0] / b[0];
    x[0] = x[0] / b[0];

    /* loop from 1 to X - 1 inclusive, performing the forward sweep */
    for (size_t ix = 1; ix < X; ix++) {
        const float m = 1.0f / (b[ix] - a[ix] * c[ix - 1]);
        c[ix] = c[ix] * m;
        x[ix] = (x[ix] - a[ix] * x[ix - 1]) * m;
    }

    /* loop from X - 2 to 0 inclusive (safely testing loop condition for an unsigned integer), to perform the back substitution */
    for (size_t ix = X - 2; ix > 0; ix--)
        x[ix] -= c[ix] * x[ix + 1];
    x[0] -= c[0] * x[1];
}

void CrankNicolson(double u[N], double u_updated[N], double dx, double dt, double mu){
    double r = mu * dt / (2 * pow(dx, 2));
    // printf("%f \n", r);
    float a[N-2], b[N-2], c[N-2];

    for (int i=0; i<N-2; i++){
        a[i] = -r;
        b[i] = 1 + 2 * r;
        c[i] = -r;
    }

    float B[N-2];
    for (int i=0; i<N-2;i++){
            B[i] = r * u[i+2] + (1-2*r) * u[i+1] + r * u[i];
        }


    solve_tridiagonal_in_place_destructive(B, N-2, a, b, c);
    // for (int i=0; i<N-2; i++){
    //     printf("%f, %f \n", B[i], u[i]);
    // }

    for (int i=1; i<N-1; i++){
        u_updated[i] = B[i-1];
    }

}


double compute_error(double u[N], double updated_u[N]){
    // Function to compute error between successive iterations

    double error = 0.0;

    for (int i=1; i<N-1; i++){
            error = error + fabs(updated_u[i] - u[i]);
        }
}


int main(int argc, char** argv){

    FILE *fptr;

    double U0 = 40.0, h = 0.04, mu = 0.000217;

    double dx = h/(N-1);

    double dt = 0.45 * dx * dx / mu;
    // double dt = 1.0;

    printf("%f", dt);

    double error = 10000;

    double u[N], u_new[N];

    setup_bcs(u, U0);
    setup_ic(u);


    fptr = fopen("crank.csv","w");
    // fptr = fopen("FTCS.csv","w");

    int k = 0;
    double time = 0.0;

    while (time <= 1.5){
        // printf("%f", time);
        time+= dt;
        k++;
        // FTCS(u, u_new, dx, dt, mu);
        CrankNicolson(u, u_new, dx, dt, mu);

        error = compute_error(u, u_new);

        for(int i=1; i<N-1; i++){
            u[i] = u_new[i];
        }

        if (time-dt < 0.15 && time + dt > 0.15){
            for(int i=0; i<N; i++){
                fprintf(fptr, "%f,", u[i]);
            }
            fprintf(fptr, "\n");
            printf("1");
        }

        if (time-dt*0.7 < 0.8 && time + dt*0.7 > 0.8){
            for(int i=0; i<N; i++){
                fprintf(fptr, "%f,", u[i]);
            }
            fprintf(fptr, "\n");
            printf("");

        }

        if (time-dt*0.5 < 1.5 && time + dt*0.5 > 1.5){
            for(int i=0; i<N; i++){
                fprintf(fptr, "%f,", u[i]);
            }
            fprintf(fptr, "\n");
            printf("3");

        }


        // printf("%d, %f \n", k, error);
        // if (k == 2 || k == 1)
        //     print_u(u);
            // break;
    }

}
