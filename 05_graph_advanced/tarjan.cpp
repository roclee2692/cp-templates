/*
 * 【Tarjan 算法】- 求强连通分量（SCC）
 * 
 * 时间复杂度：O(n + m)
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 求强连通分量
 *   - 缩点成 DAG（求 SCC 个数的题目）
 *   - 2-SAT 问题（特殊情况）
 *   - 图的连通性分析
 * 
 * 模板题：
 *   - 洛谷 P3387 - 【模板】缩点
 *   - Codeforces 1109D - Sasha and His Friend
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

struct Tarjan {
    int n;
    vector<int> adj[MAXN];
    int dfn[MAXN], low[MAXN];
    bool in_stack[MAXN];
    stack<int> st;
    int timestamp = 0, scc_count = 0;
    vector<int> scc_id;
    
    Tarjan(int n) : n(n), scc_id(n + 1) {}
    
    void dfs(int u) {
        dfn[u] = low[u] = ++timestamp;
        st.push(u);
        in_stack[u] = true;
        
        for (int v : adj[u]) {
            if (!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        
        // 找到一个 SCC 的根
        if (dfn[u] == low[u]) {
            scc_count++;
            while (true) {
                int v = st.top();
                st.pop();
                in_stack[v] = false;
                scc_id[v] = scc_count;
                if (v == u) break;
            }
        }
    }
    
    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    Tarjan tarjan(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        tarjan.adj[u].push_back(v);
    }
    
    tarjan.solve();
    
    cout << "SCC 个数: " << tarjan.scc_count << "\n";
    
    for (int i = 1; i <= n; i++) {
        cout << "节点 " << i << " 属于 SCC " << tarjan.scc_id[i] << "\n";
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. dfn[u]：u 的发现时间戳
 * 2. low[u]：u 及其子树能到达的最小时间戳
 * 3. dfn[u] == low[u]：u 是某个 SCC 的根
 * 4. 栈用途：存储当前 DFS 路径上的节点
 * 5. in_stack[]：判断边是否是回边（指向栈中节点）
 * 
 * 【关键性质】
 * - 回边：v 在栈中且未被弹出
 * - 前向边/横边：不影响 low 值（或者说 dfn[v] > dfn[u]）
 * 
 * 【常见变体】
 * - Kosaraju 算法（两次 DFS）
 * - 2-SAT（Tarjan 特化版本）
 * - 缩点后的 DAG
 * 
 * 【提交前检查】
 * ✓ dfn 数组初值为 0（未访问）
 * ✓ low 初始化为 dfn[u]
 * ✓ 栈操作的一致性
 * ✓ SCC 根节点识别
 */
