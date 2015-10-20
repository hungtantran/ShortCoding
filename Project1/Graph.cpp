#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include "HelperMethod.h"

using namespace std;

struct Graph {
    int numVertices;
    vector<vector<int>> edges;

    Graph(int numVertices) :
        numVertices(numVertices)
    {
        edges.resize(numVertices);
    }

    void addEdge(int source, int dest)
    {
        edges[source].emplace_back(dest);
    }

    void addUndirectedEdge(int source, int dest)
    {
        edges[source].emplace_back(dest);
        edges[dest].emplace_back(source);
    }

    void BFS(int startNode)
    {
        if (startNode < 0 || startNode >= numVertices)
        {
            return;
        }

        queue<int> toVisit;
        set<int> visited;
        toVisit.push(startNode);

        while (!toVisit.empty())
        {
            int nextNode = toVisit.front();
            toVisit.pop();
            visited.insert(nextNode);

            cout << nextNode << " ";
            for (int i = 0; i < edges[nextNode].size(); ++i)
            {
                if (visited.find(edges[nextNode][i]) == visited.end())
                {
                    toVisit.push(edges[nextNode][i]);
                }
            }
        }
        cout << endl;
    }

    void DFS(int startNode)
    {
        if (startNode < 0 || startNode >= numVertices)
        {
            return;
        }

        stack<int> toVisit;
        set<int> visited;
        toVisit.push(startNode);

        while (!toVisit.empty())
        {
            int nextNode = toVisit.top();
            toVisit.pop();
            visited.insert(nextNode);

            cout << nextNode << " ";
            for (int i = 0; i < edges[nextNode].size(); ++i)
            {
                if (visited.find(edges[nextNode][i]) == visited.end())
                {
                    toVisit.push(edges[nextNode][i]);
                }
            }
        }
        cout << endl;
    }

    bool isCycle()
    {
        if (numVertices == 0)
        {
            return false;
        }

        queue<int> toVisit;
        for (int i = 0; i < this->numVertices; ++i)
        {
            toVisit.push(i);
        }

        while (!toVisit.empty())
        {
            int nextNode = toVisit.front();
            toVisit.pop();

            set<int> visited;
            queue<int> toCheck;
            toCheck.push(nextNode);
            while (!toCheck.empty())
            {
                int nextCheck = toCheck.front();
                toCheck.pop();
                visited.insert(nextCheck);

                for (int i = 0; i < this->edges[nextCheck].size(); ++i)
                {
                    if (visited.find(this->edges[nextCheck][i]) != visited.end())
                    {
                        return true;
                    }

                    toCheck.push(this->edges[nextCheck][i]);
                }
            }
        }

        return false;
    }
};

struct Graph2
{
    vector<vector<int>> graph;

    Graph2(int numVertices)
    {
        graph.resize(numVertices);
        for (int i = 0; i < graph.size(); ++i)
        {
            graph[i].resize(numVertices, 0);
        }
    }

    void addEdge(int src, int dest)
    {
        graph[src][dest] = 1;
    }

    void addEdge(int src, int dest, int weight)
    {
        graph[src][dest] = weight;
    }
};

//http://www.geeksforgeeks.org/detect-cycle-in-a-graph/
// int main()
int detect_cyle_in_graph()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    cout << g.isCycle() << endl;

    Graph g2(4);
    g2.addEdge(3, 0);
    g2.addEdge(3, 1);
    g2.addEdge(3, 2);
    g2.addEdge(1, 2);
    cout << g2.isCycle() << endl;

    Graph g3(4);
    g3.addEdge(3, 0);
    g3.addEdge(3, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 3);
    cout << g3.isCycle() << endl;

    int test;
    cin >> test;

    return 0;
}

//http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/
int main()
//int BFS()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    g.BFS(2);
    g.DFS(2);

    int test;
    cin >> test;

    return 0;
}