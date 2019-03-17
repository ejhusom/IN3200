#include "PE_functions_ejhusom.h"

void read_graph_from_file(char *filename, int *from_node_id, int *to_node_id){
    /* This function reads web graph from a text file. */

    FILE *infile = fopen(filename,"r");

    if(infile==NULL){
        printf("File not found.\n");
        exit(0);
    }

    int nodes;
    int edges;
    for(int i=0; i<2; i++) fscanf(infile, "%*[^\n]\n"); // skip the first lines.
    fscanf(infile, "%*s %*s %d %*s %d ", &nodes, &edges); // read number of nodes and edges.
    fscanf(infile, "%*[^\n]\n"); // skip another line


    from_node_id = malloc(edges*sizeof*from_node_id);
    to_node_id = malloc(edges*sizeof*to_node_id);

    for(int i=0; i<edges; i++){
        fscanf(infile, "%d %d", &from_node_id[i], &to_node_id[i]);
    } 

    printf("File '%s' read successfully!\n", filename);
// Print out webgraph
//    printf("Nodes: %d, edges: %d\n", nodes, edges);
//    for(int i=0; i<edges; i++){
//        printf("%d   %d\n", from_node_id[i], to_node_id[i]);
//    }

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
