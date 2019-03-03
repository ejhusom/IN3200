#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void writeASCII(double *arr, size_t n);
void writeBin(double *arr);
void readASCII(double *arr);
void readBin(double *arr);

int main(int argc, char const *argv[]) {

    size_t n = 10;

    double *arr = (double*)malloc(sizeof(double)*n);

    for(size_t i=0; i<n; i++){
        arr[i] = i;
    }

    clock_t begin = clock();
    writeASCII(arr, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time used for writing ASCII: %f\n", time_spent);

    begin = clock();
    writeBin(arr);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time used for writing binary: %f\n", time_spent);

    begin = clock();
    readASCII(arr);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time used for reading ASCII: %f\n", time_spent);

    begin = clock();
    readBin(arr);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time used for reading binary: %f\n", time_spent);

    free(arr);

    return 0;
}

void writeASCII(double *arr, size_t n){

    FILE *outfile;
    outfile = fopen("array.txt","w");
    for (size_t i=0; i<n; i++){
        fprintf(outfile, "%f\n", arr[i]);
    }
    fclose(outfile);
}

void writeBin(double *arr){

    FILE *outfile;
    outfile = fopen("array.bin","wb");
    fwrite(arr, sizeof(double), sizeof(arr), outfile);
    fclose(outfile);
}

void readASCII(double *arr){
    double var;
    int i = 0;
    FILE *infile;
    infile = fopen("array.txt","r");
    while (fscanf(infile, "%lf\n", &var) == 1){
        arr[i] = var;
        i++;
    }
    fclose(infile);
}



void readBin(double *arr){
    FILE *infile;
    infile = fopen("array.bin","rb");
    fwrite(arr, sizeof(double), sizeof(arr), infile);
    fclose(infile);
}
