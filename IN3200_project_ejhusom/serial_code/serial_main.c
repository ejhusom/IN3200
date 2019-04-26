#include <stdio.h>
#include "functions.h"

#ifdef __MACH__
#include <stdlib.h>
#else 
#include <malloc.h>
#endif

void import_JPEG_file (const char* filename, unsigned char** image_chars,
                       int* image_height, int* image_width,
                       int* num_components);
void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                       int image_height, int image_width,
                       int num_components, int quality);


int main (int argc, char *argv[])
{

    int m, n, c; 
    int iters = 10;
    float kappa = 0.2;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename;
    char *output_jpeg_filename = "denoised.jpeg";

    /* TAKING COMMAND LINE ARGUMENTS ******************************************/
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
            printf("4: number of iterations (optioanl, default: 10)\n");
            return 0;
    }
    printf("%f\n", kappa);
 
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

    allocate_image(&u, m, n);
    allocate_image(&u_bar, m, n);
    convert_jpeg_to_image(image_chars, &u);
    iso_diffusion_denoising(&u, &u_bar, kappa, iters);
    printf("Image is denoised!\n");

    convert_image_to_jpeg(&u_bar, image_chars);    

    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

    deallocate_image(&u);
    deallocate_image(&u_bar);

    return 0;
}
