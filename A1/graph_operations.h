#ifndef GRAPH_OPERATIONS_H
#define GRAPH_OPERATIONS_H
#define NEWLINE "\n"
#define TAB "\t"

#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    unordered_map<int, list<int> *> *adj;
    int N;
    Graph(unordered_map<int, list<int> *> *g, int n);
    ~Graph();
    void connected_components();
    void one_cycle();
    void shortest_paths(int source);

    void DFS(unordered_set<int> *visited, int v);
    bool findCycle(unordered_set<int> *visited, int v, int parent, vector<int> *path);
};

#endif