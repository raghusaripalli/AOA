#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H
#define NEWLINE "\n"
#define TAB "\t"

#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    vector<int> *adj;
    int N;
    Graph(int n);
    ~Graph();

    // Algorithms
    void connected_components();
    void one_cycle();
    void shortest_paths(int source);

    // Helper for Algorithms
    void DFS(bool *visited, int v);
    bool findCycle(bool *visited, int v, int parent, vector<int> *path);

    // Graph Utilities
    void addEdge(int u, int v);
};
#endif