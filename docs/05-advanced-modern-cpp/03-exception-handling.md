# Exception Handling and Robust Error Management

## 1. Definition
**Exception Handling** in C++ is a structured language mechanism for transferring execution control from the point where an unexpected error or contract violation occurs (`throw`) to an enclosing handler block (`catch`) that knows how to resolve or report the error.

---

## 2. Why Does It Matter?
- **Unignorable Errors**: Unlike integer return error codes (which programmers often forget to check), unhandled exceptions immediately terminate the program safely rather than silently corrupting state.
- **Separation of Concerns**: Keeps the "happy path" clean and readable by separating operational business logic from edge-case error recovery.
- **Stack Unwinding & RAII**: When an exception is thrown, C++ automatically unwinds the call stack, invoking destructors for all local automatic objects in reverse order of creation.

---

## 3. How Does It Work?

### The Standard Exception Hierarchy (`<stdexcept>`)
All standard C++ exceptions derive from `std::exception`:

```
std::exception
 ├── std::logic_error (Errors detectable before execution / contract bugs)
 │    ├── std::invalid_argument (e.g., negative money, divide by 0)
 │    ├── std::out_of_range (e.g., vector::at() index out of bounds)
 │    └── std::length_error
 ├── std::runtime_error (Errors detectable only during runtime / environmental issues)
 │    ├── std::overflow_error
 │    └── std::range_error
 └── std::bad_alloc (Heap out of memory)
```

### Syntax and Catching by Reference
Always catch exceptions by `const std::exception&` to prevent **object slicing** and avoid copying:
```cpp
try {
    // Risky code
} catch (const std::invalid_argument& err) {
    // Specific handler
} catch (const std::exception& err) {
    // Polymorphic fallback handler for all standard exceptions
    std::cerr << err.what() << '\n';
}
```

---

## 4. Practical Examples from the Repository

### Example 1: Mathematical Validation with `std::invalid_argument`
*(From: `saptamana_4/ziua_21/fct_mate.cpp`)*

```cpp
#include <iostream>
#include <stdexcept>

double imparte(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Numitorul nu poate fi 0!\n");
    }
    return a / b;
}

int main() {
    while (true) {
        try {
            double a, b;
            std::cout << "Introdu a si b:\n";
            std::cin >> a >> b;
            double rezultat = imparte(a, b);
            std::cout << "Rezultat: " << rezultat << '\n';
            break; // Success: exit retry loop
        } catch (const std::invalid_argument& err) {
            std::cout << "Eroare: " << err.what(); // Report and prompt again
        }
    }
    return 0;
}
```

### Example 2: Domain-Specific Banking Validation
*(From: `saptamana_4/ziua_21/sistemBancar.cpp`)*

```cpp
#include <iostream>
#include <stdexcept>

double retrageBani(double soldCurent, double sumaDorita) {
    if (sumaDorita <= 0) {
        throw std::invalid_argument("Introdu o suma valida!");
    }
    if (sumaDorita > soldCurent) {
        throw std::runtime_error("Fonduri insuficiente!");
    }
    return soldCurent - sumaDorita;
}
```

### Example 3: Capstone Business Logic Exceptions
*(From: `saptamana_4/ziua_24/Library Management/Library.cpp`)*

```cpp
void Library::imprumutaCarte(const std::string& titlu) {
    for (const auto& carte : book_list) {
        if (titlu == carte->getTitlu()) {
            if (carte->isDisponibil()) {
                carte->setDisponibil(false);
                return;
            } else {
                throw std::runtime_error("Cartea este deja imprumutata!");
            }
        }
    }
    throw std::invalid_argument("Cartea nu exista.");
}
```

---

## 5. Common Mistakes and Pitfalls
1. **Catching by Value**:
   ```cpp
   catch (std::exception err) // BAD: Slices derived classes, losing custom what() messages!
   catch (const std::exception& err) // GOOD: Retains full polymorphism and avoids copying.
   ```
2. **Throwing in Destructors**:
   Destructors are implicitly `noexcept` in modern C++. Throwing an exception inside a destructor while another exception is already unwinding triggers immediate program termination (`std::terminate`).
3. **Leaking Memory on Throw with Raw Pointers**:
   ```cpp
   int* arr = new int[100];
   riskyOperation(); // If this throws, 'delete[] arr' is SKIPPED! LEAK!
   delete[] arr;
   ```
   **Remedy**: Use `std::unique_ptr` or `std::vector`; their destructors are guaranteed to run during stack unwinding.

---

## 6. Quick Revision
- Exceptions report runtime or contract errors using `throw`, `try`, and `catch`.
- Standard exceptions live in `<stdexcept>` and inherit from `std::exception`.
- Always catch by `const std::exception&` to avoid slicing.
- Stack unwinding automatically invokes destructors of local objects when an exception propagates.
- RAII is essential for exception safety; raw pointers cause leaks during exceptions.

---

## 7. Repository References
- **Division by Zero Validation**: [fct_mate.cpp](../../saptamana_4/ziua_21/fct_mate.cpp)
- **Banking Exceptions**: [sistemBancar.cpp](../../saptamana_4/ziua_21/sistemBancar.cpp)
- **Library Management Exceptions**: [Library.cpp](../../saptamana_4/ziua_24/Library%20Management/Library.cpp) and [main.cpp](../../saptamana_4/ziua_24/Library%20Management/main.cpp)
