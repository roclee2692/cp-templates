/*
 * 【SPFA 算法】- 单源最短路径（支持负权边）
 * 
 * 时间复杂度：O(E * V)（最坏），平均 O(E)
 * 空间复杂度：O(V + E)
 * 
 * 适用场景：
 *   - 边权可能为负
 *   - 判断负环
 *   - Dijkstra 不适用的情况
 * 
 * 模板题：洛谷 P3385 - 【模板】负环
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
const ll INF = 1e18;
const int XN=1e6+7;
vector<pll> adj[XN];// inq[u] 标记 u 是否在队列中
vector<ll> dist;// dist: 最短距离；cnt: 入队次数
ll cnt[XN],inq[XN];//vector<ll> dist,cnt,inq;// ❌ 没有分配大小 初始化不完整
bool spfa(int start,int n){
    dist.assign(n+1,INF);
    dist[start]=0;
    queue<ll> q;
    q.push(start);
    inq[start]=1;
    cnt[start]++;
    while(!q.empty()){
        ll u=q.front(); q.pop();
        inq[u]=0;
        for(auto &e:adj[u]){
            ll v=e.first,w=e.second;
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                if(!inq[v]){
                    q.push(v);
                    inq[v]=1;
                    cnt[v]++;
                    if(cnt[v]>=n) return 0;// 如果某个点入队超过 n-1 次，说明存在负环
                }
            }
        }
    }
    return 1;// 不存在负环
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    ll n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        ll u,v,w;
         cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
     if (!spfa(1, n)) {
        cout << "YES\n";  // 存在负环
    } else {
        cout << "NO\n";  // 不存在负环
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. 使用队列（不是优先队列）
 * 2. cnt[] 记录每个节点入队次数
 * 3. 如果任何节点入队次数 >= n，说明存在负环
 * 4. 边松弛成功才加入队列
 * 
 * 【原理】
 * - 正常情况下，每条最短路径最多经过 n-1 条边
 * - 如果某个节点入队 n 次或以上，说明路径形成环
 * - 且该环总权值为负（负环）
 * 
 * 【常见变体】
 * - 只求最短路（不检测负环）：删除 cnt[] 相关代码
 * - 多源点检测负环：对所有点调用一次 spfa()
 * - 记录路径：用 parent[] 数组
 * 
 * 【性能优化】
 * - 小队列优化：用双端队列，入队时决定放在队首还是队尾
 * - 堆栈优化 (SLF)：用栈代替队列
 * - 当该算法超时时，改用 Dijkstra + 重新标号 (Potential)
 * 
 * 【提交前检查】
 * - [ ] n, m 是否正确？
 * - [ ] 负环的判断条件是否正确？
 * - [ ] 是否需要处理多个连通分量？
 */
