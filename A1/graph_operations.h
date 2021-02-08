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
    vector<int> *connected_components();
    vector<int> *one_cycle();
    vector<int> *shortest_paths(int source);

    // Helper for Algorithms
    void DFS(bool *visited, int v, vector<int> *cc, int cc_idx);
    bool findCycle(bool *visited, int v, int parent, vector<int> *path);

    // Graph Utilities
    void addEdge(int u, int v);
};
#endif