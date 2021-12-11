#include <bits/stdc++.h>

std::vector<std::vector<int>> heightmap;
std::vector<std::pair<int, int>> mins;
std::vector<std::vector<int>> basinmap;
std::vector<int> basins;

bool ismin(int i, int j)
{
    if (i > 0 && heightmap[i-1][j] <= heightmap[i][j]) return false;
    if (j > 0 && heightmap[i][j-1] <= heightmap[i][j]) return false;
    if (i < heightmap.size()-1 && heightmap[i+1][j] <= heightmap[i][j]) return false;
    if (j < heightmap[i].size()-1 && heightmap[i][j+1] <= heightmap[i][j]) return false;
    return true;
}

void findMins()
{
    for (int i = 0; i < heightmap.size(); i++)
    {
        for (int j = 0; j < heightmap[0].size(); j++)
        {
            if (ismin(i,j))
            {
                mins.push_back(std::make_pair(i,j));
                basins.push_back(0);
            }
        }
    }
}

void floodfill(std::pair<int, int> p0, int id)
{
    std::queue<std::pair<int, int>> q = std::queue<std::pair<int, int>>();

    q.push(p0);
    while (!q.empty())
    {
        std::pair<int, int> p = q.front(); q.pop();
        if (heightmap[p.first][p.second] == 9) continue;
        if (basinmap[p.first][p.second] == id+1) continue;

        basins[id]++;
        basinmap[p.first][p.second] = id+1;

        if (p.first > 0) q.push(std::make_pair(p.first - 1, p.second));
        if (p.second > 0) q.push(std::make_pair(p.first, p.second - 1));
        if (p.first < heightmap.size() - 1) q.push(std::make_pair(p.first + 1, p.second));
        if (p.second < heightmap[0].size() - 1) q.push(std::make_pair(p.first, p.second + 1));
    }
}

unsigned long long solve()
{
    findMins();
    for (int i = 0; i < mins.size(); i++)
    {
        floodfill(mins[i], i);
    }

    /*
    for (const auto& r : basinmap)
    {
        for (const auto i : r)
        {
            std::cout << i;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/

    std::sort(basins.begin(), basins.end(), std::greater<int>());
    for (const auto b : basins) std::cout << b << " ";
    std::cout << std::endl;

    return (unsigned long long)basins[0] * basins[1] * basins[2];
}


int main()
{
    heightmap = std::vector<std::vector<int>>();
    std::string s;
    while (std::cin >> s)
    {
        std::vector<int> row = std::vector<int>();
        for (const char c : s)
        {
            row.push_back(c-'0');
        }
        heightmap.push_back(row);
    }
    basinmap = std::vector<std::vector<int>>(
        heightmap.size(), std::vector<int>(heightmap[0].size(), 0));

    std::cout << solve() << std::endl;
}



