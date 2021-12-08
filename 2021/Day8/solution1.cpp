#include <bits/stdc++.h>

int main()
{
    std::vector<std::string> patterns = std::vector<std::string>(10);
    std::vector<std::string> outputs = std::vector<std::string>(4);
    std::string delimeter;
    int ctr = 0;
    while (std::cin >> patterns[0])
    {
        for (int i = 1; i < 10; i++) std::cin >> patterns[i];
        std::cin >> delimeter;
        for (int i = 0; i < 4; i++) std::cin >> outputs[i];

        for (int i = 0; i < 4; i++)
        {
            int l = outputs[i].length();
            std::cout << outputs[i] << ", ";
            if (l == 2 || l == 4 || l == 3 || l == 7) ctr++;
        }
        std::cout << std::endl;
    }
    std::cout << ctr << std::endl;
}
