#ifndef PE_FUNCTIONS_EJHUSOM_H
#define PE_FUNCTIONS_EJHUSOM_H

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int read_graph_from_file(char *filename, double **val, int **col_idx, int **row_ptr, int **D, int *dangling_count);
void PageRank_iterations(double **val, int **col_idx, int **row_ptr, double **x, double **x_new, int node_count, double damping, double threshold, int **D, int *dangling_count);
void top_n_webpages(int n);
void swap(int *a, int *b);
void sort(int arr[], int beg, int end, int perm[]);

#endif /* PE_FUNCTIONS_EJHUSOM_H */
