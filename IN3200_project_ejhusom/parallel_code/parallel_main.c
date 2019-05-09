#include "functions.h"

void import_JPEG_file (const char* filename, unsigned char** image_chars,
                       int* image_height, int* image_width,
                       int* num_components);
void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                       int image_height, int image_width,
                       int num_components, int quality);


int main (int argc, char *argv[])
{

    int m, n, c; 
    int my_m, my_start, my_stop, my_rank, num_procs;
    int iters = 100;
    float kappa = 0.2;
    image u, u_bar, whole_image;
    unsigned char *image_chars, *my_image_chars;
    char *input_jpeg_filename;
    char *output_jpeg_filename = "denoised.jpeg";

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    /* TAKING COMMAND LINE ARGUMENTS */
    switch (argc) {
        case 5:
            iters = atoi(argv[4]);
        case 4: 
            kappa = atof(argv[3]);
        case 3:
            output_jpeg_filename = argv[2];
        case 2: 
            input_jpeg_filename = argv[1];
            break;
        case 1: 
            printf("Give the following command line arguments:\n");
            printf("1: input filename of JPEG\n");
            printf("2: output filename of JPEG (optional, default: denoised.jpeg)\n");
            printf("3: kappa (optional, default: 0.2)\n");
            printf("4: number of iterations (optional, default: 100)\n");
            return 0;
    }
 
    /* IMPORTING IMAGE */
    if (my_rank==0){
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
        allocate_image(&whole_image, m, n);
    }



    /* FINDING REGION AND BOUNDS FOR EACH PROCESS */
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int m_partition = m/num_procs;
    int m_rest = m%num_procs;
    if (m_rest > 0){
        my_start = n*my_rank*(m_partition + 1);
        if (my_rank < num_procs-1){
            my_m = m_partition + 1;
            my_stop = n*(my_rank + 1)*(m_partition + 1);
        } else {
            my_stop = m*n;
            my_m = m - my_start/n;
        }
    } else {
        my_start = n*my_rank*m_partition;
        my_m = m_partition;
        my_stop = n*(my_rank + 1)*m_partition;
    }

    printf("Rank=%d, my_m=%d, start=%d, stop=%d\n", my_rank, my_m, my_start, my_stop);

    int *sizes, *start_idx;
    int my_size = my_m*n;
    if (my_rank == 0){
        sizes = (int*)malloc(num_procs*sizeof(int));
        start_idx = (int*)malloc(num_procs*sizeof(int));
    }
    MPI_Gather(&my_size, 1, MPI_INT, sizes, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(&my_start, 1, MPI_INT, start_idx, 1, MPI_INT, 0, MPI_COMM_WORLD);

    my_image_chars = (unsigned char*)malloc(my_size*sizeof(unsigned char));

    MPI_Scatterv(image_chars, sizes, start_idx, MPI_UNSIGNED_CHAR, my_image_chars, my_size, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    allocate_image(&u, my_m, n);
    allocate_image(&u_bar, my_m, n);
    convert_jpeg_to_image(my_image_chars, &u);

    /* DENOISING IMAGE AND MEASURING TIME USAGE */
    
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    MPI_Barrier(MPI_COMM_WORLD);

    iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters, num_procs, my_rank);

    MPI_Barrier(MPI_COMM_WORLD);
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    if (my_rank == 0){
        printf("Time spent: %f\n", time_spent);
        /* WRITING TIME MEASUREMENT TO FILE */
    //    FILE *outfile = fopen("timing.txt", "a");
    //    fprintf(outfile, "%f\n", end-start);
    //    fclose(outfile);
    }

    if (my_rank == 0) printf("Image is denoised!\n");


    convert_image_to_jpeg(&u, my_image_chars);

    MPI_Gatherv(my_image_chars, my_size, MPI_UNSIGNED_CHAR, image_chars, sizes, start_idx, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    if (my_rank==0){
        export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
        deallocate_image(&whole_image);
        free(image_chars);
        free(sizes);
        free(start_idx);
    }

    deallocate_image(&u);
    deallocate_image(&u_bar);
    free(my_image_chars);

    MPI_Finalize();
    return 0;
}
