# RAII and Modern Smart Pointers (unique_ptr, shared_ptr, weak_ptr)

## 1. Definition
**RAII** (**R**esource **A**cquisition **I**s **I**nitialization) is the foundational design idiom of Modern C++. It states that every resource (heap memory, file handles, database connections, mutex locks) must be acquired inside the constructor of an object and automatically released in that object's destructor.

**Smart Pointers** (`<memory>`) are standard library RAII classes that wrap raw pointers to provide automated, deterministic memory management and unambiguous ownership semantics.

---

## 2. Why Does It Matter?
- **Zero Memory Leaks**: When an object's stack frame is popped or an exception is thrown, destructors run automatically, freeing the managed heap memory.
- **Exception Safety**: If an error or exception occurs midway through a function, raw `delete` statements are skipped, causing leaks. RAII guarantees cleanup during stack unwinding.
- **Explicit Ownership**: The type itself reveals who is responsible for managing the memory:
  - `unique_ptr`: "I alone own this resource."
  - `shared_ptr`: "We co-own this resource; the last one out turns off the lights."
  - `weak_ptr`: "I observe this resource without keeping it alive."

---

## 3. How Does It Work?

### 1. `std::unique_ptr<T>` (Exclusive Ownership)
- **Ownership**: Sole, exclusive ownership. No two `unique_ptr` instances can point to the same resource simultaneously.
- **Copying**: Copying is disabled (`delete` copy constructor).
- **Moving**: Can be moved using `std::move()`, transferring ownership from source to destination.
- **Overhead**: **Zero overhead** compared to a raw pointer!
- **Construction**: Always prefer `std::make_unique<T>(args...)` (C++14).

### 2. `std::shared_ptr<T>` (Shared Ownership)
- **Ownership**: Multiple `shared_ptr` instances share ownership of a single heap object.
- **Control Block**: In addition to the managed object, it maintains a heap-allocated **Control Block** holding:
  - Reference Count (`use_count()`): Number of active `shared_ptr` owners.
  - Weak Count: Number of active `weak_ptr` observers.
  - Custom deleter (if provided).
- **Deallocation**: When a `shared_ptr` is destroyed, `use_count()` is decremented. When `use_count()` hits 0, the managed object is destroyed.
- **Construction**: Always prefer `std::make_shared<T>(args...)` (single allocation for object + control block).

### 3. `std::weak_ptr<T>` (Non-Owning Observer)
- Points to an object managed by `shared_ptr` without incrementing its `use_count()`.
- Used to break circular dependencies (e.g., Parent $\leftrightarrow$ Child graphs) which would otherwise cause memory leaks.
- Must be converted to `shared_ptr` using `.lock()` before reading.

---

## 4. Memory Visualization

### Ownership Transfer with `std::unique_ptr` and `std::move`
*(Studied in `Saptamana_2/ziua_12/move_ptr.cpp`)*

```
1. In main(): auto array = make_unique<int[]>(size);
STACK (main)                               HEAP (Free Store)
+-----------------------------+          +-------------------------+
| array: ptr -> 0x7000        | -------->| [0]: int | [1]: int ... |
+-----------------------------+          +-------------------------+

2. Passing via std::move(array) into preiaTablou(unique_ptr<int[]> ptr):
STACK (main)
+-----------------------------+
| array: nullptr (RESET!)     | --------x (Ownership surrendered!)
+-----------------------------+

STACK (preiaTablou)                        HEAP (Free Store)
+-----------------------------+          +-------------------------+
| ptr: 0x7000                 | -------->| [0]: int | [1]: int ... |
+-----------------------------+          +-------------------------+

3. When preiaTablou returns:
   - `ptr` destructor executes.
   - `delete[]` is automatically called on 0x7000.
   - HEAP MEMORY IS FREED!
   - In main(), checking `array == nullptr` evaluates to TRUE!
```

### Shared Pointer Reference Counting
*(Studied in `Saptamana_2/ziua_12/shared_ptr.cpp`)*

```
STACK                                      HEAP (Free Store)
+-------------------------+               +-------------------------------------+
| p1 (shared_ptr)         | ------------> | Managed Object: int (100)           |
+-------------------------+       |       +-------------------------------------+
                                  +-----> | Control Block:                      |
+-------------------------+       |       |   use_count: 2 (p1 and p2)          |
| p2 (shared_ptr)         | ------+       |   weak_count: 0                     |
+-------------------------+               +-------------------------------------+

When p2 goes out of scope:
- p2 destructor fires -> use_count drops to 1. Object remains alive.
When p1 goes out of scope:
- p1 destructor fires -> use_count drops to 0. int(100) and Control Block are destroyed!
```

---

## 5. Practical Examples from the Repository

### Example 1: Automatic Scope Deallocation with `std::unique_ptr`
*(From: `Saptamana_2/ziua_12/smart_pointers_alocare_dinamica.cpp`)*

