#include <bits/stdc++.h>

std::vector<std::string> input;
int N;
std::vector<int> digits;

unsigned long long int solve()
{
    digits = std::vector<int>(input[0].length());
    for (const std::string &s : input)
    {
        for (int i = 0; i < s.length(); i++)
        {
            digits[i] += (s[i] == '1') ? 1 : 0;
        }
    }

    unsigned long long int gamma = 0;
    unsigned long long int epsilon = 0;

    for (int i = 0; i < digits.size(); i++)
    {
        if (digits[i] == (N-digits[i])) std::cout << "Equal" << std::endl;
        else if (digits[i] < (N-digits[i]))
        {
            // more 0s
            epsilon++;
        }
        else if (digits[i] > (N-digits[i]))
        {
            // more 1s
            gamma++;
        }
        if (i < digits.size() - 1)
        {
            epsilon <<= 1;
            gamma <<= 1;
        }
    }
    std::cout << "Gamma: " << gamma << ", Epsilon: " << epsilon << std::endl;
    return gamma * epsilon;
}

int main()
{
    std::string s;
    while (std::cin >> s)
    {
        input.push_back(s);
    }
    N = input.size();

    unsigned long long int ans = solve();
    std::cout << ans << std::endl;
}