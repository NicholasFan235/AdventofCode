#include <bits/stdc++.h>

enum command
{
    forward, up, down
};

std::vector<std::pair<command, int>> instructions;

long long int solve()
{
    int pitch = 0;
    long long int pos = 0;
    long long int depth = 0;
    for (const auto& i : instructions)
    {
        switch (i.first)
        {
            case command::forward:
                pos += i.second;
                depth += i.second * pitch;
                break;
            case command::up:
                pitch -= i.second;
                break;
            case command::down:
                pitch += i.second;
                break;
        }
    }
    return pos * depth;
}

int main()
{
    std::string dir;
    int n;
    while (std::cin >> dir >> n)
    {
        if (dir == "forward") instructions.push_back(std::make_pair(command::forward, n));
        else if (dir == "down") instructions.push_back(std::make_pair(command::down,n));
        else if (dir == "up") instructions.push_back(std::make_pair(command::up, n));
        else std::cout << "Invalid direction" << std::endl;
    }
    
    long long int ans = solve();
    std::cout << ans << std::endl;
}