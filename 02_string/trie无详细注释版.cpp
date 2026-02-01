/*
 * 【Trie 树（字典树）】- 高效字符串前缀处理
 * 
 * 核心思想：利用字符串的公共前缀来减少查询时间和存储空间
 * 
 * 时间复杂度：O(L)，L = 字符串长度
 *   - 插入：O(L)
 *   - 查询：O(L)
 *   - 前缀匹配：O(L)
 * 
 * 空间复杂度：O(ALPHABET_SIZE × N)，N = 总字符数
 * 
 * 适用场景：
 *   - 字符串检索（词典、搜索提示）
 *   - 前缀匹配（自动补全）
 *   - 字符串去重
 *   - 统计前缀出现次数
 *   - 最长公共前缀
 *   - 异或最大值（01-Trie）
 * 
 * 模板题：
 *   - 洛谷 P8306 - 【模板】字典树
 *   - 洛谷 P2580 - 于是他错误的点名开始了
 */

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

struct Node{
    ll passCnt=0;  // 经过此节点的字符串数
    ll endCnt=0;   // 以此节点结尾的单词数
    unordered_map<char, ll> nxt;  // 子节点映射：字符 → 下标
};

vector<Node> T(2);
ll tot=1;

inline void clear(){
    T.assign(2,Node());
    tot=1;
}

inline void insertStr(const string &s){
    ll u=1;
    T[u].passCnt++;
    
    for(char ch:s){
        if(!T[u].nxt.count(ch)){
            T[u].nxt[ch]=++tot;
            if((ll)T.size() <= tot){  // ✅ 修正：显式类型转换
                T.emplace_back();
            }
        }
        u=T[u].nxt[ch];
        /*
        T[u].nxt[ch]  // 表示：字符 ch 对应的子节点编号（可能是新创建的，也可能是已存在的）
        tot           // 表示：当前最大的节点编号（只在创建新节点时更新）*/
        T[u].passCnt++;
    }
    T[u].endCnt++;
}

inline ll countWord(const string &s){
    ll u=1;
    for(char ch:s){
        if(!T[u].nxt.count(ch)) return 0;
        u=T[u].nxt[ch];
    }
    return T[u].endCnt;
}

inline ll countPrefix(const string &p){
    ll u=1;
    for(char ch:p){
        if(!T[u].nxt.count(ch)) return 0;
        u=T[u].nxt[ch];
    }
    return T[u].passCnt;
}

inline void eraseOnce(const string & s){
    if(countWord(s)==0) return;  // ✅ 修正：void 函数不返回值
    ll u=1;
    T[u].passCnt--;
    for(char ch:s){
        u=T[u].nxt[ch];
        T[u].passCnt--;
    }
    T[u].endCnt--;
}
int main(){
     ios::sync_with_stdio(false);
    cin.tie(nullptr);

    clear();
    insertStr("apple");
    insertStr("app");
    insertStr("apple");
    cout << countWord("apple") << "\n";   // 输出：2（插入了 2 次）
    cout << countWord("app") << "\n";     // 输出：1
    cout << countWord("appl") << "\n";    // 输出：0（不完整）
    cout << countPrefix("app") << "\n";   // 输出：3（app×1 + apple×2）
    
    eraseOnce("apple");
    cout << countWord("apple") << "\n";   // 输出：1（删除一次后）
    
    return 0;
}
/*
 * ==================== 核心知识点 ====================
 * 
 * 【Trie 树结构】
 *        root
 *       /    \
 *      a      b
 *     / \      \
 *    p   t      a
 *   / \   \      \
 *  p   t   e      d
 * 
 * 存储：app, apt, ate, bad
 * 
 * 【关键点】
 * 1. 根节点为空，不存储任何字符
 * 2. 每个节点存储一个字符到子节点的映射
 * 3. isEnd 标记单词结尾（区分前缀和完整单词）
 * 4. cnt 统计经过次数（用于统计前缀频率）
 * 
 * 【search vs startsWith 的区别】
 * search("app"):     需要检查 isEnd，必须是完整单词
 * startsWith("app"): 不检查 isEnd，只要前缀存在即可
 * 
 * 例如 Trie 中有 "apple"：
 *   search("app")      → false（不是完整单词）
 *   startsWith("app")  → true（前缀存在）
 *   search("apple")    → true（完整单词）
 * 
 * 【实现方式对比】
 * 
 * | 特性 | map 实现 | 数组实现 |
 * |------|---------|---------|
 * | 速度 | 较慢（log 级） | 快（O(1)） |
 * | 空间 | 节省（按需分配） | 固定开销大 |
 * | 灵活性 | 支持任意字符 | 仅固定字母表 |
 * | 适用 | 字符集不确定 | 字符集固定 |
 * 
 * 竞赛建议：
 * - 小写字母题目：用数组（children[26]）更快
 * - 字符集未知：用 map 更安全
 * 
 * 【常见变体】
 * 
 * 1. 01-Trie（异或字典树）
 *    - 用于求异或最大值、异或第 k 大等
 *    - 每个节点只有 0/1 两个子节点
 *    - 应用：最大异或对、异或路径问题
 * 
 * 2. 持久化 Trie
 *    - 支持查询历史版本
 *    - 可持久化线段树的思想
 * 
 * 3. 带权 Trie
 *    - 边上有权值
 *    - 用于字符串路径和问题
 * 
 * 【时间复杂度分析】
 * - 插入 n 个长度为 L 的字符串：O(n × L)
 * - 查询：O(L)
 * - 空间：最坏 O(n × L × ALPHABET_SIZE)
 * 
 * 【常见应用题型】
 * 1. 字符串检索（基础）
 * 2. 前缀统计（countPrefix）
 * 3. 最长公共前缀（LCP）
 * 4. 字符串去重
 * 5. 异或最大值（01-Trie）
 * 6. 自动补全/搜索提示
 * 
 * 【优化技巧】
 * 1. 数组代替 map：字母表固定时速度提升 3-5 倍
 * 2. 内存池：避免频繁 new/delete
 * 3. 路径压缩：合并只有一个子节点的链
 * 
 * 【提交前检查清单】
 * - [ ] 字符集是什么？（小写/大写/数字/任意）
 * - [ ] 使用 map 还是数组？
 * - [ ] search 和 startsWith 的区别理解清楚了吗？
 * - [ ] 是否需要支持重复插入？（wordCnt）
 * - [ ] 是否需要删除操作？
 * - [ ] 内存是否足够？（估算节点数）
 */
