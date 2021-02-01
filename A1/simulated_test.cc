#include "graph_operations.h"

void addEdge(vector<vector<int>> *graph, int v, int w)
{
    (*graph)[v].push_back(w);
    (*graph)[w].push_back(v);
}

int main()
{
    // fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // redirect stdout to output.txt
    freopen("output.txt", "w", stdout);

    int N = 5;
    vector<vector<int>> *graph = new vector<vector<int>>(N);
    for (int i = 0; i < N; i++)
    {
        vector<int> *x = new vector<int>();
        graph->push_back(*x);
    }
    addEdge(graph, 1, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 3);
    connected_components(graph, N);
    one_cycle();
    shortest_paths();
    delete graph;
}