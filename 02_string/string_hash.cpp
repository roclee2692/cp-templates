/*
 * 【字符串哈希】- 快速比较字符串相等性
 * 
 * 时间复杂度：O(n) 预处理 + O(1) 查询
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 快速判断两个子串是否相等（不用直接比较）
 *   - 字符串去重
 *   - 回文检测（正向哈希 vs 反向哈希）
 * 
 * 模板题：
 *   - Codeforces 835F - Roads and Ramen
 *   - 洛谷 P3370 - 字符串哈希
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;
const ll BASE = 31;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = s.size();
    
    // 预计算 BASE 的幂次
    vector<ll> pow(n + 1);
    pow[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow[i] = (pow[i - 1] * BASE) % MOD;
    }
    
    // 计算前缀哈希
    vector<ll> hash(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] * BASE + (s[i - 1] - 'a' + 1)) % MOD;
    }
    
    // 查询 [l, r] 子串的哈希值（1-indexed）
    auto getHash = [&](int l, int r) -> ll {
        ll res = (hash[r] - hash[l - 1] * pow[r - l + 1]) % MOD;
        return (res + MOD) % MOD;
    };
    
    // 示例：找出所有重复的子串
    set<ll> seen;
    int len = 3;  // 子串长度
    for (int i = 1; i + len - 1 <= n; i++) {
        ll h = getHash(i, i + len - 1);
        if (seen.count(h)) {
            cout << "Found duplicate substring at positions " << i << "\n";
        }
        seen.insert(h);
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. BASE 选择：31 或 37（质数）
 * 2. MOD 选择：1e9+7 或 double hash（两个MOD避免冲突）
 * 3. getHash 公式：hash[r] - hash[l-1] * BASE^(r-l+1)
 * 4. 字符映射：s[i] - 'a' + 1（避免0字符影响）
 * 
 * 【常见变体】
 * - 双哈希：防止哈希碰撞（小概率但存在）
 * - 回文检测：反向字符串哈希对比
 * - 多模式匹配：配合KMP或AC自动机
 * 
 * 【提交前检查】
 * ✓ MOD 和 BASE 是否设置
 * ✓ pow 数组是否预计算
 * ✓ getHash 公式是否正确
 * ✓ 是否考虑模运算的负数
 */
