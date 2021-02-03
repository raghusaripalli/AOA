#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //put your program together with thsi file in the same folder.

    int N = 2649430;
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

    string arr[] = {"data/ratings_data_1.txt", "data/ratings_data_2.txt", "data/ratings_data_3.txt", "data/ratings_data_4.txt"};
    int count = 0;
    for (int k = 0; k < 4; k++)
    {
        cout << arr[k] << endl;
        ifstream input(arr[k]);
        string delimiter = ",";
        string skip = ":";
        int g_max = INT_MIN;
        int g_min = INT_MAX;
        if (input.is_open())
        {
            cout << "File Opened" << endl;
            while (!input.eof())
            {
                string line;
                int data;
                getline(input, line);
                if (line.find(skip) != std::string::npos)
                {
                    continue;
                }
                string number = line.substr(0, line.find(delimiter));
                data = atoi(number.c_str());
                visited[data] = true;
                g_max = max(g_max, data);
                g_min = min(g_min, data);
            }
        }

        cout << "Max: " << g_max << endl;
        cout << "Min: " << g_min << endl;
    }
    for (int i = 0; i < N; i++)
        count += visited[i];
    cout << N - count << endl;
    return 0;
}