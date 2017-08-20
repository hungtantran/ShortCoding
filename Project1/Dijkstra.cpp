// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

#include <iostream>
#include <vector>
#include <queue>
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

    return 0;
}