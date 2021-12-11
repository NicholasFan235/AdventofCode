#include <bits/stdc++.h>


std::vector<std::string> lines;
std::map<char, unsigned long long> pointsMap = 
    {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
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
                else return pointsMap[c];
                break;
            default:
                std::cout << "Invalid character: " << c << std::endl;
                return 0;
        }
    }
    return 0;
}


unsigned long long solve()
{
    unsigned long long ans = 0;
    for (const std::string& l : lines)
    {
        ans += solveLine(l);
    }
    return ans;
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
