/*
 * 【素数筛与质因数分解】- 快速找质数与质因数
 * 
 * 时间复杂度：O(n log log n) 埃筛 / O(n log n) 线性筛
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 打表质数表
 *   - 质因数分解
 *   - 欧拉函数计算
 *   - 莫比乌斯函数计算
 * 
 * 模板题：
 *   - 洛谷 P3383 - 【模板】线性筛素数
 *   - Codeforces 1295E - Permutation Sort
 */

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int MAXN = 1e7 + 5;

// 埃拉托斯特尼筛法（简单版）
vector<int> eratosthenes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

// 线性筛（更快）
// 【核心思想】每个合数只被它的最小质因子筛一次
//
// 【手动模拟：筛到 n=15 的过程】
//
// 初始：is_prime[] 全为 true，primes = []
//
// i=2: is_prime[2]=true → 2是质数，primes=[2]
//      遍历 primes=[2]:
//        p=2: i*p=4, 4%2=0 → 筛掉4，然后break（因为2是2的最小质因子）
//      结果：筛掉[4]
//
// i=3: is_prime[3]=true → 3是质数，primes=[2,3]
//      遍历 primes=[2,3]:
//        p=2: i*p=6, 3%2≠0 → 筛掉6，继续
//        p=3: i*p=9, 3%3=0 → 筛掉9，然后break（因为3是3的最小质因子）
//      结果：筛掉[6,9]
//
// i=4: is_prime[4]=false → 4是合数，不加入primes，primes=[2,3]
//      遍历 primes=[2,3]:
//        p=2: i*p=8, 4%2=0 → 筛掉8，然后break（因为2是4的最小质因子）
//        （不继续尝试p=3，避免重复筛12）
//      结果：筛掉[8]
//      【关键】12=4*3没被筛，因为12的最小质因子是2（不是3）
//               12会在i=6时由6*2筛掉
//
// i=5: is_prime[5]=true → 5是质数，primes=[2,3,5]
//      遍历 primes=[2,3,5]:
//        p=2: i*p=10, 5%2≠0 → 筛掉10，继续
//        p=3: i*p=15, 5%3≠0 → 筛掉15，继续
//        p=5: i*p=25>15 → break（超出范围）
//      结果：筛掉[10,15]
//
// i=6: is_prime[6]=false → 6是合数，primes=[2,3,5]
//      遍历 primes=[2,3,5]:
//        p=2: i*p=12, 6%2=0 → 筛掉12，然后break
//        （不继续尝试p=3和p=5）
//      结果：筛掉[12]
//      【重要】18=6*3 和 30=6*5 没被筛，因为它们的最小质因子是2（不是3/5）
//               18会在i=9时由9*2筛掉，30会在i=15时由15*2筛掉
//
// i=7: is_prime[7]=true → 7是质数，primes=[2,3,5,7]
//      遍历 primes=[2,3,5,7]:
//        p=2: i*p=14, 7%2≠0 → 筛掉14，继续
//        p=3: i*p=21>15 → break
//      结果：筛掉[14]
//
// 【为什么 i%p==0 时要break？】
// 如果 p 是 i 的最小质因子（即 i%p==0），那么：
// - i*p 的最小质因子是 p ✓ 这个要筛
// - i*q (q>p的质数) 的最小质因子也是 p（不是q）✗ 这个不能现在筛
//   因为会在 i'=(i/p)*q 时被筛掉，那时 p 才不整除 i'
//
// 例如 i=6, p=2:
// - 6*2=12 的最小质因子是2 ✓ 现在筛
// - 6*3=18 的最小质因子是2（不是3）✗ 应该在 i=9 时由 9*2 筛
// - 6*5=30 的最小质因子是2（不是5）✗ 应该在 i=15 时由 15*2 筛
//
// 【为什么是线性O(n)？】
// 每个合数 m 只被筛一次：当 i = m/minPrime(m) 且 p = minPrime(m) 时
// 例如 12 = 2×2×3：
// - 不在 i=4,p=3 时筛（因为4%2==0会break）
// - 不在 i=3,p=4 时筛（4不是质数）
// - 只在 i=6,p=2 时筛一次（因为6=12/2，且2是12的最小质因子）
vector<int> linearSieve(int n) {
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        
        for (int p : primes) {
            if ((ll)i * p > n) break;
            is_prime[i * p] = false;
            if (i % p == 0) break;  // ❗关键：必须在筛掉 i*p 之后再 break
            
            // 【为什么这个顺序？】
            // 1. 先筛掉 i*p：保证每个合数被其最小质因子筛到
            // 2. 再检查 i % p == 0：如果成立，说明 p 是 i 的最小质因子
            //    此时停止，因为 i*primes[j] (j > 当前) 的最小质因子是 p，不是 primes[j]
            //    这些数会在 i'=i/p 时被筛掉（那时 p 才是 i' 的最小质因子）
            //
            // 【如果互换会怎样？】
            // 如果写成：
            //   if (i % p == 0) break;
            //   is_prime[i * p] = false;  // ❌ 永远执行不到！
            // 那么当 i % p == 0 时会直接 break，导致 i*p 没被筛掉，漏掉合数！
            //
            // 【例子】i = 6, p = 2
            // - 6 % 2 == 0，说明 2 是 6 的最小质因子
            // - 先筛掉 6*2=12 ✓（12 的最小质因子是 2）
            // - 再 break，不继续筛 6*3=18, 6*5=30...
            // - 因为 18 的最小质因子是 2（不是 3），应该在 i=9 时由 9*2 筛掉
            // - 如果互换顺序，12 就会被漏掉！
        }
    }
    
    return primes;
}

