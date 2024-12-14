#include <bits/stdc++.h>


std::vector<std::string> rocks;

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v)
{
    for (const auto& s : v) os << s << std::endl;
    return os;
}

void tilt()
{
    for (int j = 0; j < rocks[0].size(); j++)
    {
        int u = 0, l = -1;
        while (++l < rocks.size())
        {
            if (rocks[l][j] == 'O') std::swap(rocks[l][j], rocks[u++][j]);
            else if (rocks[l][j] == '#') u = l+1;
        }
    }
}

unsigned long long calculate_load()
{
    unsigned long long ret = 0;
    for (int i = 0; i < rocks.size(); i++)
    {
        for (int j = 0; j < rocks[i].size(); j++)
        {
            if (rocks[i][j] == 'O') ret += rocks.size() - i;
        }
    }
    return ret;
}

void solve()
{
    tilt();
    unsigned long long ans = calculate_load();
    std::cout << ans << std::endl;
}

int main()
{
    rocks = std::vector<std::string>();
    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) break;
        rocks.push_back(s);
    }
    solve();
}
