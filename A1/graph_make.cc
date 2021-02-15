#include "graph_make.h"
#include "measure_time.h"
#define RATING_N_ 1

/*
    Read User and Movie Data from the netflix data provided
*/
void read_netflix_data(
    char *data_path,
    vector<int> *users,
    vector<int> *movies,
    vector<int> *dates,
    vector<int> *ratings)
{
    start_time();
    // Lookup maps
    unordered_map<int, int> *lookup, *rLookup, *movieIDYearLookup;
    unordered_map<string, int> *dLookup;

    lookup = new unordered_map<int, int>();
    rLookup = new unordered_map<int, int>();
    movieIDYearLookup = new unordered_map<int, int>();
    dLookup = new unordered_map<string, int>();
    // convert data_path to string
    string path = data_path;
    // Read from movie_titles.csv
    string movieCSVPath = path + "movie_titles.csv";
    ifstream movieTitle(movieCSVPath);
    if (movieTitle.is_open())
    {
        cout << TAB << movieCSVPath << endl;
        string movieIdStr, yearStr, delimiter = ",";
        int movieId, year, pos;
        while (!movieTitle.eof())
        {
            string line;
            getline(movieTitle, line);
            pos = line.find(delimiter);
            movieIdStr = line.substr(0, pos);
            movieId = atoi(movieIdStr.c_str());
            yearStr = line.substr(pos + 1, 4);
            year = atoi(yearStr.c_str());
            movieIDYearLookup->insert({movieId, year});
        }
        movieTitle.close();
    }

    // paths of the input files
    string arr[] = {"ratings_data_1.txt", "ratings_data_2.txt", "ratings_data_3.txt", "ratings_data_4.txt"};
    int id = 0, date_id = 0;
    for (int k = 0; k < 4; k++)
    {
        string fPath = path + arr[k];
        cout << TAB << fPath << endl;
        ifstream input(fPath); // opening the kth input file
        string delimiter = ",", movie_delim = ":";
        if (input.is_open())
        {
            string mid, number, date, rstr, yearStr;
            int movie_id = 0, user_id, eid, edid, rating, year;
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
                yearStr = date.substr(0, 4);
                year = atoi(yearStr.c_str());
                rstr = line.substr(line.size() - 12, 1);
                rating = atoi(rstr.c_str());
                user_id = atoi(number.c_str());
                // If user_id id not in the lookup table
                if (lookup->find(user_id) == lookup->end())
                {
                    lookup->insert({user_id, id});
                    rLookup->insert({id, user_id});
                    users[id].push_back(movie_id);
                    if (movieIDYearLookup->at(movie_id) == year + 1)
                        movies[movie_id].push_back(id);
                    ++id;
                }
                else
                {
                    eid = lookup->at(user_id);
                    users[eid].push_back(movie_id);
                    if (movieIDYearLookup->at(movie_id) == year + 1)
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

            // close the input file
            input.close();
        }
    }

    // free the memory used by lookups
    delete lookup;
    delete dLookup;
    delete rLookup;
    delete movieIDYearLookup;

    end_and_display_time("Reading and parsing netflix data");
}

/*
 1. Film Buffs: Users who rated more than 1000 movies from 1999 to 2005.
 */
void graph_criteria_1(
    vector<int> *users,
    Graph *g)
{
    start_time();
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
    end_and_display_time("Creating graph based on 1st Criteria");
}

/*
 2. Late Watchers: Users who rated movie exactly the next year after the release.
 */
void graph_criteria_2(vector<int> *movies, Graph *g)
{
    start_time();
    for (int i = 0; i < MOVIE_N_; i++)
    {
        int N = movies[i].size();
        for (int j = 1; j < N; j++)
        {
            g->addEdge(movies[i][j], movies[i][j - 1]);
        }
    }
    end_and_display_time("Creating graph based on 2nd Criteria");
}

/*
 3. Movie Critics: Users who rated movies on the same date and gave a rating of ‘1.0’ to the respective movie.
*/
void graph_criteria_3(vector<int> *dates, vector<int> *ratings, Graph *g)
{
    start_time();
    for (int i = 0; i < DATE_N_; i++)
    {
        int ND = dates[i].size();
        for (int j = 1; j < ND; j++)
        {
            if (ratings[i][j] == RATING_N_ && ratings[i][j - 1] == RATING_N_)
                g->addEdge(dates[i][j], dates[i][j - 1]);
        }
    }
    end_and_display_time("Creating graph based on 3rd Criteria");
}