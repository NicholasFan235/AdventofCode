#include <bits/stdc++.h>

std::vector<std::vector<std::bitset<7>>> patterns;
std::vector<std::vector<std::bitset<7>>> outputs;
std::vector<std::vector<std::string>> patternStrings;
std::vector<std::vector<std::string>> outputStrings;

std::map<int, int> displayMap = 
{
    {0b0100100, 1}, {0b1011101, 2}, {0b1101101, 3}, {0b0101110, 4},
    {0b1101011, 5}, {0b1111011, 6}, {0b0100101, 7}, {0b1111111, 8},
    {0b1101111, 9}, {0b1110111, 0}
};

int count(std::bitset<7> b)
{
    int ctr = 0;
    for (int i = 0; i < 7; i++)
    {
        ctr += b[i];
    }
    return ctr;
}

unsigned long long solveSingle(int i)
{
    std::vector<std::bitset<7>> possibilities =
        std::vector<std::bitset<7>>(7, std::bitset<7>(255));

    /*for (int j = 0; j < 4; j++)
        std::cout << outputs[i][j] << " ";
    std::cout << std::endl;
    for (int j = 0; j < 4; j++)
        std::cout << outputStrings[i][j] << " ";
    std::cout << std::endl;*/

    while (true)
    {
        for (int j = 0; j < 10; j++)
        {
            int nChars = patternStrings[i][j].length();
            if (nChars == 2)
            {
                for (int s = 0; s < 7; s++)
                {
                    if (s == 2 || s == 5)
                    {
                        possibilities[s] &= patterns[i][j];
                    }
                    else
                    {
                        patterns[i][j].flip();
                        possibilities[s] &= patterns[i][j];
                        patterns[i][j].flip();
                    }
                }
            }
            else if (nChars == 3)
            {
                for (int s = 0; s < 7; s++)
                {
                    if (s == 0 || s == 2 || s == 5)
                    {
                        possibilities[s] &= patterns[i][j];
                    }
                    else
                    {
                        patterns[i][j].flip();
                        possibilities[s] &= patterns[i][j];
                        patterns[i][j].flip();
                    }
                }
            }
            else if (nChars == 4)
            {
                for (int s = 0; s < 7; s++)
                {
                    if (s == 1 || s == 2 || s == 3 || s == 5)
                    {
                        possibilities[s] &= patterns[i][j];
                    }
                    else
                    {
                        patterns[i][j].flip();
                        possibilities[s] &= patterns[i][j];
                        patterns[i][j].flip();
                    }
                }
            }
            else if (nChars == 5)
            {
                // is 2 or 5
                for (int s = 0; s < 7; s++)
                {
                    if (s == 0 || s == 3 || s == 6)
                    {
                        possibilities[s] &= patterns[i][j];
                    }
                }
            }
            else if (nChars == 6)
            {
                for (int s = 0; s < 7; s++)
                {
                    if (s == 0 || s == 1 || s == 5 || s == 6)
                    {
                        possibilities[s] &= patterns[i][j];
                    }
                }
            }
        }
        break;
    }

    std::vector<int> numBits = std::vector<int>(7, 0);
    for (int j = 0; j < 7; j++)
    {
        numBits[j] = count(possibilities[j]);
    }

    for (int c = 0; c < 7; c++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (numBits[j] == 1)
            {
                for (int k = 0; k < 7; k++)
                {
                    if (numBits[k] > 1)
                    {
                        possibilities[j].flip();
                        possibilities[k] &= possibilities[j];
                        possibilities[j].flip();
                        numBits[k] = count(possibilities[k]);
                    }
                }
            }
        }
    }
    bool success = true;
    for (int j = 0; j < 7; j++)
    {
        //std::cout << possibilities[j] << " ";
        if (numBits[j] != 1) success = false;
    }
    //std::cout << std::endl;

    if (!success)
    {
        std::cout << i << " failed." << std::endl;
    }


    // Decode outputs
    unsigned long long ans = 0;
    for (int j = 0; j < 4; j++)
    {
        auto display = std::bitset<7>(255);
        for (int s = 0; s < 7; s++)
        {
            display[s] = !(possibilities[s] & outputs[i][j]).none();
            //std::cout << display[s] << " ";
        }
        ans += displayMap[display.to_ulong()];
        if (j < 3) ans *= 10;
        //std::cout << std::endl;
    }
    //std::cout << ans << std::endl;
    return ans;
}

unsigned long long solve()
{
    unsigned long long ans = 0;
    for (int i = 0; i < outputs.size(); i++)
    {
        ans += solveSingle(i);
    }

    return ans;
}

std::bitset<7> str2bits(const std::string &s)
{
    std::bitset<7> ret = std::bitset<7>(0);
    for (const auto c : s)
    {
        int i = c - 'a';
        if (i < 0 || i > 7)
            std::cout << "Bad character: " << c << std::endl;
        ret[i] = 1;
    }
    return ret;
}

int main()
{
    patterns = std::vector<std::vector<std::bitset<7>>>();
    outputs = std::vector<std::vector<std::bitset<7>>>();
    patternStrings = std::vector<std::vector<std::string>>();
    outputStrings = std::vector<std::vector<std::string>>();

    std::string s;
    int j = 0;
    while (std::cin >> s)
    {
        patterns.push_back(std::vector<std::bitset<7>>(10));
        outputs.push_back(std::vector<std::bitset<7>>(4));
        patternStrings.push_back(std::vector<std::string>(10));
        outputStrings.push_back(std::vector<std::string>(4));

        patternStrings[j][0] = s;
        patterns[j][0] = str2bits(s);
        for (int i = 1; i < 10; i++)
        {
            std::cin >> patternStrings[j][i];
            patterns[j][i] = str2bits(patternStrings[j][i]);
        }
        std::cin >> s;
        for (int i = 0; i < 4; i++)
        {
            std::cin >> outputStrings[j][i];
            outputs[j][i] = str2bits(outputStrings[j][i]);
        }
        j++;
    }

    std::cout << solve() << std::endl;
}
