#include <bits/stdc++.h>

std::vector<std::pair<char, int>> commands;

unsigned long long int solve()
{
    long long int X = 0, Y = 0;
    long long int wx = 10, wy = 1;

    for (auto c : commands)
    {
        if (c.first == 'N')
            wy += c.second;
        else if (c.first == 'S')
            wy -= c.second;
        else if (c.first == 'E')
            wx += c.second;
        else if (c.first == 'W')
            wx -= c.second;
        else if (c.first == 'L')
        {
            for (int i = 0; i < c.second; i += 90)
            {
                std::swap(wx, wy);
                wx *= -1;
            }
        }
        else if (c.first == 'R')
        {
            for (int i = 0; i < c.second; i += 90)
            {
                std::swap(wx, wy);
                wy *= -1;
            }
        }
        else if (c.first == 'F')
        {
            X += wx * c.second;
            Y += wy * c.second;
        }
        else
            std::cout << "Invalid command: " << c.first << c.second << std::endl;
        printf("Ship: (%lld, %lld), Waypint: (%lld, %lld)\n", X, Y, wx, wy);
    }
    return std::abs(X) + std::abs(Y);
}

int main()
{
    char a;
    int v;
    commands = std::vector<std::pair<char, int>>();
    while (std::cin >> a >> v)
    {
        commands.push_back(std::make_pair(a, v));
    }

    unsigned long long int ans = solve();
    std::cout << ans << std::endl;
}
