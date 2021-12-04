#include <bits/stdc++.h>

std::vector<std::pair<char, int>> commands;


unsigned long long int solve()
{
    long long int X = 0, Y = 0;
    int rotation = 90;

    for (auto c : commands)
    {
        if (c.first == 'N') Y += c.second;
        else if (c.first == 'S') Y -= c.second;
        else if (c.first == 'E') X += c.second;
        else if (c.first == 'W') X -= c.second;
        else if (c.first == 'L')
            rotation = (rotation - c.second + 360) % 360;
        else if (c.first == 'R')
            rotation = (rotation + c.second) % 360;
        else if (c.first == 'F')
        {
            if (rotation%90 != 0) std::cout << "Bad rotation: " << rotation << std::endl;
            else if (rotation == 90) X += c.second;
            else if (rotation == 270) X -= c.second;
            else if (rotation == 0) Y += c.second;
            else if (rotation == 180) Y -= c.second; 
        }
        else std::cout << "Invalid command: " << c.first << c.second << std::endl;
        printf("(%lld, %lld)\n", X, Y);
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
