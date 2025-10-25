/*
 * 【矩阵快速幂 DP】- 线性递推加速
 * 
 * 时间复杂度：O(k^3 * log n)，k = 递推阶数
 * 空间复杂度：O(k^2)
 * 
 * 适用场景：
 *   - 线性递推数列求第 n 项
 *   - 斐波那契数列
 *   - 任意线性递推关系
 * 
 * 模板题：
 *   - 洛谷 P1962 - 斐波那契数列
 *   - Codeforces 1106F - Lunar New Year and a Recursive Sequence
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

struct Matrix {
    ll a[2][2];
    int n, m;
    
    Matrix(int _n = 2, int _m = 2) : n(_n), m(_m) {
        memset(a, 0, sizeof(a));
    }
    
    Matrix operator*(const Matrix &b) const {
        Matrix c(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int k = 0; k < m; k++) {
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
                }
            }
        }
        return c;
    }
};

Matrix qpow(Matrix a, ll b) {
    Matrix res(2, 2);
    res.a[0][0] = res.a[1][1] = 1;  // 单位矩阵
    
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

// 求斐波那契数列 F(n)
// F(n) = F(n-1) + F(n-2)
// 矩阵形式：[F(n+1), F(n)]^T = [[1,1],[1,0]] * [F(n), F(n-1)]^T
ll fib(ll n) {
    if (n == 1 || n == 2) return 1;
    
    Matrix base(2, 2);
    base.a[0][0] = 1; base.a[0][1] = 1;
    base.a[1][0] = 1; base.a[1][1] = 0;
    
    Matrix res = qpow(base, n - 1);
    
    return res.a[0][0];  // F(n) = [[1,1],[1,0]]^(n-1)[0][0]
}

// 通用线性递推求解
// f(n) = c1*f(n-1) + c2*f(n-2) + ... + ck*f(n-k)
ll linearRecurrence(vector<ll> &c, vector<ll> &init, ll n) {
    int k = c.size();  // 递推阶数
    
    if (n < init.size()) return init[n];
    
    Matrix base(k, k);
    // 第一行放系数（按倒序）
    for (int i = 0; i < k; i++) {
        base.a[0][i] = c[i];
    }
    // 其余行构造移位矩阵
    for (int i = 1; i < k; i++) {
        base.a[i][i - 1] = 1;
    }
    
    Matrix res = qpow(base, n - k + 1);
    
    // 结果是 res * init 的第一个分量
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        ans = (ans + res.a[0][i] * init[k - 1 - i]) % MOD;
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;
    
    cout << fib(n) << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. 递推式转矩阵：识别线性递推关系
 * 2. 矩阵构造：系数作为第一行，下面是移位矩阵
 * 3. 矩阵乘法：注意模运算，防止溢出
 * 4. 快速幂：指数 b 从 n-k+1
 * 5. 初值设置：前 k 项的初值
 * 
 * 【常见变体】
 * - 二阶递推：F(n) = a*F(n-1) + b*F(n-2)
 * - 更高阶递推：类似扩展矩阵大小
 * - 模运算加法递推
 * 
 * 【提交前检查】
 * ✓ 矩阵乘法是否正确
 * ✓ 快速幂逻辑
 * ✓ 初值个数是否正确
 * ✓ 模运算防溢出（使用 long long）
 */
