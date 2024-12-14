#include <bits/stdc++.h>

size_t N;
std::vector<int> n_winning;
std::vector<int> dp;

int solve_card(const std::set<int>& winning_nums, const std::vector<int>& nums)
{
    int c = 0;
    for (const auto& n : nums)
    {
        if (winning_nums.find(n) != winning_nums.end()) c++;
    }
    return c;
}

void solve()
{
    dp = std::vector<int>(N);
    for (int i = N-1; i >= 0; --i)
    {
        int s = 1;
        for (int j = i+1; j <= i+n_winning[i]; ++j)
        {
            s += dp[j];
        }
        dp[i] = s;
    }
    
    unsigned long long ans = std::accumulate(dp.begin(), dp.end(), 0);
    std::cout << ans << std::endl;
}

int main()
{
    std::string s;
    int col = 0;
    N = 0;
    std::vector<int> nums = std::vector<int>();
    std::set<int> winning_nums = std::set<int>();
    while (std::cin >> s)
    {
        if (s == "Card")
        {
            std::cin >> s;
            if (!nums.empty()) n_winning.push_back(solve_card(winning_nums, nums));
            nums.clear();
            winning_nums.clear();
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
        if (col == 0) winning_nums.insert(n);
        else nums.push_back(n);
    }
    if (!nums.empty()) n_winning.push_back(solve_card(winning_nums, nums));
    solve();
}

