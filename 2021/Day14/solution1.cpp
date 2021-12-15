#include <bits/stdc++.h>


std::list<char> polymer;
std::map<char, unsigned long long> counts;
std::map<std::pair<char, char>, char> rules;


template <typename T>
std::ostream& operator<<(std::ostream& os, std::list<T> l)
{
    std::for_each(l.begin(), l.end(), [&](char c){ os << c; });
    return os;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T, U> p)
{
    std::cout << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::map<T, U> m)
{
    std::for_each(m.begin(), m.end(), [&](std::pair<T, U> p) { os << p.first << ": " << p.second << std::endl; });
    return os;
}


void pass()
{
    char prev = polymer.front();
    for (auto it = std::next(polymer.begin(), 1); it != polymer.end(); ++it)
    {
        std::pair<char, char> p = std::make_pair(prev, *it);
        if (rules.find(p) != rules.end())
        {
            polymer.insert(it, rules[p]);
        }
        prev = *it;
    }
}


unsigned long long count()
{
    counts.clear();
    std::for_each(polymer.begin(), polymer.end(), [](char c){ ++counts[c]; });

    unsigned long long max = 0, min = ULLONG_MAX;
    for (const auto p : counts)
    {
        min = std::min(min, p.second);
        max = std::max(max, p.second);
    }
    return max - min;
}


unsigned long long solve()
{
    std::cout << "Template: " << polymer << std::endl;
    for (int i = 1; i <= 10; i++)
    {
        pass();
        //std::cout << "After step " << i << ": " << polymer << std::endl;
    }
    return count();
}


int main()
{
    std::string s;
    std::cin >> s;
    std::for_each(s.begin(), s.end(), [](char c){ polymer.push_back(c); });

    std::regex regex("(.)(.) -> (.)");
    while (getline(std::cin, s))
    {
        if (s.empty()) continue;
        std::smatch match;
        if (std::regex_search(s, match, regex))
        {
            rules[std::make_pair(match[1].str()[0], match[2].str()[0])] = match[3].str()[0];
        }
    }

    std::cout << solve() << std::endl;
}
