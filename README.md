# Modern C++ Knowledge Base & Learning Repository

Welcome to the structured C++ Knowledge Base and Revision Resource!

This repository documents an intensive, hands-on journey from fundamental C++ mechanics to modern object-oriented design, advanced Standard Template Library (STL) programming, memory management, and algorithmic problem-solving.

Originally developed chronologically over four weeks of daily exercises, this repository has been transformed into a **topic-based technical knowledge base**, optimized for rapid revision, conceptual clarity, and deep understanding.

---

## Quick Navigation

| Resource | Purpose | Target Audience |
| :--- | :--- | :--- |
| [**Learning & Revision Roadmap**](review/learning-roadmap.md) | Prerequisite dependency chart and suggested study path | New learners & systematic review |
| [**Quick Revision Guide**](review/quick-revision-guide.md) | High-yield summary cheat sheet across all topics | Exam prep & pre-interview refresher |
| [**Active Recall Flashcards**](review/flashcards.md) | Q&A cards testing deep conceptual mechanics | Fast self-quizzing |
| [**Self-Assessment Challenges**](review/self-assessment.md) | Tricky code-reading exercises & bug-spotting challenges | Advanced mastery verification |
| [**LeetCode Problem Collection**](docs/06-leetcode-patterns/README.md) | 13 LeetCode problems grouped by algorithmic pattern | Data structures & algorithm practice |

---

## Knowledge Base by Topic

### 1. C++ Fundamentals
- [Variables, Fundamental Types, and Memory Representation](docs/01-cpp-fundamentals/01-variables-types-memory.md)
- [Strings and Character Manipulation](docs/01-cpp-fundamentals/02-strings-and-char-manipulation.md)
- [References and Const Correctness](docs/01-cpp-fundamentals/03-references-and-const.md)

### 2. Memory Architecture & Safety (Special Focus)
- [Memory Architecture: Stack vs. Heap and Object Lifetimes](docs/02-memory-management/01-stack-vs-heap.md)
- [Pointers and Pointer Arithmetic](docs/02-memory-management/02-pointers-and-pointer-arithmetic.md)
- [Raw Dynamic Memory Allocation & Safety Hazards](docs/02-memory-management/03-dynamic-allocation-raw.md)
- [RAII and Modern Smart Pointers (unique_ptr, shared_ptr, weak_ptr)](docs/02-memory-management/04-raii-and-smart-pointers.md)
- [Deep Copy vs. Shallow Copy & The Rule of Three / Five](docs/02-memory-management/05-deep-vs-shallow-copy.md)

### 3. Object-Oriented Programming (OOP)
- [Classes and Encapsulation](docs/03-object-oriented-programming/01-classes-and-encapsulation.md)
- [Inheritance vs. Composition](docs/03-object-oriented-programming/02-inheritance-and-composition.md)
- [Dynamic Polymorphism, Virtual Functions, and Abstract Classes](docs/03-object-oriented-programming/03-polymorphism-and-virtual-functions.md)

### 4. Standard Template Library (STL)
- [Sequential Containers and Adaptors (vector, stack, queue)](docs/04-standard-template-library/01-sequential-containers.md)
- [Associative Containers: Hash Tables and Sets (unordered_map, unordered_set)](docs/04-standard-template-library/02-associative-containers.md)
- [Container Adaptors and Heaps (priority_queue)](docs/04-standard-template-library/03-container-adaptors-and-heaps.md)
- [Iterators and Standard Algorithms (sort, lower_bound, Erase-Remove)](docs/04-standard-template-library/04-iterators-and-algorithms.md)

### 5. Advanced & Modern C++
- [Templates and Generic Programming](docs/05-advanced-modern-cpp/01-templates-generic-programming.md)
- [Modern Lambdas and Functional Predicates](docs/05-advanced-modern-cpp/02-lambdas-and-functional.md)
- [Exception Handling and Robust Error Management](docs/05-advanced-modern-cpp/03-exception-handling.md)
- [File I/O and Stream Processing (fstream, sstream)](docs/05-advanced-modern-cpp/04-file-io-and-streams.md)
- [Capstone Project Architecture: Library Management System](docs/05-advanced-modern-cpp/05-capstone-library-management.md)

