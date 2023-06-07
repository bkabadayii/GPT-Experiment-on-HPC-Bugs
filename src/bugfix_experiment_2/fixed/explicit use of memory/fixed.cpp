#include <stdio.h>
#include <omp.h>

#define SIZE 1000

int main() {
    int array[SIZE];
    int i, sum = 0;

    // Initialize the array
    for (i = 0; i < SIZE; i++) {
        array[i] = i;
    }

    double start_time = omp_get_wtime(); // Start measuring time

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < SIZE; i++) {
        sum += array[i];
    }

    double end_time = omp_get_wtime(); // Stop measuring time

    FILE *fp;
    fp = fopen("runtime.txt", "a");
    fprintf(fp, "%.6f\n", end_time - start_time);
    fclose(fp);

    return 0;
}