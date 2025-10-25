/*
 * 【树形 DP】- 树上的动态规划
 * 
 * 时间复杂度：O(n) 通常
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 树上路径问题
 *   - 树的计数问题
 *   - 树的匹配问题
 *   - 树的着色问题
 * 
 * 模板题：
 *   - 洛谷 P1352 - 没有上司的舞会
 *   - Codeforces 1106D - Lunar New Year and a Recursive Sequence
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
ll dp[MAXN][2];  // dp[u][0/1] 表示 u 不选/选择时的答案
ll value[MAXN];
int n;

void dfs(int u, int p) {
    dp[u][0] = 0;  // u 不选
    dp[u][1] = value[u];  // u 选
    
    for (int v : adj[u]) {
        if (v == p) continue;
        
        dfs(v, u);
        
        // 如果 u 不选，v 可选可不选
        dp[u][0] += max(dp[v][0], dp[v][1]);
        
        // 如果 u 选，v 不能选
        dp[u][1] += dp[v][0];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, -1);
    
    cout << max(dp[1][0], dp[1][1]) << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. dp[u][0/1]：u 不选/选时的最优值
 * 2. dfs 遍历：从任意根出发（这里从 1）
 * 3. 转移关键：当前节点的选择影响子节点的选择
 * 4. 亲子关系：通过参数 p 避免往父亲方向回溯
 * 5. 合并子树：逐个加入子树的贡献
 * 
 * 【常见变体】
 * - 树上路径：dp[u][d] = 经过 u 且向下距离为 d 的最长路径
 * - 树的匹配：dp[u] = u 的子树中的最大匹配
 * - 树的着色：dp[u][c] = u 着色为 c 时的方案数
 * 
 * 【提交前检查】
 * ✓ 状态定义是否清晰
 * ✓ dfs 遍历是否覆盖所有节点
 * ✓ 转移是否考虑所有情况
 * ✓ 亲子关系处理（避免重复访问）
 */
