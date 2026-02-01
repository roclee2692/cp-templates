/*
 * 【Catalan 数列】- 组合计数中的经典数列
 * 
 * 时间复杂度：O(n) 递推，O(1) 查表
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 合法括号序列
 *   - 二叉搜索树计数
 *   - 出栈序列
 *   - 凸多边形三角剖分
 * 
 * 模板题：
 *   - 洛谷 P1044 - 栈（出栈序列）
 *   - Codeforces 9D - How many trees?
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 5;
const ll MOD = 1e9 + 7;//must prime

ll catalan[MAXN];  // catalan[n] = 第 n 个 Catalan 数
ll fac[MAXN];      // 阶乘
ll inv[MAXN];      // 逆元

// ===== 快速幂 =====
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// ===== 方法 1：递推公式（最快）=====
// 公式：C(n) = C(n-1) * (4n - 2) / (n + 1)
// 为什么这个公式成立？从通项公式推导而来
// 时间复杂度：O(n)
void init_catalan_recurrence(int n) {
    catalan[0] = 1;
    catalan[1] = 1;
    
    // ===== 递推公式 =====
    // C(n) = C(n-1) * (4n - 2) / (n + 1)
    // 
    // 推导：
    // C(n) = C(2n, n) / (n+1)
    // C(n) / C(n-1) = [C(2n, n) / (n+1)] / [C(2n-2, n-1) / n]
    //               = [C(2n, n) / C(2n-2, n-1)] * [n / (n+1)]
    //               = [(2n)! / (n! * n!)] / [(2n-2)! / ((n-1)! * (n-1)!)] * [n / (n+1)]
    //               = [(2n) * (2n-1)] / [n * n] * [n / (n+1)]
    //               = (4n - 2) / (n + 1)
    for (int i = 2; i <= n; i++) {
        // Step 1: Multiply by (4i - 2)
        // catalan[i] = catalan[i-1] * (4i - 2) / (i + 1)
        // We compute the multiplication first with modulo
        catalan[i] = catalan[i - 1] * (4 * i - 2) % MOD;
        
        // Step 2: Divide by (i + 1) using modular inverse
        // 【为什么用 qpow(i + 1, MOD - 2, MOD)?】
        // 
        // 问题：在模运算中，我们不能直接除以 (i+1)
        // 解决：用"乘以逆元"来代替"除法"
        //
        // 【什么是模逆元 (modular inverse)?】
        // 数字 a 在模 p 下的逆元是一个数 a_inv，满足：
        //     (a * a_inv) ≡ 1 (mod p)
        //     意思是：a 乘以 a_inv 除以 p 的余数是 1
        // 
        // 所以：除以 a 等价于 乘以 a_inv
        //     x / a ≡ x * a_inv (mod p)
        //
        // 【如何计算模逆元？】
        // 使用费马小定理 (Fermat's Little Theorem)：当 p 是质数时
        //     a^(p-1) ≡ 1 (mod p)          （费马小定理）
        //     两边同时除以 a：
        //     a^(p-2) * a ≡ 1 (mod p)
        // 因此：a^(p-2) 就是 a 的模逆元！
        //
        // 【这行代码的含义：】
        // - 我们想要：catalan[i] = catalan[i] / (i+1) mod MOD
        // - 实际计算：catalan[i] = catalan[i] * (i+1)^(MOD-2) mod MOD
        // - qpow(i+1, MOD-2, MOD) 计算 (i+1) 的 (MOD-2) 次方，结果对 MOD 取模
        // - 这个结果就是 (i+1) 的模逆元
        //
        // 【具体例子：】
        // 假设 MOD = 7，i = 2，我们要除以 3
        // 
        // 步骤1：求 3 的逆元
        //   3^(7-2) mod 7 = 3^5 mod 7 = 243 mod 7 = 5
        // 
        // 步骤2：验证 3 * 5 ≡ 1 (mod 7)
        //   3 * 5 = 15 = 7 * 2 + 1，所以 15 mod 7 = 1 ✓
        // 
        // 步骤3：用逆元替代除法
        //   如果我们要算 20 / 3 (mod 7)：
        //   直接除：20 / 3 = 6.666...（不是整数，无法取模）
        //   用逆元：20 * 5 = 100，100 mod 7 = 2
        //   
        //   验证：20 / 3 = 6.666..., 6 mod 7 = 6（错误的理解）
        //   正确理解：我们找的是 x 使得 3x ≡ 20 (mod 7)
        //            3x ≡ 20 ≡ 6 (mod 7)
        //            x ≡ 6 * 5 ≡ 30 ≡ 2 (mod 7) ✓
        //
        // 【为什么模数要是质数？】
        // 费马小定理只对质数成立，所以 MOD 必须是质数（如 1e9+7）
        // 如果 MOD 不是质数，需要用扩展欧几里得算法求逆元
        catalan[i] = catalan[i] * qpow(i + 1, MOD - 2, MOD) % MOD;
    }
}

// ===== 方法 2：通项公式 =====
// 公式：C(n) = C(2n, n) / (n + 1) = C(2n, n) - C(2n, n+1)
// 为什么？这是 Catalan 数的定义
// 时间复杂度：O(n) 预处理，O(1) 查询
void init_catalan_formula(int n) {
    // ===== 预处理阶乘和逆元 =====
    fac[0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    
    inv[2 * n] = qpow(fac[2 * n], MOD - 2, MOD);
    for (int i = 2 * n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
    
    // ===== 通项公式计算 =====
    // C(n) = C(2n, n) / (n + 1)
    //      = (2n)! / (n! * n!) / (n + 1)
    //      = (2n)! / (n! * n! * (n + 1))
    for (int i = 0; i <= n; i++) {
        ll C_2n_n = fac[2 * i] * inv[i] % MOD * inv[i] % MOD;
        catalan[i] = C_2n_n * qpow(i + 1, MOD - 2, MOD) % MOD;
    }
}

// ===== 方法 3：DP 递推（理解 Catalan 数的本质）=====
// 公式：C(n) = Σ C(i) * C(n-1-i)，i = 0..n-1
// 这个公式揭示了 Catalan 数的组合意义
void init_catalan_dp(int n) {
    catalan[0] = 1;
    
    // ===== DP 递推 =====
    // C(n) 表示 n 对括号的合法序列数
    // 枚举第一对括号包含的子序列长度 i
    // 左边有 i 对，右边有 n-1-i 对
    // 
    // 例如：n = 3
    // ()()()  - 第一对包含 0 对：C(0) * C(2) = 1 * 2 = 2
    // (())()  - 第一对包含 1 对：C(1) * C(1) = 1 * 1 = 1
    // (()())  - 第一对包含 2 对：C(2) * C(0) = 2 * 1 = 2
    // C(3) = 2 + 1 + 2 = 5
    for (int i = 1; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] = (catalan[i] + catalan[j] * catalan[i - 1 - j]) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    // ===== 三种方法任选其一 =====
    init_catalan_recurrence(n);  // 推荐：最快
    // init_catalan_formula(n);
    // init_catalan_dp(n);
    
    cout << catalan[n] << "\n";
    
    return 0;
}

/*
 * ========== Catalan 数核心原理 ==========
 * 
 * 【什么是 Catalan 数？】
 * 定义：第 n 个 Catalan 数 C(n) = C(2n, n) / (n + 1)
 * 
 * 前几项：1, 1, 2, 5, 14, 42, 132, 429, ...
 * 
 * 通项公式：C(n) = (2n)! / ((n+1)! * n!)
 * 递推公式：C(n) = C(n-1) * (4n - 2) / (n + 1)
 * DP 公式：C(n) = Σ C(i) * C(n-1-i)，i = 0..n-1
 * 
 * 【Catalan 数的经典应用】
 * 
 * 1. **合法括号序列**
 *    - 问题：n 对括号的合法序列有多少种？
 *    - 答案：C(n)
 *    - 例子：n=3 时，有 5 种：()()(), ()(()), (())(), (()()), ((()))
 * 
 * 2. **出栈序列**
 *    - 问题：n 个元素依次入栈，有多少种出栈序列？
 *    - 答案：C(n)
 *    - 理解：入栈 = '('，出栈 = ')'，合法序列 = 出栈序列
 * 
 * 3. **二叉搜索树**
 *    - 问题：n 个节点的 BST 有多少种形态？
 *    - 答案：C(n)
 *    - 理解：枚举根节点，左子树 i 个节点，右子树 n-1-i 个
 * 
 * 4. **凸多边形三角剖分**
 *    - 问题：n+2 边形有多少种三角剖分方式？
 *    - 答案：C(n)
 *    - 理解：选一条边，枚举与它构成三角形的顶点
 * 
 * 5. **路径计数**
 *    - 问题：(0,0) 到 (n,n) 不越过对角线的路径数？
 *    - 答案：C(n)
 *    - 理解：右 = '('，上 = ')'，不越过对角线 = 合法括号
 * 
 * 6. **不相交弦**
 *    - 问题：圆上 2n 个点，两两连线不相交的方案数？
 *    - 答案：C(n)
 * 
 * 【为什么是 C(2n, n) / (n+1)？】
 * 证明（反射原理）：
 * 
 * 1. 从 (0,0) 到 (n,n) 的所有路径：C(2n, n)
 * 2. 越过对角线的路径：必经过 (0,1) 或 (1,0) 上方
 * 3. 这些路径可以一一对应到 (0,0) 到 (n-1, n+1) 的路径
 * 4. 不越过对角线的路径 = C(2n, n) - C(2n, n+1)
 *                      = C(2n, n) * [1 - n/(n+1)]
 *                      = C(2n, n) / (n+1)
 * 
 * 【递推公式的理解】
 * C(n) = Σ C(i) * C(n-1-i)
 * 
 * 括号序列解释：
 * - 第一对括号 "( ... )"
 * - 括号内有 i 对（左边）
 * - 括号外有 n-1-i 对（右边）
 * - 枚举 i = 0..n-1，相加得 C(n)
 * 
 * 【三种计算方法对比】
 * 
 * | 方法 | 优点 | 缺点 | 推荐度 |
 * |------|-----|------|--------|
 * | 递推公式 | 最快 O(n) | 需要逆元 | ⭐⭐⭐⭐⭐ |
 * | 通项公式 | 单个查询快 | 预处理慢 | ⭐⭐⭐⭐ |
 * | DP | 容易理解 | 慢 O(n²) | ⭐⭐⭐ |
 * 
 * 【常见题型】
 * 1. 直接套公式：合法括号数、BST 数
 * 2. 转化问题：识别出是 Catalan 数
 * 3. 变体：加限制条件（如高度限制）
 * 4. 生成函数：求和、求积
 * 
 * 【识别 Catalan 数的技巧】
 * 特征：
 * - 涉及配对、嵌套、树形结构
 * - "合法"、"不相交"、"不越过"等关键词
 * - 递推关系形如 f(n) = Σ f(i) * f(n-1-i)
 * 
 * 【常见错误】
 * 1. 下标从 0 还是 1 开始（Catalan 从 0 开始）
 * 2. 递推公式写错（4n-2 还是 4n-1）
 * 3. 逆元计算错误
 * 4. 溢出（用 ll，取模）
 * 5. 预处理范围不够
 * 
 * 【扩展知识】
 * 1. **Super-Catalan 数**：更复杂的计数问题
 * 2. **Ballot 问题**：Catalan 数的推广
 * 3. **Motzkin 数**：类似 Catalan，但多一种选择
 * 
 * 【公式总结】
 * C(0) = 1
 * C(n) = C(n-1) * (4n - 2) / (n + 1)
 * C(n) = C(2n, n) / (n + 1)
 * C(n) = Σ C(i) * C(n-1-i)，i = 0..n-1
 * 
 * 【生成函数】
 * G(x) = Σ C(n) * x^n = (1 - sqrt(1 - 4x)) / (2x)
 * 
 * 【提交前检查】
 * ✓ 下标从 0 开始
 * ✓ 递推公式正确
 * ✓ 逆元用快速幂
 * ✓ 预处理范围足够
 * ✓ 取模防溢出
 * 
 * 【竞赛考察频率】
 * - NOI/省选：⭐⭐⭐⭐（组合数学常考）
 * - ICPC/CCPC：⭐⭐⭐（区域赛偶尔）
 * - Codeforces：⭐⭐（Div2 D/E）
 * 
 * 【推荐练习】
 * 1. 洛谷 P1044 - 栈（出栈序列）
 * 2. HDU 1131 - Count the Trees（BST 计数）
 * 3. Codeforces 9D - How many trees?
 */
