#include "graph_operations.h"
#include "MinPQ.h"

void Graph::DFS(bool *visited, int v, vector<int> *cc, int cc_idx)
{
    // mark node 'v' as visited
    visited[v] = true;
    cc[cc_idx].push_back(v);

    // Iterate through all the nodes connected to 'v'
    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(visited, *i, cc, cc_idx);
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

vector<int> *Graph::connected_components()
{
    cout << "Connected Components" << NEWLINE;
    // Create visited arr and init it to false
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    // declare arr of vectors for connected components
    vector<int> *cc = new vector<int>[N];
    int cc_idx = 0;

    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            DFS(visited, i, cc, cc_idx);
            cc_idx++;
        }
    }
    // free visited
    delete visited;

    return cc;
}

vector<int> *Graph::one_cycle()
{
    cout << "One Cycle" << NEWLINE;

    // Create visited set
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    // Path vector
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

    // free visited and path
    delete visited;

    // If found return path else null
    if (found)
        return path;

    else
        return NULL;
}

vector<int> *Graph::shortest_paths(int source)
{
    cout << "Shortest Paths" << endl;

    // DS to hold paths, parent and distances
    int dist[N];
    int parent[N];
    vector<int> *paths = new vector<int>[N];

    MinPriorityQueue pq;

    struct MinPQ *minPQ = pq.newMinPQ(N);

    // Initializing dist, minPQ
    for (int v = 0; v < N; v++)
    {
        dist[v] = INT_MAX;
        parent[v] = -1;
        minPQ->array[v] = pq.newNode(v, dist[v]);
        minPQ->positionsForDecreaseKey[v] = v;
    }

    // Put the source Node into MinPQ
    minPQ->array[source] = pq.newNode(source, dist[source]);
    minPQ->positionsForDecreaseKey[source] = source;
    dist[source] = 0;
    parent[source] = -1;
    pq.decreaseKey(minPQ, source, dist[source]);

    minPQ->size = N;

    // Iterate until minPQ is empty
    while (!pq.isEmpty(minPQ))
    {
        // Extract the top element in the minPQ
        struct Node *node = pq.extractMin(minPQ);

        int u = node->vertex;

        dist[u] = node->distance;

        // Iterating over the neighbours of vertex 'u'
        vector<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = *i;
            // Compare distances from neighbours to source in minPQ
            // If the new dist is shorter update the minPQ, dist and parent
            if (pq.isInMinPQ(minPQ, v) && dist[u] != INT_MAX && 1 + dist[u] < dist[v])
            {
                dist[v] = dist[u] + 1;

                // update distance
                pq.decreaseKey(minPQ, v, dist[v]);

                // update parent
                parent[v] = u;
            }
        }
    }

    /*cout << "Parent" << endl;
    for (int i = 0; i < N; ++i)
    {
        cout << i << ":" << parent[i] << NEWLINE;
    }

    cout << "Distance" << endl;
    for (int i = 0; i < N; ++i)
    {
        cout << i << ":" << dist[i] << NEWLINE;
    }

    for (int i = 0; i < N; ++i)
    {
        int v = i;
        cout << i << ": [";
        while (parent[v] != -1)
        {
            cout << parent[v] << " ";
            v = parent[v];
        }
        cout << "]"
             << ";";
    }*/

    for (int i = 0; i < N; ++i)
    {
        int v = i;
        while (parent[v] != -1)
        {
            paths[i].push_back(parent[v]);
            v = parent[v];
        }
    }

    return paths;
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