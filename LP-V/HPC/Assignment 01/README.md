## Assignment 01 - Parallel DFS and BFS on Graphs
  
How to run
```bash
g++ -fopenmp main.cpp
./a.out
```

If you are on windows, use WSL

This is the output (Results may vary across runs for parallel DFS)

```
--Adjacency list--
0 -> 1 2 3
1 -> 0 4 5
2 -> 0 6 7
3 -> 0 8 9
4 -> 1 10 6
5 -> 1 10 7
6 -> 2 11 4
7 -> 2 11 5
8 -> 3 11 10
9 -> 3 10 11
10 -> 4 5 9 8
11 -> 6 7 8 9
BFS: 0 1 2 3 4 5 6 7 8 9 10 11
BFS Parallel: 0 1 2 3 4 5 6 7 8 9 10 11
DFS: 0 3 9 11 8 10 5 7 2 6 4 1
DFS Parallel: 0 1 2 3 5 4 6 7 9 8 11 10
```
