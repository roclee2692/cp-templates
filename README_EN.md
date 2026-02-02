# 🚀 Competitive Programming Templates Library

> **From "Learning Repository" to "Practical Repository"** - Condensed essence of 6-week competitive programming sprint. Not just knowledge records, but true ability accumulation.

[中文版本 (Chinese Version)](README_CN.md)

---

## ✨ Why Choose This Template Library?

### 🎯 **Competition-Focused, Covering Core Topics**
- 📊 **85%+ Coverage**: Carefully selected **core test points** from Luogu, Codeforces, Lanqiao, and other mainstream competitions
- 🔥 **High-Frequency First**: Every template is the **most frequently appearing** algorithm in real contests
- 💡 **Not "big and complete", but "precise and accurate"**: Only keep implementations that **actually get tested**

### 📝 **Every Line Manually Reviewed - Comments You Can Actually Understand**

Comparison with traditional code libraries:

| Traditional Libraries | This Library ⭐ |
|----------------------|-----------------|
| Code copied from internet, sparse comments | **Every line personally understood and annotated by author** |
| Only algorithm implementation, unclear principles | **Detailed comments on思路 and rationale for each step** |
| No warnings on error-prone parts | **Clearly mark易错 points and precautions** |
| No complexity analysis | **Time/Space complexity at beginning and end** |
| Unknown competition focus | **Mark examination frequency in different contests** |
| Abstract and hard to understand | **Use real examples to show code execution** |

#### **Code Comment Structure (included in every file):**

```cpp
/*
 * [Algorithm Name] - Functional Description
 * 
 * Time Complexity: O(...)
 * Space Complexity: O(...)
 * 
 * Use Cases: When to use this algorithm
 * Practice Problem: Luogu/CF problem number
 * Contest Frequency: ★★★★☆ (Luogu/CF/Lanqiao appearance rate)
 */

// Core implementation
// Detailed comments on every step, explaining "why write this way"

/*
 * [Key Points]
 * 1. Core idea
 * 2. Common mistakes
 * 3. Complexity analysis
 * 
 * [Common Variants]
 * - Variant 1: How to modify
 * - Variant 2: Special case handling
 * 
 * [Pre-submission Checklist]
 * - [ ] Data range matches?
 * - [ ] Edge cases handled?
 */
```

### 🛡️ **Quality Assurance**

✅ **Manual Review**: Every line written only after author **personally understands** it, not machine-generated  
✅ **Practice-Verified**: All templates **actually submitted and AC'd** on Luogu/CF  
✅ **Understanding First**: Comments aim to **ensure you understand every step**, not "still confused after reading"  
✅ **Continuously Updated**: **Dynamically adjusted** based on latest competition problems

---

## 📦 Library Organization

Organized by **6-week sprint plan**, each template includes:
- ✅ **Detailed commented version**: Every step annotated (for learning)
- ✅ **Streamlined version**: Removed comments (for fast copying in contests)
- ✅ **Standard template**: Verified on Luogu/CF
- ✅ **Common variants**: Modifications for special cases

---

## ⚖️ About Commercial Use

This library uses **MIT License**, allowing commercial use. **However**:

- 🙏 **If commercializing based on this library**, please **clearly credit source** and **retain original author info**
- 💡 **Recommended**:
  - Keep original author info in LICENSE
  - Document "**Based on cp-templates project**"
  - Link back to https://github.com/roclee2692/cp-templates

- ❌ **Discouraged**:
  - Copy all code claiming as original work
  - Sell without attribution ("information gap exploitation")
  - Disrespects open source community

> **We rely on "moral constraints" not "legal constraints".** Honest developers respect this; dishonest won't follow any agreement. Open source power lies in **trust** and **mutual respect**.

---

## 📂 Complete Directory Structure

