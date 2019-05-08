#include "functions.h"

void allocate_image(image *u, int m, int n){
    u->m = m;
    u->n = n;
    u->image_data = (float**) malloc(m * sizeof(float*));

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
            u->image_data[i][j] = (float)image_chars[u->n*i + j];
        }
    }
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars){
    for (int i = 0; i < u->m; i++){
        for (int j = 0; j < u->n; j++){
            image_chars[u->n*i + j] = u->image_data[i][j];
        }
    }
}


void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters, int num_procs, int my_rank){

    int inner_length = u->n - 2;
    float *upper_edge = (float*)malloc(inner_length*sizeof(float));
    float *lower_edge = (float*)malloc(inner_length*sizeof(float));

    /* SETTING BOUNDARIES OF IMAGE */
    for (int i = 0; i < u->m; i++){
        u_bar->image_data[i][0] = u->image_data[i][0];
        u_bar->image_data[i][u->n-1] = u->image_data[i][u->n-1];
    }
    if (my_rank==0 || my_rank==(num_procs -1)){
        for (int j = 1; j < u->n-1; j++){
            u_bar->image_data[0][j] = u->image_data[0][j];
            u_bar->image_data[u->m-1][j] = u->image_data[u->m-1][j];
        }
    }

    /* STARTING ITERATIONS */
    for (int it = 0; it < iters; it++){
        /* SENDING AND RECIEVING EDGES */
        if (my_rank == 0){
            MPI_Send(&(u->image_data[u->m - 1][1]), inner_length, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD);
            MPI_Recv(lower_edge, inner_length, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else if (my_rank == (num_procs - 1)){
            MPI_Recv(upper_edge, inner_length, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&(u->image_data[0][1]), inner_length, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD);
        } else {
            if ( (my_rank % 2) > 0){
                MPI_Recv(upper_edge, inner_length, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&(u->image_data[u->m-1][1]), inner_length, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD);
                MPI_Recv(lower_edge, inner_length, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&(u->image_data[0][1]), inner_length, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD);
            } else {
                MPI_Send(&(u->image_data[u->m-1][1]), inner_length, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD);
                MPI_Recv(upper_edge, inner_length, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&(u->image_data[0][1]), inner_length, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD);
                MPI_Recv(lower_edge, inner_length, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }


//        if (my_rank != 0 && my_rank != (num_procs - 1)){
//
//            for (int i = 1; i < u->m-1; i++){
//                for (int j = 1; j < u->n-1; j++){
//                    u_bar->image_data[i][j] = u->image_data[i][j] 
//                                                + kappa*(u->image_data[i-1][j] 
//                                                        + u->image_data[i][j-1] 
//                                                        - 4*u->image_data[i][j] 
//                                                        + u->image_data[i][j+1] 
//                                                        + u->image_data[i+1][j]); 
//                }
//            } 
//        }

        /* UPDATING IMAGE */
        for (int i = 1; i < u->m-1; i++){
            for (int j = 1; j < u->n-1; j++){
                u->image_data[i][j] = u_bar->image_data[i][j];
            }
        }
    } /* end of iterations */
    
}
