# Dynamic Polymorphism, Virtual Functions, and Abstract Classes

## 1. Definition
- **Polymorphism** ("many forms") is the ability in C++ to treat objects of different derived classes uniformly through a common Base class interface.
- **Dynamic (Runtime) Polymorphism**: The mechanism where the decision of which specific member function to execute is made at **runtime**, based on the actual type of the object pointed to, rather than the compile-time type of the pointer.
- **Virtual Function**: A member function in a base class declared with the `virtual` keyword, signaling that it can be overridden by derived classes.
- **Pure Virtual Function & Abstract Class**: A function declared with `= 0` (e.g., `virtual void draw() = 0;`). A class with at least one pure virtual function cannot be instantiated directly and serves as an **Abstract Base Class (Interface)**.

---

## 2. Why Does It Matter?
- **Extensibility (Open-Closed Principle)**: You can add new derived types (e.g., `NotificarePush`, `Triunghi`) without changing existing client loops or processing logic.
- **Heterogeneous Collections**: Enables storing diverse subclasses in a single container using base pointers (e.g., `std::vector<std::unique_ptr<Animal>>`).
- **Clean Architecture**: Separates high-level business policies from low-level implementation details.

---

## 3. How Does It Work? The Vtable and Vptr Mechanism
Under the hood, C++ implements dynamic dispatch using two structures:
1. **vtable (Virtual Method Table)**: A static table created per class by the compiler containing function pointers to each virtual function for that class.
2. **vptr (Virtual Table Pointer)**: An invisible pointer automatically injected into every instance of a class that has virtual functions. It points to the class's vtable.

```
OBJECT INSTANCES (Heap/Stack)            VTABLES (Static Memory)
+---------------------------------+     +------------------------------------+
| Caine instance:                 |     | Caine vtable:                      |
|   vptr ------------------------>|---->|   ~Animal()     -> ~Caine()        |
+---------------------------------+     |   scoateSunet() -> Caine::scoateSunet|
                                        +------------------------------------+

+---------------------------------+     +------------------------------------+
| Pisica instance:                |     | Pisica vtable:                     |
|   vptr ------------------------>|---->|   ~Animal()     -> ~Pisica()       |
+---------------------------------+     |   scoateSunet() -> Pisica::scoateSunet|
                                        +------------------------------------+
```
When `a->scoateSunet()` is called on an `Animal*`:
1. The CPU looks up the object's `vptr`.
2. Follows `vptr` to the object's actual class `vtable`.
3. Calls the function pointer stored at the `scoateSunet` offset.

---

## 4. The Critical Rule: Virtual Destructors
> [!IMPORTANT]
> If a class has ANY virtual function, its destructor MUST be declared `virtual`!

If a base class has a non-virtual destructor:
```cpp
Animal* ptr = new Caine();
delete ptr; // UNDEFINED BEHAVIOR! Only ~Animal() is called; ~Caine() is skipped!
```
With `virtual ~Animal() = default;`, deleting through `Animal*` guarantees that `~Caine()` runs first, correctly cleaning up derived resources.

---

## 5. Practical Examples from the Repository

### Example 1: Virtual Methods and Virtual Destructors
*(From: `saptamana_3_OOP/ziua_16_polimorfism_dinamic/animal.cpp`)*

```cpp
#include <iostream>
#include <memory>
#include <vector>

class Animal {
public:
    virtual ~Animal() {
        std::cout << "Animal destructor\n";
    }
    virtual void scoateSunet() const {
        std::cout << "Sunet generic animal\n";
    }
};

class Caine : public Animal {
public:
    void scoateSunet() const override {
        std::cout << "ham\n";
    }
};

class Pisica : public Animal {
public:
    void scoateSunet() const override {
        std::cout << "miau\n";
    }
};

int main() {
    // Heterogeneous collection using smart pointers
    std::vector<std::unique_ptr<Animal>> animale;
    animale.push_back(std::make_unique<Caine>());
    animale.push_back(std::make_unique<Pisica>());
    animale.push_back(std::make_unique<Animal>());

    // Polymorphic invocation: calls the right method for each object!
    for (const auto& a : animale) {
        a->scoateSunet();
    }
    return 0;
}
```