```
cp-templates/
├── 📁 01_graph_basic/              [Week 1: Graph Basics] 11 templates
│   ├── dijkstra.cpp               ⭐⭐⭐⭐⭐ Single-source shortest path (heap)
│   ├── spfa.cpp                   ⭐⭐⭐⭐  Negative weight shortest path
│   ├── bellman-ford.cpp           ⭐⭐⭐   Negative weight/cycle detection
│   ├── floyd.cpp                  ⭐⭐⭐⭐  All-pairs shortest path
│   ├── johnson.cpp                ⭐⭐    Mixed shortest path optimization
│   ├── dsu.cpp                    ⭐⭐⭐⭐⭐ Union-Find (path compression + rank)
│   ├── kruskal.cpp                ⭐⭐⭐⭐  Minimum Spanning Tree
│   ├── Prim堆优化版.cpp           ⭐⭐⭐   MST (dense graph)
│   ├── 01BFS.cpp                  ⭐⭐⭐   0-1 BFS
│   ├── 差分约束.cpp               ⭐⭐    Difference constraints
│   └── dijkstra.exe               (compiled artifact)
│
├── 📁 02_string/                   [Week 2: String Algorithms] 8 templates
│   ├── kmp.cpp                    ⭐⭐⭐⭐⭐ Single pattern matching
│   ├── string_hash.cpp            ⭐⭐⭐⭐⭐ String hashing (double hash)
│   ├── 字符串哈希.cpp             ⭐⭐⭐⭐  Hash (Chinese version)
│   ├── trie.cpp                   ⭐⭐⭐⭐  Trie (detailed comments)
│   ├── trie无详细注释版.cpp       ⭐⭐⭐⭐  Trie (streamlined)
│   ├── ac_automaton.cpp           ⭐⭐⭐⭐  AC Automaton (detailed)
│   ├── ac_automaton无详细注释版.cpp ⭐⭐⭐ AC Automaton (streamlined)
│   └── AC 自动机.cpp              ⭐⭐⭐⭐  Multi-pattern matching
│
├── 📁 03_data_structure/           [Week 3: Data Structures] 6 templates
│   ├── bit.cpp                    ⭐⭐⭐⭐⭐ Fenwick Tree (BIT)
│   ├── segment_tree.cpp           ⭐⭐⭐⭐⭐ Segment Tree (lazy propagation)
│   ├── lca.cpp                    ⭐⭐⭐⭐  LCA (binary lifting)
│   ├── persistent_segtree.cpp     ⭐⭐⭐   Persistent Segment Tree
│   ├── heavy_light_decomposition.cpp ⭐⭐⭐ Heavy-Light Decomposition
│   └── binary_search_answer.cpp   ⭐⭐⭐⭐  Binary search on answer
│
├── 📁 04_number_theory/            [Week 4: Number Theory] 6 templates
│   ├── fast_power.cpp             ⭐⭐⭐⭐⭐ Fast exponentiation
│   ├── exgcd.cpp                  ⭐⭐⭐⭐  Extended Euclidean
│   ├── crt.cpp                    ⭐⭐⭐   Chinese Remainder Theorem
│   ├── sieve_and_factorize.cpp    ⭐⭐⭐⭐  Prime sieve + factorization
│   ├── lucas.cpp                  ⭐⭐⭐   Lucas Theorem (combinatorics mod)
│   └── catalan.cpp                ⭐⭐    Catalan numbers
│
├── 📁 05_graph_advanced/           [Week 5: Advanced Graph] 5 templates
│   ├── topo_sort.cpp              ⭐⭐⭐⭐  Topological sort
│   ├── tarjan.cpp                 ⭐⭐⭐⭐  Strongly Connected Components
│   ├── bridge_and_cutpoint.cpp    ⭐⭐⭐   Bridges & Cut vertices
│   ├── dinic.cpp                  ⭐⭐⭐⭐  Maximum flow (Dinic)
│   └── mcmf.cpp                   ⭐⭐    Min-cost max-flow
│
├── 📁 06_dynamic_programming/      [Week 6: Dynamic Programming] 6 templates
│   ├── bitmask_dp.cpp             ⭐⭐⭐⭐⭐ Bitmask DP
│   ├── tree_dp.cpp                ⭐⭐⭐⭐  Tree DP
│   ├── matrix_power_dp.cpp        ⭐⭐⭐   Matrix exponentiation DP
│   ├── cdq_divide_conquer.cpp     ⭐⭐    CDQ divide & conquer
│   ├── convex_hull.cpp            ⭐⭐    Convex hull optimization
│   └── bitmask_dp.exe             (compiled artifact)
│
├── 📄 README.md                    Main entrance (bilingual navigation)
├── 📄 README_CN.md                 Complete Chinese guide
├── 📄 README_EN.md                 Complete English guide (this file)
├── 📄 FAQ.md                       Frequently Asked Questions
├── 📄 LICENSE                      MIT Open source license
└── 📄 .gitignore                   Git ignore config

Total: 42 core templates | 6 modules | 85%+ competition coverage
```

### 🔥 **Template Frequency Legend**
- ⭐⭐⭐⭐⭐ **Must-know**: Appears in almost every contest (Dijkstra, BIT, Fast Power, etc.)
- ⭐⭐⭐⭐ **High-frequency**: Essential for Div.2/Provincial (KMP, Segment Tree, Tarjan, etc.)
- ⭐⭐⭐ **Mid-frequency**: Common in advanced problems (Persistent Segtree, HLD, Lucas, etc.)
- ⭐⭐ **Low-frequency**: Specific scenarios (MCMF, Johnson, etc.)

---

## 📚 Learning Guide

### Study Process

1. **Detailed Version Study** (Week 1-3)
   - Open **detailed commented version** (e.g., `trie.cpp`)
   - Understand每line comment
   - Try blank-screen reproduction (write without looking)
   - Compare differences, understand common mistakes

