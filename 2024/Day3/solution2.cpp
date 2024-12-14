#include <bits/stdc++.h>

std::regex regex("mul\\((\\d+),(\\d+)\\)");
std::regex do_regex("^(.*?)(?:don't\\(\\))|(?:do\\(\\))(.*?)(?:don't\\(\\))|(?:do\\(\\))(.*?)$");

unsigned long long process_string(const std::string &s)
{
    unsigned long long ans = 0;

    auto phrase_begin = std::sregex_iterator(s.begin(), s.end(), do_regex);
    // std::cout << std::distance(phrase_begin, std::sregex_iterator()) << std::endl;
    for (auto i = phrase_begin; i != std::sregex_iterator(); ++i)
    {
        std::smatch phrase_match = *i;
        // std::cout << phrase_match.str() << std::endl;
        const std::string& phrase = phrase_match.str();
        // std::cout << phrase << std::endl;
        // std::cout << "\t" << phrase << std::endl;
        auto word_begin = std::sregex_iterator(phrase.begin(), phrase.end(), regex);
        for (auto j = word_begin; j != std::sregex_iterator(); ++j)
        {
            std::smatch match = *j;
            if (match.str().empty()) continue;
            // std::cout << "\t\t" << match[0].str() << std::endl;
            ans += std::atoi(match[1].str().c_str()) * std::atoi(match[2].str().c_str());
        }
    }
    return ans;
}

int main()
{
    unsigned long long ans = 0;
    std::string input = "";
    std::string line;
    while (std::getline(std::cin, line, '\n'))
    {
        input += line;
    }
    ans = process_string(input);
    std::cout << ans << std::endl;
}