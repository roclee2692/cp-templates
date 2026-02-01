/*
 * 【Prim 算法】- 最小生成树（堆优化版）
 * 
 * 时间复杂度：O((V + E) log V)
 * 空间复杂度：O(V + E)
 * 
 * 适用场景：
 *   - 求最小生成树（权值最小）
 *   - 稠密图更优
 *   - 需要逐步构建生成树
 * 
 * 模板题：洛谷 P3366 - 【模板】最小生成树
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(1LL<<60);
using pll=pair<ll,ll>;
// Prim（堆优化版）最小生成树模板 —— 全局变量 + 详细注释 + 健壮性检查
// 说明：
//  1. 点编号默认 1~n，图为无向加权连通图（若不连通会返回 -1）。
//  2. 采用邻接表 + 小根堆，时间复杂度 O(m log n)。
//  3. 全局保存生成树边 mst，权值和为 prim() 的返回值。
ll n,m;
vector<vector<pll>> adj;  // 邻接表：adj[u] = {(v, w), ...}

struct Edge{
    ll u,v,w;
};
// emplace_back(pre[u], u, d) 即可正常工作
vector<Edge> mst;  
// Prim 相关全局辅助数组

vector<ll> dist,pre; // 每个点到当前生成树的最小边权   pre[v] = 把 v 加入 MST 时连接的父节点
// Prim：返回 MST 权值，不连通返回 -1
ll prim(ll src=1){//加点法
  dist.assign(n+1,INF);
  pre.assign(n+1,-1);
  mst.clear();
  priority_queue<pll,vector<pll>,greater<pll> > pq;
  dist[src]=0;
  pq.emplace(0,src);
  ll total=0,cnt=0;
  while(!pq.empty()){
    auto p=pq.top();pq.pop();
    ll d=p.first,u=p.second;
    if(d>dist[u]) continue;
    total+=d;
     // 只有当 pre[u]!=-1（即真正加入一条边）时才自增 cnt
        if(pre[u] != -1){
            // 保持 struct edge 不变
            mst.push_back({ pre[u], u, d });
  // 注意：使用 emplace_back 时需 struct 提供匹配的构造函数，
  //否则可改用 push_back({…}) 进行列表初始化，避免编译错误。
            cnt++;    // 现在 cnt 记录的是边数
        }
    //cnt++;// 注意：cnt 记录的是加入 MST 的节点数，
    //连通性应检查 cnt==n（节点数），而非 cnt==n-1（边数）
    for(auto &e:adj[u]){
      ll v=e.first,w=e.second;
      if(w<dist[v]){
        dist[v]=w;
        pre[v]=u;
        pq.emplace(dist[v],v);
      }
    }
  }
  return cnt==n-1 ?total:-1;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    adj.assign(n+1,{});
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    ll ans=prim();
    if(ans==-1){
        cout<<"orz\n";  // 不连通
    }else{
        cout<<ans<<'\n';
        // 可选：输出每条边
        // for(auto &e:mst) cout<<e.u<<" "<<e.v<<" "<<e.w<<"\n";
    }
    return 0;
}

/*
 * 【Prim 算法步骤】
 * 1. 从起点开始，初始化dist[src]=0
 * 2. 每次选择dist最小且未加入MST的节点u
 * 3. 将u加入MST，更新u的邻居到MST的最短边
 * 4. 重复直到所有节点加入（n-1条边）
 * 
 * 【为什么贪心有效？】
 * - 切分定理（Cut Property）：
 *   "连接两个连通分量的最小边一定在MST中"
 * - Prim每次选择最小的连接边，保证全局最优
 * 
 * 【与 Kruskal 的对比】
 * Prim:
 *   - 时间：O((V + E) log V)（堆优化）
 *   - 空间：O(V + E)
 *   - 适合：稠密图
 *   - 特点：逐点扩展
 * Kruskal:
 *   - 时间：O(E log E)
 *   - 空间：O(V + E)
 *   - 适合：稀疏图
 *   - 特点：逐边添加
 * 
 * 【常见优化】
 * - 斐波那契堆：降至O(E + V log V)，但常数大
 * - 邻接矩阵版本：适合V²级别边数的稠密图
 * - 起点选择：从度数大的点开始可能更快
 * 
 * 【提交前检查】
 * - [ ] 邻接表是否正确构建？
 * - [ ] 堆中是否有过时状态检查？
 * - [ ] 是否检查了连通性（cnt==n-1）？
 * - [ ] dist初始化是否为INF？
 * - [ ] 边权是否可能溢出？
 */
