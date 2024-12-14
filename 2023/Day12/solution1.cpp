#include <bits/stdc++.h>


std::vector<std::string> springs;
std::vector<std::string> signatures;
std::vector<unsigned long long> ways;



std::string create_signature(const std::string& s)
{
    std::stringstream ss;
    int ctr = 0;
    for (const char c : s)
    {
        if (c == '#') ctr++;
        else
        {
            if (ctr > 0) ss << ctr << ",";
            ctr = 0;
        }
    }
    if (ctr > 0) ss << ctr << ",";
    std::string result = ss.str();
    result.pop_back();
    return result;
}

unsigned long long count_ways(std::string s, const std::string& target, int pos=0)
{
    if (pos == s.size())
    {
        std::string signature = create_signature(s);
        return (target == signature ? 1 : 0);
    }
    if (s[pos] == '?')
    {
        unsigned long long tmp = 0;
        s[pos] = '#';
        tmp += count_ways(s, target, pos+1);
        s[pos] = '.';
        tmp += count_ways(s, target, pos+1);
        return tmp;
    }
    else
    {
        return count_ways(s, target, pos+1);
    }
}

void solve()
{
    ways = std::vector<unsigned long long>();
    for (int i = 0; i < springs.size(); i++)
    {
        unsigned long long c = count_ways(springs[i], signatures[i]);
        ways.push_back(c);
    }

    unsigned long long ans = std::accumulate(ways.begin(), ways.end(), 0ull);
    std::cout << ans << std::endl;
}

int main()
{
    springs = std::vector<std::string>();
    signatures = std::vector<std::string>();
    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) continue;
        springs.push_back(s);
        std::cin >> s;
        signatures.push_back(s);
    }
    solve();
}
