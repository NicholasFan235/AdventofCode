#include <bits/stdc++.h>


std::vector<std::string> springs;
std::vector<std::string> signatures;
std::vector<std::vector<int>> spring_groups;
std::vector<unsigned long long> ways;



template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << (i==0 ? "" : " ") << v[i];
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& v)
{
    for (const auto& r : v) os << r << std::endl;
    return os;
}


unsigned long long count_ways(const std::string& row, const std::vector<int>& groups)
{
    std::vector<std::vector<unsigned long long>> dp = std::vector<std::vector<unsigned long long>>(
        groups.size()+1, std::vector<unsigned long long>(row.size()+1, 0));
    for (int j = 1; j < dp[0].size(); j++)
    {
        if (row[j-1] == '#') break;
        dp[0][j] = 1;
    }
    //for (int i = 0; i < dp.size(); i++) dp[i][0] = 1;
    dp[0][0] = 1;

    for (int i = 1; i < groups.size()+1; i++)
    {
        std::vector<bool> has_contiguous_group = std::vector<bool>(row.size(), false);
        std::vector<int> latest_forced = std::vector<int>(row.size(), 0);
        int ctr = 0;
        int latest = 0;
        for (int j = 0; j < row.size(); j++)
        {
            if (row[j] == '.') ctr = 0;
            else
            {
                if (++ctr >= groups[i-1]) has_contiguous_group[j] = true;
            }

            if (row[j] == '#') latest = j;
            latest_forced[j] = latest;
        }
        //std::cout << "Has contigous group of " << groups[i-1] << ": " << has_contiguous_group << std::endl;

        for (int j = 0; j < row.size(); j++)
        {
            // Contiguous group of groups[i] springs with empty at position j
            if (row[j] == '#')
            {
                dp[i][j+1] = 0;
                continue;
            }

            int latest_forced = 0;
            for (int k = 0; k < j; k++)
            {
                if (row[k] == '#') latest_forced = k;
            }
            
            for (int k = latest_forced; k < j; k++)
            {
                // dp[i-1][k-1] * is contiguous group possible starting from k
                //if (k-groups[i-1] < 0) continue;
                if (has_contiguous_group[k])
                {
                    dp[i][j+1] += dp[i-1][k-groups[i-1]+1];
                }
            }
        }
    }
    //std::cout << dp;
    return dp[groups.size()].back();
}

void solve()
{
    std::vector<unsigned long long> ways = std::vector<unsigned long long>();
    for (int i = 0; i < springs.size(); i++)
    {
        unsigned long long c = count_ways(springs[i], spring_groups[i]);
        ways.push_back(c);
    }
    
    unsigned long long ans = std::accumulate(ways.begin(), ways.end(), 0ull);
    std::cout << ans << std::endl;
}

void process_signatures()
{
    spring_groups = std::vector<std::vector<int>>();
    for (int i = 0; i < signatures.size(); i++)
    {
        spring_groups.push_back(std::vector<int>());
        std::stringstream ss(signatures[i]);
        int n;
        char c;
        while (ss >> n)
        {
            spring_groups.back().push_back(n);
            if (!ss) break;
            ss >> c;
        }
    }
}

int main()
{
    springs = std::vector<std::string>();
    signatures = std::vector<std::string>();
    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) continue;
        //springs.push_back(s + '.');
        springs.push_back(s+"?"+s+"?"+s+"?"+s+"?"+s+'.');
        std::cin >> s;
        //signatures.push_back(s);
        signatures.push_back(s+","+s+","+s+","+s+","+s);
    }
    process_signatures();
    solve();
}
