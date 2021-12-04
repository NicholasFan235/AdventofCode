#include <bits/stdc++.h>


std::vector<std::pair<std::string, int>> instructions;
std::map<std::string, int> accumulated;

long long int solve()
{
    std::cout << "Forward: " << accumulated["forward"]
        << ", Depth: " << accumulated["depth"] << std::endl;
    return (accumulated["forward"] * accumulated["depth"]);
}

int main()
{
    std::string dir;
    int n;
    while (std::cin >> dir >> n)
    {
        instructions.push_back(std::make_pair(dir, n));
        if (dir == "forward")
        {
            accumulated["forward"] += n;
        }
        else if (dir == "up")
        {
            accumulated["depth"] -= n;
            if (accumulated["depth"] < 0) std::cout << "Invalid Depth" << std::endl;
        }
        else if (dir == "down")
        {
            accumulated["depth"] += n;
        }
        else
        {
            std::cout << "Invalid Directon" << std::endl;
        }
    }
    
    long long int ans = solve();
    std::cout << ans << std::endl;
}