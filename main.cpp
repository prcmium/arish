#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9; 
int n, m; // n - количество вершин, m - количество рёбер
vector<vector<int>> c_flow; 
vector<vector<int>> adj; 

bool bfs(vector<int>& d, int s, int t) { // строим вспомогательную сеть
    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    queue<int> A;
    A.push(s);
    while (!A.empty()) {
        int u = A.front();
        A.pop();
        for (int v : adj[u]) {
            if (c_flow[u][v] > 0 && d[v] == INF) {
                d[v] = d[u] + 1;
                A.push(v);
            }
        }
    }
    return d[t] != INF;
}

int dfs(int u, int minC, vector<int>& d, vector<int>& p, int t) { // ищем блокирующий поток
    if (u == t || minC == 0) {
        return minC;
    }
    for (int& i = p[u]; i < adj[u].size(); ++i) { // перебираем все вершины смежные u, начиная с последней проверенной
        int v = adj[u][i];
        if (d[v] == d[u] + 1) {
            int delta = dfs(v, min(minC, c_flow[u][v]), d, p, t);
            if (delta != 0) {
                c_flow[u][v] -= delta;
                c_flow[v][u] += delta;
                return delta;
            }
        }
    }
    return 0;
}

int MaxFlow(int s, int t) {
    int maxFlow = 0;
    vector<int> d(n);
    while (bfs(d, s, t)) { 
        vector<int> p(n, 0);
        int flow;
        do {
            flow = dfs(s, INF, d, p, t);
            maxFlow += flow;
        } while (flow != 0);
    }
    return maxFlow;
}

int main() {
    cin >> n >> m; 
    c_flow.assign(n, vector<int>(n, 0));
    adj.assign(n, vector<int>());

    int u, v, c;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> c; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        c_flow[u][v] = c; 
    }

    int s, t;
    cin >> s >> t; 
    cout << "Максимальный поток: " << MaxFlow(s, t) << '\n';
    
}