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
    std::map<std::string, int>& visited,
    bool hasDoubleVisit)
{
    if (nextLoc == "end") return 1;
    if (nextLoc == "start" && visited["start"] > 0) return 0;
    if (islower(nextLoc[0]))
    {
        if (visited[nextLoc] != 0)
        {
            if (hasDoubleVisit) return 0;
            hasDoubleVisit = true;
        }
    }

    path.push_back(nextLoc);
    visited[nextLoc]++;

    unsigned long long ans = 0;
    for (const std::string& next : edges[nextLoc])
    {
        ans += traverse(next, path, visited, hasDoubleVisit);
    }
    
    path.pop_back();
    visited[nextLoc]--;
    return ans;
}


unsigned long long solve()
{
    std::vector<std::string> path = {};
    std::map<std::string, int> visited = {};
    return traverse("start", path, visited, false);
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



