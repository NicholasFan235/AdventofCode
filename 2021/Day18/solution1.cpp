#include <bits/stdc++.h>
#include "number.hpp"

std::vector<std::string> input;

void solve()
{
    NumberPtr n = std::make_shared<Number>(input[0]);
    while (n->reduce());
    for (int i = 1; i < input.size(); i++)
    {
        n = add(n, input[i]);
        while (n->reduce());
    }
    std::cout << n->magnitude() << std::endl;
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
