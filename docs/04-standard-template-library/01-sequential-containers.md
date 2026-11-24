# Sequential Containers and Adaptors (std::vector, std::queue, std::stack)

## 1. Definition
- **Sequential Containers**: Store elements in a strictly linear sequence where position is independent of value. Elements are ordered by their insertion or index.
- **`std::vector`**: A dynamically resizable array stored contiguously in memory.
- **Container Adaptors (`std::stack`, `std::queue`)**: Wrapper classes that restrict access to underlying sequential containers (defaulting to `std::deque`) to enforce specific access protocols:
  - `std::stack`: LIFO (Last-In, First-Out)
  - `std::queue`: FIFO (First-In, First-Out)

---

## 2. Why Does It Matter?
- **Vector Dominance**: Bjarne Stroustrup famously advises: *"By default, use `std::vector` unless you have a specific reason to choose another container."* Its contiguous memory layout provides unmatched cache locality and $O(1)$ random access.
- **Predictable Control**: `std::stack` and `std::queue` enforce structural discipline, preventing arbitrary index modifications when simulating real-world processes (call stacks, event queues, ticket systems).

---

## 3. How Does It Work?

### Vector Memory Growth: Size vs. Capacity
A `std::vector` manages three internal pointers on the stack: `begin`, `end`, and `end_of_storage`.
- `size()`: Number of active elements currently in the vector.
- `capacity()`: Total number of elements the current heap buffer can hold before a reallocation is forced.
- **Amortized $O(1)$ Push Back**: When `size() == capacity()`, the vector allocates a new buffer (typically $2\times$ or $1.5\times$ larger), copies/moves existing elements into the new block, and deletes the old block.

```
Vector Growth Visualization:
Size: 1, Capacity: 1  -> [ 1 ]
Push 2: Reallocates!
Size: 2, Capacity: 2  -> [ 1 | 2 ]
Push 3: Reallocates! (Doubles to 4)
Size: 3, Capacity: 4  -> [ 1 | 2 | 3 | _ ]
Push 4: Fits in unused capacity!
Size: 4, Capacity: 4  -> [ 1 | 2 | 3 | 4 ]
Push 5: Reallocates! (Doubles to 8)
Size: 5, Capacity: 8  -> [ 1 | 2 | 3 | 4 | 5 | _ | _ | _ ]
```

---

## 4. Practical Examples from the Repository

### Example 1: Vector Capacity Growth and Manual Shift Deletion
*(From: `Saptamana_1/ziua_2/vector_ex.cpp`)*

```cpp
#include <iostream>
#include <vector>

void adauga_elemente(std::vector<int>& v) {
    std::vector<int> copie = v;
    for (int elem : copie) {
        v.push_back(elem);
        // Observing dynamic capacity doubling:
        std::cout << "Capacity during append: " << v.capacity() << '\n';
    }
}

// Manual element shifting vs modern erase:
void sterge_element(std::vector<int>& v, int pozitie) {
    for (int i = pozitie; i < v.size() - 1; i++) {
        v[i] = v[i + 1]; // Shift elements left O(N)
    }
    v.pop_back(); // Remove final duplicate in O(1)
}
```

### Example 2: Queue (FIFO) Customer & Order Processing
*(From: `Saptamana_2/ziua_9/pair_queue.cpp` and `sistem_ticket.cpp`)*

```cpp
#include <iostream>
#include <queue>
#include <string>

int main() {
    // Queue storing pairs of (product, price)
    std::queue<std::pair<std::string, int>> comenzi;
    comenzi.push({"laptop", 3000});
    comenzi.push({"mouse", 150});
    comenzi.push({"tastatura", 250});

    while (!comenzi.empty()) {
        auto [produs, pret] = comenzi.front(); // FIFO: inspect front element
        std::cout << "Se proceseaza " << produs << " in valoare de " << pret << " RON\n";
        comenzi.pop(); // Pop front element
    }
    return 0;
}
```

### Example 3: Stack (LIFO) Reversal
*(From: `Saptamana_2/ziua_9/stack_reverse_string.cpp`)*

```cpp
#include <iostream>
#include <stack>
#include <string>

void inverseaza_string(const std::string& s) {
    std::stack<char> st;
    for (char c : s) st.push(c); // Push all characters
    
    // Popping produces reverse order:
    while (!st.empty()) {
        std::cout << st.top();
        st.pop();
    }
}
```

---

## 5. Complexity Summary
| Operation | `std::vector` | `std::stack` | `std::queue` |
| :--- | :--- | :--- | :--- |
| Random Access `[]` | $O(1)$ | N/A | N/A |
| Insert / Remove End | Amortized $O(1)$ | $O(1)$ (push/pop) | $O(1)$ (push) |
| Insert / Remove Beginning | $O(N)$ (requires shifting) | N/A | $O(1)$ (pop) |
| Memory Locality | Contiguous / Cache friendly | Segmented (`std::deque`) | Segmented (`std::deque`) |

---

## 6. Common Mistakes and Pitfalls
1. **Iterator Invalidation**: Modifying a vector (with `push_back` or `insert`) while iterating through it may trigger a reallocation, rendering all existing pointers and iterators dangling!
2. **Calling `pop()` or `top()` on Empty Adaptors**: Invoking `st.top()` or `q.front()` when `empty() == true` is undefined behavior. Always verify `!container.empty()`.
3. **`vec[i]` vs `vec.at(i)`**: `vec[i]` does not perform bounds checking for speed; `vec.at(i)` throws `std::out_of_range`.

---

## 7. Quick Revision
- `std::vector` is a dynamically resizing contiguous array.
- Capacity doubles when full, giving amortized $O(1)$ append time.
- `std::stack` implements LIFO (`push`, `pop`, `top`).
- `std::queue` implements FIFO (`push`, `pop`, `front`).
- Reallocation invalidates existing pointers, references, and iterators to vector elements.

---

## 8. Repository References
- **Vector Mechanics & Sizing**: [vector_ex.cpp](../../Saptamana_1/ziua_2/vector_ex.cpp)
- **Vector as LIFO Stack**: [vector_stack.cpp](../../Saptamana_1/ziua_2/vector_stack.cpp)
- **Order Queue with std::pair**: [pair_queue.cpp](../../Saptamana_2/ziua_9/pair_queue.cpp)
- **Customer Ticket System**: [sistem_ticket.cpp](../../Saptamana_2/ziua_9/sistem_ticket.cpp)
- **Stack String Inversion**: [stack_reverse_string.cpp](../../Saptamana_2/ziua_9/stack_reverse_string.cpp)
