#include <bits/stdc++.h>


std::vector<std::string> input;
std::vector<std::vector<bool>> processed;



bool is_digit(int i, int j)
{
    return input[i][j] >= '0' && input[i][j] <= '9';
}

int get_number(int i, int j)
{
    std::list<int> num;
    int t = j-1;
    while (++t < input[i].size())
    {
        if (is_digit(i,t))
        {
            num.push_back(input[i][t] - '0');
            processed[i][t] = true;
        }
        else break;
    }

    t = j;
    while (t-- > 0)
    {
        if (is_digit(i,t))
        {
            num.push_front(input[i][t]-'0');
            processed[i][t] = true;
        }
        else break;
    }

    int ret = 0;
    for (const auto& n : num) ret = ret * 10 + n;
    return ret;
}


int check_cog(int i, int j)
{
    int n_nums = 0;
    int ans = 1;
    for (int di = std::max(0, i-1); di <= std::min((int)input.size()-1, i+1); di++)
    {
        for (int dj = std::max(0, j-1); dj <= std::min((int)input[i].size()-1, j+1); dj++)
        {
            if (processed[di][dj]) continue;
            if (is_digit(di, dj))
            {
                n_nums++;
                ans *= get_number(di, dj);
            }
        }
    }
    return n_nums == 2 ? ans : 0;
}

void solve()
{
    long long int ans = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '*')
            {
                ans += check_cog(i,j);
            }
        }
    }
    std::cout << ans << std::endl;
}



int main()
{
    input = std::vector<std::string>();
    std::string s;
    while (std::cin >> s)
    {
        input.push_back(s);
    }
    processed = std::vector<std::vector<bool>>(input.size(), std::vector<bool>(input[0].size(), false));
    solve();
}
