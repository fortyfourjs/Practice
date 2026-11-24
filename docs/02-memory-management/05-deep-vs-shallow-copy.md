# Deep Copy vs. Shallow Copy and the Rule of Three / Five

## 1. Definition
- **Shallow Copy**: Duplicates an object's member variables bit-by-bit. If a member is a pointer, only the *memory address* stored in the pointer is copied, NOT the underlying heap data. Both the original and the copied object end up referencing the exact same physical heap memory.
- **Deep Copy**: Allocates a brand-new, independent block of memory on the heap and duplicates the actual *values* into the new memory block. The original and the copy become completely independent.

---

## 2. Why Does It Matter?
When a class manages raw resources (like dynamic arrays or file handles), relying on the compiler's default shallow copy behavior causes critical bugs:
1. **Double Free Crash**: When both objects go out of scope, their destructors execute `delete[]` on the exact same address, corrupting the heap and crashing the program.
2. **Hidden Side Effects**: Mutating data through one object silently mutates data in the other object.
3. **Dangling Pointers**: If one object is destroyed early, the second object's pointer now points to invalid, deallocated memory.

---

## 3. How Does It Work?

### Visualizing Shallow vs. Deep Copy

```
SHALLOW COPY (Compiler Default - DANGEROUS):
Object A: [ size: 5 | data: 0x8000 ] ----\
                                           +---> [ HEAP: 10, 20, 30, 40, 50 ]
Object B: [ size: 5 | data: 0x8000 ] ----/
                                           |
WHEN Object A IS DESTROYED:                |
delete[] data; -> Heap is freed!          |
                                           v
Object B now holds a DANGLING POINTER!
WHEN Object B IS DESTROYED:
delete[] data; -> CRASH! DOUBLE FREE ERROR!
```

```
DEEP COPY (Custom Copy Constructor - SAFE):
Object A: [ size: 5 | data: 0x8000 ] ---------> [ HEAP 1: 10, 20, 30, 40, 50 ]

Object B: [ size: 5 | data: 0x9500 ] ---------> [ HEAP 2: 10, 20, 30, 40, 50 ]
                                                (Independent allocated copy!)
```

---

## 4. The Rule of Three, Five, and Zero

### The Rule of Three (C++98 / C++03)
If a class explicitly defines any of the following, it must almost certainly define all three:
1. **Destructor**: To release acquired heap memory.
2. **Copy Constructor**: To perform a deep copy when initializing a new object.
3. **Copy Assignment Operator**: To clean up existing memory, handle self-assignment, and perform a deep copy.

### The Rule of Five (Modern C++11 and later)
With the advent of move semantics, two more special member functions complete the set for maximum efficiency:
4. **Move Constructor**: To pilfer resources from an expiring rvalue without copying.
5. **Move Assignment Operator**: To transfer resources in assignment without copying.

### The Rule of Zero
Design your classes so they do not manage raw pointers directly. Use standard RAII types (`std::vector`, `std::string`, `std::unique_ptr`). Then, you define **zero** special member functions, and the compiler-generated defaults are 100% leak-proof and correct!

---

## 5. Practical Implementation: `customBuffer.cpp` Analysis
*(From: `saptamana_3_OOP/ziua_14_deepxshallow_copy/customBuffer.cpp`)*

Below is the implementation studied in the repository, followed by annotations:

```cpp
#include <iostream>

class customBuffer {
private:
    int* data;
    int size;

public:
    // 1. Regular Constructor
    customBuffer(int s) : size(s), data(new int[s]) {
        for (int i = 0; i < size; i++) {
            data[i] = i * 10;
        }
    }

    // 2. Destructor
    ~customBuffer() {
        std::cout << "Destructor: releasing memory at " << data << '\n';
        delete[] data;
    }

    // 3. Deep Copy Constructor
    customBuffer(const customBuffer& other) {
        size = other.size;
        data = new int[size]; // Allocate fresh independent heap block
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i]; // Copy elements
        }
    }

    // 4. Deep Copy Assignment Operator
    customBuffer& operator=(const customBuffer& other) {
        // Step A: Self-assignment check (e.g., b1 = b1)
        if (this == &other) {
            return *this;
        }
        // Step B: Free existing resource currently held by 'this'
        delete[] data;

        // Step C: Allocate new buffer and copy data
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

        // Step D: Return reference to *this for assignment chaining (a = b = c)
        return *this;
    }

    void set(int index, int value) { data[index] = value; }
    void print() const {
        for (int i = 0; i < size; i++) {
            std::cout << "Val: " << data[i] << " at addr: " << &data[i] << '\n';
        }
    }
};

int main() {
    customBuffer b1(5);
    customBuffer b2 = b1; // Invokes Copy Constructor (Deep Copy)
    b1.set(2, 99);        // Mutates b1 only
    
    b1.print();           // b1[2] is 99
    b2.print();           // b2[2] remains 20! Completely independent!
    return 0;
}
```

---

## 6. Supplementary Material: Upgrading to the Rule of Five
*(Extending `customBuffer` to modern C++ move semantics)*

In the original repository implementation, moving a `customBuffer` still invokes the copy constructor. Adding move operations dramatically accelerates performance when returning buffers from functions:

```cpp
// 5. Move Constructor
customBuffer(customBuffer&& other) noexcept 
    : data(other.data), size(other.size) {
    // Steal pointer from other, leave other in safe null state:
    other.data = nullptr;
    other.size = 0;
}

// 6. Move Assignment Operator
customBuffer& operator=(customBuffer&& other) noexcept {
    if (this != &other) {
        delete[] data;        // Free old resource
        data = other.data;    // Steal new resource
        size = other.size;
        other.data = nullptr; // Nullify donor
        other.size = 0;
    }
    return *this;
}
```

---

## 7. Common Mistakes and Pitfalls
1. **Forgetting Self-Assignment Check**:
   In `operator=`, omitting `if (this == &other) return *this;` will cause `b1 = b1;` to delete `b1`'s data, and then read from the deleted memory to populate the new array!
2. **Forgetting to Free Existing Memory in `operator=`**:
   Allocating `new int[size]` without first calling `delete[] data;` leaks the memory previously held by `this`.
3. **Using Shallow Copy with Polymorphic Classes**:
   Copying derived objects through base class pointers causes object slicing. Always implement a virtual clone method (`virtual std::unique_ptr<Base> clone() const = 0;`).

---

## 8. Quick Revision
- A shallow copy copies pointer addresses; a deep copy clones the pointed-to heap data.
- The Rule of Three requires Destructor, Copy Constructor, and Copy Assignment Operator for classes managing raw pointers.
- The Rule of Five adds Move Constructor and Move Assignment Operator for optimal performance.
- In `operator=`, always protect against self-assignment (`this == &other`) and delete existing memory before reallocating.
- The Rule of Zero states that using standard types (`std::vector`, `std::unique_ptr`) eliminates the need to write custom memory management routines.

---

## 9. Repository References
- **Custom Buffer Implementation**: [customBuffer.cpp](../../saptamana_3_OOP/ziua_14_deepxshallow_copy/customBuffer.cpp)
- **Heap Duplication Function**: [duplicare_tablou.cpp](../../Saptamana_2/ziua_11/duplicare_tablou.cpp)
- **Smart Pointer Ownership Transfer**: [move_ptr.cpp](../../Saptamana_2/ziua_12/move_ptr.cpp)
