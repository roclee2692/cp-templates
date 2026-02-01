/*
 * 【Bellman-Ford 算法】- 单源最短路径（支持负权边）
 * 
 * 时间复杂度：O(V*E)
 * 空间复杂度：O(V)
 * 
 * 适用场景：
 *   - 边权可为负
 *   - 检测负环
 *   - 点数较小（n <= 1000）
 * 
 * 模板题：洛谷 P3385 - 【模板】负环
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(ll)1e18;

struct Edge{
    ll u,v,w;
};
int n,m,src;
vector<Edge> edges;
vector<ll> dist;

bool bellmanFord(){
    dist.assign(n+1,INF);
    dist[src]=0;
    // 松弛 n-1 次
    for(int i=0;i<n-1;i++){
        for(auto &e:edges){
            if(dist[e.u]!=INF && dist[e.u]+e.w<dist[e.v]){
                dist[e.v]=dist[e.u]+e.w;
            }
        }
    }
    // 检测负环
    for(auto &e:edges){
        if(dist[e.u]!=INF && dist[e.u]+e.w<dist[e.v]){
            return 0;
        }
    }
    return 1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>src;
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        edges.push_back({u,v,w});

    }

    if(bellmanFord()){
        for(int i=1;i<=n;i++){
            cout<<(dist[i]==INF?-1:dist[i])<<' ';
        }
        cout<<'\n';
    }else cout<<"YES\n";//存在负环
    return 0;
}
/*
 * 【关键点】
 * 1. 边存储为结构体数组，便于遍历
 * 2. 外层循环 n-1 次（最短路最多经过 n-1 条边）
 * 3. 松弛时检查 dist[e.u]!=INF 防止溢出
 * 4. 第 n 次循环用于检测负环
 * 
 * 【原理】
 * - 正常图中，从源点出发的最短路最多经过 n-1 条边
 * - 如果第 n 次循环还能松弛边，说明存在负环
 * 
 * 【注意事项】
 * - [ ] 初始化 dist[src]=0，其余为 INF
 * - [ ] 松弛次数必须是 n-1（不是 n）
 * - [ ] 检查溢出：dist[e.u]!=INF
 * - [ ] 时间复杂度 O(VE) 较高，不适合大图
 * - [ ] 若图不连通，未到达的点应输出 INF 或 -1
 */
