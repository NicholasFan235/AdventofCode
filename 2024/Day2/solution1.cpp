#include <bits/stdc++.h>

bool is_valid(const std::vector<int>& v)
{
    std::vector<int> diffs = std::vector<int>(v.size()-1, 0);
    for (int i = 1; i < v.size(); i++) diffs[i-1] = v[i]-v[i-1];

    for (int i = 1; i < diffs.size(); i++)
    {
        if (diffs[i]*diffs[i-1] <= 0) return false;
        if (std::abs(diffs[i])>3) return false;
    }
    return std::abs(diffs[0])<=3;
}

int main()
{
    unsigned long long ans = 0;

    std::string line;
    while (std::getline(std::cin, line, '\n'))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        
        std::vector<int> row = std::vector<int>();
        int n;
        while (ss >> n) row.push_back(n);

        ans += is_valid(row);
    }

    std::cout << ans << std::endl;
}