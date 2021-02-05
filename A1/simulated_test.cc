#include "graph_operations.h"

clock_t t;

// Helper Methods

void addEdge(vector<int> *adj, int u, int v)
{
    adj[v].push_back(u);
    adj[u].push_back(v);
}

vector<int> *initializeGraph(int N)
{
    vector<int> *adj = new vector<int>[N];
    return adj;
}

void start_time()
{
    t = clock();
}

void end_and_display_time(string stage)
{
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    cout << stage << " took " << time_taken << " secs." << NEWLINE;
}

// adj Simulation Methods

vector<int> *nCycle(int N)
{
    vector<int> *adj = initializeGraph(N);
    for (int i = 1; i < N; i++)
    {
        addEdge(adj, i, i - 1);
    }
    addEdge(adj, 0, N - 1);
    return adj;
}

vector<int> *completeGraph(int N)
{
    vector<int> *adj = initializeGraph(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            addEdge(adj, i, j);
        }
    }
    return adj;
}

vector<int> *emptyGraph(int N)
{
    return initializeGraph(N);
}

int main()
{
    // User Input
    int N, graphChoice, algoChoice;
    string fileName = "simulated_test_output.txt";
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

    // redirect stdout to output.txt
    freopen(fileName.c_str(), "w", stdout);

    start_time();
    vector<int> *adj;
    switch (graphChoice)
    {
    case 1:
        adj = nCycle(N);
        break;
    case 2:
        adj = completeGraph(N);
        break;
    case 3:
        adj = emptyGraph(N);
        break;
    default:
        adj = nCycle(N);
        break;
    }
    end_and_display_time("Graph Simulation");

    // Create and Assign to graph
    Graph graph(adj, N);
    start_time();
    switch (algoChoice)
    {
    case 1:
        graph.connected_components();
        break;
    case 2:
        graph.one_cycle();
        break;
    case 3:
        graph.shortest_paths(0);
        break;
    default:
        break;
    }
    end_and_display_time("Algorithm Execution");
    cout << endl;
    return 0;
}