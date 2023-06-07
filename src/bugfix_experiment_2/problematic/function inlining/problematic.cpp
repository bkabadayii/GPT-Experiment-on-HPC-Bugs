#include <stdio.h>
#include <omp.h>

// Function that needs inlining fix
inline int compute_sum(int a, int b) {
    return a + b;
}

int main() {
    int sum = 0;
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 10; ++i) {
        int result = compute_sum(i, i + 1);
        sum += result;
    }

    end_time = omp_get_wtime();
    double runtime = end_time - start_time;

    printf("Function inlining Runtime: %.6f seconds\n", runtime);

    return 0;
}
