/*
 * 【Trie 树（字典树）】- 竞赛简洁版
 * 
 * 核心思想：用数组存储所有节点，用下标代替指针
 * 
 * 时间复杂度：O(L)，L = 字符串长度
 * 空间复杂度：O(N × ALPHABET_SIZE)，N = 总字符数
 * 
 * 优势：
 *   - 无需指针，避免内存管理
 *   - 数组连续存储，缓存友好
 *   - 代码简洁，易于调试
 *   - 速度快，内存可控
 * 
 * 适用场景：
 *   - 字符串检索、前缀匹配
 *   - 字符串去重、统计
 *   - 最长公共前缀
 * 
 * 模板题：洛谷 P8306
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* ==================== Trie 节点定义 ==================== */
struct Node {
    ll passCnt = 0;  // 经过此节点的字符串数（用于前缀统计）
    ll endCnt = 0;   // 以此节点结尾的单词数（支持重复插入）
    
    // 子节点映射：字符 → 子节点下标
    unordered_map<char, ll> nxt;  // 快速查找，适合 Trie
    // map<char, ll> nxt;         // 有序版本，内存更省但稍慢
    
    // 【数组实现】如果字符集固定（如仅小写字母）
    // ll nxt[26] = {0};  // 初始化为 0 表示无子节点
};

/* ==================== 全局 Trie 数组 ==================== */
vector<Node> T(2);  // T[0] 空置，T[1] 作为根节点
ll tot = 1;         // 当前已分配的节点数

/* ==================== Trie 操作函数 ==================== */

// 【函数 1】清空 Trie（重置状态）
// 用于多组测试数据
inline void clearTrie() {
    T.assign(2, Node());  // 重置为初始状态
    tot = 1;
}

// 【函数 2】插入字符串
// 功能：将字符串 s 插入 Trie 树
// 时间复杂度：O(|s|)
inline void insertStr(const string &s) {
    ll u = 1;  // 从根节点开始
    T[u].passCnt++;  // 根节点的 passCnt++
    
    for (char ch : s) {
        // 如果当前字符的子节点不存在，创建新节点
        if (!T[u].nxt.count(ch)) {
            T[u].nxt[ch] = ++tot;  // 分配新节点编号
            
            // 动态扩展数组（按需分配，节省空间）
            if ((ll)T.size() <= tot) {
                T.emplace_back();  // 添加新节点
            }
        }
        
        u = T[u].nxt[ch];  // 移动到子节点
        T[u].passCnt++;    // 经过此节点的字符串数+1
    }
    
    T[u].endCnt++;  // 标记单词结尾，支持重复插入统计
}

// 【函数 3】精确查找
// 功能：统计字符串 s 完整出现的次数
// 返回：出现次数（0 表示不存在）
inline ll countWord(const string &s) {
    ll u = 1;
    for (char ch : s) {
        if (!T[u].nxt.count(ch)) return 0;  // 路径不存在
        u = T[u].nxt[ch];
    }
    return T[u].endCnt;  // 返回以此节点结尾的单词数
}

// 【函数 4】前缀统计
// 功能：统计有多少个字符串以 p 为前缀
// 返回：前缀出现的次数
inline ll countPrefix(const string &p) {
    ll u = 1;
    for (char ch : p) {
        if (!T[u].nxt.count(ch)) return 0;  // 前缀不存在
        u = T[u].nxt[ch];
    }
    return T[u].passCnt;  // 返回经过此节点的字符串数
}

// 【函数 5】删除一次（可选）
// 功能：从 Trie 中删除字符串 s 的一次出现
// 注意：只减少计数，不真正释放节点（竞赛中通常够用）
inline void eraseOnce(const string &s) {
    if (countWord(s) == 0) return;  // 单词不存在，直接返回
    
    ll u = 1;
    T[u].passCnt--;  // 根节点计数-1
    
    for (char ch : s) {
        u = T[u].nxt[ch];
        T[u].passCnt--;  // 路径上所有节点计数-1
    }
    
    T[u].endCnt--;  // 结尾计数-1
}

/* ==================== 使用示例 ==================== */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 示例 1：基本操作
    clearTrie();
    insertStr("apple");
    insertStr("app");
    insertStr("apple");  // 重复插入
    
    cout << countWord("apple") << "\n";   // 输出：2（插入了 2 次）
    cout << countWord("app") << "\n";     // 输出：1
    cout << countWord("appl") << "\n";    // 输出：0（不完整）
    cout << countPrefix("app") << "\n";   // 输出：3（app×1 + apple×2）
    
    eraseOnce("apple");
    cout << countWord("apple") << "\n";   // 输出：1（删除一次后）
    
    // 示例 2：洛谷 P8306 模板题
    /*
    int T;
    cin >> T;
    while (T--) {
        clearTrie();  // 每组数据清空
        int n, q;
        cin >> n >> q;
        
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            insertStr(s);
        }
        
        for (int i = 0; i < q; i++) {
            string s;
            cin >> s;
            cout << countPrefix(s) << "\n";
        }
    }
    */
    
    return 0;
}

