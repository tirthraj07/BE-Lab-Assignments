/*
Code For Practical Exams

BFS Parallel: 
Level : 0 
[LOG] Thread 2 : Visited Node: 1
[LOG] Thread 2 : Visited Node: 2
[LOG] Thread 2 : Visited Node: 3
Level : 1 2 3 
[LOG] Thread 6 : Visited Node: 8
[LOG] Thread 3 : Visited Node: 4
[LOG] Thread 4 : Visited Node: 6
[LOG] Thread 6 : Visited Node: 9
[LOG] Thread 4 : Visited Node: 7
[LOG] Thread 3 : Visited Node: 5
Level : 8 9 6 7 4 5 
[LOG] Thread 5 : Visited Node: 11
[LOG] Thread 0 : Visited Node: 10
Level : 10 11 

DFS Parallel: 
[LOG] Thread 5 : 0
[LOG] Thread 7 : 1
[LOG] Thread 0 : 2
[LOG] Thread 2 : 3
[LOG] Thread 4 : 6
[LOG] Thread 1 : 9
[LOG] Thread 3 : 8
[LOG] Thread 4 : 11
[LOG] Thread 7 : 5
[LOG] Thread 3 : 4
[LOG] Thread 6 : 7
[LOG] Thread 0 : 10
*/

#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

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


        void bfs_parallel(int start){
            vector<int> visited(V, false);
            vector<int> currLevel;
            
            visited[start] = 1;
            currLevel.push_back(start);

            while(!currLevel.empty()){
                cout << "Level : ";
                for(int i=0; i<currLevel.size(); i++){
                    cout << currLevel[i] << " ";
                }
                cout << endl;

                vector<int> sharedNextLevel;
                
                // Execute the following block parallely
                #pragma omp parallel 
                {
                    vector<int> localNextLevel;
                    
                    // Execute for loop in parallel
                    #pragma omp for nowait schedule(dynamic)
                    for(int i=0; i<currLevel.size(); i++){
                        int curr = currLevel[i];
                        for(int j=0; j<adjList[curr].size(); j++){
                            int next = adjList[curr][j];
                            int hasBeenVisited = 0;
                            // Ensure that only one thread adds the next in its localNextLevel
                            #pragma omp atomic capture
                            {
                                hasBeenVisited = visited[next];
                                visited[next] = 1;
                            }
                            if(!hasBeenVisited){
                                #pragma omp critical
                                cout << "[LOG] Thread "<< omp_get_thread_num() << " : Visited Node: " << next << endl;
                                localNextLevel.push_back(next);
                            }
                        }

                    }

                    #pragma omp critical
                    sharedNextLevel.insert(sharedNextLevel.end(), localNextLevel.begin(), localNextLevel.end());
                }

                currLevel.swap(sharedNextLevel);
            }
            cout << endl;
        }

        void dfs_task(int node, vector<int>& visited){
            #pragma omp critical
            {
                cout << "[LOG] Thread " << omp_get_thread_num() << " : " << node << endl;
            }
            // Check chilren
            for(int i=0; i<adjList[node].size(); i++){
                int next = adjList[node][i];
                int hasBeenVisited = 0;
                #pragma omp atomic capture
                {
                    hasBeenVisited = visited[next];
                    visited[next] = 1;
                }
                if(!hasBeenVisited){
                    #pragma omp task firstprivate(next) shared(visited)
                    dfs_task(next, visited);
                }
            }
            #pragma omp taskwait 
        }

        void dfs_parallel(int start){
            vector<int> visited(V, 0);
            visited[start] = 1;

            #pragma omp parallel shared(visited)
            {   
                #pragma omp single
                dfs_task(start, visited);
            }
            cout << endl;
        }


};



int main(){
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

    cout << "BFS Parallel: \n";
    g.bfs_parallel(0);

    cout << "DFS Parallel: \n";
    g.dfs_parallel(0);

    return 0;
}