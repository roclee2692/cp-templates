/*
 * 【Dijkstra 算法】- 单源最短路径（堆优化版）
 * 
 * 时间复杂度：O((E + V) log V)
 * 空间复杂度：O(V + E)
 * 
 * 适用场景：
 *   - 求单源最短路径
 *   - 所有边权非负
 *   - 稠密图可用邻接矩阵，稀疏图用邻接表
 * 
 * 模板题：洛谷 P3371 - 【模板】单源最短路径（弱化版）
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;  // (距离, 节点编号)

const ll INF = 1e18;

vector<pair<int, ll>> graph[100005];  // graph[u] = {(v, w)}
ll dist[100005];
bool visited[100005];

void dijkstra(int start, int n) {
    // 初始化
    fill(dist, dist + n + 1, INF);
    fill(visited, visited + n + 1, false);
    dist[start] = 0;
    
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        // 松弛操作
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, s;
    cin >> n >> m >> s;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    
    dijkstra(s, n);
    
    for (int i = 1; i <= n; i++) {
        cout << dist[i];
        if (i < n) cout << " ";
    }
    cout << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. 使用优先队列优化：每次取距离最小的节点
 * 2. visited 数组避免重复处理同一节点
 * 3. 松弛操作：if (dist[u] + w < dist[v]) 更新
 * 4. 必须保证所有边权非负（否则用 SPFA）
 * 
 * 【常见变体】
 * - 求多源最短路：对每个源点调用一次 dijkstra()
 * - 记录路径：用 parent[] 数组记录前驱节点
 * - 输出路径：反向递推 parent[]
 * 
 * 【提交前检查】
 * - [ ] 边权是否可能为负？(是则用 SPFA)
 * - [ ] n, m 是否在范围内？
 * - [ ] 是否考虑了自环和重边？
 */
