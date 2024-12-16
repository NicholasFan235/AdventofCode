#include <bits/stdc++.h>

std::vector<std::string> map;
std::map<char, std::vector<std::pair<int,int>>> antennae;
int N,M;


bool in_bounds(const std::pair<int,int>& p)
{
    return p.first>=0 && p.second>=0 && p.first<N && p.second<M;
}

std::pair<int,int> operator+(const std::pair<int,int>& p, const std::pair<int,int>& q)
{
    return std::make_pair(p.first+q.first, p.second+q.second);
}

std::pair<int,int> operator-(const std::pair<int,int>& p, const std::pair<int,int>& q)
{
    return std::make_pair(p.first-q.first, p.second-q.second);
}

std::pair<int,int> operator/(const std::pair<int,int>& p, const int& q)
{
    return std::make_pair(p.first/q, p.second/q);
}

std::pair<int,int> abs(const std::pair<int,int>& p)
{
    return std::make_pair(std::abs(p.first), std::abs(p.second));
}

void solve()
{
    std::set<std::pair<int,int>> antinodes;
    auto insert_antinode = [&antinodes](const std::pair<int,int>& p)
    {
        if (!in_bounds(p)) return;
        antinodes.insert(p);
    };

    for (const auto& freq : antennae)
    {
        // for (int i = 0; i < freq.second.size(); i++)
        // {
        //     for (int j = 0; j < i; j++)
        //     {
        //         const auto& p = freq.second[i];
        //         const auto& q = freq.second[j];
        for (const auto& p : freq.second)
        {
            for (const auto& q : freq.second)
            {
                if (p==q) continue;
                std::pair<int,int> delta = (q-p);
                int gcd = std::gcd(std::abs(delta.first), std::abs(delta.second));
                // std::cout << "(" << delta.first << "," << delta.second << "): " << gcd << std::endl;
                delta = delta / gcd;

                std::pair<int,int> curr = p;
                while (in_bounds(curr))
                {
                    insert_antinode(curr);
                    curr = curr + delta;
                }

                curr = p;
                while (in_bounds(curr))
                {
                    insert_antinode(curr);
                    curr = curr - delta;
                }
            }
        }
    }
    // for (const auto& p : antinodes)
    // {
    //     if (map[p.first][p.second] == '.') map[p.first][p.second] = '#';
    // }
    // for (const auto& l : map)
    // {
    //     std::cout << l << std::endl;
    // }
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
            antennae[map[i][j]].push_back(std::make_pair(i,j));
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

