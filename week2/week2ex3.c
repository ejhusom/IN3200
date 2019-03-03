/* Program by Erik Johannes Husom, 21.01.2019.
IN3200, UiO, week 2, exercise 3 and 4.
This program allocates two 3D arrays, initializes all values of the first, and calculates the values of the second array from the the first. */

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

void get_walltime_(double* wcTime) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}

void get_walltime(double* wcTime){
    get_walltime_(wcTime);
}



int main(int argc, char const *argv[]){

    size_t nx=10, ny=10, nz=10;

    double *v_storage = (double*)malloc(nx*ny*nz*sizeof(double));
    double *u_storage = (double*)malloc(nx*ny*nz*sizeof(double));
    double ***v = (double***)malloc(sizeof(double**)*nx);
    double ***u = (double***)malloc(sizeof(double**)*nx);

    for(size_t i = 0; i < nx; i++){
        v[i] = (double**)malloc(ny*sizeof(double*));
        u[i] = (double**)malloc(ny*sizeof(double*));
        for(size_t j = 0; j < ny; j++){
            int idx = nx*j + nx*ny*i;
            v[i][j] = &(v_storage[idx]);
            u[i][j] = &(u_storage[idx]);
        }
    }

    for (size_t i=0; i<nx; i++){
        for (size_t j=0; j<ny; j++){
            for (size_t k = 0; k<nz; k++) {
                v[i][j][k] = 2.0 + sin(i*j*k*M_PI/((nx-1)*(ny-1)*(nz-1)));
                u[i][j][k] = 0.0;
            }
        }
    }

    
    
    double start, end;
    get_walltime(&start);

    for (size_t i=1; i<nx-1; i++){
        for (size_t j=1; j<ny-1; j++){
            for (size_t k=1; k<nz-1; k++){
                u[i][j][k] = v[i][j][k] + (v[i-1][j][k] + v[i][j-1][k] + v[i][j][k-1] - 6*v[i][j][k] + v[i+1][j][k] + v[i][j+1][k] + v[i][j][k+1])/6;
                memcpy(v_storage,u_storage,nx*ny*nz);            
            }
        }
    }

    get_walltime(&end);
    printf("Time used by function: %f\n", (float)(end-start));
    double flops = 9*(nz-2)*(ny-2)*(nx-2);
    printf("Number of FLOPs: %f\n", flops);
    printf("FLOPs per second: %.2e\n", flops/(float)(end-start));

//    for (size_t i=0; i<nx; i++){
//        for (size_t j=0; j<ny; j++){
//            for (size_t k = 0; k<nz; k++) {
//                printf("%f     ", v[i][j][k]);
//                printf("%f\n", u[i][j][k]);
//            }
//        }
//    }


    free(v[0][0]);
    free(u[0][0]);
    for (size_t i = 0; i < nx; i++) {
        free(v[i]);
        free(u[i]);
    }
    free(v);
    free(u);

    return 0;
}

