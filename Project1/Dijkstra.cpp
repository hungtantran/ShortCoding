// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

#include "HelperMethod.h"

using namespace std;

// First method, using priority queue
struct Vertex {
    int index;
    int distance;

    Vertex(int index, int distance) : index(index), distance(distance) {};

    struct Compare {
        bool operator() (const Vertex& left, const Vertex& right) {
            return left.distance > right.distance;
        }
    };
};

void dijkstra_1(const vector<vector<int>>& graph, int start_pos) {
    vector<bool> visited(graph.size(), false);
    priority_queue<Vertex, std::vector<Vertex>, Vertex::Compare> vertex_queue;
    vertex_queue.emplace(Vertex(start_pos, 0));
    vector<int> distances(graph.size(), INT_MAX);
    distances[start_pos] = 0;

    while (!vertex_queue.empty()) {
        Vertex cur_vertex = vertex_queue.top();
        vertex_queue.pop();
        if (visited[cur_vertex.index]) {
            continue;
        }
        visited[cur_vertex.index] = true;
        for (int i = 0; i < graph[cur_vertex.index].size(); ++i) {
            if (!visited[i] && graph[cur_vertex.index][i] > 0) {
                int next_distance = graph[cur_vertex.index][i] + distances[cur_vertex.index];
                if (next_distance < distances[i]) {
                    distances[i] = next_distance;
                    vertex_queue.emplace(Vertex(i, distances[i]));
                }
            }
        }
    }

    HelperMethod::printArray(distances);
}

// Second method
int MinUnprocessedVertex(const vector<int>& distances, const vector<bool>& visited) {
    int min_distance = INT_MAX;
    int min_index = -1;
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i] && min_distance >= distances[i]) {
            min_index = i;
            min_distance = distances[i];
        }
    }
    return min_index;
}

void dijkstra_2(const vector<vector<int>>& graph, int start_pos) {
    vector<int> distances(graph.size(), INT_MAX);
    distances[start_pos] = 0;
    vector<bool> visited(graph.size(), false);
    for (int i = 0; i < graph.size(); i++) {
        int next_vertex = MinUnprocessedVertex(distances, visited);
        visited[next_vertex] = true;
        for (int j = 0; j < graph[next_vertex].size(); ++j) {
            if (!visited[j] && graph[next_vertex][j] > 0) {
                int distance = distances[next_vertex] + graph[next_vertex][j];
                if (distance < distances[j]) {
                    distances[j] = distance;
                }
            }
        }
    }
    HelperMethod::printArray(distances);
}

// Third implementation
void dijkstra_3(const vector<vector<pair<int, int>>>& graph, int start_pos) {
    vector<bool> visited(graph.size(), false);
    vector<int> distances(graph.size(), INT_MAX);
    distances[start_pos] = 0;

    for (int i = 0; i < graph.size(); ++i) {
        int next_vertex = MinUnprocessedVertex(distances, visited);
        visited[next_vertex] = true;
        for (int j = 0; j < graph[next_vertex].size(); ++j) {
            const pair<int, int> neighbor = graph[next_vertex][j];
            if (!visited[neighbor.first] && distances[next_vertex] + neighbor.second < distances[neighbor.first]) {
                distances[neighbor.first] = distances[next_vertex] + neighbor.second;
            }
        }
    }

    HelperMethod::printArray(distances);
}

// Fourth implementation
// Be careful:
// + struct contain const reference doesn't have default operator=
// + Edge1 and NodeDistance1 should hold pointer to Node1 instead of reference or index
struct Node1;

struct Edge1 {
    int weight;
    Node1* source;
    Node1* target;

    Edge1(int weight, Node1* source, Node1* target)
        : weight(weight), source(source), target(target) {}

};

struct Node1 {
    int index;
    std::vector<Edge1> edges;

    Node1(int index) : index(index) {}
};

void addEdge(Node1* source, Node1* target, int weight, bool undirected=true) {
    source->edges.emplace_back(Edge1(weight, source, target));
    if (undirected) {
        target->edges.emplace_back(Edge1(weight, target, source));
    }
}

struct NodeDistance1 {
    Node1* node;
    int distance;
    NodeDistance1(Node1* node, int distance)
        : node(node), distance(distance) {}

    struct Comapre {
        bool operator() (const NodeDistance1& left, const NodeDistance1& right) {
            return left.distance > right.distance;
        }
    };
};

void dijkstra_4(struct Node1& start) {
    set<int> visited;
    map<int, int> distances;
    distances.emplace(start.index, 0);
    priority_queue<NodeDistance1, std::vector<NodeDistance1>, NodeDistance1::Comapre> queue;
    queue.emplace(NodeDistance1(&start, 0));

    while (!queue.empty()) {
        const NodeDistance1 next = queue.top();
        queue.pop();
        if (visited.find(next.node->index) != visited.end()) {
            continue;
        }
        visited.insert(next.node->index);
        distances.emplace(next.node->index, next.distance);
        const vector<Edge1>& edges = next.node->edges;
        for (int i = 0; i < edges.size(); ++i) {
            if (visited.find(edges[i].target->index) == visited.end()) {
                int distance = edges[i].weight + next.distance;
                if (distances.find(edges[i].target->index) == distances.end() || distance < distances.at(edges[i].target->index)) {
                    queue.emplace(NodeDistance1(edges[i].target, distance));
                }
            }
        }
    }

    HelperMethod::printMap(distances);
}

