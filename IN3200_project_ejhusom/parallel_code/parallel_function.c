#include "parallel_function.h"

void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters){
    for (int i = 0; i < u->m; i++){
        u_bar->image_data[i][0] = u->image_data[i][0];
        u_bar->image_data[i][u->n-1] = u->image_data[i][u->n-1];
    }
    for (int j = 1; j < u->n-1; j++){
        u_bar->image_data[0][j] = u->image_data[0][j];
        u_bar->image_data[u->m-1][j] = u->image_data[u->m-1][j];
    }
    for (int it = 0; it < iters; it++){
        for (int i = 1; i < u->m-1; i++){
            for (int j = 1; j < u->n-1; j++){
                u_bar->image_data[i][j] = u->image_data[i][j] 
                                            + kappa*(u->image_data[i-1][j] 
                                                    + u->image_data[i][j-1] 
                                                    - 4*u->image_data[i][j] 
                                                    + u->image_data[i][j+1] 
                                                    + u->image_data[i+1][j]); 
            }
        } 
        
        for (int i = 1; i < u->m-1; i++){
            for (int j = 1; j < u->n-1; j++){
                u->image_data[i][j] = u_bar->image_data[i][j];
            }
        }
    }
}
