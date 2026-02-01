# 🚀 Competitive Programming Templates Library

> **From "Learning Repository" to "Practical Repository"** - Condensed essence of 6 weeks of competitive programming sprint. Not just knowledge records, but ability accumulation.

This is a curated template library organized by **6-week sprint plan**. Each template includes:
- **Blank-screen reproduction version**: For memory training
- **Standard template**: For submission and application
- **Common variations**: For handling special cases

---

[中文版本](README_CN.md)

---

## ⚖️ About Commercial Use

This library is under **MIT License**, which allows commercial use. **However**:

- 🙏 **If you commercialize based on this library**, please **clearly indicate the source** and **retain original author information** in your product
- 💡 **Recommended practices**:
  - Keep original author information in LICENSE file
  - Document that it's "**Based on cp-templates project**"
  - Consider linking back to original repo https://github.com/roclee2692/cp-templates

- ❌ **Discouraged practices**:
  - Copy all code and claim as original work
  - Sell without indicating source (this is "information gap exploitation")
  - This disrespects the open source community and original authors

> **Essentially, we rely on "moral constraints" rather than "legal constraints".** Honest developers will respect this; dishonest people won't follow any agreement anyway. The power of open source community lies in **trust** and **mutual respect**.

---

## 📂 Directory Structure

### Week 1: Graph Fundamentals
**Folder**: `01_graph_basic/`

| Algorithm | File | Practice Problem | Difficulty |
|-----------|------|------------------|-----------|
| Dijkstra (Heap) | `dijkstra.cpp` | Luogu P3371 | ⭐⭐ |
| SPFA (Queue) | `spfa.cpp` | Luogu P3385 | ⭐⭐ |
| Floyd (All-pairs) | `floyd.cpp` | Luogu P1119 | ⭐⭐ |
| Kruskal (MST) | `kruskal.cpp` | Luogu P3366 | ⭐⭐ |
| Prim (MST) | `prim.cpp` | Luogu P3366 | ⭐⭐ |
| DSU (Union-Find) | `dsu.cpp` | Luogu P3367 | ⭐ |

### Week 2: String Algorithms
**Folder**: `02_string/`

| Algorithm | File | Practice Problem | Difficulty |
|-----------|------|------------------|-----------|
| KMP Matching | `kmp.cpp` | Luogu P3375 | ⭐⭐ |
| String Hash | `string_hash.cpp` | Luogu P3370 | ⭐⭐ |
| Trie | `trie.cpp` | Luogu P2580 | ⭐⭐ |
| AC Automaton | `ac_automaton.cpp` | Luogu P3796 | ⭐⭐⭐ |

### Week 3: Data Structures
**Folder**: `03_data_structure/`

| Algorithm | File | Practice Problem | Difficulty |
|-----------|------|------------------|-----------|
| Fenwick Tree (BIT) | `bit.cpp` | Luogu P3374 | ⭐⭐ |
| Segment Tree | `segment_tree.cpp` | Luogu P3372 | ⭐⭐⭐ |
| LCA (Binary Lifting) | `lca.cpp` | Luogu P3379 | ⭐⭐⭐ |
| Persistent Segment Tree | `persistent_segtree.cpp` | Luogu P3380 | ⭐⭐⭐⭐ |

### Week 4: Number Theory
**Folder**: `04_number_theory/`

| Algorithm | File | Practice Problem | Difficulty |
|-----------|------|------------------|-----------|
| Fast Exponentiation | `fast_power.cpp` | Luogu P1226 | ⭐ |
| Extended Euclidean | `exgcd.cpp` | Luogu P1082 | ⭐⭐ |
| Chinese Remainder Theorem | `crt.cpp` | Luogu P1495 | ⭐⭐ |
| Sieve & Factorize | `sieve_and_factorize.cpp` | Luogu P1835 | ⭐⭐ |

### Week 5: Advanced Graph Theory
**Folder**: `05_graph_advanced/`

