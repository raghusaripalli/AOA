#include "graph_make.h"
#include "measure_time.h"

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
    cout << endl;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cerr << "Couldn't start program due to insufficient command line arguments" << endl;
        cerr << "Usage Example:\n > ./real_test /home/cise/tmp/netflix_data/" << endl;
        return -1;
    }

    // Output filepath
    string fileName = "output/real_test_output.txt";
    cout << "Output is written to the file: " << fileName << endl;

    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // redirect stdout to file
    freopen(fileName.c_str(), "w", stdout);

    // Data structures to hold netflix data

    vector<int> *users = new vector<int>[USER_N_];
    vector<int> *movies = new vector<int>[MOVIE_N_];
    vector<int> *dates = new vector<int>[DATE_N_];
    vector<int> *ratings = new vector<int>[DATE_N_];

    // Load data from all four files
    read_netflix_data(argv[1], users, movies, dates, ratings);

    Graph *g;
    vector<int> *cc;

    // Build graph based on criteria 1
    g = new Graph(USER_N_);
    graph_criteria_1(users, g);
    start_time();
    cc = g->connected_components();
    end_and_display_time("Connected components Algorithm execution");
    printCountAndLength(cc, g->N);

    // Build graph based on criteria 2
    g = new Graph(USER_N_);
    graph_criteria_2(movies, g);
    start_time();
    cc = g->connected_components();
    end_and_display_time("Connected components Algorithm execution");
    printCountAndLength(cc, g->N);

    // Build graph based on criteria 3
    g = new Graph(USER_N_);
    graph_criteria_3(dates, ratings, g);
    start_time();
    cc = g->connected_components();
    end_and_display_time("Connected components Algorithm execution");
    printCountAndLength(cc, g->N);

    return 0;
}