/*
 * 【Trie 树】- 高效前缀匹配和字典树
 * 
 * 时间复杂度：O(L) 插入/查询，L = 字符串长度
 * 空间复杂度：O(ALPHABET_SIZE * N)，N = 节点数
 * 
 * 适用场景：
 *   - 字典序最小/最大问题
 *   - 前缀匹配（自动补全）
 *   - 字典中最长匹配前缀
 *   - IP 路由（最长前缀匹配）
 * 
 * 模板题：
 *   - 洛谷 P8306 - 【模板】Trie
 *   - Codeforces 706C - Hard problem
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    map<char, TrieNode*> children;
    bool isEnd = false;
    int cnt = 0;  // 经过此节点的字符串数
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->cnt++;
        }
        node->isEnd = true;
    }
    
    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) return false;
            node = node->children[c];
        }
        return node->isEnd;
    }
    
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children.count(c)) return false;
            node = node->children[c];
        }
        return true;
    }
    
    string longestPrefix(const string& word) {
        TrieNode* node = root;
        string result = "";
        for (char c : word) {
            if (!node->children.count(c)) break;
            result += c;
            node = node->children[c];
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    Trie trie;
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        string op, word;
        cin >> op >> word;
        
        if (op == "insert") {
            trie.insert(word);
        } else if (op == "search") {
            cout << (trie.search(word) ? "YES" : "NO") << "\n";
        } else if (op == "startsWith") {
            cout << (trie.startsWith(word) ? "YES" : "NO") << "\n";
        }
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. TrieNode 结构：children map + isEnd flag + cnt 计数
 * 2. insert：逐个字符创建/访问节点
 * 3. search：要检查 isEnd，前缀存在但字符串不完整
 * 4. startsWith：不需要 isEnd 检查
 * 5. cnt 统计：可用于找最长前缀等问题
 * 
 * 【常见变体】
 * - 数组代替 map（固定字母表，速度更快）
 * - 带权 Trie（每条边有权值）
 * - 异或 Trie（二进制Trie，配合贪心）
 * 
 * 【提交前检查】
 * ✓ new 创建的节点是否考虑内存释放
 * ✓ search vs startsWith 的逻辑区别
 * ✓ 是否支持重复插入
 * ✓ 字母表大小是否设置正确
 */
