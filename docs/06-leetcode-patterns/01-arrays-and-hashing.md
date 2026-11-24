# Pattern 01: Arrays and Hashing

## Overview
The **Arrays and Hashing** pattern utilizes hash tables (`std::unordered_map`) and hash sets (`std::unordered_set`) to trade space for time. By remembering elements or frequencies seen previously in $O(1)$ average time, we eliminate nested loops ($O(N^2)$) and solve lookup problems in a single $O(N)$ pass.

---

## Problem 1: LeetCode 217 — Contains Duplicate
- **Problem Link**: [LeetCode 217 - Contains Duplicate](https://leetcode.com/problems/contains-duplicate/)
- **Original Solution**: [217.leetcode_containsduplicate.cpp](../../Saptamana_1/ziua_2/217.leetcode_containsduplicate.cpp) (also explored in [vector_ex.cpp](../../Saptamana_1/ziua_2/vector_ex.cpp))
- **Main Pattern**: Sorting vs. Hash Set Lookup
- **Key Insight**: In a sorted array, any duplicates must reside adjacent to each other (`nums[i] == nums[i+1]`). Alternatively, an `unordered_set` can detect duplicates on the fly.
- **Approach in Repo**:
  1. Sort `nums` in ascending order using `std::sort`.
  2. Scan through the array with a single loop comparing each element with its neighbor.
  3. If identical, return `true`; if the loop completes without matches, return `false`.
- **Complexity**:
  - **Time Complexity**: $O(N \log N)$ due to sorting.
  - **Space Complexity**: $O(1)$ auxiliary space if sorted in-place.
- **Alternative / Supplementary Optimal Pattern**:
  Using `std::unordered_set<int>` gives $O(N)$ time and $O(N)$ space:
  ```cpp
  bool containsDuplicate(std::vector<int>& nums) {
      std::unordered_set<int> seen;
      for (int x : nums) {
          if (!seen.insert(x).second) return true; // insert().second is false if already present
      }
      return false;
  }
  ```
- **Important Lessons**: In `vector_ex.cpp`, a bug existed where `return false;` was placed inside the loop body, causing the function to terminate on the very first mismatch. Always ensure the negative return statement is outside the loop!

---

## Problem 2: LeetCode 1 — Two Sum
- **Problem Link**: [LeetCode 1 - Two Sum](https://leetcode.com/problems/two-sum/)
- **Original Solution**: [1.leetcode_twosum.cpp](../../Saptamana_1/ziua_6/1.leetcode_twosum.cpp)
- **Main Pattern**: Hash Map Complement Lookup
- **Key Insight**: For any number `x`, the required complement that sums to `target` is uniquely determined: `complement = target - x`. We can check if this complement was already encountered in $O(1)$ time using a hash map.
- **Approach in Repo**:
  The repository implemented a preliminary approach: generating a separate vector of complements, then running a nested loop ($O(N^2)$) to locate the match.
- **Complexity (Repo Implementation)**:
  - **Time Complexity**: $O(N^2)$
  - **Space Complexity**: $O(N)$
- **Optimal Single-Pass Hash Map Pattern**:
  *(Using the `unordered_map` techniques studied later in Week 2 Day 7)*:
  ```cpp
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
      std::unordered_map<int, int> numToIndex; // Value -> Index
      for (int i = 0; i < nums.size(); i++) {
          int complement = target - nums[i];
          if (numToIndex.count(complement)) {
              return {numToIndex[complement], i};
          }
          numToIndex[nums[i]] = i;
      }
      return {};
  }
  ```
  - **Optimal Time**: $O(N)$
  - **Optimal Space**: $O(N)$
- **Important Lesson**: Hash maps transform nested search loops into instantaneous constant-time lookups.

---

## Problem 3: LeetCode 242 — Valid Anagram
- **Problem Link**: [LeetCode 242 - Valid Anagram](https://leetcode.com/problems/valid-anagram/)
- **Original Solutions**: [valid_anagram.cpp](../../Saptamana_2/ziua_7/valid_anagram.cpp) and [valid_anagram_one_hashmap.cpp](../../Saptamana_2/ziua_7/valid_anagram_one_hashmap.cpp)
- **Main Pattern**: Character Frequency Counting
- **Key Insight**: Two strings are anagrams if and only if they have identical lengths and every character appears with the exact same frequency in both strings.
- **Approaches in Repo**:
  1. *Two Hash Maps*: Populate `hm_s1` and `hm_s2`, then compare maps directly (`hm_s1 == hm_s2`).
  2. *Single Hash Map*: Increment frequencies for `s1`, decrement for `s2`, and confirm all counts equal zero.
- **Complexity**:
  - **Time Complexity**: $O(N)$ where $N$ is string length.
  - **Space Complexity**: $O(1)$ auxiliary space (at most 26 lowercase English letters).
- **Important Lesson**: Passing `unordered_map` by value into helper functions creates unnecessary heap copies. Pass by `const &` or construct locally.

---

## Problem 4: LeetCode 49 — Group Anagrams
- **Problem Link**: [LeetCode 49 - Group Anagrams](https://leetcode.com/problems/group-anagrams/)
- **Original Solution**: [anagrame_grupate.cpp](../../Saptamana_2/ziua_7/anagrame_grupate.cpp)
- **Main Pattern**: Canonical Hash Key Generation
- **Key Insight**: All anagrams share the exact same sorted character sequence (e.g., `"eat"`, `"tea"`, `"ate"` all become `"aet"` when sorted). Use this canonical sorted string as the hash map key!
- **Approach in Repo**:
  1. Maintain an `unordered_map<std::string, std::vector<std::string>>`.
  2. For each word, create a copy, sort its letters, and push the original word into `groups[sortedWord]`.
  3. Extract all vector values from the map into the final result.
- **Complexity**:
  - **Time Complexity**: $O(N \cdot K \log K)$, where $N$ is the number of words and $K$ is the maximum length of a word.
  - **Space Complexity**: $O(N \cdot K)$ to store groups in the hash map.
- **Important Lesson**: Sorting can serve as a normalization step to group disparate items into equivalence classes.

---

## Problem 5: LeetCode 349 — Intersection of Two Arrays
- **Problem Link**: [LeetCode 349 - Intersection of Two Arrays](https://leetcode.com/problems/intersection-of-two-arrays/)
- **Original Solution**: [349.leetcode_array_intersection.cpp](../../Saptamana_2/ziua_7/349.leetcode_array_intersection.cpp)
- **Main Pattern**: Hash Set Filtering
- **Key Insight**: Uniqueness of elements is enforced by sets. Inserting elements of the first array into an `unordered_set` allows $O(1)$ membership checks for elements of the second array.
- **Approach in Repo**:
  1. Construct `unordered_set<int> set_nums1(nums1.begin(), nums1.end())`.
  2. Iterate through `nums2`; if an element exists in `set_nums1`, insert it into `rezultat_set`.
  3. Convert `rezultat_set` into a `std::vector<int>` and return.
- **Complexity**:
  - **Time Complexity**: $O(N + M)$ average time.
  - **Space Complexity**: $O(N + M)$ to store the sets.
- **Alternative Pattern**: If both arrays are already sorted, Two Pointers can find the intersection in $O(1)$ auxiliary space!
