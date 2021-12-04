#include <bits/stdc++.h>

unsigned long long int startT;
std::vector<int> busses;

unsigned long long int solve()
{
    int bestWait = INT_MAX;
    int bestBus = 0;
    for (const int bus : busses)
    {
        int wait = bus - (startT % bus);
        printf("Bus %d -> %d mins wait.\n", bus, wait);
        if (wait < bestWait)
        {
            bestWait = wait;
            bestBus = bus;
        }
    }
    return bestWait * bestBus;
}


int main()
{
    std::cin >> startT;
    std::string s;
    while (std::getline(std::cin, s, ','))
    {
        if (!s.empty() && s != "x")
        {
            busses.push_back(std::atoi(s.c_str()));
        }
    }
    
    int ans = solve();
    std::cout << ans << std::endl;
}
