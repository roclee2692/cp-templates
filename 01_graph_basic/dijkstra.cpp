/*
 * 【Dijkstra 算法】- 单源最短路径（堆优化版）
 * 
 * 时间复杂度：O((E + V) log V)
 * 空间复杂度：O(V + E)
 * 
 * 适用场景：
 *   - 求单源最短路径
 *   - 所有边权非负
 *   - 稠密图可用邻接矩阵，稀疏图用邻接表
 * 
 * 模板题：洛谷 P3371 - 【模板】单源最短路径（弱化版）
 */
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF = 4e18;
const int XN=1e6+7;

vector<pll> adj[XN];
ll dist[XN];

void dijkstra(ll start,ll n){
    fill(dist,dist+n+1,INF);
    dist[start]=0;

    priority_queue<pll,vector<pll>,greater<pll>> pq;
    pq.push({0,start});

    while(!pq.empty()){
        auto p=pq.top(); pq.pop();
        ll d=p.first, u=p.second;
        if(d>dist[u]) continue;
        for(auto &e:adj[u]){
            ll v=e.first, w=e.second;
 //松弛操作 给到 v 的距离“放松”一下，看看能不能再缩短一点，能就更新。
//d 就是你当初 emplace(dist[u], u) 时，把当时 dist[u] 的值装到队列里的那个“快照
// u之前也压入过不是最终最短路径的值 只有d==dist[u] 该值才是可用的
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.emplace(dist[v],v);
//min()会将每条边都往堆里压一次，即便它并没有“松弛”到更短的距离
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    ll n,m,s;
    cin>>n>>m>>s;
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    dijkstra(s,n);
    for(int i=1;i<=n;i++){
        if(dist[i]==INF) cout<<(1<<31)-1;
        else  cout << dist[i];
        if (i < n) cout << " ";
    }
    return 0;
}
/*
 * 【关键点】
 * 1. 使用优先队列优化：每次取距离最小的节点
 * 3. 松弛操作：if (dist[u] + w < dist[v]) 更新
 * 4. 必须保证所有边权非负（否则用 SPFA）
 * 
 * 【常见变体】
 * - 求多源最短路：对每个源点调用一次 dijkstra()
 * - 记录路径：用 parent[] 数组记录前驱节点
 * - 输出路径：反向递推 parent[]
 * 
 * 【提交前检查】
 * - [ ] 边权是否可能为负？(是则用 SPFA)
 * - [ ] n, m 是否在范围内？
 * - [ ] 是否考虑了自环和重边？
 */