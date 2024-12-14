#include <bits/stdc++.h>

std::vector<std::string> input;


int hash(std::string s)
{
    int ans = 0;
    for (const char& c : s) ans = ((ans+static_cast<int>(c))*17)%256;
    return ans;
}

void solve()
{
    std::vector<int> hashes = std::vector<int>(input.size(),0);
    for (int i = 0; i < input.size(); i++) hashes[i] = hash(input[i]);

    unsigned long long ans = std::accumulate(hashes.begin(), hashes.end(), 0ull);
    std::cout << ans << std::endl;
}

int main()
{
    std::string s;
    while (getline(std::cin, s, ','))
    {
        if (s.empty()) continue;
        if (s.back() == '\n') s.pop_back();
        input.push_back(s);
    }
    solve();
}