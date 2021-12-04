#include <bits/stdc++.h>

std::vector<int> adapters;
std::map<int, long long int> solved;
std::vector<int> path;

long long int traverse(int i)
{
    if (i == adapters.size()-1)
    {
        //for (const auto i : path) std::cout << i << " ";
        //std::cout << std::endl;
        return 1;
    }
    if (i >= adapters.size()) return 0;

    if (solved.find(i) != solved.end()) return solved[i];

    long long int ans = 0;
    int iCpy = i;
    while (adapters[++iCpy] - adapters[i] <= 3)
    {
        path.push_back(adapters[iCpy]);
        ans += traverse(iCpy);
        path.pop_back();
        if (iCpy >= adapters.size()-1) break;
    }
    
    solved[i] = ans;
    return ans;
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
    adapters.push_back(0);
    std::sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters[adapters.size()-1] + 3);

    solved = std::map<int, long long int>();
    solved[adapters.size()-1] = 1;
    path = std::vector<int>();
    path.push_back(0);
    long long int ans = traverse(0);

    std::cout << adapters.size() << std::endl;
    for (const auto& p : solved)
    {
        std::cout << p.first << "(" << adapters[p.first] << ") : " << p.second << std::endl;
    }
    std::cout << std::endl;

    std::cout << ans << std::endl;
}