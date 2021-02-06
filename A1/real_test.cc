#include "graph_make.h"

// Helper Methods
void printCountAndLength(vector<int> *cc, int N)
{
    int count = 0;
    for (int i = 0; i < N; i++)
        if (cc[i].size() > 1)
            count++;
    cout << "No of connected components: " << count << NEWLINE;
    cout << "Size of connected components:" << NEWLINE;
    for (int i = 0, j = 1; i < N; i++)
    {
        if (cc[i].size() > 1)
        {
            cout << j << ":" << cc[i].size() << NEWLINE;
            j++;
        }
    }
}

int main()
{
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // redirect stdout to file
    string fileName = "output/real_test_output.txt";
    freopen(fileName.c_str(), "w", stdout);

    // Data structures to hold netflix data
    unordered_map<int, int> *lookup, *rLookup;
    lookup = new unordered_map<int, int>();
    rLookup = new unordered_map<int, int>();
    vector<int> *users = new vector<int>[USER_N_];
    vector<int> *movies = new vector<int>[MOVIE_N_];

    // Load data from all four files
    read_netflix_data(lookup, rLookup, users, movies);

    Graph *g = new Graph(USER_N_);

    // Build graph based on criteria 1
    graph_criteria_1(users, movies, g);
    vector<int> *cc = g->connected_components();
    printCountAndLength(cc, g->N);

    return 0;
}