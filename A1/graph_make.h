#include "graph_operations.h"
#define USER_N_ 480189
#define USER_MAX_N_ 2649430
#define MOVIE_N_ 17771
#define DATE_N_ 2182

void read_netflix_data(
    unordered_map<int, int> *lookup,
    unordered_map<int, int> *rLookup,
    unordered_map<string, int> *dLookup,
    vector<int> *users,
    vector<int> *movies,
    int **min_rating,
    vector<int> *user_ratings,
    vector<int> *dates,
    vector<int> *ratings);

void graph_criteria_1(
    vector<int> *users,
    vector<int> *movies,
    Graph *g);

void graph_criteria_2(
    vector<int> *dates,
    vector<int> *ratings,
    Graph *g);

void graph_criteria_3(
    vector<int> *movies, 
    vector<int> *user_ratings, 
    int **min_rating, 
    Graph *g);