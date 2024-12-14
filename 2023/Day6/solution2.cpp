#include <bits/stdc++.h>


void solve()
{
    unsigned long long int time = 48938595;
    unsigned long long int record = 296192812361391;

    double disc = sqrt((double)time*time - 4.0*record);
    int lower = (int)floor(((double)time-disc)/2.0)+1;
    int upper = (int)ceil(((double)time+disc)/2.0)-1;

    std::cout << upper - lower + 1 << std::endl;
}


int main()
{
    solve();
}

