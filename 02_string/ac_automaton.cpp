/*
 * 【AC 自动机】- 多模式字符串匹配（升级版Trie）
 * 
 * 时间复杂度：O(n + m*k) 预处理 + O(len) 匹配
 *   n = 所有模式总长度，m = 模式数，k = 字母表大小，len = 文本长度
 * 空间复杂度：O(n*k)
 * 
 * 适用场景：
 *   - 在文本中查找多个模式的所有出现位置
 *   - 敏感词过滤
 *   - 字典最长匹配（贪心）
 * 
 * 模板题：
 *   - 洛谷 P3808 - 【模板】AC 自动机（简单版）
 *   - Codeforces 754F - Robbers
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
const int ALPHABET_SIZE = 26;

struct AhoCorasick {
    int go[MAXN][ALPHABET_SIZE];
    int fail[MAXN];
    int cnt[MAXN];  // 节点处的模式匹配计数
    int node_count = 0;
    
    AhoCorasick() {
        memset(go, 0, sizeof(go));
        memset(fail, 0, sizeof(fail));
        memset(cnt, 0, sizeof(cnt));
    }
    
    void insert(const string& s) {
        int u = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (!go[u][ch]) {
                go[u][ch] = ++node_count;
            }
            u = go[u][ch];
        }
        cnt[u]++;
    }
    
    void build() {
        queue<int> q;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (go[0][i]) {
                q.push(go[0][i]);
            }
        }
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (go[u][i]) {
                    int v = go[u][i];
                    int f = fail[u];
                    while (f && !go[f][i]) {
                        f = fail[f];
                    }
                    fail[v] = go[f][i];
                    cnt[v] += cnt[fail[v]];  // 累加失配链上的匹配数
                    q.push(v);
                } else {
                    int f = fail[u];
                    while (f && !go[f][i]) {
                        f = fail[f];
                    }
                    go[u][i] = go[f][i];
                }
            }
        }
    }
    
    int query(const string& text) {
        int u = 0, result = 0;
        for (char c : text) {
            int ch = c - 'a';
            u = go[u][ch];
            result += cnt[u];
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    AhoCorasick ac;
    
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        ac.insert(s);
    }
    
    ac.build();
    
    for (int i = 0; i < m; i++) {
        string text;
        cin >> text;
        cout << ac.query(text) << "\n";
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. Trie 构建：insert 函数逐个模式字符串
 * 2. fail 链构建：BFS 按层处理，fail 指向更短的相同后缀
 * 3. go 数组完善：处理失配时的边跳转
 * 4. cnt 累加：失配链上的匹配数要累加到当前节点
 * 5. query 流程：按文本字符逐个转移，累加 cnt
 * 
 * 【常见变体】
 * - 记录具体匹配位置（不仅是计数）
 * - 状态压缩（bit 标记匹配模式）
 * - 带权版本（每个模式有权值）
 * 
 * 【提交前检查】
 * ✓ MAXN 是否足够（总字符数 + 余量）
 * ✓ fail 链的构建逻辑
 * ✓ go 数组是否完全填充（不留空转移）
 * ✓ cnt 累加位置（在 fail 链建立时进行）
 */
