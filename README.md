# 🚀 竞赛编程模板库

> **从"学习库"到"实战库"的蜕变** —— 这个库聚集了6周竞赛编程冲刺的核心精华。不仅是知识的记录，更是能力的沉淀。

按照 **6 周冲刺计划** 组织的模板库。每个模板都包含：
- **空屏复现版本**：用于记忆训练
- **标准模板**：用于提交和应用
- **常见变体**：处理特殊情况

---

## ⚖️ 关于商业使用

本库采用 **MIT License**，允许商业使用。**但是**：

- 🙏 **如果你基于本库进行商业化**，请在你的产品中**明确标注来源**和**保留原作者信息**
- 💡 **建议的做法**：
  - 保留 LICENSE 文件中的原作者信息
  - 在文档中说明"**基于 cp-templates 项目**"
  - 考虑在商业产品中链接回原仓库 https://github.com/roclee2692/cp-templates

- ❌ **不提倡的做法**：
  - 直接复制所有代码，声称为自己的原创
  - 不标注来源就对外宣传和出售（这是"信息差收割"）
  - 这是对开源社区和原作者的不尊重

> **本质上，我们靠的是"道德约束"而不是"法律约束"。** 诚实的开发者会尊重这一点；不诚实的人，再严格的协议也没用。开源社区的力量就在于**信任**和**互相尊重**。

---

## 📂 目录结构

### 第 1 周：图论基础 (Week 1)
**文件夹**：`01_graph_basic/`

| 模板 | 文件 | 模板题 | 难度 |
|------|------|--------|------|
| Dijkstra（堆优化） | `dijkstra.cpp` | 洛谷 P3371 | ⭐⭐ |
| SPFA（队列） | `spfa.cpp` | 洛谷 P3385 | ⭐⭐ |
| Floyd（多源最短路） | `floyd.cpp` | 洛谷 P1119 | ⭐⭐ |
| Kruskal（最小生成树） | `kruskal.cpp` | 洛谷 P3366 | ⭐⭐ |
| Prim（最小生成树） | `prim.cpp` | 洛谷 P3366 | ⭐⭐ |
| 并查集（路径压缩+秩） | `dsu.cpp` | 洛谷 P3367 | ⭐ |

---

### 第 2 周：字符串算法 (Week 2)
**文件夹**：`02_string/`

| 模板 | 文件 | 模板题 | 难度 |
|------|------|--------|------|
| KMP 字符串匹配 | `kmp.cpp` | 洛谷 P3375 | ⭐⭐ |
| 字符串哈希（Rolling Hash） | `hash.cpp` | 洛谷 P3370 | ⭐⭐ |
| Trie 树 | `trie.cpp` | 洛谷 P2580 | ⭐⭐ |
| AC 自动机 | `ac_automaton.cpp` | 洛谷 P3796 | ⭐⭐⭐ |
| Fail 树优化 | `ac_automaton_advanced.cpp` | 洛谷 P5357 | ⭐⭐⭐ |

---

### 第 3 周：数据结构 (Week 3)
**文件夹**：`03_data_structure/`

| 模板 | 文件 | 模板题 | 难度 |
|------|------|--------|------|
| 树状数组（单点修改） | `fenwick_basic.cpp` | 洛谷 P3374 | ⭐⭐ |
| 树状数组（区间修改） | `fenwick_range.cpp` | 洛谷 P3368 | ⭐⭐ |
| 线段树（区间修改+懒标记） | `segment_tree.cpp` | 洛谷 P3372 | ⭐⭐⭐ |
| 线段树（区间乘法） | `segment_tree_mul.cpp` | 洛谷 P3373 | ⭐⭐⭐ |
| LCA（倍增法） | `lca_binary_lifting.cpp` | 洛谷 P3379 | ⭐⭐⭐ |
| 树链剖分（HLD） | `hld.cpp` | 洛谷 P3384 | ⭐⭐⭐⭐ |

---

### 第 4 周：数论与组合数学 (Week 4)
**文件夹**：`04_number_theory/`

