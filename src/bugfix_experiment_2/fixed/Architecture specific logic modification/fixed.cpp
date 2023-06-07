#include <iostream>
#include <chrono>
#include <omp.h>
#include <fstream>

int main() {
    int num_threads = 8;
    long long sum = 0;

    auto start_time = std::chrono::high_resolution_clock::now(); // Start runtime measurement

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        long long thread_sum = 0;

        #pragma omp for
        for (long long i = 0; i < 1000000000; i++) {
            // Architecture-specific logic modification
            // For example, incorrect usage of SIMD instructions
            int value = thread_id * i;
            thread_sum += value;
        }

        #pragma omp critical
        {
            sum += thread_sum;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // End runtime measurement
    std::chrono::duration<double> runtime = end_time - start_time;

    std::ofstream outfile;
    outfile.open("runtime.txt", std::ios_base::app);
    outfile << runtime.count() << std::endl;
    outfile.close();

    return 0;
}