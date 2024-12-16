#include <bits/stdc++.h>

std::vector<std::string> map;
std::map<char, std::set<std::pair<int,int>>> antennae;
int N,M;

void solve()
{
    std::set<std::pair<int,int>> antinodes;
    auto insert_antinode = [&antinodes](int i, int j)
    {
        if (i<0||j<0 || i>=N||j>=M) return;
        antinodes.insert(std::make_pair(i,j));
    };

    for (const auto& freq : antennae)
    {
        for (const auto& p : freq.second)
        {
            for (const auto& q : freq.second)
            {
                if (p==q) continue;
                insert_antinode(2*p.first-q.first, 2*p.second-q.second);
                insert_antinode(2*q.first-p.first, 2*q.second-p.second);
            }
        }
    }
    std::cout << antinodes.size() << std::endl;
}


void preprocess()
{
    N = map.size();
    M = map.front().size();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j] == '.') continue;
            antennae[map[i][j]].insert(std::make_pair(i,j));
        }
    }
}

int main()
{
    map = std::vector<std::string>();

    std::string line;
    while (std::cin >> line)
    {
        if (line.empty()) continue;

        map.push_back(line);
    }
    preprocess();
    solve();
}

