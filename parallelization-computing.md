# Parallelization in practice - Code

## Table of contents
1. [OpenMP](#openmp)
2. [MPI](#mpi)

---

## OpenMP

### Including
~~~
#include <omp.h>
~~~

### Compiling:
$ gcc -fopenmp source.c

### Setting number of threads
In command line (recommended):
$ export OMP_NUM_THREADS=6

Inside program (not recommended):
~~~c
#pragma omp parallel num_threads(6)
~~~

### Parallel region:
~~~c
#pragma omp parallel
{
   /* code */
}
~~~
Variables defined inside these brackets are private to each thread.


### Private and firstprivate
~~~c
#pragma omp parallel private(var1, var2, var3) firstprivate(var4)
{
}
Firstprivate means that also the value of the variable is inherited.
~~~

### Default work sharing:
~~~c
#pragma omp parallel for
   for(i=0; i<N; i++) a[i] = b[i] + c[i];
~~~
The compiler takes care of deciding the bounds for each thread. One doesn’t need brackets. The loop can not contain `break`, `return` or `exit` statements. The `continue`statement is allowed. The index update has to be a fixed increment or decrement. Changes to the loop index variable inside the loop is not allowed.

Different ways of dividing threads: static, dynamic, guided. The default is static, which divides the iterations into contigious chunks of (roughly) equal size. It is possible to prescribe a chunksize in the schedule clause:
~~~c
#pragma omp parallel for schedule(static|dynamic
guided [,chunk])
~~~
Example:
~~~c
#pragma omp parallel for schedule(dynamic,3)
~~~

#### Dynamic (default chunk size=1)
The first chunks are divided as specified, and after that the threads who finish first will get the next.

#### Guided (default chunk size=1)
Starts out as static, but decreases until given chunk size is reached.


### Manual work sharing:
~~~c
#pragma omp parallel
{
    int num_threads, thread_id;
    int blen, bstart, bend, i;
    num_threads = omp_get_num_threads();
    thread_id = omp_get_thread_num();
    blen = N/num_threads;
    if (thread_id < (N%num_threads)){
        blen = blen + 1;
        bstart = blen * thread_id;
    } else {
        bstart = blen * thread_id + (N%num_threads);
    }
    bend = bstart + blen;
    for (i=bstart; i<bend; i++)
        a[i] = b[i] + c[i];
} // end of parallel region
~~~

### Critical
~~~c
#pragma omp critical
{
}
~~~
This block will be visited by each thread in turn, and eliminates race conditions. Critical can many times be replaced by `reduction`:
~~~c
#pragma omp parallel for reduction(+:s)
for (i=0; i<N; i++)
  s = s + a[i]*a[i];
~~~
This creates a private variable in each thread, and then adds everything together in the end.


### Single
A "single" code block will only be entered by one thread (the one that reachs the block first). All other threads wait at the end of the single block due to an implicit barrier.

### Task
A task can be used inside a single block, where any other thread than the single-thread can execute the task.

### Master
A "master" code block will only be entered by the master thread. The other threads skip the block without waiting for the master thread to finish.

### Barrier


---


## MPI

The same program runs on all processes (SPMD), no difference from OpenMP in this regard.

DIFFERENCE: All variables in a process are LOCAL to each process (nothing is shared).

~~~c
#include <mpi.h>

rv = MPI_Xxxxxxx(parameter, ... )
~~~

Beware of case-sensitive naming pattern. Return value (rv) returns MPI_SUCCESS if the routine is completed.

### Compilation and execution
$ mpicc source.c
$ mpirun -np 4 ./a.out

The integer 4 is number of processes.

### Functions

~~~c
// Initializes parallel environment:
int MPI_Init(int *argc, char ***argv);
~~~


### MPI_COMM_WORLD

An MPI communicator is a "communication universe" for a group of processes. MPI_COMM_WORLD is the name of the default communicator. Each process in a communicator is identified by its rank. Almost every MPI command needs to provide a communicator as input argument.

### MPI process rank

Each process has a unique rank (integer identifier). Rank value between 0 and #procs-1.

### MPI_Finalize()

Parallel program shut down. Only process with rank 0 will execute something after this command.



