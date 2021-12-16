#include <bits/stdc++.h>

std::string input;
std::vector<char> hex;
std::vector<int> binary;

int versionSum = 0;

int bin2int(std::vector<int>::reverse_iterator begin, std::vector<int>::reverse_iterator end)
{
    int i = 0;
    std::for_each(begin, end, [&](int j){ i <<= 1; i += j;});
    return i;
}

struct literal {int version; int type; int value;};
struct op {int version; int type; std::vector<int>::reverse_iterator start; };

void interpret_packet(std::vector<int>::reverse_iterator& it)
{
    int version = bin2int(it, std::next(it, 3));
    versionSum += version;
    int type = bin2int(std::next(it, 3), std::next(it, 6));
    it += 6;
    if (type == 4)
    {
        // literal
        int n = 0;
        while (*it == 1)
        {
            ++it;
            n += bin2int(it, std::next(it, 4));
            n <<= 4;
            it += 4;
        }
        ++it;
        n += bin2int(it, std::next(it, 4));
        it += 4;
        std::cout << n << " ";
    }
    else
    {
        int lengthType = *it;
        it++;
        std::cout << "{ ";
        if (lengthType == 0)
        {
            int length = bin2int(it, std::next(it, 15));
            it += 15;
            const std::vector<int>::reverse_iterator start = it;
            while (std::distance(start, it) < length)
            {
                interpret_packet(it);
            }
        }
        else if (lengthType == 1)
        {
            int nPackets = bin2int(it, std::next(it, 11));
            it += 11;
            const std::vector<int>::reverse_iterator start = it;
            for (int pi = 0; pi < nPackets; pi++)
            {
                interpret_packet(it);
            }
        }
        std::cout << "}";
    }
}


void solve()
{
    auto it = binary.rbegin();
    interpret_packet(it);
    std::cout << std::endl << "Sum of Versions: " << versionSum;
}

void printBinary()
{
    for (int i = binary.size()-1; i >= 0; --i) std::cout << binary[i];
    std::cout << std::endl;
}

void reset()
{
    input.clear();
    hex = std::vector<char>();
    binary = std::vector<int>();
    versionSum = 0;
}

int main()
{
    int T;
    std::cin >> T;
    for (int t = 1; t <= T; t++)
    {
        reset();
        std::cin >> input;
        for (int i = input.length()-1; i>=0; --i)
        {
            int n = input[i] - '0';
            if (n > 9) n = input[i] - 'A' + 10;
            for (int j = 0; j < 4; j++)
            {
                binary.push_back(n%2);
                n >>= 1;
            }
            hex.push_back(input[i]);
        }
        printBinary();
        std::cout << "Test case #" << t << ": ";
        solve();
        std::cout << std::endl;
    }
}
