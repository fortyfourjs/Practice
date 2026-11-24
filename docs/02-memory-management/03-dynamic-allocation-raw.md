# Raw Dynamic Memory Allocation: new, delete, and Safety Hazards

## 1. Definition
**Dynamic Memory Allocation** is the process by which a program requests blocks of memory from the operating system's heap at runtime. In C++, dynamic allocation is initiated using the `new` (single object) or `new[]` (array of objects) operators, and released back to the free store using `delete` or `delete[]`.

---

## 2. Why Does It Matter?
Compile-time array sizing (`int arr[100];`) requires array dimensions to be known in advance. Dynamic memory allocation solves this limitation:
- **Runtime Sizing**: Arrays can be sized based on dynamic user input or file contents.
- **Large Capacity**: Allows allocating gigabytes of data exceeding the limited stack size.
- **Unbounded Lifetimes**: Data persists across multiple function calls and returns until explicitly destroyed.

However, raw dynamic allocation is notoriously error-prone, as C++ enforces **manual memory management** when smart pointers are not used.

---

## 3. How Does It Work?

### Single Object vs. Array Allocation
```cpp
// 1. Single Object
int* p = new int(42);       // Allocates 4 bytes on heap, initializes to 42
delete p;                   // Deallocates heap memory
p = nullptr;                // Reset pointer to null

// 2. Array Allocation
int* arr = new int[5]{1,2,3,4,5}; // Allocates contiguous block + stores array size metadata
delete[] arr;                     // Calls destructors and frees the entire block
arr = nullptr;
```

### The Mechanism of `delete[]` vs. `delete`
When `new Type[N]` is executed, the runtime allocator typically writes an internal header (sometimes called a **heap cookie** or array size prefix) right before the memory address returned to the programmer. This header records the number of elements $N$.
- When you call `delete[] arr;`, the runtime reads this header, calls the destructor for all $N$ objects, and deallocates the block.
- If you mistakenly call `delete arr;` (scalar delete) on an array, the compiler treats it as a single object: only the first element's destructor is run, and the allocator may corrupt internal heap metadata, causing **Undefined Behavior (UB)** or program crashes!

---

## 4. Memory Visualization: Heap Lifecycle and Hazards

```
1. ALLOCATED STATE:
Stack: [ arr: 0x5000 ] ------> Heap: [0x5000: Element 0 | 0x5004: Element 1 | 0x5008: Element 2]

2. AFTER delete[] arr (WITHOUT nullptr):
Stack: [ arr: 0x5000 ] ------> Heap: [ FREED / RECLAIMED BY OS / GARBAGE DATA ]
         ^
         |__ DANGLING POINTER! The pointer still holds 0x5000! Dereferencing *arr causes UB!

3. SAFE PRACTICE (arr = nullptr):
Stack: [ arr: 0x00000000 (nullptr) ]
         ^
         |__ Safe! Deleting nullptr is a legal no-op. Accidental access crashes cleanly.
```

---

## 5. Critical Memory Hazards

### Hazard 1: Memory Leaks
Occurs when dynamically allocated memory is never freed. Over time, the application consumes increasing RAM until the system runs out of memory.
*(Studied intentionally in `Saptamana_1/ziua_5/eroare_alocare_dinamica.cpp`)*

### Hazard 2: Dangling Pointers
Occurs when a pointer continues pointing to a memory address after that memory has already been deallocated via `delete`. Accessing a dangling pointer is undefined behavior.

### Hazard 3: Double Free
Occurs when `delete` or `delete[]` is invoked twice on the same memory address:
```cpp
int* p = new int(10);
delete p;
delete p; // CRASH! Heap corruption!
```

### Hazard 4: Mixing `new[]` with scalar `delete`
Undefined behavior resulting from incorrect allocator cleanup.

---

## 6. Practical Examples from the Repository

### Example 1: Dynamic Vector Input and Proper Cleanup
*(From: `Saptamana_1/ziua_5/alocare_dinamica_vector.cpp` and `Saptamana_2/ziua_11/alocare_dinamica.cpp`)*

