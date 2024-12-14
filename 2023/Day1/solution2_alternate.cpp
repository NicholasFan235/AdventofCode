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


struct Node
{
    std::map<char, Node*> links;
    int value;

    Node(int v = -1): value(v) {}

    ~Node() { for (const auto& p : links) delete p.second; }
};
Node* tree;

void populate(Node* node, std::string::const_iterator begin, std::string::const_iterator end, int value)
{
    if (begin == end)
    {
        node->value = value;
        return;
    }
    char c = *begin;
    if (node->links.find(c) == node->links.end())
    {
        node->links[c] = new Node(-1);
    }
    populate(node->links[c], begin+1, end, value);
}

int match(Node* node, std::string::const_iterator begin, std::string::const_iterator end)
{
    if (node->value >= 0) return node->value;
    if (begin == end) return -1;
    char c = *begin;
    if (node->links.find(c) != node->links.end())
    {
        return match(node->links.at(c), begin+1, end);
    }
    return -1;
}


int interpret(std::string s)
{
    std::string::iterator i = s.begin();
    std::vector<int> nums = std::vector<int>();
    while (i != s.end())
    {
        int m = match(tree, i, s.end());
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
    tree = new Node(-1);
    for (const auto& p : num_map)
    {
        populate(tree, p.first.begin(), p.first.end(), p.second);
    }
    
    input = std::vector<std::string>();
    std::string s;
    while (std::cin >> s)
    {
        input.push_back(s);
    }
    solve();
}