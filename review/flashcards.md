# C++ Flashcards for Rapid Active Recall

Test your conceptual mastery. Read the question, formulate your technical answer, and expand the card to check your understanding.

---

### Flashcard 01: Pointers vs. References
<details>
<summary><b>Q: What is the exact difference between a pointer and a reference in C++?</b></summary>

**Answer:**
- A **pointer** is an independent variable that holds a memory address. It can be reassigned to point elsewhere, can be null (`nullptr`), can be left uninitialized (wild pointer), and supports pointer arithmetic.
- A **reference** is an alias for an existing object. It must be bound upon declaration, cannot be rebound to refer to another object, cannot be null, and has no independent address of its own.
</details>

---

### Flashcard 02: RAII
<details>
<summary><b>Q: What is RAII, and what fundamental problem does it solve?</b></summary>

**Answer:**
**RAII** (Resource Acquisition Is Initialization) is a C++ idiom where a resource (heap memory, file handle, socket, mutex) is acquired in an object's constructor and released automatically in its destructor. It solves memory leaks and resource leaks by guaranteeing deterministic cleanup upon scope exit and during exception stack unwinding.
</details>

---

### Flashcard 03: unique_ptr Scope Exit
<details>
<summary><b>Q: What exactly happens when a `std::unique_ptr` goes out of scope?</b></summary>

**Answer:**
The destructor of `std::unique_ptr` executes automatically. If it currently owns an object (i.e., its internal raw pointer is not `nullptr`), it calls `delete` (or `delete[]` for array specializations) on the managed heap pointer, immediately freeing the heap memory.
</details>

---

### Flashcard 04: Stack vs. Heap
<details>
<summary><b>Q: What is the difference between stack and heap memory allocation?</b></summary>

**Answer:**
- **Stack Allocation**: Managed automatically by CPU hardware. Blazing fast (1 instruction pointer adjustment). Fixed small size (1-8 MB). Objects have automatic storage duration and are destroyed when their `{}` scope ends.
- **Heap Allocation**: Managed manually via the OS free store (`new`/`delete` or smart pointers). Slower allocation time due to search and fragmentation overhead. Unbounded lifetime: objects persist until explicitly freed.
</details>

---

### Flashcard 05: Dangling Pointer
<details>
<summary><b>Q: What is a dangling pointer, and how do you prevent it?</b></summary>

**Answer:**
A dangling pointer is a pointer that continues to store the memory address of an object that has already been deallocated. Dereferencing it causes undefined behavior.
**Prevention**:
1. Assign raw pointers to `nullptr` immediately after `delete`.
2. Prefer modern smart pointers (`std::unique_ptr`, `std::shared_ptr`) which prevent dangling pointers.
</details>

---

### Flashcard 06: std::move
<details>
<summary><b>Q: What does `std::move` actually do, and when should you use it?</b></summary>

**Answer:**
`std::move` does not move any memory at runtime! It is an unconditional compile-time static cast that converts an lvalue into an rvalue reference (`T&&`). This signals to the compiler that the object can be "pilfered" by a Move Constructor or Move Assignment Operator without expensive copying.
**When to use**: When you want to transfer ownership of a resource (e.g., passing a `std::unique_ptr` into a function or container).
</details>

---

### Flashcard 07: new vs new[]
<details>
<summary><b>Q: Why is calling scalar `delete` on an array allocated with `new[]` undefined behavior?</b></summary>

**Answer:**
When allocating an array `new T[N]`, the runtime allocator writes an internal header (heap cookie) storing the array length $N$.
`delete[]` reads this header, calls destructors for all $N$ objects, and frees the entire block. Calling scalar `delete` assumes a single object: only the first destructor runs, and the allocator attempts to free the memory using wrong metadata, corrupting the heap.
</details>

---

### Flashcard 08: Virtual Destructors
<details>
<summary><b>Q: Why must a Base class destructor be declared `virtual` if it has virtual methods?</b></summary>

**Answer:**
If an object of a derived class is deleted through a base class pointer (`Base* p = new Derived(); delete p;`), and the base destructor is **not** virtual, only `~Base()` is executed! The derived destructor `~Derived()` is skipped, causing memory leaks and undefined behavior. Declaring `virtual ~Base() = default;` ensures dynamic dispatch calls `~Derived()` first.
</details>

---

### Flashcard 09: Shallow Copy vs. Deep Copy
<details>
<summary><b>Q: Why is a shallow copy dangerous for classes managing raw pointers?</b></summary>

**Answer:**
A shallow copy duplicates the pointer's memory address, meaning both objects point to the same heap block. When both objects are destroyed, their destructors attempt to free the same heap block twice (**Double Free**), corrupting the heap and crashing the program.
</details>

---

### Flashcard 10: Rule of Three / Five
<details>
<summary><b>Q: What is the Rule of Three, and what functions make up the Rule of Five?</b></summary>

**Answer:**
- **Rule of Three**: If a class manages a raw resource and defines one of:
  1. Destructor
  2. Copy Constructor
  3. Copy Assignment Operator
  it must explicitly define all three.
- **Rule of Five**: In Modern C++, add:
  4. Move Constructor
  5. Move Assignment Operator
  to avoid unnecessary copies of expiring objects.
</details>

---

### Flashcard 11: unordered_map vs map
<details>
<summary><b>Q: What are the primary differences between `std::map` and `std::unordered_map`?</b></summary>

**Answer:**
- `std::map`: Implemented as a Red-Black BST. Elements are strictly sorted. Guaranteed $O(\log N)$ search, insertion, and deletion.
- `std::unordered_map`: Implemented as a Hash Table. Elements are stored in arbitrary order across buckets. Amortized $O(1)$ average search, insertion, and deletion ($O(N)$ worst-case on collisions).
</details>

---

### Flashcard 12: Object Slicing
<details>
<summary><b>Q: What is object slicing in C++, and how do you prevent it?</b></summary>

**Answer:**
Object slicing occurs when a derived class instance is assigned to a base class object **by value** (`Base b = derivedObj;`). The derived portion and the `vptr` are sliced off, leaving only the base sub-object.
**Prevention**: Always pass and store polymorphic objects by reference (`const Base&`) or smart pointer (`std::unique_ptr<Base>`).
</details>

---

### Flashcard 13: Erase-Remove Idiom
<details>
<summary><b>Q: How does the Erase-Remove idiom work for filtering vectors?</b></summary>

**Answer:**
`std::remove_if` shifts all elements that do *not* match the condition to the front of the vector in $O(N)$ time and returns an iterator to the new logical end. Then, `vector::erase(newEnd, v.end())` shrinks the vector's size in $O(1)$ without shifting.
</details>

---

### Flashcard 14: Lambda Captures
<details>
<summary><b>Q: What is the difference between `[=]` and `[&]` in a lambda expression?</b></summary>

**Answer:**
- `[=]`: Captures all referenced outer local variables by **value** (read-only copies).
- `[&]`: Captures all referenced outer local variables by **reference**. Modifying them inside the lambda mutates the original outer variables.
</details>
