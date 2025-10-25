/*
 * 【KMP 算法】- 字符串模式匹配
 * 
 * 时间复杂度：O(n + m)，其中 n = 文本长度，m = 模式长度
 * 空间复杂度：O(m)
 * 
 * 适用场景：
 *   - 在文本中查找所有模式出现位置
 *   - 不允许回溯（相比朴素算法更高效）
 * 
 * 模板题：洛谷 P3375 - 【模板】KMP字符串匹配
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text, pattern;
    cin >> text >> pattern;
    
    int n = text.size();
    int m = pattern.size();
    
    // 计算 next 数组（失配函数）
    vector<int> next(m, 0);
    for (int i = 1; i < m; i++) {
        int j = next[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        next[i] = j;
    }
    
    // KMP 匹配
    vector<int> positions;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            positions.push_back(i - m + 1);
            j = next[j - 1];
        }
    }
    
    // 输出结果
    for (int pos : positions) {
        cout << pos + 1 << "\n";  // 1-indexed
    }
    
    return 0;
}

/*
 * 【待填充】
 * - next 数组的完整解释
 * - 与朴素算法的对比
 * - 常见变体（多模式匹配等）
 * - 提交前检查清单
 */
