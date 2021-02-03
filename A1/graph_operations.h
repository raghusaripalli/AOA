#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H
#define NEWLINE "\n"

#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    unordered_map<int, list<int> *> *adj;
    int N;
    Graph(unordered_map<int, list<int> *> *g, int n)
    {
        adj = g;
        N = n;
    }
    ~Graph()
    {
        delete[] adj;
    }
    void connected_components();
    bool one_cycle();
    void shortest_paths();

    void DFS(unordered_set<int> *visited, int v);
    bool isCyclic(unordered_set<int> *visited, int v, int parent);
};

#endif