/*
 * ==================== 核心知识点 ====================
 * 
 * 【本版本优势】
 * 1. 无指针：用数组下标代替指针，避免内存管理
 * 2. 简洁：核心代码不到 50 行
 * 3. 高效：数组连续存储，缓存友好
 * 4. 灵活：unordered_map 支持任意字符集
 * 5. 实用：支持重复插入、删除、前缀统计
 * 
 * 【Trie 树结构】
 *    下标:  1 (root)
 *          / \
 *         2   3
 *        /     \
 *       4       5
 * 
 * 存储方式：T[1] 是根节点，T[2]、T[3]... 是子节点
 * 优势：数组访问比指针更快，内存连续利用缓存
 * 
 * 【核心变量说明】
 * - passCnt: 经过此节点的字符串数（用于前缀统计）
 * - endCnt:  以此节点结尾的单词数（支持重复插入）
 * - nxt:     子节点映射（字符 → 下标）
 * - tot:     当前已分配的节点总数
 * 
 * 【countWord vs countPrefix】
 * countWord("app"):    返回完整单词 "app" 的出现次数（检查 endCnt）
 * countPrefix("app"):  返回以 "app" 为前缀的字符串数（检查 passCnt）
 * 
 * 例如插入 "app", "apple", "apple"：
 *   countWord("app")     → 1
 *   countWord("apple")   → 2
 *   countPrefix("app")   → 3（1个app + 2个apple）
 * 
 * 【实现方式对比】
 * 
 * | 特性 | 本版本（数组+map） | 指针版 | 数组版(nxt[26]) |
 * |------|------------------|--------|----------------|
 * | 代码量 | 少 | 中 | 少 |
 * | 速度 | 快 | 中 | 最快 |
 * | 内存 | 按需分配 | 按需分配 | 固定开销 |
 * | 灵活性 | 任意字符 | 任意字符 | 仅固定字符集 |
 * | 易用性 | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐ |
 * 
 * 【如何改为数组版（仅小写字母）】
 * struct Node {
 *     ll passCnt = 0, endCnt = 0;
 *     ll nxt[26] = {0};  // 0 表示无子节点
 * };
 * 
 * // 插入时：
 * int idx = ch - 'a';
 * if (!T[u].nxt[idx]) {
 *     T[u].nxt[idx] = ++tot;
 *     if ((ll)T.size() <= tot) T.emplace_back();
 * }
 * u = T[u].nxt[idx];
 * 
 * 【常见应用题型】
 * 1. 字符串检索/去重（countWord）
 * 2. 前缀统计（countPrefix）- 洛谷 P8306
 * 3. 最长公共前缀（LCP）
 * 4. 字符串排序
 * 5. 异或最大值（01-Trie，改为 nxt[2]）
 * 6. 自动补全/搜索提示
 * 
 * 【01-Trie 改法（异或问题）】
 * struct Node {
 *     ll cnt = 0;
 *     ll nxt[2] = {0};  // 0/1 两个子节点
 * };
 * 
 * void insertNum(ll x) {  // 插入数字的二进制表示
 *     ll u = 1;
 *     for (int i = 30; i >= 0; i--) {  // 从高位到低位
 *         int bit = (x >> i) & 1;
 *         if (!T[u].nxt[bit]) {
 *             T[u].nxt[bit] = ++tot;
 *             if ((ll)T.size() <= tot) T.emplace_back();
 *         }
 *         u = T[u].nxt[bit];
 *     }
 * }
 * 
 * 【内存估算】
 * - n 个长度为 L 的字符串
 * - 最坏情况：O(n × L) 个节点
 * - 每个节点：sizeof(Node) ≈ 32 字节（map版）
 * - 总内存：约 n × L × 32 字节
 * - 例如：10^5 个长度 50 的字符串 ≈ 150MB
 * 
 * 【优化技巧】
 * 1. 预分配空间：T.reserve(n * L) 避免多次扩容
 * 2. 字符集固定：改用数组 nxt[26] 更快
 * 3. 多组数据：用 clearTrie() 重置，避免重新分配
 * 
 * 【提交前检查清单】
 * - [ ] 字符集是什么？（决定用 map 还是数组）
 * - [ ] 是否需要支持重复插入？（已支持，看 endCnt）
 * - [ ] 是否需要删除操作？（已有 eraseOnce）
 * - [ ] 内存是否足够？（估算节点数 ≈ 总字符数）
 * - [ ] 多组数据是否清空？（调用 clearTrie）
 * - [ ] 下标从 1 开始！（T[0] 空置，T[1] 是根）
 */
