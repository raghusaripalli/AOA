#include "graph_operations.h"

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

bool Graph::isCyclic(unordered_set<int> *visited, int v, int parent)
{
    // mark node 'v' as visited
    visited->insert(v);

    // Iterate through all the nodes connected to 'v'
    list<int>::iterator i;
    for (i = (*adj)[v]->begin(); i != (*adj)[v]->end(); ++i)
    {
        if (visited->find(*i) == visited->end())
        {
            if (isCyclic(visited, *i, v))
            {
                return true;
            }
        }
        else if (*i != parent)
        {
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

bool Graph::one_cycle()
{
    // Create visited set
    unordered_set<int> *visited = new unordered_set<int>();

    for (int i = 0; i < N; i++)
    {
        if (visited->find(i) == visited->end())
        {
            if (isCyclic(visited, i, -1))
            {
                return true;
            }
        }
    }

    // free visited
    delete visited;

    return false;
}

void Graph::shortest_paths()
{
    cout << "SP" << endl;
}