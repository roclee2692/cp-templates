/*
 * 【差分约束系统】- 线性不等式组求解
 * 
 * 原理：转化为单源最短路问题
 * 时间复杂度：O(V*E)（SPFA/Bellman-Ford 实现）
 * 空间复杂度：O(V+E)
 * 
 * 适用场景：
 *   - 求解一组形如 xᵢ - xⱼ ≤ cₖ 的不等式
 *   - 判断不等式组是否存在解（通过检测负环）
 * 
 * 模板题：洛谷 P5960 - 【模板】差分约束算法
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = (ll)1e18;
struct Edge { ll u, v; ll w; };
ll n, m;
vector<Edge> edges;
vector<ll> distDif;
// 解差分约束：判断是否可行，并求最小 x[i]
bool SDC(){
     // 节点编号假设为 1..n，加入超源 0
    distDif.assign(n+1, INF);
    distDif[0] = 0;
    // 构造超源边 0->i (权 0)
    vector<Edge> es = edges;
    for (int i = 1; i <= n; ++i)
        es.push_back({0, i, 0});
          // Bellman–Ford 松弛 n 轮
    for (int i = 0; i < n; ++i) {
        bool updated = false;
        for (auto &e : es) {
            if (distDif[e.u] != INF && distDif[e.u] + e.w < distDif[e.v]) {
                distDif[e.v] = distDif[e.u] + e.w;
                updated = true;
            }
        }
        if (!updated) break;
    }
    // 第 n 轮检测负环
    for (auto &e : es) {
        if (distDif[e.u] != INF && distDif[e.u] + e.w < distDif[e.v])
            return false;
    }
    return true;
}

int main(){
ios::sync_with_stdio(0);cin.tie(0);
    
    // 输入：变量个数 n，不等式条数 m
    cin >> n >> m;
    edges.clear();
    edges.reserve(m);
    // 每条约束 u,v,w 表示 x[v] - x[u] <= w
    for (int i = 0; i < m; ++i) {
        int u, v; ll w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
     bool ok = SDC();
      if (!ok) {
        cout << "NO\n";  // 存在冲突（负环）
    } else {
        cout << "YES\n";
        // 若需输出最小解 x[1..n]：
        // for (int i = 1; i <= n; ++i) cout << distDif[i] << ' ';
        // cout << "\n";
    }
  return 0;
}
/*
 * 【约束转化规则】
 * 原约束形式          转化为图的边
 * ─────────────────────────────────────
 * xᵢ - xⱼ ≤ c      j → i, 权重 c
 * xᵢ ≥ xⱼ + c      j → i, 权重 c（同上）
 * xᵢ - xⱼ ≥ c      i → j, 权重 -c
 * xᵢ = xⱼ          双向：j <--(0)--> i
 * 
 * 【求解步骤】
 * 1. 建立图：每个不等式转化为一条有向边。
 * 2. 添加超级源点 S (通常是0)，向所有变量节点连权重为0的边。
 * 3. 从源点 S 运行 SPFA 或 Bellman-Ford 求单源最短路。
 * 4. 若存在负环，则系统无解。
 * 5. 否则，dist[i] 就是变量 xᵢ 的一组可行解（通常是满足约束的最小/最大值边界）。
 * 
 * 【注意事项】
 * - [ ] 约束转化方向和权重正负要正确。
 * - [ ] 必须添加超级源点以保证图的连通性，处理所有变量。
 * - [ ] 负环判断是关键，SPFA通过入队次数，Bellman-Ford通过第n轮松弛。
 * - [ ] 如果求最大值，需要将所有不等式反向，求最长路（等价于边权取反求最短路）。
 */