2. **Streamlined Version Practice** (Week 4-6)
   - Use **streamlined version** (e.g., `trie无详细注释版.cpp`)
   - Quick copy-paste in contests
   - Template verification: Submit on Luogu/CF, ensure AC

3. **Extended Application** (Every weekend)
   - Practice CF 1600-1900 difficulty problems
   - Identify which template to use
   - Modify parameters based on problem requirements

---

## 🎯 Recommended Learning Schedule

### Week 1: Graph Basics (Must-know Algorithms)
```
Day 1-2: dijkstra.cpp + dsu.cpp → Luogu P3371, P3367
Day 3: spfa.cpp / bellman-ford.cpp → Luogu P3385
Day 4: floyd.cpp → Luogu P1119
Day 5: kruskal.cpp → Luogu P3366
Day 6-7: CF 1600-1800 graph problems (shortest path + MST)
```

### Week 2: Strings (High-frequency Topics)
```
Day 1: kmp.cpp → Luogu P3375
Day 2: string_hash.cpp → Luogu P3370
Day 3: trie.cpp → Luogu P2580
Day 4-5: ac_automaton.cpp → Luogu P3796
Day 6-7: CF string problems
```

### Week 3: Data Structures (Core Tools)
```
Day 1: bit.cpp → Luogu P3374
Day 2-3: segment_tree.cpp → Luogu P3372
Day 4: lca.cpp → Luogu P3379
Day 5: binary_search_answer.cpp → Mixed problems
Day 6-7: Tree problems practice
```

### Week 4: Number Theory (Essential Techniques)
```
Day 1: fast_power.cpp + exgcd.cpp → Luogu P1226, P1082
Day 2: crt.cpp → Luogu P1495
Day 3: sieve_and_factorize.cpp → Prime-related problems
Day 4: lucas.cpp → Luogu P3807
Day 5-7: CF number theory problems
```

### Week 5: Advanced Graph (Score Booster)
```
Day 1: topo_sort.cpp → Luogu P4017
Day 2-3: tarjan.cpp → Luogu P3387
Day 4: bridge_and_cutpoint.cpp → Luogu P3388
Day 5: dinic.cpp → Luogu P3376 (max flow)
Day 6-7: CF advanced graph problems
```

### Week 6: DP (Comprehensive Skills)
```
Day 1-2: bitmask_dp.cpp → Luogu P1879
Day 3: tree_dp.cpp → Luogu P2015
Day 4: matrix_power_dp.cpp → CF DP problems
Day 5-7: Full mock contest (Lanqiao/CF Div.2)
```

---

## 💡 Pre-submission Checklist

Before every submission:

- [ ] **Data types**: int/long long match problem range?
- [ ] **Array size**: Allocated enough (usually n+7 or 2*n)?
- [ ] **Initialization**: dist[] / vis[] / dp[] correctly initialized?
- [ ] **Edge cases**: Handled n=0, n=1, etc.?
- [ ] **Time complexity**: Within limit (usually 10^8 operations)?
- [ ] **Space complexity**: Within memory limit (usually 256MB)?
- [ ] **Input/Output**: Format exactly matches problem?

---

## 🔗 Recommended Resources

### Online Judges
- **Luogu**: https://www.luogu.com.cn - Chinese problem set, rich templates
- **Codeforces**: https://codeforces.com - International contests, rated difficulty
- **Lanqiao**: https://www.lanqiao.cn - Chinese algorithm contests

### Learning Materials
- **OI Wiki**: https://oi-wiki.org - Algorithm encyclopedia
- **CP-Algorithms**: https://cp-algorithms.com - English algorithm tutorials
- **Competitive Programming** (book) - By Steven & Felix Halim

---

## 💭 Design Philosophy: "Learning Repository" vs "Practical Repository"

This library originated from my personal "learning repository" - containing various attempts, lengthy comments, numerous examples.

**I realized**: Learning repos are "broad", practical repos need to be "precise".

Thus created **cp-templates**:
- ✅ **Curated core**: Each algorithm keeps only 1-2 core implementations  
- ✅ **Detailed comments**: Every line written only after personal understanding
- ✅ **Practice-oriented**: Complete path from "understand" → "reproduce" → "apply"
- ✅ **Systematic improvement**: 6-week sprint with direction and rhythm

**Core Philosophy**:
> Competitive programming ultimately returns to "**practice**". Every algorithm must be writable within 24 hours, quickly identifiable and applicable in real contests. This library was created for this exact goal.

---

## 🙏 Acknowledgments

Thanks to **GitHub Copilot** for support in organization and documentation, helping refine scattered knowledge into a systematic learning plan.

Thanks to open source contributors, especially problem setters on Luogu and Codeforces, providing platforms for verification and practice.

Finally, thanks for your attention. Hope this library helps you go further in competitive programming 💪

---

**Good luck on your 6-week sprint! 🚀**
