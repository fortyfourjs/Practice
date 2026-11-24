# Variables, Fundamental Types, and Memory Representation

## 1. Definition
In C++, a **variable** is a named storage location in computer memory that holds a value of a specific **type**. The type determines the variable's size in bytes, its internal representation (e.g., two's complement for signed integers, IEEE 754 for floating-point numbers), the valid operations that can be performed on it, and its memory alignment requirements.

---

## 2. Why Does It Matter?
Unlike interpreted or garbage-collected languages (such as Python or JavaScript), C++ gives developers direct access to physical memory addresses, exact byte layouts, and hardware-level operations:
- **Predictable Performance**: Memory layout is deterministic without runtime VM overhead.
- **Cache Locality**: Contiguous storage of primitive types in arrays or vectors maximizes CPU L1/L2 cache efficiency.
- **Hardware Interfacing**: Understanding exact bit patterns and byte sizes allows direct interaction with OS system calls, network sockets, and hardware registers.

---

## 3. How Does It Work?
Every variable possesses four core attributes:
1. **Name (Identifier)**: The symbolic label used in code.
2. **Type**: Dictates the byte size and interpretation rules.
3. **Address (`&var`)**: The hexadecimal location in physical/virtual memory where the first byte is stored.
4. **Value**: The binary bits stored across the variable's memory addresses.

When you declare `int x = 10;`, the compiler reserves 4 bytes (typically on 32-bit/64-bit systems) on the current stack frame. The variable name `x` is mapped to an offset from the stack base pointer.

### Common Primitive Types and Typical Sizes
| Type | Typical Size (x86/x64) | Value Range | Memory Representation |
| :--- | :--- | :--- | :--- |
| `bool` | 1 byte | `true` (1), `false` (0) | Byte flag |
| `char` | 1 byte | -128 to 127 (or 0 to 255) | ASCII code |
| `int` | 4 bytes | $-2^{31}$ to $2^{31}-1$ | Two's complement integer |
| `double` | 8 bytes | $\pm 1.7 \times 10^{\pm 308}$ | IEEE 754 double precision |
| `size_t` | 8 bytes (64-bit) | $0$ to $2^{64}-1$ | Unsigned machine word |

---

## 4. Syntax & Operators
```cpp
// 1. Declaration and Initialization (Modern C++ Brace-Initialization)
int age{25};                  // Direct brace initialization (prevents narrowing conversions)
double balance = 1500.50;     // Copy initialization
char grade = 'A';             // Character literal in single quotes

// 2. Querying Size and Memory Addresses
std::cout << sizeof(age) << " bytes\n";  // Query size in bytes
std::cout << &age << "\n";               // Address-of operator '&'
```

---

## 5. Memory Visualization
Consider declaring two contiguous variables and an array:
```cpp
char ch = 'A';       // 1 byte, ASCII 65 (0x41)
int count = 42;      // 4 bytes, 0x0000002A
```

```
Stack Memory (Addresses increase downwards or upwards depending on ABI):
+-----------------+-------------------+---------------+
| Memory Address  | Variable Name     | Stored Value  |
+-----------------+-------------------+---------------+
| 0x7ffd10a4      | ch (char, 1 byte) | 'A' (0x41)    |
| 0x7ffd10a5..a7  | [padding bytes]   | (alignment)   |
| 0x7ffd10a8..ab  | count (int, 4 B)  | 42 (0x0000002A|
+-----------------+-------------------+---------------+
```

When elements are placed in a container or array (as studied in `citire_vector.cpp`), memory is strictly contiguous:
```
&vec[0] = 0x7ffee000 (offset +0)
&vec[1] = 0x7ffee004 (offset +4 bytes for int)
&vec[2] = 0x7ffee008 (offset +8 bytes for int)
```

---

## 6. Practical Examples & Code Analysis

### Example 1: Inspecting Memory Addresses and Sizes
*(From repository file: `Saptamana_1/ziua_2/citire_vector.cpp`)*

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> vocale {"a", "e", "i", "o", "u"};
    
    // Inspecting size of char
    std::cout << "sizeof(char): " << sizeof(char) << " byte(s)\n";
    
    // Memory addresses of elements in the vector
    std::cout << "Address 0: " << &vocale[0] << "\n";
    std::cout << "Address 1: " << &vocale[1] << "\n";
    std::cout << "Address 2: " << &vocale[2] << "\n";

    return 0;
}
```

### Key Observation:
In `citire_vector.cpp`, printing `&vocale[0]` displays the address of the `std::string` object within the vector's heap buffer. Notice that contiguous elements are separated by `sizeof(std::string)` (which is 24 or 32 bytes depending on the standard library implementation).

---

## 7. Common Mistakes and Pitfalls
1. **Narrowing Conversions**:
   ```cpp
   int x = 3.99; // Silently truncates to 3 without warning
   int y{3.99};  // COMPILE ERROR with brace-initialization (guaranteed type safety)
   ```
2. **Uninitialized Primitive Variables**:
   In C++, local primitive variables are not zero-initialized by default. Reading them produces **Undefined Behavior (UB)** with garbage stack data.
   ```cpp
   int score; // Garbage value!
   int score{}; // Zero-initialized (0)
   ```
3. **Signed/Unsigned Comparison**:
   Comparing signed `int` with unsigned `size_t` (e.g., `for (int i = 0; i < v.size(); i++)`) causes implicit promotion of negative integers to large positive values, risking loop bugs. Always use `size_t` or `auto`.

---

## 8. When Should I Use What?
- Use `int` for general counting and indexing when values fit within $\pm 2 \times 10^9$.
- Use `size_t` for container sizes, memory offsets, and array indexing.
- Use `double` for real numbers unless working in embedded systems or strict memory constraints where `float` is explicitly required.
- Use `bool` for conditional flags.

---

## 9. Quick Revision
- A variable binds a symbolic name to a memory address, byte size, and interpretation type.
- The `sizeof` operator returns the memory size in bytes at compile time.
- The address-of operator `&` retrieves the memory address of an lvalue.
- Modern C++ strongly favors uniform brace initialization `{}` to avoid accidental truncation and garbage values.
- Fundamental types stored consecutively form contiguous memory blocks, essential for fast CPU cache access.

---

## 10. Repository References
- **Original Experiment**: [citire_vector.cpp](../../Saptamana_1/ziua_2/citire_vector.cpp)
- **Vector Indexing & Sizes**: [vector_ex.cpp](../../Saptamana_1/ziua_2/vector_ex.cpp)
