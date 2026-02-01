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

// --- 矩阵结构体定义 ---
struct Matrix {
    // 使用 vector 动态分配大小，防止 k > 2 时越界
    vector<vector<ll>> a;//定义二维全局数组
    int n, m; // n行 m列
    
    // 构造函数：初始化 n*m 的全 0 矩阵
    Matrix(int _n=2, int _m=2) : n(_n), m(_m) {
        a.assign(n, vector<ll>(m, 0));
    }
    
    // --- 核心：矩阵乘法重载 ---
    // 原理：C(i, j) = sum(A(i, k) * B(k, j))
    Matrix operator*(const Matrix &b) const {
        // 结果矩阵是 当前行数 x b的列数
        Matrix c(n, b.m);
        for (int i = 0; i < n; i++) {           // 枚举自己(左矩阵)的行
            for (int k = 0; k < m; k++) {       // 枚举中间维度(优化：放在中间层利用缓存亲和性)
                if (a[i][k] == 0) continue;     // 剪枝：如果乘数是0就不乘了
                for (int j = 0; j < b.m; j++) { // 枚举对方(右矩阵)的列
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
                }
            }
        }
        return c;
    }
};

// --- 核心：矩阵快速幂 ---
// 计算 Matrix a 的 b 次方
//编译器会自动调用上面那个重载的 operator*。 每一次矩阵相乘，生成的新矩阵的每一个元素都已经取过模了。
Matrix qpow(Matrix a, ll b) {
    // 1. 初始化结果为单位矩阵 I (对角线为1，其余为0)
    // 类似于数字乘法的 1，任何矩阵乘 I 等于它本身
    Matrix res(a.n, a.n);
    for (int i = 0; i < a.n; i++) res.a[i][i] = 1;
    
    // 2. 二进制拆分指数 b
    while (b > 0) {
        // 如果 b 的二进制最后一位是 1，则乘上当前的底数 a
        if (b & 1) res = res * a;
        // 底数倍增：a -> a^2 -> a^4 ...
        a = a * a;
        // 指数右移：处理下一位
        b >>= 1;
    }
    return res;
}

// --- 斐波那契数列求解 ---
ll fib(ll n) {
    if (n == 0) return 0;
    if (n == 1 || n == 2) return 1;
    
    // 构造转移矩阵 Base (2x2)
    // | 1 1 |
    // | 1 0 |
    Matrix base(2, 2);
    base.a[0][0] = 1; base.a[0][1] = 1;
    base.a[1][0] = 1; base.a[1][1] = 0;
    
    // 计算 Base^(n-2)
    // 为什么是 n-2？因为我们要从 [F2, F1] 推到 [Fn, Fn-1]
    // 实际上代码里 n-1 也是一种常见写法，取决于初始向量是 [F1, F0] 还是 [F2, F1]
    // 这里为了适配 F(1)=1, F(2)=1，我们算 base^(n-2) 乘初始向量 [1, 1]
    // 或者直接算 base^(n-1)，结果取 a[0][1] 或 a[1][0] 等，这里沿用你的逻辑修正：
    
    // 这种写法：qpow(base, n-1) * [1, 0]^T (F1=1, F0=0)
    Matrix res = qpow(base, n - 1);
    
    // F(n) 位于结果矩阵的 (0,0) 位置 * F(1) + (0,1) * F(0)
    // 因为 F(1)=1, F(0)=0，所以直接返回 res.a[0][0]
    return res.a[0][0]; 
}