| 模板 | 文件 | 模板题 | 难度 |
|------|------|--------|------|
| 快速幂 | `fast_pow.cpp` | 洛谷 P1226 | ⭐ |
| 扩展欧几里得（exgcd） | `exgcd.cpp` | 洛谷 P1082 | ⭐⭐ |
| 模逆元（费马小定理） | `mod_inverse.cpp` | 洛谷 P3811 | ⭐⭐ |
| 中国剩余定理（CRT） | `crt.cpp` | 洛谷 P1495 | ⭐⭐ |
| 组合数（Pascal 三角形） | `combinatorics_basic.cpp` | 洛谷 P4720 | ⭐ |
| Lucas 定理 | `lucas.cpp` | 洛谷 P3807 | ⭐⭐⭐ |
| Catalan 数 | `catalan.cpp` | 洛谷 P5191 | ⭐⭐ |

---

### 第 5 周：图论进阶 (Week 5)
**文件夹**：`05_graph_advanced/`

| 模板 | 文件 | 模板题 | 难度 |
|------|------|--------|------|
| 拓扑排序（Kahn 算法） | `topological_sort.cpp` | 洛谷 P4017 | ⭐⭐ |
| 割点（Tarjan） | `articulation_point.cpp` | 洛谷 P3388 | ⭐⭐⭐ |
| 桥（Tarjan） | `bridge.cpp` | 洛谷 P1656 | ⭐⭐⭐ |
| 强连通分量（SCC） | `scc.cpp` | 洛谷 P3387 | ⭐⭐⭐ |
| 缩点 + DAG DP | `scc_dp.cpp` | 蓝桥综合题 | ⭐⭐⭐⭐ |

---

### 第 6 周：动态规划 (Week 6)
**文件夹**：`06_dynamic_programming/`

| 模板 | 文件 | 模板题 | 难度 |
|------|------|--------|------|
| 状压 DP（基础） | `bitmask_dp.cpp` | 洛谷 P1879 | ⭐⭐ |
| 集合 DP（TSP） | `set_dp_tsp.cpp` | 洛谷 P1171 | ⭐⭐⭐ |
| 矩阵快速幂 DP | `matrix_exp_dp.cpp` | CF 题 | ⭐⭐⭐ |
| 树形 DP | `tree_dp.cpp` | 蓝桥题 | ⭐⭐⭐ |

---

## 📚 使用指南

### 学习流程

1. **空屏复现** (Mon-Wed 每周)
   - 打开对应的 `.cpp` 文件
   - 不看代码，自己写一遍
   - 与模板对比找出差异

2. **模板题验证** (Thu 每周)
   - 直接复制模板代码
   - 在洛谷/CF 上提交
   - 确保 AC

3. **延展应用** (Fri-Sun 每周)
   - 去 CF 或蓝桥找对应的 1600-1900 分题
   - 识别使用哪个模板
   - 修改参数并提交

---

## 🎯 推荐学习顺序

### 第 1 周：图论基础
```
Day 1: dijkstra.cpp → 洛谷 P3371
Day 2: spfa.cpp → 洛谷 P3385
Day 3: floyd.cpp → 洛谷 P1119
Day 4: kruskal.cpp + prim.cpp → 洛谷 P3366
Day 5: dsu.cpp → 洛谷 P3367
Day 6-7: 刷 CF 1600-1800 分图论题
```

### 第 2 周：字符串算法
```
Day 1: kmp.cpp → 洛谷 P3375
Day 2: hash.cpp → 洛谷 P3370
Day 3: trie.cpp → 洛谷 P2580
Day 4: ac_automaton.cpp → 洛谷 P3796
Day 5: ac_automaton_advanced.cpp → 洛谷 P5357
Day 6-7: 刷 CF 字符串题
```

### 第 3 周：数据结构
```
Day 1-2: fenwick_basic.cpp + fenwick_range.cpp → 洛谷 P3374, P3368
Day 3: segment_tree.cpp → 洛谷 P3372
Day 4: segment_tree_mul.cpp → 洛谷 P3373
Day 5: lca_binary_lifting.cpp → 洛谷 P3379
Day 6: hld.cpp → 洛谷 P3384
Day 7: 蓝桥路径题综合
```

