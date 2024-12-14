#include <bits/stdc++.h>


std::vector<std::string> input;



void solve()
{
    long long int sol = 0;
    for (std::string s : input)
    {
        while (s.back() - '0' > 9) s.pop_back();
        int i = 0;
        while (s[i] - '0' > 9) ++i;
        std::cout << s[i] << s.back() << std::endl;
        sol += (s[i] - '0') * 10 + s.back() - '0';
    }
    std::cout << sol << std::endl;
}


int main()
{
    input = std::vector<std::string>();
    std::string s;
    while (std::cin >> s)
    {
        input.push_back(s);
    }
    solve();
}