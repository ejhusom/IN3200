#include "PE_functions_ejhusom.h"

void read_graph_from_file(char *filename, int *from_node_id, int *to_node_id, double *val, int *col_idx, int *row_ptr){
    /* This function reads web graph from a text file, and sets up the hyperlink matrix in CRS format. */

    // READ FILE -----------------------------------------------------
    FILE *infile = fopen(filename,"r");

    if(infile==NULL){
        printf("File not found.\n");
        exit(0);
    }
    int node_count;
    int edge_count;
    for(int i=0; i<2; i++) fscanf(infile, "%*[^\n]\n"); // skip the first lines.
    fscanf(infile, "%*s %*s %d %*s %d ", &node_count, &edge_count); // read number of nodes and edges.
    fscanf(infile, "%*[^\n]\n"); // skip another line

    from_node_id = malloc(edge_count*sizeof*from_node_id);
    to_node_id = malloc(edge_count*sizeof*to_node_id);
    val = malloc(edge_count*sizeof*val);
    col_idx = malloc(edge_count*sizeof*col_idx);
    row_ptr = malloc(node_count*sizeof*row_ptr);

    for(int edge=0; edge<edge_count; edge++){
        fscanf(infile, "%d %d", &from_node_id[edge], &to_node_id[edge]);
    } 

    printf("File '%s' read successfully!\n", filename);
// Print out webgraph
//    printf("Nodes: %d, edge_count: %d\n", node_count, edge_count);
//    for(int i=0; i<edge_count; i++){
//        printf("%d   %d\n", from_node_id[i], to_node_id[i]);
//    }

    // Finding L(j) -----------------------------------------------------------------
    int *perm = malloc(edge_count*sizeof*perm);
    for (size_t i = 0; i < edge_count; i++) {
        perm[i] = i;
    }
    sort(from_node_id, 0, edge_count, perm); // sorting to find L(j) 

    int *L = malloc(node_count*sizeof*L);
    int edge = 0;
    for(int node=0; node<node_count; node++){
        while(from_node_id[perm[edge]]==node){
            L[node]++;
            edge++;
        }
    }
    // Print L(j)
//    for(int node=0; node<node_count; node++){
//        printf("%d\n", L[node]);
//    }

    // Sorting arrays --------------------------------------------------------------
    sort(to_node_id, 0, edge_count, perm);

    int start = 0;
    int end = 0;
    edge = 0;
    for(int node=0; node<node_count; node++){
        row_ptr[node] = start;
        while(to_node_id[perm[edge]]==node){
            end++;
            edge++;
        }
        sort(from_node_id, start, end, perm);
        start = end;
    }
    printf("Sorting done!\n");

    // Printing sorted array 
//    printf("========\n");
//    for (size_t i = 0; i < 17; i++) {
//        printf("%d  %d\n", from_node_id[perm[i]], to_node_id[perm[i]]);
//    }

    // Setting up hyperlink matrix in CRS format ----------------------------------
    for(int edge=0; edge<edge_count; edge++){
        col_idx[edge] = from_node_id[perm[edge]];
        val[edge] = 1.0/(double)L[col_idx[edge]];
    }    

    // Printing hyperlink matrix
//    printf("========\n");
//    for (size_t i = 0; i < 17; i++) {
//        printf("%f  %d\n", val[i], col_idx[i]);
//    }
//    printf("========\n");
//    for (size_t i = 0; i < 8; i++) {
//        printf("%d\n", row_ptr[i]);
//    }

    free(L);
    free(perm);

}

void PageRank_iterations(double damping, double threshold){

}

void top_n_webpages(int n){
    /* This function lists the top n webpages with their score. */
    int page_idx = 0;
    double score = 1.0;

    printf("Rank  Page index    Score");
    for (int i=1; i<n+1; i++){
        printf("%d   %d    %f", i, page_idx, score);
    }
}

void swap(int *a, int *b){
  int t=*a; *a=*b; *b=t;
}

void sort(int arr[], int beg, int end, int perm[]){
  if (end > beg + 1) {
    int piv = arr[perm[beg]], l = beg + 1, r = end;
    while (l < r) {
      if (arr[perm[l]] <= piv)
        l++;
      else
        swap(&perm[l], &perm[--r]);
    }
    swap(&perm[--l], &perm[beg]);
    sort(arr, beg, l, perm);
    sort(arr, r, end, perm);
  }
}

