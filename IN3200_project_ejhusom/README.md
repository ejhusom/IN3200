# IN3200 High-performance computing and numerical projects - Project: Image Denoising

## Dependencies, compilation and executing the code

The program requires a gcc compiler and MPI. It is only tested on Ubuntu 18.04.

### Serial implementation

Run `cd serial_code/` to enter the correct folder. The code is compiled by running `make`, which produces the executable `serial_main.exe`.

The executable takes 4 command line arguments, of which 3 are optional:
1. File name of the image to be denoised.
2. File name of the output image (optional, default: "denoised.jpg".
3. Kappa value, a scalar constant used by the diffusion algorithm. Should be maximum 0.2 (optional, default: 0.2).
4. Number of iterations, where a larger number corresponds to a higher degree of denoising (optional, default: 100).


#### Example compilation and executing serial code

Compiling the code and executing with default values:

~~~
$ cd serial_code/
$ make
(...)
(...)
Linking complete!
serial_main.exe ready to run!
$ ./serial_main.exe mona_lisa_noisy.jpg
Time used: 3.042708
Image is denoised!
~~~

### Parallel implementation

Run `cd parallel_code/` to enter the correct folder. The code is compiled by running `make`, which produces the executable `parallel_main.exe`.

The executable must be run with `mpirun -np [number of processes]`, and takes 4 command line arguments, of which 3 are optional (same as serial code):
1. File name of the image to be denoised.
2. File name of the output image (optional, default: "denoised.jpg".
3. Kappa value, a scalar constant used by the diffusion algorithm. Should be maximum 0.2 (optional, default: 0.2).
4. Number of iterations, where a larger number corresponds to a higher degree of denoising (optional, default: 100).


#### Example compilation and executing parallel code

Compiling the code and executing with 4 processes and otherwise default values:

~~~
$ cd parallel_code/
$ make
(...)
(...)
Linking complete!
parallel_main.exe ready to run!
$ mpirun -np 4 parallel_main.exe mona_lisa_noisy.jpg
Time spent: 2.071043
Image is denoised!
~~~

## Timing
Each time any of the programs are run the timing measurements of the diffusion algorithm is appended to a file called `timing.txt`.