### 6. LeetCode Algorithmic Patterns
All 13 LeetCode problems solved across the repository, categorized by pattern:
- [Pattern 01: Arrays and Hashing](docs/06-leetcode-patterns/01-arrays-and-hashing.md) *(Two Sum, Contains Duplicate, Valid Anagram, Group Anagrams, Array Intersection)*
- [Pattern 02: Two Pointers](docs/06-leetcode-patterns/02-two-pointers.md) *(Reverse String, Valid Palindrome, Remove Duplicates, Merge Strings Alternately)*
- [Pattern 03: Stacks and Queues](docs/06-leetcode-patterns/03-stacks-and-queues.md) *(Valid Parentheses, Remove Adjacent Duplicates)*
- [Pattern 04: Heap / Priority Queue](docs/06-leetcode-patterns/04-heap-and-priority-queue.md) *(Kth Largest Element in an Array)*
- [Pattern 05: Binary Search and Boyer-Moore Voting](docs/06-leetcode-patterns/05-binary-search-and-voting.md) *(Majority Element, Lower Bound Search)*

---

## Original Chronological Learning History

All original exercises, notes, and experiments are preserved completely intact in their original folders:

- **[Week 1: Foundations, Vectors & Pointers](Saptamana_1/)**
  - [Day 1](Saptamana_1/ziua_1/): String manipulation, palindromes, character extraction.
  - [Day 2](Saptamana_1/ziua_2/): Dynamic vectors, capacity growth, vector as stack, LeetCode 217 & 344.
  - [Day 4](Saptamana_1/ziua_4/): In-place swaps, string sanitization, LeetCode 125.
  - [Day 5](Saptamana_1/ziua_5/): Raw pointers, dynamic allocation (`new[]`/`delete[]`), heap exhaustion, LeetCode 26.
  - [Day 6](Saptamana_1/ziua_6/): LeetCode 1 (Two Sum), LeetCode 1768, multi-step data cleaning pipeline.
- **[Week 2: Associative Containers, Heaps & Smart Pointers](Saptamana_2/)**
  - [Day 7](Saptamana_2/ziua_7/): `std::unordered_map` & `std::unordered_set`, anagrams, LeetCode 349.
  - [Day 9](Saptamana_2/ziua_9/): `std::stack`, `std::queue`, `std::priority_queue`, order queues, LeetCode 20, 1047 & 215.
  - [Day 10](Saptamana_2/ziua_10/): Binary search (`std::lower_bound`), Boyer-Moore Voting, LeetCode 169.
  - [Day 11](Saptamana_2/ziua_11/): Pointer arithmetic, heap cloning, two-pointer array reversal.
  - [Day 12](Saptamana_2/ziua_12/): Modern smart pointers (`std::unique_ptr`, `std::shared_ptr`, `std::move`).
- **[Week 3: Object-Oriented Programming (OOP)](saptamana_3_OOP/)**
  - [Day 13](saptamana_3_OOP/ziua_13_incapsulare/): Classes, private state, invariant validation (`BankAccount`).
  - [Day 14](saptamana_3_OOP/ziua_14_deepxshallow_copy/): Deep vs. shallow copy, Rule of Three (`customBuffer`).
  - [Day 15](saptamana_3_OOP/ziua_15_mostenire_compozitie/): Inheritance (`Employee`) vs. Composition (`Library`).
  - [Day 16](saptamana_3_OOP/ziua_16_polimorfism_dinamic/): Dynamic polymorphism, virtual destructors (`Animal`, `Notificare`).
  - [Day 17](saptamana_3_OOP/ziua_17_abstractizarea/): Pure virtual functions & abstract interfaces (`FormaGeometrica`).
- **[Week 4: Modern Paradigms & Capstone Architecture](saptamana_4/)**
  - [Day 19](saptamana_4/ziua_19/): Function & class templates, generic pair and box wrappers.
  - [Day 20](saptamana_4/ziua_20/): Explicit iterator traversal, Docker/Nginx web experiment.
  - [Day 21](saptamana_4/ziua_21/): Exception handling (`std::invalid_argument`, `std::runtime_error`).
  - [Day 22](saptamana_4/ziua_22/): Modern lambdas with state capture, `std::sort` & `std::count_if`.
  - [Day 23](saptamana_4/ziua_23/): Persistent append logging with `<fstream>`.
  - [Day 24 (Capstone Project)](saptamana_4/ziua_24/Library%20Management/): Complete Library Management System with multi-file architecture, `unique_ptr` ownership, CSV file database, and CLI interface.

---

## Compilation and Tooling

All code in this repository conforms to modern C++ standards (C++17 / C++20).

To compile any standalone file using `g++`:
```bash
g++ -std=c++17 -Wall -Wextra -O2 path/to/file.cpp -o program
./program
```

To build the multi-file **Library Management Capstone Project**:
```bash
cd "saptamana_4/ziua_24/Library Management"
g++ -std=c++17 -Wall -Wextra Book.cpp Library.cpp main.cpp -o LibraryApp
./LibraryApp
```
