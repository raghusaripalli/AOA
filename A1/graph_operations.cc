#include "graph_operations.h"

using namespace std;

void DFS(vector<vector<int>> *graph, bool *visited, int v)
{
    // mark node 'v' as visited
    visited[v] = true;
    cout << v << " ";
    
    // Iterate through all the nodes connected to 'v'
    vector<int>::iterator i;
    for (i = (*graph)[v].begin(); i != (*graph)[v].end(); ++i)
        if (!visited[*i])
            DFS(graph, visited, *i);
}

void connected_components(vector<vector<int>> *graph, int N)
{
    // Create and initializa visited arr to false
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            DFS(graph, visited, i);
            cout << endl;
        }
    }
    // free visited array
    delete[] visited;
}

void one_cycle()
{
    cout << "OC" << endl;
}

void shortest_paths()
{
    cout << "SP" << endl;
}