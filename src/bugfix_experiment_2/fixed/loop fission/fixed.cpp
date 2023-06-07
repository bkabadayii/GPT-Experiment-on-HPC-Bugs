#include <omp.h>
#include <stdio.h>

#define ARRAY_SIZE 1000

int main() {
    int i;
    int array[ARRAY_SIZE];

    // Initialize the array
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for
        for (i = 0; i < ARRAY_SIZE; i++) {
            // Perform computation on array element
            array[i] = array[i] * 2;
        }
    }

    #pragma omp parallel
    {
        // Some other parallel computation that depends on the modified array
        #pragma omp for
        for (i = 0; i < ARRAY_SIZE; i++) {
            // printf("%d\n", array[i]);
        }
    }

    double end_time = omp_get_wtime();
    double runtime = end_time - start_time;
    FILE *fp;
    fp = fopen("runtime.txt", "a");
    fprintf(fp, "%f\n", runtime);
    fclose(fp);

    return 0;
}