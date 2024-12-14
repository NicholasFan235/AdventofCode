#include <bits/stdc++.h>


struct Race
{
    int time, record;
    Race(int t, int r) : time(t), record(r) {}
};

std::vector<Race> races;


void solve()
{
    std::vector<int> ways = std::vector<int>();
    for (const auto& race : races)
    {
        double disc = sqrt((double)race.time*race.time - 4.0*race.record);
        int lower = (int)floor(((double)race.time-disc)/2.0)+1;
        int upper = (int)ceil(((double)race.time+disc)/2.0)-1;
        ways.push_back(upper-lower+1);
    }
    
    unsigned long long ans = std::accumulate(ways.begin(), ways.end(), 1,
        [](const unsigned long long& l, const int& r) { return l*r; });
    std::cout << ans << std::endl;
}


int main()
{
    std::vector<int> times = std::vector<int>();
    std::vector<int> records = std::vector<int>();

    std::string s;
    std::cin >> s;
    while (std::cin >> s)
    {
        if (s == "Distance:") break;
        times.push_back(atoi(s.c_str()));
    }
    while (std::cin >> s)
    {
        records.push_back(atoi(s.c_str()));
    }

    races = std::vector<Race>();
    for (int i = 0; i < times.size() && i < records.size(); i++)
    {
        races.push_back(Race{times[i], records[i]});
    }

    solve();
}

