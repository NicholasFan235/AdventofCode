#include <bits/stdc++.h>

std::pair<int, int> xBounds;
std::pair<int, int> yBounds;


template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T, U> p)
{
    std::cout << "(" << p.first << ", " << p.second << ")";
    return os;
}

bool isPossible(int vx, int vy)
{
    int x = 0, y = 0;
    while (y >= yBounds.first)
    {
        if (x >= xBounds.first && x <= xBounds.second && y >= yBounds.first && y <= yBounds.second)
            return true;
        x += vx; y += vy;
        if (vx > 0) vx--;
        vy--;
    }
    return false;
}

unsigned long long solve()
{
    unsigned long long ctr = 0;
    for (int x = 0; x <= xBounds.second; x++)
    {
        for (int y = -std::abs(yBounds.first); y < std::abs(yBounds.first); y++)
        {
            ctr += isPossible(x, y) ? 1 : 0;
        }
    }
    return ctr;
}


int main()
{
    std::string s;
    std::regex regex("target area: x=(-?[0-9]*)\\.\\.(-?[0-9]*), y=(-?[0-9]*)\\.\\.(-?[0-9]*)");
    getline(std::cin, s);
    std::smatch match;
    if (std::regex_search(s, match, regex))
    {
        xBounds = std::make_pair(atoi(match[1].str().c_str()), atoi(match[2].str().c_str()));
        yBounds = std::make_pair(atoi(match[3].str().c_str()), atoi(match[4].str().c_str()));
    }
    std::cout << "target area: x=" << xBounds << ", y=" << yBounds << std::endl;
    std::cout << solve() << std::endl;
}

