#include <bits/stdc++.h>

int N;
std::array<std::map<int, int>, 2> input;


void solve()
{
    unsigned long long ans = std::accumulate(input[0].begin(), input[0].end(), 0,
    [&](const unsigned long long& ans, const std::pair<int, int>& p)
    {
        return ans + p.first * p.second * input[1][p.first];
    });
    std::cout << ans << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        os << (i==0 ? "" : " ") << v[i];
    }
    return os;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    std::cout << p.first << ", " << p.second;
    return os;
}


template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::map<T,U>& m)
{
    for (const std::pair<T,U>& p : m) std::cout << p << std::endl;
    return os;
}

int main()
{
    int s1, s2;
    while (std::cin >> s1 >> s2)
    {
        ++N;
        ++input[0][s1];
        ++input[1][s2];
    }
    solve();
}