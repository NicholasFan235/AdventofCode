#include <bits/stdc++.h>


unsigned long long int threshold = ULLONG_MAX/2024;

std::map<unsigned long long int, unsigned long long int> stones;


void blink()
{
    std::map<unsigned long long int, unsigned long long int> new_stones;

    for (const auto& s : stones)
    {
        if (s.first==0)
        {
            new_stones[1] += s.second;
            continue;
        }

        int n_digits = std::log10(s.first)+1;
        if ((n_digits>1) && (n_digits%2==0))
        {
            unsigned long long int div = std::pow(10, n_digits/2);
            new_stones[s.first/div] += s.second;
            new_stones[s.first%div] += s.second;
            continue;
        }

        if (s.first >= threshold) throw std::runtime_error("Integer overflow");
        new_stones[s.first*2024] += s.second;
    }

    std::swap(stones, new_stones);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
        os << (i==0?"" : " ") << v[i];
    return os;
}

unsigned long long int n_stones()
{
    unsigned long long int ans = 0;
    for (const auto& s : stones) ans += s.second;
    return ans;
}

void solve()
{
    for (int i = 0; i < 75; i++)
    {
        blink();
        std::cout << i+1 << ": " << n_stones() << std::endl;
        // std::cout << stones << std::endl;
    }
}

int main()
{
    unsigned long long int s;
    while (std::cin >> s) stones[s]++;

    solve();
}
