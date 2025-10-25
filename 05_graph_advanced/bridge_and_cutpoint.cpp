/*
 * 【桥与割点】- 找关键边和关键点
 * 
 * 时间复杂度：O(n + m)
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 找桥（删除后增加连通分量的边）
 *   - 找割点（删除后增加连通分量的点）
 *   - 图的二边连通分量
 *   - 二点连通分量
 * 
 * 模板题：
 *   - 洛谷 P3388 - 【模板】割点(割顶)
 *   - Codeforces 555B - Case of Fugitive
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

struct BridgeAndCutpoint {
    vector<int> adj[MAXN];
    int dfn[MAXN], low[MAXN];
    bool visited[MAXN];
    int timestamp = 0;
    vector<pair<int, int>> bridges;
    vector<int> cutpoints;
    int n;
    
    BridgeAndCutpoint(int n) : n(n) {}
    
    void dfs(int u, int p) {
        visited[u] = true;
        dfn[u] = low[u] = ++timestamp;
        int children = 0;
        
        for (int v : adj[u]) {
            if (v == p) {
                // 处理重边：跳过第一条返回边
                p = -1;
                continue;
            }
            
            if (visited[v]) {
                low[u] = min(low[u], dfn[v]);
            } else {
                children++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                
                // 判断桥
                if (low[v] > dfn[u]) {
                    bridges.push_back({u, v});
                }
                
                // 判断割点：不是根且低点 >= 自身时间戳
                if (u != p && low[v] >= dfn[u]) {
                    cutpoints.push_back(u);
                }
            }
        }
        
        // 根节点的割点判断：有多于 1 个子树
        if (p == -1 && children > 1) {
            cutpoints.push_back(u);
        }
    }
    
    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i, -1);
            }
        }
        
        // 去重
        sort(cutpoints.begin(), cutpoints.end());
        cutpoints.erase(unique(cutpoints.begin(), cutpoints.end()), cutpoints.end());
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    BridgeAndCutpoint bac(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        bac.adj[u].push_back(v);
        bac.adj[v].push_back(u);
    }
    
    bac.solve();
    
    cout << "桥数: " << bac.bridges.size() << "\n";
    cout << "割点数: " << bac.cutpoints.size() << "\n";
    
    for (auto [u, v] : bac.bridges) {
        cout << "桥: " << u << " - " << v << "\n";
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. 桥：low[v] > dfn[u]（v 的子树无法返回到 u 的祖先）
 * 2. 割点（非根）：low[v] >= dfn[u]
 * 3. 割点（根）：多于 1 个子树时
 * 4. 重边处理：跳过重边，用 p = -1 标记已跳过
 * 5. 重边的作用：无向图中可能出现多条相同边
 * 
 * 【常见变体】
 * - 二边连通分量：同一个分量中任意两点有两条不同的路径
 * - 二点连通分量：同一个分量中任意两点有两条不同的路径（经过不同顶点）
 * 
 * 【提交前检查】
 * ✓ 重边处理（跳过返回边）
 * ✓ 根节点的割点判断（children > 1）
 * ✓ 非根割点判断（low[v] >= dfn[u]）
 * ✓ 割点去重
 */
