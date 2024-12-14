#include <bits/stdc++.h>


std::string instructions;
std::map<std::string, std::pair<std::string, std::string>> network;

std::regex regex("^([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)$");


void solve()
{
    std::string location = "AAA";
    unsigned long long moves = 0;
    while (true)
    {
        //std::cout << location << std::endl;
        if (location == "ZZZ") break;

        char direction = instructions[moves++%instructions.size()];
        if (direction == 'L')
        {
            location = network[location].first;
        }
        else if (direction == 'R')
        {
            location = network[location].second;
        }
        else
        {
            std::cout << "Invalid Direction: " << direction << std::endl;
        }
    }
    std::cout << moves << std::endl;
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