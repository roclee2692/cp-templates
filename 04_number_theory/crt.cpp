/*
 * 【中国剩余定理 CRT】- 求解同余方程组
 * 
 * 时间复杂度：O(k log m)，k = 方程个数，m = 模数最大值
 * 空间复杂度：O(k)
 * 
 * 适用场景：
 *   - 求解 x ≡ a_i (mod m_i) 的同余方程组
 *   - 前提：所有 m_i 两两互质
 *   - 扩展 CRT：m_i 不互质时
 * 
 * 模板题：
 *   - 洛谷 P1495 - 【模板】中国剩余定理(CRT)/曾经沧海
 *   - Codeforces 1106F - Lunar New Year and a Recursive Sequence
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll d = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return d;
}

// 中国剩余定理（互质版本）
// a[i] 为余数，m[i] 为模数（两两互质）
// 返回解 x 和大模数 M
pair<ll, ll> crt(vector<ll> &a, vector<ll> &m) {
    int n = a.size();
    ll M = 1, ans = 0;
    
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }
    
    for (int i = 0; i < n; i++) {
        ll Mi = M / m[i];
        ll x, y;
        exgcd(Mi, m[i], x, y);
        x = (x % m[i] + m[i]) % m[i];
        ans = (ans + a[i] * Mi % M * x % M) % M;
    }
    
    return {ans, M};
}

// 扩展中国剩余定理（非互质版本）
// 合并两个同余方程
pair<ll, ll> extgcd_merge(ll a1, ll m1, ll a2, ll m2) {
    ll x, y;
    ll d = exgcd(m1, m2, x, y);
    
    if ((a2 - a1) % d != 0) {
        return {-1, -1};  // 无解
    }
    
    ll lcm = m1 / d * m2;
    ll a = (a1 + m1 * x % lcm * ((a2 - a1) / d) % lcm) % lcm;
    a = (a + lcm) % lcm;
    
    return {a, lcm};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<ll> a(n), m(n);
    for (int i = 0; i < n; i++) {
        cin >> m[i] >> a[i];
    }
    
    auto [ans, M] = crt(a, m);
    
    cout << ans << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. 互质 CRT：M = ∏m_i, 答案 = Σ(a_i * M_i * (M_i^-1 mod m_i))
 * 2. M_i = M / m_i，需要计算其在 m_i 下的逆元
 * 3. 非互质 CRT：用扩展欧几里得逐两个合并
 * 4. 无解条件：(a2 - a1) % gcd(m1, m2) ≠ 0
 * 5. 合并后 lcm = m1 * m2 / gcd(m1, m2)
 * 
 * 【常见变体】
 * - 求最小正整数解
 * - 区间内的解计数
 * - 多个非互质方程逐个合并
 * 
 * 【提交前检查】
 * ✓ 互质性检查（或使用扩展版本）
 * ✓ 模逆元计算正确性
 * ✓ 取模防止溢出
 * ✓ 无解条件判断
 */
