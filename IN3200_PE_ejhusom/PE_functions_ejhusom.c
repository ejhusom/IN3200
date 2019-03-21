#include "PE_functions_ejhusom.h"

int read_graph_from_file(char *filename, double **val, int **col_idx, int **row_ptr, int **D, int *dangling_count){
    /* This function reads web graph from a text file, and sets up the hyperlink matrix in CRS format. */

    /* READING FILE ***********************************************/

    FILE *infile = fopen(filename,"r");

    if(infile==NULL){
        printf("File not found.\n");
        exit(0);
    }
    int node_count;
    int edge_count;
    for(int i=0; i<2; i++) fscanf(infile, "%*[^\n]\n"); // skip the first lines.
    fscanf(infile, "%*s %*s %d %*s %d ", &node_count, &edge_count); // read number of nodes and edges.
    fscanf(infile, "%*[^\n]\n"); // skip another line.
    printf("Nodes: %d, edges: %d\n", node_count, edge_count);

    (*row_ptr) = malloc((node_count+1)*sizeof*(*row_ptr));
    int *outbound_count = calloc(node_count, sizeof*outbound_count);
    int *inbound_count = calloc(node_count, sizeof*inbound_count);
    int *from_node_id = malloc(edge_count*sizeof*from_node_id);
    int *to_node_id = malloc(edge_count*sizeof*to_node_id);

    int edge_count_new = 0;
    int from_node;
    int to_node;
    for(int edge=0; edge<edge_count; edge++){
        fscanf(infile, "%d %d", &from_node, &to_node);
        if(from_node != to_node){
            from_node_id[edge_count_new] = from_node;
            to_node_id[edge_count_new] = to_node;
            outbound_count[from_node_id[edge_count_new]]++;
            inbound_count[to_node_id[edge_count_new]]++;
            edge_count_new++;
        }
    }
    fclose(infile);
    printf("File '%s' read successfully!\n", filename);
    printf("Number of self-links: %d\n", edge_count - edge_count_new);
    edge_count = edge_count_new; // removing self-linkage.

    (*val) = malloc(edge_count*sizeof*(*val));
    (*col_idx) = malloc(edge_count*sizeof*(*col_idx));

    /* DEBUG: Print out webgraph */
//    for(int i=0; i<edge_count; i++){
//        printf("%d   %d\n", from_node_id[i], to_node_id[i]);
//    }

    /* FINDING ROW_PTR ***********************************************/
    int sum = 0;
    (*row_ptr)[0] = 0;
    for(int i=1; i<node_count+1; i++){
        sum += inbound_count[i-1];
        (*row_ptr)[i] = sum;
        // printf("row_ptr: %d\n", (*row_ptr)[i]); /* DEBUG */
        //printf("inbound_count: %d\n", inbound_count[i-1]); /* DEBUG */
    }

    /* FINDING D *****************************************************/
    for(int node=0; node<node_count; node++){
        if(outbound_count[node]==0) (*dangling_count)++;
    }
    if((*dangling_count)>0){
        printf("Number of dangling webpages: %d\n", *dangling_count);
        (*D) = malloc(*dangling_count*sizeof*(*D));
        int node = 0;
        for(int d_node=0; d_node<*dangling_count; d_node++){
            while(outbound_count[node] != 0){
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
//        printf("outbound_count(%d): %d\n", node, outbound_count[node]);
//    }
//    for(int node=0; node<*dangling_count; node++){
//        printf("D(%d): %d\n", node, (*D)[node]);
//    }

    /* Sorting arrays *************************************************/
    int *perm = malloc(edge_count*sizeof*perm);
    for (size_t i = 0; i < edge_count; i++) {
        perm[i] = i;
    }
//    struct timespec start, end;
//	clock_gettime(CLOCK_REALTIME, &start);
//    sort(from_node_id, 0, edge_count, perm);
//    clock_gettime(CLOCK_REALTIME, &end);
//	double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
//	printf("Time elapsed for sorting is %f seconds.\n\n", time_spent);
//    int col;
//    int row;
//    int idx;
//    int *elm_count = calloc(node_count, sizeof*elm_count);
//    for(int edge=0; edge<edge_count; edge++){
//        col = from_node_id[perm[edge]];
//        row = to_node_id[perm[edge]];
//        elm_count[row]++;
//        idx = (*row_ptr)[row] + elm_count[row] - 1;
//        (*col_idx)[idx] = col;
//        (*val)[idx] = 1.0/((double)outbound_count[col]);
//    }

    int col;
    int row;
    int idx;
    int *elm_count = calloc(node_count, sizeof*elm_count);
    for(int edge=0; edge<edge_count; edge++){
        col = from_node_id[perm[edge]];
        row = to_node_id[perm[edge]];
        elm_count[row]++;
        idx = (*row_ptr)[row] + elm_count[row] - 1;
        (*col_idx)[idx] = col;
    }

    struct timespec start, end;
    int start_idx = 0;
    int end_idx = 0;
	clock_gettime(CLOCK_REALTIME, &start);
    for(int node=0; node<node_count; node++){
        end_idx += inbound_count[node];         
        sort(from_node_id, start_idx, end_idx, perm);
        start_idx = end_idx;
    }
    clock_gettime(CLOCK_REALTIME, &end);
	double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time elapsed for sorting is %f seconds.\n\n", time_spent);

    printf("Sorting done!\n");

    for(int edge=0; edge<edge_count; edge++){
        (*val)[edge] = 1.0/((double)outbound_count[(*col_idx)[edge]]);

    }

//    struct timespec start, end;
//	clock_gettime(CLOCK_REALTIME, &start);
//    sort(to_node_id, 0, edge_count, perm);
//    clock_gettime(CLOCK_REALTIME, &end);
//	double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
//	printf("Time elapsed for sorting is %f seconds.\n\n", time_spent);
//    int start_idx = 0;
//    int end_idx = 0;
//	clock_gettime(CLOCK_REALTIME, &start);
//    for(int node=0; node<node_count; node++){
//        end_idx += inbound_count[node];         
//        sort(from_node_id, start_idx, end_idx, perm);
//        start_idx = end_idx;
//    }
//    clock_gettime(CLOCK_REALTIME, &end);
//	time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
//	printf("Time elapsed for sorting is %f seconds.\n\n", time_spent);
//
//    printf("Sorting done!\n");
//
//    // Printing sorted array 
////    printf("========\n");
////    for (size_t i = 0; i < edge_count; i++) {
////        printf("%d  %d\n", from_node_id[perm[i]], to_node_id[perm[i]]);
////    }
//
//    // Setting up hyperlink matrix in CRS format ----------------------------------
//    for(int edge=0; edge<edge_count; edge++){
//        (*col_idx)[edge] = from_node_id[perm[edge]];
//        (*val)[edge] = 1.0/((double)outbound_count[(*col_idx)[edge]]);
//    }    
    // Printing hyperlink matrix
//    printf("val      col_idx\n");
//    for (size_t i = 0; i < edge_count; i++) {
//        printf("%f  %d\n", (*val)[i], (*col_idx)[i]);
//    }

    free(from_node_id);
    free(to_node_id);
    free(outbound_count);
    free(inbound_count);
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
    int counter_while = 0;
    int loop = 1;

    while(loop){
        W = 0;
        diff = 0.0;
        for(int d_node=0; d_node<*dangling_count; d_node++){
            W += (*x)[(*D)[d_node]];
        }
        temp = (1 - damping + damping*W)/(double)node_count;

        //#pragma omp parallel for schedule(static)
        for(int i=0; i<node_count; i++){
            (*x_new)[i] = 0;
            for(int j=(*row_ptr)[i]; j<(*row_ptr)[i+1]; j++){
                (*x_new)[i] += (*val)[j]*((*x)[(*col_idx)[j]]); 
            }
            (*x_new)[i] = (*x_new)[i]*damping + temp;
        }

        for(int i=0; i<node_count; i++){
            diff += fabs((*x)[i] - (*x_new)[i]);
            (*x)[i] = (*x_new)[i];
        }
        if(diff < threshold) loop = 0;

        counter_while++;
    }

    printf("Number of PageRank iterations: %d\n", counter_while);

    /* DEBUG: Print resulting vector */
//    for(int i=0; i<node_count; i++) printf("x%d: %.20f\n", i, (*x)[i]);

}

void top_n_webpages(double **x, int n, int node_count){
    /* This function lists the top n webpages with their score. */
    int *perm = malloc(node_count*sizeof*perm);
    for (int i = 0; i<node_count; i++) {
        perm[i] = i;
    }

    sort_double(*x, 0, node_count, perm);

    printf("Rank          Page      Score\n");
    for (int i=0; i<n; i++){
        printf("%3d      %7d       %.10f\n", i+1, perm[node_count - 1 - i], (*x)[perm[node_count - 1 - i]]);
    }

    free(perm);
    
//
//    double roof = 10.0;
//    double max_temp = 0;
//    int rank = 1;
//    int idx = node_count;
//    int idx_prev = node_count;
//    printf("Rank  Page   Score\n");
//    for(int i=0; i<n; i++){
//        for(int node=0; node<node_count; node++){
//            if((*x)[node] > max_temp && (*x)[node] <= roof && idx_prev != node){
//                max_temp = (*x)[node];
//                idx = node;
//            }
//        }
//        printf("%d      %d       %.20f\n", rank, idx, max_temp);
//        rank++;
//        roof = max_temp;
//        max_temp = 0;
//        idx_prev = idx;
//    }



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

void sort_double(double arr[], int beg, int end, int perm[]){
  if (end > beg + 1) {
    double piv = arr[perm[beg]];
    int l = beg + 1, r = end;
    while (l < r) {
      if (arr[perm[l]] <= piv)
        l++;
      else
        swap(&perm[l], &perm[--r]);
    }
    swap(&perm[--l], &perm[beg]);
    sort_double(arr, beg, l, perm);
    sort_double(arr, r, end, perm);
  }
}
