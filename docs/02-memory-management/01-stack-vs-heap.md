# Memory Architecture: Stack vs. Heap and Object Lifetimes

## 1. Definition
In C++, computer memory allocated to a process is divided into distinct segments:
- **The Stack**: A contiguous, high-speed memory region managed automatically by CPU hardware instructions. It stores function call frames, local variables, parameters, and return addresses according to the Last-In, First-Out (LIFO) discipline.
- **The Heap (Free Store)**: A large, dynamic memory pool managed by the C++ runtime and OS allocator. Memory on the heap is allocated explicitly at runtime using operators (`new`, `malloc`) or standard library containers, and persists until explicitly freed (`delete`, `free`) or collected by RAII wrappers.

---

## 2. Why Does It Matter?
Memory architecture is the foundation of C++ systems programming:
- **Lifetime Control**: Stack variables die automatically when their enclosing `{}` scope ends; heap objects survive until explicitly deallocated.
- **Size Flexibility**: The stack has a fixed, small size (typically 1MB to 8MB). Large allocations (like images, large datasets, or dynamically-sized buffers) must reside on the heap to prevent a **Stack Overflow**.
- **Performance Trade-off**: Stack allocations take 1 CPU instruction (adjusting the stack pointer). Heap allocations require searching free lists, memory fragmentation management, and thread synchronization.

---

## 3. How Does It Work?

### Process Memory Layout
A typical C++ program layout in virtual memory:
```
High Memory Addresses (0x7FFF...)
+-------------------------------------------------------+
| Environment variables & Command line arguments        |
+-------------------------------------------------------+
| THE STACK (grows DOWNWARD toward lower addresses)     |
|   - Function frames (main, helper)                    |
|   - Local automatic variables                         |
|   - Return addresses                                  |
|         |                                             |
|         v                                             |
|                                                       |
|         ^                                             |
|         |                                             |
| THE HEAP (Free Store - grows UPWARD toward higher)    |
|   - Dynamic arrays (`new int[n]`)                    |
|   - Container internal buffers (`vector`, `string`)   |
|   - Objects managed by smart pointers                 |
+-------------------------------------------------------+
| BSS Segment (Uninitialized global & static variables) |
+-------------------------------------------------------+
| Data Segment (Initialized global & static variables)  |
+-------------------------------------------------------+
| Text Segment (Compiled machine code instructions)     |
+-------------------------------------------------------+
Low Memory Addresses (0x0040...)
```

### Static vs. Automatic vs. Dynamic Storage Duration
1. **Static Storage Duration**: Global and `static` variables. Allocated before `main()` starts; destroyed when program terminates.
2. **Automatic Storage Duration (Stack)**: Local variables declared inside a block `{}`. Created upon entering the scope; destroyed immediately in reverse order of creation when exiting the scope.
3. **Dynamic Storage Duration (Heap)**: Created explicitly via `new` or `make_unique`. Lifetime is decoupled from lexical scope.

---

## 4. Stack vs. Heap Comparison Matrix
| Attribute | Stack Memory | Heap Memory |
| :--- | :--- | :--- |
| **Allocation Speed** | Blazing fast (1 CPU cycle, pointer add/sub) | Slower (allocator searches memory blocks) |
| **Deallocation** | Automatic upon exiting `{}` scope | Manual (`delete[]`) or automatic via RAII |
| **Size Limit** | Small (typically 1–8 MB) | Limited only by available RAM / virtual memory |
| **Access Pattern** | Highly cache-friendly (L1/L2 cache locality) | Potential cache misses due to pointer chasing |
| **Fragmentation** | Impossible (strictly LIFO) | Possible over long runtimes with varying sizes |
| **Lifetime** | Tied strictly to enclosing function/block | Independent of scope until explicitly released |
| **Failure Mode** | Stack Overflow (crash / segmentation fault) | `std::bad_alloc` exception |

---

## 5. Memory Visualization

Consider this code inspired by `Saptamana_1/ziua_5/alocare_dinamica_vector.cpp`:
```cpp
void createBuffer() {
    int localSize = 3;                       // Stack variable
    int* buffer = new int[localSize]{10, 20, 30}; // buffer pointer on Stack, array on Heap
} // localSize and buffer go out of scope here!
```

