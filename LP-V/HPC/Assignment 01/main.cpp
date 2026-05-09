/*
Assignment 01: Parallel DFS and BFS
Design and implement Parallel Breadth First Search and Depth First Search using OpenMP. 
Use a Tree or an undirected graph. 
Measure the performance of sequential and parallel algorithms.
*/

#include <iostream>
#include <omp.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/*
What is OpenMP?
OpenMP is an API that is used to write parallel programs in C, C++, and Fortran.
It is a free and open standard for shared-memory parallel programming in C/C++ and Fortran.
It is supported by many compilers, including GCC, Clang, and Intel.
It is supported by many operating systems, including Linux, Windows, and macOS.
It is supported by many architectures, including x86, x86_64, and ARM.

Instead of writing complex, low-level threading code from scratch (like managing raw POSIX threads or Windows threads), 
OpenMP allows developers to add simple compiler directives to their existing sequential code to tell the compiler 
to execute certain blocks in parallel.

OpenMP is designed strictly for shared-memory architectures. 
This means all the threads created by OpenMP share the same physical memory space and can read/write to the same variables. 
It is ideal for multi-core processors, but it cannot be used to parallelize code across multiple separate computers over a 
network (which requires a different standard like MPI—Message Passing Interface).

The Fork-Join Execution Model
OpenMP programs always begin as a single thread of execution, known as the MASTER thread.
Fork: 
    When the master thread encounters a parallel region in the code, 
    it "forks" (creates or awakens) a team of worker threads. 
    The workload is divided among this team, and they execute the code block simultaneously.

Join:
    Once the parallel block is complete, the worker threads synchronize and terminate (or go to sleep), 
    and only the master thread continues past that point.


