#include <stdio.h>
#include <time.h>

int main(int argc, const char *argv[]){


    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    int a = 1;
    int b = 0;
    for(int i=0; i<1000000000; i++) b += a*i;
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;


    FILE *outfile = fopen("timing.txt", "a");
    fprintf(outfile, "%f\n", time_spent);
    fclose(outfile);

    printf("Time used: %f\n", time_spent);
    printf("Program done!\n");

    return 0;
}
