#include <bits/stdc++.h>

std::map<std::string, std::set<std::string>> edges;


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << (i>0 ? " " : "") << v[i];
    }
    return os;
}

unsigned long long traverse(
    std::string nextLoc,
    std::vector<std::string>& path,
    std::set<std::string>& visited)
{
    if (nextLoc == "end") return 1;
    if (islower(nextLoc[0]) && visited.find(nextLoc) != visited.end()) return 0;

    path.push_back(nextLoc);
    visited.insert(nextLoc);

    unsigned long long ans = 0;
    for (const std::string& next : edges[nextLoc])
    {
        ans += traverse(next, path, visited);
    }
    
    path.pop_back();
    visited.erase(nextLoc);
    return ans;
}


unsigned long long solve()
{
    std::vector<std::string> path = {};
    std::set<std::string> visited = {};
    return traverse("start", path, visited);
}


int main()
{
    std::string s1, s2;
    while (std::getline(std::cin, s1, '-'))
    {
        std::getline(std::cin, s2, '\n');
        edges[s1].insert(s2);
        edges[s2].insert(s1);
    }

    std::cout << solve() << std::endl;
}



