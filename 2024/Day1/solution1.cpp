#include <bits/stdc++.h>

int N;
std::vector<std::vector<int>> input;


void solve()
{
    std::sort(input[0].begin(), input[0].end());
    std::sort(input[1].begin(), input[1].end());

    unsigned long long ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans += std::abs(input[0][i] - input[1][i]);
    }
    std::cout << ans << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        os << (i==0 ? "" : " ") << v[i];
    }
    return os;
}

int main()
{
    int s1, s2;
    N = 0;
    input = std::vector<std::vector<int>>(2, std::vector<int>());
    while (std::cin >> s1 >> s2)
    {
        ++N;
        input[0].push_back(s1);
        input[1].push_back(s2);
    }

    solve();
}