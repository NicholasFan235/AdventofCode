#include <bits/stdc++.h>

bool is_diffs_valid(const std::list<int>& diffs)
{
    auto prev_it = diffs.begin();
    for (auto it = ++diffs.begin(); it != diffs.end(); ++it)
    {
        if (*prev_it* *it <= 0) return false;
        if (std::abs(*it)>3) return false;
    }
    return std::abs(*diffs.begin()) <= 3;
}

bool is_valid(const std::vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        std::list<int> diffs = std::list<int>();
        
        int prev = i==0 ? 1 : 0;
        for (int j = i==0 ? 2 : 1; j < v.size(); j++)
        {
            if (j==i) continue;
            diffs.push_back(v[j]-v[prev]);
            prev = j;
        }
        if (is_diffs_valid(diffs)) return true;
    }
    return false;
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