/*
 * 【快速幂】- 高效计算 a^b mod m
 * 
 * 时间复杂度：O(log b)
 * 空间复杂度：O(1)
 * 
 * 适用场景：
 *   - 大指数幂模运算
 *   - 模幂计算（密码学）
 *   - 任何形如 a^b mod m 的问题
 * 
 * 模板题：
 *   - Codeforces 50A - Dominoes
 *   - 洛谷 P1226 - 【模板】快速幂||取余运算
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 基础版本
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 处理负数版本
ll qpow_neg(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    if (a < 0) a += mod;
    
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 快速乘（防止溢出）
ll qmul(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

// 快速乘版本的快速幂
ll qpow_mul(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = qmul(res, a, mod);
        a = qmul(a, a, mod);
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll a, b, mod;
    cin >> a >> b >> mod;
    
    cout << qpow(a, b, mod) << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. 二进制表示：b 的每一位对应 a 的某个幂次
 * 2. 每次循环：a 自乘（a^1, a^2, a^4, ...）
 * 3. b & 1 判断：取当前二进制位
 * 4. 模运算：保持结果在范围内
 * 5. 负数处理：模运算后可能为负
 * 
 * 【常见变体】
 * - __int128 快速乘：处理超大数相乘
 * - 费马小定理：快速计算模逆元
 * - 矩阵快速幂：线性递推加速
 * 
 * 【提交前检查】
 * ✓ 模运算是否在每一步进行
 * ✓ 初值 res = 1
 * ✓ 避免整数溢出（使用 __int128 或快速乘）
 * ✓ 负数情况处理
 */