// Fifth implementation
pair<int, int> MinUnprocessedCell(const vector<vector<bool>>& visited, const vector<vector<int>>& distances) {
    if (visited.size() == 0) {
        return{ -1, -1 };
    }
    int min_distance = INT_MAX;
    pair<int, int> min_cell = { -1, -1 };
    for (int i = 0; i < visited.size(); ++i) {
        for (int j = 0; j < visited[0].size(); ++j) {
            if (!visited[i][j] && distances[i][j] != -1 && min_distance >= distances[i][j]) {
                min_distance = distances[i][j];
                min_cell = { i, j };
            }
        }
    }
    return min_cell;
}

void dijkstra_5(vector<vector<int>> matrix, pair<int, int> start) {
    if (matrix.size() == 0) {
        return;
    }
    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));
    vector<vector<int>> distances(matrix.size(), vector<int>(matrix[0].size(), -1));
    distances[start.first][start.second] = 0;

    for (int i = 0; i < matrix.size() * matrix[0].size(); ++i) {
        pair<int, int> next = MinUnprocessedCell(visited, distances);
        if (next.first == -1 || next.second == -1) {
            break;
        }
        visited[next.first][next.second] = true;
        for (int m = -1; m <= 1; ++m) {
            for (int n = -1; n <= 1; ++n) {
                if (m == 0 && n == 0) {
                    continue;
                }
                if (next.first + m < 0 || next.first + m >= matrix.size()) {
                    continue;
                }
                if (next.second + n < 0 || next.second + n >= matrix[0].size()) {
                    continue;
                }
                if (!visited[next.first + m][next.second + n] && matrix[next.first + m][next.second + n] != 0) {
                    int distance = distances[next.first][next.second] + 1;
                    if (distances[next.first + m][next.second + n] == -1 || distance < distances[next.first + m][next.second + n]) {
                        distances[next.first + m][next.second + n] = distance;
                    }
                }
            }
        }
    }
    HelperMethod::printMatrix(distances);
}

int main() {
    /* Let us create the example graph discussed above */
    vector<vector<int>> graph =
    { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
    { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
    { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
    { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
    { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
    { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
    { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
    { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
    { 0, 0, 2, 0, 0, 0, 6, 7, 0 }};

    dijkstra_1(graph, 0);
    dijkstra_2(graph, 0);

    vector<vector<std::pair<int, int>>> graph_2 =
    {
        { { 1, 4 }, { 7, 8 } },
        { { 0, 4 }, { 2, 8 }, { 7, 11 } },
        { { 1, 8 }, { 3, 7 }, { 5, 4 }, { 8, 2 } },
        { { 2, 7 }, { 4, 9 }, { 5, 14 } },
        { { 3, 9 }, { 5, 10 } },
        { { 2, 4 }, { 3, 14 }, { 4, 10 }, { 6, 2 } },
        { { 5, 2 }, { 7, 1 }, { 8, 6 } },
        { { 0, 8 }, { 1, 11 }, { 6, 1 }, { 8, 7 } },
        { { 2, 2 }, { 6, 6 }, {7, 7} }
    };
    dijkstra_3(graph_2, 0);

    Node1 node0(0);
    Node1 node1(1);
    Node1 node2(2);
    Node1 node3(3);
    Node1 node4(4);
    Node1 node5(5);
    Node1 node6(6);
    Node1 node7(7);
    Node1 node8(8);
    addEdge(&node0, &node1, 4);
    addEdge(&node0, &node7, 8);
    addEdge(&node1, &node2, 8);
    addEdge(&node7, &node1, 11);
    addEdge(&node2, &node3, 7);
    addEdge(&node2, &node5, 4);
    addEdge(&node2, &node8, 2);
    addEdge(&node3, &node4, 9);
    addEdge(&node3, &node5, 14);
    addEdge(&node4, &node5, 10);
    addEdge(&node5, &node6, 2);
    addEdge(&node6, &node7, 1);
    addEdge(&node6, &node8, 6);
    addEdge(&node7, &node8, 7);
    dijkstra_4(node0);

    vector<vector<int>> graph_3 =
    {
        { 1, 1, 0, 1, 1, 1, 1 },
        { 1, 1, 0, 1, 0, 0, 1 },
        { 1, 1, 0, 1, 0, 1, 1 },
        { 1, 1, 1, 1, 0, 1, 1 }
    };
    dijkstra_5(graph_3, {1, 1});

    return 0;
}