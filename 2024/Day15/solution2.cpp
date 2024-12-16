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


void printworld()
{
    for (const auto& s : world) std::cout << s << std::endl;
}

bool can_move(const std::pair<int,int> p, const std::pair<int,int> dir)
{
    // std::cout << "(" << p.first << "," << p.second << "): " << at(p+dir) << std::endl;
    switch (at(p+dir))
    {
        case '#': return false;
        case '.': return true;
        case '[':
        {
            if (dir == directions.at('<')) return can_move(p+dir,dir);
            if (dir == directions.at('>')) return can_move(p+dir+dir, dir);
            return can_move(p+dir, dir) && can_move(std::make_pair(p.first, p.second+1)+dir, dir);
        }
        case ']':
        {
            if (dir == directions.at('>')) return can_move(p+dir,dir);
            if (dir == directions.at('<')) return can_move(p+dir+dir, dir);
            return can_move(p+dir, dir) && can_move(std::make_pair(p.first, p.second-1)+dir, dir);
        }
        default: throw std::runtime_error("Unknown object in can_move: " + std::string(1,at(p+dir)));
    }
}

void move(const std::pair<int,int> p, const std::pair<int,int> dir)
{
    // std::cout << "(" << p.first << "," << p.second << "): " << at(p+dir) << std::endl;
    switch (at(p+dir))
    {
        case '.':
        {
            std::swap(at(p), at(p+dir)); return;
        }
        case '[':
        {
            move(p+dir, dir);
            if (dir != directions.at('>') && dir != directions.at('<')) {move(std::make_pair(p.first, p.second+1)+dir, dir);}
            move(p,dir); return;
        }
        case ']':
        {
            move(p+dir, dir);
            if (dir != directions.at('>') && dir != directions.at('<')) move(std::make_pair(p.first, p.second-1)+dir, dir);
            move(p,dir); return;
        }
        case '#': throw std::runtime_error("Cannot move into wall");
        default: throw std::runtime_error("Unknown object in move: " + std::string(1,at(p+dir)));
    }
}

void count_world()
{
    unsigned long long ans = 0;
    for (int i = 0; i < world.size(); i++)
    {
        for (int j = 0; j < world.at(i).size(); j++)
        {
            if (world.at(i).at(j) != '[') continue;
            ans += 100*i + j;
        }
    }
    std::cout << ans << std::endl;
}

inline bool try_move(const std::pair<int,int> p, const char c)
{
    std::pair<int,int> dir = directions.at(c);
    // std::cout << "(" << robot.first << "," << robot.second << ") -> " << c << std::endl;
    if (can_move(p,dir))
    {
        // std::cout << "Can Move" << std::endl;
        move(p,dir);
        return true;
    }
    return false;
}

void solve()
{
    for (const auto c : instructions)
    {
        if (try_move(robot, c)) robot = robot+directions.at(c);
    }
    count_world();
}

int main()
{
    std::string line;
    std::stringstream ss;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;
        ss.str(std::string());
        for (const auto c : line)
        {
            switch (c)
            {
            case '#':
                ss << "##"; break;
            case 'O':
                ss << "[]"; break;
            case '.':
                ss << ".."; break;
            case '@':
                ss << "@."; break;
            default:
                throw std::runtime_error("Unknown box");
            }
        }
        world.push_back(ss.str());
    }
    ss.str(std::string());
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

