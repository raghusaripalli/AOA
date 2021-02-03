#include "graph_operations.h"

clock_t t;

// Helper Methods

void addEdge(unordered_map<int, list<int> *> *graph, int v, int w)
{

    if (graph->find(v) == graph->end())
        graph->insert({v, new list<int>()});
    if (graph->find(w) == graph->end())
        graph->insert({w, new list<int>()});
    graph->at(v)->push_back(w);
    graph->at(w)->push_back(v);
}

unordered_map<int, list<int> *> *initializeGraph(int N)
{
    unordered_map<int, list<int> *> *graph = new unordered_map<int, list<int> *>();
    return graph;
}

void start_time()
{
    t = clock();
}

void end_and_display_time(string funcName)
{
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    cout << "Executed '" << funcName << "' in " << time_taken << " secs." << NEWLINE;
}

// Graph Simulation Methods

unordered_map<int, list<int> *> *nCycle(int N)
{
    unordered_map<int, list<int> *> *graph = initializeGraph(N);
    for (int i = 1; i < N; i++)
    {
        addEdge(graph, i, i - 1);
    }
    addEdge(graph, 0, N);
    return graph;
}

unordered_map<int, list<int> *> *completeGraph(int N)
{
    unordered_map<int, list<int> *> *graph = initializeGraph(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            addEdge(graph, i, j);
        }
    }
    return graph;
}

int main()
{

    // fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // redirect stdout to output.txt
    freopen("simulated_test_output.txt", "w", stdout);

    start_time();
    int N = 480000;
    unordered_map<int, list<int> *> *adj = completeGraph(N);
    end_and_display_time("Graph Simulation");

    // Create and Assign to Graph
    Graph graph(adj, N);
    start_time();
    graph.connected_components();
    end_and_display_time("Connected Components");

    //graph.one_cycle();
    graph.shortest_paths();
    return 0;
}