# Templates and Generic Programming in C++

## 1. Definition
**Templates** are C++'s mechanism for **Generic Programming**. A template is a blueprint or formula that instructs the compiler to generate specialized functions or classes for any data type at compile time.
- **Function Templates**: Generic algorithms operating on abstract type parameters `template<typename T>`.
- **Class Templates**: Generic data structures (like `std::vector<T>` or custom wrappers) parametrized over types.

---

## 2. Why Does It Matter?
- **DRY (Don't Repeat Yourself)**: Eliminates the need to write redundant overloads for `int`, `double`, `float`, and user-defined types.
- **Zero Runtime Overhead**: Templates are resolved entirely at compile time via **monomorphization** (template instantiation), yielding identical machine code performance as hand-written typed functions.
- **Strong Type Safety**: Type checking occurs at compile time, catching type mismatches before execution.

---

## 3. How Does It Work?

### Template Instantiation
When the compiler encounters a template call like `aduna(3, 5)`:
1. It inspects argument types (`int`, `int`).
2. Deduce `T = int`.
3. It generates an actual machine function `int aduna(int, int)` in the binary.
If you later call `aduna(3.5, 2.1)`, it generates a distinct `double aduna(double, double)` function.

```
Template Code in Source:
template<typename T> T aduna(T a, T b) { return a + b; }

Compiler Generates Behind the Scenes:
int aduna(int a, int b) { return a + b; }          // For ints
double aduna(double a, double b) { return a + b; } // For doubles
```

---

## 4. Syntax

```cpp
// Function Template
template<typename T>
T maxim(T a, T b) {
    return (a > b) ? a : b;
}

// Class Template
template<typename T>
class Cutie {
private:
    T continut;
public:
    void setContinut(T v) { continut = v; }
    T getContinut() const { return continut; }
};
```

---

## 5. Practical Examples from the Repository: `templates.cpp`
*(From: `saptamana_4/ziua_19/templates.cpp`)*

```cpp
#include <iostream>
#include <typeinfo>
#include <string>

// Generic addition
template<typename T>
T aduna(T a, T b) {
    return a + b;
}

// Generic maximum selection
template<typename T>
T maxim(T a, T b) {
    return (a > b) ? a : b;
}

// Generic Container Box with RTTI Type Inspection
template<typename T>
class Cutie {
private:
    T continut;
public:
    Cutie() = default;
    void setContinut(T v) { continut = v; }
    T getContinut() const { return continut; }
    void afiseazaTip() const {
        // Inspecting demangled/mangled type name via typeid:
        std::cout << "Tip: " << typeid(T).name() << " | valoare: " << continut << "\n";
    }
};

// Generic Pair
template<typename T>
class Pereche {
private:
    T primul;
    T alDoilea;
public:
    Pereche(T a, T b) : primul(a), alDoilea(b) {}
    T getMaxim() const { return (primul > alDoilea) ? primul : alDoilea; }
    void afiseaza() const {
        std::cout << "[" << primul << ", " << alDoilea << "]\n";
    }
};

int main() {
    int sum = aduna(3, 5);           // Deduced T = int
    double maxVal = maxim(6.5, 8.2); // Deduced T = double

    Cutie<int> cutieInt;
    cutieInt.setContinut(33);
    cutieInt.afiseazaTip();

    Cutie<std::string> cutieStr;
    cutieStr.setContinut("C++ Generics");
    cutieStr.afiseazaTip();

    Pereche<int> p(10, 25);
    p.afiseaza();
    std::cout << "Max in pair: " << p.getMaxim() << '\n';

    return 0;
}
```

---

## 6. Common Mistakes and Pitfalls
1. **Header-Only Requirement**:
   Because the compiler must see the full template implementation to instantiate it, template definitions must reside in **header files (`.h` or `.hpp`)**, not separate `.cpp` translation units!
2. **Unsupported Operators**:
   If a template uses `a > b` and you instantiate it with a type that does not overload `operator>`, a compile error occurs at the site of instantiation.
3. **Type Deduction Mismatch**:
   Calling `aduna(3, 4.5)` fails to compile because the compiler cannot deduce whether `T` should be `int` or `double`. Provide explicit type arguments: `aduna<double>(3, 4.5)`.

---

## 7. Quick Revision
- Templates enable compile-time generic functions and classes.
- Instantiation creates concrete functions for each distinct type used.
- Zero runtime performance cost compared to hand-written functions.
- Class templates require type parameters (e.g., `Cutie<int>`), though C++17 Class Template Argument Deduction (CTAD) allows deduction in constructors.
- Template definitions must be placed in headers.

---

## 8. Repository References
- **Function and Class Templates**: [templates.cpp](../../saptamana_4/ziua_19/templates.cpp)
