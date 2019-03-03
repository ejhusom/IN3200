#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b);
void sort(int arr[], int beg, int end, int perm[]);

int main(int argc, char const *argv[]) {

  int N = 10;
  int arr[N];
  int perm[N];

  srand(time(NULL));

  for (size_t i = 0; i < N; i++) {
    arr[i] = rand() % 100;
    perm[i] = i;
    printf("%d\n", arr[i]);
  }

  sort(arr, 0, N, perm);

  // Check if array is sorted by printing it out
  printf("========\n");
  for (size_t i = 0; i < N; i++) {
    printf("%d\n", arr[perm[i]]);
  }

  return 0;
}

void swap(int *a, int *b){
  int t=*a; *a=*b; *b=t;
}

void sort(int arr[], int beg, int end, int perm[]){
  if (end > beg + 1) {
    int piv = arr[perm[beg]], l = beg + 1, r = end;
    while (l < r) {
      if (arr[perm[l]] <= piv)
        l++;
      else
        swap(&perm[l], &perm[--r]);
        // swap(&arr[l], &arr[--r]);
    }
    swap(&perm[--l], &perm[beg]);
    // swap(&arr[--l], &arr[beg]);
    sort(arr, beg, l, perm);
    sort(arr, r, end, perm);
  }
}
