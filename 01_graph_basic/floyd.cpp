/*
 * 【Floyd 算法】- 多源最短路径
 * 
 * 时间复杂度：O(n^3)
 * 空间复杂度：O(n^2)
 * 
 * 适用场景：
 *   - 多源最短路径（任意两点之间）
 *   - 边权可以为负（但不含负环）
 *   - n 较小（通常 n <= 500）
 *   - 求传递闭包
 * 
 * 模板题：洛谷 P1119 - 灾后重建
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;

ll dist[505][505];
int n, m;

void floyd() {
    // k 是中间节点
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    // 初始化
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }
    
    // 读入边
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);  // 处理重边
    }
    
    floyd();
    
    // 输出结果
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == INF) {
                cout << -1;  // 无通路
            } else {
                cout << dist[i][j];
            }
            if (j < n) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. 三重循环：k 在最外层（选择中间节点）
 *    - 错误：i, k, j 的顺序会导致结果错误
 *    - 正确：k 必须在最外层
 * 2. 初始化：dist[i][i] = 0，不同节点为 INF
 * 3. 处理重边：dist[u][v] = min(dist[u][v], w)
 * 4. 检查 INF：防止溢出
 * 
 * 【Floyd 循环的意义】
 * - 第一层 k=1：找只通过节点 1 的最短路
 * - 第二层 k=2：找通过节点 1 或 2 的最短路
 * - ...
 * - 第 n 层 k=n：找通过任意节点的最短路（答案）
 * 
 * 【常见变体】
 * - 记录路径：用 next[i][j] 记录 i->j 的下一个节点
 * - 求传递闭包：dist[i][j] = true/false（是否有通路）
 * - 求连通块：多次 Floyd + 并查集
 * 
 * 【性能考虑】
 * - 对于 n > 500，考虑用 Dijkstra 多次或其他算法
 * - 时间复杂度 O(n^3) 在 n=500 时约 1.25 亿次操作
 * 
 * 【提交前检查】
 * - [ ] k 循环是否在最外层？
 * - [ ] 初始化是否正确？
 * - [ ] 是否处理了重边？
 * - [ ] INF 值是否合理？
 * - [ ] n 是否超过 500？(是则可能超时)
 */
