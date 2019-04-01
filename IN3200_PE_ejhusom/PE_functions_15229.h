#ifndef PE_FUNCTIONS_EJHUSOM_H
#define PE_FUNCTIONS_EJHUSOM_H

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <time.h>

int read_graph_from_file(char *filename, double **val, int **col_idx, int **row_ptr, int **D, int *dangling_count);
void PageRank_iterations(double **val, int **col_idx, int **row_ptr, double **x, double **x_new, int node_count, double damping, double threshold, int **D, int *dangling_count, int threads);
void top_n_webpages(double *x, int n, int node_count);
void sort(int arr[], int beg, int end);
void swap(int *a, int *b);

#endif /* PE_FUNCTIONS_EJHUSOM_H */
