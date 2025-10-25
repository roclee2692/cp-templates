/*
 * 【Kruskal 算法】- 最小生成树（依赖并查集）
 * 
 * 时间复杂度：O(E log E)（边排序主导）
 * 空间复杂度：O(V + E)
 * 
 * 适用场景：
 *   - 求最小生成树（权值最小）
 *   - 稀疏图更优
 *   - 边权较小（容易排序）
 * 
 * 模板题：洛谷 P3366 - 【模板】最小生成树
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class DSU {
public:
    vector<int> parent;
    
    DSU(int n) : parent(n + 1) {
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        parent[x] = y;
        return true;
    }
};

struct Edge {
    ll w;
    int u, v;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    // 按权值排序
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    ll total = 0;
    int cnt = 0;
    
    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            cnt++;
            if (cnt == n - 1) break;  // 已加入 n-1 条边
        }
    }
    
    if (cnt == n - 1) {
        cout << total << "\n";
    } else {
        cout << "No MST\n";  // 无连通生成树
    }
    
    return 0;
}

/*
 * 【Kruskal 算法步骤】
 * 1. 将所有边按权值从小到大排序
 * 2. 依次考虑每条边：
 *    - 如果两端点不连通，加入这条边
 *    - 否则跳过（会形成环）
 * 3. 直到加入 n-1 条边（形成树）
 * 
 * 【为什么贪心有效？】
 * - 最小生成树的关键性质：
 *   "最小权值的边一定在某个 MST 中"
 * - 每次加入最小的未加入边，最终得到全局最优
 * 
 * 【与 Prim 的对比】
 * Kruskal:
 *   - 时间：O(E log E)
 *   - 空间：O(E)
 *   - 适合：稀疏图
 * Prim:
 *   - 时间：O((V + E) log V)（堆优化）
 *   - 空间：O(V)
 *   - 适合：稠密图
 * 
 * 【常见变体】
 * - 第 k 小生成树：需要特殊处理
 * - 带约束的 MST：限制某些边是否使用
 * - 最大生成树：改为降序排列
 * 
 * 【提交前检查】
 * - [ ] 并查集是否正确实现？
 * - [ ] 边是否按权值排序？
 * - [ ] 是否检查了连通性？
 * - [ ] 是否处理了重边和自环？
 * - [ ] 最终是否有 n-1 条边？
 */