```cpp
#include <iostream>

int main() {
    int dimensiune;
    std::cout << "Ce dimensiune vrei sa aiba vectorul?\n";
    std::cin >> dimensiune;

    // 1. Allocation on the heap
    int* vector_dinamic = new int[dimensiune];

    for (int i = 0; i < dimensiune; i++) {
        std::cin >> vector_dinamic[i];
    }

    // 2. Deallocation: Must use delete[] for arrays
    delete[] vector_dinamic;

    // 3. Prevent dangling pointer
    vector_dinamic = nullptr;

    return 0;
}
```

### Example 2: Heap Exhaustion and `std::bad_alloc`
*(From: `Saptamana_1/ziua_5/eroare_alocare_dinamica.cpp`)*

```cpp
#include <iostream>

int main() {
    int pas = 1;
    // Repeatedly allocating 40MB chunks without freeing
    while (true) {
        // 10,000,000 ints * 4 bytes = ~40 MB per iteration
        int* vector_dinamic = new int[10000000];
        vector_dinamic[0] = 7; 
        
        std::cout << "Pasul " << pas << ": Am alocat ~40 MB. Adresa: " << vector_dinamic << '\n';
        pas++;
        // NOTE: Memory is never deleted! Eventually throws std::bad_alloc!
    }
    return 0;
}
```
> [!WARNING]
> This code demonstrates what happens during a severe memory leak. If the OS runs out of available virtual memory, `new` fails and throws the exception `std::bad_alloc`.

### Example 3: Returning Dynamic Arrays (The Ownership Dilemma)
*(From: `Saptamana_1/ziua_5/filtreaza_nr_pare.cpp`)*

```cpp
int* filtreaza_pare(int* arr, int dimensiune, int& dimensiune_noua) {
    int count = 0;
    for (int i = 0; i < dimensiune; i++) {
        if (arr[i] % 2 == 0) count++;
    }
    dimensiune_noua = count;
    
    // Function allocates memory on heap:
    int* rezultat = new int[dimensiune_noua];
    int index_nou = 0;
    for (int i = 0; i < dimensiune; i++) {
        if (arr[i] % 2 == 0) {
            rezultat[index_nou++] = arr[i];
        }
    }
    return rezultat; // CALLER MUST REMEMBER TO DELETE THIS!
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int dim = 0;
    int* pare = filtreaza_pare(arr, 8, dim);

    delete[] pare;  // Caller successfully takes ownership and frees
    pare = nullptr;
    return 0;
}
```
> [!NOTE]
> While `filtreaza_nr_pare.cpp` correctly frees the memory in `main()`, returning raw dynamic pointers creates **ambiguous ownership**. If another developer calls `filtreaza_pare` and forgets to delete `pare`, a leak is guaranteed. Modern C++ solves this cleanly by returning `std::vector<int>` or `std::unique_ptr<int[]>`.

---

## 7. `NULL` vs. `nullptr`
- In legacy C and old C++, `NULL` is a macro defined as integer `0` or `(void*)0`. This creates ambiguity in overloaded functions: `void func(int)` vs `void func(int*)`.
- In Modern C++ (C++11 and later), `nullptr` is a distinct literal of type `std::nullptr_t`. It can only implicitly convert to pointer types, never to integers, guaranteeing type safety.

---

## 8. Quick Revision
- `new` pairs with `delete`; `new[]` pairs with `delete[]`. Mixing them triggers undefined behavior.
- Memory allocated with `new` persists until `delete` is called.
- A **memory leak** occurs when allocated memory is no longer referenced but never freed.
- A **dangling pointer** points to already-freed memory; set pointers to `nullptr` immediately after `delete`.
- Passing raw heap pointers out of functions obscures ownership and causes leaks; prefer RAII.

---

## 9. Repository References
- **Dynamic Array Allocation**: [alocare_dinamica_vector.cpp](../../Saptamana_1/ziua_5/alocare_dinamica_vector.cpp)
- **Heap Exhaustion Experiment**: [eroare_alocare_dinamica.cpp](../../Saptamana_1/ziua_5/eroare_alocare_dinamica.cpp)
- **Returning Heap Memory**: [filtreaza_nr_pare.cpp](../../Saptamana_1/ziua_5/filtreaza_nr_pare.cpp)
- **Heap Duplication**: [duplicare_tablou.cpp](../../Saptamana_2/ziua_11/duplicare_tablou.cpp)
