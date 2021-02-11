#include "graph_operations.h"
#define USER_N_ 480189
#define USER_MAX_N_ 2649430
#define MOVIE_N_ 17771
#define DATE_N_ 2182

void read_netflix_data(
    char* data_path,
    vector<int> *users,
    vector<int> *movies,
    vector<int> *dates,
    vector<int> *ratings);

void graph_criteria_1(
    vector<int> *users,
    Graph *g);

void graph_criteria_2(
    vector<int> *movies,
    Graph *g);

void graph_criteria_3(
    vector<int> *dates,
    vector<int> *ratings,
    Graph *g);

void serialize_graph(Graph *g, string fileName);

Graph *deserialize_graph(string fileName);