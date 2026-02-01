/*
 * 【树链剖分 HLD】- 树上路径查询与修改
 * 
 * 时间复杂度：O(n) 预处理，O(log² n) 单次查询/修改
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 树上路径求和/最值
 *   - 树上路径修改
 *   - 树上 LCA 查询
 *   - 子树查询修改
 * 
 * 模板题：
 *   - 洛谷 P3384 - 【模板】树链剖分
 *   - Codeforces 343D - Water Tree
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;

// ===== 树链剖分核心数据 =====
vector<int> adj[MAXN];      // 邻接表存储树
int n, m, root;

// ===== 第一次 DFS 的数据 =====
int fa[MAXN];       // fa[u] = u 的父节点
int dep[MAXN];      // dep[u] = u 的深度（根节点深度为 1）
int siz[MAXN];      // siz[u] = 以 u 为根的子树大小
int son[MAXN];      // son[u] = u 的重儿子（子树最大的儿子）
                    // 为什么需要重儿子？用于构建重链，减少链的数量

// ===== 第二次 DFS 的数据 =====
int top[MAXN];      // top[u] = u 所在重链的顶端节点
                    // 为什么需要 top？查询路径时，每次跳到链顶，最多跳 O(log n) 次
int dfn[MAXN];      // dfn[u] = u 的 DFS 序（时间戳）
                    // 为什么需要 DFS 序？把树映射到线段树上，重链在 DFS 序上连续
int rnk[MAXN];      // rnk[i] = DFS 序为 i 的节点编号（dfn 的逆映射）
int cnt_dfn;        // DFS 序计数器

ll a[MAXN];         // 节点权值
ll w[MAXN];         // w[dfn[u]] = a[u]（按 DFS 序重排的权值）

// ===== 线段树维护 DFS 序上的区间 =====
struct SegmentTree {
    ll tree[MAXN * 4];   // 区间和
    ll lazy[MAXN * 4];   // 懒标记（区间加）
    
    void push_up(int u) {
        tree[u] = tree[u * 2] + tree[u * 2 + 1];
    }
    
    void push_down(int u, int len) {
        if (!lazy[u]) return;
        lazy[u * 2] += lazy[u];
        lazy[u * 2 + 1] += lazy[u];
        tree[u * 2] += lazy[u] * (len / 2);
        tree[u * 2 + 1] += lazy[u] * (len - len / 2);
        lazy[u] = 0;
    }
    
    void build(int u, int l, int r) {
        if (l == r) {
            tree[u] = w[l];  // 用 DFS 序上的权值建树
            return;
        }
        int mid = (l + r) / 2;
        build(u * 2, l, mid);
        build(u * 2 + 1, mid + 1, r);
        push_up(u);
    }
    
    void update(int u, int l, int r, int ql, int qr, ll val) {
        if (ql <= l && r <= qr) {
            lazy[u] += val;
            tree[u] += val * (r - l + 1);
            return;
        }
        push_down(u, r - l + 1);
        int mid = (l + r) / 2;
        if (ql <= mid) update(u * 2, l, mid, ql, qr, val);
        if (qr > mid) update(u * 2 + 1, mid + 1, r, ql, qr, val);
        push_up(u);
    }
    
    ll query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[u];
        push_down(u, r - l + 1);
        int mid = (l + r) / 2;
        ll res = 0;
        if (ql <= mid) res += query(u * 2, l, mid, ql, qr);
        if (qr > mid) res += query(u * 2 + 1, mid + 1, r, ql, qr);
        return res;
    }
} seg;

// ===== 第一次 DFS：计算 fa, dep, siz, son =====
// 为什么需要两次 DFS？第一次确定树的结构，第二次构建重链
void dfs1(int u, int f, int d) {
    fa[u] = f;
    dep[u] = d;
    siz[u] = 1;
    son[u] = 0;  // 初始化无重儿子
    
    int max_siz = 0;
    for (int v : adj[u]) {
        if (v == f) continue;  // 跳过父节点
        dfs1(v, u, d + 1);
        siz[u] += siz[v];
        
        // ===== 找重儿子：子树最大的儿子 =====
        // 为什么选最大的？因为重链越长，跳链次数越少
        if (siz[v] > max_siz) {
            max_siz = siz[v];
            son[u] = v;
        }
    }
}

// ===== 第二次 DFS：构建重链，计算 top, dfn =====
// 参数 t 表示当前重链的顶端节点
void dfs2(int u, int t) {
    top[u] = t;               // 记录所在重链的顶端
    dfn[u] = ++cnt_dfn;       // 分配 DFS 序
    rnk[cnt_dfn] = u;         // 记录逆映射
    w[cnt_dfn] = a[u];        // 按 DFS 序重排权值
    
    if (!son[u]) return;      // 叶子节点，无需继续
    
    // ===== 优先遍历重儿子 =====
    // 为什么先遍历重儿子？保证重链在 DFS 序上连续
    dfs2(son[u], t);  // 重儿子继承链顶 t（在同一条重链上）
    
    // ===== 再遍历轻儿子 =====
    for (int v : adj[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);   // 轻儿子开启新的重链，链顶是自己
    }
}

// ===== 路径查询：u 到 v 的路径和 =====
// 核心思想：让 u 和 v 不断跳到各自重链的链顶，直到它们在同一条重链上
ll query_path(int u, int v) {
    ll res = 0;
    
    // ===== 循环：将 u 和 v 跳到同一条重链上 =====
    while (top[u] != top[v]) {
        // ===== 谁的链顶深度大，谁先跳 =====
        // 为什么？保证最终在 LCA 附近相遇
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        
        // u 跳到链顶
        // 查询 [dfn[top[u]], dfn[u]] 这段 DFS 序的和
        // 为什么 DFS 序连续？因为重链在 DFS 序上是连续的
        res += seg.query(1, 1, n, dfn[top[u]], dfn[u]);
        
        // u 跳到链顶的父节点（进入上一条重链）
        u = fa[top[u]];
    }
    
    // ===== 现在 u 和 v 在同一条重链上 =====
    // 保证 u 在 v 上方（深度更小）
    if (dep[u] > dep[v]) swap(u, v);
    
    // 查询 [dfn[u], dfn[v]] 的和
    res += seg.query(1, 1, n, dfn[u], dfn[v]);
    return res;
}

// ===== 路径修改：u 到 v 的路径都加上 val =====
void update_path(int u, int v, ll val) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        seg.update(1, 1, n, dfn[top[u]], dfn[u], val);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    seg.update(1, 1, n, dfn[u], dfn[v], val);
}

// ===== 子树查询：以 u 为根的子树和 =====
// 为什么简单？因为子树在 DFS 序上是连续区间 [dfn[u], dfn[u] + siz[u] - 1]
ll query_subtree(int u) {
    return seg.query(1, 1, n, dfn[u], dfn[u] + siz[u] - 1);
}

// ===== 子树修改 =====
void update_subtree(int u, ll val) {
    seg.update(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int mod;
    cin >> n >> m >> root >> mod;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ===== 树链剖分预处理 =====
    dfs1(root, 0, 1);  // 第一次 DFS
    dfs2(root, root);  // 第二次 DFS
    seg.build(1, 1, n); // 建线段树
    
    // ===== 处理操作 =====
    while (m--) {
        int op;
        cin >> op;
        
        if (op == 1) {
            // 路径加
            int x, y;
            ll z;
            cin >> x >> y >> z;
            update_path(x, y, z);
        } else if (op == 2) {
            // 路径查询
            int x, y;
            cin >> x >> y;
            cout << query_path(x, y) % mod << "\n";
        } else if (op == 3) {
            // 子树加
            int x;
            ll z;
            cin >> x >> z;
            update_subtree(x, z);
        } else {
            // 子树查询
            int x;
            cin >> x;
            cout << query_subtree(x) % mod << "\n";
        }
    }
    
    return 0;
}

/*
 * ========== 树链剖分核心原理 ==========
 * 
 * 【什么是树链剖分？】
 * - 把树分成若干条"重链"（Heavy Path），使得任意路径最多跨越 O(log n) 条重链
 * - 重链在 DFS 序上连续，可以用线段树高效维护
 * 
 * 【核心思想】
 * 1. 重儿子：子树最大的儿子
 * 2. 重链：由重儿子连成的路径
 * 3. DFS 序：先遍历重儿子，保证重链连续
 * 4. 跳链：查询路径时，不断跳到链顶，最多跳 O(log n) 次
 * 
 * 【为什么复杂度是 O(log² n)？】
 * - 跳链次数：O(log n)（每次至少跳过一半的节点）
 * - 单次线段树操作：O(log n)
 * - 总复杂度：O(log n) × O(log n) = O(log² n)
 * 
 * 【为什么需要两次 DFS？】
 * - 第一次 DFS：计算子树大小，找出重儿子
 * - 第二次 DFS：构建重链，分配 DFS 序
 * 
 * 【为什么 DFS 序很重要？】
 * - 重链在 DFS 序上是连续区间，可以用线段树维护
 * - 子树也在 DFS 序上是连续区间 [dfn[u], dfn[u] + siz[u] - 1]
 * 
 * 【树链剖分 vs LCA】
 * - LCA：只能查询祖先关系，O(log n)
 * - 树链剖分：可以查询/修改路径，O(log² n)
 * 
 * 【常见应用】
 * 1. 树上路径和/最值（配合线段树）
 * 2. 树上路径修改（区间加、区间赋值）
 * 3. 树上 LCA（副产品，比倍增慢但更灵活）
 * 4. 树上差分（路径加 + 前缀和）
 * 
 * 【常见错误】
 * 1. 第二次 DFS 时，没有先遍历重儿子（重链不连续）
 * 2. 跳链时，没有判断 dep[top[u]] 谁大（可能跳过 LCA）
 * 3. 子树操作时，区间写错（应该是 [dfn[u], dfn[u] + siz[u] - 1]）
 * 4. 忘记取模（题目要求取模）
 * 
 * 【提交前检查】
 * ✓ dfs2 先遍历重儿子
 * ✓ 跳链时判断深度
 * ✓ 子树区间计算正确
 * ✓ 线段树 build 时用 w[] 而不是 a[]
 * ✓ 取模操作（如果需要）
 * 
 * 【优化技巧】
 * 1. 用数组代替 vector（常数优化）
 * 2. 线段树用非递归版本（更快）
 * 3. 如果只查询不修改，可以用树状数组代替线段树
 * 
 * 【竞赛考察频率】
 * - NOI/省选：⭐⭐⭐⭐⭐（必会！）
 * - ICPC/CCPC：⭐⭐⭐⭐（区域赛常考）
 * - Codeforces：⭐⭐⭐（Div1 D/E）
 */
