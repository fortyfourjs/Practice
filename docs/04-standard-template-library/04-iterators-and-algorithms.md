# Iterators and Standard Algorithms (std::sort, lower_bound, Erase-Remove)

## 1. Definition
- **Iterator**: An object that points to an element inside a container and can be incremented (`++`) and dereferenced (`*`, `->`) to traverse elements. Iterators serve as the generic "glue" between STL containers and STL algorithms.
- **Half-Open Range `[begin, end)`**: The fundamental iterator convention in C++. `begin()` refers to the first element; `end()` refers to the memory location **one past the last element**, acting as a sentinel.
- **STL Algorithms (`<algorithm>`)**: A collection of highly optimized, generic functions (sorting, searching, partitioning, counting) that operate over iterator ranges.

---

## 2. Why Does It Matter?
- **Decoupling**: Algorithms do not need to know container internals; they only operate on iterators. The same `std::find` algorithm works on `std::vector`, `std::string`, and `std::list`.
- **Optimal Time Complexity**: Standard library algorithms use state-of-the-art algorithms (e.g., `std::sort` uses **Introsort**, a hybrid of Quicksort, Heapsort, and Insertion Sort guaranteed to run in $O(N \log N)$ time).

---

## 3. How Does It Work?

### Iterator Half-Open Range
```
Vector Elements:  [ 10 | 20 | 30 | 40 ]
                     ^                    ^
                     |                    |
                 v.begin()              v.end() (One past the end! DO NOT DEREFERENCE!)
```

### Binary Search: `lower_bound` vs. `upper_bound`
For a sorted collection:
- `std::lower_bound(begin, end, val)`: Returns an iterator to the **first element that is $\ge val$**.
- `std::upper_bound(begin, end, val)`: Returns an iterator to the **first element that is $> val$**.
- Finding 0-based index: `int index = it - v.begin();`

---

## 4. Practical Examples from the Repository

### Example 1: `lower_bound` Binary Search and Erase-Remove Idiom
*(From: `Saptamana_2/ziua_10/upper/lower_bound.cpp`)*

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 4, 4, 4, 6, 8};

    // 1. Binary search using lower_bound (Runs in O(log N) because v is sorted):
    auto it = std::lower_bound(v.begin(), v.end(), 4);

    if (it != v.end() && *it == 4) {
        // Iterator arithmetic to compute 0-based index:
        int index = it - v.begin();
        std::cout << "Value " << *it << " found at index: " << index << '\n';
    } else {
        std::cout << "Element not found\n";
    }

    // 2. Erase-Remove Idiom with Lambda:
    // std::remove_if moves elements to keep to the front and returns the new logical end.
    // v.erase removes the leftover trailing elements. Runs in O(N)!
    v.erase(std::remove_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0; // Remove all even numbers
    }), v.end());

    for (int i : v) std::cout << i << " "; // Prints remaining odd elements
    return 0;
}
```

### Example 2: Explicit Iterator Traversal
*(From: `saptamana_4/ziua_20/iterator.cpp`)*

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>

int main() {
    std::vector<int> v = {10, 20, 30, 40};
    
    // Explicit vector iterator:
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << '\n';
    }

    std::map<std::string, int> map = {{"Produs1", 30}, {"Produs2", 10}};
    
    // Explicit map const_iterator:
    for (std::map<std::string, int>::const_iterator it = map.begin(); it != map.end(); ++it) {
        // NOTE: Use -> arrow operator (or (*it).first) on map iterators:
        std::cout << it->first << " costs " << it->second << '\n';
    }
    return 0;
}
```

---

## 5. Subtle Bug Analysis in Original Repository
In `saptamana_4/ziua_20/iterator.cpp`, the original code contained:
```cpp
std::cout << it.first << it.second << '\n'; // SYNTAX ERROR: it is an iterator, not a struct!
```
**Fix**: Because an iterator acts like a pointer to a `std::pair<const Key, Value>`, you must use the arrow operator `it->first` and `it->second`, or dereference first: `(*it).first`.

---

## 6. Common Mistakes and Pitfalls
1. **Dereferencing `end()`**: `*v.end()` is undefined behavior. Always check `if (it != v.end())` before dereferencing.
2. **Calling `lower_bound` on an Unsorted Range**: Binary search assumes the range is sorted. Calling `std::lower_bound` on unsorted data produces garbage results without warning!
3. **Using Member `erase()` in a Loop**: Calling `v.erase(it)` inside a raw for-loop shifts elements and invalidates iterators. Always use the **Erase-Remove Idiom** (`std::remove_if` + `v.erase`).

---

## 7. Quick Revision
- Iterators navigate containers using pointer semantics (`*it`, `it->`, `++it`).
- Ranges are always half-open: `[begin, end)`. Never dereference `end()`.
- `std::lower_bound` finds the first element $\ge target$ in $O(\log N)$ on sorted ranges.
- Subtracting `v.begin()` from an iterator gives the 0-based array index.
- The Erase-Remove idiom is the standard, $O(N)$ way to filter and delete container elements.

---

## 8. Repository References
- **Lower Bound & Erase-Remove**: [lower_bound.cpp](../../Saptamana_2/ziua_10/upper/lower_bound.cpp)
- **Iterator Traversal**: [iterator.cpp](../../saptamana_4/ziua_20/iterator.cpp)
- **Sorting with Custom Lambdas**: [lambda_produse.cpp](../../saptamana_4/ziua_22/lambda_produse.cpp)