```cpp
#include <iostream>
#include <memory>

void processArray(int size) {
    // Heap array allocated automatically
    auto array = std::make_unique<int[]>(size);
    std::cout << "VALORI IN HEAP\n";
    for (int i = 0; i < size; i++) {
        array[i] = (i + 1) * 10;
        std::cout << "Valoare: " << array[i] << " la adresa: " << &array[i] << '\n';
    }
    // Scope ends here: array is AUTOMATICALLY destroyed with delete[]! Zero leaks!
}

int main() {
    processArray(3);
    return 0;
}
```

### Example 2: Verifying Ownership Transfer
*(From: `Saptamana_2/ziua_12/move_ptr.cpp`)*

```cpp
#include <iostream>
#include <memory>

void preiaTablou(std::unique_ptr<int[]> ptr, int size) {
    std::cout << "Array successfully received by function!\n";
} // ptr is destroyed here, freeing the heap memory!

int main() {
    auto array = std::make_unique<int[]>(5);
    
    // Passing array requires explicit std::move because unique_ptr cannot be copied
    preiaTablou(std::move(array), 5);
    
    // Confirming that main no longer owns the resource
    if (array == nullptr) {
        std::cout << "memorie eliberata (ownership transferred, array is null)\n";
    }
    return 0;
}
```

### Example 3: Shared Pointers and Reference Counts
*(From: `Saptamana_2/ziua_12/shared_ptr.cpp`)*

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p1 = std::make_shared<int>(100);
    std::cout << "Value: " << *p1 << " | use_count: " << p1.use_count() << '\n'; // 1
    {
        auto p2 = p1; // Copy: increments reference count
        std::cout << "Inside inner block: use_count: " << p1.use_count() << '\n';   // 2
    } // p2 goes out of scope here
    
    std::cout << "After inner block: use_count: " << p1.use_count() << '\n';    // 1
    return 0;
}
```

### Example 4: Managing Collections of Polymorphic Objects with `std::unique_ptr`
*(From Capstone: `saptamana_4/ziua_24/Library Management/Library.h`)*

```cpp
class Library {
private:
    // Storing polymorphic or dynamically allocated objects safely:
    std::vector<std::unique_ptr<Book>> book_list;
public:
    void adaugaCarte(const std::string& titlu, const std::string& autor, const std::string& isbn, bool stare) {
        auto carte = std::make_unique<Book>(titlu, autor, isbn, stare);
        // unique_ptr must be moved into vector:
        book_list.push_back(std::move(carte));
    }
};
```

---

## 6. Common Mistakes and Pitfalls
1. **Attempting to Copy a `std::unique_ptr`**:
   ```cpp
   std::unique_ptr<int> p1 = std::make_unique<int>(10);
   std::unique_ptr<int> p2 = p1; // COMPILE ERROR: use of deleted copy constructor!
   std::unique_ptr<int> p2 = std::move(p1); // OK: p1 is now nullptr, p2 owns the int.
   ```
2. **Creating Multiple Independent `shared_ptr` from the Same Raw Pointer**:
   ```cpp
   int* raw = new int(20);
   std::shared_ptr<int> sp1(raw);
   std::shared_ptr<int> sp2(raw); // CATASTROPHIC: Creates two separate control blocks!
   // When sp1 dies, raw is deleted. When sp2 dies, double-free crash occurs!
   ```
3. **Circular References with `shared_ptr`**:
   If Node A has a `shared_ptr` to Node B, and Node B has a `shared_ptr` to Node A, their `use_count()` will never drop to 0, leaking both nodes. Break the cycle by making one link a `std::weak_ptr`.

---

## 7. When Should I Use Which?
| Scenario | Recommended Type |
| :--- | :--- |
| Default dynamic allocation | `std::unique_ptr` |
| Transferring resource ownership into a collection | `std::move(unique_ptr)` |
| Multiple components need concurrent, shared read/write access | `std::shared_ptr` |
| Caches, observer patterns, circular reference breaking | `std::weak_ptr` |
| Function parameter that only needs to observe data | `const T&` or raw pointer `T*` |

---

## 8. Quick Revision
- RAII binds resource lifetime to object lifetime: allocate in constructor, release in destructor.
- `std::unique_ptr` is the default choice: zero-cost, single ownership, movable only.
- `std::shared_ptr` provides reference-counted shared ownership; frees memory when `use_count() == 0`.
- `std::weak_ptr` observes without owning, preventing circular reference memory leaks.
- Never use raw `new` and `delete` in modern C++ application code.

---

## 9. Repository References
- **Scope Deallocation**: [smart_pointers_alocare_dinamica.cpp](../../Saptamana_2/ziua_12/smart_pointers_alocare_dinamica.cpp)
- **Move Semantics & Ownership**: [move_ptr.cpp](../../Saptamana_2/ziua_12/move_ptr.cpp)
- **Shared Pointer Reference Counting**: [shared_ptr.cpp](../../Saptamana_2/ziua_12/shared_ptr.cpp)
- **Vector of Unique Pointers (Polymorphism)**: [animal.cpp](../../saptamana_3_OOP/ziua_16_polimorfism_dinamic/animal.cpp)
- **Library Management Unique Pointers**: [Library.cpp](../../saptamana_4/ziua_24/Library%20Management/Library.cpp)
