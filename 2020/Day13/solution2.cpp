#include <bits/stdc++.h>

unsigned long long int startT;
std::vector<int> busses;
std::vector<int> offsets;
std::vector<int> ms;
int maxBus = 0;

unsigned long long int solve()
{
    unsigned long long t = -offsets[maxBus];
    unsigned long long ctr = 0;
    while (true)
    {
        t += busses[maxBus];

        bool valid = true;
        for (int i = 0; i < busses.size(); i++)
        {
            if ((busses[i] - t%busses[i])%busses[i] != offsets[i])
            {
                valid = false;
                break;
            }
        }
        if (valid) return t;
        ctr ++;
        if (ctr%100000000 == 0) std::cout << t << std::endl;
    }
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
    ms = std::vector<int>(busses.size(), 1);
    
    int ans = solve();

    for (int i = 0; i < busses[i]; i++)
    {
        std::cout << busses[i] << ": " << offsets[i] << std::endl;
    }
    std::cout << "max bus = " << busses[maxBus] << " index " << maxBus << std::endl;

    std::cout << ans << std::endl;
}
