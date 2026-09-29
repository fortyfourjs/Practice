#pragma once
#include <string>

class Book {
    private:
        std::string titlu;
        std::string autor;
        std::string isbn;
        bool disponibil;
    
    public:
        Book(std::string t, std::string a, std::string i, bool disp);
        std::string getTitlu() const;
        std::string getAutor() const;
        std::string getISBN() const;
        bool isDisponibil() const;
        void setDisponibil(bool stare);
};