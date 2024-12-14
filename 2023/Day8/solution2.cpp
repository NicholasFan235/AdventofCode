#include <bits/stdc++.h>
#include <numeric>


std::string instructions;
std::map<std::string, std::pair<std::string, std::string>> network;

std::regex regex("^(.{3}) = \\((.{3}), (.{3})\\)$");

std::vector<long long> paths;

void solve()
{
    paths = std::vector<long long>();

    std::vector<std::string> locations;
    for (const auto& p : network) if (p.first[2] == 'A') locations.push_back(p.first);
    
    for (int i = 0; i < locations.size(); i++)
    {
        long long moves = 0;
        while (locations[i][2] != 'Z')
        {
            //std::cout << location << std::endl;

            char direction = instructions[moves++%instructions.size()];
            if (direction == 'L')
            {
                locations[i] = network[locations[i]].first;
            }
            else if (direction == 'R')
            {
                locations[i] = network[locations[i]].second;
            }
            else
            {
                std::cout << "Invalid Direction: " << direction << std::endl;
            }
        }
        paths.push_back(moves);
        std::cout << moves << std::endl;
    }
    
    long long ans = std::accumulate(paths.begin(), paths.end(), 1ll, 
        [](const long long& l, const long long& r) { return std::lcm<long long, long long>(l,r); });
    std::cout << ans << std::endl;
}


int main()
{
    std::cin >> instructions;

    std::string line;
    while (getline(std::cin, line))
    {
        if (line.empty()) continue;
        std::smatch match;
        if (std::regex_match(line, match, regex))
        {
            network[match[1].str()] = std::make_pair(match[2].str(), match[3].str());
        }
        else
        {
            std::cout << "Unable to process line: " << line << std::endl;
        }
    }
    solve();
}