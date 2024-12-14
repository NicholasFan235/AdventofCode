#include <bits/stdc++.h>

std::map<char, int> shapeMap{
    {'|', 0b0101}, {'-', 0b1010}, {'L', 0b0011}, {'J', 0b1001}, {'7', 0b1100}, {'F', 0b0110}, {'.', 0b0000}, {'S', 0b1111}
};
std::map<int, char> connectionsToShapeMap;

struct Node {
    char shape;
    int y, x;
    std::set<Node*> neighbours;

    Node(const char s, int y, int x) : shape(s), y(y), x(x), neighbours() {}
};

struct Pipeline {
    std::set<Node*> nodes;
    Node* previous;
    Node* open_end;
    int direction = 0;

    Pipeline(Node* previous, Node* start) : open_end(start), previous(previous), nodes() {
        nodes.insert(start); nodes.insert(previous);
        if (open_end->y > previous->y) direction = 0b0100;
        if (open_end->y < previous->y) direction = 0b0001;
        if (open_end->x > previous->x) direction = 0b0010;
        if (open_end->x < previous->x) direction = 0b1000;
    }
};

std::vector<std::vector<Node*>> grid;
std::vector<Pipeline> pipelines;
std::set<Node*> loop_nodes;
Node* start_node;

void connectNeighbours()
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            grid[i][j]->neighbours.clear();
            char connections = shapeMap.at(grid[i][j]->shape);
            if (connections & 0b0001) if (i > 0) if (shapeMap.at(grid[i-1][j]->shape) & 0b0100) grid[i][j]->neighbours.insert(grid[i-1][j]);
            if (connections & 0b0100) if (i < grid.size()-1) if (shapeMap.at(grid[i+1][j]->shape) & 0b0001) grid[i][j]->neighbours.insert(grid[i+1][j]);
            if (connections & 0b0010) if (j < grid[i].size()-1) if (shapeMap.at(grid[i][j+1]->shape) & 0b1000) grid[i][j]->neighbours.insert(grid[i][j+1]);
            if (connections & 0b1000) if (j > 0) if (shapeMap.at(grid[i][j-1]->shape) & 0b0010) grid[i][j]->neighbours.insert(grid[i][j-1]);
        }
    }
}

bool extend(Pipeline& pipeline)
{
    if (pipeline.open_end->neighbours.size() < 2) return false;
    if (pipeline.open_end->neighbours.size() > 2)
        std::cout << "Reached Node with more than 2 connections" << std::endl;

    for (Node* neighbour : pipeline.open_end->neighbours)
    {
        if (neighbour == pipeline.previous) continue;
        pipeline.previous = pipeline.open_end;
        pipeline.nodes.insert(neighbour);
        pipeline.open_end = neighbour;
        return true;
    }
    return false;
}

void find_loop()
{
    pipelines = std::vector<Pipeline>();
    for (Node* neighbour : start_node->neighbours)
    {
        pipelines.emplace_back(start_node, neighbour);
    }

    while (pipelines.size() > 0)
    {
        for (int i = 0; i < pipelines.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (pipelines[i].open_end == pipelines[j].open_end)
                {
                    if (pipelines[i].nodes.size() != pipelines[j].nodes.size())
                    {
                        std::cout << "Unexpected piplines of different lengths" << std::endl;
                    }
                    loop_nodes = std::set<Node*>();
                    loop_nodes.insert(pipelines[i].nodes.begin(), pipelines[i].nodes.end());
                    loop_nodes.insert(pipelines[j].nodes.begin(), pipelines[j].nodes.end());
                    int origin_connections = pipelines[i].direction | pipelines[j].direction;
                    if (connectionsToShapeMap.find(origin_connections) == connectionsToShapeMap.end())
                        std::cout << "Cannot find shape for connections: " << std::bitset<4>(origin_connections) << " (" << origin_connections << ")" << std::endl;
                    start_node->shape = connectionsToShapeMap.at(origin_connections);
                    std::swap(pipelines[i], pipelines.back()); pipelines.pop_back();
                    std::swap(pipelines[j], pipelines.back()); pipelines.pop_back();
                }
            }
        }
        for (int i = pipelines.size()-1; i>=0; i--)
        {
            if (!extend(pipelines[i]))
            {
                std::swap(pipelines[i], pipelines.back());
                pipelines.pop_back();
            }
        }
    }
}

bool is_inside(Node* node)
{
    int ctr = 0;
    for (int i = node->x; i < grid[node->y].size(); i++)
    {
        char c = grid[node->y][i]->shape;
        if (c == 'L' || c == 'F' || c == '|') ctr++;
    }
    return ctr%2 == 1;
}

void solve()
{
    find_loop();

    connectNeighbours();
    
    Pipeline loop = Pipeline(start_node, *start_node->neighbours.begin());
    std::vector<Node*> nodes = std::vector<Node*>();
    nodes.push_back(start_node);
    nodes.push_back(loop.open_end);
    extend(loop);
    while (loop.previous != start_node)
    {
        nodes.push_back(loop.open_end);
        extend(loop);
    }
    nodes.push_back(loop.open_end);

    std::cout << "Loop with " << loop_nodes.size() << " nodes." << std::endl;

    long long area = 0;
    for (int i = 1; i < nodes.size()-1; i++)
    {
        area += (long long)nodes[i]->y * (nodes[i-1]->x - nodes[i+1]->x);
    }
    area = std::abs(area);
    if (area%2 != 0) std::cout << "Computed Non Integer Area" << std::endl;
    area /= 2;
    std::cout << "Area: " << area << std::endl;

    long long interior_points = area + 1 - loop_nodes.size()/2;
    std::cout << interior_points << " interior points." << std::endl;
}


int main()
{
    for (const auto& p : shapeMap) connectionsToShapeMap[p.second] = p.first;

    grid = std::vector<std::vector<Node*>>();

    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) continue;
        grid.push_back(std::vector<Node*>());
        for (const char c : s)
        {
            grid.back().push_back(new Node(c, grid.size()-1, grid.back().size()));
            if (c == 'S') start_node = grid.back().back();
        }
    }
    connectNeighbours();
    solve();
}
