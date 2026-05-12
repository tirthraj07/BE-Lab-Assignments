#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <omp.h>
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


    void bfs(int start){
        vector<bool> visited(V, false);
        
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while(!q.empty()){
            int curr = q.front();
            q.pop();
            cout << curr << " ";
            
            vector<int> neighbours = adjList[curr];
            for(int next : neighbours){
                if(visited[next]) continue;
                q.push(next);
                visited[next] = true;
            }
        }
        cout << endl;
    }

    void bfs_parallel(int start){
        vector<int> visited(V, 0);
        visited[start] = 1;
        vector<int> currLevel = {start};

        while(!currLevel.empty()){

            cout << "Level ";
            for(int node: currLevel) cout << node << " ";
            cout << endl;

            vector<int> nextLevel;

            #pragma omp parallel
            {
                vector<int> localNextLevel;

                #pragma omp for nowait schedule(dynamic)
                for(int i=0; i<currLevel.size(); i++){
                    int node = currLevel[i];

                    for(int j=0; j<adjList[node].size(); j++){
                        int next = adjList[node][j];
                        int old;
                        #pragma omp atomic capture
                        {
                            old = visited[next];
                            visited[next] = 1;
                        }

                        if(old == 0){
                            #pragma omp critical
                            cout << "[INFO] Thread " << omp_get_thread_num() << ": added " << next << endl;
                            localNextLevel.push_back(next);
                        }
                    }

                }

                #pragma omp critical
                nextLevel.insert(nextLevel.end(), localNextLevel.begin(), localNextLevel.end());
            }

            currLevel.swap(nextLevel);
        }   
        
    }

    void dfs(int start){
        vector<bool> visited(V, false);
        stack<int> st;
        st.push(start);
        visited[start] = true;
        while(!st.empty()){
            int curr = st.top();
            st.pop();
            cout << curr << " ";
            vector<int> neighbours = adjList[curr];
            for(int next: neighbours){
                if(visited[next]) continue;
                st.push(next);
                visited[next] = true;
            }
        }
        cout << endl;
    }


    void dfs_task(int node, vector<int>& visited){
        #pragma omp critical
        cout << node << " ";

        for(int i=0; i < adjList[node].size(); i++){
            int next = adjList[node][i];
            int old = 0;
            #pragma omp atomic capture
            {
                old = visited[next];
                visited[next] = 1;
            }
            if(old == 0){
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
    }


};


int main(){
    Graph g(12);
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

    g.bfs(0);
    g.dfs(0);

    g.bfs_parallel(0);
    g.dfs_parallel(0);

}