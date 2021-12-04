#include <bits/stdc++.h>


std::vector<int> numbers;

int solve()
{
    std::map<int, int> numMap = std::map<int, int>();
    for (const int n : numbers)
    {
        for (const std::pair<int, int> p : numMap)
        {
            if (p.second < 1) continue;
            int missing = 2020 - n - p.first;
            if (missing < 0) continue;
            if (numMap[missing] > 0)
            {
                if (p.first == missing && numMap[missing] < 2) continue;
                printf("%d, %d, %d\n", n, p.first, missing);
                return n * p.first * missing;
            }
        }
        numMap[n]++;
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