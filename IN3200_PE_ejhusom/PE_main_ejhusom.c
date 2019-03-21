#include "PE_functions_ejhusom.h"
#include <time.h>

int main(int argc, char *argv[]){

    int node_count = 0;
    char *filename;
    int n = 8;
    int *D = NULL;
    // Hyperlink matrix in CRS format:
    double *val = NULL;
    int *col_idx = NULL;
    int *row_ptr = NULL;
    // PageRank algorithm:
    double damping = 1.00;
    double threshold = 1e-3;
    int dangling_count = 0; 

    switch (argc) {
        case 5: 
            n = atoi(argv[4]);
        case 4: 
            threshold = atof(argv[3]);
        case 3: 
            damping = atof(argv[2]);
        case 2: 
            filename = argv[1];
            break;
        case 1: 
            printf("Give the following command line arguments:\n");
            printf("1: File name.\n");
            printf("Optional arguments:\n");
            printf("2: Damping constant.\n");
            printf("3: Convergence threshold.\n");
            printf("4: Number of top webpages you want to show.\n");
            return 0;
    }

    struct timespec start_total, end_total;
	clock_gettime(CLOCK_REALTIME, &start_total);

    struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
    node_count = read_graph_from_file(filename, &val, &col_idx, &row_ptr, &D, &dangling_count);
    clock_gettime(CLOCK_REALTIME, &end);
	double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Time elapsed for read_graph_from_file() is %f seconds.\n\n", time_spent);


	clock_gettime(CLOCK_REALTIME, &start);
    double *x = malloc(node_count*sizeof*x);
    double *x_new = malloc(node_count*sizeof*x_new);
    PageRank_iterations(&val, &col_idx, &row_ptr, &x, &x_new, node_count, damping, threshold, &D, &dangling_count);
    clock_gettime(CLOCK_REALTIME, &end);
	time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Time elapsed for PageRank_iterations() is %f seconds.\n\n", time_spent);

	clock_gettime(CLOCK_REALTIME, &start);
    top_n_webpages(&x, n, node_count);
    clock_gettime(CLOCK_REALTIME, &end);
	time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time elapsed for top_n_webpages() is %f seconds.\n\n", time_spent);

    clock_gettime(CLOCK_REALTIME, &end_total);
	double time_spent_total = (end_total.tv_sec - start_total.tv_sec) + (end_total.tv_nsec - start_total.tv_nsec) / 1000000000.0;
	printf("Time elapsed in total is %f seconds.\n\n", time_spent_total);

    free(D);
    free(val);
    free(col_idx);
    free(row_ptr);
    free(x);
    free(x_new);


    return 0;
}
