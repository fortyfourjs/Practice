# Modern C++ Lambdas and Functional Predicates

## 1. Definition
A **Lambda Expression** in Modern C++ is an anonymous, inline callable object (a closure) that can be defined directly at the point of use. Lambdas can capture variables from their enclosing scope by value or by reference.

---

## 2. Why Does It Matter?
- **Inline Expressiveness**: Eliminates the need to write standalone helper functions or verbose functor structs for simple custom operations.
- **Custom Predicates**: Seamlessly customizes standard STL algorithms (like `std::sort`, `std::find_if`, `std::count_if`).
- **Encapsulated Scope**: Captures local state without exposing global or member variables.

---

## 3. How Does It Work?

### Lambda Syntax Breakdown
```cpp
[ capture_clause ] ( parameters ) -> return_type {
    // function body
}
```

### The Capture Clause Explained
| Capture Syntax | Meaning |
| :--- | :--- |
| `[]` | Captures nothing from the enclosing scope |
| `[=]` | Captures all local variables used in the body by **value** (read-only copy) |
| `[&]` | Captures all local variables used in the body by **reference** |
| `[var]` | Captures only `var` by **value** |
| `[&var]` | Captures only `var` by **reference** |
| `[this]` | Captures the enclosing class instance pointer |

Under the hood, the compiler transforms a lambda into an unnamed unique `struct` with an overloaded `operator()`. Captured variables become member fields of that struct!

---

## 4. Practical Example from the Repository: `lambda_produse.cpp`
*(From: `saptamana_4/ziua_22/lambda_produse.cpp`)*

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Produse {
    std::string nume;
    double pret;
};

int main() {
    double prag;
    std::cout << "Introdu pragul de pret:\n";
    std::cin >> prag;

    std::vector<Produse> vectorProduse = {
        {"Produs1", 300.0},
        {"Produs2", 100.0},
        {"Produse3", 455.0},
        {"Produs4", 76.0}
    };

    // 1. Sorting using a stateless lambda comparator:
    std::sort(vectorProduse.begin(), vectorProduse.end(), 
        [](const Produse& p1, const Produse& p2) {
            return p1.pret < p2.pret; // Ascending sort by price
        }
    );

    std::cout << "\nProduse sortate crescator dupa pret:\n";
    for (const auto& p : vectorProduse) {
        std::cout << p.nume << ": " << p.pret << " RON\n";
    }

    // 2. Counting elements using a lambda with explicit state capture:
    // [prag] captures the local variable 'prag' by value so it can be used inside:
    int nrProduseScumpe = std::count_if(vectorProduse.begin(), vectorProduse.end(),
        [prag](const Produse& p) {
            return p.pret > prag;
        }
    );

    std::cout << "\nExista " << nrProduseScumpe << " produse cu pretul peste " << prag << " RON.\n";

    return 0;
}
```

---

## 5. Sorting Unique Pointers with Lambdas
*(From Capstone: `saptamana_4/ziua_24/Library Management/Library.cpp`)*

In the Capstone Library Management project, sorting a `std::vector<std::unique_ptr<Book>>` cannot use standard `operator<` on pointers because that would sort by raw memory addresses! A lambda solves this effortlessly:

```cpp
void Library::sorteazaCarti() {
    std::sort(book_list.begin(), book_list.end(), 
        [](const std::unique_ptr<Book>& a, const std::unique_ptr<Book>& b) {
            return a->getTitlu() < b->getTitlu(); // Sort alphabetically by title
        }
    );
}
```

---

## 6. Common Mistakes and Pitfalls
1. **Dangling References in Async/Escaping Lambdas**:
   Capturing local variables by reference `[&]` when the lambda outlives the current stack frame leads to reading destroyed memory.
2. **Modifying Value Captures without `mutable`**:
   By default, variables captured by value `[x]` are `const` inside the lambda body. To modify the local copy, you must mark the lambda `mutable`: `[x]() mutable { x++; }`.
3. **Overusing `[=]` or `[&]`**:
   Blindly using default captures can accidentally capture large data or hide subtle dependencies. Prefer capturing explicitly (e.g., `[prag]`).

---

## 7. Quick Revision
- Lambdas are inline anonymous functions created at the point of call.
- Syntax: `[capture](params) { body }`.
- `[=]` captures by value; `[&]` captures by reference; `[x]` captures specific variable.
- Essential for STL algorithms: `std::sort`, `std::count_if`, `std::remove_if`.
- Lambdas can dereference and sort smart pointers cleanly without operator overloading.

---

## 8. Repository References
- **Product Sorting & Filtering**: [lambda_produse.cpp](../../saptamana_4/ziua_22/lambda_produse.cpp)
- **Erase-Remove with Lambda**: [lower_bound.cpp](../../Saptamana_2/ziua_10/upper/lower_bound.cpp)
- **Sorting Unique Pointers**: [Library.cpp](../../saptamana_4/ziua_24/Library%20Management/Library.cpp)
