#include "functions.h"

void allocate_image(image *u, int m, int n){
    u->m = m;
    u->n = n;
    u->image_data = (float**) malloc(m * sizeof(float*));
    //u->image_data = (float*)calloc(m*n , sizeof*u->image_data);

    for (int i = 0; i < m; i++) {
        u->image_data[i] = (float*)malloc(n * sizeof(float));
    }

}

void deallocate_image(image *u){
    for (int i = 0; i < u->m; i++){
        free(u->image_data[i]);
    } 
    free(u->image_data);
}

void convert_jpeg_to_image(const unsigned char* image_chars, image *u){
    for (int i = 0; i < u->m; i++){
        for (int j = 0; j < u->n; j++){
            //u->image_data[idx(i, j)] = (float)image_chars[u->n*i + j];
            u->image_data[i][j] = (float)image_chars[u->n*i + j];
        }
    }
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars){
    for (int i = 0; i < u->m; i++){
        for (int j = 0; j < u->n; j++){
            //image_chars[u->n*i + j] = u->image_data[idx(i, j)];
            image_chars[u->n*i + j] = u->image_data[i][j];
        }
    }
}

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters){
    for (int i = 0; i < u->m; i++){
        u_bar->image_data[i][0] = u->image_data[i][0];
        u_bar->image_data[i][u->n-1] = u->image_data[i][u->n-1];
//        u_bar->image_data[idx(i, 0)] = u->image_data[idx(i, 0)];
//        u_bar->image_data[idx(i, u->n-1)] = u->image_data[idx(i, u->n-1)];
    }
    for (int j = 1; j < u->n-1; j++){
        u_bar->image_data[0][j] = u->image_data[0][j];
        u_bar->image_data[u->m-1][j] = u->image_data[u->m-1][j];
//        u_bar->image_data[idx(0, j)] = u->image_data[idx(0, j)];
//        u_bar->image_data[idx(u->m-1, j)] = u->image_data[idx(u->m-1, j)];
    }
    for (int it = 0; it < iters; it++){
        for (int i = 1; i < u->m-1; i++){
            for (int j = 1; j < u->n-1; j++){
//                u_bar->image_data[idx(i, j)] = u->image_data[idx(i, j)] 
//                                            + kappa*(u->image_data[idx(i-1, j)] 
//                                                    + u->image_data[idx(i, j-1)] 
//                                                    - 4*u->image_data[idx(i, j)] 
//                                                    + u->image_data[idx(i, j+1)] 
//                                                    + u->image_data[idx(i+1, j)]); 
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
                //u->image_data[idx(i, j)] = u_bar->image_data[idx(i, j)];
                u->image_data[i][j] = u_bar->image_data[i][j];
            }
        }
    }
    

//      float* A = u->image_data; /* used for shorthand */
//  float* B = u_bar->image_data;
//
//  /* first copy boundry values from u=A to u_bar=B */
//  for (int i = 0; i < u->m; i++) {
//    B[idx(i, 0)] = A[idx(i, 0)];
//    B[idx(i, u->n-1)] = A[idx(i, u->n-1)];
//  }
//  for (int j = 1; j < u->n-1; j++) {
//    B[idx(0, j)] = A[idx(0, j)];
//    B[idx(u->m-1, j)] = A[idx(u->m-1, j)];
//  }
//  
//  for (int counter = 0; counter < iters; counter++) {
//    /* perform one iteration of the transformation
//     * note that only inner pixels are modified */
//    for (int i = 1; i < u->m-1; i++) {
//      for (int j = 1; j < u->n-1; j++) {
//        B[idx(i, j)] = A[idx(i, j)] + kappa * (A[idx(i-1, j)] + A[idx(i, j-1)]
//				     - 4*A[idx(i, j)]
//				     + A[idx(i+1, j)] + A[idx(i, j+1)] );
//      }
//    }
//
//    /* update for a new iteration */
//    for (int i = 1; i < u->m; i++) 
//      for (int j = 1; j < u->n; j++) 
//	u->image_data[idx(i, j)] = u_bar->image_data[idx(i, j)];
//} 

}
