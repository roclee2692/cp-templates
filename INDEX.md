# 📋 模板快速索引

## 🔍 按算法名称查找

### 图论
| 算法 | 文件 | 周数 | 难度 |
|------|------|------|------|
| Dijkstra | `01_graph_basic/dijkstra.cpp` | Week 1 | ⭐⭐ |
| SPFA | `01_graph_basic/spfa.cpp` | Week 1 | ⭐⭐ |
| Floyd | `01_graph_basic/floyd.cpp` | Week 1 | ⭐⭐ |
| Kruskal | `01_graph_basic/kruskal.cpp` | Week 1 | ⭐⭐ |
| Prim | `01_graph_basic/prim.cpp` | Week 1 | ⭐⭐ |
| DSU | `01_graph_basic/dsu.cpp` | Week 1 | ⭐ |
| Tarjan (SCC) | `05_graph_advanced/scc.cpp` | Week 5 | ⭐⭐⭐ |
| 割点 | `05_graph_advanced/articulation_point.cpp` | Week 5 | ⭐⭐⭐ |
| 桥 | `05_graph_advanced/bridge.cpp` | Week 5 | ⭐⭐⭐ |
| 拓扑排序 | `05_graph_advanced/topological_sort.cpp` | Week 5 | ⭐⭐ |

### 字符串
| 算法 | 文件 | 周数 | 难度 |
|------|------|------|------|
| KMP | `02_string/kmp.cpp` | Week 2 | ⭐⭐ |
| Hash | `02_string/hash.cpp` | Week 2 | ⭐⭐ |
| Trie | `02_string/trie.cpp` | Week 2 | ⭐⭐ |
| AC 自动机 | `02_string/ac_automaton.cpp` | Week 2 | ⭐⭐⭐ |
| AC 自动机高级 | `02_string/ac_automaton_advanced.cpp` | Week 2 | ⭐⭐⭐ |

### 数据结构
| 算法 | 文件 | 周数 | 难度 |
|------|------|------|------|
| 树状数组基础 | `03_data_structure/fenwick_basic.cpp` | Week 3 | ⭐⭐ |
| 树状数组区间 | `03_data_structure/fenwick_range.cpp` | Week 3 | ⭐⭐ |
| 线段树 | `03_data_structure/segment_tree.cpp` | Week 3 | ⭐⭐⭐ |
| 线段树乘法 | `03_data_structure/segment_tree_mul.cpp` | Week 3 | ⭐⭐⭐ |
| LCA 倍增 | `03_data_structure/lca_binary_lifting.cpp` | Week 3 | ⭐⭐⭐ |
| 树链剖分 | `03_data_structure/hld.cpp` | Week 3 | ⭐⭐⭐⭐ |

### 数论
| 算法 | 文件 | 周数 | 难度 |
|------|------|------|------|
| 快速幂 | `04_number_theory/fast_pow.cpp` | Week 4 | ⭐ |
| exgcd | `04_number_theory/exgcd.cpp` | Week 4 | ⭐⭐ |
| 模逆元 | `04_number_theory/mod_inverse.cpp` | Week 4 | ⭐⭐ |
| CRT | `04_number_theory/crt.cpp` | Week 4 | ⭐⭐ |
| 组合数基础 | `04_number_theory/combinatorics_basic.cpp` | Week 4 | ⭐ |
| Lucas 定理 | `04_number_theory/lucas.cpp` | Week 4 | ⭐⭐⭐ |
| Catalan | `04_number_theory/catalan.cpp` | Week 4 | ⭐⭐ |

### 动态规划
| 算法 | 文件 | 周数 | 难度 |
|------|------|------|------|
| 状压 DP | `06_dynamic_programming/bitmask_dp.cpp` | Week 6 | ⭐⭐ |
| TSP (集合 DP) | `06_dynamic_programming/set_dp_tsp.cpp` | Week 6 | ⭐⭐⭐ |
| 矩阵 DP | `06_dynamic_programming/matrix_exp_dp.cpp` | Week 6 | ⭐⭐⭐ |
| 树形 DP | `06_dynamic_programming/tree_dp.cpp` | Week 6 | ⭐⭐⭐ |

---

## ⏰ 按学习顺序

### Week 1：图论基础
```
Day 1: dijkstra.cpp → Codeforces: [1, 1]
Day 2: spfa.cpp → Codeforces: [1, 1], [2, 1]
Day 3: floyd.cpp → Codeforces: [1, 2], [2, 1]
Day 4: dsu.cpp, kruskal.cpp → Codeforces: [1, 3], [2, 1], [2, 3]
Day 5: 复习 + 蓝桥题
```

