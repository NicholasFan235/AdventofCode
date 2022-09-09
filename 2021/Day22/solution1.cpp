#include <bits/stdc++.h>

#include "region.hpp"
#include "helpers.hpp"

std::vector<Instruction> instructions;

void solve()
{
    std::cout << instructions << std::endl;

    Region r = Region(Point(-50, -50, -50), Point(51, 51, 51));
    for (const auto& instruction : instructions)
    {
        r.split_x(instruction.region.p1.x);
        r.split_x(instruction.region.p2.x);
        r.split_y(instruction.region.p1.y);
        r.split_y(instruction.region.p2.y);
        r.split_z(instruction.region.p1.z);
        r.split_z(instruction.region.p2.z);
        r.set_if(instruction.region, instruction.on);
        std::cout << r.count() << " cubes on, " << r.num_regions() << " regions" << std::endl;
    }
    std::cout << r.count() << std::endl;
}


int main()
{
    std::regex instruction_regex("(on|off) x=(-?\\d+)\\.\\.(-?\\d+),y=(-?\\d+)\\.\\.(-?\\d+),z=(-?\\d+)\\.\\.(-?\\d+)");
    std::string s;
    instructions = std::vector<Instruction>();
    while (std::getline(std::cin, s))
    {
        std::smatch matches;
        auto match = std::regex_search(s, matches, instruction_regex);
        bool on = matches[1] == "on";
        int x1 = stoi(matches[2]), x2 = stoi(matches[3])+1;
        int y1 = stoi(matches[4]), y2 = stoi(matches[5])+1;
        int z1 = stoi(matches[6]), z2 = stoi(matches[7])+1;

        instructions.emplace_back(on, Region(Point(x1,y1,z1), Point(x2,y2,z2)));
    }

    solve();
}