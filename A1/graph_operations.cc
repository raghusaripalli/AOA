#include "graph_operations.h"
#include "MinHeap.h"

void Graph::DFS(unordered_set<int> *visited, int v)
{
    // mark node 'v' as visited
    visited->insert(v);
    cout << v << " ";

    // Iterate through all the nodes connected to 'v'
    list<int>::iterator i;
    for (i = (*adj)[v]->begin(); i != (*adj)[v]->end(); ++i)
        if (visited->find(*i) == visited->end())
            DFS(visited, *i);
}

bool Graph::findCycle(unordered_set<int> *visited, int v, int parent, vector<int> *path)
{
    // mark node 'v' as visited
    visited->insert(v);

    // Iterate through all the nodes connected to 'v'
    list<int>::iterator i;
    for (i = (*adj)[v]->begin(); i != (*adj)[v]->end(); ++i)
    {
        if (visited->find(*i) == visited->end())
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
    // Create visited set
    unordered_set<int> *visited = new unordered_set<int>();

    for (auto it = adj->begin(); it != adj->end(); ++it)
    {
        int i = it->first;
        if (visited->find(i) == visited->end())
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
    // Create visited set
    unordered_set<int> *visited = new unordered_set<int>();
    vector<int> *path = new vector<int>();
    bool found = false;
    for (int i = 0; i < N; i++)
    {
        if (visited->find(i) == visited->end())
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
    delete path;
}

void Graph::shortest_paths(int source)
{
    unordered_map<int, int> dist;
    map<int, int> parent;
    map<int, list<int>*>* paths = new map<int, list<int>*>(); 

    MinPriorityQueue pq;

    struct MinHeap *minHeap = pq.createMinHeap(N);

    for (auto it = adj->begin(); it != adj->end(); ++it)
    {
        int v = it->first;
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
        list<int>::iterator i;
        for (i = (*adj)[u]->begin(); i != (*adj)[u]->end(); ++i)
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

    cout << "Parent" << endl;
    for (auto it = parent.begin(); it != parent.end(); ++it)
    {
        cout << it->first << ":" << it->second << NEWLINE;
    }

    cout << "Distance" << endl;
    for (auto it = dist.begin(); it != dist.end(); ++it)
    {
        cout << it->first << ":" << it->second << NEWLINE;
    }

    for (auto it = parent.begin(); it != parent.end(); ++it)
    {
        int v = it->first;
        list<int> *shortest_path = new list<int>();
        while (parent[v] != -1) {
            shortest_path->push_back(parent[v]);
            v = parent[v];
        }
        paths->insert({it->first, shortest_path});
    }

    cout << "Paths:" << endl;
    for (auto it = paths->begin(); it != paths->end(); ++it)
    {
        cout << it->first << ":[";
        list<int> *shortest_path = it->second;
        for (auto i = shortest_path->begin(); i != shortest_path->end(); ++i) {
            cout << *i << " ";
        }
        cout << "]" << NEWLINE; 
    }
}

Graph::Graph(unordered_map<int, list<int> *> *g, int n)
{
    adj = g;
    N = n;
}
Graph::~Graph() {}