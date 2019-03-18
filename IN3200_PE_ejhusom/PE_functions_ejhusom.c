#include "PE_functions_ejhusom.h"

void read_graph_from_file(char *filename, int *from_node_id, int *to_node_id, double *val, int *col_idx, int *row_ptr){
    /* This function reads web graph from a text file, and sets up the hyperlink matrix in CRS format. */

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

    for(int edge=0; edge<edge_count; i++){
        fscanf(infile, "%d %d", &from_node_id[edge], &to_node_id[edge]);
    } 

    printf("File '%s' read successfully!\n", filename);
// Print out webgraph
//    printf("Nodes: %d, edge_count: %d\n", node_count, edge_count);
//    for(int i=0; i<edge_count; i++){
//        printf("%d   %d\n", from_node_id[i], to_node_id[i]);
//    }

    // Finding L(j)
    int *L = malloc(node_count*sizeof*L);
    int edge = 0;
    for(int node=0; node<node_count; node++){
        while(from_node_id[edge]==node){
            L[node] += 1;
            edge++;
        }
    }
    // Print L(j)
//    for(int node=0; i<node_count; i++){
//        printf("%d\n", L[node]);
//    }

    // Set up hyperlink matrix
    for(int edge=0; edge<edge_count; edge++){
        
    }


}

void PageRank_iterations(){

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