### Week 2：字符串
```
Day 1: kmp.cpp → Codeforces
Day 2: hash.cpp → Codeforces
Day 3: trie.cpp → Codeforces
Day 4: ac_automaton.cpp → Codeforces
Day 5: ac_automaton_advanced.cpp → Codeforces (fail 树)
```

### Week 3：数据结构
```
Day 1: fenwick_basic.cpp → Codeforces
Day 2: fenwick_range.cpp → Codeforces
Day 3: segment_tree.cpp → Codeforces
Day 4: segment_tree_mul.cpp → Codeforces
Day 5: lca_binary_lifting.cpp → Codeforces
Day 6: hld.cpp → Codeforces
Day 7: 综合题
```

### Week 4：数论
```
Day 1: fast_pow.cpp, exgcd.cpp → Codeforces
Day 2: mod_inverse.cpp → Codeforces
Day 3: crt.cpp → Codeforces
Day 4: combinatorics_basic.cpp, lucas.cpp → Codeforces
Day 5: catalan.cpp → Codeforces
```

### Week 5：图论进阶
```
Day 1: topological_sort.cpp → Codeforces
Day 2-3: 割点、桥、SCC → Codeforces
Day 4-5: 缩点 + DAG DP → 蓝桥题
```

### Week 6：DP + 综合
```
Day 1-2: bitmask_dp.cpp, set_dp_tsp.cpp → Codeforces
Day 3-4: matrix_exp_dp.cpp, tree_dp.cpp → Codeforces
Day 5-7: 模拟赛（蓝桥真题/CF Div.2）
```

---

## 📝 使用建议

### 空屏复现
1. 打开对应 `.cpp` 文件
2. **关闭文件**，在空白编辑器中自己写
3. 对比找出差异
4. 理解差异原因

### 模板题提交
1. 复制模板代码
2. 改动输入/输出格式适应题目
3. 在洛谷/CF 提交
4. 记录 AC 时间

### 延展题练习
1. 去 CF 搜索对应标签
2. 筛选 1600-1900 分题目
3. 识别需要哪个模板
4. 自己写解法（不复制）
5. 提交前手工验证边界

---

## 🎯 检查清单

完成每个模板后打勾：

- [ ] **Week 1**
  - [ ] Dijkstra - AC 于洛谷 P3371
  - [ ] SPFA - AC 于洛谷 P3385
  - [ ] Floyd - AC 于洛谷 P1119
  - [ ] Kruskal - AC 于洛谷 P3366
  - [ ] Prim - AC 于洛谷 P3366
  - [ ] DSU - AC 于洛谷 P3367

- [ ] **Week 2**
  - [ ] KMP - AC 于洛谷 P3375
  - [ ] Hash - AC 于洛谷 P3370
  - [ ] Trie - AC 于洛谷 P2580
  - [ ] AC 自动机 - AC 于洛谷 P3796
  - [ ] AC 自动机高级 - AC 于洛谷 P5357

- [ ] **Week 3**
  - [ ] 树状数组基础 - AC 于洛谷 P3374
  - [ ] 树状数组区间 - AC 于洛谷 P3368
  - [ ] 线段树 - AC 于洛谷 P3372
  - [ ] 线段树乘法 - AC 于洛谷 P3373
  - [ ] LCA - AC 于洛谷 P3379
  - [ ] HLD - AC 于洛谷 P3384

- [ ] **Week 4**
  - [ ] 快速幂 - AC 于洛谷 P1226
  - [ ] exgcd - AC 于洛谷 P1082
  - [ ] 模逆元 - AC 于洛谷 P3811
  - [ ] CRT - AC 于洛谷 P1495
  - [ ] Lucas - AC 于洛谷 P3807
  - [ ] Catalan - AC 于洛谷 P5191

- [ ] **Week 5**
  - [ ] 拓扑排序 - AC 于洛谷 P4017
  - [ ] 割点 - AC 于洛谷 P3388
  - [ ] 桥 - AC 于洛谷 P1656
  - [ ] SCC - AC 于洛谷 P3387

- [ ] **Week 6**
  - [ ] 状压 DP - AC 于洛谷 P1879
  - [ ] TSP DP - AC 于洛谷 P1171
  - [ ] 矩阵 DP - AC 于 CF
  - [ ] 树形 DP - AC 于蓝桥题

---

## 💬 遇到问题？

1. **模板不会写？** → 看代码注释和关键点部分
2. **提交总是 WA？** → 检查"提交前检查"清单
3. **超时？** → 确认时间复杂度是否符合题目约束
4. **逻辑错误？** → 用小样例手工验证

---

**加油！相信这 6 周的系统训练能让你的竞赛编程能力突飞猛进！💪**
