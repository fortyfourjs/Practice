# Pattern 04: Heap and Priority Queue

## Overview
The **Heap / Priority Queue** pattern is the gold standard for problems requiring repeated access to the maximum or minimum element in a collection without paying the full cost of sorting the entire dataset ($O(N \log N)$). It is particularly powerful for **Top-K elements**, stream processing, and scheduling.

---

## Problem: LeetCode 215 — Kth Largest Element in an Array
- **Problem Link**: [LeetCode 215 - Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)
- **Original Solutions**:
  - Main Solution: [kth_element_easy.cpp](../../Saptamana_2/ziua_9/kth_element_easy.cpp)
  - Naive Exploration: [kth_element_noob.cpp](../../Saptamana_2/ziua_9/kth_element_noob.cpp)
  - Concept Introduction: [priority_queue.cpp](../../Saptamana_2/ziua_9/priority_queue.cpp)
- **Main Pattern**: Max-Heap Extraction vs. Min-Heap Window

---

### Solution Strategy 1: Max-Heap (Repo Approach in `kth_element_easy.cpp`)
- **Key Insight**: Building a heap from an array takes $O(N)$ time using `std::priority_queue`'s range constructor. Popping the root $k - 1$ times discards the top $k - 1$ largest values; the next `.top()` is guaranteed to be the $k$-th largest element.
- **Implementation**:
  ```cpp
  int findKthLargest(vector<int>& nums, int k) {
      priority_queue<int> lista_numere(nums.begin(), nums.end()); // O(N) build
      for (int i = 0; i < k - 1; i++) {
          lista_numere.pop(); // Discard largest k-1 elements: (k-1) * O(log N)
      }
      return lista_numere.top();
  }
  ```
- **Complexity**:
  - **Time Complexity**: $O(N + k \log N)$.
  - **Space Complexity**: $O(N)$ to hold all numbers in the heap.

---

### Solution Strategy 2: Min-Heap of Size $K$ (Supplementary Optimal Streaming Pattern)
- **Key Insight**: If we maintain a **Min-Heap** capped at size $K$, the root will always hold the smallest of the $K$ largest elements seen so far.
- **Implementation**:
  ```cpp
  int findKthLargestMinHeap(const vector<int>& nums, int k) {
      priority_queue<int, vector<int>, greater<int>> minHeap;
      for (int x : nums) {
          minHeap.push(x);
          if (minHeap.size() > k) {
              minHeap.pop(); // Evict smallest element outside the top K
          }
      }
      return minHeap.top();
  }
  ```
- **Complexity**:
  - **Time Complexity**: $O(N \log K)$. When $K \ll N$, this is substantially faster than $O(N \log N)$.
  - **Space Complexity**: $O(K)$ auxiliary space (vastly superior for massive streams).

---

### Solution Strategy 3: Quickselect Algorithm (Supplementary Pattern)
- **Key Insight**: Based on Quicksort partitioning. Chooses a pivot and partitions elements into smaller and larger. Only recurses into the partition containing the target index.
- **Average Time**: $O(N)$, **Space**: $O(1)$ auxiliary space. (Standard C++ provides this via `std::nth_element`).

---

## Comparison Summary
| Strategy | Time Complexity | Space Complexity | Practical Best For |
| :--- | :--- | :--- | :--- |
| **Full Sort (`std::sort`)** | $O(N \log N)$ | $O(1)$ in-place | Small, static arrays |
| **Max-Heap (Repo approach)** | $O(N + k \log N)$ | $O(N)$ | Small $k$, entire array available |
| **Min-Heap (Size $k$)** | $O(N \log K)$ | $O(K)$ | **Streaming data / huge $N$** |
| **`std::nth_element` (QuickSelect)** | $O(N)$ average | $O(1)$ | High performance in-place arrays |

---

## Lessons from the Repository
In `kth_element_noob.cpp`, the author experimented with dumping the heap into a vector and linearly scanning for matches. This redundant work illustrated why using heap primitives directly (`.top()` and `.pop()`) is both cleaner and computationally superior.
