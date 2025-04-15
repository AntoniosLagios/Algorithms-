//Breadth-First Search (BFS)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int start, vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// Depth-First Search (DFS)
void dfsUtil(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";

    for (int v : adj[u]) {
        if (!visited[v])
            dfsUtil(v, adj, visited);
    }
}

void dfs(int start, vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    dfsUtil(start, adj, visited);
}

//Dijkstra's Algorithm
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void dijkstra(int src, vector<vector<pair<int, int>>>& adj, int V) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto [v, weight] : adj[u]) {
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < V; i++)
        cout << "Distance to " << i << ": " << dist[i] << "\n";
}

//Kruskal’s Algorithm (MST)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) {
        return weight < other.weight;
    }
};

int find(int u, vector<int>& parent) {
    if (parent[u] != u)
        parent[u] = find(parent[u], parent);
    return parent[u];
}

void kruskal(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end());
    vector<int> parent(V);
    for (int i = 0; i < V; i++) parent[i] = i;

    int mstWeight = 0;
    for (auto& e : edges) {
        int pu = find(e.u, parent);
        int pv = find(e.v, parent);
        if (pu != pv) {
            mstWeight += e.weight;
            cout << e.u << " - " << e.v << " : " << e.weight << "\n";
            parent[pu] = pv;
        }
    }
    cout << "MST Total Weight: " << mstWeight << endl;
}

//Bellman-Ford Algorithm (Single Source Shortest Path with Negative Weights)
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, weight;
};

void bellmanFord(int V, int E, int src, vector<Edge>& edges) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        for (auto& edge : edges) {
            if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v])
                dist[edge.v] = dist[edge.u] + edge.weight;
        }
    }

    // Check for negative weight cycles
    for (auto& edge : edges) {
        if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
            cout << "Negative weight cycle detected\n";
            return;
        }
    }

    for (int i = 0; i < V; ++i)
        cout << "Distance to " << i << ": " << dist[i] << "\n";
}

//Prim's Algorithm (Minimum Spanning Tree)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void primMST(vector<vector<pair<int, int>>>& adj, int V) {
    vector<bool> inMST(V, false);
    vector<int> key(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    key[0] = 0;
    pq.push({0, 0}); // {weight, vertex}

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (auto [v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    int mstWeight = 0;
    for (int w : key) mstWeight += w;

    cout << "MST total weight: " << mstWeight << "\n";
}

//Floyd-Warshall Algorithm (All-Pairs Shortest Paths)
#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& dist, int V) {
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // Output the final distance matrix
    cout << "Shortest distances between every pair:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
