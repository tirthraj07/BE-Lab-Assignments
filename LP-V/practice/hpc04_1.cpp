%%writefile vector_add.cu
#include <iostream>
#include <vector>
#include <cuda_runtime.h>
using namespace std;


__global__ void vector_add_gpu(int* a, int* b, int* c, int n){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n) c[i] = a[i] + b[i];
}

// Runs on CPU — sequential loop
void vector_add_cpu(vector<int>& a, vector<int>& b, vector<int>& c, int n){
    for(int i = 0; i < n; i++) c[i] = a[i] + b[i];
}

int main(){
    int n = 1000000;

    // Host (CPU) memory
    vector<int> h_a(n), h_b(n), h_c_cpu(n), h_c_gpu(n);
    for(int i = 0; i < n; i++){ h_a[i] = i; h_b[i] = i * 2; }

    // Sequential
    clock_t cpu_start = clock();
    vector_add_cpu(h_a, h_b, h_c_cpu, n);
    clock_t cpu_end = clock();
    double cpu_time = (double)(cpu_end - cpu_start) / CLOCKS_PER_SEC * 1000;
    cout << "Sequential: " << cpu_time << " ms" << endl;

    // Parallel
    int *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, n * sizeof(int));          // allocate GPU memory
    cudaMalloc(&d_b, n * sizeof(int));
    cudaMalloc(&d_c, n * sizeof(int));

    cudaMemcpy(d_a, h_a.data(), n * sizeof(int), cudaMemcpyHostToDevice);  // CPU → GPU
    cudaMemcpy(d_b, h_b.data(), n * sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);

    vector_add_gpu<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);  // launch

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float gpu_time = 0;
    cudaEventElapsedTime(&gpu_time, start, stop);
    cout << "Parallel (GPU): " << gpu_time << " ms" << endl;

    cudaMemcpy(h_c_gpu.data(), d_c, n * sizeof(int), cudaMemcpyDeviceToHost);  // GPU → CPU

    // Verify
    bool correct = true;
    for(int i = 0; i < n; i++) if(h_c_cpu[i] != h_c_gpu[i]){ correct = false; break; }
    cout << "Correct: " << (correct ? "YES" : "NO") << endl;
    cout << "Speedup: " << cpu_time / gpu_time << "x" << endl;

    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
    return 0;
}
