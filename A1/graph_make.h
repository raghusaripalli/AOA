#include "graph_operations.h"
#define USER_N_ 480189
#define USER_MAX_N_ 2649430
#define MOVIE_N_ 17771

void read_netflix_data(
    unordered_map<int, int> *lookup,
    unordered_map<int, int> *rLookup,
    vector<int> *users,
    vector<int> *movies);

void graph_criteria_1(
    vector<int> *users,
    vector<int> *movies,
    Graph *g);