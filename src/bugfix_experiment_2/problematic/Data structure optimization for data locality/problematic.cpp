#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000000


void process_array(int *array) {
    #pragma omp parallel for
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = array[i] * 2;
    }
}

int main() {
    int array[ARRAY_SIZE];

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    double start_time = omp_get_wtime(); // Start runtime measurement

    process_array(array);

    double end_time = omp_get_wtime(); // End runtime measurement
    double runtime = end_time - start_time;

    printf("Data structure optimization for data locality Runtime: %f seconds\n", runtime);

    return 0;
}


