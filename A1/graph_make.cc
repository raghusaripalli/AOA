#include "graph_make.h"

void read_netflix_data(
    unordered_map<int, int> *lookup,
    unordered_map<int, int> *rLookup,
    vector<int> *users,
    vector<int> *movies)
{
    // paths of the input files
    string arr[] = {"data/ratings_data_1.txt", "data/ratings_data_2.txt", "data/ratings_data_3.txt", "data/ratings_data_4.txt"};
    int id = 0;
    for (int k = 0; k < 4; k++)
    {
        cout << arr[k] << endl;
        ifstream input(arr[k]); // opening the kth input file
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
                // If user_id id not in the lookup table
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
    vector<int> *users,
    vector<int> *movies,
    Graph *g)
{
    cout << "Building Graph" << endl;

    vector<int> criteria_users;

    int N = 750;
    // Adding user_ids to criteria_users
    for (int i = 0; i < g->N; i++)
        if (users[i].size() >= N)
            criteria_users.push_back(i);

    int criteria_user_size = criteria_users.size();
    // Creating complete graph between all criteria users. So. adding edge between all users.
    for (int i = 0; i < criteria_user_size; i++)
    {
        for (int j = i + 1; j < criteria_user_size; j++)
        {
            g->addEdge(criteria_users[i], criteria_users[j]);
        }
    }

    cout << "Building Graph Completed" << endl;
}