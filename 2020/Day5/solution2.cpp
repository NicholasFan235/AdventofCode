#include <bits/stdc++.h>

std::array<bool, 2<<10> S = std::array<bool, 2<<10>();

int calc(const std::string& s)
{
    int curr = 0;
    for (const char& c : s)
    {
        curr <<= 1;
        if (c == 'B' or c == 'R')
        {
            curr += 1;
        }
    }
    return curr;
}

int main()
{
    S.fill(false);
    std::string s;
    while (std::cin >> s)
    {
        int seatNum = calc(s);
        S[seatNum] = true;
    }

    int currGap = 0;
    for (int i = 1; i < S.size()-1; i++)
    {
        if (!S[i] && S[i-1] && S[i+1]) std::cout << i << std::endl;
    }
}