# C++ Quick Revision Guide

A concentrated, high-yield summary of core C++ concepts, rules of thumb, and essential syntax for rapid interview and exam revision.

---

## 1. Fundamentals & References
- **Variables**: Named memory locations holding values. Type dictates size, alignment, and operations.
- **`sizeof`**: Compile-time operator returning byte size. (`sizeof(char) == 1`, `sizeof(int) == 4`, `sizeof(double) == 8` typically).
- **Uniform Brace Initialization (`{}`)**: Avoids accidental narrowing conversions (e.g., `int x{3.14}` is a compiler error).
- **Pointers (`T*`)**: Variables holding memory addresses. Can be `nullptr`, can be reassigned, support pointer arithmetic.
- **References (`T&`)**: Immutable aliases for existing objects. Must be initialized immediately; cannot be null; cannot be rebound.
- **Const Correctness**:
  - `const T*`: Pointer to const data (data is immutable).
  - `T* const`: Const pointer (the address cannot change).
  - `void func() const`: Member function that cannot mutate any member variables.

---

## 2. Memory Management (Critical High-Yield)
- **Stack**: Fixed-size, CPU-managed LIFO memory. Allocations are near-instantaneous; variables die automatically at scope exit `}`.
- **Heap (Free Store)**: Large, dynamic memory pool. Manual allocation (`new`) and deallocation (`delete`). Unbounded lifetime.
- **`new` vs `new[]`**: `new` pairs with `delete`; `new[]` pairs with `delete[]`. Mixing them triggers undefined behavior!
- **Memory Leak**: Memory allocated on the heap that is no longer accessible and was never freed.
- **Dangling Pointer**: A pointer holding the address of already-deallocated memory. Always set pointers to `nullptr` after deletion.
- **Double Free**: Calling `delete` twice on the same memory address, causing heap corruption.

### Smart Pointers (`<memory>`)
- **RAII**: Resource Acquisition Is Initialization. Resources are acquired in constructors and freed automatically in destructors.
- **`std::unique_ptr<T>`**: Exclusive ownership. Zero overhead. Movable, but **cannot be copied**. Always prefer `std::make_unique<T>()`.
- **`std::shared_ptr<T>`**: Shared ownership. Uses an internal reference counter (`use_count()`). Deallocates heap object when counter hits 0. Always prefer `std::make_shared<T>()`.
- **`std::weak_ptr<T>`**: Non-owning observer of a `shared_ptr`. Does not increase reference count; breaks circular dependency leaks. Convert using `.lock()`.
- **`std::move()`**: Casts an lvalue to an rvalue reference (`T&&`), enabling ownership transfer without copying.

### Copy Semantics & The Rule of Three / Five
- **Shallow Copy**: Member-wise copy of pointers. Both objects share the same heap memory $\rightarrow$ leads to double free!
- **Deep Copy**: Allocates a new heap block and copies values independently.
- **Rule of Three**: If you define a Destructor, Copy Constructor, or Copy Assignment Operator, you must define all three.
- **Rule of Five**: For modern performance, also implement the Move Constructor and Move Assignment Operator.
- **Rule of Zero**: Use standard types (`std::vector`, `std::unique_ptr`) so you don't need custom memory management.

---

## 3. Object-Oriented Programming (OOP)
- **Encapsulation**: Keeping member variables `private` and exposing validated public methods.
- **Inheritance (`is-a`)**: Derived class extends a Base class. Always use member initializer list `: Base(...)` to call base constructors.
- **Composition (`has-a`)**: Class contains instances of other classes. Prefer composition over inheritance.
- **Dynamic Polymorphism**: Calling derived methods through Base pointers/references at runtime using the `vtable` and `vptr`.
- **Virtual Destructors**: **MANDATORY** on any base class with virtual functions (`virtual ~Base() = default;`), otherwise deleting through `Base*` leaks derived resources!
- **Pure Virtual Function (`= 0`)**: Makes a class Abstract (an Interface). Cannot be instantiated. Subclasses must implement all pure virtual methods.
- **`override` Keyword**: Guarantees at compile time that the derived function overrides a matching base virtual method.

---

## 4. Standard Template Library (STL)
- **`std::vector`**: Dynamic contiguous array. Capacity doubles on demand; amortized $O(1)$ push_back. Contiguous memory ensures maximum CPU cache efficiency.
- **`std::stack`**: LIFO adaptor (`push`, `pop`, `top`).
- **`std::queue`**: FIFO adaptor (`push`, `pop`, `front`).
- **`std::priority_queue`**: Binary heap. $O(1)$ top element inspection, $O(\log N)$ push and pop. Default is Max-Heap; `std::greater<T>` makes it a Min-Heap.
- **`std::unordered_map`**: Hash table. Average $O(1)$ key lookup and insertion. `operator[]` inserts a default value if key is absent; use `.find()` for read-only inspection.
- **`std::unordered_set`**: Hash set. Stores unique keys with average $O(1)$ membership checks.
- **Half-Open Ranges `[begin, end)`**: `end()` points one past the last element. Never dereference `end()`.
- **`std::lower_bound`**: First element $\ge target$ in sorted range ($O(\log N)$).
- **Erase-Remove Idiom**: `v.erase(std::remove_if(v.begin(), v.end(), pred), v.end());` for in-place $O(N)$ container filtering.

---

## 5. Modern & Advanced C++
- **Templates**: Compile-time generic code generation via monomorphization. Zero runtime cost. Definitions must be placed in header files.
- **Lambdas**: Anonymous inline function closures: `[capture](params) -> return_type { body }`.
  - `[]`: No capture.
  - `[=]`: Capture all by value (copy).
  - `[&]`: Capture all by reference.
  - `[var]`: Capture specific variable.
- **Exceptions (`<stdexcept>`)**: `throw`, `try`, `catch`. Always catch by `const std::exception&` to avoid object slicing. Stack unwinding automatically invokes destructors of local objects.
- **File I/O (`<fstream>`)**: `std::ifstream` (read), `std::ofstream` (write), `std::ios::app` (append mode). Delimited parsing with `std::stringstream` and `std::getline(ss, token, ',')`.

---

## 6. Algorithmic Patterns Cheat Sheet
| Pattern | Signal | Canonical Approach | Example |
| :--- | :--- | :--- | :--- |
| **Arrays & Hashing** | Need instant $O(1)$ lookups or frequency counts | `std::unordered_map` or `std::unordered_set` | Two Sum, Valid Anagram, Group Anagrams |
| **Two Pointers** | Sorted arrays, palindrome symmetry, in-place deduplication | Converging (`left`/`right`) or Fast/Slow pointers | Valid Palindrome, Reverse String, Remove Duplicates |
| **Stack (LIFO)** | Nested structures, adjacent pair cancellation, matching tags | Push to stack, match/cancel against `.top()` | Valid Parentheses, Remove Adjacent Duplicates |
| **Priority Queue** | Top-K elements, stream processing | Min-Heap of size $K$ ($O(N \log K)$) | Kth Largest Element |
| **Binary Search** | Sorted sequences, searching over monotonic range | `std::lower_bound` / `std::upper_bound` | Binary Search, Lower Bound Index |
| **Boyer-Moore Voting**| Find element occurring $> 50\%$ of the time | Single pass: candidate + counter cancellation | Majority Element |
