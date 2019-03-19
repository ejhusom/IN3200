#include "PE_functions_ejhusom.h"

int main(int argc, char *argv[]){

    int node_count;
    char *filename;
    int n = 3;
    int *D = NULL;
    // Hyperlink matrix in CRS format:
    double *val = NULL;
    int *col_idx = NULL;
    int *row_ptr = NULL;
    // PageRank algorithm:
    double damping = 0.85;
    double threshold = 0.1;
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

    node_count = read_graph_from_file(filename, &val, &col_idx, &row_ptr, &D, &dangling_count);

    double *x = malloc(node_count*sizeof*x);
    double *x_new = malloc(node_count*sizeof*x_new);

    PageRank_iterations(&val, &col_idx, &row_ptr, &x, &x_new, node_count, damping, threshold, &D, &dangling_count);

    free(D);
    free(val);
    free(col_idx);
    free(row_ptr);
    free(x);
    free(x_new);

    return 0;
}
