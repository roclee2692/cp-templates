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
            if (i % p == 0) break;  // 关键：避免重复筛
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
vector<int> computeEuler(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++) phi[i] = i;
    
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {  // i 是质数
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    
    return phi;
}

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
