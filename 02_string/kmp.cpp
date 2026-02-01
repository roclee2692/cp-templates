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
using ll=long long;
using pll=pair<ll,ll>;

string S,P;
vector<ll> nxt,pos;
ll cnt;

// 构建 next 数组：nxt[i] = P[0..i] 的最长相等前后缀长度
void build(){
    ll m=P.size();
    nxt.assign(m,0);  // 初始化全为 0
    // 【关键】i 必须从 1 开始，因为：
    // - nxt[0] 定义就是 0（单字符没有真前后缀）
    // - 如果 i=0 进入循环，会错误计算：P[0]==P[0] 导致 nxt[0]=1（错误！）
    for(int i=1,j=0;i<m;i++){  
        // j 表示当前最长相等前后缀的长度
        // 当 P[i] 不匹配时，回退 j 到更短的前缀
        while(j>0 && P[i]!=P[j]) j=nxt[j-1];
        // 如果匹配，前后缀长度+1
        if(P[i]==P[j]) j++;
        nxt[i]=j;  // 记录 P[0..i] 的最长相等前后缀长度
    }
}

// KMP 匹配：在文本 S 中查找模式 P
void kmp(){
    int n=S.size(),m=P.size();
    pos.clear();
    cnt=0;
    // i 扫描文本 S，j 表示已匹配的长度（即下一个要比较的是 P[j]）
    for(int i=0,j=0;i<n;i++){
        // 失配：回退 j 到更短的已匹配前缀
        while(j>0 && S[i]!=P[j]) j=nxt[j-1];
        // 匹配：已匹配长度+1
        if(S[i]==P[j]) j++;
        // 完整匹配：j==m 说明 P 的所有字符都匹配了
        if(j==m){
            // 计算匹配起始位置：i 是当前位置，i-m+1 是起点（0-indexed）
            pos.push_back(i-m+1);      // 0-indexed 存储
            // 【1-indexed 方案】若题目要求从 1 开始：pos.push_back(i-m+2);
            
            // 继续查找下一个匹配
            j=nxt[j-1];                // 允许重叠（标准 KMP）
            // j=0;                    // 不允许重叠（从头开始找）
            cnt++;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> S >> P;
    
    build();
    kmp();
     // 输出所有匹配位置（1-indexed）
    for (int p : pos) cout << p + 1 << "\n";
    
    return 0;
}

/*
 * 【使用说明】
 * S = 文本串，P = 模式串
 * build() 构建 next 数组
 * kmp() 查找所有匹配，结果存在 pos 中（0-indexed）
 * 
 * 【next 数组】
 * nxt[i] = P[0..i] 的最长相等前后缀长度
 * 
 * 【提交前检查】
 * - [ ] 输出是 0-indexed 还是 1-indexed？
 * - [ ] 是否需要输出 next 数组？
 */
