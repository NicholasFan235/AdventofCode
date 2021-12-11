#include <bits/stdc++.h>

std::vector<std::vector<int>> heightmap;

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

bool ismin(int i, int j)
{
    if (i > 0 && heightmap[i-1][j] <= heightmap[i][j]) return false;
    if (j > 0 && heightmap[i][j-1] <= heightmap[i][j]) return false;
    if (i < heightmap.size()-1 && heightmap[i+1][j] <= heightmap[i][j]) return false;
    if (j < heightmap[i].size()-1 && heightmap[i][j+1] <= heightmap[i][j]) return false;
    return true;
}


unsigned long long solve()
{
    unsigned long long risk = 0;
    for (int i = 0; i < heightmap.size(); i++)
    {
        for (int j = 0; j < heightmap[0].size(); j++)
        {
            if (ismin(i,j)) risk += 1 + heightmap[i][j];
        }
    }

    return risk;
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

    std::cout << solve() << std::endl;
}



