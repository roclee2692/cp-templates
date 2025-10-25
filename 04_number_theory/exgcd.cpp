/*
 * 【扩展欧几里得算法】- 求解 ax + by = gcd(a,b)
 * 
 * 时间复杂度：O(log min(a, b))
 * 空间复杂度：O(log min(a, b))（递归栈）
 * 
 * 适用场景：
 *   - 求解线性方程 ax + by = c
 *   - 计算模逆元（a*x ≡ 1 (mod m)）
 *   - 中国剩余定理
 *   - 贝祖定理应用
 * 
 * 模板题：
 *   - 洛谷 P1082 - 同余方程
 *   - Codeforces 1106F - Lunar New Year and a Recursive Sequence
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 扩展欧几里得算法
// 返回 gcd(a, b)，同时求出 x, y 满足 ax + by = gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    
    ll x1, y1;
    ll d = exgcd(b, a % b, x1, y1);
    
    // 由 bx1 + (a%b)y1 = d 推导出 ay + bx = d
    x = y1;
    y = x1 - a / b * y1;
    
    return d;
}

// 求解线性方程 ax + by = c
// 返回是否有整数解，若有返回一组特解 (x0, y0)
bool linearEquation(ll a, ll b, ll c, ll &x0, ll &y0) {
    ll x, y;
    ll d = exgcd(a, b, x, y);
    
    if (c % d != 0) return false;  // 无整数解
    
    // 扩大倍数
    x0 = x * (c / d);
    y0 = y * (c / d);
    
    return true;
}

// 计算模逆元 a*x ≡ 1 (mod m)
// 前提：gcd(a, m) = 1
ll modInverse(ll a, ll m) {
    ll x, y;
    ll d = exgcd(a, m, x, y);
    
    if (d != 1) return -1;  // 无逆元
    
    return (x % m + m) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll a, b;
    cin >> a >> b;
    
    ll x, y;
    exgcd(a, b, x, y);
    
    cout << (x % b + b) % b << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. exgcd 递归形式：b = 0 时 x = 1, y = 0
 * 2. 回溯公式：x = y1, y = x1 - (a/b)*y1
 * 3. 线性方程：c 必须是 gcd(a,b) 的倍数
 * 4. 模逆元：仅在 gcd(a,m) = 1 时存在
 * 5. 取模处理：(x % m + m) % m 防止负数
 * 
 * 【常见变体】
 * - 中国剩余定理（多个线性同余方程）
 * - 二次同余方程（Legendre符号）
 * - 求最小正整数解（通解参数化）
 * 
 * 【提交前检查】
 * ✓ gcd(a,b) 是否整除 c
 * ✓ 回溯公式是否正确
 * ✓ 模逆元的条件检查
 * ✓ 取模负数处理
 */
