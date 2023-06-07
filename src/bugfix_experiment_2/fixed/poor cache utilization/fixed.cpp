#include <stdio.h>
#include <omp.h>

#define N 10000
#define CHUNK_SIZE 100

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
        #pragma omp for schedule(static, CHUNK_SIZE)
        for (i = 0; i < N; i++) {
            sum += data[i];
        }
    }

    end_time = omp_get_wtime();

    // Print the final sum and the runtime
    FILE *fp;
    fp = fopen("runtime.txt", "a");
    fprintf(fp, "%.6f\n", end_time - start_time);
    fclose(fp);

    return 0;
}