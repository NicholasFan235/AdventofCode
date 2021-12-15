#include <bits/stdc++.h>


std::map<char, unsigned long long> counts;
std::map<std::pair<char, char>, char> rules;
std::map<std::pair<char, char>, unsigned long long> pairs;


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
    std::map<std::pair<char, char>, unsigned long long> pcopy = pairs;
    for (const auto& p : pcopy)
    {
        if (p.second == 0) continue;
        if (rules.find(p.first) != rules.end())
        {
            char c = rules[p.first];
            counts[c] += p.second;
            pairs[std::make_pair(p.first.first, c)] += p.second;
            pairs[std::make_pair(c, p.first.second)] += p.second;
            pairs[p.first] -= p.second;
        }
    }
}

unsigned long long solve()
{
    for (int i = 0; i < 40; i++)
    {
        pass();
    }
    
    unsigned long long min = ULLONG_MAX, max = 0;
    for (const auto& p : counts)
    {
        min = std::min(min, p.second);
        max = std::max(max, p.second);
    }
    return max - min;
}


int main()
{
    counts.clear(); rules.clear(); pairs.clear();

    std::string s;
    std::cin >> s;
    std::for_each(s.begin(), s.end(), [](char c){counts[c]++;});
    for (int i = 1; i < s.length(); i++)
        pairs[std::make_pair(s[i-1], s[i])]++;

    std::regex regex("(.)(.) -> (.)");
    while (getline(std::cin, s))
    {
        if (s.empty()) continue;
        std::smatch match;
        if (std::regex_search(s, match, regex))
            rules[std::make_pair(match[1].str()[0], match[2].str()[0])] = match[3].str()[0];
    }

    std::cout << solve() << std::endl;
}
