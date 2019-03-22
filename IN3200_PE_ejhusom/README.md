# IN3200 High-performance computing and numerical projects - Partial exam: Computing PageRank

## Compilation, dependencies and executing the program

The project is compiled by running `make`, which produces the executable `PageRank.exe`. The program requires a gcc compiler and OpenMP. It is only tested on Ubuntu 18.04.

The executable takes 5 command line arguments, of which 3 are optional:
1. File name of the file containing the webgraph.
2. Number of threads for the parallelized part of the program.
3. Threshold value for the stopping criterion in the PageRank algorithm (optional, default: 1e-08).
4. Integer n to show the top n webpages in the webgraph (optional, default: 8).
5. Damping constant (optional, default: 0.85).

### Example compilation and executing with printouts

~~~
$ make
gcc -g -Wall -fopenmp PE_functions_ejhusom.c PE_main_ejhusom.c -o PageRank.exe
Linking complete!
PageRank.exe ready to run!
$ ./PageRank.exe web-NotreDame.txt 4

******************************
Web graph: web-NotreDame.txt
Nodes: 325729, edges: 1497134
Number of self-links: 27455
Number of dangling webpages: 188795

Time elapsed for read_graph_from_file() is 0.452580 seconds.

Number of PageRank iterations: 85

Time elapsed for PageRank_iterations() is 0.910567 seconds.

Rank          Page      Score
  1.         1963       0.0056267675
  2.            0       0.0054045120
  3.       124802       0.0033262290
  4.        12129       0.0028570561
  5.       191267       0.0027487314
  6.        32830       0.0027318342
  7.         3451       0.0025899847
  8.        83606       0.0024596916

Time elapsed for top_n_webpages() is 0.007787 seconds.


Time elapsed in total is 1.370984 seconds.
~~~

## Project structure

The main source file `PE_main_ejhusom.c` sets up the needed arrays, calls all functions and times each function, in addition to the total run time.

The project consists of the following functions, placed in the file `PE_functions_ejhusom.c`:

### `read_graph_from_file()`

This functions reads a webgraph from a file, and sets up a matrix in the Compressed Row storage (CRS) format.

### `PageRank_iterations()`

This functions implements the PageRank algorithm, which includes doing matrix-vector-multiplication on the CRS matrix produced by `read_graph_from_file()`. The algorithm produces a result vector, which contains the converged PageRank scores for each page. The PageRank iterations continues until the sum of the differences between the new vector and the vector from the previous step is below a certain threshold.

OpenMP is used to parallelize the matrix-vector-multiplication in this function, in addition to the for loop which sets up the initial score vector.

### `top_n_webpages()`

This function a number n as input, and prints the n highest scores from result vector produced in `PageRank_iterations()`.
