# Inheritance vs. Composition in C++

## 1. Definition
- **Inheritance** is an OOP mechanism where a new class (**Derived Class** or Subclass) acquires properties and behaviors from an existing class (**Base Class** or Superclass). It models an **"is-a"** relationship (e.g., A `Developer` *is-an* `Employee`).
- **Composition** is a design principle where a class contains one or more instances of other classes as member variables. It models a **"has-a"** relationship (e.g., A `Library` *has-a* collection of `Book`s).

---

## 2. Why Does It Matter?
- **Code Reuse**: Avoids rewriting shared logic across related domains.
- **Polymorphism Enabler**: Public inheritance establishes subtyping, allowing derived objects to be manipulated through base class pointers and references.
- **"Prefer Composition Over Inheritance"**: In software engineering, composition provides loose coupling, easier testing, and dynamic runtime flexibility, whereas deep inheritance hierarchies introduce rigid coupling.

---

## 3. How Does It Work?

### Inheritance Mechanics & Access Levels
When inheriting publicly:
- `public` members of the Base remain `public` in the Derived.
- `protected` members of the Base are accessible inside Derived member functions, but hidden from external code.
- `private` members of the Base remain strictly hidden from Derived classes.

### Constructor Chaining
When a Derived object is instantiated:
1. The **Base class constructor** runs first.
2. The **Derived class constructor** runs second.
Destruction occurs in the exact reverse order.

---

## 4. Practical Examples from the Repository

### Example 1: Inheritance ("is-a")
*(From: `saptamana_3_OOP/ziua_15_mostenire_compozitie/employee.cpp`)*

```cpp
#include <iostream>
#include <string>

// Base Class
class Employee {
protected:
    std::string name;
    int id;
    double salary;

public:
    Employee(std::string n, int i, double s) 
        : name(n), id(i), salary(s) {}

    void printInfo() const {
        std::cout << "Nume: " << name << " | ID: " << id << " | Salariu: " << salary << '\n';
    }
};

// Derived Class
class Developer : public Employee {
private:
    std::string programmingLanguage;

public:
    // Calling Base constructor via member initializer list:
    Developer(std::string n, int i, double s, std::string lang) 
        : Employee(n, i, s), programmingLanguage(lang) {}

    void printDevInfo() const {
        printInfo(); // Reusing base class method
        std::cout << "Limbaj: " << programmingLanguage << '\n';
    }
};

int main() {
    Developer dev("Alex", 101, 7500.0, "C++");
    dev.printDevInfo();
    return 0;
}
```

### Example 2: Composition ("has-a")
*(From: `saptamana_3_OOP/ziua_15_mostenire_compozitie/book_compozitie.cpp`)*

```cpp
#include <iostream>
#include <vector>
#include <string>

class Book {
private:
    std::string title;
    std::string author;

public:
    Book(std::string t, std::string a) : title(t), author(a) {}
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
};

// Library HAS-A collection of Books
class Library {
private:
    std::vector<Book> books; // Composition!

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void showBooks() const {
        for (const auto& b : books) {
            std::cout << "Titlu: " << b.getTitle() << " | Autor: " << b.getAuthor() << '\n';
        }
    }
};
```

---

## 5. Architectural Decision: When to Choose What?
| Metric | Inheritance (`is-a`) | Composition (`has-a`) |
| :--- | :--- | :--- |
| **Relationship** | Class A is a specialized type of Class B | Class A contains Class B as a building block |
| **Coupling** | Tight (changes to Base affect Derived) | Loose (changes to component rarely affect host) |
| **Polymorphism** | Yes, allows dynamic runtime dispatch | No direct subtyping polymorphism |
| **Flexibility** | Static (fixed at compile time) | Dynamic (components can be swapped or added at runtime) |
| **Rule of Thumb** | Use when you need polymorphic base pointers | Use for almost all other structural relationships |

---

## 6. Quick Revision
- Inheritance models `is-a`; derived classes extend base classes.
- Derived constructors must invoke the base class constructor in their member initializer list.
- Use `protected` to allow derived classes access to internal variables while keeping them hidden from client code.
- Composition models `has-a` and is generally preferred for flexibility and low coupling.

---

## 7. Repository References
- **Inheritance Example**: [employee.cpp](../../saptamana_3_OOP/ziua_15_mostenire_compozitie/employee.cpp)
- **Composition Example**: [book_compozitie.cpp](../../saptamana_3_OOP/ziua_15_mostenire_compozitie/book_compozitie.cpp)
- **Advanced Composition with Smart Pointers**: [Library.h](../../saptamana_4/ziua_24/Library%20Management/Library.h)
