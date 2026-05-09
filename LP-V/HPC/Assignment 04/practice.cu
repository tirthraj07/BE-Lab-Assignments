#include <iostream>
#include <vector>
#include <cuda_runtime.h>
using namespace std;

// Define a Function that runs on GPU
__global__ void parallel_add(int* a, int* b, int* c, int n){
	// Given two vectors a and b
	// We are going to add them and then store its value in vector c
	// c[i] = a[i] + b[i]
	// n is the length of vectors

	// We want to run this parallely across multiple cores (parallel threads)
	// Each thread will correspond to one index
	// Therefore we must calculate the current index based on the thread that is executing it?
	// How are we going to do that you say? We use CUDA's Thread Hierarchy to deterministically calculate that (read this up from README.md)
	
	int i = blockIdx.x * blockDim.x + threadIdx.x;

	// Now it is possible that the number of threads > size of vector, so we might go out of bounds
	// Therefore we put a guard if (i<n) then calculate the sum
	
	if (i < n){
		c[i] = a[i] + b[i];
	}

}
// comments are more than the code lol :)


// Function to add the vectors on CPU (Simple addition function)
void add(vector<int>& a, vector<int>& b, vector<int>& c, int n){
	for(int i=0; i<n; i++){
		c[i] = a[i] + b[i];
	}
}

int main(){
	int n = 1000000;

	// Initialize the input vectors
	vector<int> a(n);
	vector<int> b(n);
	for(int i=0; i<n; i++){
		// Fill random values
		a[i] = i;
		b[i] = i * 2;
	}
	
	// Initialize two output vectors
	vector<int> c_cpu(n);	// This will contain the results when we run the vector addition on CPU
	vector<int> c_gpu(n);	// This will contain the results when we run the vector addition on GPU

	// Sequential CPU
	add(a, b, c_cpu, n);

	// Parallel GPU
	
	// Allocate memory first
	int *d_a, *d_b, *d_c;
	cudaMalloc(&d_a, n * sizeof(int));
	cudaMalloc(&d_b, n * sizeof(int));
	cudaMalloc(&d_c, n * sizeof(int));

	// Copy memory from Host(CPU) to Device(GPU)
	cudaMemcpy(d_a, a.data(), n*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b.data(), n*sizeof(int), cudaMemcpyHostToDevice);

	int threadsPerBlock = 256;
	int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

	parallel_add<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);

	cudaMemcpy(c_gpu.data(), d_c, n * sizeof(int), cudaMemcpyDeviceToHost);

	bool success = true;
        for(int i = 0; i < n; i++) {
            if(c_cpu[i] != c_gpu[i]) {
                success = false;
                break;
            }
        }
        if(success) cout << "Success! GPU matches CPU." << endl;
        else cout << "Mismatch found!" << endl;

	// Free up memory
	cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

	
	return 0;
}
