#include <bits/stdc++.h>


std::vector<int> adapters;
std::map<int, int> distrib;

void solve()
{
    distrib = std::map<int, int>();
    distrib[adapters[0]]++;
    distrib[3]++;

    for (int i = 1; i < adapters.size(); i++)
    {
        distrib[adapters[i]-adapters[i-1]] += 1;
    }

    for (const auto p : distrib)
    {
        std::cout << p.first << ": " << p.second << std::endl;
    }
    std::cout << std::endl;

    std::cout << distrib[1] * distrib[3] << std::endl;
}

int main()
{
    adapters = std::vector<int>();
    while (!std::cin.eof())
    {
        int j;
        std::cin >> j;
        adapters.push_back(j);
    }
    std::sort(adapters.begin(), adapters.end());

/*
    printf("%d", adapters[0]);
    for (int i = 1; i < adapters.size(); i++)
    {
        printf(", %d", adapters[i]);
    }
    printf("\n");
*/

    solve();
}