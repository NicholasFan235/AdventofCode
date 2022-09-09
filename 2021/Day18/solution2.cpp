#include <bits/stdc++.h>
#include "number.hpp"

std::vector<std::string> input;

unsigned long long check(int i, int j)
{
    NumberPtr n = std::make_shared<Number>(
        std::make_shared<Number>(input[i]),
        std::make_shared<Number>(input[j]));
    while (n->reduce());
    return n->magnitude();
}


void solve()
{
    unsigned long long max = 0;

    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            max = std::max(max, check(i, j));
            max = std::max(max, check(j, i));
        }
    }
    
    std::cout << max << std::endl;
}

int main()
{
    std::string s;
    while (std::cin >> s)
    {
        input.push_back(s);
    }
    solve();
}
