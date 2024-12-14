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

    bool overlaps(const Node<T>& other)
    {
        return low <= other.high && other.low <= high;
    }
    
    bool contains(const T& point)
    {
        return low <= point && point <= high;
    }

    bool overlaps(const std::pair<T,T>& other)
    {
        return low <= other.second && other.first <= high;
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

    void intersections(const T& point, std::vector<std::pair<T, T>>& out)
    {
        intersections(m_root, point, out);
    }

    void intersections(const std::pair<T,T>& interval, std::vector<std::pair<T,T>>& out)
    {
        intersections(m_root, interval, out);
    }

    void find_gaps(std::vector<std::pair<T,T>>& gaps)
    {
        T max_filled = 0;
        find_gaps(m_root, max_filled, gaps);
        if (max_filled < std::numeric_limits<T>::max()) gaps.push_back(std::make_pair(max_filled+1, std::numeric_limits<T>::max()));
    }

    std::vector<std::pair<T,T>> to_vector()
    {
        std::vector<std::pair<T,T>> r = std::vector<std::pair<T,T>>();
        std::function<void(Node<T>*)> f = [&](Node<T>* node) { r.push_back(std::make_pair(node->low, node->high)); };
        ordered_for(m_root, f);
        return r;
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

    void intersections(Node<T>* root, const T& point, std::vector<std::pair<T, T>>& out)
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

    void intersections(Node<T>* root, const std::pair<T,T>& interval, std::vector<std::pair<T,T>>& out)
    {
        if (root == nullptr) return;

        if (root->overlaps(interval))
        {
            out.push_back(std::make_pair(root->low, root->high));
            intersections(root->left, interval, out);
            intersections(root->right, interval, out);
        }

        if (root->left != nullptr && root->left->max >= interval.first)
        {
            intersections(root->left, interval, out);
            return;
        }
        intersections(root->right, interval, out);
    }

    void find_gaps(Node<T>* root, T& max_filled, std::vector<std::pair<T,T>>& gaps)
    {
        if (root->left != nullptr) find_gaps(root->left, max_filled, gaps);
        
        if (root->low > max_filled+1) gaps.push_back(std::make_pair(max_filled, root->low-1));
        max_filled = std::max(root->high, max_filled);

        if (root->right != nullptr) find_gaps(root->right, max_filled, gaps);
    }

    void ordered_for(Node<T>* root, std::function<void(Node<T>*)>& callback)
    {
        if (root->left != nullptr) ordered_for(root->left, callback);

        callback(root);

        if (root->right != nullptr) ordered_for(root->right, callback);
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

    void convert(const std::pair<T,T>& interval, std::vector<std::pair<T,T>>& out)
    {
        std::vector<std::pair<T, T>> results = std::vector<std::pair<T, T>>();
        m_tree->intersections(interval, results);
        //std::cout << "Found " << results.size() << " intersections." << std::endl;
        for (const std::pair<T,T>& result : results)
        {
            out.push_back(std::make_pair(
                std::max(interval.first, result.first) + m_map.at(result),
                std::min(interval.second, result.second) + m_map.at(result)
            ));
        }
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

    void fill_gaps()
    {
        std::vector<std::pair<T,T>> gaps = std::vector<std::pair<T,T>>();
        m_tree->find_gaps(gaps);
        for (const auto& gap : gaps)
        {
            insert(gap.first, gap.second, 0);
        }
    }

    void print()
    {
        std::vector<std::pair<T,T>> intervals = m_tree->to_vector();
        for (const std::pair<T,T>& interval : intervals)
        {
            std::cout << "[" << interval.first << "-" << interval.second << "] -> " << m_map.at(interval) << std::endl;
        }
    }

private:

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<T,T>>& intervals)
{
    for (const std::pair<T,T>& interval : intervals)
    {
        os << "(" << interval.first << ", " << interval.second << ")";
    }
    os << std::endl;
    return os;
}


std::vector<std::pair<long long int, long long int>> seeds;
Map<long long int> seedSoilMap, soilFertilizerMap, fertilizerWaterMap,
    waterLightMap, lightTemperatureMap, temperatureHumidityMap,
    humidityLocationMap;

void solve()
{
    typedef long long int T;
    seedSoilMap.fill_gaps();
    //seedSoilMap.print();
    //std::cout << seeds;
    std::vector<std::pair<T,T>> soils = std::vector<std::pair<T,T>>();
    for (const auto& p : seeds) seedSoilMap.convert(p, soils);
    //std::cout << soils;

    soilFertilizerMap.fill_gaps();
    //soilFertilizerMap.print();
    std::vector<std::pair<T,T>> fertilizers = std::vector<std::pair<T,T>>();
    for (const auto& p : soils) soilFertilizerMap.convert(p, fertilizers);
    //std::cout << fertilizers;

    fertilizerWaterMap.fill_gaps();
    //fertilizerWaterMap.print();
    std::vector<std::pair<T,T>> waters = std::vector<std::pair<T,T>>();
    for (const auto& p : fertilizers) fertilizerWaterMap.convert(p, waters);
    //std::cout << waters;

    waterLightMap.fill_gaps();
    //waterLightMap.print();
    std::vector<std::pair<T,T>> lights = std::vector<std::pair<T,T>>();
    for (const auto& p : waters) waterLightMap.convert(p, lights);
    //std::cout << lights;

    lightTemperatureMap.fill_gaps();
    //lightTemperatureMap.print();
    std::vector<std::pair<T,T>> temperatures = std::vector<std::pair<T,T>>();
    for (const auto& p : lights) lightTemperatureMap.convert(p, temperatures);
    //std::cout << temperatures;

    temperatureHumidityMap.fill_gaps();
    //temperatureHumidityMap.print();
    std::vector<std::pair<T,T>> humidities = std::vector<std::pair<T,T>>();
    for (const auto& p : temperatures) temperatureHumidityMap.convert(p, humidities);
    //std::cout << humidities;

    humidityLocationMap.fill_gaps();
    //humidityLocationMap.print();
    std::vector<std::pair<T,T>> locations = std::vector<std::pair<T,T>>();
    for (const auto& p : humidities) humidityLocationMap.convert(p, locations);
    //std::cout << locations;


    T ans = std::accumulate(locations.begin(), locations.end(), std::numeric_limits<T>::max(),
        [](const T& l, const std::pair<T,T>&r){ return std::min(l, r.first); });
    std::cout << ans << std::endl;
}


int main()
{
    seeds = std::vector<std::pair<long long int, long long int>>();

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
        long long int m;
        std::cin >> m;
        seeds.push_back(std::make_pair(n,n+m-1));
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
