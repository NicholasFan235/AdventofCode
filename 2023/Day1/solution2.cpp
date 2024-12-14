#include <bits/stdc++.h>
#include <optional>


std::vector<std::string> input;


std::regex regex("^((one)|(two)|(three)|(four)|(five)|(six)|(seven)|(eight)|(nine)|(zero)|(\\d))");
std::map<std::string, int> num_map{
    {"zero", 0},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
    {"0", 0}, {"1", 1}, {"2",2}, {"3",3}, {"4",4}, {"5",5}, {"6",6}, {"7",7}, {"8",8}, {"9",9}
};


int match(std::string::const_iterator begin, std::string::const_iterator end)
{
    std::smatch smatch;
    std::regex_search(begin, end, smatch, regex);
    if (smatch.empty()) return -1;
    else return num_map[smatch[0]];
}


int interpret(std::string s)
{
    std::string::iterator i = s.begin();
    std::vector<int> nums = std::vector<int>();
    while (i != s.end())
    {
        int m = match(i, s.end());
        if (m >= 0) nums.push_back(m);
        ++i;
    }
    return nums.front() * 10 + nums.back();
}


void solve()
{
    long long int sol = 0;
    
    for (std::string s : input)
    {
        sol += interpret(s);
    }
    std::cout << sol << std::endl;
}


int main()
{
    input = std::vector<std::string>();
    std::string s;
    while (std::cin >> s)
    {
        input.push_back(s);
    }
    solve();
}