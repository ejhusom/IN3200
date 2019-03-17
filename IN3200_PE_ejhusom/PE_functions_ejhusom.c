#include "PE_functions_ejhusom.h"

read_graph_from_file(FILE *infile){
    /* This function reads web graph from a text file. */
    double var;
    int i = 0;
    FILE *infile;
    infile = fopen("array.txt","r");
    while (fscanf(infile, "%lf\n", &var) == 1){
        //arr[i] = var;
        i++;
    }
    fclose(infile);
}

PageRank_iterations(){

}

top_n_webpages(int n){
    /* This function lists the top n webpages with their score. */
    int page_idx = 0;
    double score = 1.0;

    printf("Rank  Page index    Score");
    for (int i=1; i<n+1; i++){
        printf("%d   %d    %f", i, page_idx, score);
    }
}
