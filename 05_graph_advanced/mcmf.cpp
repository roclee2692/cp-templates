/*
 * 【最小费用最大流 MCMF】- 在最大流基础上优化费用
 * 
 * 时间复杂度：O(n * m * f)，f 为最大流
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 最小费用流问题
 *   - 二分图最优匹配
 *   - 任务分配优化
 *   - 物流运输成本
 * 
 * 模板题：
 *   - 洛谷 P3381 - 【模板】最小费用最大流
 *   - Codeforces 362E - Petya and Pipes
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;
const int MAXM = 1e5 + 5;
const ll INF = 1e18;

// ===== MCMF 核心数据结构 =====
struct Edge {
    int to;      // 终点
    ll cap;      // 容量
    ll cost;     // 单位流量的费用
    int rev;     // 反向边的位置
};

vector<Edge> adj[MAXN];
int n, m, s, t;
ll dis[MAXN];      // dis[i] = 从源点到 i 的最短费用
int pre_v[MAXN];   // pre_v[i] = 最短路中 i 的前驱节点
int pre_e[MAXN];   // pre_e[i] = 最短路中到达 i 的边的编号
bool inq[MAXN];    // SPFA 中是否在队列中

// ===== 添加边 =====
// 同时添加正向边和反向边
// 反向边的费用是负的（用于退流时退回费用）
void add_edge(int from, int to, ll cap, ll cost) {
    // 正向边：from → to，容量 cap，费用 cost
    adj[from].push_back({to, cap, cost, (int)adj[to].size()});
    
    // 反向边：to → from，容量 0，费用 -cost
    // 为什么费用是负的？退流时要退回之前的费用
    adj[to].push_back({from, 0, -cost, (int)adj[from].size() - 1});
}

// ===== SPFA 寻找最短费用的增广路 =====
// 返回：是否存在增广路
// 核心：找从 s 到 t 的最小费用路径（允许有负权边，但不能有负环）
bool spfa() {
    fill(dis, dis + n + 1, INF);
    fill(inq, inq + n + 1, false);
    
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    inq[s] = true;
    
    // ===== SPFA 算法 =====
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        
        for (int i = 0; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            
            // 只考虑还有容量的边
            if (e.cap > 0 && dis[e.to] > dis[u] + e.cost) {
                dis[e.to] = dis[u] + e.cost;
                pre_v[e.to] = u;
                pre_e[e.to] = i;
                
                if (!inq[e.to]) {
                    q.push(e.to);
                    inq[e.to] = true;
                }
            }
        }
    }
    
    // 返回是否能到达汇点
    return dis[t] != INF;
}

// ===== 最小费用最大流主函数 =====
// 返回：{最大流，最小费用}
// 核心思想：每次找最小费用的增广路，直到没有增广路
pair<ll, ll> mcmf() {
    ll max_flow = 0, min_cost = 0;
    
    // ===== 主循环：不断找最小费用增广路 =====
    while (spfa()) {
        // ===== 找瓶颈容量（增广路上的最小容量）=====
        ll flow = INF;
        for (int v = t; v != s; v = pre_v[v]) {
            flow = min(flow, adj[pre_v[v]][pre_e[v]].cap);
        }
        
        // ===== 更新流量和费用 =====
        max_flow += flow;
        min_cost += flow * dis[t];
        
        // ===== 更新边的容量 =====
        for (int v = t; v != s; v = pre_v[v]) {
            Edge &e = adj[pre_v[v]][pre_e[v]];
            e.cap -= flow;                      // 正向边减少容量
            adj[v][e.rev].cap += flow;          // 反向边增加容量
        }
    }
    
    return {max_flow, min_cost};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> s >> t;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll cap, cost;
        cin >> u >> v >> cap >> cost;
        add_edge(u, v, cap, cost);
    }
    
    auto [flow, cost] = mcmf();
    cout << flow << " " << cost << "\n";
    
    return 0;
}

/*
 * ========== MCMF 核心原理 ==========
 * 
 * 【什么是最小费用最大流？】
 * - 在最大流的基础上，每条边有单位费用
 * - 目标：在流量最大的前提下，总费用最小
 * - 应用：物流、任务分配、二分图最优匹配
 * 
 * 【MCMF vs 最大流】
 * | 算法 | 目标 | 边属性 | 复杂度 |
 * |------|------|--------|--------|
 * | Dinic | 最大流 | 容量 | O(n²m) |
 * | MCMF | 最小费用最大流 | 容量+费用 | O(nmf) |
 * 
 * 【核心思想】
 * 1. 每次找最小费用的增广路（SPFA 最短路）
 * 2. 沿着这条路增广
 * 3. 重复直到没有增广路
 * 
 * 【为什么用 SPFA 而不是 Dijkstra？】
 * - 反向边的费用是负的，可能有负权边
 * - SPFA 可以处理负权边（但不能有负环）
 * - 如果保证没有负权边，可以用 Dijkstra（更快）
 * 
 * 【为什么反向边的费用是负的？】
 * 退流时要退回之前的费用：
 * - 正向边：流量 f，费用 f * cost
 * - 退流：减少正向边流量 f，相当于增加反向边流量 f
 * - 费用变化：-f * cost = f * (-cost)
 * 
 * 【复杂度分析】
 * - 单次 SPFA：O(nm)
 * - 增广次数：最多 f 次（f 为最大流）
 * - 总复杂度：O(nmf)
 * 
 * 实际表现：
 * - 如果流量小，很快
 * - 如果流量大，会很慢（可以用 Dinic + 费用流）
 * 
 * 【经典应用】
 * 
 * 1. **二分图最大权匹配**
 *    - 边权取负，转化为最小费用流
 *    - 最大权 = -最小费用
 * 
 * 2. **任务分配问题**
 *    - n 个人，m 个任务
 *    - 每个人做每个任务有费用
 *    - 求最小费用分配方案
 * 
 * 3. **物流运输**
 *    - 多个仓库、多个客户
 *    - 运输有成本
 *    - 求最小成本满足需求
 * 
 * 4. **K 短路**
 *    - 转化为最小费用流
 *    - 流量 = K，费用 = 路径长度
 * 
 * 【建图技巧】
 * 
 * 1. **拆点**
 *    - 点有容量限制：拆成两个点，中间连边（容量 = 限制）
 * 
 * 2. **多源多汇**
 *    - 超级源点连所有源点（容量 = 供应量，费用 = 0）
 *    - 所有汇点连超级汇点（容量 = 需求量，费用 = 0）
 * 
 * 3. **费用转化**
 *    - 最大权 → 最小费用：边权取负
 *    - 必须经过：设置高费用强制选择
 * 
 * 【常见变体】
 * 
 * 1. **最大费用最大流**
 *    - 所有边的费用取负
 *    - 答案再取负
 * 
 * 2. **固定流量的最小费用**
 *    - 限制最大流 ≤ K
 *    - 在 SPFA 中判断流量
 * 
 * 3. **上下界费用流**
 *    - 每条边流量 [L, R]
 *    - 转化为无下界问题
 * 
 * 【优化技巧】
 * 
 * 1. **势函数优化（Johnson 算法）**
 *    - 消除负权边，用 Dijkstra 代替 SPFA
 *    - 时间复杂度优化到 O(f * m * log n)
 * 
 * 2. **zkw 费用流**
 *    - 原始对偶算法
 *    - 实践中非常快
 * 
 * 3. **Dinic + 费用流**
 *    - 先用 Dinic 找最大流
 *    - 再优化费用
 * 
 * 【常见错误】
 * 1. 反向边费用忘记取负
 * 2. SPFA 忘记判断 cap > 0
 * 3. 增广时忘记更新反向边
 * 4. pre_v 和 pre_e 没有正确记录
 * 5. 费用溢出（用 ll）
 * 
 * 【调试技巧】
 * 1. 检查费用是否正确（打印每次增广的费用）
 * 2. 验证流量守恒
 * 3. 检查反向边费用是否为负
 * 4. 小数据手模增广过程
 * 
 * 【提交前检查】
 * ✓ 反向边费用为负
 * ✓ SPFA 判断 cap > 0
 * ✓ pre_v 和 pre_e 正确记录
 * ✓ 费用和流量用 ll
 * ✓ 数组大小足够
 * ✓ 源点和汇点不搞反
 * 
 * 【MCMF vs 其他算法】
 * 
 * | 问题 | 算法 | 复杂度 |
 * |------|------|--------|
 * | 二分图最大匹配 | 匈牙利 | O(nm) |
 * | 二分图最大权匹配 | KM | O(n³) |
 * | 二分图最大权匹配 | MCMF | O(nmf) |
 * | 任务分配 | 贪心 | O(n log n) |
 * | 任务分配（带约束）| MCMF | O(nmf) |
 * 
 * 【竞赛考察频率】
 * - NOI/省选：⭐⭐⭐⭐（网络流专题）
 * - ICPC/CCPC：⭐⭐⭐（区域赛及以上）
 * - Codeforces：⭐⭐（Div1 E/F）
 * 
 * 【推荐练习】
 * 1. 洛谷 P3381 - 最小费用最大流模板
 * 2. 洛谷 P4014 - 分配问题
 * 3. HDU 1533 - Going Home
 * 4. POJ 2195 - Going Home
 */

