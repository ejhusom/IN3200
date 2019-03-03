#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

double numerical_integration (double x_min, double x_max, int slices){
    double delta_x = (x_max-x_min)/slices;
    double x, sum = 0.0;
    for (int i=0; i<slices; i++) {
        x = x_min + (i+0.5)*delta_x;
        sum = sum + 4.0/(1.0+x*x);
    }
    return sum*delta_x;
}

double powNew(double x){
    double result = x;
    for(size_t i=0; i<99; i++){
        result *= x;
    }
    return result;
}

void get_walltime_(double* wcTime) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}

void get_walltime(double* wcTime){
    get_walltime_(wcTime);
}

int main(int argc, char const *argv[]){

    // Exercise 1
    double x_min = 0;
    double x_max = 1;
    for ( size_t i=1; i<1000001; i *= 10){
        printf("%f\n", numerical_integration(x_min, x_max, i));
    }

    // Exercise 3
    double x = 200.0;
    double start, end;
  
    get_walltime(&start);
    printf("%f\n", pow(x,100));
    get_walltime(&end);
    printf("Time used by library function: %f\n", (float)(end-start));

    get_walltime(&start);
    printf("%f\n", powNew(x));
    get_walltime(&end);
    printf("Time used by manual function: %f\n", (float)(end-start));



    return 0;
}
