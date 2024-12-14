#include <bits/stdc++.h>

struct Problem
{
    unsigned long long int ans = 0;
    std::vector<unsigned long long int> inputs = std::vector<unsigned long long int>();
};




std::vector<Problem> problems;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << (i==0?"":" ") << v[i];
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Problem& p)
{
    os << p.ans << " = " << p.inputs;
    return os;
}

template <>
std::ostream& operator<<(std::ostream& os, const std::vector<Problem>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << v[i];
        if (i<v.size()-1) os << std::endl;
    }
    return os;
}

unsigned long long int join(unsigned long long int a, unsigned long long int b)
{
    std::stringstream ss;
    ss << a << b;
    std::stringstream os(ss.str());
    unsigned long long int r;
    os >> r;
    return r;
}

bool search(const Problem& p, int pos=0, const unsigned long long int current=0)
{
    if (pos == 0) return search(p, pos+1, p.inputs[0]);
    if (pos >= p.inputs.size()) return p.ans == current;
    return search(p, pos+1,current+p.inputs[pos]) || search(p, pos+1, current*p.inputs[pos]) || search(p, pos+1, join(current, p.inputs[pos]));
}

void solve()
{
    unsigned long long int ans = 0;
    for (const auto& p : problems)
    {
        if (search(p))
        {
            // std::cout << p << " -> " << ans << std::endl;
            ans += p.ans;
        }
    }
    std::cout << ans << std::endl;
}


int main()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;

        std::stringstream ss(line);

        problems.emplace_back();

        unsigned long long int i; char c;
        ss >> i >> c;
        problems.back().ans = i;
        while (ss >> i) problems.back().inputs.push_back(i);
    }

    solve();
}
