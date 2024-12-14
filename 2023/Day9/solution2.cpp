#include <bits/stdc++.h>



std::vector<std::vector<long long int>> sequences;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << (i==0 ? "" : " ") << v[i];
    }
    return os;
}

long long int extrapolate(const std::vector<long long int>& sequence)
{
    std::vector<long long int> diffs = std::vector<long long int>(sequence.size()-1, 0);
    bool all_zero = true;
    for (int i = 0; i < sequence.size()-1; i++)
    {
        diffs[i] = sequence.at(i+1) - sequence.at(i);
        if (diffs[i] != 0) all_zero = false;
    }
    if (all_zero)
    {
        return sequence.front();
    }

    long long int e = extrapolate(diffs);
    return sequence.front() - e;
}


void solve()
{
    std::vector<long long int> extrapolations = std::vector<long long int>();
    for (const auto& sequence : sequences)
    {
        extrapolations.push_back(extrapolate(sequence));
    }
    long long int ans = std::accumulate(extrapolations.begin(), extrapolations.end(), 0ll);
    std::cout << ans << std::endl;
}


int main()
{
    sequences = std::vector<std::vector<long long int>>();
    std::string line;
    while (getline(std::cin, line))
    {
        sequences.push_back(std::vector<long long int>());
        std::stringstream ss(line);
        long long int n;
        while (ss >> n) sequences.back().push_back(n);
    }
    solve();
}