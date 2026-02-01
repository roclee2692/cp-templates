/*
 * 【0-1 BFS】- 最短路径（边权仅为 0 或 1）
 * 
 * 时间复杂度：O(V+E)
 * 空间复杂度：O(V)
 * 
 * 适用场景：
 *   - 边权仅为 0 或 1
 *   - 比 Dijkstra 更快
 *   - 比 BFS 支持权重
 * 
 * 模板题：洛谷 P6175 - 无向图的最小环
 */
//在一个图中，所有边的权重（代价）只有 0 或 1，求从起点到终点的最短路径。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
const ll INF=(ll)1e18;

int n,m,src;
vector<vector<pll>> adj;
vector<ll> dist01;

void zeroOneBFS(){
    deque<ll> dq;
    dist01.assign(n+1,INF);
    dist01[src]=0;
    dq.push_front(src);
    
    while(!dq.empty()){
        ll u=dq.front();
        dq.pop_front();
        
        for(auto &[v,w]:adj[u]){
            if(dist01[u]+w<dist01[v]){
                dist01[v]=dist01[u]+w;
                
                // 权重为 0 的边加到队首（优先处理）
                if(w==0) dq.push_front(v);
                // 权重为 1 的边加到队尾
                else dq.push_back(v);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>src;
    adj.assign(n+1,vector<pll>());
    
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        // 若无向图可加：adj[v].push_back({u,w});
    }
    
    zeroOneBFS();
    
    for(int i=1;i<=n;i++){
        cout<<(dist01[i]==INF?-1:dist01[i]);
        if(i<n) cout<<' ';
    }
    cout<<'\n';
    
    return 0;
}

/*
 * 【关键点】
 * 1. 使用双端队列（deque）代替优先队列
 * 2. 权重为 0 的边加到队首（push_front）
 * 3. 权重为 1 的边加到队尾（push_back）
 * 4. 这样保证先处理权重小的边
 * 
 * 【原理】
 * - 边权只有 0 和 1，所以距离序列单调递增
 * - 权重 0 的边不增加距离，优先处理
 * - 权重 1 的边增加距离 1，延后处理
 * - 相当于 BFS + 权重，时间复杂度 O(V+E)
 * 
 * 【常见变体】
 * - 无向图：加双向边（记得两个方向都加）
 * - 记录路径：用 parent[] 数组
 * - 多源点：初始时把所有源点都加入队列，距离设为 0
 * 
 * 【注意事项】
 * - [ ] 边权必须仅为 0 或 1，否则算法错误
 * - [ ] 不能有负权边
 * - [ ] 队首用 push_front + pop_front
 * - [ ] 队尾用 push_back + pop_back
 * - [ ] 初始化 dist01[src]=0，其余为 INF
 * - [ ] 时间复杂度 O(V+E)，比 Dijkstra 快得多
 */
