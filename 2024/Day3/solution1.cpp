#include <bits/stdc++.h>


std::regex regex("mul\\((\\d+),(\\d+)\\)");
std::regex do_regex();
std::regex n_regex("don't\\(\\)((?!don't\\(\\)).)*?do\\(\\)");


unsigned long long process_string(const std::string& s)
{
    unsigned long long ans = 0;

    auto begin = std::sregex_iterator(s.begin(), s.end(), regex);
    auto end = std::sregex_iterator();

    for (auto i = begin; i != end; ++i)
    {
        std::smatch match = *i;
        ans += std::atoi(match[1].str().c_str()) * std::atoi(match[2].str().c_str());
    }
    return ans;
}

int main()
{
    unsigned long long ans = 0;
    std::string input;
    while (std::cin >> input)
    {
        ans += process_string(input);
    }
    std::cout << ans << std::endl;
}