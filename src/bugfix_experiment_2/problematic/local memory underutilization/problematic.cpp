#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    int i, tid;
    int data[N];
    int sum = 0;
    double start_time, end_time;

    // Initialize data array
    for (i = 0; i < N; i++) {
        data[i] = i + 1;
    }

    start_time = omp_get_wtime();

    #pragma omp parallel private(i, tid) shared(data) reduction(+: sum)
    {
        tid = omp_get_thread_num();
        sum = 0;

        // Each thread processes a portion of the data array
        #pragma omp for
        for (i = 0; i < N; i++) {
            sum += data[i];
        }

        // Print the local sum for each thread
    }

    end_time = omp_get_wtime();

    // Print the final sum and the runtime
    printf("Local memory underutilization Runtime: %.6f seconds\n", end_time - start_time);

    return 0;
}