// --- 通用线性递推求解 ---
// 求解 f(n) = c[0]*f(n-1) + c[1]*f(n-2) + ...
// init 是初始项 f(0), f(1), ..., f(k-1)
ll linearRecurrence(vector<ll> &c, vector<ll> &init, ll n) {
    int k = c.size(); // 阶数
    
    // 1. 如果 n 在前 k 项内，直接返回
    if (n < k) return init[n];
    
    // 2. 构造 k * k 的转移矩阵
    Matrix base(k, k);
    
    // 第一行：系数 c0, c1, ... ck-1
    for (int i = 0; i < k; i++) base.a[0][i] = c[i];
    
    // 下面的行：构造移位 (第 i 行的第 i-1 列为 1)
    // 作用是将 f(n-1) 移到 f(n-2) 的位置，f(n-2) 移到 f(n-3)...
    for (int i = 1; i < k; i++) base.a[i][i - 1] = 1;
    
    // 3. 矩阵快速幂：计算 base^(n - k + 1)
    // 为什么是 n - k + 1? 
    // 初始状态向量是 [f(k-1), f(k-2), ..., f(0)]^T
    // 乘一次矩阵得到 [f(k), f(k-1), ..., f(1)]^T
    // 我们需要求 f(n)，即目标向量的第一个元素
    Matrix res = qpow(base, n - k + 1);
    
    // 4. 结果 = 转移矩阵 * 初始列向量
    // Ans = res * [init[k-1], init[k-2], ..., init[0]]^T
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        // init[k - 1 - i] 对应的是 f(k-1), f(k-2)...
        ans = (ans + res.a[0][i] * init[k - 1 - i]) % MOD;
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    // 输入 n，比如求 F(6)
    if (cin >> n) {
        cout << "Fib(" << n << ") = " << fib(n) << "\n";
    }

    // --- 示例：运行通用线性递推 ---
    // 例子：f(n) = 1*f(n-1) + 1*f(n-2)，即斐波那契
    // 初值：f(0)=0, f(1)=1 (Codeforces 习惯从0开始)
    // vector<ll> c = {1, 1}; 
    // vector<ll> init = {0, 1};
    // cout << "Linear Fib(6) = " << linearRecurrence(c, init, 6) << endl;

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

/*
 * 运行示例（命令行输入输出）
 * -----------------------------------------------------------------
 * 示例 1：斐波那契
 * 输入：
 *   6
 * 输出：
 *   8
 * 解释：程序 main() 读取 n 并输出 fib(n)。F(6)=8（1,1,2,3,5,8）
 *
 * 示例 2：使用线性递推函数（手动调用说明）
 *  假设递推关系 f(n)=2*f(n-1)+3*f(n-2)，初值 f(0)=1, f(1)=2，求 f(5)
 *  - k=2，c={2,3}，init={1,2}
 *  - 手工计算（验证）：
 *      f(2)=2*2+3*1=7
 *      f(3)=2*7+3*2=20
 *      f(4)=2*20+3*7=61
 *      f(5)=2*61+3*20=202
 *  - 若要用本程序测试，请把 main 改为调用：
 *      vector<ll> c={2,3}; vector<ll> init={1,2}; cout<<linearRecurrence(c,init,5)<<"\n";
 *  - 输出应为 202（模 MOD 后若较大则取 MOD）
 *
 * 为什么矩阵方法成立（简要说明）
 * -----------------------------------------------------------------
 * 线性递推 f(n)=c1*f(n-1)+...+ck*f(n-k) 可以用状态向量表示：
 *   S(n) = [f(n), f(n-1), ..., f(n-k+1)]^T
 *  存在常数矩阵 M 使得 S(n) = M * S(n-1)。M 的第一行为系数 c1..ck，
 *  其余为单位移位以把 f(n-1) 推到第二分量，依此类推。
 *  因此 S(n) = M^(n-k+1) * S(k-1)，只需计算矩阵幂并与初始向量相乘。
 *
 * 当前代码注意事项与改进建议
 * 
 * -----------------------------------------------------------------
 * 1) 矩阵存储限制：当前 struct Matrix 使用固定成员 ll a[2][2]，但
 *    linearRecurrence 构造 k×k 矩阵时会访问 a[i][j]，若 k>2 会越界。
 *    解决方案（推荐）：将 Matrix 的存储改为动态分配，例如
 *      vector<vector<ll>> a;
 *    并在构造函数中按大小分配：a.assign(n, vector<ll>(m,0));
 *    同时修改乘法实现以支持任意 k。
 *
 * 2) 单位矩阵生成：qpow 中创建单位矩阵应根据 a.n 调整维度，
 *    而不是固定为 2×2。
 *
 * 3) 索引/初值约定：linearRecurrence 中对 init 的使用是 init[0..k-1]
 *    表示 f(0..k-1)。调用者应按该约定准备初值，或在函数注释中明确。
 *
 * 4) 模化与负数：若系数或初值可能为负数，请在取模时统一处理以
 *    保证结果非负（例如 (x%MOD+MOD)%MOD）。
 *
 * 小结：本文件已实现矩阵快速幂求 Fibonacci 和通用线性递推的
 * 基本逻辑，若要处理 k>2 的通用递推，需先修正 Matrix 的存储结构。
 */
