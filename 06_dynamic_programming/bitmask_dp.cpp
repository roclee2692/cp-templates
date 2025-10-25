/*
 * 【位运算 DP】- 状态压缩动态规划
 * 
 * 时间复杂度：O(n * 2^n * m) 通常
 * 空间复杂度：O(2^n)
 * 
 * 适用场景：
 *   - 小范围集合状态（n ≤ 20）
 *   - 旅行商问题（TSP）
 *   - 棋盘状态压缩
 *   - 子集枚举
 * 
 * 模板题：
 *   - 洛谷 P1097 - 统计数字
 *   - Codeforces 10D - LCIS
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // dp[mask] 表示状态 mask 下的答案
    vector<ll> dp(1 << n, 0);
    dp[0] = 1;  // 空状态初值
    
    // 示例：计算所有子集
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == 0) continue;
        
        // 枚举 mask 的所有超集
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0) {  // i 未被选中
                int new_mask = mask | (1 << i);
                dp[new_mask] += dp[mask];
            }
        }
    }
    
    // 另一种枚举方式：枚举子集
    for (int mask = 1; mask < (1 << n); mask++) {
        // 枚举 mask 的所有子集（更高效）
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            // 处理子集 sub
        }
    }
    
    // 位操作技巧
    auto popcount = [](int x) { return __builtin_popcount(x); };
    
    auto count_bit = [](int x, int k) { return (x >> k) & 1; };
    
    auto set_bit = [](int x, int k) { return x | (1 << k); };
    
    auto unset_bit = [](int x, int k) { return x & ~(1 << k); };
    
    auto toggle_bit = [](int x, int k) { return x ^ (1 << k); };
    
    return 0;
}

/*
 * 【关键点】
 * 1. 状态范围：2^n（必须 n ≤ 20 左右）
 * 2. 状态转移：通常通过添加/移除元素
 * 3. 子集枚举：for (int sub = mask; sub > 0; sub = (sub-1) & mask)
 * 4. 时间复杂度：O(3^n) 枚举所有子集对
 * 5. 位操作：count, set, unset, toggle
 * 
 * 【常见变体】
 * - TSP（旅行商）：dp[mask][i] = 访问 mask 集合且在 i 的最小路径
 * - 棋盘覆盖：按行转移状态
 * - 子集 DP：计算所有子集的某个性质
 * 
 * 【提交前检查】
 * ✓ 状态定义清晰
 * ✓ 子集枚举公式正确
 * ✓ 初值设置
 * ✓ 转移逻辑
 */
