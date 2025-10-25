/*
 * 【树状数组/芬威克树】- 区间查询与单点更新
 * 
 * 时间复杂度：O(log n) 单点更新 + O(log n) 区间查询
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 区间和查询
 *   - 单点更新
 *   - 逆序对计数
 *   - 比线段树轻量（常数小）
 * 
 * 模板题：
 *   - 洛谷 P3374 - 【模板】树状数组 1
 *   - Codeforces 1155D - Neko and Enticement
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class BIT {
private:
    vector<ll> tree;
    int n;
    
    int lowbit(int x) {
        return x & (-x);
    }
    
public:
    BIT(int n) : n(n), tree(n + 1, 0) {}
    
    void update(int pos, ll val) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tree[i] += val;
        }
    }
    
    ll query(int pos) {
        ll res = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            res += tree[i];
        }
        return res;
    }
    
    // 区间查询 [l, r]
    ll rangeQuery(int l, int r) {
        if (l > r) return 0;
        return query(r) - (l > 1 ? query(l - 1) : 0);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    BIT bit(n);
    
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        bit.update(i, x);
    }
    
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        
        if (op == 1) {
            // 单点更新
            int pos;
            ll val;
            cin >> pos >> val;
            ll old = bit.rangeQuery(pos, pos);
            bit.update(pos, val - old);
        } else {
            // 区间查询
            int l, r;
            cin >> l >> r;
            cout << bit.rangeQuery(l, r) << "\n";
        }
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. lowbit(x) = x & (-x)：提取最低位的 1
 * 2. update：沿 i += lowbit(i) 路径向上更新
 * 3. query：沿 i -= lowbit(i) 路径向下查询
 * 4. 位置是 1-indexed（传统）
 * 
 * 【常见变体】
 * - 差分数组：区间加 + 单点查询
 * - 二维树状数组：矩形求和
 * - 带修改主席树（树状数组 + 主席树）
 * 
 * 【提交前检查】
 * ✓ lowbit 公式是否正确
 * ✓ 索引是否 1-indexed
 * ✓ update/query 的方向是否对应
 * ✓ rangeQuery 边界处理
 */
