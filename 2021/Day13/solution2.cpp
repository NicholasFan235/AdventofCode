#include <bits/stdc++.h>


std::set<std::pair<int, int>> dots;
std::vector<std::pair<char, int>> folds;


template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        os << v[i];
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& v)
{
    for (const std::vector<T>& u : v)
    {
        os << u << std::endl;
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& v)
{
    std::for_each(v.cbegin(), v.cend(), [&](T x){ os << x << std::endl; });
    return os;
}


void iterate(int i)
{
    std::cout << "Fold along " << folds[i].first << " = " << folds[i].second << " -> ";
    std::set<std::pair<int, int>> new_dots;
    if (folds[i].first == 'x')
    {
        for (auto it = dots.begin(); it != dots.end(); ++it)
        {
            std::pair<int, int> n = std::make_pair(
                it->first > folds[i].second ?
                    2 * folds[i].second - it->first :
                    it->first,
                it->second);
            new_dots.insert(n);
        }
    }
    else if (folds[i].first == 'y')
    {
        for (auto it = dots.begin(); it != dots.end(); ++it)
        {
            std::pair<int, int> n = std::make_pair(
                it->first,
                it->second > folds[i].second ?
                    2 * folds[i].second - it->second :
                    it->second);
            new_dots.insert(n);
        }
    }
    else
    {
        std::cout << "Invalid fold direction " << folds[i].first << std::endl;
    }
    dots = new_dots;
    std::cout << dots.size() << std::endl;
}

void printDots()
{
    int X = 0, Y = 0;
    for (auto it = dots.begin(); it != dots.end(); ++it)
    {
        X = std::max(X, it->first); Y = std::max(Y, it->second);
    }

    std::vector<std::vector<char>> map = std::vector<std::vector<char>>(
        Y+1, std::vector<char>(X+1, '.'));
    
    for (auto it = dots.begin(); it != dots.end(); ++it)
    {
        map[it->second][it->first] = '#';
    }

    std::cout << map << std::endl;
}


unsigned long long solve()
{
    std::cout << dots.size() << std::endl;
    for (int i = 0; i < folds.size(); i++)
    {
        iterate(i);
    }
    printDots();
    return 0;
}


int main()
{
    std::string s;
    while (getline(std::cin, s))
    {
        std::stringstream ss(s);
        int a, b; char c;
        ss >> a >> c >> b;
        dots.insert(std::make_pair(a, b));

        if (s.empty()) break;
    }

    std::regex regex("fold along ([x,y])=([0-9]*)");
    while (getline(std::cin, s))
    {
        std::smatch match;
        if (std::regex_search(s, match, regex))
        {
            std::stringstream ss(match[2]);
            int i;
            ss >> i;
            folds.push_back(std::make_pair(match[1].str()[0], i));
        }
    }

    std::cout << solve() << std::endl;
}
