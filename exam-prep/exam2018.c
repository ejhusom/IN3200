#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

void merge (int m, const int *sorted_sublist1, const int *sorted_sublist2, int *merged_list){
    int i,j,k;
    i = 0;
    j = 0;
    k = 0;

    while (i<m && j<m)  {
        if (sorted_sublist1[i] <=sorted_sublist2[j])    {
            merged_list[k] = sorted_sublist1[i];
            i++;
        } else {
            merged_list[k] = sorted_sublist2[j];
            j++;
        }
        k++;
    }

    if (i<m) {
        while (i<m){
            merged_list[k] = sorted_sublist1[i];
        }
    } else {
        while (j<m){
            merged_list[k] = sorted_sublist2[j];
        }
    }


}

void compare_split(int m, int *my_sublist, int my_MPI_rank, int other_MPI_rank){


    int other_sublist[m];
    int merged_list[2*m];

    MPI_Sendrecv(my_sublist, m, MPI_INT, other_MPI_rank, 0, other_sublist, m, MPI_INT, other_MPI_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    merge(m, my_sublist, other_sublist, merged_list);

    if (my_MPI_rank < other_MPI_rank){
        for (int i = 0; i < m; i++) my_sublist[i] = merged_list[i];
    } else {
        for (int i = m; i < 2*m; i++) my_sublist[i-m] = merged_list[i];
    }

}


void odd_even_block_paralell(int m, int *my_sublist, int my_rank, int num_procs){

    int n = num_procs*m;
    for (int i = 0; i < n; i++) {
        if (i%2) {
            if (my_rank%2 && my_rank != num_procs-1) {
                compare_split(m, my_sublist, my_rank, my_rank + 1);
            } else if (!(my_rank%2) && my_rank != 0) {
                compare_split(m, my_sublist, my_rank, my_rank - 1);
            }
        } else {
            if (!(my_rank%2) && my_rank != 0) {
                compare_split(m, my_sublist, my_rank, my_rank + 1);
            } else if (my_rank%2 && my_rank != num_procs-1) {
                compare_split(m, my_sublist, my_rank, my_rank - 1);
            }
        }
    }

}


int main(int argc, char *argv[]) {

    int my_rank;
    int num_procs;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    int m = 5;
    int my_sublist[m];
    int other_rank;

    if (my_rank == 0) {
        for (int i = 0; i < m; i++) {
            my_sublist[i] = i*2;
        }
        other_rank = 1;
    } else {
        for (int i = 0; i < m; i++) {
            my_sublist[i] = i*2 + 1;
        }
        other_rank = 0;
    }

    printf("My rank: %d\n", my_rank);
    for (int i = 0; i < m; i++) {
        printf("%d\n", my_sublist[i]);
    }


    odd_even_block_paralell(m, my_sublist, my_rank, num_procs);


    printf("My rank: %d\n", my_rank);
    for (int i = 0; i < m; i++) {
        printf("%d\n", my_sublist[i]);
    }


    return 0;
}
