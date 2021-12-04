#include <bits/stdc++.h>

class Memory
{
public:
    std::vector<std::bitset<36>> onesMasks;
    std::vector<std::bitset<36>> zerosMasks;
    std::unordered_map<unsigned long long int, std::bitset<36>> memory;

    Memory() :
        onesMasks(),
        zerosMasks(),
        memory()
    {}

    void set(size_t location, unsigned long val)
    {
        for (int i = 0; i < onesMasks.size(); i++)
        {
            std::bitset<36> loc(location);
            loc |= onesMasks[i];
            loc &= ~zerosMasks[i];
            memory[loc.to_ullong()] = val;
        }
    }

    void mask(const std::string &m)
    {
        if (m.length() != 36)
            std::cout << "Invalid Mask Size" << std::endl;
        //std::cout << "Mask: " << m << std::endl;
        zerosMasks.clear();
        onesMasks.clear();
        std::vector<int> xPositions;
        std::bitset<36> baseMask;
        std::bitset<36> dynBits;
        for (int i = 0; i < m.length(); i++)
        {
            if (m[35-i]=='X')
            {
                xPositions.push_back(i);
                dynBits[i] = 1;
            }
            else if (m[35-i] == '1')
            {
                baseMask[i] = 1;
            }
        }

        for (unsigned long long int i = 0; i < (unsigned long long int)1<<xPositions.size(); i++)
        {
            std::bitset<36> dynMask = std::bitset<36>();
            for (int j = 0; j < xPositions.size(); j++)
            {
                dynMask[xPositions[j]] = (i>>j)%2;
            }
            zerosMasks.push_back(dynBits & ~dynMask);
            onesMasks.push_back(baseMask | (dynBits & dynMask));
        }

        /*std::cout << "Ones Masks:" << std::endl;
        for (const auto i : zerosMasks) std::cout << i << std::endl;
        std::cout << "Zeros Masks:" << std::endl;
        for (const auto i : onesMasks) std::cout << i << std::endl;*/
    }

    unsigned long long sum()
    {
        unsigned long long ans = 0;
        for (const auto p : memory)
            ans += p.second.to_ullong();
        return ans;
    }
};

int main()
{
    Memory memory = Memory();

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
        else
            std::cout << "Invalid Command: " << command << std::endl;
    }

    std::cout << memory.sum() << std::endl;
}