/*这段代码实现的是 **最小费用最大流 (Min-Cost Max-Flow, MCMF)** 算法。

这也是一个经典的模板，用一句话概括它的核心思想就是：**在保证能流过去的前提下，每次都挑最便宜的那条路走，直到没路可走。**

它和 Dinic 的区别在于：

* **Dinic (最大流)**：只在乎“快”，每次 BFS 按距离分层，只走“短”路。
* **MCMF (费用流)**：在乎“钱”，每次 SPFA 按费用找路，只走“便宜”的路。

这段代码使用的是 **基于 SPFA 的 EK (Edmonds-Karp) 增广路算法**。你可以把它看作是“魔改版”的 EK 算法。

---

### 1. 结构体与建边 (`Edge` & `add_edge`)

```cpp
struct Edge{
    int to;
    ll cap;  // 容量
    ll cost; // 单价（流过 1 单位流量花的钱）
    int rev; // 反向边索引
};

void add_edge(int from,int to,ll cap,ll cost){
    // 正向边：容量 cap，费用 cost
    adj[from].push_back({to,cap,cost,(int)adj[to].size()});
    // 反向边：容量 0，费用 -cost 【关键！】
    adj[to].push_back({from,0,-cost,(int)adj[from].size()-1});
}

```

**用人话讲：**

* **正向边**：你去买东西，花钱（`cost` 是正的）。
* **反向边**：你后悔了，退货，商家要把钱退给你（`cost` 是负的）。
* 这就是为什么要 `-cost`。当我们“退流”（走反向边）时，不仅要把流量拿回来，还要把之前算的费用减掉。

---

### 2. 寻路导航 (`spfa`)

这是核心中的核心。在 Dinic 里这里是 BFS，但在费用流里，这里变成了 **SPFA**（或者 Bellman-Ford）。

**为什么不用 Dijkstra？**
因为图里有 **负权边**（反向边的费用是负的）。Dijkstra 处理不了负权边，所以只能用 SPFA。

```cpp
bool spfa(){
    // ... 初始化距离为无穷大 ...
    // ... 标准 SPFA 模板 ...
    while(!q.empty()){
        int u=q.front(); q.pop(); inq[u]=0;
        for(int i=0;i<adj[u].size();i++){
            Edge &e=adj[u][i];
            // 只有还有剩余容量(cap>0)的路才能走
            // 松弛操作：如果你这里的花费比已知的更便宜，就更新
            if(e.cap>0 && dis[e.to]>dis[u]+e.cost){
                dis[e.to]=dis[u]+e.cost;
                // 【记录路径】你是从哪个点(u)、哪条边(i)走过来的？
                pre_v[e.to]=u;
                pre_e[e.to]=i;
                if(!inq[e.to]){ ... }
            }
        }
    }
    // 如果 dis[t] 还是无穷大，说明走不到汇点 t 了，结束
    return dis[t]!=INF;
}

```

**用人话讲：**

* **任务**：在残量网络里，找到一条从  到  的路径。
* **要求**：这条路径的总费用（`cost` 之和）必须是所有可行路径里 **最小的**。
* **面包屑导航**：`pre_v` 和 `pre_e` 就像在森林里撒面包屑。因为 SPFA 只是找路，它跑完之后，我们需要顺着面包屑从  倒着找回 ，才能知道刚才到底走了哪条路。

---

### 3. 总指挥 (`mcmf`)

有了导航找到的最便宜路径，现在开始运货。

```cpp
pair<ll,ll> mcmf(){
    ll max_flow=0,min_cost=0;
    // 只要导航还能找到路（能流过去），就一直循环
    while(spfa()){
        ll flow=INF;
        // 第一步：回溯路径，算出这条路上的瓶颈（最小容量）
        for(int v=t;v!=s;v=pre_v[v]){
            flow=min(flow,adj[pre_v[v]][pre_e[v]].cap);
        }
        
        // 第二步：累加流量和费用
        max_flow+=flow;
        min_cost+=flow*dis[t]; // 费用 = 流量 * 单价和
        
        // 第三步：真正扣除容量（正向减，反向加）
        for(int v=t;v!=s;v=pre_v[v]){
            Edge &e=adj[pre_v[v]][pre_e[v]]; // 找到正向边
            e.cap-=flow;                     // 正向容量减少
            adj[v][e.rev].cap+=flow;         // 反向容量增加（给后悔留后路）
        }
    }
    return {max_flow,min_cost};
}

```

**用人话讲：**
这是一个“贪心”的过程：

1. **问导航**：“现在去终点最便宜的路是哪条？”
2. **导航说**：“走 A->C->D->T，单价是 5 块。”
3. **计算瓶颈**：检查这条路上最细的水管能流多少水（假设是 10 吨）。
4. **发货**：运送 10 吨水。总费用增加  块。
5. **更新地图**：把这条路上的容量扣掉。如果某段路满了，下次导航就不会再选它了（或者只能走反向边退流）。
6. **重复**：回到第 1 步，直到导航说“没路了”。

---

### 总结与对比

你可能会问：**“这代码和 Dinic 怎么不像呢？没有 DFS 呀？”**

是的，这是两种不同的流派：

1. **Dinic 写法（多路增广）**：
* BFS 分层。
* DFS 一次性找**很多条**路把这层填满。
* **优点**：对于最大流问题，非常快。
* **缺点**：在费用流里，为了保证“最便宜”，DFS 不能乱跑，必须严格沿着最短路跑，实现起来比较麻烦（叫 ZKW 费用流）。


2. **EK-SPFA 写法（单路增广，就是你这段代码）**：
* SPFA 找**一条**最便宜的路。
* `mcmf` 函数沿着这条路推流。
* 然后再找下一条。
* **优点**：代码简单，逻辑清晰（找一条路 -> 推流 -> 再找一条）。
* **缺点**：理论复杂度比 Dinic 高，但在费用流问题中，因为每次只找一条路，通常跑得也不慢，完全够用。



**一句话总结这段代码：**
这是一个**基于 SPFA 寻找最短路（最小费用路）的单路增广算法**。它不做多路同时增广，而是“一次只做一单生意”，每单生意都挑当前最赚（费用最低）的做。*/