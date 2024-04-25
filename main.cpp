#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isBipartite(vector<vector<int>>& graph, int src, vector<int>& colors){
    queue<int> q;
    q.push(src);
    colors[src] = 1; 

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (int v : graph[u]){
            if (colors[v] == colors[u]) 
                return false;
            if (colors[v] == -1){ 
                colors[v] = 1 - colors[u];
                q.push(v);
            }
        }
    }
    return true;
}

bool bpm(vector<vector<int>>& bpGraph, int u, vector<bool>& seen, vector<int>& matchR){
    for (int v = 0; v < bpGraph[u].size(); v++){
        if (bpGraph[u][v] && !seen[v]){
            seen[v] = true;
            if (matchR[v] < 0 || bpm(bpGraph, matchR[v], seen, matchR)){
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxMatching(vector<vector<int>>& graph, int n, int m){
    vector<int> matchR(m, -1); 
    int result = 0; 

    for (int u = 0; u < n; u++){
        vector<bool> seen(m, false);
        if (bpm(graph, u, seen, matchR))
            result++;
    }
    return result;
}

int main(){
    int n = 4; 
    int m = 4; 
    vector<vector<int>> graph(n, vector<int>(m, 0)); 

    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][2] = 1;
    graph[2][3] = 1;

    vector<int> colors(n, -1); 

    if (isBipartite(graph, 0, colors)) {
        cout << "Граф является двудольным." << endl;
        cout << "Максимальное совпадение: " << maxMatching(graph, n, m) << endl;
    } else {
        cout << "Граф не является двудольным." << endl;
    }

    return 0;
}