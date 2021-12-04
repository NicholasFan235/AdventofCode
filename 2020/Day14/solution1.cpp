#include <bits/stdc++.h>


class Memory
{
public:
    unsigned long onesMask = 0, zerosMask = 0;
    std::vector<unsigned long> memory;

    Memory(size_t n):
        memory(n, 0)
    {}

    void set(size_t location, unsigned long val)
    {
        if (location > memory.size()) std::cout << "Out of range" << std::endl;
        //std::cout << val << " -> ";
        val |= onesMask;
        val &= ~zerosMask;
        memory[location] = val;
        //std::cout << val << std::endl;
    }

    void mask(const std::string& m)
    {
        if (m.length() != 36) std::cout << "Invalid Mask Size" << std::endl;
        onesMask = 0;
        zerosMask = 0;
        for (const char c : m)
        {
            if (c == '1') onesMask++;
            if (c=='0') zerosMask++;
            onesMask <<= 1;
            zerosMask <<= 1;
        }
        onesMask >>= 1;
        zerosMask >>= 1;
        //std::cout << m << std::endl;
        //std::cout << std::bitset<37>(onesMask) << std::endl;
        //std::cout << std::bitset<37>(zerosMask) << std::endl;
    }

    unsigned long long sum()
    {
        unsigned long long ans = 0;
        for (const auto i : memory) ans += i;
        return ans;
    }

};



int main()
{
    Memory memory = Memory(100000);

    std::string command;
    while (std::cin >> command)
    {
        if (command == "mask")
        {
            std::string mask;
            std::cin >> mask;
            memory.mask(mask);
        }
        else if (command == "mem")
        {
            size_t loc;
            unsigned long val;
            std::cin >> loc >> val;
            memory.set(loc, val);
        }
        else std::cout << "Invalid Command: " << command << std::endl;
    }

    std::cout << memory.sum() << std::endl;
}