### 第 4 周：数论与组合数学
```
Day 1: fast_pow.cpp + exgcd.cpp → 洛谷 P1226, P1082
Day 2: mod_inverse.cpp → 洛谷 P3811
Day 3: crt.cpp → 洛谷 P1495
Day 4: combinatorics_basic.cpp + lucas.cpp → 洛谷 P3807
Day 5: catalan.cpp → 洛谷 P5191
Day 6-7: 刷 CF 数论题
```

### 第 5 周：图论进阶
```
Day 1: topological_sort.cpp → 洛谷 P4017
Day 2-3: articulation_point.cpp + bridge.cpp → 洛谷 P3388, P1656
Day 4: scc.cpp → 洛谷 P3387
Day 5: scc_dp.cpp → 蓝桥综合题
Day 6-7: CF 缩点 + DAG DP 题
```

### 第 6 周：DP 与综合实战
```
Day 1: bitmask_dp.cpp → 洛谷 P1879
Day 2: set_dp_tsp.cpp → 洛谷 P1171
Day 3: matrix_exp_dp.cpp → CF
Day 4: tree_dp.cpp → 蓝桥题
Day 5-7: 完整的模拟赛（蓝桥真题/CF Div.2）
```

---

## 💡 模板编写建议

### 每个模板文件的结构
```cpp
// 1. 头注释：算法名称、时间复杂度、适用场景
// 2. 核心代码：标准模板
// 3. 注释：关键步骤解释
// 4. 示例：简单的测试用例
// 5. 变体注释：常见变形说明
```

### 提交代码的 Checklist
- [ ] 包含所有必要的头文件
- [ ] 定义了合适的数据类型（int/long long）
- [ ] 初始化了所有数组/向量
- [ ] 处理了边界情况
- [ ] 时间复杂度符合题目要求
- [ ] 空间复杂度不超过限制

---

## 📊 进度追踪

在学完每个模板后，在对应行打 ✅：

- [ ] Week 1: Dijkstra, SPFA, Floyd, Kruskal, Prim, DSU
- [ ] Week 2: KMP, Hash, Trie, AC Automaton (基础+高级)
- [ ] Week 3: Fenwick, Segment Tree (基础+乘法), LCA, HLD
- [ ] Week 4: Fast Pow, exgcd, CRT, 组合数, Lucas, Catalan
- [ ] Week 5: 拓扑排序, 割点, 桥, SCC, 缩点DP
- [ ] Week 6: 状压 DP, 集合 DP, 矩阵 DP, 树形 DP

---

## 🔗 相关资源

- **洛谷**：https://www.luogu.com.cn (模板题验证)
- **Codeforces**：https://codeforces.com (延展题练习)
- **蓝桥杯真题**：https://www.lanqiao.cn (实战练习)

---

## 💭 "学习库" vs "实战库"

这个库最初来自我的个人"学习库"——一个包含各种尝试、注释冗长、示例众多的知识宝库。

后来，我意识到一个问题：**学习库很"宽泛"，实战库需要"精准"**。

因此，我决定创建 **cp-templates**：
- ✅ **精选的模板**：每个算法只保留 1-2 个最核心的实现
- ✅ **可复现的训练**：从"空屏复现"到"模板验证"到"延展应用"的完整学习路径
- ✅ **6 周冲刺**：不是漫无目的的积累，而是有方向、有节奏的系统提升

**我的理念**：
> 竞赛编程的学习，最终要回归"**实战**"。每周学到的算法，要能在 24 小时内快速写出来，在实战中快速识别和应用。这个库就是为了这个目标而生。

---

## 🙏 致谢

感谢 **GitHub Copilot** 在组织、文档化和代码审视方面的支持，帮助我将散落在各处的知识片段整理成了一套系统的学习方案。

也感谢所有开源社区的贡献者，特别是洛谷、Codeforces 等平台的出题者，他们为我们提供了验证和延展的舞台。

最后，感谢你在这里停留。希望这个库能帮助你 💪

---

**祝你 6 周冲刺成功！加油💪**
