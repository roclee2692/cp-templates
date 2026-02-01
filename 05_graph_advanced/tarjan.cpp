/*
 * 【Tarjan 算法】- 求强连通分量（SCC）
 *   /ˈtɑr.jɑn/ "塔-扬"（第一个音重，第二个音轻）
 * 时间复杂度：O(n + m)
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 求强连通分量
 *   - 缩点成 DAG
 *   - 2-SAT 问题
 * 
 * 模板题：
 *   - 洛谷 P3387 - 【模板】缩点
 *   - Codeforces 1109D - Sasha and His Friend
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int n, m;
vector<int> adj[MAXN];    // 邻接表
int dfn[MAXN], low[MAXN]; // dfn: 时间戳, low: 能到达的最小时间戳
bool in_stk[MAXN];         // 是否在栈中
int stk[MAXN], top;        // 手写栈
int timestamp;             // 时间戳计数器
int scc_cnt;               // SCC 个数
int scc_id[MAXN];          // 每个点属于哪个 SCC

// Tarjan DFS
void tarjan(int u) {
    // 【初始化】给 u 分配时间戳
    // dfn[u]: 记录 u 第一次被访问的时间
    // low[u]: 初始化为 dfn[u]，后续可能被更新为更小的值
    dfn[u] = low[u] = ++timestamp;
    
    // 【入栈】u 加入栈中，表示 u 正在被处理
    // 栈中存储的是当前 DFS 路径上的所有节点
    stk[++top] = u;
    in_stk[u] = true;
    
    // 【遍历所有出边】检查 u 的每一条出边 u -> v
    for (int v : adj[u]) {
        if (!dfn[v]) {
            // 【情况1：树边】v 还没被访问过
            // 说明 v 是 u 的后代节点，这是 DFS 树上的一条树边
            tarjan(v);  // 递归访问 v 的子树
            
            // 【回溯更新】v 的子树处理完毕，用 low[v] 更新 low[u]
            // 如果 v 的子树能回溯到更早的节点，那么 u 也能通过 v 回溯到那个节点
            low[u] = min(low[u], low[v]);
            
        } else if (in_stk[v]) {
            // 【情况2：回边】v 已被访问且还在栈中
            // 说明 v 是 u 的祖先节点（在 DFS 树上）
            // 这是一条回边，连接了 u 到它的祖先 v
            // 
            // 【为什么用 dfn[v] 而不是 low[v]？】
            // 因为 v 在栈中，可能还在被处理，low[v] 可能还会变
            // 我们只需要知道能回溯到 v 这个点即可，所以用 dfn[v]
            low[u] = min(low[u], dfn[v]);
        }
        // 【情况3：横叉边】v 已访问但不在栈中 → 什么都不做
        // v 所在的 SCC 已经处理完并弹栈了
        // u 到 v 只是单向可达，不构成强连通
        // 所以不更新 low[u]（这条边对当前 SCC 没有影响）
    }
    
    // u 是 SCC 的根
    // 【为什么 dfn[u] == low[u] 说明 u 是 SCC 根？】
    // low[u] 表示 u 能回溯到的最早节点的时间戳
    // 如果 low[u] == dfn[u]，说明 u 无法回溯到比自己更早的节点
    // 即：u 及其子树中的所有节点都无法到达 u 之前访问的节点
    // 因此 u 就是一个 SCC 的"入口点"（根节点）
    if (dfn[u] == low[u]) {
        scc_cnt++;  // 发现一个新的 SCC
        
        // 【弹栈：从栈顶弹出所有属于这个 SCC 的节点】
        // 栈中从 u 到栈顶的所有节点都属于同一个 SCC
        // 
        // 【为什么这些节点属于同一个 SCC？】
        // 1. 这些节点都是在访问 u 之后才入栈的（时间戳 > dfn[u]）
        // 2. 它们都无法回溯到 u 之前的节点（否则 low[u] 会更小）
        // 3. 它们之间相互可达（通过 DFS 树上的路径）
        // 4. u 是它们的"最早公共祖先"
        //
        // 【弹栈过程】
        // do-while 保证至少弹出 u 自己
        // 从栈顶开始弹，直到弹出 u 为止
        int v;
        do {
            v = stk[top--];        // 弹出栈顶节点
            in_stk[v] = false;     // 标记 v 不再在栈中
            scc_id[v] = scc_cnt;   // 给 v 分配 SCC 编号
        } while (v != u);  // 直到弹出 u（SCC 的根）
        
        // 【示例】假设栈中有 [1, 2, 3, 4]，u = 2
        // 第1次循环：v = 4，弹出 4，scc_id[4] = scc_cnt
        // 第2次循环：v = 3，弹出 3，scc_id[3] = scc_cnt
        // 第3次循环：v = 2，弹出 2，scc_id[2] = scc_cnt，v == u，结束
        // 结果：节点 2, 3, 4 属于同一个 SCC，节点 1 留在栈中
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    // 【建图】读入所有有向边
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // 添加有向边 u -> v
    }
    
    // 【执行 Tarjan】对所有未访问的点执行 Tarjan
    // 为什么要遍历所有点？因为图可能不连通，有多个连通分量
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {  // dfn[i] == 0 表示 i 还没被访问过
            tarjan(i);
        }
    }
    
    // 【输出结果】
    cout << "SCC 个数: " << scc_cnt << "\n";
    
    for (int i = 1; i <= n; i++) {
        cout << "节点 " << i << " 属于 SCC " << scc_id[i] << "\n";
    }
    
    return 0;
}

/*
 * 【核心思想】
 * dfn[u]: u 第一次被访问的时间
 * low[u]: u 能够回溯到的最早的栈中节点的时间
 * 
 * 如果 dfn[u] == low[u]，说明 u 无法回溯到更早的节点，u 是 SCC 的根
 * 
 * 【三种边】
 * 1. 树边：v 未访问 → 递归访问，用 low[v] 更新 low[u]
 * 2. 回边：v 在栈中 → v 是祖先，用 dfn[v] 更新 low[u]
 * 3. 横叉边：v 已访问但不在栈中 → v 在另一个 SCC，不更新
 * 
 * 【为什么会有横叉边？什么时候产生？】
 * 
 * 情况：当 u -> v 但 v 已经被访问过且不在栈中
 * 
 * 原因：v 所在的 SCC 已经被完全处理完毕并弹栈了
 * 
 * 【具体例子】
 * 图结构：1 -> 2 -> 3 -> 4
 *              ↓         ↓
 *              5         1
 *              ↓
 *              6
 * 
 * DFS 顺序：1 -> 2 -> 3 -> 4 -> (回到 1，发现 SCC{1,2,3,4})
 *          弹栈后 in_stk[1,2,3,4] = false
 *          继续 -> 5 -> 6
 *          此时如果有边 6 -> 3，则 6 -> 3 是横叉边
 *          因为 3 已访问(dfn[3] != 0) 且不在栈中(in_stk[3] = false)
 * 
 * 【为什么横叉边不更新 low？】
 * 因为 v 已经在另一个 SCC 中了，u 不可能通过这条边回到 v 所在的 SCC
 * （强连通的定义：互相可达。u 可以到 v，但 v 不能回到 u）
 * 
 * 所以：横叉边指向的是已经确定的、与当前节点不在同一个 SCC 的节点
 * 
 * 【为什么回边用 dfn[v] 而不是 low[v]？】
 * 因为 v 在栈中，v 的 low 可能还会被后续更新
 * 我们要的是 v 本身的时间戳，不是 v 子树能到达的最小时间戳
 */
