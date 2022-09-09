#include <bits/stdc++.h>

int p1, p2;
unsigned long long s1, s2;
unsigned long long rolls = 0;

int roll()
{
    return (rolls++%100) + 1;
}

unsigned long long play()
{
    while (true)
    {
        p1 += roll() + roll() + roll();
        p1 = ((p1-1)%10) + 1;
        s1 += p1;
        if (s1 >= 1000) return s2 * rolls;

        p2 += roll() + roll() + roll();
        p2 = ((p2-1)%10) + 1;
        s2 += p2;
        if (s2 >= 1000) return s1 * rolls;
    }
}

void solve()
{
    std::cout << play() << std::endl;
}

int main()
{
    std::string s;

    std::regex regex("^Player [1,2] starting position: ([0-9]*)$");
    std::smatch match;
    s1 = 0; s2 = 0;
    getline(std::cin, s);
    if (std::regex_search(s, match, regex))
        p1 = atoi(match[1].str().c_str());
    getline(std::cin, s);
    if (std::regex_search(s, match, regex))
        p2 = atoi(match[1].str().c_str());

    solve();
}
