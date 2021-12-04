#include <bits/stdc++.h>

std::vector<std::vector<bool>> map;
int m;

int solve()
{
    int ctr = 0;
    for (int i = 1; i < map.size(); i++)
    {
        ctr += map[i][i*3 % m];
    }
    return ctr;
}

int main()
{
    std::string l;
    map = std::vector<std::vector<bool>>();
    while (std::cin >> l)
    {
        std::vector<bool> row = std::vector<bool>(l.length());
        for (int i = 0; i < l.length(); i++)
        {
            row[i] = l[i] == '#';
        }
        map.push_back(row);
    }
    m = static_cast<int>(map[0].size());

    int ans = solve();
    std::cout << ans << std::endl;

}