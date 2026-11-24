# Pointers and Pointer Arithmetic

## 1. Definition
A **pointer** is a compound variable type whose value is the **memory address** of another object or variable in memory.

**Pointer Arithmetic** is the set of operations (addition, subtraction, increment, decrement) performed directly on pointers. Crucially, pointer arithmetic is typed: advancing a pointer by `+1` moves it forward by `sizeof(T)` bytes in memory.

---

## 2. Why Does It Matter?
- **Low-Level Memory Access**: Pointers allow software to inspect and manipulate hardware memory structures, operating system buffers, and network packets.
- **Dynamic Array Traversal**: Enables efficient iteration through contiguous memory blocks without array index calculations.
- **Polymorphic Interfaces**: Base class pointers (`Base*`) are the fundamental mechanism for dynamic runtime polymorphism in C++.

---

## 3. How Does It Work?

### Pointer Mechanics and Syntax
- Address-of Operator (`&`): Retrieves the hexadecimal memory address of a variable.
- Dereference Operator (`*`): Accesses or modifies the value stored at the address pointed to.
- Reassignment: Pointers can be changed at any time to point to a completely different memory address.

```cpp
int x = 10;
int y = 50;

int* p = &x;  // 'p' holds the memory address of 'x'
*p = 20;      // Dereferencing: 'x' is now 20!

p = &y;       // 'p' now holds the memory address of 'y'
*p = 100;     // 'y' is now 100!
```

### Pointer Decay
When a raw C-style array is passed to a function, it **decays** into a pointer to its first element (`T*`), losing all information about its original size:
```cpp
void inspect(int arr[]) // Internally compiled as: void inspect(int* arr)
{
    // sizeof(arr) here returns sizeof(int*) (8 bytes on 64-bit), NOT array length!
}
```

### Pointer Arithmetic Mechanics
If `int* ptr` points to address `0x1000` (assuming 4-byte integers):
- `ptr + 1` evaluates to address `0x1004` (moves forward by $1 \times 4$ bytes)
- `ptr + 3` evaluates to address `0x100C` (moves forward by $3 \times 4$ bytes)
- `*(ptr + i)` is exactly equivalent to `ptr[i]`
- Pointer subtraction `ptr2 - ptr1` returns the number of *elements* between them (of type `std::ptrdiff_t`), not raw bytes.

---

## 4. Memory Visualization

Let's trace array reversal using two pointers from `duplicare_tablou.cpp`:
```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* left = arr;               // Points to arr[0] (0x2000)
int* right = arr + 5 - 1;       // Points to arr[4] (0x2010)
```

```
Addresses:    0x2000    0x2004    0x2008    0x200C    0x2010
Elements:   [   10   |   20   |   30   |   40   |   50   ]
                ^                                       ^
                |                                       |
              left                                    right
             (0x2000)                                (0x2010)

Iteration 1: swap(*left, *right) -> 10 and 50 swap.
Advance:     left++  (becomes 0x2004)
             right-- (becomes 0x200C)

Addresses:    0x2000    0x2004    0x2008    0x200C    0x2010
Elements:   [   50   |   20   |   30   |   40   |   10   ]
                          ^                   ^
                          |                   |
                        left                right
```

---

## 5. Practical Examples from the Repository

### Example 1: Pointer Basic Assignment & Dereferencing
*(From: `Saptamana_1/ziua_5/pointeri.cpp`)*

```cpp
#include <iostream>

int main() {
    int x = 10;
    int y = 50;
    int *p = &x;
    std::cout << "x initially: " << x << '\n'; // 10
    
    *p = 20; // Mutates x via pointer dereference
    std::cout << "x after *p = 20: " << x << '\n'; // 20
    
    p = &y;  // Re-points p to y
    *p = 100;
    std::cout << "x=" << x << " y=" << y << '\n'; // x=20 y=100
    return 0;
}
```

### Example 2: In-Place Array Reversal via Pointer Arithmetic
*(From: `Saptamana_2/ziua_11/duplicare_tablou.cpp`)*

```cpp
void reverseArray(int* arr, int size) {
    int* left = arr;
    int* right = arr + size - 1; // Address of last element
    
    for (int i = 0; i < size / 2; i++) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;   // Advance forward by 4 bytes
        right--;  // Move backward by 4 bytes
    }
}
```

### Example 3: Subscript Notation vs. Dereference Offset
*(From: `Saptamana_2/ziua_11/duplicare_tablou.cpp`)*

```cpp
// These two expressions access identical memory locations:
*(copie + i) == copie[i]
```

---

## 6. Common Mistakes and Pitfalls
1. **Uninitialized (Wild) Pointers**:
   ```cpp
   int* p; // Contains arbitrary memory address
   *p = 10; // CATASTROPHIC: Writes to random memory! Segmentation fault or data corruption!
   ```
2. **Buffer Overrun / Out of Bounds Arithmetic**:
   Incrementing past the allocated boundary `arr + size` results in reading or writing invalid memory.
3. **Pointer Arithmetic on `void*`**:
   `void*` has no associated type size (`sizeof(void)` is undefined in standard C++). Direct arithmetic on `void*` is illegal.
4. **Confusing Operator Precedence**:
   `*ptr++` dereferences `ptr` and then increments the *pointer*.
   `(*ptr)++` increments the *value* stored at `ptr`.

---

## 7. Quick Revision
- A pointer stores an address; the dereference operator `*` accesses the value at that address.
- Pointer arithmetic automatically scales by the byte size of the target type `T`.
- Array names decay to pointers when passed into functions, losing array size information.
- `*(ptr + i)` is syntactically and functionally identical to `ptr[i]`.
- Always initialize raw pointers to `nullptr` if an object is not immediately available.

---

## 8. Repository References
- **Basic Pointer Operations**: [pointeri.cpp](../../Saptamana_1/ziua_5/pointeri.cpp)
- **Pointer Swap Review**: [swap_pointer.cpp](../../Saptamana_2/ziua_11/swap_pointer.cpp)
- **Two-Pointer Array Reversal via Arithmetic**: [duplicare_tablou.cpp](../../Saptamana_2/ziua_11/duplicare_tablou.cpp)
- **Decayed Array Inversion**: [reverse_vector_dinamic.cpp](../../Saptamana_1/ziua_5/reverse_vector_dinamic.cpp)
