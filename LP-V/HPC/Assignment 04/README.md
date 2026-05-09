## Assignment 04 - CUDA Programming

### What is CUDA?

Your CPU has maybe 8-16 cores.   
It's designed for complex, sequential tasks — running your OS, handling logic, branching.Your GPU has thousands of cores. 

A typical NVIDIA GPU has 3000-10000+ cores. But each core is simple — it can only do basic math. No complex branching, no OS tasks.

```
CPU: 8 powerful cores
     good at: complex logic, sequential tasks

GPU: 4000 simple cores  
     good at: doing the SAME simple operation on THOUSANDS of values simultaneously
```

CUDA is NVIDIA's framework that lets you write code that runs on those thousands of GPU cores.



### The core idea — why vector addition is perfect for GPU
Sequential CPU thinking:

```
for i in 0 to 1000000:
    c[i] = a[i] + b[i]    ← one at a time, 1 million iterations
```

GPU thinking:
```
launch 1000000 threads simultaneously
each thread does exactly ONE addition: c[i] = a[i] + b[i]
all done in parallel
```
Every addition is independent — c[5] doesn't depend on c[4]. 
This is exactly what GPUs are built for.


### CUDA Thread Hierarchy

CUDA organizes threads in two levels.
Level 1 — Thread: The individual worker. Does one unit of work.
Level 2 — Block: A group of threads. Typically 256 threads per block.
Level 3 — Grid: A group of blocks. As many as you need.

```
Grid
├── Block 0
│   ├── Thread 0   → handles c[0]
│   ├── Thread 1   → handles c[1]
│   ├── Thread 2   → handles c[2]
│   └── ... Thread 255 → handles c[255]
├── Block 1
│   ├── Thread 0   → handles c[256]
│   ├── Thread 1   → handles c[257]
│   └── ... Thread 255 → handles c[511]
├── Block 2
│   └── ... handles c[512] to c[767]
└── ...
```

So each thread needs to know: which element am I responsible for?
```cpp
int i = blockIdx.x * blockDim.x + threadIdx.x;
```

blockIdx.x  = which block am I in?        (0, 1, 2, ...)  
blockDim.x  = how many threads per block? (256)  
threadIdx.x = which thread within block?  (0 to 255)  

Block 0, Thread 0:   i = 0   * 256 + 0   = 0  
Block 0, Thread 1:   i = 0   * 256 + 1   = 1  
Block 1, Thread 0:   i = 1   * 256 + 0   = 256  
Block 1, Thread 5:   i = 1   * 256 + 5   = 261  
Block 3, Thread 7:   i = 3   * 256 + 7   = 775  

Each thread computes its own i and handles exactly c[i].

### Memory — the most important practical concept
GPU and CPU have separate memory. They cannot directly read each other's RAM.

```
CPU RAM (Host)     GPU VRAM (Device)
┌──────────┐       ┌──────────┐
│  h_a[]   │       │  d_a[]   │
│  h_b[]   │       │  d_b[]   │
│  h_c[]   │       │  d_c[]   │
└──────────┘       └──────────┘
     ↑                   ↑
  your program        GPU kernel
  runs here           runs here
```

So the workflow is always:
```
1. Allocate memory on GPU    (cudaMalloc)
2. Copy data CPU → GPU       (cudaMemcpy HostToDevice)
3. Run kernel on GPU         (kernel<<<...>>>)
4. Copy result GPU → CPU     (cudaMemcpy DeviceToHost)
5. Free GPU memory           (cudaFree)
```

Now let's build the program step by step.

#### Step 1: Writing a kernel
A kernel is a function that runs on the GPU. You mark it with __global__:

```cpp
__global__ void vector_add_gpu(int* a, int* b, int* c, int n){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n){
        c[i] = a[i] + b[i];
    }
}
```

`__global__` means: called from CPU, runs on GPU.

The `if(i < n)` guard is because you might launch more threads than elements. 
For n=1000000 with 256 threads/block you need 3907 blocks = 1000192 threads. 
The extra 192 threads would access out-of-bounds memory without the guard.


#### Step 2: Allocating GPU memory

```cpp
int *d_a, *d_b, *d_c;
cudaMalloc(&d_a, n * sizeof(int));
cudaMalloc(&d_b, n * sizeof(int));
cudaMalloc(&d_c, n * sizeof(int));
```

`d_` prefix is a convention meaning "device" (GPU).   
`h_` means "host" (CPU).  
cudaMalloc works like malloc but allocates on the GPU.  

#### Step 3: Copying data to GPU
```cpp
// cudaMemcpy(destination, source, size, direction)
cudaMemcpy(d_a, h_a.data(), n * sizeof(int), cudaMemcpyHostToDevice);
cudaMemcpy(d_b, h_b.data(), n * sizeof(int), cudaMemcpyHostToDevice);
```

Direction can be:
cudaMemcpyHostToDevice   → CPU to GPU
cudaMemcpyDeviceToHost   → GPU to CPU

#### Step 4: Launching the kernel
```cpp
int threadsPerBlock = 256;
int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

vector_add_gpu<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);
```


#### Step 5: Timing Correctly
This is a common mistake. The kernel launch is asynchronous:

```cpp
vector_add_gpu<<<...>>>(d_a, d_b, d_c, n);
// CPU returns immediately here, GPU is still working
// So clock() would measure near-zero time.
```

You need CUDA events:

```cpp
cudaEvent_t start, stop;
cudaEventCreate(&start);
cudaEventCreate(&stop);

cudaEventRecord(start);                          // start timer on GPU timeline
vector_add_gpu<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);
cudaEventRecord(stop);                           // stop timer on GPU timeline

cudaEventSynchronize(stop);                      // CPU waits here until GPU is done

float gpu_time = 0;
cudaEventElapsedTime(&gpu_time, start, stop);    // time in milliseconds
```

`cudaEventSynchronize` is what forces the CPU to wait for the GPU to actually finish.

#### Step 6: Copy result back and free memory

```cpp
cudaMemcpy(h_c_gpu.data(), d_c, n * sizeof(int), cudaMemcpyDeviceToHost);

cudaFree(d_a);
cudaFree(d_b);
cudaFree(d_c);
```
Always free GPU memory just like you free heap memory in C.