#include <bits/stdc++.h>


std::vector<std::pair<std::string, int>> memory;
std::map<int, int> history;
int accumulator;

int perform(int i)
{
    if (i < 0 || i >= memory.size()) return -2;
    const auto& instruction = memory[i];
    if (history.find(i) != history.end()) return 0;
    if (instruction.first == "nop")
    {
        history[i] = accumulator;
        return perform(i+1);
    }
    else if (instruction.first == "acc")
    {
        accumulator += instruction.second;
        history[i] = accumulator;
        return perform(i+1);
    }
    else if (instruction.first == "jmp")
    {
        history[i] = accumulator;
        return perform(i+instruction.second);
    }
    std::cout << "Invalid instruction: \"" << instruction.first << "\"" << std::endl;
    return -1;
}

void solve()
{
    history = std::map<int, int>();
    accumulator = 0;
    int err = perform(0);
    std::cout << accumulator << std::endl;
}


int main()
{
    std::string instruction;
    int val;
    memory = std::vector<std::pair<std::string, int>>();
    while (!std::cin.eof())
    {
        std::cin >> instruction >> val;
        memory.push_back(std::make_pair(instruction, val)); 
    }

    solve();
}



