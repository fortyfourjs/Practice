# C++ Conceptual Self-Assessment & Code-Reading Challenges

Test your understanding of C++ memory mechanics, OOP patterns, and common pitfalls. Work through each challenge before revealing the detailed explanations.

---

## Part 1: Spot the Bug & Code Reading Challenges

### Challenge 1: The Loop Return Trap
Look closely at this function adapted from early vector exercises:
```cpp
bool hasDuplicate(std::vector<int>& v) {
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i] == v[i + 1]) {
            return true;
        }
        return false;
    }
    return false;
}
```
**Question**: What is the subtle bug here, and what will `hasDuplicate({1, 5, 5, 9})` return?

<details>
<summary><b>View Explanation & Solution</b></summary>

**Bug**: `return false;` is placed **inside** the body of the `for` loop!
In `{1, 5, 5, 9}`, on iteration `i = 0`, `v[0] == 1` and `v[1] == 5`. Because they are not equal, execution immediately hits `return false;` and terminates the entire function!
**Result**: Returns `false` even though the vector contains duplicate `5`s.
**Fix**: Remove the internal `return false;` so the loop continues checking all adjacent pairs.
</details>

---

### Challenge 2: The Self-Destruction in `operator=`
Examine this copy assignment operator:
```cpp
class Buffer {
    int* data;
    int size;
public:
    Buffer& operator=(const Buffer& other) {
        delete[] data;
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
        return *this;
    }
};
```
**Question**: What happens if a client executes `b = b;` (self-assignment)?

<details>
<summary><b>View Explanation & Solution</b></summary>

**Bug**: Missing **Self-Assignment Guard** (`if (this == &other) return *this;`).
When `b = b;` executes:
1. `delete[] data;` deletes `b`'s own heap data.
2. `new int[size]` allocates a new block.
3. `other.data[i]` attempts to read from `b`'s old memory block that was just deleted in step 1!
**Result**: Reading dangling/freed memory (**Undefined Behavior**).
</details>

---

### Challenge 3: The Sliced Notification
Consider this snippet:
```cpp
class Notificare {
public:
    virtual void trimite() const { std::cout << "Generica\n"; }
};

class NotificareSMS : public Notificare {
public:
    void trimite() const override { std::cout << "SMS\n"; }
};

void proceseaza(Notificare n) {
    n.trimite();
}

int main() {
    NotificareSMS sms;
    proceseaza(sms);
    return 0;
}
```
**Question**: What does this program print, and why?

<details>
<summary><b>View Explanation & Solution</b></summary>

**Output**: `Generica`
**Explanation**: `proceseaza` accepts parameter `Notificare n` **by value**. Passing `sms` into `proceseaza` triggers **Object Slicing**: only the base `Notificare` portion is copied; the derived `NotificareSMS` data and vtable pointer are stripped off.
**Fix**: Pass by reference to enable dynamic polymorphism:
`void proceseaza(const Notificare& n)` prints `SMS`.
</details>

---

### Challenge 4: The Hidden Memory Leak in Inheritance
```cpp
class Base {
public:
    ~Base() { std::cout << "~Base\n"; } // Notice: NOT virtual!
};

class Derived : public Base {
    int* buffer;
public:
    Derived() : buffer(new int[1000]) {}
    ~Derived() {
        std::cout << "~Derived\n";
        delete[] buffer;
    }
};

int main() {
    Base* p = new Derived();
    delete p;
    return 0;
}
```
**Question**: What is printed, and is there a memory leak?

<details>
<summary><b>View Explanation & Solution</b></summary>

**Output**:
```
~Base
```
**Explanation**: Because `Base`'s destructor is not declared `virtual`, deleting through `Base*` does not use dynamic dispatch. The runtime only executes `~Base()`.
`~Derived()` is **never called**!
**Result**: The 4000 bytes allocated by `new int[1000]` are leaked, and the deletion triggers **Undefined Behavior** according to the C++ standard.
**Fix**: Declare `virtual ~Base() = default;`.
</details>

---

### Challenge 5: Pass-by-Value Map Performance Killer
Consider this function signature:
```cpp
bool verifica_anagram(std::string& s1, std::string& s2, std::unordered_map<char, int> hashmap);
```
**Question**: What critical performance flaw exists in this signature?

<details>
<summary><b>View Explanation & Solution</b></summary>

**Flaw**: `std::unordered_map<char, int> hashmap` is passed **by value**.
Every single call to `verifica_anagram` allocates a new heap bucket array and copies all key-value entries from the caller's hash table.
**Fix**: If `hashmap` is only used internally, declare it inside the function body. If passed from caller, pass by reference: `std::unordered_map<char, int>&`.
</details>

---

### Challenge 6: The Iteration Syntax Mistake
Examine this iterator loop:
```cpp
std::map<std::string, int> catalog = {{"C++", 100}, {"Rust", 90}};
for (auto it = catalog.begin(); it != catalog.end(); ++it) {
    std::cout << it.first << ": " << it.second << '\n';
}
```
**Question**: Will this compile? If not, what is the exact error and fix?

<details>
<summary><b>View Explanation & Solution</b></summary>

**Compile Error**: `error: request for member 'first' in 'it', which is of non-class type / iterator type`
**Explanation**: `it` is an iterator (acting like a pointer), NOT the `std::pair` object itself.
**Fix**: Use pointer dereference syntax:
`std::cout << it->first << ": " << it->second << '\n';`
or structured binding with range-for:
`for (const auto& [nume, scor] : catalog)`.
</details>

---

## Part 2: Conceptual Mastery Questions

### Question 1: Ownership Dynamics with `unique_ptr`
If function `void takeOwnership(std::unique_ptr<int[]> p)` is called from `main()` using `takeOwnership(std::move(myPtr))`:
1. What does `myPtr` contain after the call?
2. When is the underlying array deleted?

<details>
<summary><b>View Answer</b></summary>

1. `myPtr` contains `nullptr` because ownership was moved out.
2. The heap array is deleted when `takeOwnership` finishes execution and parameter `p`'s destructor runs at the function's closing brace `}`.
</details>

---

### Question 2: Why not use raw arrays in Modern C++?
Why does modern C++ prefer `std::vector<int>` or `std::array<int, N>` over `int* arr = new int[N]`?

<details>
<summary><b>View Answer</b></summary>

1. **RAII**: Vectors automatically free memory on destruction or exceptions. Raw arrays leak if exceptions occur or if `delete[]` is forgotten.
2. **Bounds Checking**: Vectors provide `.at()` with bounds checking.
3. **Copy/Move Semantics**: Vectors support proper deep copying and constant-time moves (`std::move`). Raw arrays decay to pointers, losing size information and requiring manual deep-copy loops.
4. **Rich STL API**: Ready-to-use `.size()`, `.capacity()`, iterators, and compatibility with `<algorithm>`.
</details>

---

### Question 3: Stack Unwinding in Action
If a function allocates an object on the stack and an object with `std::make_unique` on the heap, and then throws an exception, what happens to both objects?

<details>
<summary><b>View Answer</b></summary>

**Both are cleanly destroyed without leaks!**
During **Stack Unwinding**, the C++ runtime walks back up the call stack to find a matching `catch` block. As each stack frame is destroyed:
1. The stack variable's destructor is executed.
2. The `std::unique_ptr`'s destructor is executed, which calls `delete` on the heap allocation.
</details>
