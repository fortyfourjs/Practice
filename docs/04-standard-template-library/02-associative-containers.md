# Associative Containers: Hash Tables and Sets (unordered_map, unordered_set)

## 1. Definition
- **Associative Containers**: Containers that store elements referenced by **keys** rather than sequential index positions.
- **`std::unordered_map<Key, Value>`**: An associative container holding key-value pairs with unique keys, implemented as a **Hash Table**.
- **`std::unordered_set<Key>`**: An associative container holding unique keys, implemented as a Hash Table.
- **`std::map` / `std::set`**: Ordered counterparts implemented using self-balancing Red-Black binary search trees.

---

## 2. Why Does It Matter?
- **$O(1)$ Average Lookup**: Hash tables reduce lookup, insertion, and deletion complexity from $O(N)$ (linear search in arrays) down to **amortized $O(1)$ constant time**.
- **Crucial for Algorithmic Problems**: Fundamental building block for frequency counting, caching/memoization, duplicate detection, graph adjacency lists, and pattern matching (e.g., Two Sum, Anagrams, Group Anagrams).

---

## 3. How Does It Work?

### Hash Table Architecture
1. **Hash Function**: Maps a key (e.g., `string`, `int`) to an integer hash code (`std::hash<Key>`).
2. **Bucket Array**: The hash code modulo the number of buckets gives the bucket index.
3. **Collision Handling**: Modern standard libraries resolve bucket collisions using **separate chaining** (linked lists or small vectors at each bucket).
4. **Load Factor & Rehash**: When `load_factor() = size / bucket_count` exceeds `max_load_factor()` (typically 1.0), the table allocates more buckets and rehashes all elements.

```
HASH TABLE VISUALIZATION:
Key: "eat"  -> std::hash -> 483920 -> % 4 Buckets -> Bucket 0
Key: "tea"  -> std::hash -> 483920 -> % 4 Buckets -> Bucket 0 (Collision! Chained)
Key: "bat"  -> std::hash -> 291811 -> % 4 Buckets -> Bucket 3

Bucket 0: [ ("eat", ...) ] -> [ ("tea", ...) ]
Bucket 1: nullptr
Bucket 2: nullptr
Bucket 3: [ ("bat", ...) ]
```

### Unordered vs. Ordered Comparison
| Feature | `std::unordered_map` / `set` | `std::map` / `set` |
| :--- | :--- | :--- |
| **Underlying Data Structure** | Hash Table (Buckets) | Self-Balancing Red-Black BST |
| **Average Time Complexity** | $O(1)$ amortized | $O(\log N)$ guaranteed |
| **Worst-Case Complexity** | $O(N)$ (all hash collisions) | $O(\log N)$ |
| **Order of Elements** | Unspecified / Arbitrary | Strictly sorted by key (`<`) |
| **Key Requirement** | `std::hash<Key>` and `operator==` | `operator<` (Strict Weak Ordering) |

---

## 4. Practical Examples from the Repository

### Example 1: Frequency Table with Structured Binding
*(From: `Saptamana_2/ziua_7/unordered_map.cpp`)*

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::string text = "abracadabra";
    std::unordered_map<char, int> freq;

    // Incrementing frequencies
    for (char c : text) {
        freq[c]++; // If 'c' not present, operator[] inserts it with value 0, then increments!
    }

    // Modern C++17 Structured Binding iteration:
    std::cout << "Char\t\tCount\n";
    for (const auto& [caracter, frecventa] : freq) {
        std::cout << caracter << "\t\t" << frecventa << "\n";
    }
    return 0;
}
```

### Example 2: Group Anagrams using Sorted String as Hash Key
*(From: `Saptamana_2/ziua_7/anagrame_grupate.cpp`)*

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& words) {
    // Key = sorted canonical form ("aet"), Value = list of matching words
    std::unordered_map<std::string, std::vector<std::string>> groups;

    for (const auto& word : words) {
        std::string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        groups[sortedWord].push_back(word);
    }

    std::vector<std::vector<std::string>> result;
    for (const auto& [key, list] : groups) {
        result.push_back(list);
    }
    return result;
}
```

### Example 3: Set Intersection in $O(N + M)$
*(From: `Saptamana_2/ziua_7/349.leetcode_array_intersection.cpp`)*

```cpp
#include <vector>
#include <unordered_set>

std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::unordered_set<int> set1(nums1.begin(), nums1.end()); // O(N)
    std::unordered_set<int> resultSet;

    for (int num : nums2) { // O(M)
        if (set1.count(num)) { // O(1) average lookup
            resultSet.insert(num);
        }
    }
    return std::vector<int>(resultSet.begin(), resultSet.end());
}
```

---

## 5. Common Mistakes and Pitfalls
1. **Accidental Insertion via `operator[]`**:
   Calling `map[nonExistentKey]` on a `std::unordered_map` **silently creates and inserts** that key with a default-constructed value!
   - To inspect a key without modifying the map, always use `.find(key)` or `.count(key)`.
2. **Passing Hash Maps by Value**:
   In `Saptamana_2/ziua_7/valid_anagram_one_hashmap.cpp`, passing `unordered_map<char, int> hashmap` by value creates a full heap-allocated clone of the hash table. Pass by reference or instantiate locally!
3. **Invalid Iterator after Rehash**:
   Inserting elements that cause a rehash invalidates all existing iterators (though references to elements remain valid in hash maps).

---

## 6. Quick Revision
- `std::unordered_map` provides average $O(1)$ key-value lookups using a hash table.
- `std::unordered_set` stores unique keys with average $O(1)$ membership checks.
- `operator[]` inserts a default value if the key does not exist; use `.find()` for read-only checks.
- Use C++17 structured bindings `for (const auto& [k, v] : map)` for clean iteration.
- Pass hash tables by `const std::unordered_map&` to avoid duplicating the bucket structure.

---

## 7. Repository References
- **Frequency Counter**: [unordered_map.cpp](../../Saptamana_2/ziua_7/unordered_map.cpp)
- **Two-Map Anagram**: [valid_anagram.cpp](../../Saptamana_2/ziua_7/valid_anagram.cpp)
- **Single-Map Anagram**: [valid_anagram_one_hashmap.cpp](../../Saptamana_2/ziua_7/valid_anagram_one_hashmap.cpp)
- **Group Anagrams**: [anagrame_grupate.cpp](../../Saptamana_2/ziua_7/anagrame_grupate.cpp)
- **Majority Element with Hash Map**: [nr_majoritar.cpp](../../Saptamana_2/ziua_7/nr_majoritar.cpp)
- **Array Intersection with Set**: [349.leetcode_array_intersection.cpp](../../Saptamana_2/ziua_7/349.leetcode_array_intersection.cpp)
