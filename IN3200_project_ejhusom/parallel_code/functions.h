#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

typedef struct
{
    float** image_data;
    int m;
    int n;
}
image;

void allocate_image(image *u, int m, int n);
void deallocate_image(image *u);
void convert_jpeg_to_image(const unsigned char* image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char* image_chars);
void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters, int num_procs, int my_rank);

#endif /* FUNCTIONS_H */
