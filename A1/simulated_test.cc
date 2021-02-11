#include "graph_operations.h"
#include "measure_time.h"

void printConnectedComponents(vector<int> *cc, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (!cc[i].size())
            continue;

        cout << i << ": [";
        for (auto it = cc[i].begin(); it != cc[i].end(); ++it)
        {
            cout << *it << " ";
        }
        cout << "]" << NEWLINE;
    }
}

void printShortestPaths(vector<int> *paths, int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << i << ":[";
        for (auto j = paths[i].begin(); j != paths[i].end(); ++j)
        {
            cout << *j << " ";
        }
        cout << "]" << NEWLINE;
    }
}

void printOneCycle(vector<int> *path, int N)
{
    if (path == NULL)
    {
        cout << "Cycle Not Found." << NEWLINE;
    }
    else
    {
        cout << "Cycle Found:" << NEWLINE;
        vector<int>::reverse_iterator i;
        for (i = path->rbegin(); i != path->rend(); ++i)
            cout << *i << (i == path->rend() - 1 ? "" : " -> ");
        cout << NEWLINE;
    }
}

// adj Simulation Methods

void nCycle(Graph g)
{
    for (int i = 1; i < g.N; i++)
    {
        g.addEdge(i, i - 1);
    }
    g.addEdge(0, g.N - 1);
}

void completeGraph(Graph g)
{
    for (int i = 0; i < g.N; i++)
    {
        for (int j = i + 1; j < g.N; j++)
        {
            g.addEdge(i, j);
        }
    }
}

int main()
{
    // User Input
    int N, graphChoice, algoChoice;
    string fileName = "output/simulated_test_output.txt";
    do
    {
        cout << "Select one of the following graphs to simulate:" << NEWLINE << endl;
        cout << TAB << "1. N Cycle adj" << NEWLINE;
        cout << TAB << "2. Complete adj" << NEWLINE;
        cout << TAB << "3. Empty adj" << NEWLINE << TAB;
        cin >> graphChoice;
    } while (graphChoice < 1 || graphChoice > 3);

    cout << "Enter no of nodes in the adj: " << NEWLINE << TAB;
    cin >> N;

    do
    {
        cout << "Select one of the 3 algorithms to run on the above mentioned adj:" << NEWLINE << endl;
        cout << TAB << "1. Connected Components" << NEWLINE;
        cout << TAB << "2. One Cycle" << NEWLINE;
        cout << TAB << "3. Shortest Paths" << NEWLINE << TAB;
        cin >> algoChoice;
    } while (algoChoice < 1 || algoChoice > 3);

    cout << "Output written to the file: " << fileName << endl;

    // fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // redirect stdout to file
    freopen(fileName.c_str(), "w", stdout);

    start_time();
    // Initialize graph DS
    Graph graph(N);

    // Add edges acc to criteria
    switch (graphChoice)
    {
    case 1:
        nCycle(graph);
        break;
    case 2:
        completeGraph(graph);
        break;
    case 3:
        break;
    default:
        nCycle(graph);
        break;
    }
    end_and_display_time("Graph Simulation");

    start_time();
    // Exec appropriate algo as per user input
    switch (algoChoice)
    {
    case 1:
        printConnectedComponents(graph.connected_components(), N);
        break;
    case 2:
        printOneCycle(graph.one_cycle(), N);
        break;
    case 3:
        printShortestPaths(graph.shortest_paths(0), N);
        break;
    default:
        break;
    }
    end_and_display_time("Algorithm Execution");
    cout << endl;
    return 0;
}