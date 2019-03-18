#include "PE_functions_ejhusom.h"

int main(int argc, char *argv[]){

    char *filename;
    if(argc > 1){
        filename = argv[1];
    } else {
        printf("Give file name as command line argument.\n");
        return 0;
    }

    int *from_node_id = NULL; 
    int *to_node_id = NULL;
    // Hyperlink matrix in CRS format:
    double *val = NULL;
    int *col_idx = NULL;
    int *row_ptr = NULL;

    read_graph_from_file(filename, from_node_id, to_node_id, val, col_idx, row_ptr);


    free(from_node_id);
    free(to_node_id);
    free(val);
    free(col_idx);
    free(row_ptr);

    return 0;
}
