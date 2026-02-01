/*
 * 【Johnson 算法】- 多源最短路径（支持负权边）
 * 
 * 时间复杂度：O(V*E + V^2*log V) ≈ O(VE + V^2*log V)
 * 空间复杂度：O(V^2)
 * 
 * 适用场景：
 *   - 稀疏图多源最短路
 *   - 支持负权边（无负环）
 *   - n 不超过 500
 * 
 * 模板题：洛谷 P1119 - 灾后重建
 */

// 势能转化的本质：
// 给每个节点一个"高度"h[v]
// 边权 = 原权重 + 起点高度 - 终点高度
// 这样做既保持了最短路性质，又消除了负权边
// w'(u,v) = w(u,v) + h[u] - h[v]
//        原权重  + 势能差

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(ll)1e18;
using pll=pair<ll,ll>;
const int XN=1e3+7;
int n,m;
vector<pll> adj[XN];
ll dist[XN][XN];// dist[s][t]: 最终最短距离
ll h[XN];  // 势能
// 1. Johnson 重加权：多源全对全最短路（有向图，允许负权但无负环）
// 返回 false 表示存在负环，true 表示成功并填充 dist 矩阵
// Bellman-Ford 重新标号，计算势函数 h[]
// 1) Bellman–Ford 在超源 0 上求势能 h[1..n]
// * 【Bellman-Ford 算法】- 单源最短路径（支持负权边）
bool bellmanFord(){
  vector<ll> d(n+2,INF);
  d[0]=0;
   // 从虚拟源点 0 连向所有点，权重 0
   for(int i=1;i<=n;i++){
     adj[0].push_back({i,0});//出度 储存指向谁
   }
    // 松弛 n 次
   for(int i=0;i<n;i++){//多了个虚拟节点 之前n-1次 松弛 现在松弛n次
       for(int u=0;u<=n;u++){//外层控制轮次 内层正常遍历n+1个点
          if(d[u]==INF) continue;
          for(auto &[v,w]:adj[u]){
              if(d[u]+w<d[v]) d[v]=d[u]+w;
          }
       }
   }
    // 检测负环  只要原内层
    for(int u=0;u<=n;u++){//由于存在虚拟节点0 所有对点的松弛遍历全都要从0开始
        if(d[u]==INF) continue;
        for(auto &[v,w]:adj[u]){
            if(d[u]+w<d[v]) return 0;
        }
    }
//如果程序能继续向下进行则必须满足收敛状态：无法再进行任何松弛操作
//不存在d[u]+w<d[v] 则 d[u]+w>=d[v]
//既有 d[u]-d[v]+w>=0
//dist[v] ≤ dist[u] + w(u,v)  // 对所有边都成立
    for(int i=1;i<=n;i++) h[i]=d[i];
// Bellman-Ford计算h[i] = dist[0→i]的单源最短距离
// h[i] = 从虚拟源点0到节点i的最短距离
    //让暴力求出的单源最短路径作为从0到i的势能
    return 1;
}
// Dijkstra 计算从 src 到所有点的最短路
void dijkstra(int src){
    priority_queue<pll,vector<pll>,greater<pll>> pq;
    vector<ll> d(n+1,INF);
    d[src]=0;
    pq.push({0,src});
    
    while(!pq.empty()){
        auto [d_u,u]=pq.top();pq.pop();
        if(d_u>d[u]) continue;
        
        for(auto &[v,w]:adj[u]){
            // 转化边权：w' = w + h[u] - h[v]  h[0]-h[v]
            ll nw=w+h[u]-h[v];
            if(d[u]+nw<d[v]){
                d[v]=d[u]+nw;
                pq.push({d[v],v});
            }
        }
    }
    
    // 转化回原始距离
    for(int i=1;i<=n;i++){
        dist[src][i]=(d[i]==INF?INF:d[i]+h[i]-h[src]);//h[v]-h[0]
    }
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;ll w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    
    if(!bellmanFord()){
        cout<<"YES\n";  // 存在负环
        return 0;
    }
    
    for(int i=1;i<=n;i++) dijkstra(i);
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<(dist[i][j]==INF?-1:dist[i][j]);
            if(j<n) cout<<' ';
        }
        cout<<'\n';
    }
    
    return 0;
}
/*
 * 【关键点】
 * 1. 第一步：使用 Bellman-Ford 计算势函数 h[]
 * 2. 第二步：对每个源点使用 Dijkstra（用势函数重新标号）
 * 3. 转化公式：w' = w + h[u] - h[v]（保证非负）
 * 4. 最终距离需要转化回原始值：dist = d + h[v] - h[src]
 * 
 * 【原理】
 * - Bellman-Ford 检测负环并计算势函数
 * - 势函数使得所有边权变非负
 * - 再用 Dijkstra 计算最短路
 * 
 * 【注意事项】
 * - [ ] 虚拟源点 0 必须连向所有点，权重为 0
 * - [ ] 势函数转化公式不能错
 * - [ ] 最终距离转化时 h[src] 的符号
 * - [ ] 检查是否存在负环（返回）
 * - [ ] adj[0] 在 Bellman-Ford 中才添加（避免重复）
 * - [ ] 时间复杂度：O(VE + V^2 log V)，适合稀疏图
 */