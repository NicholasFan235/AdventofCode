#include <bits/stdc++.h>


int main()
{
    std::set<char> S = std::set<char>();

    long long int ctr = 0;
    std::string s;
    while (!std::cin.eof())
    {
        std::getline(std::cin, s);
        if (s.empty())
        {
            ctr += S.size();
            if (S.size() > 0) std::cout << S.size() << std::endl;
            S.clear();
            continue;
        }
        for (const char& c : s)
        {
            S.insert(c);
        }
    }

    printf("\n%lld\n", ctr);
}