#ifndef PE_FUNCTIONS_EJHUSOM_H
#define PE_FUNCTIONS_EJHUSOM_H

#include <stdlib.h>
#include <stdio.h>

void read_graph_from_file(char *filename, int *from_node_id, int *to_node_id);
void PageRank_iterations();
void top_n_webpages(int n);

#endif /* PE_FUNCTIONS_EJHUSOM_H */
