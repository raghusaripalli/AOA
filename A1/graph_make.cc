#include "graph_make.h"
#define RATING_N_ 1

// 9808 - 1
// 3136 - 2
// 62 - 3
// 20 - 4
// 52 - 5

void read_netflix_data(
    unordered_map<int, int> *lookup,
    unordered_map<int, int> *rLookup,
    unordered_map<string, int> *dLookup,
    vector<int> *users,
    vector<int> *movies,
    int **min_rating,
    vector<int> *user_ratings,
    vector<int> *dates,
    vector<int> *ratings)
{
    // paths of the input files
    string arr[] = {"data/ratings_data_1.txt", "data/ratings_data_2.txt", "data/ratings_data_3.txt", "data/ratings_data_4.txt"};
    int id = 0, date_id = 0;
    for (int k = 0; k < 4; k++)
    {
        cout << arr[k] << endl;
        ifstream input(arr[k]); // opening the kth input file
        string delimiter = ",", movie_delim = ":";
        if (input.is_open())
        {
            cout << "File Opened" << endl;
            string mid, number, date, rstr;
            int movie_id = 0, user_id, eid, edid, rating, ratingIdx;
            while (!input.eof())
            {
                string line;
                getline(input, line);
                if (line.size() < 2)
                    continue;
                if (line.find(movie_delim) != string::npos)
                {
                    mid = line.substr(0, line.find(movie_delim));
                    movie_id = atoi(mid.c_str());
                    continue;
                }
                number = line.substr(0, line.find(delimiter));
                date = line.substr(line.size() - 10);
                rstr = line.substr(line.size() - 12, 1);
                rating = atoi(rstr.c_str());
                user_id = atoi(number.c_str());

                user_ratings[movie_id].push_back(rating);
                ratingIdx = rating - 1;
                min_rating[movie_id][ratingIdx] += 1;
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

                if (dLookup->find(date) == dLookup->end())
                {
                    dLookup->insert({date, date_id});
                    dates[date_id].push_back(lookup->at(user_id));
                    ratings[date_id].push_back(rating);
                    date_id++;
                }
                else
                {
                    edid = dLookup->at(date);
                    dates[edid].push_back(lookup->at(user_id));
                    ratings[edid].push_back(rating);
                }
            }
            input.close();
            cout << "File Closed" << endl;
        }
    }
    cout << "Data Reading Completed." << NEWLINE << endl;
}

// Movie Critics - Users who rated atleast 1000 movies
void graph_criteria_1(
    vector<int> *users,
    vector<int> *movies,
    Graph *g)
{
    cout << "Building Graph based on Criteria 1" << endl;

    vector<int> criteria_users;

    int N = 1000;
    // Adding user_ids to criteria_users
    for (int i = 0; i < g->N; i++)
        if ((int)users[i].size() >= N)
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

// Movie Buddies - connecting users who rated movies on same date and ratings == RATINGS_N_
void graph_criteria_2(vector<int> *dates, vector<int> *ratings, Graph *g)
{
    cout << "Building Graph based on Criteria 2" << endl;
    for (int i = 0; i < DATE_N_; i++)
    {
        int ND = dates[i].size();
        for (int j = 1; j < ND; j++)
        {
            if (ratings[i][j] == RATING_N_ && ratings[i][j - 1] == RATING_N_)
                g->addEdge(dates[i][j], dates[i][j - 1]);
        }
    }

    cout << "Building Graph Completed" << endl;
}

void graph_criteria_3(vector<int> *movies, vector<int> *user_ratings, int **min_rating, Graph *g)
{
    cout << "Building Graph based on Criteria 3" << endl;
    for (int i = 0; i < MOVIE_N_; i++)
    {
        vector<int> criteria_users;
        int minCount = INT_MIN;
        int minRating = -1;
        for (int j = 0; j < 5; j++)
        {
            if (min_rating[i][j] >= minCount)
            {
                minCount = min_rating[i][j];
                minRating = j;
            }
        }
        minRating = 3;
        int N = user_ratings[i].size();
        for (int j = 0; j < N; j++)
        {
            if (user_ratings[i][j] == minRating)
            {
                criteria_users.push_back(movies[i][j]);
            }
        }

        int CN = criteria_users.size();

        for (int j = 1; j < CN; j++)
        {
            g->addEdge(criteria_users[j], criteria_users[j - 1]);
        }
    }
    cout << "Building Graph Completed" << endl;
}