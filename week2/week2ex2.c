/* By Erik Johannes Husom, 21.01.2019, IN3200, UiO.
This program compares a hand-coded copy operation of an array with the standard memcpy function. The results shows that the standard function clearly is superior.*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

void get_walltime_(double* wcTime) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}

void get_walltime(double* wcTime){
    get_walltime_(wcTime);
}

void memcpyFunc(double *b, double *a, size_t n){
    for (size_t i=0; i<n; i++) b[i]=a[i];
}

int main(int argc, char const *argv[]){
 
    size_t n = 100000;
    double *a = (double*)malloc(sizeof(double)*n);  
          
    double *b = (double*)malloc(sizeof(double)*n);
    double *c = (double*)malloc(sizeof(double)*n);

    for (size_t i=0; i<n; i++) a[i]=i;
    
    double start, end;
    get_walltime(&start);
    memcpyFunc(b, a, n);
    get_walltime(&end);
    printf("Time used by manual function: %f\n", (float)(end-start));

    get_walltime(&start); 
    memcpy(c, a, n); 
    get_walltime(&end);
    printf("Time used by standard function: %f\n", (float)(end-start));

    free(a);
    free(b);
    free(c);
              
        
    return 0;
}
      
