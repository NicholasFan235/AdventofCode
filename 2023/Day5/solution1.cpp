#include <bits/stdc++.h>


template <typename T>
struct Node
{
    T low, high, max;
    Node<T> *left, *right;

    Node(T low, T high):low(low), high(high), max(high), left(nullptr), right(nullptr) {}
    ~Node()
    {
        if (left != nullptr) delete left;
        left = nullptr;
        if (right != nullptr) delete right;
        right = nullptr;
    }

    bool overlaps(Node<T>& other)
    {
        return low <= other.high && other.low <= high;
    }
    
    bool contains(T point)
    {
        return low <= point && point <= high;
    }
};


template <typename T>
class Tree
{
private:
    Node<T>* m_root;

public:
    Tree() : m_root(nullptr) {}
    ~Tree()
    {
        if (m_root != nullptr) delete m_root;
        m_root = nullptr;
    }

    void insert(T low, T high)
    {
        m_root = insert(m_root, low, high);
    }

    void intersections(T point, std::vector<std::pair<T, T>>& out)
    {
        intersections(m_root, point, out);
    }

private:
    Node<T>* insert(Node<T>* root, T low, T high)
    {
        if (root == nullptr) return new Node<T>(low, high);

        if (low < root->low)
        {
            root->left = insert(root->left, low, high);
        }
        else
        {
            root->right = insert(root->right, low, high);
        }

        root->max = std::max(root->max, high);
        return root;
    }

    void intersections(Node<T>* root, T point, std::vector<std::pair<T, T>>& out)
    {
        if (root == nullptr) return;

        if (root->contains(point))
        {
            out.push_back(std::make_pair(root->low, root->high));
            intersections(root->left, point, out);
            intersections(root->right, point, out);
            return;
        }

        if (root->left != nullptr && root->left->max >= point)
        {
            intersections(root->left, point, out);
            return;
        }
        intersections(root->right, point, out);
    }
};

template <typename T>
class Map
{
private:
    Tree<T>* m_tree;
    std::map<std::pair<T, T>, long long int> m_map;

public:
    Map() : m_map() { m_tree = new Tree<T>(); }
    ~Map()
    {
        if (m_tree != nullptr) delete m_tree;
        m_tree = nullptr;
    }

    void insert(T low, T high, long long int delta)
    {
        m_tree->insert(low, high);
        m_map[std::make_pair(low, high)] = delta;
    }

    long long int operator[](T p)
    {
        std::vector<std::pair<T, T>> results = std::vector<std::pair<T, T>>();
        m_tree->intersections(p, results);
        if (results.empty()) return p;
        if (results.size() > 1)
        {
            std::cout << "Multiple possible map values found for point " << p << ":" << std::endl;
            for (const auto& i : results) std::cout << "\t[" << i.first << ", " << i.second << "]" << std::endl;
        }
        return m_map.at(results.front()) + p;
    }

private:

};


std::vector<long long int> seeds;
Map<long long int> seedSoilMap, soilFertilizerMap, fertilizerWaterMap,
    waterLightMap, lightTemperatureMap, temperatureHumidityMap,
    humidityLocationMap;

void solve()
{
    long long int min_location = LONG_LONG_MAX;
    for (long long int i : seeds)
    {
        long long int soil, fertilizer, water, light, temperature, humidity, location;
        soil = seedSoilMap[i];
        fertilizer = soilFertilizerMap[soil];
        water = fertilizerWaterMap[fertilizer];
        light = waterLightMap[water];
        temperature = lightTemperatureMap[light];
        humidity = temperatureHumidityMap[temperature];
        location = humidityLocationMap[humidity];
        std::cout << "Seed " << i << ": " << soil << " -> " << fertilizer << " -> "
            << water << " -> " << light << " -> " << temperature << " -> " 
            << humidity << " -> " << location << std::endl;
        min_location = std::min(location, min_location);
    }
    std::cout << min_location << std::endl;
}


int main()
{
    seeds = std::vector<long long int>();

    std::string s;
    std::cin >> s;
    if (s != "seeds:")
    {
        std::cout << "Expected seeds:" << std::endl;
        return -1;
    }
    while (std::cin >> s)
    {
        if (s == "seed-to-soil") break;
        long long int n = atoll(s.c_str());
        seeds.push_back(n);
    }
    std::cin >> s;

    while (std::cin >> s)
    {
        if (s == "soil-to-fertilizer") break;
        long long int dest, source, range;
        dest = atoll(s.c_str());
        std::cin >> source >> range;

        seedSoilMap.insert(source, source+range-1, dest-source);
    }
    std::cin >> s;

    while (std::cin >> s)
    {
        if (s == "fertilizer-to-water") break;
        long long int dest, source, range;
        dest = atoll(s.c_str());
        std::cin >> source >> range;

        soilFertilizerMap.insert(source, source+range-1, dest-source);
    }
    std::cin >> s;

    while (std::cin >> s)
    {
        if (s == "water-to-light") break;
        long long int dest, source, range;
        dest = atoll(s.c_str());
        std::cin >> source >> range;

        fertilizerWaterMap.insert(source, source+range-1, dest-source);
    }
    std::cin >> s;

    while (std::cin >> s)
    {
        if (s == "light-to-temperature") break;
        long long int dest, source, range;
        dest = atoll(s.c_str());
        std::cin >> source >> range;

        waterLightMap.insert(source, source+range-1, dest-source);
    }
    std::cin >> s;

    while (std::cin >> s)
    {
        if (s == "temperature-to-humidity") break;
        long long int dest, source, range;
        dest = atoll(s.c_str());
        std::cin >> source >> range;

        lightTemperatureMap.insert(source, source+range-1, dest-source);
    }
    std::cin >> s;

    while (std::cin >> s)
    {
        if (s == "humidity-to-location") break;
        long long int dest, source, range;
        dest = atoll(s.c_str());
        std::cin >> source >> range;

        temperatureHumidityMap.insert(source, source+range-1, dest-source);
    }
    std::cin >> s;

    while (std::cin >> s)
    {
        long long int dest, source, range;
        dest = atoll(s.c_str());
        std::cin >> source >> range;

        humidityLocationMap.insert(source, source+range-1, dest-source);
    }

    solve();
}
