#include <bits/stdc++.h>

std::map<char, int> shapeMap{
    {'|', 0b0101}, {'-', 0b1010}, {'L', 0b0011}, {'J', 0b1001}, {'7', 0b1100}, {'F', 0b0110}, {'.', 0b0000}, {'S', 0b1111}
};

struct Node {
    char shape;
    std::set<Node*> neighbours;

    Node(const char s) : shape(s), neighbours() {}
};

struct Pipeline {
    std::set<Node*> nodes;
    Node* previous;
    Node* open_end;

    Pipeline(Node* previous, Node* start) : open_end(start), previous(previous), nodes() {
        nodes.insert(start); nodes.insert(previous);
    }
};

std::vector<std::vector<Node*>> grid;
std::vector<Pipeline> pipelines;
Node* start_node;

void connectNeighbours()
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
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


void solve()
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
                    std::cout << pipelines[i].nodes.size() - 1 << std::endl;
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


int main()
{
    grid = std::vector<std::vector<Node*>>();

    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) continue;
        grid.push_back(std::vector<Node*>());
        for (const char c : s)
        {
            grid.back().push_back(new Node(c));
            if (c == 'S') start_node = grid.back().back();
        }
    }
    connectNeighbours();
    solve();
}
