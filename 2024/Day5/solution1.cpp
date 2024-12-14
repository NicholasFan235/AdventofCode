#include <bits/stdc++.h>


std::vector<std::pair<int,int>> rules;
std::vector<std::string> update_strings;


const inline std::regex create_regex()
{
    std::stringstream ss;
    for (const auto& r : rules)
    {
        ss << r.second << ".*?" << r.first << "|";
    }
    std::string s = ss.str();
    s.pop_back();
    return std::regex(s);
}

const inline std::vector<int> to_vector(std::string u)
{
    std::vector<int> pages = std::vector<int>();
    const std::regex page_regex(",");
    for (auto it = std::sregex_token_iterator(u.begin(), u.end(), page_regex, -1);
        it != std::sregex_token_iterator(); ++it)
    {
        pages.push_back(atoi(it->str().c_str()));
    }
    return pages;
}

void solve()
{
    const std::regex rule_regex = create_regex();

    unsigned long long int ans = 0;

    for (const auto& u : update_strings)
    {
        if (std::regex_search(u.begin(), u.end(), rule_regex)) continue;

        const std::vector<int> update = to_vector(u);
        ans += update[update.size()/2];
    }
    std::cout << ans << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << (i>0?" ":"") << v[i];
    }
    os << std::endl;
    return os;
}

int main()
{
    rules = std::vector<std::pair<int,int>>();
    update_strings = std::vector<std::string>();

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;

        std::stringstream ss(line);
        int p1, p2;
        char c;
        ss >> p1 >> c >> p2;
        rules.push_back(std::make_pair(p1,p2));
    }

    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;

        update_strings.push_back(line);
    }
    solve();
}

