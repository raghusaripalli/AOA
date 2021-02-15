#include "graph_simulator.h"

/*
 The vertices are integers from 0 through n − 1. The vertices u and v are connected by an
 edge if u − v = ±1 or u − v = ±(n − 1). There is one connected component, every shortest path has
 length at most n/2, and there is a unique cycle of length n.
*/
Graph nCycle(int N)
{
    Graph g(N);
    for (int i = 1; i < g.N; i++)
    {
        g.addEdge(i, i - 1);
    }
    g.addEdge(0, g.N - 1);
    return g;
}

/*
 The vertices are integers from 0 through n − 1. Every pair of distinct
 vertices forms an edge. There is one connected component, every shortest path has unit length, and
 there are many cycles.
*/
Graph completeGraph(int N)
{
    Graph g(N);
    for (int i = 0; i < g.N; i++)
    {
        for (int j = i + 1; j < g.N; j++)
        {
            g.addEdge(i, j);
        }
    }
    return g;
}

/*
 The vertices are integers from 0 through n − 1. There are no edges.
 There are n connected components, no paths, and no cycles
*/
Graph emptyGraph(int N)
{
    Graph g(N);
    return g;
}