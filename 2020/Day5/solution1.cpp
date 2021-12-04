#include <bits/stdc++.h>

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
    int currMax = 0;
    std::string s;
    while (std::cin >> s)
    {
        int seatNum = calc(s);
        currMax = std::max(currMax, seatNum);
        std::cout << seatNum << std::endl;
    }

    printf("\n%d\n", currMax);
}