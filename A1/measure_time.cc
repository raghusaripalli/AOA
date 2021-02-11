#include "measure_time.h"

clock_t t;

void start_time()
{
    t = clock();
}

void end_and_display_time(string stage)
{
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    cout << stage << " took " << time_taken << " secs.\n" << endl;
}