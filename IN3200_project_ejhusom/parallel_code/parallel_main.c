#include "../serial_code/functions.h"
#include "parallel_function.h"

void import_JPEG_file (const char* filename, unsigned char** image_chars,
                       int* image_height, int* image_width,
                       int* num_components);
void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                       int image_height, int image_width,
                       int num_components, int quality);


int main (int argc, char *argv[])
{

    int m, n, c; 
    int my_m, my_n, my_rank, num_procs;
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
 
    if (my_rank==0){
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
        allocate(&whole_image, m, n);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPIP_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPIP_COMM_WORLD);
    
    m_overflow = m%num_procs;
    n_overflow = n%num_procs;
    my_m = ;
    my_n = 0;

    allocate_image(&u, m, n);
    allocate_image(&u_bar, m, n);

    /* each process asks process 0 for a partitioned region */
    /* of image_chars and copy the values into u */
    /*  ...  */

    convert_jpeg_to_image(image_chars, &u);
    
    /* DENOISING IMAGE AND MEASURING TIME USAGE */
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters);

    /* each process sends its resulting content of u_bar to process 0 */
    /* process 0 receives from each process incoming values and */
    /* copy them into the designated region of struct whole_image */
    /*  ...  */

    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    /* WRITING TIME MEASUREMENT TO FILE */
//    FILE *outfile = fopen("timing.txt", "a");
//    fprintf(outfile, "%f\n", time_spent);
//    fclose(outfile);

    printf("Image is denoised!\n");

    if (my_rank==0){
        convert_image_to_jpeg(&whole_image, image_chars);    
        export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
        deallocate_image(&whole_image);
    }

    deallocate_image(&u);
    deallocate_image(&u_bar);

    MPI_Finalize();
    return 0;
}
