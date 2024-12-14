#include <bits/stdc++.h>


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
{
    os << "{";
    for (auto it = s.begin(); it != s.end(); it++)
    {
        os << (it == s.begin() ? "" : ", ") << *it;
    }
    os << "}";
    return os;
}


class Pattern
{
private:
    std::vector<std::string> m_pattern;
    std::set<int> m_vertical_mirrors;
    std::set<int> m_horizontal_mirrors;

public:
    Pattern() : m_pattern() {}
    Pattern(std::istream& is) : m_pattern() { is >> *this; }

    const std::set<int>& vertical_mirrors()
    {
        return m_vertical_mirrors;
    }
    const std::set<int>& horizontal_mirrors()
    {
        return m_horizontal_mirrors;
    }
    const std::vector<std::string>& pattern() { return m_pattern; }

    friend std::istream& operator>>(std::istream& is, Pattern& pattern)
    {
        std::string s;
        while (getline(is, s))
        {
            if (s.empty()) break;
            pattern.m_pattern.push_back(s);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pattern& pattern)
    {
        for (const std::string& s : pattern.m_pattern) os << s << std::endl;
        return os;
    }

    void process()
    {
        find_vertical_mirrors();
        find_horizontal_mirrors();
    }

    int value()
    {
        return std::accumulate(m_horizontal_mirrors.begin(), m_horizontal_mirrors.end(), 0) * 100
            + std::accumulate(m_vertical_mirrors.begin(), m_vertical_mirrors.end(), 0);
    }

private:
    bool can_be_vertical_mirror(int row, int j)
    {
        std::string& s = m_pattern[row];
        for (int i = 0; i <= std::min((int)s.size()-j-2, j); i++)
        {
            if (s[j-i] != s[j+1+i]) return false;
        }
        return true;
    }

    void find_vertical_mirrors()
    {
        std::vector<std::set<int>> possible_mirrors = std::vector<std::set<int>>(m_pattern.size(), std::set<int>());
        for (int i = 0; i < m_pattern.size(); i++)
        {
            for (int j = 0; j < m_pattern[i].size()-1; j++)
            {
                if (can_be_vertical_mirror(i, j))
                    possible_mirrors[i].insert(j+1);
            }
        }

        m_vertical_mirrors = std::accumulate(possible_mirrors.begin(), possible_mirrors.end(), possible_mirrors.front(),
            [](const std::set<int>& l, const std::set<int>& r)
            {
                std::set<int> ret = std::set<int>();
                std::set_intersection(l.begin(), l.end(), r.begin(), r.end(), std::inserter(ret, ret.end()));
                return ret;
            });

        // std::cout << "Verticals:" << std::endl;
        // for (const auto& s : possible_mirrors) std::cout << s << std::endl;
    }

    bool can_be_horizontal_mirror(int j, int col)
    {
        for (int i = 0; i <= std::min((int)m_pattern.size()-j-2, j); i++)
        {
            if (m_pattern[j-i][col] != m_pattern[j+1+i][col]) return false;
        }
        return true;
    }

    void find_horizontal_mirrors()
    {
        std::vector<std::set<int>> possible_mirrors = std::vector<std::set<int>>(m_pattern[0].size(), std::set<int>());
        for (int i = 0; i < m_pattern.size()-1; i++)
        {
            for (int j = 0; j < m_pattern[i].size(); j++)
            {
                if (can_be_horizontal_mirror(i,j))
                    possible_mirrors[j].insert(i+1);
            }
        }

        m_horizontal_mirrors = std::accumulate(possible_mirrors.begin(), possible_mirrors.end(), possible_mirrors.front(),
            [](const std::set<int>& l, const std::set<int>& r)
            {
                std::set<int> ret = std::set<int>();
                std::set_intersection(l.begin(), l.end(), r.begin(), r.end(), std::inserter(ret, ret.end()));
                return ret;
            });

        // std::cout << "Horizontals: " << std::endl;
        // for (const auto& s : possible_mirrors) std::cout << s << std::endl;
    }

};

std::vector<Pattern> patterns;


void solve()
{
    std::vector<int> values = std::vector<int>();
    for (int i = 0; i < patterns.size(); i++)
    {
        patterns[i].process();
        values.push_back(patterns[i].value());
        // std::cout << "Pattern " << i << ": vertical=" << patterns[i].vertical_mirrors() << ", horizontal=" << patterns[i].horizontal_mirrors() 
        //     << ", value=" << patterns[i].value() << std::endl;
    }

    long long ans = std::accumulate(values.begin(), values.end(), 0ll);
    std::cout << ans << std::endl;
}

int main()
{
    patterns = std::vector<Pattern>();
    while (std::cin)
    {
        patterns.emplace_back(std::cin);
    }
    solve();
}

