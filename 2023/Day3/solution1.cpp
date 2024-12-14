#include <bits/stdc++.h>


std::vector<std::string> input;


void solve()
{
    long long int ans = 0;
    for (int i = 0; i < input.size(); i++)
    {
        int num = 0;
        bool include = false;
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] < '0' || input[i][j] > '9')
            {
                if (include) ans += num;
                num = 0;
                include = false;
                continue;
            }
            
            num = num*10 + input[i][j] - '0';
            for (int di = std::max(0, i-1); di <= std::min((int)input[i].size()-1, i+1); di++)
            {
                for (int dj = std::max(0, j-1); dj <= std::min((int)input[j].size()-1, j+1); dj++)
                {
                    char& c = input[di][dj];
                    if (c == '.') continue;
                    if (c >= '0' && c <= '9') continue;
                    include = true;
                }
            }
        }
        if (include) ans += num;
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
    solve();
}