### Example 2: Polymorphic Notification System
*(From: `saptamana_3_OOP/ziua_16_polimorfism_dinamic/sistem_notificari.cpp`)*

```cpp
class Notificare {
protected:
    std::string mesaj;
public:
    Notificare(std::string msg) : mesaj(msg) {}
    virtual ~Notificare() = default; // Modern C++ virtual destructor default
    virtual void trimite() const {
        std::cout << "Notificare generica: " << mesaj << '\n';
    }
};

class NotificareSMS : public Notificare {
private:
    int nrtelefon;
public:
    NotificareSMS(std::string msg, int nr) : Notificare(msg), nrtelefon(nr) {}
    void trimite() const override {
        std::cout << "SMS catre " << nrtelefon << ": " << mesaj << '\n';
    }
};

class NotificareEmail : public Notificare {
private:
    std::string email;
public:
    NotificareEmail(std::string msg, std::string mail) : Notificare(msg), email(mail) {}
    void trimite() const override {
        std::cout << "Email catre " << email << ": " << mesaj << '\n';
    }
};
```

### Example 3: Pure Virtual Functions and Abstract Base Classes
*(From: `saptamana_3_OOP/ziua_17_abstractizarea/forma_geometrica.cpp`)*

```cpp
// Abstract Interface
class FormaGeometrica {
public:
    virtual ~FormaGeometrica() = default;
    
    // Pure virtual functions: MUST be implemented by concrete subclasses
    virtual double calculeazaAria() const = 0;
    virtual void afiseaza() const = 0;
};

class Patrat : public FormaGeometrica {
private:
    double latura;
public:
    Patrat(double l) : latura(l) {}
    double calculeazaAria() const override { return latura * latura; }
    void afiseaza() const override {
        std::cout << "Patrat | Latura: " << latura << " | Aria: " << calculeazaAria() << '\n';
    }
};

class Cerc : public FormaGeometrica {
private:
    double raza;
public:
    Cerc(double r) : raza(r) {}
    double calculeazaAria() const override { return 3.14159 * raza * raza; }
    void afiseaza() const override {
        std::cout << "Cerc | Raza: " << raza << " | Aria: " << calculeazaAria() << '\n';
    }
};
```

---

## 6. Common Mistakes and Pitfalls
1. **Forgetting `virtual` on Base Destructor**: Causes memory leaks and slicing during destruction of derived objects via base pointers.
2. **Missing `override` Specifier**: If you accidentally misspell the function name or change parameter types in a derived class, without `override` the compiler silently treats it as a brand-new function instead of an override!
3. **Attempting to Instantiate an Abstract Class**:
   `FormaGeometrica f; // COMPILE ERROR: cannot declare variable 'f' to be of abstract type`
4. **Object Slicing**:
   Assigning a derived object to a base object by value:
   `Animal a = Caine(); // SLICED! All Caine specific data and vptr are stripped away!`
   Always use pointers or references for polymorphism: `std::unique_ptr<Animal> a = std::make_unique<Caine>();`.

---

## 7. Quick Revision
- Dynamic polymorphism chooses method implementations at runtime using the `vtable` and `vptr`.
- Virtual functions are marked with `virtual` in base and `override` in derived classes.
- A virtual destructor is mandatory on any class intended for inheritance.
- Pure virtual functions (`= 0`) define interfaces; classes containing them are abstract and cannot be instantiated directly.
- Polymorphism requires pointers (`Base*`, `unique_ptr<Base>`) or references (`Base&`), never values.

---

## 8. Repository References
- **Dynamic Polymorphism with Animal**: [animal.cpp](../../saptamana_3_OOP/ziua_16_polimorfism_dinamic/animal.cpp)
- **Notification Subsystems**: [sistem_notificari.cpp](../../saptamana_3_OOP/ziua_16_polimorfism_dinamic/sistem_notificari.cpp)
- **Abstract Shapes**: [forma_geometrica.cpp](../../saptamana_3_OOP/ziua_17_abstractizarea/forma_geometrica.cpp)
