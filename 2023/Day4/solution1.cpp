#include <bits/stdc++.h>

size_t N;
std::vector<std::vector<int>> nums;
std::vector<std::set<int>> winning_nums;

void solve()
{
    unsigned long long ans = 0;
    for (size_t i = 0; i < N; i++)
    {
        unsigned long long val = 0;
        for (const auto& num : nums.at(i))
        {
            if (winning_nums.at(i).find(num) != winning_nums.at(i).end())
            {
                val = std::max(1ull, val*2);
            }
        }
        //std::cout << "Card " << i << ": " << val << std::endl;
        ans += val;
    }
    std::cout << ans << std::endl;
}

int main()
{
    std::string s;
    int col = 0;
    N = 0;
    while (std::cin >> s)
    {
        if (s == "Card")
        {
            std::cin >> s;
            nums.push_back(std::vector<int>());
            winning_nums.push_back(std::set<int>());
            col = 0;
            ++N;
            continue;
        }
        if (s == "|")
        {
            ++col;
            continue;
        }
        int n = atoi(s.c_str());
        if (col == 0) winning_nums.back().insert(n);
        else nums.back().push_back(n);
    }
    solve();
}

