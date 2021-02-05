#include "graph_operations.h"
#include "MinHeap.h"

void Graph::DFS(bool *visited, int v)
{
    // mark node 'v' as visited
    visited[v] = true;
    cout << v << " ";

    // Iterate through all the nodes connected to 'v'
    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(visited, *i);
}

bool Graph::findCycle(bool *visited, int v, int parent, vector<int> *path)
{
    // mark node 'v' as visited
    visited[v] = true;

    // Iterate through all the nodes connected to 'v'
    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
        {
            if (findCycle(visited, *i, v, path))
            {
                // Min 3 nodes form cycle
                if (path->size() < 2 || path->front() != path->back())
                    path->push_back(v);
                return true;
            }
        }
        // Check whether it's the parent or not
        else if (*i != parent)
        {
            path->push_back(*i);
            path->push_back(v);
            return true;
        }
    }
    return false;
}

void Graph::connected_components()
{
    cout << "Connected Components" << NEWLINE;
    // Create visited arr and init it to false
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            DFS(visited, i);
            cout << NEWLINE;
        }
    }
    // free visited
    delete visited;
}

void Graph::one_cycle()
{
    cout << "One Cycle" << NEWLINE;
    // Create visited set
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    vector<int> *path = new vector<int>();
    bool found = false;
    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            if (findCycle(visited, i, -1, path))
            {
                found = true;
                break;
            }
        }
    }

    if (found)
    {
        cout << "Cycle Found:" << NEWLINE;
        vector<int>::iterator i;
        for (i = path->begin(); i != path->end(); ++i)
            cout << *i << " ";
        cout << NEWLINE;
    }
    else
    {
        cout << "Cycle Not Found." << NEWLINE;
    }

    // free visited and path
    delete visited;
}

void Graph::shortest_paths(int source)
{
    cout << "Shortest Paths" << NEWLINE;
    int dist[N];
    int parent[N];
    vector<int> *paths[N];

    MinPriorityQueue pq;

    struct MinHeap *minHeap = pq.createMinHeap(N);

    for (int v = 0; v < N; v++)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = pq.newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Distance from source to itself is zero
    minHeap->array[source] = pq.newMinHeapNode(source, dist[source]);
    minHeap->pos[source] = source;
    dist[source] = 0;
    parent[source] = -1;
    pq.decreaseKey(minHeap, source, dist[source]);

    // Initially size of min heap is equal to V
    minHeap->size = N;

    // Loop till min heap is empty
    while (!pq.isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode *minHeapNode = pq.extractMin(minHeap);

        // Store the extracted vertex
        int u = minHeapNode->v;

        // update shortest distance of current vertex from source vertex
        dist[u] = minHeapNode->dist;

        // Traverse through all adjacent vertices of u (the extracted vertex) and update their distance values
        vector<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = *i;
            if (pq.isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 1 + dist[u] < dist[v])
            {
                dist[v] = dist[u] + 1;

                // update distance
                pq.decreaseKey(minHeap, v, dist[v]);

                // update parent
                parent[v] = u;
            }
        }
    }

    /*
    cout << "Parent" << endl;
    for (int i = 0; i < N; ++i)
    {
        cout << i << ":" << parent[i] << NEWLINE;
    }

    cout << "Distance" << endl;
    for (int i = 0; i < N; ++i)
    {
        cout << i << ":" << dist[i] << NEWLINE;
    }
    */

   for (int i = 0; i < N; ++i)
    {
        int v = i;
        cout << i << ": [";
        while (parent[v] != -1)
        {
            cout << parent[v] << " ";
            v = parent[v];
        }
        cout << "]" << NEWLINE;
    }
    
    /*for (int i = 0; i < N; ++i)
    {
        int v = i;
        vector<int> *shortest_path = new vector<int>();
        while (parent[v] != -1)
        {
            shortest_path->push_back(parent[v]);
            v = parent[v];
        }
        paths[i] = shortest_path;
    }

    cout << "Shortest Paths:" << endl;
    for (int i = 0; i < N; i++)
    {

        cout << i << ":[";
        for (auto j = paths[i]->begin(); j != paths[i]->end(); ++j)
        {
            cout << *j << " ";
        }
        cout << "]" << NEWLINE;
    }*/
}

Graph::Graph(int n)
{
    N = n;
    adj = new vector<int>[N];
}
Graph::~Graph() {}


void Graph::addEdge(int u, int v)
{
    adj[v].push_back(u);
    adj[u].push_back(v);
}