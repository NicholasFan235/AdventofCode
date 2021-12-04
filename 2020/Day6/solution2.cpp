#include <bits/stdc++.h>


int main()
{
    std::set<char> S = std::set<char>();
    for (const char& c : "abcdefghijklmnopqrstuvwxyz") S.insert(c);

    long long int ctr = 0;
    std::string s;
    while (!std::cin.eof())
    {
        std::getline(std::cin, s);
        if (s.empty())
        {
            ctr += S.size();
            if (S.size() > 0) std::cout << S.size() << std::endl;
            for (const char& c : "abcdefghijklmnopqrstuvwxyz") S.insert(c);
            continue;
        }

        std::set<char> newS = std::set<char>();
        for (const char& c : s)
        {
            newS.insert(c);
        }

        std::set<char> delS = std::set<char>();
        for (const char& c : S)
        {
            if (newS.find(c) == newS.end()) delS.insert(c);
        }

        for (const char& c : delS)
        {
            S.erase(c);
        }
    }

    printf("\n%lld\n", ctr);
}