#include <bits/stdc++.h>


std::vector<std::vector<int>> risk;
std::vector<std::vector<unsigned long long>> distance;

unsigned long long solve()
{
    std::priority_queue<std::pair<unsigned long long, std::pair<int, int>>,
        std::vector<std::pair<unsigned long long, std::pair<int, int>>>,
        std::greater<std::pair<unsigned long long, std::pair<int, int>>>> checkQueue;
    checkQueue.push(std::make_pair(0, std::make_pair(0,0)));
    distance = std::vector<std::vector<unsigned long long>>(
        risk.size(), std::vector<unsigned long long>(risk[0].size(), ULLONG_MAX));

    auto push = [&](unsigned long long dist, int i, int j, int di, int dj)
    {
        checkQueue.push(std::make_pair(dist + risk[i+di][j+dj] - i - j - di - dj, std::make_pair(i+di, j+dj)));
    };

    while (!checkQueue.empty())
    {
        auto loc = checkQueue.top().second;
        auto dist = checkQueue.top().first + loc.first + loc.second;
        checkQueue.pop();

        if (dist >= distance[loc.first][loc.second]) continue;
        distance[loc.first][loc.second] = dist;
        
        if (loc.first == risk.size()-1 && loc.second == risk[0].size()-1) return dist;

        if (loc.first < risk.size()-1) push(dist, loc.first, loc.second, 1, 0);
        if (loc.first > 0) push(dist, loc.first, loc.second, -1, 0);
        if (loc.second < risk[0].size()-1) push(dist, loc.first, loc.second, 0, 1);
        if (loc.second > 0) push(dist, loc.first, loc.second, 0, -1);
    }
    std::cout << "Failed" << std::endl;
    return 0;
}


int main()
{
    risk = std::vector<std::vector<int>>();
    std::string s;
    while (std::cin >> s)
    {
        std::vector<int> row = std::vector<int>(s.length());
        for (int i = 0; i < s.length(); i++)
            row[i] = s[i] - '0';
        risk.push_back(row);
    }

    std::cout << solve() << std::endl;

    /*for (const auto& r : distance)
    {
        for (const auto& v : r)
        {
            std::cout << (v < ULLONG_MAX ? v : '#') << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/
}

