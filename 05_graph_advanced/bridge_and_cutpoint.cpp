/*
 * 【桥与割点】- 找关键边和关键点
 * 
 * 时间复杂度：O(n + m) 
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 找桥（删除后增加连通分量的边）
 *   - 找割点（删除后增加连通分量的点）
 * 
 * 模板题：
 *   - 洛谷 P3388 - 【模板】割点(割顶)
 *   - Codeforces 555B - Case of Fugitive
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int n, m;
vector<int> adj[MAXN];       // 邻接表
int dfn[MAXN], low[MAXN];    // dfn: 时间戳, low: 能回溯到的最小时间戳
bool vis[MAXN];              // 是否访问过
int timestamp;               // 时间戳计数器
vector<pair<int, int>> bridges;  // 桥
set<int> cut;                // 割点（用 set 自动去重）

void dfs(int u, int fa) {
    // 【初始化】标记已访问，分配时间戳
    vis[u] = true;
    dfn[u] = low[u] = ++timestamp;
    
    // 【子树计数】记录子树个数（用于判断根是否为割点）
    int children = 0;
    
    for (int v : adj[u]) {
        // 【重边处理】第一次遇到父节点跳过，p=-1 标记已跳过
        if (v == fa) {
            fa = -1;
            continue;
        }
        
        if (vis[v]) {
            // 【回边】v 已访问，更新 low[u]
            low[u] = min(low[u], dfn[v]);
        } else {
            // 【树边】v 未访问
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            
            // 【判断桥】low[v] > dfn[u] 说明 v 无法回到 u
            if (low[v] > dfn[u]) {
                bridges.push_back({min(u, v), max(u, v)});
            }
            
            // 【判断割点（非根）】low[v] >= dfn[u] 说明 v 最多回到 u
            if (fa != -1 && low[v] >= dfn[u]) {
                cut.insert(u);
            }
        }
    }
    
    // 【判断割点（根）】根有 ≥2 个子树就是割点
    if (fa == -1 && children > 1) {
        cut.insert(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 对所有未访问节点执行 DFS
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, -1);
        }
    }
    
    cout << "桥数: " << bridges.size() << "\n";
    cout << "割点数: " << cut.size() << "\n";
    
    for (auto [u, v] : bridges) {
        cout << "桥: " << u << " - " << v << "\n";
    }
    
    for (int u : cut) {
        cout << "割点: " << u << "\n";
    }
    
    return 0;
}

/*
 * 【关键概念解释】
 * 
 * 【桥（Bridge）】
 * - 定义：删除后使图的连通分量增加的边
 * - 判断条件：low[v] > dfn[u]
 * - 含义：v 的子树无法通过其他路径回到 u 或 u 的祖先
 * - 用 > 而不是 >=：如果能回到 u，说明有另一条路径，不是桥
 *    
 * 【割点（Cut Vertex / Articulation Point）】
 * - 定义：删除后使图的连通分量增加的点
 * - 判断条件（非根）：low[v] >= dfn[u]
 * - 判断条件（根）：有 ≥2 个子树
 * - 含义：v 的子树最多只能回到 u，删除 u 后会断开
 * 
 * 【为什么桥用 > 而割点用 >=？】
 * 例子：边 u-v
 * - 如果 low[v] == dfn[u]：v 能回到 u（但不能越过 u）
 *   → u-v 不是桥（因为还能通过 v 回到 u）
 *   → 但 u 是割点（因为删除 u 后，v 无法到达 u 的祖先）
 * - 如果 low[v] > dfn[u]：v 连 u 都回不到
 *   → u-v 是桥，u 也是割点
 * 
 * 【重边处理的技巧】
 * 无向图存储：u-v 会存两次
 * - adj[u] 包含 v
 * - adj[v] 包含 u
 * 
 * 问题：DFS 从 u 到 v 后，遍历 v 的邻接点会再次遇到 u
 * 解决：第一次遇到父节点时跳过，p = -1 标记已跳过
 * 
 * 如果有重边（两条 u-v）：
 * - 第一次遇到 v==p：跳过，p=-1
 * - 第二次遇到 v==p（其实是 v==-1，不成立）：当作普通节点处理
 * 
 * 【根节点的特殊性】
 * 根节点没有父节点，判断标准不同：
 * - 非根节点：看子树能否绕过自己
 * - 根节点：看有几个子树（≥2 个就是割点）
 * 
 * 【常见应用】
 * 1. 网络可靠性分析：找关键节点和关键连接
 * 2. 二连通分量：没有割点的极大子图
 * 3. 边双连通分量：没有桥的极大子图
 */
