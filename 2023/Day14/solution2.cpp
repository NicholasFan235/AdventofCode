#include <bits/stdc++.h>


std::vector<std::string> rocks;
std::map<std::string, int> state_load;
std::map<std::string, int> node_number;

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v)
{
    for (const auto& s : v) os << s << std::endl;
    return os;
}

void tilt_north()
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

void tilt_south()
{
    for (int j = 0; j < rocks[0].size(); j++)
    {
        int l = rocks.size()-1, u = rocks.size();
        while (--u >= 0)
        {
            if (rocks[u][j] == 'O') std::swap(rocks[u][j], rocks[l--][j]);
            else if (rocks[u][j] == '#') l = u-1;
        }
    }
}

void tilt_east()
{
    for (int i = 0; i < rocks.size(); i++)
    {
        int l = rocks[i].size(), r = rocks[i].size()-1;
        while (--l >= 0)
        {
            if (rocks[i][l] == 'O') std::swap(rocks[i][l], rocks[i][r--]);
            else if (rocks[i][l] == '#') r = l-1;
        }
    }
}

void tilt_west()
{
    for (int i = 0; i < rocks.size(); i++)
    {
        int l = 0, r = -1;
        while (++r < rocks[i].size())
        {
            if (rocks[i][r] == 'O') std::swap(rocks[i][r], rocks[i][l++]);
            else if (rocks[i][r] == '#') l = r+1;
        }
    }
}

void tilt_cycle()
{
    tilt_north();
    tilt_west();
    tilt_south();
    tilt_east();
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

std::string hash_state()
{
    return std::accumulate(rocks.begin(), rocks.end(), std::string());
}

void solve()
{
    std::string hash = hash_state();
    state_load[hash] = calculate_load();
    node_number[hash] = 0;

    for (int i = 0; i < 1000000000; i++)
    {
        tilt_cycle();
        hash = hash_state();
        if (node_number.find(hash) != node_number.end()) break;
        state_load[hash] = calculate_load();
        node_number[hash] = i+1;
    }

    //std::cout << node_number.size() << ", " << node_number[hash] << std::endl;
    int ans_node_num = (1000000000-node_number[hash])%(node_number.size() - node_number[hash]) + node_number[hash];
    //std::cout << ans_node_num << std::endl;

    for (const auto& p : state_load)
    {
        //std::cout << node_number[p.first] << ": " << p.second << std::endl;
        if (node_number[p.first] == ans_node_num) std::cout << p.second << std::endl;
    }
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
