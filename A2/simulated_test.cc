#include "skyline.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#define MOD 50
#define NEWLINE "\n"
#define COMMA ","

using namespace std;

struct Point
{
    int left;
    int height;
    int right;
};

Point *generateRandomPoint()
{
    Point *point = new Point();
    point->left = (rand() % MOD) + 1;
    point->right = (rand() % MOD) + 1;
    point->height = (rand() % MOD) + 1;
    return point;
}

vector<Point *> *generateRandomPoints(int N)
{
    vector<Point *> *points = new vector<Point *>();
    for (int i = 0; i < N; i++)
    {
        points->push_back(generateRandomPoint());
    }

    return points;
}

void printRandomPoints(vector<Point *> *points)
{
    int N = points->size();
    for (int i = 0; i < N; i++)
    {
        Point *point = points->at(i);
        cout << point->left << COMMA << point->height << COMMA << point->right << NEWLINE;
    }
    cout << endl;
}

int main()
{
    srand(time(0));
    printRandomPoints(generateRandomPoints(50));
    return 0;
}