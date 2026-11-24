# Pattern 02: Two Pointers

## Overview
The **Two Pointers** pattern uses two integer indices (or raw pointers) to traverse a contiguous sequence either:
1. **Converging from both ends** (e.g., `left = 0`, `right = n - 1` moving toward each other for palindrome checks and string reversal).
2. **Moving at different speeds in the same direction** (e.g., a *slow* write pointer and a *fast* read pointer for in-place deduplication or partitioning).

This pattern eliminates auxiliary buffer allocations, enabling in-place $O(N)$ runtime with $O(1)$ auxiliary space.

---

## Problem 1: LeetCode 344 — Reverse String
- **Problem Link**: [LeetCode 344 - Reverse String](https://leetcode.com/problems/reverse-string/)
- **Original Solutions**: [344.leetcode_reversestring.cpp](../../Saptamana_1/ziua_2/344.leetcode_reversestring.cpp) and [inversare_sir.cpp](../../Saptamana_1/ziua_1/inversare_sir.cpp)
- **Main Pattern**: Converging Two Pointers (Left & Right)
- **Key Insight**: The character at index `i` mirrors the character at index `n - 1 - i`. Swapping pairs while advancing `i` from $0$ to $n/2$ reverses the entire sequence in-place.
- **Approach in Repo**:
  ```cpp
  void reverseString(vector<char>& s) {
      int n = s.size();
      for (int i = 0; i < n / 2; i++) {
          int temp = s[i];
          s[i] = s[n - 1 - i];
          s[n - 1 - i] = temp;
      }
  }
  ```
- **Complexity**:
  - **Time Complexity**: $O(N)$ ($\approx N/2$ swap operations).
  - **Space Complexity**: $O(1)$ in-place auxiliary space.
- **Modern Idiomatic C++**: `std::swap(s[left], s[right])` or `std::reverse(s.begin(), s.end())`.

---

## Problem 2: LeetCode 125 — Valid Palindrome
- **Problem Link**: [LeetCode 125 - Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)
- **Original Solutions**: [125.leetcode_validpalindrome.cpp](../../Saptamana_1/ziua_4/125.leetcode_validpalindrome.cpp) and [palindrom.cpp (Day 4)](../../Saptamana_1/ziua_4/palindrom.cpp)
- **Main Pattern**: Two-Pointer Symmetry Check with Sanitization
- **Key Insight**: A string is a palindrome if it reads identically forwards and backwards after stripping non-alphanumeric characters and normalizing casing.
- **Approach in Repo**:
  1. Helper `curata_sir`: Filter chars with `std::isalnum` and convert to lowercase with `std::tolower`.
  2. Compare characters at symmetric positions: `if (s[i] != s[n - 1 - i]) return false;`.
- **Complexity**:
  - **Time Complexity**: $O(N)$.
  - **Space Complexity**: $O(N)$ auxiliary space for the sanitized string.
- **Optimal In-Place Two-Pointer Variant (Zero Extra Space)**:
  We can skip non-alphanumeric characters directly using two converging pointers without building a temporary string:
  ```cpp
  bool isPalindrome(const std::string& s) {
      int left = 0, right = s.size() - 1;
      while (left < right) {
          while (left < right && !std::isalnum(s[left])) left++;
          while (left < right && !std::isalnum(s[right])) right--;
          if (std::tolower(s[left]) != std::tolower(s[right])) return false;
          left++;
          right--;
      }
      return true;
  }
  ```
  - **Time**: $O(N)$, **Space**: $O(1)$.

---

## Problem 3: LeetCode 26 — Remove Duplicates from Sorted Array
- **Problem Link**: [LeetCode 26 - Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)
- **Original Solutions**: [26.leetcode_removeduplicatesarray.cpp](../../Saptamana_1/ziua_5/26.leetcode_removeduplicatesarray.cpp) and [final_program.cpp](../../Saptamana_1/ziua_6/final_program.cpp)
- **Main Pattern**: Fast & Slow Pointers (Reader & Writer)
- **Key Insight**: In a sorted array, new unique values appear whenever `nums[i] != nums[i - 1]`. A "slow" pointer (`unic`) tracks the insertion index for the next unique element, while a "fast" pointer (`i`) scans ahead.
- **Approach in Repo**:
  ```cpp
  int removeDuplicates(vector<int>& nums) {
      if (nums.empty()) return 0;
      int unic = 1;
      for (int i = 1; i < nums.size(); i++) {
          if (nums[i] != nums[i - 1]) {
              nums[unic] = nums[i];
              unic++;
          }
      }
      return unic;
  }
  ```
- **Complexity**:
  - **Time Complexity**: $O(N)$ single pass.
  - **Space Complexity**: $O(1)$ in-place auxiliary space.
- **Important Lesson**: In `final_program.cpp`, the author combined this with `v.resize(unic)` to physically shrink the container after deduplication, matching the behavior of `std::unique`.

---

## Problem 4: LeetCode 1768 — Merge Strings Alternately
- **Problem Link**: [LeetCode 1768 - Merge Strings Alternately](https://leetcode.com/problems/merge-strings-alternately/)
- **Original Solution**: [1768.leetcode_mergestringsalt.cpp](../../Saptamana_1/ziua_6/1768.leetcode_mergestringsalt.cpp)
- **Main Pattern**: Dual Pointer / Index Traversal
- **Key Insight**: Traverse both strings up to $\max(|word1|, |word2|)$. If index $i$ is within bounds of string 1, append its character; then repeat for string 2.
- **Complexity**:
  - **Time Complexity**: $O(N + M)$ where $N, M$ are lengths of the two words.
  - **Space Complexity**: $O(N + M)$ to store the merged result.
- **Optimization Tip**: Pre-allocate memory using `merge.reserve(n1 + n2)` to prevent multiple reallocations during appending.
