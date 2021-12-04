#include <bits/stdc++.h>

std::vector<int> depths;

unsigned long solve()
{
    unsigned long ctr = 0;
    int prev = depths[0] + depths[1] + depths[2];
    for (int i = 3; i < depths.size(); i++)
    {
        int next = prev - depths[i-3] + depths[i];
        ctr += (next > prev) ? 1 : 0;
        prev = next;
    }
    return ctr;
}

int main()
{
    int n;
    depths = std::vector<int>();
    while (std::cin >> n)
    {
        depths.push_back(n);
    }

    unsigned long ans = solve();
    std::cout << ans << std::endl;
}