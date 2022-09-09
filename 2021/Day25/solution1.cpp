#include <bits/stdc++.h>

#define Right 0
#define Down 1

struct Cucumber
{
    std::pair<int, int> pos;
    short dir;

    Cucumber(int x, int y, short dir) : pos({x, y}), dir(dir) {}
};

int X, Y;
std::array<std::vector<Cucumber>, 2> cucumbers;
std::set<std::pair<int, int>> map;


long iterate(short dir)
{
    long moves = 0;
    std::set<std::pair<int, int>> newMap = map;
    for (auto& cucumber : cucumbers[dir])
    {
        std::pair<int, int> newPos = std::make_pair(
            (cucumber.pos.first + (dir==Right ? 1 : 0)) % X,
            (cucumber.pos.second + (dir==Down ? 1 : 0)) % Y);
        if (map.find(newPos) == map.end())
        {
            newMap.erase(cucumber.pos);
            cucumber.pos = newPos;
            newMap.insert(cucumber.pos);
            ++moves;
        }
    }
    map = newMap;
    return moves;
}


void solve()
{
    long counter = 0;
    while (true)
    {
        long moves = 0;
        moves += iterate(Right);
        moves += iterate(Down);
        ++counter;
        if (moves <= 0) break;
    }
    std::cout << counter << std::endl;
}


int main()
{
    std::string s;
    int y = 0;
    while (std::cin >> s)
    {
        X = s.size();
        for (int x = 0; x < s.size(); x++)
        {
            if (s[x] == '.') continue;
            map.insert(std::make_pair(x, y));
            short dir = s[x]=='>' ? Right : Down;
            cucumbers[dir].emplace_back(x, y, dir);
        }
        ++y;
    }
    Y = y;

    solve();
}