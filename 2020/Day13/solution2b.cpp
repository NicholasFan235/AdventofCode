#include <bits/stdc++.h>

typedef unsigned long long ull;

unsigned long long startT;
std::vector<int> busses;
std::vector<int> offsets;
int maxBus = 0;

std::pair<ull, ull> reduce(std::pair<ull, ull> a, std::pair<ull, ull> b)
{
    printf("Solved busses (%lld, %lld), (%lld, %lld) -> ",
        a.first, a.second, b.first, b.second);
    std::cout << std::flush;
    ull t = a.second;
    std::vector<ull> res = std::vector<ull>();
    int ctr1 = 0;
    int ctr2 = 0;
    while (res.size() < 2)
    {
        if (res.size() < 1) ctr1++;
        ctr2++;
        t += a.first;
        if ((b.first - (t%b.first))%b.first == b.second%b.first) res.push_back(t);
    }

    printf("(%lld, %lld) in %d iterations, looped after %d.\n",
        res[1]-res[0], res[0], ctr1, ctr2);
    return std::make_pair(res[1] - res[0], res[0]);
}


unsigned long long int solve()
{
    std::vector<std::pair<ull, ull>> points = std::vector<std::pair<ull, ull>>();
    for (int i = 0; i < busses.size(); i++)
    {
        points.push_back(std::make_pair<ull, ull>(busses[i], offsets[i]));
    }
    //std::sort(points.begin()+1, points.end(), std::less<std::pair<ull, ull>>());
    std::pair<ull, ull> c = points[0];
    for (int i = 1; i < busses.size(); i++)
    {
        c = reduce(c, points[i]);
    }
    return c.second;
}


int main()
{
    std::cin >> startT;
    std::string s;
    int offset = 0;
    while (std::getline(std::cin, s, ','))
    {
        if (!s.empty() && s != "x")
        {
            busses.push_back(std::atoi(s.c_str()));
            offsets.push_back(offset);
        }
        offset++;
    }
    for (int i = 0; i < busses.size(); i++)
        if (busses[i] > busses[maxBus]) maxBus = i;
    
    ull ans = solve();
    std::cout << "startT: " << startT << std::endl;
    std::cout << ans << std::endl;
}
