#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <sstream>

using namespace std;

struct Job
{
    char name;
    int deadline;
    int profit;
};

int JobCompare(const void* j1, const void* j2)
{
    return ((Job*)(j2))->profit - ((Job*)(j1))->profit;
}

/*
// Recursive version

void job_sequencing_scheduling(const vector<Job>& arr, int curTime, vector<Job>& curJobs, vector<Job>& maxJobs, int& maxProfit)
{
    vector<Job> possibleJob;
    for (int i = 0; i < arr.size(); ++i)
    {
        if (arr[i].deadline > curTime)
        {
            bool found = false;
            for (int j = 0; j < curJobs.size(); ++j)
            {
                if (arr[i].name == curJobs[j].name)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                possibleJob.emplace_back(arr[i]);
            }
        }
    }

    if (possibleJob.empty())
    {
        int profit = 0;
        for (int i = 0; i < curJobs.size(); ++i)
        {
            profit += curJobs[i].profit;
        }

        if (profit > maxProfit)
        {
            maxJobs = curJobs;
            maxProfit = profit;
        }

        return;
    }

    for (int i = 0; i < possibleJob.size(); ++i)
    {
        curJobs.emplace_back(possibleJob[i]);
        job_sequencing_scheduling(possibleJob, curTime + 1, curJobs, maxJobs, maxProfit);
        curJobs.pop_back();
    }
}

void job_sequencing_scheduling(const vector<Job>& arr)
{
    vector<Job> curJobs;
    vector<Job> maxJobs;
    int maxProfit = 0;
    job_sequencing_scheduling(arr, 0, curJobs, maxJobs, maxProfit);

    for (int i = 0; i < maxJobs.size(); ++i)
    {
        cout << maxJobs[i].name << " ";
    }

    cout << endl;
} */

void job_sequencing_scheduling(vector<Job>& arr)
{
    qsort(&(arr[0]), arr.size(), sizeof(Job), JobCompare);

    vector<char> timeSlots(arr.size(), ' ');

    for (int i = 0; i < arr.size(); ++i)
    {
        for (int j = timeSlots.size() - 1; j >= 0; --j)
        {
            if (timeSlots[j] == ' ' && arr[i].deadline > j)
            {
                timeSlots[j] = arr[i].name;
                break;
            }
        }
    }

    for (int i = 0; i < timeSlots.size(); ++i)
    {
        if (timeSlots[i] != ' ')
        {
            cout << timeSlots[i] << " ";
        }
    }
    cout << endl;
}

void dijkstra_shortest_path(vector<vector<int>>& graph, int source)
{
    vector<bool> include(graph.size(), false);
    vector<int> costs(graph.size(), INT_MAX);
    costs[source] = 0;

    int count = 0;
    while (count < graph.size())
    {
        int minIndex = 0;
        int minCost = INT_MAX;
        for (int i = 0; i < costs.size(); ++i)
        {
            if (include[i] == false && minCost > costs[i])
            {
                minIndex = i;
                minCost = costs[i];
            }
        }

        include[minIndex] = true;
        for (int i = 0; i < graph[minIndex].size(); ++i)
        {
            if (include[i] == false && graph[minIndex][i] > 0 && costs[minIndex] + graph[minIndex][i] < costs[i])
            {
                costs[i] = costs[minIndex] + graph[minIndex][i];
            }
        }

        ++count;
    }

    for (int i = 0; i < costs.size(); ++i)
    {
        cout << i << " " << costs[i] << endl;
    }
}

void dijkstra_shortest_path(vector<vector<int>>& graph, int source, int dest)
{
    vector<bool> include(graph.size(), false);
    vector<int> costs(graph.size(), INT_MAX);
    costs[source] = 0;

    int count = 0;
    while (count < graph.size())
    {
        int minIndex = 0;
        int minCost = INT_MAX;
        for (int i = 0; i < costs.size(); ++i)
        {
            if (include[i] == false && minCost > costs[i])
            {
                minIndex = i;
                minCost = costs[i];
            }
        }

        include[minIndex] = true;
        for (int i = 0; i < graph[minIndex].size(); ++i)
        {
            if (include[i] == false && graph[minIndex][i] > 0 && costs[minIndex] + graph[minIndex][i] < costs[i])
            {
                costs[i] = costs[minIndex] + graph[minIndex][i];
            }
        }

        ++count;
    }

    stack<int> path;
    path.push(dest);
    int cost = costs[dest];
    int curIndex = dest;
    while (cost > 0)
    {
        for (int i = 0; i < graph[curIndex].size(); ++i)
        {
            if (graph[curIndex][i] > 0 && costs[i] == cost - graph[curIndex][i])
            {
                curIndex = i;
                cost = costs[i];
                path.push(i);
                break;
            }
        }
    }

    while (!path.empty())
    {
        cout << path.top() << " ";
        path.pop();
    }
}

// http://www.geeksforgeeks.org/job-sequencing-problem-set-1-greedy-algorithm/
// int main()
int job_sequencing_scheduling()
{
    vector<Job> arr = { { 'a', 2, 100 }, { 'b', 1, 19 }, { 'c', 2, 27 }, { 'd', 1, 25 }, { 'e', 3, 15 } };
    job_sequencing_scheduling(arr);

    vector<Job> arr2 = { { 'a', 4, 20 }, { 'b', 1, 10 }, { 'c', 1, 40 }, { 'd', 1, 30 } };
    job_sequencing_scheduling(arr2);

    int test;
    cin >> test;

    return 0;
}

// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
// int main()
int dijkstra_shortest_path()
{
    vector<vector<int>> graph =
    {
    { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
    { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
    { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
    { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
    { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
    { 0, 0, 4, 0, 10, 0, 2, 0, 0 },
    { 0, 0, 0, 14, 0, 2, 0, 1, 6 },
    { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
    { 0, 0, 2, 0, 0, 0, 6, 7, 0 }
    };

    dijkstra_shortest_path(graph, 0);

    cout << "Path from 0 to 8 is " << endl;
    dijkstra_shortest_path(graph, 0, 8);

    int test;
    cin >> test;

    return 0;
}

