#include "Library.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>


void Library::adaugaCarte(const std::string& titlu, const std::string& autor, const std::string& isbn, bool stare){
    std::unique_ptr<Book> carte = std::make_unique<Book>(titlu, autor, isbn, stare);
    book_list.push_back(std::move(carte));
}