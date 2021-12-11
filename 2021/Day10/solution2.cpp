#include <bits/stdc++.h>


std::vector<std::string> lines;
std::map<char, unsigned long long> pointsMap = 
    {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
std::map<char, char> closeMap = 
    {{')','('}, {']','['}, {'}','{'}, {'>','<'}};


unsigned long long solveLine(const std::string& s)
{
    std::stack<char> brackets = std::stack<char>();
    for (const auto c : s)
    {
        switch (c)
        {
            case '(':
            case '[':
            case '{':
            case '<':
                brackets.push(c);
                break;
            case ')':
            case ']':
            case '}':
            case '>':
                if (brackets.top() == closeMap[c]) brackets.pop();
                else return 0;
                break;
            default:
                std::cout << "Invalid character: " << c << std::endl;
                return 0;
        }
    }

    unsigned long long ans = 0;
    while (!brackets.empty())
    {
        char c = brackets.top(); brackets.pop();
        ans *= 5;
        ans += pointsMap[c];
    }
    return ans;
}


unsigned long long solve()
{
    std::vector<unsigned long long> a = std::vector<unsigned long long >();
    for (const std::string& l : lines)
    {
        unsigned long long ai = solveLine(l);
        if (ai > 0) a.push_back(ai);
    }
    std::sort(a.begin(), a.end());
    return a[a.size()/2];
}


int main()
{
    std::string s;
    while (std::cin >> s)
    {
        lines.push_back(s);
    }

    std::cout << solve() << std::endl;
}
