# IN3200 - Exam notes

## OpenMP




## MPI
~~~c
int MPI_Comm_size( MPI_Comm comm, int*size )
int MPI_Comm_rank( MPI_Comm comm, int*rank )
int MPI_Barrier( MPI_Comm comm )
int MPI_Send(const void *buf, int count, MPI_Datatype datatype,int dest, int tag, MPI_Comm comm)
int MPI_Recv(void*buf, int count, MPI_Datatype datatype, int source,int tag, MPI_Comm comm, MPI_Status*status)
int MPI_Bcast( void*buffer, int count, MPI_Datatype datatype, int root,MPI_Comm comm )
int MPI_Alltoall(const void*sendbuf, int sendcount, MPI_Datatype sendtype,void*recvbuf, int recvcount, MPI_Datatype recvtype,MPI_Comm comm)
int MPI_Reduce(const void*sendbuf, void*recvbuf, int count,MPI_Datatype datatype,MPI_Op op, int root, MPI_Comm comm)
int MPI_Allreduce(const void*sendbuf, void*recvbuf, int count,MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
int MPI_Gather(const void*sendbuf, int sendcount, MPI_Datatype sendtype,void*recvbuf, int recvcount, MPI_Datatype recvtype,int root, MPI_Comm comm)
int MPI_Scatter(const void*sendbuf, int sendcount, MPI_Datatype sendtype,void*recvbuf, int recvcount, MPI_Datatype recvtype,int root, MPI_Comm comm)
int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,int dest, int sendtag,void *recvbuf, int recvcount, MPI_Datatype recvtype,int source, int recvtag,MPI_Comm comm, MPI_Status *status)
~~~

Basic MPI usage:
~~~c
int my_rank;
int num_procs;
MPI_Init (&argc, &argv);
MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
MPI_Comm_size (MPI_COMM_WORLD, &num_procs);
~~~

## Odd-even transposition

MPI version:
~~~c
void odd_even_block_parallel (int m, int *sublist)
{
  int my_rank, n, i;
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &n);

  for (i=1; i<=n; i++) {
    if ((i%2)) {
      if ((my_rank+1)%2 && my_rank<(n-1))
        compare_split (m, sublist, my_rank, my_rank+1);
      else if  (!((my_rank+1)%2) && my_rank>0)
        compare_split (m, sublist, my_rank, my_rank-1);
    }
    else {
      if (!((my_rank+1)%2) && my_rank<(n-1))
        compare_split (m, sublist, my_rank, my_rank+1);
      else if  ((my_rank+1)%2 && my_rank>0)
        compare_split (m, sublist, my_rank, my_rank-1);
    }
  }
}

//Comment: "id" in the algorithm is assumed to be between 1 and n, so my_rank+1 actually works as "id".
~~~


## Bubble sort

~~~c
int compare_exchange(int *a, int *b) {
    int tmp;

    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
        return 1;
    } else {
        return 0;
    }
}

void bubble_sort(int n, int *a){

    int flag;

    for (int i = n; i > 1; i--) {
        flag = 0;
        for (int j = 0; j < i; j++) {
            if (compare_exchange(&a[j], &a[j+1])) {
                flag = 1;
            }
        }
        if (!flag) break;
    }

}
~~~

## MPI matrix-vector multiplication

~~~c
void para_matvec (int n, double** A, double *x, double *y){

    int i, j, p;
    double temp;
    MPI_COMM_SIZE (&p, MPI_COMM_WORLD);
    MPI_Bcast (x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for (int i = 0; i < n/p ; i++) {
        tmp = 0.0;
        for (int j = 0; j < n; j++) {
            tmp += A[i][j]*x[j];
        }
        y[i] = tmp;
    }
    MPI_Gather (y, n/p, MPI_DOUBLE, y, n/p, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}
~~~
