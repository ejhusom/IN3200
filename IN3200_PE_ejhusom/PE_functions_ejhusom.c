#include "PE_functions_ejhusom.h"

int read_graph_from_file(char *filename, double **val, int **col_idx, int **row_ptr, int **D, int *dangling_count){
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

    int *from_node_id = malloc(edge_count*sizeof*from_node_id);
    int *to_node_id = malloc(edge_count*sizeof*to_node_id);
    (*val) = malloc(edge_count*sizeof*(*val));
    (*col_idx) = malloc(edge_count*sizeof*(*col_idx));
    (*row_ptr) = malloc((node_count+1)*sizeof*(*row_ptr));
    int *L = malloc(node_count*sizeof*L);
    int *inbound_count = malloc(node_count*sizeof*inbound_count);

    for(int edge=0; edge<edge_count; edge++){
        fscanf(infile, "%d %d", &from_node_id[edge], &to_node_id[edge]);
        L[from_node_id[edge]]++;
        inbound_count[to_node_id[edge]]++;
    } 

    printf("File '%s' read successfully!\n", filename);
// Print out webgraph
//    printf("Nodes: %d, edges: %d\n", node_count, edge_count);
//    for(int i=0; i<edge_count; i++){
//        printf("%d   %d\n", from_node_id[i], to_node_id[i]);
//    }

    // Finding L(j) and D ---------------------------------------------------------
    int *perm = malloc(edge_count*sizeof*perm);
    for (size_t i = 0; i < edge_count; i++) {
        perm[i] = i;
    }
    sort(from_node_id, 0, edge_count, perm); // sorting to find L(j) 
    int edge = 0;
    for(int node=0; node<node_count; node++){
        if(L[node]==0) (*dangling_count)++;
    }
    if(*dangling_count>0){
        printf("No. of dangling webpages: %d\n", *dangling_count);
        (*D) = malloc(*dangling_count*sizeof*(*D));
        int node = 0;
        for(int d_node=0; d_node<*dangling_count; d_node++){
            while(L[node] != 0){
               node++; 
            }
            (*D)[d_node] = node;
            node++;
        }
    } else {
        printf("No dangling webpages.\n");
    }

    // Print L(j) and D
//    for(int node=0; node<node_count; node++){
//        printf("L(%d): %d\n", node, L[node]);
//    }
//    for(int node=0; node<*dangling_count; node++){
//        printf("D(%d): %d\n", node, (*D)[node]);
//    }
    // Sorting arrays --------------------------------------------------------------
    sort(to_node_id, 0, edge_count, perm);

    int start = 0;
    int end = 0;
    for(int node=0; node<node_count; node++){
        (*row_ptr)[node] = start;
        end += inbound_count[node];         
        sort(from_node_id, start, end, perm);
        start = end;
    }
    (*row_ptr)[node_count] = edge_count;

    printf("Sorting done!\n");

    // Printing sorted array 
//    printf("========\n");
//    for (size_t i = 0; i < edge_count; i++) {
//        printf("%d  %d\n", from_node_id[perm[i]], to_node_id[perm[i]]);
//    }

    // Setting up hyperlink matrix in CRS format ----------------------------------
    for(int edge=0; edge<edge_count; edge++){
        (*col_idx)[edge] = from_node_id[perm[edge]];
        (*val)[edge] = 1.0/(double)L[(*col_idx)[edge]];
    }    

    // Printing hyperlink matrix
//    printf("val      col_idx\n");
//    for (size_t i = 0; i < edge_count; i++) {
//        printf("%f  %d\n", (*val)[i], (*col_idx)[i]);
//    }
//    printf("row_ptr\n");
//    for (size_t i = 0; i < node_count; i++) {
//        printf("%d\n", (*row_ptr)[i]);
//    }

    free(from_node_id);
    free(to_node_id);
    free(L);
    free(perm);

    return node_count;
}

void PageRank_iterations(double **val, int **col_idx, int **row_ptr, double **x, double **x_new, int node_count, double damping, double threshold, int **D, int *dangling_count){
    // Initial guess:
    for(int i=0; i<node_count; i++){
       (*x)[i] = 1.0/(double)node_count;
    }    
    double W;
    double temp;
    double diff;
    int counter = 0;

    do {
        W = 0;
        diff = 0;
        for(int d_node=0; d_node<*dangling_count; d_node++){
            W += (*x)[(*D)[d_node]];
        }
        temp = (1 - damping + damping*W)/(double)node_count;
        for(int i=0; i<node_count; i++){
            (*x_new)[i] = 0;
            for(int j=(*row_ptr)[i]; j<(*row_ptr)[i+1]; j++){
                (*x_new)[i] += (*val)[j]*((*x)[(*col_idx)[j]]); 
            }
            (*x_new)[i] *= damping + temp;
            diff += abs((*x)[i] - (*x_new)[i]);
        }
        for(int i=0; i<node_count; i++) (*x)[i] = (*x_new)[i];
        counter++;
    } while(diff > threshold);

    printf("Counter: %d\n", counter);
    // Print resulting vector
    for(int i=0; i<node_count; i++) printf("x%d: %f\n", i, (*x)[i]);

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
