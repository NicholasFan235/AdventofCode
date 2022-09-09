#include <bits/stdc++.h>

const int padding_size = 10;

std::string algorithm;
std::vector<std::vector<char>> image;

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &v)
{
    for (const auto &r : v)
    {
        for (const auto &c : r)
            os << c;
        os << std::endl;
    }
    return os;
}

int decode(int i, int j)
{
    std::bitset<9> ans = std::bitset<9>();
    if (i == 0 || j == 0 || i == image.size()-1 || j == image[0].size()-1)
    {
        if (image[i][j] == '#') ans.flip();
        return ans.to_ulong();
    }
    for (int k = -1; k <= 1; k++)
    {
        for (int l = -1; l <= 1; l++)
        {
            int index = 8 - (k+1) * 3 - l - 1;
            ans[index] = image[i+k][j+l] == '#' ? 1 : 0;
        }
    }
    return ans.to_ulong();
}

void iterate()
{
    std::vector<std::vector<char>> new_image = std::vector<std::vector<char>>(
        image.size(), std::vector<char>(image[0].size()));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[i].size(); j++)
        {
            new_image[i][j] = algorithm[decode(i, j)];
        }
    }
    image = new_image;
}

unsigned long long count()
{
    unsigned long long ctr = 0;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[i].size(); j++)
        {
            ctr += (image[i][j] == '#') ? 1 : 0;
        }
    }
    return ctr;
}

void solve()
{
    for (int n = 0; n < 2; n++)
    {
        iterate();
    }

    std::cout << count() << std::endl;
}

int main()
{
    std::cin >> algorithm;
    std::string s;

    image = std::vector<std::vector<char>>();

    while (std::cin >> s)
    {
        if (image.empty())
            for (int i = 0; i < padding_size; i++)
                image.push_back(std::vector<char>(s.size() + padding_size * 2, '.'));
        std::vector<char> row = std::vector<char>(s.size() + padding_size * 2, '.');
        for (int i = 0; i < s.length(); i++)
            row[padding_size + i] = s[i];
        image.push_back(row);
    }
    for (int i = 0; i < padding_size; i++)
        image.push_back(std::vector<char>(s.size() + padding_size * 2, '.'));

    solve();
}
