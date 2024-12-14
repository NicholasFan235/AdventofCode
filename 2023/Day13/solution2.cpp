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

    void process(int n_diffs = 0)
    {
        find_vertical_mirrors(n_diffs);
        find_horizontal_mirrors(n_diffs);
    }

    int value()
    {
        return std::accumulate(m_horizontal_mirrors.begin(), m_horizontal_mirrors.end(), 0) * 100
            + std::accumulate(m_vertical_mirrors.begin(), m_vertical_mirrors.end(), 0);
    }

private:
    int test_vertical_mirror(int col)
    {
        int diffs = 0;
        for (int i = 0; i < m_pattern.size(); i++)
        {
            for (int j = 0; j <= col; j++)
            {
                int l = col-j;
                int r = col+j+1;
                if (r >= m_pattern[i].size()) continue;
                diffs += m_pattern[i][l] != m_pattern[i][r];
            }
        }
        return diffs;
    }

    void find_vertical_mirrors(int n_diffs = 0)
    {
        m_vertical_mirrors.clear();
        for (int i = 0; i < m_pattern.front().size()-1; i++)
        {
            int diffs = test_vertical_mirror(i);
            if (diffs == n_diffs) m_vertical_mirrors.insert(i+1);
        }
    }

    int test_horizontal_mirror(int row)
    {
        int diffs = 0;
        for (int i = 0; i <= row; i++)
        {
            int u = row-i;
            int l = row+i+1;
            if (l >= m_pattern.size()) continue;
            for (int j = 0; j < m_pattern[u].size(); j++)
            {
                diffs += m_pattern[u][j] != m_pattern[l][j];
            }
        }
        return diffs;
    }

    void find_horizontal_mirrors(int n_diffs = 0)
    {
        m_horizontal_mirrors.clear();
        for (int i = 0; i < m_pattern.size()-1; i++)
        {
            int diffs = test_horizontal_mirror(i);
            if (diffs == n_diffs) m_horizontal_mirrors.insert(i+1);
        }
    }

};

std::vector<Pattern> patterns;


void solve()
{
    std::vector<int> values = std::vector<int>();
    for (int i = 0; i < patterns.size(); i++)
    {
        patterns[i].process(1);
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