```
STACK FRAME (createBuffer)                    HEAP (Free Store)
+-------------------------+                 +---------------------+
| localSize: 3            |                 | [0]: 10             | Address: 0x904000
|                         |                 +---------------------+
| buffer: 0x904000  ------+---------------> | [1]: 20             | Address: 0x904004
+-------------------------+                 +---------------------+
                                            | [2]: 30             | Address: 0x904008
                                            +---------------------+

WHAT HAPPENS AT SCOPE EXIT:
1. `buffer` (the pointer on the stack) is erased from the stack frame.
2. The 12 bytes on the HEAP (0x904000..0x90400C) REMAIN ALLOCATED!
3. Because no pointer holds 0x904000 anymore, that memory is LEAKED!
```

---

## 6. Practical Examples from the Repository

### Example 1: Demonstrating Stack LIFO Behavior with a Vector
*(From: `Saptamana_1/ziua_2/vector_stack.cpp`)*

```cpp
#include <iostream>
#include <vector>

void printStack(const std::vector<int>& stack) {
    std::cout << "Stack: ";
    for (int i : stack) std::cout << "(" << i << ") ";
    std::cout << "| Capacity: " << stack.capacity() << " Length: " << stack.size() << '\n';
}

int main() {
    std::vector<int> stack;
    stack.push_back(1); // Push to top of stack
    stack.push_back(2);
    stack.push_back(3);
    printStack(stack);  // (1) (2) (3)
    
    stack.pop_back();   // LIFO Pop: 3 is removed
    printStack(stack);  // (1) (2)
    return 0;
}
```

### Example 2: Inspecting Heap Addresses vs Stack Addresses
*(From: `Saptamana_2/ziua_11/alocare_dinamica.cpp`)*

```cpp
int main() {
    int stackVar = 5;
    int* heapArr = new int[3]{10, 20, 30};

    std::cout << "Stack address: " << &stackVar << "\n"; // e.g., 0x7ffeeb... (High address)
    std::cout << "Heap pointer variable on stack: " << &heapArr << "\n";
    std::cout << "Heap allocated block address: " << heapArr << "\n"; // e.g., 0x55a8... (Lower address)

    delete[] heapArr;
    heapArr = nullptr;
    return 0;
}
```

---

## 7. Common Mistakes and Pitfalls
1. **Stack Overflow from Huge Stack Allocations**:
   ```cpp
   void bad() {
       int hugeArray[10000000]; // Trying to allocate ~40MB on the stack! Crashes instantly!
   }
   ```
2. **Dangling Pointers to Stack Memory**:
   ```cpp
   int* getStackPointer() {
       int x = 42;
       return &x; // UB: x is destroyed as soon as the closing brace } is hit!
   }
   ```
3. **Leaking Heap Memory upon Function Exit**:
   Failing to invoke `delete[]` before returning or when an exception is thrown.

---

## 8. When Should I Use Stack vs. Heap?
- **Use the Stack by default**: For all local variables, small objects, loop counters, and temporary values.
- **Use the Heap**:
  - When the size is only known at runtime (e.g., user enters $N$).
  - When the data structure is very large (e.g., dynamic arrays > a few KB).
  - When the object must outlive the scope that created it (e.g., factory functions).
  - **Best practice**: Always manage heap allocations using smart pointers (`std::unique_ptr`, `std::shared_ptr`) or containers (`std::vector`, `std::string`), NEVER raw `new`/`delete`!

---

## 9. Quick Revision
- The stack is automatic, fixed-size, LIFO, and CPU-managed; objects are destroyed at `}`.
- The heap is dynamic, flexible, and manual; objects survive until explicitly freed.
- Local pointers live on the stack; the memory they point to may live on the heap.
- If a pointer on the stack goes out of scope without releasing its heap memory, a **memory leak** occurs.
- Stack allocations are practically zero-cost; heap allocations involve allocator overhead.

---

## 10. Repository References
- **Vector as a Stack**: [vector_stack.cpp](../../Saptamana_1/ziua_2/vector_stack.cpp)
- **Heap Allocation with new[]**: [alocare_dinamica_vector.cpp](../../Saptamana_1/ziua_5/alocare_dinamica_vector.cpp)
- **Heap Address Printing**: [alocare_dinamica.cpp](../../Saptamana_2/ziua_11/alocare_dinamica.cpp)
- **Heap Exhaustion Experiment**: [eroare_alocare_dinamica.cpp](../../Saptamana_1/ziua_5/eroare_alocare_dinamica.cpp)
