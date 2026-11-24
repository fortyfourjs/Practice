# Classes and Encapsulation

## 1. Definition
**Encapsulation** is an Object-Oriented Programming (OOP) principle that bundles internal state (member variables) and behavior (member functions) together within a single unit called a `class`, while restricting direct external access to internal data representations using access specifiers (`private`, `protected`, `public`).

---

## 2. Why Does It Matter?
- **Class Invariant Protection**: By keeping state private and exposing controlled methods (`deposit`, `withdraw`), a class guarantees that its data remains valid at all times (e.g., balance cannot become arbitrarily corrupted or negative).
- **Reduced Coupling**: External client code interacts only with the public interface, allowing the internal implementation to change without breaking dependent code.
- **Maintainability & Debugging**: Logic modifying an object is localized to member functions, making bug tracking straightforward.

---

## 3. How Does It Work?

### Access Specifiers
- `private`: Accessible only by member functions of the class (and `friend`s). Default access level for `class`.
- `public`: Accessible from anywhere in the program.
- `protected`: Accessible by member functions of the class and derived classes. Default access level for `struct` is `public`.

### Member Initializer Lists
Constructors should initialize members before the constructor body executes using the **member initializer list**:
```cpp
BankAccount(std::string acc, double initBal) 
    : accountNumber(std::move(acc)), balance(initBal >= 0 ? initBal : 0.0) {}
```
Direct initialization in the initializer list avoids default-constructing the member and then overwriting it in the body.

### Const Correctness in Classes
Member functions that only read data should be declared `const`:
```cpp
double getBalance() const; // Cannot modify any member variable
```

---

## 4. Practical Example from the Repository: `bankaccount.cpp`
*(From: `saptamana_3_OOP/ziua_13_incapsulare/bankaccount.cpp`)*

```cpp
#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    double balance;

public:
    // Constructor with invariant validation
    BankAccount(std::string accNum, double initialBalance) {
        accountNumber = accNum;
        if (initialBalance >= 0) {
            balance = initialBalance;
            std::cout << "Soldul curent: " << balance << " RON\n";
        } else {
            balance = 0.0;
        } 
    }

    // Mutator with business validation
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Soldul curent: " << balance << " RON\n";
        } else {
            std::cout << "Suma trebuie sa fie pozitiva!\n";
        }
    }

    // Mutator preventing overdraft
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Soldul curent: " << balance << " RON\n";
        } else {
            std::cout << "Fonduri insuficiente\n";
            std::cout << "Soldul curent: " << balance << " RON\n";
        }
    }

    // Inspector (Read-only access)
    double getBalance() const {
        return balance;
    }
};

int main() {
    BankAccount cont("RON4341RO", 3000);
    cont.deposit(300);
    cont.withdraw(3400); // Exceeds balance -> rejected safely
    std::cout << "Sold: " << cont.getBalance() << '\n';
    cont.deposit(-4050); // Negative deposit -> rejected safely
    return 0;
}
```

---

## 5. Common Mistakes and Pitfalls
1. **Public Member Variables**:
   Making data fields `public` destroys encapsulation; external code can assign invalid states (e.g., `cont.balance = -999999;`).
2. **Missing `const` on Getters**:
   If `getBalance()` is not marked `const`, calling it on a `const BankAccount&` object fails to compile!
3. **Prefer Member Initializer Lists**:
   Assigning fields inside `{ body }` can lead to redundant work for complex types.

---

## 6. Quick Revision
- Encapsulation hides private internal state behind a validated public interface.
- Constructors ensure objects are initialized into a valid state.
- Always use member initializer lists for cleaner, faster construction.
- Mark all read-only getters as `const`.

---

## 7. Repository References
- **Bank Account Class**: [bankaccount.cpp](../../saptamana_3_OOP/ziua_13_incapsulare/bankaccount.cpp)
- **Book Class Encapsulation**: [Book.h](../../saptamana_4/ziua_24/Library%20Management/Book.h) and [Book.cpp](../../saptamana_4/ziua_24/Library%20Management/Book.cpp)
