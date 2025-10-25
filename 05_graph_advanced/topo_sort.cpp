/*
 * 【拓扑排序】- 有向无环图的线性排序
 * 
 * 时间复杂度：O(n + m) Kahn 算法
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 检测有向环
 *   - DAG 上的动态规划
 *   - 任务调度（有依赖关系）
 *   - 编译顺序
 * 
 * 模板题：
 *   - 洛谷 P1113 - 杰森的困境(拓扑排序)
 *   - Codeforces 1385F - Red-Blue Graph
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    // Kahn 算法：BFS 基础拓扑排序
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> topo_order;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // 检查是否有环
    if (topo_order.size() != n) {
        cout << "有环\n";
        return 0;
    }
    
    // 输出拓扑排序
    for (int node : topo_order) {
        cout << node << " ";
    }
    cout << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. 入度：每个节点的前驱节点数
 * 2. 初始化：入度为 0 的节点入队
 * 3. 处理：弹出节点，更新其后继入度
 * 4. 有环检测：最后排序大小 != n
 * 5. 多个排序解：不同的初始化顺序产生不同结果
 * 
 * 【常见变体】
 * - DFS 版本拓扑排序
 * - 字典序最小的拓扑排序（优先队列）
 * - 拓扑排序 + 动态规划
 * 
 * 【提交前检查】
 * ✓ 入度数组是否正确计算
 * ✓ 有环检测逻辑
 * ✓ 输出大小验证
 * ✓ 图的表示（邻接表）
 */
