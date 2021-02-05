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
    Graph(vector<int> *g, int n);
    ~Graph();
    void connected_components();
    void one_cycle();
    void shortest_paths(int source);

    void DFS(bool *visited, int v);
    bool findCycle(bool *visited, int v, int parent, vector<int> *path);
};

#endif