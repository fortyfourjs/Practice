# Pattern 05: Binary Search and Boyer-Moore Voting

## Overview
This pattern covers two high-efficiency algorithmic strategies:
1. **Binary Search**: Logarithmic $O(\log N)$ search over sorted spaces using STL bounds (`std::lower_bound`, `std::upper_bound`).
2. **Boyer-Moore Voting Algorithm**: A specialized linear $O(N)$ time and $O(1)$ space algorithm that finds a majority element ($\text{count} > \lfloor N / 2 \rfloor$) by pair-wise cancellation.

---

## Problem: LeetCode 169 — Majority Element
- **Problem Link**: [LeetCode 169 - Majority Element](https://leetcode.com/problems/majority-element/)
- **Original Solutions**:
  - Hash Map Approach: [nr_majoritar.cpp](../../Saptamana_2/ziua_7/nr_majoritar.cpp)
  - Sorting & Boyer-Moore Approaches: [majority_element_leet.cpp](../../Saptamana_2/ziua_10/upper/majority_element_leet.cpp)
- **Main Patterns**: Hash Map vs. Sorting vs. Boyer-Moore Voting

---

### Approach 1: Hash Map Frequency Counter (From `nr_majoritar.cpp`)
- **Key Insight**: Count frequencies of each number in an `unordered_map<int, int>`. As soon as any frequency exceeds $\lfloor N / 2 \rfloor$, that number is the majority element.
- **Complexity**:
  - **Time Complexity**: $O(N)$ average time.
  - **Space Complexity**: $O(N)$ auxiliary space for the map.

---

### Approach 2: Sorting (From `majority_element_leet.cpp`)
- **Key Insight**: If an element appears more than $\lfloor N / 2 \rfloor$ times, after sorting, it will always occupy the middle index:
  $$\text{Index} = \lfloor N / 2 \rfloor$$
  Regardless of where the majority elements start, they span across the center of the sorted array!
- **Implementation**:
  ```cpp
  int majorityElement(std::vector<int>& nums) {
      std::sort(nums.begin(), nums.end());
      return nums[nums.size() / 2]; // O(1) retrieval after sort!
  }
  ```
- **Complexity**:
  - **Time Complexity**: $O(N \log N)$.
  - **Space Complexity**: $O(1)$ auxiliary space.

---

### Approach 3: Boyer-Moore Voting Algorithm (From `majority_element_leet.cpp`)
- **Key Insight**: Imagine a room of voters where every voter for a candidate pairs up with a voter for a rival candidate, and both leave the room. If a candidate holds more than $50\%$ of all votes, that candidate is guaranteed to have surviving voters when the room is empty!
- **Algorithm Mechanics**:
  - Maintain a `candidate` and a `counter`.
  - When `counter == 0`, assign `candidate = num`.
  - If the incoming number matches `candidate`, increment `counter++`.
  - Otherwise, decrement `counter--` (cancellation).
- **Implementation in Repo**:
  ```cpp
  int majorityElement(vector<int>& nums) {
      int counter = 0;
      int candidate = 0;
      for (int num : nums) {
          if (counter == 0) {
              candidate = num;
          }
          if (num == candidate) {
              counter++;
          } else {
              counter--;
          }
      }
      return candidate;
  }
  ```
- **Complexity**:
  - **Time Complexity**: $O(N)$ single pass.
  - **Space Complexity**: $O(1)$ constant space — optimal!

---

## Pattern: Binary Search with `std::lower_bound`
*(From: `Saptamana_2/ziua_10/upper/lower_bound.cpp`)*

When an array is sorted, we can search in $O(\log N)$ instead of $O(N)$ linear scans:
```cpp
std::vector<int> v = {1, 2, 4, 4, 4, 6, 8};

// std::lower_bound returns an iterator to the first element >= target:
auto it = std::lower_bound(v.begin(), v.end(), 4);

if (it != v.end() && *it == 4) {
    int index = it - v.begin(); // O(1) iterator distance: Index 2
    std::cout << "Element found at index: " << index << '\n';
}
```

---

## Comparison Matrix
| Technique | Time Complexity | Space Complexity | Requirements |
| :--- | :--- | :--- | :--- |
| **Hash Map** | $O(N)$ | $O(N)$ | None (works on unsorted arrays) |
| **Sorting Midpoint** | $O(N \log N)$ | $O(1)$ | Modifies array or requires copy |
| **Boyer-Moore Voting** | **$O(N)$** | **$O(1)$** | **Requires strict majority (> 50%)** |
| **Binary Search (`lower_bound`)** | $O(\log N)$ | $O(1)$ | **Requires sorted array** |
