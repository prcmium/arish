#include <iostream>
#include <vector>

using namespace std;

struct Edge{
    int v; // в какую верщину ведет
    int flow; 
    int capacity; 

    Edge(int v, int capacity)
        : v(v), flow(0), capacity(capacity) {}

    int get_capacity() { 
        return capacity - flow;
    }
};

const int INF = (int)(1e9) + 666;
const int N = 666;
int S, T; 

vector<Edge> edges;
vector<int> graph[N]; 
int used[N]; // массив использованных вершин
int timer = 1; 

void add_edge(int v, int u, int capacity) {
    graph[v].emplace_back(edges.size()); 
    edges.emplace_back(u, capacity); 
    graph[u].emplace_back(edges.size()); 
    edges.emplace_back(v, 0); 
}
int dfs(int v, int min_capacity) {
    if (v == T) {
       
        return min_capacity;
    }
    used[v] = timer;
    for (int index : graph[v]) {
        if (edges[index].get_capacity() == 0) {
            continue; 
        }
        if (used[edges[index].v] == timer) {
            continue;
        }
        int x = dfs(edges[index].v, min(min_capacity, edges[index].get_capacity()));
        if (x) { 
            edges[index].flow += x;
            edges[index ^ 1].flow -= x;
            return x;
        }
    }
  
    return 0;
}

int main() {
    int n, m;
    cin >> n >> m >> S >> T;
    for (int i = 0; i < m; ++i) {
        int v, u, capacity;
        cin >> v >> u >> capacity; // v - откуда, u - куда, capacity - пропускная способность
        add_edge(v, u, capacity);
    }
    while (dfs(S, INF)) {  
        ++timer;
    }
  
    int result = 0;
    for (int index : graph[S]) {
        result += edges[index].flow;
    }
    cout << "Максимальный поток: " << result << endl;
    return 0;
}