// 质因数分解
map<int, int> factorize(int n) {
    map<int, int> factors;
    
    for (int i = 2; (ll)i * i <= n; i++) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    
    if (n > 1) factors[n]++;
    
    return factors;
}

// 预计算欧拉函数
// 【欧拉函数 φ(n)】：1~n 中与 n 互质的数的个数
// 【公式】φ(n) = n × ∏(1- 1/p) = n × (p₁-1)/p₁ × (p₂-1)/p₂ × ...
//         其中 p₁, p₂, ... 是 n 的所有质因子
//
// 【示例】
// φ(12) = φ(2²×3) = 12 × (1-1/2) × (1-1/3) = 12 × 1/2 × 2/3 = 4
// 与12互质的数：1, 5, 7, 11（共4个）
//
// φ(15) = φ(3×5) = 15 × (1-1/3) × (1-1/5) = 15 × 2/3 × 4/5 = 8
// 与15互质的数：1, 2, 4, 7, 8, 11, 13, 14（共8个）
//
// 【算法思想】类似埃筛，从小到大枚举每个质数，更新所有它的倍数的欧拉函数
vector<int> computeEuler(int n) {
    vector<int> phi(n + 1);
    
    // 【初始化】假设每个数都与自己互质（把 φ(i) 初始化为 i）
    // 后续会根据质因子修正
    for (int i = 0; i <= n; i++) phi[i] = i;
    
    // 【筛法计算】枚举每个数，如果是质数则更新其倍数
    for (int i = 2; i <= n; i++) {
        // 【判断质数】如果 phi[i] == i，说明 i 还没被任何质因子修正过
        // 那么 i 就是质数（类似埃筛的思想）
        if (phi[i] == i) {  // i 是质数
            // 【更新所有 i 的倍数】j = i, 2i, 3i, 4i, ...
            // 对于每个 j，它的质因子包含 i，需要乘上 (1 - 1/i)
            for (int j = i; j <= n; j += i) {
                // 【公式变换】φ(j) = φ(j) × (1 - 1/i)
                //            = φ(j) × (i-1)/i
                //            = φ(j) - φ(j)/i
                // 这样可以避免浮点数运算
                phi[j] -= phi[j] / i;
                
                // 【手动模拟】以 j=12, i=2 为例：
                // - 初始 phi[12] = 12
                // - i=2 时：phi[12] = 12 - 12/2 = 6（乘了 1-1/2 = 1/2）
                // - i=3 时：phi[12] = 6 - 6/3 = 4（再乘 1-1/3 = 2/3）
                // - 最终 phi[12] = 4 ✓
            }
        }
    }
    
    return phi;
}

// 【复杂度】O(n log log n)，与埃筛相同
// 【特殊值】
// - φ(1) = 1（1与自己互质）
// - φ(p) = p-1（p是质数时，1~p-1都与p互质）
// - φ(p^k) = p^k - p^(k-1) = p^(k-1) × (p-1)
//
// 【性质】
// 1. 积性函数：gcd(m,n)=1 时，φ(m×n) = φ(m) × φ(n)
// 2. ∑_{d|n} φ(d) = n（n的所有因子的欧拉函数之和等于n）
// 3. φ(n) 是偶数（n>2时）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n = 1e7;
    
    // 获取质数表
    auto primes = linearSieve(n);
    cout << "质数个数: " << primes.size() << "\n";
    
    // 质因数分解示例
    int x = 1234567;
    auto factors = factorize(x);
    cout << "质因数分解 " << x << ": ";
    for (auto [p, cnt] : factors) {
        cout << p << "^" << cnt << " ";
    }
    cout << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. 埃筛：O(n log log n)，简单但不是线性
 * 2. 线性筛：O(n)，每个数只被其最小质因子筛一次
 * 3. 线性筛的 break：i % p == 0 时停止（避免 i*p 被重复筛）
 * 4. 质因数分解：试除法，∛n 以内的质数
 * 5. 欧拉函数：φ(n) = n * ∏(1 - 1/p)
 * 
 * 【常见变体】
 * - 莫比乌斯函数计算
 * - 最小质因子预处理
 * - 类似方向的积性函数
 * 
 * 【提交前检查】
 * ✓ 筛法范围是否足够
 * ✓ 线性筛中 break 条件是否正确
 * ✓ 质因数分解中 i*i <= n 的检查
 * ✓ 整数溢出（使用 long long）
 */
