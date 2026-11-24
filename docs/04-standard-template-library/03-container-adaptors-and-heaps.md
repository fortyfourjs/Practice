# Container Adaptors and Heaps: Priority Queues (std::priority_queue)

## 1. Definition
A **Priority Queue** is an abstract container adaptor designed such that its first element is always the greatest (or smallest, depending on the comparator) element among all items contained, according to strict weak ordering.

In C++, `std::priority_queue` is implemented on top of a random-access container (defaulting to `std::vector`) using the standard library's **Binary Heap** algorithms (`std::make_heap`, `std::push_heap`, `std::pop_heap`).

---

## 2. Why Does It Matter?
- **Fast Extreme Element Access**: Always retrieves the maximum (or minimum) element in $O(1)$ constant time.
- **Efficient Dynamic Updates**: Allows inserting elements and removing the top element in $O(\log N)$ logarithmic time, far superior to sorting an array repeatedly ($O(N \log N)$).
- **Core Algorithm Engine**: Used in Dijkstra's shortest path algorithm, Prim's minimum spanning tree, Huffman coding, event-driven simulations, and top-$K$ selection problems.

---

## 3. How Does It Work?

### Binary Heap Architecture
A binary heap is a complete binary tree stored compactly in a contiguous array without pointers:
- Root is at index 0.
- For an element at index $i$:
  - Left child is at index $2i + 1$
  - Right child is at index $2i + 2$
  - Parent is at index $\lfloor (i - 1) / 2 \rfloor$

```
MAX-HEAP TREE:                       ARRAY REPRESENTATION:
            [ 653 ]                  Index:  0    1    2    3    4    5
           /       \                 Value: [653, 456, 300, 120, 101, 10 ]
        [ 456 ]   [ 300 ]
       /      \   /
    [ 120 ] [ 101] [ 10 ]
```

### Max-Heap vs. Min-Heap Syntax
```cpp
#include <queue>
#include <vector>

// 1. Max-Heap (Default: Largest element at top)
std::priority_queue<int> maxHeap;

// 2. Min-Heap (Smallest element at top)
std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
```

---

## 4. Practical Examples from the Repository

### Example 1: Extracting Top Scores with Max-Heap
*(From: `Saptamana_2/ziua_9/priority_queue.cpp`)*

```cpp
#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> scoruri;
    scoruri.push(300);
    scoruri.push(10);
    scoruri.push(456);
    scoruri.push(120);
    scoruri.push(653);
    scoruri.push(101);

    // Extract top 3 highest scores:
    for (int i = 0; i < 3 && !scoruri.empty(); i++) {
        std::cout << scoruri.top() << "\n"; // Prints 653, then 456, then 300
        scoruri.pop();
    }
    return 0;
}
```

### Example 2: Finding Kth Largest Element (LeetCode 215)
*(From: `Saptamana_2/ziua_9/kth_element_easy.cpp`)*

```cpp
#include <iostream>
#include <vector>
#include <queue>

int findKthLargest(std::vector<int>& nums, int k) {
    // 1. Build Max-Heap with all elements: O(N)
    std::priority_queue<int> maxHeap(nums.begin(), nums.end());

    // 2. Pop the top k - 1 elements: (k - 1) * O(log N)
    for (int i = 0; i < k - 1; i++) {
        maxHeap.pop();
    }

    // 3. The current top is the k-th largest element!
    return maxHeap.top();
}
```

### Example 3: Supplementary Optimization — Min-Heap of Size $K$
The solution in `kth_element_easy.cpp` uses $O(N)$ memory. In high-performance systems processing massive streams where $N = 10^9$ and $K = 10$, keeping all elements in memory is impossible. Instead, maintain a **Min-Heap of size $K$**:

```cpp
int findKthLargestOptimized(const std::vector<int>& nums, int k) {
    // Min-heap keeps the K largest elements seen so far
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop(); // Discard the smallest among the top K + 1
        }
    }
    return minHeap.top(); // Time: O(N log K), Space: O(K)!
}
```

---

## 5. Operations & Complexity
| Operation | Method | Time Complexity |
| :--- | :--- | :--- |
| Inspect Top Element | `pq.top()` | $O(1)$ |
| Insert Element | `pq.push(val)` | $O(\log N)$ |
| Remove Top Element | `pq.pop()` | $O(\log N)$ |
| Bulk Construction | `priority_queue(begin, end)` | $O(N)$ (Floyd's build-heap) |

---

## 6. Common Mistakes and Pitfalls
1. **Calling `pop()` on Empty Queue**: Results in undefined behavior. Verify `!pq.empty()` first.
2. **Confusing Min-Heap Comparator**: Passing `std::greater<T>` creates a **min-heap**, not a max-heap! (Because elements where `greater(a, b)` is true are pushed deeper).
3. **Naive Approaches**: In `kth_element_noob.cpp`, popping all elements into a vector and linearly searching wastes time and defeats the purpose of the heap.

---

## 7. Quick Revision
- `std::priority_queue` provides $O(1)$ access to the extreme element and $O(\log N)$ insertion/removal.
- Implemented as a binary heap inside a contiguous array.
- Default is a Max-Heap; use `std::greater<T>` to construct a Min-Heap.
- To find the $K$-th largest element in a stream, use a Min-Heap of size $K$.

---

## 8. Repository References
- **Basic Max-Heap Extraction**: [priority_queue.cpp](../../Saptamana_2/ziua_9/priority_queue.cpp)
- **Kth Element Solution**: [kth_element_easy.cpp](../../Saptamana_2/ziua_9/kth_element_easy.cpp)
- **Naive Priority Queue Exploration**: [kth_element_noob.cpp](../../Saptamana_2/ziua_9/kth_element_noob.cpp)
