#pragma once
#include "Book.h"
#include <string>
#include <vector>
#include <memory>

class Library{
    private:
        std::vector<std::unique_ptr<Book>> book_list = {};
    public:
        void adaugaCarte(const std::string& titlu, const std::string& autor, const std::string& isbn, bool stare);
        void afiseazaCarti() const; 
        void imprumutaCarte(const std::string& titlu);
        void sorteazaCarti();
        void salveazaInFisier(const std::string& numeFisier);
        void incarcaDinFisier(const std::string& numeFisier);
        

};