%%writefile matrix_add.cu
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cuda_runtime.h>

using namespace std;
using namespace std::chrono;

__global__ void multiply(int *A, int *B, int *C, int size) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    // This bounds check protects us if the grid is larger than the matrix
    if (row < size && col < size) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += A[row * size + i] * B[i * size + col];  
        }
        C[row * size + col] = sum;
    }
}

void initialize(int *matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = rand() % 10;
    }
}

void print(int *matrix, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            cout << matrix[row * size + col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    srand(time(0));

    int N = 3; // Try scaling this up to 100 or 1000!
    int matrixSize = N * N;
    size_t matrixBytes = matrixSize * sizeof(int);

    int *A = new int[matrixSize];
    int *B = new int[matrixSize];
    int *C = new int[matrixSize];

    initialize(A, N);
    initialize(B, N);

    cout << "Matrix A: \n";
    print(A, N);
    cout << "Matrix B: \n";
    print(B, N);

    int *X, *Y, *Z;
    // Safely cast to void** for maximum compiler compatibility
    cudaMalloc((void**)&X, matrixBytes);
    cudaMalloc((void**)&Y, matrixBytes);
    cudaMalloc((void**)&Z, matrixBytes);

    cudaMemcpy(X, A, matrixBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B, matrixBytes, cudaMemcpyHostToDevice);

    // Standard CTA dimension (16x16 = 256 threads per block)
    int THREADS = 16; 

    // FIX 1: Robust grid calculation using ceiling division
    int BLOCKS = (N + THREADS - 1) / THREADS;

    dim3 threads(THREADS, THREADS);  
    dim3 blocks(BLOCKS, BLOCKS);  

    auto start = high_resolution_clock::now();
    
    // Launch kernel
    multiply<<<blocks, threads>>>(X, Y, Z, N);
    
    // FIX 2: Synchronize to ensure the GPU is done before stopping the clock
    cudaDeviceSynchronize();
    auto stop = high_resolution_clock::now();

    // Now copy the results back
    cudaMemcpy(C, Z, matrixBytes, cudaMemcpyDeviceToHost);

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Multiplication A x B: \n";
    print(C, N);
    cout << "Compute Time: " << duration.count() << " microseconds" << endl;

    delete[] A; delete[] B; delete[] C;
    cudaFree(X); cudaFree(Y); cudaFree(Z);

    return 0;
}