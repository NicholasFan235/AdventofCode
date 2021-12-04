#include <bits/stdc++.h>


std::vector<int> numbers;

int solve()
{
    std::set<int> nSet = std::set<int>();
    for (int n : numbers)
    {
        if (nSet.find(2020-n) != nSet.end()) return n * (2020-n);
        nSet.insert(n);
    }
    return 0;
}


int main()
{
    int n;
    numbers = std::vector<int>();
    while (std::cin >> n)
    {
        numbers.push_back(n);
    }

    int ans = solve();
    std::cout << ans << std::endl;
}