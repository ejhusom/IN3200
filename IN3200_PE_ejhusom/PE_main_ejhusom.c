#include <PE_functions_ejhusom.h>

int main(int nargs, const char *argc[]){

    double *val;
    int *col_idx;
    int *row_ptr;
    int *arr = malloc(100 * sizeof *arr);

    read_graph_from_file("page_data.data", *arr);

    return 0;
}
