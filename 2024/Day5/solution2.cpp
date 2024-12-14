#include <bits/stdc++.h>


std::map<int, std::set<int>> rules_map;
std::vector<std::pair<int,int>> rules;
std::vector<std::string> update_strings;
std::regex rule_regex;

std::map<int,int> priorities;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << (i>0?" ":"") << v[i];
    }
    return os;
}

const inline std::regex create_rule_regex()
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
        int n = atoi(it->str().c_str());
        pages.push_back(n);
    }
    return pages;
}

const inline std::set<int> to_set(std::string u)
{
    std::set<int> pages;
    const std::regex page_regex(",");
    for (auto it = std::sregex_token_iterator(u.begin(), u.end(), page_regex, -1);
        it != std::sregex_token_iterator(); ++it)
    {
        int n = atoi(it->str().c_str());
        pages.insert(n);
    }
    return pages;
}

bool is_valid(std::string u)
{
    if (!std::regex_search(u.begin(), u.end(), rule_regex)) return true;
    return false;
}

bool try_solve_update(const std::set<int>& subset, std::vector<int>& out)
{
    std::set<int> starts;
    std::copy(subset.begin(), subset.end(), std::inserter(starts, starts.end()));

    while (!starts.empty())
    {
        std::set<int> ends;
        for (const auto s : starts)
            for (const auto r : rules_map[s])
                ends.insert(r);
        
        std::vector<int> diffs = std::vector<int>();
        std::set_difference(starts.begin(), starts.end(), ends.begin(), ends.end(), std::back_inserter(diffs));

        if (diffs.size() == 0) throw std::runtime_error("No Solution");

        for (const auto& d : diffs)
        {
            out.push_back(d);
            starts.erase(d);
        }
    }
    return true;
}


void solve()
{
    unsigned long long int ans = 0;

    for (const std::string& u : update_strings)
    {
        if (is_valid(u)) continue;

        std::set<int> subset = to_set(u);
        std::vector<int> pages = std::vector<int>();

        try_solve_update(subset, pages);

        ans += pages[pages.size()/2];
    }

    std::cout << ans << std::endl;
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
        rules_map[p1].insert(p2);
    }
    rule_regex = create_rule_regex();

    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;

        update_strings.push_back(line);
    }
    solve();
}

