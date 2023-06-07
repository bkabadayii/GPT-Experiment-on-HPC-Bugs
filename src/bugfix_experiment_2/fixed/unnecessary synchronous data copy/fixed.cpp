#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main() {
    int i, tid;
    int *data;
    int sum = 0;
    double start_time, end_time;

    // Allocate memory for data array
    data = (int*)malloc(N * sizeof(int));

    // Initialize data array
    for (i = 0; i < N; i++) {
        data[i] = i + 1;
    }

    start_time = omp_get_wtime();

    #pragma omp parallel private(i, tid) shared(data) reduction(+: sum)
    {
        tid = omp_get_thread_num();
        int local_sum = 0;

        // Each thread processes a portion of the data array
        #pragma omp for
        for (i = 0; i < N; i++) {
            local_sum += data[i];
        }

        #pragma omp atomic
        sum += local_sum;
    }

    end_time = omp_get_wtime();

    // Print the final sum and the runtime
    FILE *fp;
    fp = fopen("runtime.txt", "a");
    fprintf(fp, "%.6f\n", end_time - start_time);
    fclose(fp);

    // Free allocated memory
    free(data);

    return 0;
}