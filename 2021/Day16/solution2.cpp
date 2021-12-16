#include <bits/stdc++.h>

std::string input;
std::vector<char> hex;
std::vector<int> binary;

unsigned long long bin2int(std::vector<int>::reverse_iterator begin, std::vector<int>::reverse_iterator end)
{
    unsigned long long i = 0;
    std::for_each(begin, end, [&](int j){ i <<= 1; i += j;});
    return i;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> v)
{
    os << "{";
    for (int i = 0; i < v.size(); i++)
    {
        os << v[i];
        if (i < v.size()-1) os << ", ";
    }
    os << "}";
    return os;
}

unsigned long long interpret_packet(std::vector<int>::reverse_iterator& it)
{
    int version = bin2int(it, std::next(it, 3));
    int type = bin2int(std::next(it, 3), std::next(it, 6));
    it += 6;
    if (type == 4)
    {
        // literal
        unsigned long long n = 0;
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
        return n;
    }
    else
    {
        int lengthType = *it;
        it++;
        std::vector<unsigned long long> subs = std::vector<unsigned long long>();
        if (lengthType == 0)
        {
            int length = bin2int(it, std::next(it, 15));
            it += 15;
            const std::vector<int>::reverse_iterator start = it;
            while (std::distance(start, it) < length)
            {
                subs.push_back(interpret_packet(it));
            }
        }
        else
        {
            int nPackets = bin2int(it, std::next(it, 11));
            it += 11;
            const std::vector<int>::reverse_iterator start = it;
            for (int pi = 0; pi < nPackets; pi++)
            {
                subs.push_back(interpret_packet(it));
            }
        }
        
        unsigned long long ans = 0;
        if (type == 0)
        {
            ans = 0;
            for (const auto i : subs) ans += i;
        }
        else if (type == 1)
        {
            ans = 1;
            for (const auto i : subs) ans *= i;
        }
        else if (type == 2)
        {
            ans = ULLONG_MAX;
            for (const auto i : subs) ans = std::min(ans, i);
        }
        else if (type == 3)
        {
            ans = 0;
            for (const auto i : subs) ans = std::max(ans, i);
        }
        else if (type == 5)
        {
            ans = subs[0] > subs[1] ? 1 : 0;
        }
        else if (type == 6)
        {
            ans = subs[0] < subs[1] ? 1 : 0;
        }
        else
        {
            if (type != 7) std::cout << "Invalid type: " << type << std::endl;
            ans = subs[0] == subs[1] ? 1 : 0;
        }
        return ans;
    }
}


void solve()
{
    auto it = binary.rbegin();
    unsigned long long ans = interpret_packet(it);
    std::cout << ans;
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
        std::cout << "Test case #" << t << ": ";
        solve();
        std::cout << std::endl;
    }
}
