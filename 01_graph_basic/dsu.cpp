/*
 * 【并查集 (DSU)】- 路径压缩 + 按秩合并
 * 
 * 时间复杂度：O(n α(n)) ≈ O(n)（其中 α 是反阿克曼函数，极小)
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 判断连通性
 *   - 动态连接问题
 *   - 最小生成树（Kruskal）
 *   - 图的连通分量
 * 
 * 模板题：洛谷 P3367 - 【模板】并查集
 */

#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, rank;
    
    DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    // 找根节点（路径压缩）
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }
    
    // 合并两个集合（按秩合并）
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        
        if (x == y) return false;  // 已在同一集合
        
        // 按秩合并：小树挂到大树下
        if (rank[x] < rank[y]) {
            parent[x] = y;
        } else if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[y] = x;
            rank[x]++;
        }
        
        return true;
    }
    
    // 判断是否在同一集合
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    DSU dsu(n);
    
    for (int i = 0; i < m; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        
        if (op == 1) {
            dsu.unite(x, y);
        } else {
            if (dsu.same(x, y)) {
                cout << "Y\n";
            } else {
                cout << "N\n";
            }
        }
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. 路径压缩（find 函数）：
 *    parent[x] = find(parent[x])
 *    - 每次查询时，直接指向根节点
 *    - 大幅减少树的高度
 * 
 * 2. 按秩合并（unite 函数）：
 *    - 始终将小树挂到大树下
 *    - 维持树的平衡，减少高度
 * 
 * 3. 两个优化的组合：
 *    - 单独路径压缩：O(n log n)
 *    - 单独按秩合并：O(n log n)
 *    - 两者结合：O(n α(n)) ≈ O(n)
 * 
 * 【常见变体】
 * - 不使用类：直接用数组 + 函数
 * - 加权并查集：记录每个节点到根的距离
 * - 撤销并查集：支持撤销操作（用栈）
 * 
 * 【复杂版本：带权并查集】
 * - 用于需要计算节点间距离/重量的问题
 * - 通常在图论题中与其他算法结合
 * 
 * 【提交前检查】
 * - [ ] 初始化是否正确？
 * - [ ] find() 是否进行了路径压缩？
 * - [ ] unite() 是否进行了按秩合并？
 * - [ ] 是否处理了 0 索引或 1 索引？
 */
