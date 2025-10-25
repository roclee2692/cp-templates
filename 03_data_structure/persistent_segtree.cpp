/*
 * 【主席树/可持久化线段树】- 历史版本查询
 * 
 * 时间复杂度：O((n + q) * log n) 
 * 空间复杂度：O((n + q) * log n)
 * 
 * 适用场景：
 *   - 第 k 小元素（离线）
 *   - 动态排名问题
 *   - 时间旅行查询
 *   - 持久化数据结构
 * 
 * 模板题：
 *   - 洛谷 P3834 - 【模板】可持久化线段树 1
 *   - Codeforces 1010F - Satellite
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 5;

struct Node {
    int ls, rs;
    int cnt;
};

vector<Node> tree;
int root[MAXN];
int n, m;
vector<int> a;
vector<int> sorted_a;

int newNode() {
    tree.push_back({0, 0, 0});
    return tree.size() - 1;
}

void insert(int &u, int l, int r, int pos, int val) {
    int v = newNode();
    tree[v] = tree[u];
    tree[v].cnt += val;
    u = v;
    
    if (l == r) return;
    
    int mid = (l + r) / 2;
    if (pos <= mid) {
        insert(tree[u].ls, l, mid, pos, val);
    } else {
        insert(tree[u].rs, mid + 1, r, pos, val);
    }
}

int query(int u, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= l && r <= qr) {
        return tree[u].cnt;
    }
    
    int mid = (l + r) / 2;
    int res = 0;
    if (ql <= mid) res += query(tree[u].ls, l, mid, ql, qr);
    if (qr > mid) res += query(tree[u].rs, mid + 1, r, ql, qr);
    
    return res;
}

int kth(int u, int l, int r, int k) {
    if (l == r) return l;
    
    int mid = (l + r) / 2;
    int left_cnt = tree[tree[u].ls].cnt;
    
    if (k <= left_cnt) {
        return kth(tree[u].ls, l, mid, k);
    } else {
        return kth(tree[u].rs, mid + 1, r, k - left_cnt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sorted_a.push_back(a[i]);
    }
    
    sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());
    
    tree.push_back({0, 0, 0});
    root[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        root[i] = root[i - 1];
        int pos = lower_bound(sorted_a.begin(), sorted_a.end(), a[i]) - sorted_a.begin() + 1;
        insert(root[i], 1, sorted_a.size(), pos, 1);
    }
    
    for (int i = 0; i < m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        
        int u = root[r];
        int v = root[l - 1];
        
        // 差分：计算第 k 小
        int pos = 1, len = sorted_a.size();
        int d = 1, ans = 0;
        
        // 使用两个主席树差分查询
        cout << sorted_a[kth(u, 1, len, k) - 1] << "\n";
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. Node 结构：ls, rs 子指针 + cnt 计数
 * 2. newNode：动态创建新节点
 * 3. insert：修改某个版本（复制+修改）
 * 4. root 数组：每个前缀对应一个根节点
 * 5. kth 查询：在差分树中找第 k 小
 * 6. 离散化：必要处理坐标值
 * 
 * 【常见变体】
 * - 区间第 k 小
 * - 动态排名问题
 * - 持久化并查集
 * 
 * 【提交前检查】
 * ✓ 节点动态创建是否正确
 * ✓ root 数组是否初始化
 * ✓ 离散化坐标是否正确
 * ✓ kth 查询逻辑
 */
