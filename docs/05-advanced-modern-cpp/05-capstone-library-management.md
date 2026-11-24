# Capstone Project Architecture: Library Management System

## 1. Overview
The **Library Management System** located in `saptamana_4/ziua_24/Library Management/` represents the synthesis of the entire C++ learning journey. It demonstrates how modern C++ features integrate into a maintainable, multi-file software architecture:
- **Object-Oriented Design**: Clean separation of concerns between entities (`Book`), repositories (`Library`), and presentation (`main.cpp`).
- **Memory Safety**: Sole ownership managed via `std::vector<std::unique_ptr<Book>>`, ensuring zero memory leaks without manual `delete` calls.
- **Modern Algorithms & Lambdas**: In-place sorting using `std::sort` and lambda expressions.
- **Robust Error Handling**: Structured exception throwing (`std::invalid_argument`, `std::runtime_error`) and recovery.
- **Disk Persistence**: CSV file serialization and stream tokenization via `<fstream>` and `<sstream>`.

---

## 2. Multi-File Architecture

```
saptamana_4/ziua_24/Library Management/
├── Book.h          // Entity declarations (Class interface)
├── Book.cpp        // Entity definitions (Member implementations)
├── Library.h       // Repository declarations (Collection & API)
├── Library.cpp     // Repository definitions (File I/O, borrow logic, sorting)
├── main.cpp        // Presentation layer (Interactive CLI menu & exception loops)
└── carti.txt       // Persistent storage (CSV file)
```

---

## 3. Component Deep Dive

### 1. The `Book` Entity
Encapsulates book state: title, author, ISBN, and availability flag (`disponibil`).
- Uses `const` member functions for all inspectors (`getTitlu() const`, `isDisponibil() const`).
- Protects internal state behind setters (`setDisponibil(bool stare)`).

### 2. The `Library` Controller & Memory Architecture
Instead of using raw arrays (`Book* arr = new Book[...]`) or copying large objects, `Library` owns books through unique pointers:
```cpp
class Library {
private:
    std::vector<std::unique_ptr<Book>> book_list;
    ...
};
```

#### Why `std::vector<std::unique_ptr<Book>>`?
1. **Ownership Guarantee**: `Library` has sole, unambiguous ownership of all books.
2. **Move-Only Semantics**: When a book is added, `carte` is transferred using `std::move()`:
   ```cpp
   auto carte = std::make_unique<Book>(titlu, autor, isbn, stare);
   book_list.push_back(std::move(carte));
   ```
3. **Automatic Cleanup**: When `Library` is destroyed, the vector's destructor destroys all `unique_ptr`s, which in turn automatically free each `Book` on the heap. Zero leaks!

### 3. Algorithm Integration: Sorting by Title
*(From: `Library.cpp`)*
```cpp
void Library::sorteazaCarti() {
    std::sort(book_list.begin(), book_list.end(), 
        [](const std::unique_ptr<Book>& a, const std::unique_ptr<Book>& b) {
            return a->getTitlu() < b->getTitlu();
        }
    );
}
```
The lambda comparator dereferences the smart pointers (`a->getTitlu()`), enabling the standard library's Introsort to reorder pointers based on book titles in $O(N \log N)$ time.

### 4. Persistence Engine: CSV Stream Processing
- **Writing**: `salveazaInFisier` streams CSV records line-by-line: `title,author,isbn,state\n`.
- **Reading**: `incarcaDinFisier` parses records using `std::stringstream`:
  ```cpp
  std::stringstream ss(linie);
  std::getline(ss, titlu, ',');
  std::getline(ss, autor, ',');
  std::getline(ss, isbn, ',');
  std::getline(ss, stareStr, ',');
  ```

---

## 4. Code Review and Identified Improvements

While the capstone project is well-structured and functional, our repository audit revealed three practical edge-cases worth noting for production readiness:

### 1. Vector Duplication on File Reload
In `Library.cpp`:
```cpp
void Library::incarcaDinFisier(const std::string& numeFisier) {
    // Recommendation: Clear existing books before loading:
    book_list.clear(); 
    ...
}
```
*Issue*: Without `book_list.clear()`, calling load multiple times appends duplicate entries.

### 2. Guarding Against Malformed / Blank CSV Records
In `carti.txt`, the first line is:
```csv
,,,0
```
This causes `adaugaCarte("", "", "", false)` to create an empty book.
*Fix*: Check if `titlu.empty()` before instantiating:
```cpp
if (!titlu.empty()) {
    adaugaCarte(titlu, autor, isbn, stare);
}
```

### 3. Stream State Recovery on Invalid Menu Input
In `main.cpp`, if the user types letters instead of an integer operation number (e.g., `cin >> numar_operatie`), `std::cin` enters a fail state.
*Fix*: Add input sanitation:
```cpp
if (!(std::cin >> numar_operatie)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Te rugam sa introduci un numar valid!\n";
    continue;
}
```

---

## 5. Quick Revision
- The Capstone demonstrates clean modular architecture with `.h` headers and `.cpp` implementation files.
- `std::vector<std::unique_ptr<Book>>` provides optimal, leak-proof dynamic memory management.
- `std::sort` combined with custom lambdas sorts collections of smart pointers cleanly.
- CSV parsing combines `std::ifstream`, `std::getline`, and `std::stringstream`.
- Always clear collections before re-populating from disk and validate non-empty tokens.

---

## 6. Repository References
- **Entity Header**: [Book.h](../../saptamana_4/ziua_24/Library%20Management/Book.h)
- **Entity Implementation**: [Book.cpp](../../saptamana_4/ziua_24/Library%20Management/Book.cpp)
- **Repository Header**: [Library.h](../../saptamana_4/ziua_24/Library%20Management/Library.h)
- **Repository Implementation**: [Library.cpp](../../saptamana_4/ziua_24/Library%20Management/Library.cpp)
- **Main Driver Program**: [main.cpp](../../saptamana_4/ziua_24/Library%20Management/main.cpp)
- **CSV Data File**: [carti.txt](../../saptamana_4/ziua_24/Library%20Management/carti.txt)
