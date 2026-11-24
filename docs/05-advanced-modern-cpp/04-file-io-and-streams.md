# File I/O and Stream Processing (fstream, sstream, CSV Parsing)

## 1. Definition
**File I/O Streams** (`<fstream>`) are standard library classes that provide an abstraction for reading and writing data to files on disk using C++ stream operators (`<<`, `>>`) and stream functions (`std::getline`).
- `std::ifstream`: Input file stream (reading).
- `std::ofstream`: Output file stream (writing / creating).
- `std::stringstream` (`<sstream>`): In-memory stream used for string parsing, formatting, and delimiter tokenization.

---

## 2. Why Does It Matter?
- **Data Persistence**: Preserves program state, settings, database records, and logs across application restarts.
- **RAII File Management**: Stream objects automatically close their underlying OS file handles when their destructors execute at scope exit.
- **Format Flexibility**: Stream manipulators and delimiter-based `getline` make parsing structured formats (like CSV, TSV, or key-value configs) straightforward.

---

## 3. How Does It Work?

### File Modes
When opening a stream with `std::ofstream file("log.txt", mode)`:
- `std::ios::out`: Default for `ofstream`; truncates file if it exists.
- `std::ios::app`: Append mode; writes to the end of the file without deleting existing content.
- `std::ios::in`: Default for `ifstream`; opens for reading.
- `std::ios::binary`: Disables text translation (e.g., `\r\n` $\leftrightarrow$ `\n`).

### Delimited Parsing with `std::stringstream`
`std::getline(stream, outputString, delimiter)` extracts characters until the specified delimiter (e.g., `','`) is encountered:
```cpp
std::string line = "The Hobbit,J.R.R. Tolkien,9780547928227,1";
std::stringstream ss(line);
std::string title, author, isbn, available;

std::getline(ss, title, ',');
std::getline(ss, author, ',');
std::getline(ss, isbn, ',');
std::getline(ss, available, ',');
```

---

## 4. Practical Examples from the Repository

### Example 1: Persistent Append Logger
*(From: `saptamana_4/ziua_23/logger.cpp`)*

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Appending text to log file
void scrieLog(const std::string& text) {
    // std::ios::app preserves prior lines and writes at the end:
    std::ofstream scrieFisier("log.txt", std::ios::app);
    if (scrieFisier.is_open()) {
        scrieFisier << text << '\n';
    }
    // scrieFisier automatically closes when leaving scope (RAII)
}

// Reading lines back from disk
void citesteLog() {
    std::ifstream citesteFisier("log.txt");
    if (!citesteFisier.is_open()) {
        throw std::invalid_argument("Fisierul nu e deschis.");
    }
    std::string linie;
    while (std::getline(citesteFisier, linie)) {
        std::cout << linie << '\n';
    }
}

int main() {
    scrieLog("Text1");
    scrieLog("Text2");
    scrieLog("Text3");
    citesteLog();
    return 0;
}
```

### Example 2: CSV Database Serialization and Deserialization
*(From Capstone: `saptamana_4/ziua_24/Library Management/Library.cpp`)*

```cpp
// 1. Serialization (Writing to CSV)
void Library::salveazaInFisier(const std::string& numeFisier) {
    std::ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        throw std::runtime_error("Fisierul nu e deschis!");
    }
    for (const auto& carte : book_list) {
        fisier << carte->getTitlu() << "," 
               << carte->getAutor() << "," 
               << carte->getISBN() << "," 
               << carte->isDisponibil() << '\n';
    }
}

// 2. Deserialization (Reading from CSV)
void Library::incarcaDinFisier(const std::string& numeFisier) {
    std::ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        throw std::runtime_error("Fisierul nu e deschis");
    }
    std::string linie;
    while (std::getline(fisier, linie)) {
        if (linie.empty()) continue; // Skip blank lines
        
        std::stringstream ss(linie);
        std::string titlu, autor, isbn, stareStr;
        std::getline(ss, titlu, ',');
        std::getline(ss, autor, ',');
        std::getline(ss, isbn, ',');
        std::getline(ss, stareStr, ',');
        bool stare = (stareStr == "1");

        if (!titlu.empty()) {
            adaugaCarte(titlu, autor, isbn, stare);
        }
    }
}
```

---

## 5. Common Mistakes and Pitfalls
1. **Failing to Verify `file.is_open()`**:
   If a file path does not exist or permissions are denied, attempting to write fails silently, and reading immediately returns EOF. Always check `.is_open()`.
2. **Forgetting to Flush or Relying on Explicit `close()`**:
   Streams flush and close automatically upon destruction. However, if you need data immediately flushed to disk before a long computation, invoke `file.flush()` or pass `std::flush`.
3. **Trailing Empty Lines in CSV Files**:
   In `carti.txt`, empty lines or leading commas produce records with empty titles. Always validate tokens before inserting into data structures.

---

## 6. Quick Revision
- `std::ifstream` reads; `std::ofstream` writes.
- Destructors close file streams automatically (RAII).
- Use `std::ios::app` to append without overwriting existing file content.
- Use `std::getline(file, line)` for full-line reading.
- Use `std::stringstream` with a delimiter to parse CSV and formatted strings.

---

## 7. Repository References
- **Append Logging System**: [logger.cpp](../../saptamana_4/ziua_23/logger.cpp)
- **Log Text Output**: [log.txt](../../saptamana_4/ziua_23/log.txt)
- **CSV Database Processing**: [Library.cpp](../../saptamana_4/ziua_24/Library%20Management/Library.cpp)
- **CSV Data File**: [carti.txt](../../saptamana_4/ziua_24/Library%20Management/carti.txt)
