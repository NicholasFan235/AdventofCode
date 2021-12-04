#include <bits/stdc++.h>

using namespace std;

std::vector<int> depths;

int solve()
{
    int prev = depths[0];
    int ctr = 0;
    for (int i = 1; i < depths.size(); i++)
    {
        ctr += (depths[i] > prev) ? 1 : 0;
        prev = depths[i];
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

    int ans = solve();
    std::cout << ans << std::endl;
}
