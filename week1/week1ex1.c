#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void calculateLimit();
void createArray(int n);
void createMatrix(int m, int n);
void createArray3D(int nx, int ny, int nz);

int main(int argc, char *argv[]){


  // First exercise:
  // calculateLimit();

  // Second exercise:
  // if (argc == 2) {
  //   createArray(atoi(argv[1]));
  // } else {
  //   printf("Give n as command line argument!\n");
  // }

  // Third exercise:
  // createMatrix(10000,10000);

  // Fourth exercise:
  createArray3D(10,10,10);

  return 0;
}


void calculateLimit(){
  /*Verifying that the limit of the infinite sum is equal to 4/5.*/

  double sum = 1;
  double sign = -1;
  for (int i = 1; i < 1000; i++) {
    sum += sign*1/(pow(2,i*2));
    sign *= -1;
  }

  printf("%f\n", sum);

}

void createArray(int n){
  /*Creating an array of random numbers, and finding the max and min.*/

  int *array = (int *)malloc(sizeof(int)*n);
  if (array==NULL) {
    printf("malloc failed\n");
    exit(1);
  }

  srand(time(0));

  int max = 0;
  int min = 1000;
  for (int i = 0; i < n; i++) {
    array[i] = rand() % 1000;
    if (array[i] > max)
    max = array[i];
    if (array[i] < min)
    min = array[i];
  }

  printf("Maximum: %d\n", max);
  printf("Minimum: %d\n", min);

  free(array);

}

void createMatrix(int m, int n){
  /*Checking whether it is faster to initialize a matrix iterating over the rows or columns first.*/

  int **matrix = (int**)malloc(sizeof(int*)*m);
  for (int i = 0; i < m; i++) {
    matrix[i] = (int*)malloc(sizeof(int)*n);
  }

  srand(time(0));

  clock_t begin = clock();
  for (int i=0; i<m; i++){
      for (int j=0; j<n; j++){
        matrix[i][j] = rand() % 100;
      }
  }
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time used (rows/columns): %f\n", time_spent);

  begin = clock();
  for (int i=0; i<m; i++){
      for (int j=0; j<n; j++){
        matrix[j][i] = rand() % 100;
      }
  }
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time used (columns/row): %f\n", time_spent);


  for (int i = 0; i < m; i++) {
    free(matrix[i]);
  }
  free(matrix);

}

void createArray3D(int nx, int ny, int nz){

  double *u_storage = (double*)malloc(nx*ny*nz*sizeof(double));
  double ***u = (double***)malloc(sizeof(double**)*nx);

  for(int i = 0; i < nx; i++){
    u[i] = (double**)malloc(ny*sizeof(double*));
    for(int j = 0; j < ny; j++){
      int idx = nx*j + nx*ny*i;
      u[i][j] = &(u_storage[idx]);
    }
  }

  for (int i=0; i<nx; i++){
    for (int j=0; j<ny; j++){
      for (int k = 0; k<nz; k++) {
        u[i][j][k] = i*ny*nz + j*nz + k;
      }
    }
  }

  free(u[0][0]);
  for (int i = 0; i < nx; i++) {
    free(u[i]);
  }
  free(u);
//  free(u_storage);

}
