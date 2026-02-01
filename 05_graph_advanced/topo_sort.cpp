/*
 * 【拓扑排序】- Kahn 算法（BFS）
 * 
 * 时间复杂度：O(n + m)
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 检测有向环
 *   - DAG 上的动态规划
 *   - 任务调度（有依赖关系）
 *   - 编译顺序
 * 
 * 模板题：
 *   - 洛谷 P1113 - 杰森的困境
 *   - Codeforces 1385F - Red-Blue Graph
 * 
 * 【为什么 Kahn 算法最常用？】
 * 1. 代码简单直观，容易实现
 * 2. 基于 BFS，容易理解
 * 3. 天然支持字典序最小（改用优先队列）
 * 4. 方便检测环（判断排序个数）
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int n, m;
vector<int> adj[MAXN];  // 邻接表
int in_deg[MAXN];       // 入度数组
vector<int> topo;       // 拓扑序结果

// Kahn 算法：返回 true 表示无环，false 表示有环
bool kahn() {
    queue<int> q;
    
    // 所有入度为 0 的点入队
    for (int i = 1; i <= n; i++) {
        if (in_deg[i] == 0) {
            q.push(i);
        }
    }
    
    topo.clear();
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        
        // 删除 u 的所有出边
        for (int v : adj[u]) {
            in_deg[v]--;
            if (in_deg[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // 如果排序个数 != n，说明有环
    return topo.size() == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_deg[v]++;
    }
    
    if (!kahn()) {
        cout << "有环\n";
        return 0;
    }
    
    // 输出拓扑序
    for (int x : topo) {
        cout << x << " ";
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
