#include "Book.h"
#include <iostream>
#include <string>
Book::Book(std::string t, std::string a, std::string i, bool disp){
    titlu = t;
    autor = a;
    isbn = i;
    disponibil = disp;
}

std::string Book::getTitlu() const{
    return titlu;
}
std::string Book::getAutor() const{
    return autor;
}
std::string Book::getISBN() const{
    return isbn;
}
bool Book::isDisponibil() const{
    return disponibil;
}
void Book::setDisponibil(bool stare){
    disponibil = stare;
}