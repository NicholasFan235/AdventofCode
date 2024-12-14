#include <bits/stdc++.h>



struct Hand
{
    char cards[6];
    int bid;
    int strength;
    Hand(const std::string& s, const int& bid) : bid(bid)
    {
        for (int i = 0; i < 5; i++)
        {
            cards[i] = s[i];
        }
        cards[5] = '\0';

        strength = compute_strength();
    }

private:
    int compute_strength()
    {
        std::map<char, int> card_map;
        for (int i= 0 ; i < 5; i++) card_map[cards[i]]++;

        int n_jokers = (card_map.find('J') == card_map.end()) ? 0 : card_map.at('J');

        std::map<int, int> num_map;
        for (const auto& p : card_map)
        {
            if (p.first == 'J') continue;
            num_map[p.second]++;
        }
        int n_max = num_map.empty() ? 0 : num_map.rbegin()->first;
        num_map[n_max]--;
        num_map[n_max + n_jokers]++;
        if (num_map[n_max] <= 0) num_map.erase(n_max);
        int n_groups = card_map.size() - (n_jokers > 0 ? 1 : 0);
        if (n_jokers == 5) n_groups = 1;

        if (n_groups == 1) return 7;
        if (n_groups == 2)
        {
            if (num_map[4] > 0) return 6;
            if (num_map[3] > 0) return 5;
        }
        if (n_groups == 3)
        {
            if (num_map[3] > 0) return 4;
            if (num_map[2] > 1) return 3;
        }
        if (n_groups == 4) return 2;
        if (n_groups == 5) return 1;

        std::cout << "Cannot Classify Hand: " << cards << std::endl;
        return 0;
    }
};

std::map<char, int> cardRankMap{
    {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'J', 1}, {'Q', 12}, {'K', 13}, {'A', 14}
};

bool operator>(const Hand& l, const Hand& r)
{
    if (l.strength == r.strength)
    {
        for (int i = 0; i < 5; i++)
        {
            if (cardRankMap[l.cards[i]] == cardRankMap[r.cards[i]])
            {
                continue;
            }
            return cardRankMap[l.cards[i]] > cardRankMap[r.cards[i]];
        }
        return false;
    }
    return l.strength > r.strength;
}

bool operator==(const Hand& l, const Hand& r)
{
    if (l.strength != r.strength) return false;
    for (int i = 0; i < 5; i++) if (l.cards[i] != r.cards[i]) return false;
    return true;
}

bool operator!=(const Hand& l, const Hand& r)
{
    return !(l==r);
}

bool operator>=(const Hand& l, const Hand& r)
{
    return l>r || l==r;
}

bool operator<(const Hand& l, const Hand& r)
{
    return !(l>=r);
}

bool operator<=(const Hand& l, const Hand& r)
{
    return !(l>r);
}

std::vector<Hand> hands;

std::map<int, std::string> classificationMap{
    {0, "Unclassified"},{1, "High card"}, {2, "One pair"}, {3, "Two pair"}, {4, "Three of a kind"}, {5, "Full house"}, {6, "Four of a kind"}, {7, "Five of a kind"}
};


void solve()
{
    std::sort(hands.begin(), hands.end(), std::less<Hand>());
    // for (int i = 0; i < hands.size(); i++)
    // {
    //     std::cout << hands[i].cards << " " <<  classificationMap[hands[i].strength] << " " << hands[i].bid << std::endl;
    // }

    unsigned long long ans = 0;
    for (int i = 0; i < hands.size(); i++)
    {
        ans += (unsigned long long)(i+1) * hands[i].bid;
    }
    std::cout << ans << std::endl;
}

int main()
{
    hands = std::vector<Hand>();

    std::string s;
    while (std::cin >> s)
    {
        int value;
        std::cin >> value;
        //std::cout << s << " " << value << std::endl;
        hands.push_back(Hand(s, value));
    }

    solve();
}
