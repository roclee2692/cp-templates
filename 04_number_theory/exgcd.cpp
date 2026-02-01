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
// 原理：
// 1. 递归基：当 b=0 时，ax + by = gcd(a,0) = a，显然 x=1, y=0 是解
// 2. 递归步：
//    假设我们已经求出了下一层递归的解 x1, y1，满足：
//    b * x1 + (a % b) * y1 = gcd(b, a % b) = d
//    
//    因为 a % b = a - (a / b) * b
//    代入上式：
//    b * x1 + (a - (a / b) * b) * y1 = d
//    b * x1 + a * y1 - (a / b) * b * y1 = d
//    a * y1 + b * (x1 - (a / b) * y1) = d
//    
//    对比原方程 a * x + b * y = d
//    得到递推公式：
//    x = y1
//    y = x1 - (a / b) * y1

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        // 当 b=0 时，gcd(a,0)=a。方程变为 a*x + 0*y = a
        // 显然 x=1, y=0 是一个特解
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
// 原理：贝祖定理
// ax + by = c 有解当且仅当 gcd(a, b) | c
// 我们先求出 ax + by = gcd(a, b) 的特解 (x, y)
// 然后两边同时乘以 c / gcd(a, b) 即可得到原方程的特解
bool linearEquation(ll a, ll b, ll c, ll &x0, ll &y0) {
    ll x, y;
    ll d = exgcd(a, b, x, y);
    
    if (c % d != 0) return false;  // 无整数解
    
    // 扩大倍数
    x0 = x * (c / d);
    y0 = y * (c / d);
    
    // 注意：通解公式为
    // x = x0 + k * (b / d)
    // y = y0 - k * (a / d)
    // 其中 k 为任意整数
    
    return true;
}

// 计算模逆元 a*x ≡ 1 (mod m)
// 【什么是逆元？】
// 定义：如果 a*x ≡ 1 (mod m)，则 x 称为 a 在模 m 下的乘法逆元。
// 类比：就像实数中的倒数 (a * 1/a = 1)，逆元就是模运算世界里的"倒数"。
// 用途：模运算中不能直接做除法，(a / b) % m 必须转化为 (a * inv(b)) % m 来计算。
//
// 前提：gcd(a, m) = 1 (只有当 a, m 互质时，逆元才存在)
// 原理详解：
// 1. 同余式定义：a*x ≡ 1 (mod m) 意味着 a*x 除以 m 的余数是 1
// 2. 转化为等式：这意味着 a*x - 1 是 m 的倍数
// 3. 引入整数 k：即存在整数 k 使得 a*x - 1 = m * k
// 4. 移项整理：a*x - m*k = 1
// 5. 令 y = -k：得到 ax + my = 1
// 所以求模逆元 x，等价于求不定方程 ax + my = 1 的整数解 x
// 只有当 gcd(a, m) = 1 时才有解
ll modInverse(ll a, ll m) {
    ll x, y;
    ll d = exgcd(a, m, x, y);
    
    if (d != 1) return -1;  // 无逆元
    
    // 得到的 x 可能是负数，需要转为正数
    // (x % m + m) % m 是通用的防负数取模写法
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
