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

void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters);

#endif /* FUNCTIONS_H */
