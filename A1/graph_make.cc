#include "graph_operations.h"
#define USER_N_ 480189
#define USER_MAX_N_ 2649430
#define MOVIE_N_ 17771
using namespace std;

void read_netflix_data(
    unordered_map<int, int> *lookup,
    unordered_map<int, int> *rLookup,
    vector<int> *users,
    vector<int> *movies)
{
    string arr[] = {"data/ratings_data_1.txt", "data/ratings_data_2.txt", "data/ratings_data_3.txt", "data/ratings_data_4.txt"};
    int id = 0;
    for (int k = 0; k < 4; k++)
    {
        cout << arr[k] << endl;
        ifstream input(arr[k]);
        string delimiter = ",", movie_delim = ":";
        if (input.is_open())
        {
            cout << "File Opened" << endl;
            string mid, number;
            int movie_id = 0, user_id, eid;
            while (!input.eof())
            {
                string line;
                getline(input, line);
                if (line.find(movie_delim) != string::npos)
                {
                    mid = line.substr(0, line.find(movie_delim));
                    movie_id = atoi(mid.c_str());
                    continue;
                }
                number = line.substr(0, line.find(delimiter));
                user_id = atoi(number.c_str());
                if (lookup->find(user_id) == lookup->end())
                {
                    lookup->insert({user_id, id});
                    rLookup->insert({id, user_id});
                    users[id].push_back(movie_id);
                    movies[movie_id].push_back(id);
                    ++id;
                }
                else
                {
                    eid = lookup->at(user_id);
                    users[eid].push_back(movie_id);
                    movies[movie_id].push_back(eid);
                }
            }
            input.close();
            cout << "File Closed" << endl;
        }
    }
    cout << "Data Reading Completed." << endl;
}

// Movie Critics - Users who rated atleast 750 movies
void graph_criteria_1(
    unordered_map<int, int> *lookup,
    unordered_map<int, int> *rLookup,
    vector<int> *users,
    vector<int> *movies,
    Graph *g)
{
    cout << "Building Graph" << endl;

    vector<int> criteria_users;

    int N = 750;
    vector<int>::iterator it, jt;
    for (int i = 1; i < USER_N_; i++)
        if (users[i].size() >= N)
            criteria_users.push_back(rLookup->at(i));

    int criteria_user_size = criteria_users.size();
    for (int i = 0; i < criteria_user_size; i++)
    {
        for (int j = i + 1; j < criteria_user_size; j++)
        {
            g->addEdge(criteria_users[i], criteria_users[j]);
        }
    }

    cout << "Building Graph Completed" << endl;
}

int main()
{
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // redirect stdout to file
    string fileName = "graph_make_output.txt";
    freopen(fileName.c_str(), "w", stdout);

    // Data structures to hold netflix data
    unordered_map<int, int> *lookup, *rLookup;
    lookup = new unordered_map<int, int>();
    rLookup = new unordered_map<int, int>();
    vector<int> *users = new vector<int>[USER_N_];
    vector<int> *movies = new vector<int>[MOVIE_N_];

    // Load data from all four files
    read_netflix_data(lookup, rLookup, users, movies);

    Graph *g = new Graph(USER_MAX_N_);

    // Build graph based on criteria 1
    graph_criteria_1(lookup, rLookup, users, movies, g);

    g->connected_components();
    g->shortest_paths(7);
    return 0;
}