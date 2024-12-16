#include <bits/stdc++.h>


std::vector<std::string> world;
std::pair<int,int> robot;
std::string instructions;

template <typename T, typename U>
inline std::pair<T,U> operator+(const std::pair<T,U> p, const std::pair<T,U> q) { return std::make_pair(p.first+q.first, p.second+q.second); }
template <typename T, typename U>
inline std::pair<T,U> operator-(const std::pair<T,U> p, const std::pair<T,U> q) { return std::make_pair(p.first-q.first, p.second-q.second); }

std::map<char, std::pair<int,int>> directions = {{'^',{-1,0}},{'v',{1,0}},{'<',{0,-1}},{'>',{0,1}}};

inline char& at(const std::pair<int,int> p) { return world.at(p.first).at(p.second); }

bool move(const std::pair<int,int> p, const std::pair<int,int> dir)
{
    if (at(p+dir) == '#') return false;
    
    if (at(p+dir) == '.' || move(p+dir, dir))
    {
        std::swap(at(p), at(p+dir));
        return true;
    }
    return false;
}

void printworld()
{
    for (const auto& s : world) std::cout << s << std::endl;
}

void count_world()
{
    unsigned long long ans = 0;
    for (int i = 0; i < world.size(); i++)
    {
        for (int j = 0; j < world.at(i).size(); j++)
        {
            if (world.at(i).at(j) != 'O') continue;
            ans += 100*i + j;
        }
    }
    std::cout << ans << std::endl;
}

void solve()
{
    // printworld();
    for (const auto c : instructions)
    {
        std::pair<int,int> dir = directions.at(c);
        if (move(robot, dir)) robot = robot+dir;
    }
    printworld();
    count_world();
}

int main()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;
        world.push_back(line);
    }
    std::stringstream ss;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;
        ss << line;
    }
    for (int i = 0; i < world.size(); i++)
    {
        for (int j = 0; j < world.at(i).size(); j++)
        {
            if (world.at(i).at(j) == '@')
            {
                robot = std::make_pair(i,j);
            }
        }
    }
    instructions = ss.str();
    solve();
}

