#include <bits/stdc++.h>

std::vector<std::vector<int>> levels;
std::vector<std::vector<bool>> flashMap;
std::queue<std::pair<int, int>> flashQueue;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << (i>0 ? " " : "") << v[i];
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& v)
{
    for (const std::vector<T>& u : v)
    {
        os << u << std::endl;
    }
    return os;
}


void processFlash(int i, int j)
{
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (di == 0 && dj == 0) continue;
            if (i+di >= 0 && i+di < levels.size() &&
                j+dj >= 0 && j+dj < levels[0].size())
                {
                    if (flashMap[i+di][j+dj]) continue;
                    levels[i+di][j+dj]++;
                    if (levels[i+di][j+dj] > 9)
                    {
                        flashQueue.push(std::make_pair(i+di, j+dj));
                    }
                }
        }
    }
}


unsigned long long processFlashQueue()
{
    unsigned long long flashes = 0;
    while (!flashQueue.empty())
    {
        auto p = flashQueue.front(); flashQueue.pop();

        if (flashMap[p.first][p.second]) continue;
        levels[p.first][p.second] = 0;
        flashMap[p.first][p.second] = true;
        flashes++;
        processFlash(p.first, p.second);
    }
    return flashes;
}


unsigned long long iter()
{
    flashMap = std::vector<std::vector<bool>>(levels.size(),
        std::vector<bool>(levels[0].size(), false));
    flashQueue = std::queue<std::pair<int, int>>();

    for (int i = 0; i < levels.size(); i++)
    {
        for (int j = 0; j < levels[i].size(); j++)
        {
            levels[i][j]++;
            if (levels[i][j] > 9) 
            {
                flashQueue.push(std::make_pair(i, j));
            }
        }
    }
    return processFlashQueue();
}


unsigned long long solve()
{
    unsigned long long i = 1;
    while (iter() != levels.size() * levels[0].size()) i++;
    return i;
}


int main()
{
    std::string s;
    levels = std::vector<std::vector<int>>();
    while (std::cin >> s)
    {
        std::vector<int> row = std::vector<int>();
        for (const char c : s)
        {
            row.push_back(c - '0');
        }
        levels.push_back(row);
    }

    std::cout << solve() << std::endl;
}