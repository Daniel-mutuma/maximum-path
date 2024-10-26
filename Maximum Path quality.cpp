#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Edge {
    int to, time;
};

// DFS function to explore all valid paths
void dfs(int node, int& currentQuality, int currentTime, vector<vector<Edge>>& graph, vector<int>& values, vector<bool>& visited, unordered_set<int>& uniqueNodes, int maxTime, int& maxQuality) {
    // If the node is visited for the first time in this path, add its value to currentQuality
    if (uniqueNodes.find(node) == uniqueNodes.end()) {
        currentQuality += values[node];
        uniqueNodes.insert(node);
    }

    // If we're back at the start node (node 0) and within the allowed time, update maxQuality
    if (node == 0) {
        maxQuality = max(maxQuality, currentQuality);
    }

    visited[node] = true;  // Mark the current node as visited
    for (const Edge& edge : graph[node]) {
        if (currentTime + edge.time <= maxTime) {
            // Explore the next node if within maxTime
            dfs(edge.to, currentQuality, currentTime + edge.time, graph, values, visited, uniqueNodes, maxTime, maxQuality);
        }
    }
    visited[node] = false;  // Backtrack

    // If we added the node's value to currentQuality, remove it during backtracking
    if (uniqueNodes.find(node) != uniqueNodes.end()) {
        currentQuality -= values[node];
        uniqueNodes.erase(node);
    }
}

// Main function to find the maximum quality of a valid path
int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
    int n = values.size();
    vector<vector<Edge>> graph(n);

    // Build the adjacency list
    for (const vector<int>& edge : edges) {
        int u = edge[0], v = edge[1], time = edge[2];
        graph[u].push_back({v, time});
        graph[v].push_back({u, time});
    }

    int maxQuality = 0;
    unordered_set<int> uniqueNodes;
    vector<bool> visited(n, false);

    // Start DFS from node 0
    int currentQuality = 0;
    dfs(0, currentQuality, 0, graph, values, visited, uniqueNodes, maxTime, maxQuality);

    return maxQuality;
}

int main() {
    int n, m, maxTime;
    cout << "Enter the number of nodes: ";
    cin >> n;
    vector<int> values(n);
    cout << "Enter the values of each node: ";
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    cout << "Enter the number of edges: ";
    cin >> m;
    vector<vector<int>> edges(m, vector<int>(3));
    cout << "Enter each edge (u v time):\n";
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    cout << "Enter max time: ";
    cin >> maxTime;

    int result = maximalPathQuality(values, edges, maxTime);
    cout << "Maximum quality of a valid path: " << result << endl;

    return 0;
}
