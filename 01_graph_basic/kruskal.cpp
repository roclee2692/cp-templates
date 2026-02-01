/*
 * 【Kruskal 算法】- 最小生成树（依赖并查集）
 * 
 * 时间复杂度：O(E log E)（边排序主导）
 * 空间复杂度：O(V + E)
 * 
 * 适用场景：
 *   - 求最小生成树（权值最小）
 *   - 稀疏图更优
 *   - 边权较小（容易排序）
 * 
 * 模板题：洛谷 P3366 - 【模板】最小生成树
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct DSU{
    vector<ll> p,r;//parent rank
    DSU(ll n=0):p(n+1),r(n+1)
    { iota(p.begin(),p.end(),0); };//注意这里括号内外都有分号 少了编辑器不一定能查出来
    ll find(ll x){    // 找根节点（路径压缩）
        if(p[x]!=x) p[x]=find(p[x]);
        return p[x];
    }
    // 合并两个集合（按秩合并）
    bool unite(ll a,ll b){
        a=find(a); b=find(b);
        if(a==b) return 0;// 已在同一集合
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;//指向大的
        if(r[a]==r[b]) r[a]++;//还有相等的可能性 直接增加a树的秩
        return 1;
    }
};
struct Edge{
    ll u,v,w;
    bool operator<(Edge const& o)const{
        return w<o.w;// 当调用 e1 < e2 时：实际调用 e1.operator<(e2)
    }
};
// Kruskal 最小生成树函数：
// 参数：
//   n   - 图的顶点数（编号从 1 到 n）
//   E   - 输入的所有边列表
//   mst - 存放生成树边的容器
// 返回值：最小生成树的总权重
ll n,m;
vector<Edge> E;
vector<Edge> mst;
ll kruskal(bool mintree=1){//加边法
     mst.clear();          // ← 保证干净
    if(mintree)
    sort(E.begin(),E.end());// 1. 按权重升序排序所有边
    else sort(E.rbegin(),E.rend());// 降序 ⇒ 最大生成树
     // 2. 初始化并查集
     DSU dsu(n);
     ll total=0;// MST 权重累加
 // 3. 遍历每条边，若连接的两点不连通则合并并加入 MST
    for(auto &e:E){
        if(dsu.unite(e.u,e.v)){
            total+=e.w;
            mst.push_back(e);
             // 若已选满 n-1 条边，可提前结束
             if((ll)mst.size()==n-1) break;
        }
    }   
    return total;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    E.reserve(m);
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        E.push_back({u,v,w});
    }
    ll ans=kruskal();
    // 输出构成 MST 的每条边
    if(mst.size()==n-1){//可能少于n-1条边 无法输出
        cout<<ans<<'\n';  // 连通，输出总权重
        // 可选：输出每条边
        // for (auto& e : mst) {
        //     cout << e.u << " " << e.v << " " << e.w << "\n";
        // }
    }else{
        cout<<"orz\n";  // 不连通
    }
  return 0;
}
/*
 * 【Kruskal 算法步骤】
 * 1. 将所有边按权值从小到大排序
 * 2. 依次考虑每条边：
 *    - 如果两端点不连通，加入这条边
 *    - 否则跳过（会形成环）
 * 3. 直到加入 n-1 条边（形成树）
 * 
 * 【为什么贪心有效？】
 * - 最小生成树的关键性质：
 *   "最小权值的边一定在某个 MST 中"
 * - 每次加入最小的未加入边，最终得到全局最优
 * 
 * 【与 Prim 的对比】
 * Kruskal:
 *   - 时间：O(E log E)
 *   - 空间：O(E)
 *   - 适合：稀疏图
 * Prim:
 *   - 时间：O((V + E) log V)（堆优化）
 *   - 空间：O(V)
 *   - 适合：稠密图
 * 
 * 【常见变体】
 * - 第 k 小生成树：需要特殊处理
 * - 带约束的 MST：限制某些边是否使用
 * - 最大生成树：改为降序排列
 * 
 * 【提交前检查】
 * - [ ] 并查集是否正确实现？
 * - [ ] 边是否按权值排序？
 * - [ ] 是否检查了连通性？
 * - [ ] 是否处理了重边和自环？
 * - [ ] 最终是否有 n-1 条边？
 */
