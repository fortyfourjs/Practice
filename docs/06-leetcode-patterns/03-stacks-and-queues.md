# Pattern 03: Stacks and Queues

## Overview
The **Stack** (LIFO) and **Queue** (FIFO) patterns solve problems where the order of processing depends strictly on insertion history:
- **Stacks** are ideal for matching nested structures (parentheses, XML tags), backtracking, tracking recent state, and adjacent cancellation.
- **Queues** model sequential pipelines, buffers, customer scheduling, and Breadth-First Search (BFS).

---

## Problem 1: LeetCode 20 — Valid Parentheses
- **Problem Link**: [LeetCode 20 - Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- **Original Solution**: [valid_paranthesis.cpp](../../Saptamana_2/ziua_9/valid_paranthesis.cpp)
- **Main Pattern**: Stack LIFO Matching
- **Key Insight**: The most recently opened bracket must be the first one closed. A stack preserves the open brackets in reverse order.
- **Approach in Repo**:
  1. Iterate character by character through string `s`.
  2. If character is an opening bracket (`'('`, `'['`, `'{'`), push it onto the stack.
  3. If character is a closing bracket:
     - Check if stack is empty (if so, return `false`).
     - Check if `stack.top()` matches the corresponding opening bracket. If yes, `stack.pop()`; if not, return `false`.
  4. At the end, return `stack.empty()` (ensures no unclosed brackets remain).
- **Complexity**:
  - **Time Complexity**: $O(N)$ single pass.
  - **Space Complexity**: $O(N)$ worst case (all opening brackets).
- **Important Lesson**: Always check `!stack.empty()` before calling `stack.top()`; calling `.top()` on an empty stack is undefined behavior!

---

## Problem 2: LeetCode 1047 — Remove All Adjacent Duplicates In String
- **Problem Link**: [LeetCode 1047 - Remove All Adjacent Duplicates In String](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/)
- **Original Solution**: [leetcode_1047.cpp](../../Saptamana_2/ziua_9/leetcode_1047.cpp)
- **Main Pattern**: Stack-Based Adjacent Cancellation
- **Key Insight**: When two identical adjacent characters meet, they annihilate each other. If we process characters sequentially using a stack, we can compare the incoming character with the character sitting at `stack.top()`.
- **Approach in Repo**:
  ```cpp
  void sterge_dubluri(string& s) {
      stack<char> stack;
      for (int i = 0; i < s.size(); i++) {
          if (!stack.empty() && s[i] == stack.top()) {
              stack.pop(); // Annihilate duplicate pair!
          } else {
              stack.push(s[i]);
          }
      }
      // Reconstruct string from stack
      string rezultat = "";
      while (!stack.empty()) {
          rezultat += stack.top();
          stack.pop();
      }
      for (int i = rezultat.size() - 1; i >= 0; i--) {
          cout << rezultat[i];
      }
  }
  ```
- **Complexity**:
  - **Time Complexity**: $O(N)$.
  - **Space Complexity**: $O(N)$.
- **Modern Optimization**: Instead of an adapter `std::stack<char>`, you can use `std::string` directly as a stack using `.back()`, `.push_back()`, and `.pop_back()`, eliminating the need for string reversal at the end!
  ```cpp
  std::string removeDuplicates(const std::string& s) {
      std::string res;
      for (char c : s) {
          if (!res.empty() && res.back() == c) res.pop_back();
          else res.push_back(c);
      }
      return res;
  }
  ```
