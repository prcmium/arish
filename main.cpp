#include <iostream>
#include <vector>

using namespace std;

struct Edge{
    int v; // вершина, куда ведёт ребро
    int flow; // поток, текущий по ребру
    int capacity; // пропускная способность ребра

    Edge(int v, int capacity)
        : v(v), flow(0), capacity(capacity) {}

    int get_capacity() { // пропускная способность ребра в остаточной сети
        return capacity - flow;
    }
};

const int INF = (int)(1e9) + 666;
const int N = 666;
int S, T; // сток и исток

vector<Edge> edges;
vector<int> graph[N]; // в списке смежности храним не рёбра, и индексы в списке рёбер
int used[N];
int timer = 1; // для быстрого зануления used-а

// Будем поддерживать список рёбер в таком состоянии, что для i ребра, (i ^ 1) будет обратным
void add_edge(int v, int u, int capacity) {
    graph[v].emplace_back(edges.size()); // номер ребра в списке
    edges.emplace_back(u, capacity); // прямое ребро
    graph[u].emplace_back(edges.size()); // номер ребра
    edges.emplace_back(v, 0); // обратное ребро
}
int dfs(int v, int min_capacity) {
    if (v == T) {
        // нашли увеличивающий путь, вдоль которого можно пустить min_capacity потока
        return min_capacity;
    }
    used[v] = timer;
    for (int index : graph[v]) {
        if (edges[index].get_capacity() == 0) {
            continue; // ребро отсутсвует в остаточной сети
        }
        if (used[edges[index].v] == timer) {
            continue;
        }
        int x = dfs(edges[index].v, min(min_capacity, edges[index].get_capacity()));
        if (x) { // нашли путь по которому можно пустить x потока
            edges[index].flow += x;
            edges[index ^ 1].flow -= x;
            return x;
        }
    }
    // не существует пути из v в T
    return 0;
}

int main() {
    int n, m;
    cin >> n >> m >> S >> T;
    for (int i = 0; i < m; ++i) {
        int v, u, capacity;
        cin >> v >> u >> capacity;
        add_edge(v, u, capacity);
    }
    while (dfs(S, INF)) {  // ищем увеличивающий путь
        ++timer;
    }
    // увеличивающего пути нет, следовательно максимальный потока найден
    int result = 0;
    for (int index : graph[S]) {
        result += edges[index].flow;
    }
    cout << result << endl;
    return 0;
}