| Algorithm | File | Practice Problem | Difficulty |
|-----------|------|------------------|-----------|
| Topological Sort | `topo_sort.cpp` | Luogu P4017 | ⭐⭐ |
| Tarjan (SCC) | `tarjan.cpp` | Luogu P3387 | ⭐⭐⭐ |
| Bridges & Cut Vertices | `bridge_and_cutpoint.cpp` | Luogu P3388 | ⭐⭐⭐ |

### Week 6: Dynamic Programming
**Folder**: `06_dynamic_programming/`

| Algorithm | File | Practice Problem | Difficulty |
|-----------|------|------------------|-----------|
| Bitmask DP | `bitmask_dp.cpp` | Luogu P1879 | ⭐⭐ |
| Tree DP | `tree_dp.cpp` | Lanqiao | ⭐⭐⭐ |
| Matrix Power DP | `matrix_power_dp.cpp` | CF | ⭐⭐⭐ |

---

## 📚 Learning Guide

### Study Process

1. **Blank-screen Reproduction** (Mon-Wed each week)
   - Open the corresponding `.cpp` file
   - Write it from memory without looking
   - Compare with template to find differences

2. **Template Verification** (Thu each week)
   - Copy template code directly
   - Submit on Luogu/Codeforces
   - Ensure AC (Accepted)

3. **Extended Application** (Fri-Sun each week)
   - Find 1600-1900 difficulty problems on CF/Lanqiao
   - Identify which template to use
   - Modify parameters and submit

---

## 🎯 Recommended Learning Schedule

### Week 1: Graph Basics
```
Day 1: dijkstra.cpp → Luogu P3371
Day 2: spfa.cpp → Luogu P3385
Day 3: floyd.cpp → Luogu P1119
Day 4: kruskal.cpp + dsu.cpp → Luogu P3366, P3367
Day 5-7: Practice 1600-1800 difficulty graph problems
```

### Week 2-6
[Similar schedule for weeks 2-6...]

---

## 💡 Template Structure

Each template file should follow this structure:
```cpp
// Algorithm name, time complexity, use cases
// Core implementation
// Key step comments
// Simple test case
// Common variations notes
```

---

## 📊 Progress Tracking

Mark ✅ after completing each template:

- [ ] Week 1: Dijkstra, SPFA, Floyd, Kruskal, Prim, DSU
- [ ] Week 2: KMP, Hash, Trie, AC Automaton
- [ ] Week 3: Fenwick, Segment Tree, LCA, Persistent Segtree
- [ ] Week 4: Fast Pow, exgcd, CRT, Sieve
- [ ] Week 5: Topo Sort, Tarjan, Bridges & Cutpoints
- [ ] Week 6: Bitmask DP, Tree DP, Matrix Power DP

---

## 🔗 Resources

- **Luogu**: https://www.luogu.com.cn (Template problems)
- **Codeforces**: https://codeforces.com (Practice problems)
- **Lanqiao**: https://www.lanqiao.cn (Real competition problems)

---

## 💭 Philosophy: "Learning Repository" vs "Practical Repository"

This library originated from my personal "learning repository" - containing various attempts, lengthy comments, and numerous examples.

Later, I realized: **Learning repos are "broad", practical repos need to be "precise"**.

Thus, I created **cp-templates**:
- ✅ **Curated templates**: Each algorithm has 1-2 core implementations only
- ✅ **Reproducible training**: Complete path from "blank-screen" → "verification" → "application"
- ✅ **6-week sprint**: Systematic improvement with direction and rhythm

**My philosophy**:
> Competitive programming ultimately returns to "**practice**". Every algorithm learned must be writable within 24 hours, quickly identifiable and applicable in real contests. This library was created for this exact goal.

---

## 🙏 Acknowledgments

Thanks to **GitHub Copilot** for support in organization, documentation, and code review, helping me refine scattered knowledge into a systematic learning plan.

Thanks to the entire open source community, especially the problem setters on Luogu and Codeforces, who provide verification and practice platforms.

Finally, thanks for being here. Hope this library helps you 💪

---

**Good luck on your 6-week sprint! 🚀**
