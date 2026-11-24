# Strings and Character Manipulation in C++

## 1. Definition
`std::string` is an STL class template specialization (`std::basic_string<char>`) providing dynamic, contiguous arrays of characters. Unlike C-style strings (`char[]` terminated by `'\0'`), `std::string` automatically manages its memory, provides bounds checking, supports intuitive operators (`+`, `==`, `<`), and exposes extensive utility methods.

---

## 2. Why Does It Matter?
Strings are the backbone of text processing, parsing, CLI user input, serialization, and competitive programming problems (such as palindromes, anagrams, and string tokenization).
- **Safety**: Eliminates buffer overflows common with raw C-strings (`strcpy`, `strcat`).
- **Memory Management**: Automatic heap allocation and resizing using the Small String Optimization (SSO).
- **Rich Interface**: Built-in methods for searching, sub-string extraction, in-place erasure, and character replacement.

---

## 3. How Does It Work?
Under the hood, a modern standard library `std::string` object typically occupies 24 or 32 bytes on the stack:
1. **Pointer to data**: Points to the dynamic character buffer.
2. **Size**: Number of characters currently stored.
3. **Capacity**: Size of allocated buffer before re-allocation is required.
4. **Small String Optimization (SSO)**: For short strings (usually $\le$ 15 characters), `std::string` uses internal stack space within the object itself, avoiding heap allocations entirely!

### Stream Extraction and Whitespace Handling
- `cin >> s;` reads whitespace-delimited tokens (stops at space, tab, or newline).
- `getline(cin >> ws, s);` discards leading whitespace and reads the entire line until a newline `'\n'`. This pattern is used across the repository (e.g., `elminare_spatii.cpp`, `main.cpp`).

---

## 4. Syntax & Core Methods
```cpp
#include <string>
#include <cctype>

std::string s = "Hello, World!";

// Size and capacity
size_t len = s.length(); // or s.size()
bool empty = s.empty();

// Element access
char c1 = s[0];          // Fast unchecked access
char c2 = s.at(1);       // Bounds-checked access (throws std::out_of_range)

// Substrings and Modifiers
std::string sub = s.substr(startIndex, length); // Substring from index
s.erase(index, count);                          // Erase 'count' chars from 'index'
s.push_back('!');                               // Append single char
s += " Welcome";                                // Concatenate string

// Character Classification & Conversion (<cctype>)
std::isalnum('a');  // true if letter or digit
std::isdigit('5');  // true if digit
std::tolower('A');  // returns 'a'
int digitVal = '7' - '0'; // Converts char '7' to integer 7
```

---

## 5. Practical Examples from the Repository

### Example 1: In-Place Whitespace Erasure
*(From: `Saptamana_1/ziua_1/elminare_spatii.cpp`)*

```cpp
#include <iostream>
#include <string>

void eliminare_spatii(std::string& s) {
    int i = 0;
    while (i < s.length()) {
        if (s[i] != ' ') {
            i++;
        } else {
            s.erase(i, 1); // Erase 1 character at index i; subsequent characters shift left
        }
    }
}
```
> [!NOTE]
> `s.erase(i, 1)` shifts all elements after `i` by one position to the left ($O(N)$ per erase, making the whole loop $O(N^2)$ in the worst case). For $O(N)$ linear erasure, modern C++ uses the **Erase-Remove Idiom**:
> `s.erase(std::remove(s.begin(), s.end(), ' '), s.end());`

### Example 2: String Sanitization (Lowercasing and Filtering)
*(From: `Saptamana_1/ziua_4/palindrom.cpp` and `125.leetcode_validpalindrome.cpp`)*

```cpp
std::string curata_string(const std::string& s) {
    std::string rezultat = "";
    for (char c : s) {
        if (std::isalnum(c)) {
            rezultat.push_back(std::tolower(c));
        }
    }
    return rezultat;
}
```

### Example 3: Extracting Numeric Digits from Formatted Text
*(From: `Saptamana_1/ziua_6/final_program.cpp`)*

```cpp
std::vector<int> curata_string(const std::string& s) {
    std::vector<int> cifre;
    for (char c : s) {
        if (std::isdigit(c)) {
            cifre.push_back(c - '0'); // ASCII arithmetic: '0' -> 48, '1' -> 49 ...
        }
    }
    return cifre;
}
```

---

## 6. Common Mistakes and Pitfalls
1. **Loop Index Bug after `erase()`**:
   If you increment `i++` unconditionally after `s.erase(i, 1)`, you skip the character that immediately shifted into position `i`! Notice how the author correctly structured the `if-else` in `elminare_spatii.cpp`.
2. **Missing `std::ws` Before `getline()`**:
   Mixing `cin >> num;` with `getline(cin, str);` leaves the trailing `\n` in the buffer, causing `getline` to read an empty line immediately. Always use `getline(cin >> ws, str);`.
3. **Passing Strings by Value**:
   Passing `std::string` by value creates an unnecessary heap copy. Always pass by `const std::string&` when reading, or `std::string&` when modifying in-place.

---

## 7. Quick Revision
- `std::string` manages its own dynamic buffer and null-terminator automatically.
- Small String Optimization (SSO) keeps small strings on the stack for high speed.
- `substr(pos, count)` extracts a slice; `erase(pos, count)` cuts characters in-place.
- Use `getline(cin >> ws, str)` to reliably capture strings with spaces.
- Character conversion from char to int is achieved with `c - '0'`.

---

## 8. Repository References
- **Whitespace Erasure & Substring**: [elminare_spatii.cpp](../../Saptamana_1/ziua_1/elminare_spatii.cpp)
- **String Inversion**: [inversare_sir.cpp](../../Saptamana_1/ziua_1/inversare_sir.cpp)
- **Vowel Counting**: [numar_vocale.cpp](../../Saptamana_1/ziua_1/numar_vocale.cpp)
- **Palindrome Check**: [palindrom.cpp](../../Saptamana_1/ziua_1/palindrom.cpp)
- **String Sanitization**: [palindrom.cpp (Day 4)](../../Saptamana_1/ziua_4/palindrom.cpp)
- **Digit Extraction & Parsing**: [final_program.cpp](../../Saptamana_1/ziua_6/final_program.cpp)