Compiler Directives (#pragma)
The magic of OpenMP lies in its ease of use. You primarily interact with it using compiler directives (pragmas).
For example, if you have a massive loop that processes data, a normal C++ loop looks like this:
for (int i = 0; i < 1000000; i++) {
    // Heavy computation on data[i]
}

To parallelize this with OpenMP, you just add one line above it:
#pragma omp parallel for
for (int i = 0; i < 1000000; i++) {
    // Heavy computation on data[i]
}
If your CPU has 8 cores, OpenMP will automatically divide the 1,000,000 iterations among 8 threads


Every OpenMP directive begins with #pragma omp.
Creating Threads & Sharing Work - #pragma omp parallel
This is the fundamental directive. It tells the compiler to fork a team of threads. Every thread in the team will execute the block of code inside the parallel region.

#pragma omp for (and #pragma omp parallel for)
This is the workhorse of OpenMP. It takes a standard for loop and divides its iterations across the existing team of threads. 
You will almost always see it combined with parallel to create the threads and divide the work in one line.
By default, OpenMP places an implicit barrier at the end of every omp for loop. This means all threads must wait at the end of the loop until the very last thread finishes its portion of the work.
Adding nowait removes this barrier.

schedule(dynamic, chunk_size)
This controls how the iterations of the loop are handed out to the threads.
dynamic: Instead of dividing the loop up front (static scheduling), OpenMP acts like a manager handing out tasks on the fly. 
When a thread finishes its work, it goes back to the manager and asks for more.
64 (Chunk Size): Instead of asking for 1 iteration at a time (which causes too much overhead), 
threads ask for chunks of 64 iterations at a time.


Synchronization - #pragma omp critical
This creates a "critical section." It guarantees that only one thread at a time can execute the following block of code. It's useful for safely updating shared variables or writing to standard output without the text getting jumbled.

#pragma omp atomic
This is a faster, more lightweight version of critical, but it only applies to a single, simple memory update (like +=, -=, ++, --). Hardware-level atomic operations are used, making it highly efficient.

#pragma omp barrier
This forces all threads to wait at a specific point in the code. No thread can continue past the barrier until all threads have reached it

#pragma omp single
This directive is used inside an already existing parallel region. It tells OpenMP that the next block of code should be executed by only one thread in the team, rather than all of them.

#pragma omp shared(variable_list)
This explicitly tells the compiler that the variables listed inside the parentheses are shared among all the threads in the team. They all point to the exact same location in the computer's memory.

*/

class Graph {
    private:
        int V;
        vector<vector<int>> adjList;
    
    public:
        Graph(int V){
            this->V = V;
            adjList.resize(V);
        }

        void add_edge(int u, int v){
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        void print_adj_list(){
            cout << "--Adjacency list--" << endl;
            for(int i=0; i<V; i++){
                cout << i << " -> ";
                for(int j=0; j<adjList[i].size(); j++){
                    cout << adjList[i][j] << " ";
                }
                cout << endl;
            }
        }

        void bfs(int start){
            vector<bool> visited = vector<bool>(V, false);
            queue<int> q;
            visited[start] = true;
            q.push(start);
            while(!q.empty()){
                int curr = q.front();
                q.pop();
                cout << curr << " ";

                for(int i=0; i<adjList[curr].size(); i++){
                    int next = adjList[curr][i];
                    if(!visited[next]){
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }
            cout << endl;
        }

        /*
            To make bfs_parallel genuinely parallel with OpenMP, we need to restructure it around BFS frontiers (process all nodes at a given depth in parallel), because the classic queue-based BFS loop is inherently sequential.
            Understand the bottleneck - We are keeping a single queue shared across all threads, which is a bottleneck.

            Instead of one shared queue, BFS runs in levels:
            frontier: all nodes at current distance
            each level: expand all nodes in frontier in parallel
            build nextFrontier for the next level
            repeat
        */

        void bfs_parallel(int start) {
            // use vector<int> for OpenMP atomics. 
            // In C++, vector<bool> is heavily optimized to pack bits, making it completely thread-unsafe for concurrent access.
            vector<int> visited(V, 0);          
            vector<int> frontier;

            frontier.push_back(start);
            visited[start] = 1;
            
            while (!frontier.empty()) {
                // print this level (order inside level may vary)
                for (int v : frontier) cout << v << " ";

                // nextFrontier is a single shared vector that all threads need to write to.
                vector<int> nextFrontier;

                #pragma omp parallel        // spawn 4 threads (in a 4-core CPU. Number of threads = number of cores)
                {                           // every thread executes the entire block. There's no automatic distribution — all threads run the same code.
                    vector<int> localNext;  // each thread gets its OWN localNext (stack variable)

                    
                    // #pragma omp for NOW split the loop iterations across those 4 threads
                    #pragma omp for nowait schedule(dynamic)
                    for (int i = 0; i < frontier.size(); i++) {
                        int curr = frontier[i];
                        for (int j = 0; j < adjList[curr].size(); j++) {
                            int next = adjList[curr][j];
                            int old;
                            /*
                                The core problem: 
                                Two threads might discover the same neighbor next simultaneously. Scenario:
                                    Thread 1: reads visited[5] → 0  (not visited)
                                    Thread 2: reads visited[5] → 0  (not visited)
                                    Thread 1: sets visited[5] = 1
                                    Thread 2: sets visited[5] = 1
                                    Both threads add 5 to their localNext → node visited TWICE
                                This is a classic race condition.

                                What atomic capture does:
                                It makes the read-then-write a single uninterruptible operation. 
                                No other thread can sneak in between the read and the write.

                                So the same scenario now becomes:
                                    Thread 1: atomically reads visited[5]=0, sets visited[5]=1, returns old=0
                                    Thread 2: atomically reads visited[5]=1, sets visited[5]=1, returns old=1
                                    Thread 1: old==0 → adds 5 to localNext ✓
                                    Thread 2: old==1 → skips ✓
                                Exactly one thread wins, the rest see the updated value and skip.
                                
                                Why atomic capture specifically?

                                There are a few atomic variants:
                                    #pragma omp atomic write — just atomically write a value
                                    #pragma omp atomic read — just atomically read a value
                                    #pragma omp atomic update — atomically modify (x++, x += n, etc.)
                                    #pragma omp atomic capture — atomically modify and capture the old (or new) value into a variable
                                
                                You need capture here because the logic depends on what the value was before you changed it. 
                                The old value tells you whether you were the first thread to claim that node.
                                atomic vs critical — why not just use critical here?
                                Critical is slower than atomic. It acquires a GLOBAL lock → all threads stall
                                Atomic is faster because it uses hardware-level atomic operations → no locking overhead
                            */
                            #pragma omp atomic capture
                            { 
                                old = visited[next]; // Automically read the visited[next] value. If the value is 0, it means the node is not visited.
                                visited[next] = 1; // Atomically set the visited[next] value to 1.
                            }
                            if (old == 0) { // If the node is not visited, add it to the localNext vector.
                                localNext.push_back(next);
                            }
                        }
                    }
                    /*
                    Why nowait?
                    By default, OpenMP places an implicit barrier at the end of every omp for loop. 
                    This means all threads must wait at the end of the loop until the very last thread finishes its portion of the work.
                    Adding nowait removes this barrier.
                    Without nowait, all threads would finish their loops, stand around doing nothing, and then suddenly all 
                    try to enter the critical section at the exact same time, creating a massive traffic jam. With nowait, 
                    threads enter the critical section as soon as they finish, staggering their arrival times and drastically reducing 
                    lock contention.
                    ------------------------------------------------------------------------------------------------
                    Why dynamic scheduling?
                    In a graph, workloads are highly unbalanced. One node might have 2 neighbors (taking 1 microsecond to process), 
                    while another node might be a "super-hub" with 10,000 neighbors.
                    If you used standard static scheduling, Thread A might get 1,000 super-hub nodes, while Thread B gets 1,000 nodes 
                    with no neighbors. Thread B would finish in a millisecond and sit idle, while Thread A works for an hour.
                    With schedule(dynamic, 64), if Thread B finishes its 64 nodes instantly, it immediately grabs the next 64 nodes 
                    from the pool. Faster threads naturally pick up more chunks, ensuring all CPU cores stay at 100% utilization until 
                    the entire frontier is processed.
                    ------------------------------------------------------------------------------------------------
                    */
                    
                    // This runs one thread at a time
                    #pragma omp critical
                    nextFrontier.insert(nextFrontier.end(), localNext.begin(), localNext.end());

                    /*
                        std::vector::insert is not thread-safe — if two threads call it simultaneously:
                        Thread 1: insert() → resizes internal buffer
                        Thread 2: insert() → also resizes, or writes to now-invalid memory → crash / corruption

                        #pragma omp critical - It creates a global mutex — only one thread can execute this line at a time. 
                        The other threads queue up and wait their turn.                        
                    */
                }

                // swap exchanges the internal contents of two vectors — pointer, size, and capacity — in O(1) time. No elements are copied.
                frontier.swap(nextFrontier); 
            }
            cout << endl;
        }

        void dfs(int start){
            vector<bool> visited = vector<bool>(V, false);
            stack<int> s;
            s.push(start);
            while(!s.empty()){
                int curr = s.top();
                s.pop();
                if(visited[curr]) continue;
                visited[curr] = true;
                cout << curr << " ";
                for(int i=0; i<adjList[curr].size(); i++){
                    int next = adjList[curr][i];
                    if(!visited[next]){
                        s.push(next);
                    }
                }
            }
            cout << endl;
        }

        /*
            DFS has the same core bottleneck as BFS
            A Single shared worklist stack<int> s and a shared visited that would race as soon as multiple threads participate
            Also, “true DFS order” is inherently sequential; when you parallelize it you typically get a parallel depth-first–style traversal, not a deterministic textbook DFS order.
        
            What “parallel DFS” usually means
            Instead of one loop popping from one stack, you switch to task parallelism:
                Start from start
                When you visit a node, you spawn tasks to explore its neighbors
                Use an atomic test-and-set on visited so only one thread “claims” each node
        */

        void dfs_task(int curr, vector<int>& visited){
            // prints start node
            #pragma omp critical
            cout << curr << " ";
        
            for(int next : adjList[curr]){
                int old;
                #pragma omp atomic capture
                { 
                    old = visited[next]; 
                    visited[next] = 1; 
                }
        
                if(old == 0){
                    // spawn child tasks
                    #pragma omp task firstprivate(next) shared(visited)
                    dfs_task(next, visited);

                    /*
                        Packages dfs_task(next, visited) as a task unit and throws it into a shared task queue. 
                        The current thread does NOT execute it immediately — it just registers it and moves on to the next neighbor.

                        firstprivate(next): This is the critical part.
                        next is a loop variable — it changes every iteration. By the time a thread picks up the task from the queue, the loop may have already moved to the next iteration and next has a different value.
                        Without firstprivate:
                            Iteration 1: next=6, task created, next gets captured by reference
                            Iteration 2: next=7, next changes
                            Thread picks up task → reads next → gets 7 instead of 6 → WRONG
                        With firstprivate:
                            Iteration 1: next=6, task created, a COPY of next=6 is made for this task
                            Iteration 2: next=7, task created, a COPY of next=7 is made for this task
                            Each task has its own private snapshot of next → correct
                        It's essentially saying "capture the current value of next at task creation time", not at task execution time.
                    */
                }
            }
            #pragma omp taskwait    // ← wait here until all child tasks finish
            // It ensures the recursion is complete before unwinding. Without it the DFS would return before finishing.
        }
        
        void dfs_parallel(int start){        
            // use vector<int> for OpenMP atomics.
            vector<int> visited(V, 0);
            visited[start] = 1;
        
            #pragma omp parallel shared(visited)    // spawns 4 threads:
            {
                #pragma omp single  // only one thread runs dfs_task
                dfs_task(start, visited);
                /*
                    Why do you need omp single? 
                    Because if all 4 threads called dfs_task(start) simultaneously you'd spawn 4 root tasks 
                    and traverse the graph 4 times.
                    We would do parallelism inside of dfs_task
                */
            }
        
            cout << endl;
        }

};



int main() {
    Graph g = Graph(12);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(0, 3);
    g.add_edge(1, 4);
    g.add_edge(1, 5);
    g.add_edge(2, 6);
    g.add_edge(2, 7);
    g.add_edge(3, 8);
    g.add_edge(3, 9);
    g.add_edge(4, 10);
    g.add_edge(5, 10);
    g.add_edge(6, 11);
    g.add_edge(7, 11);
    g.add_edge(8, 11);
    g.add_edge(9, 10);
    g.add_edge(4, 6);
    g.add_edge(5, 7);
    g.add_edge(8, 10);
    g.add_edge(9, 11);

    g.print_adj_list();

    cout << "BFS: ";
    g.bfs(0);

    cout << "BFS Parallel: ";
    g.bfs_parallel(0);

    cout << "DFS: ";
    g.dfs(0);

    cout << "DFS Parallel: ";
    g.dfs_parallel(0);

    return 0;
}