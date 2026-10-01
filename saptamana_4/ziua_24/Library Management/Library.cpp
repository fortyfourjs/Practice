#include "Library.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>


void Library::adaugaCarte(const std::string& titlu, const std::string& autor, const std::string& isbn, bool stare){
    std::unique_ptr<Book> carte = std::make_unique<Book>(titlu, autor, isbn, stare);
    book_list.push_back(std::move(carte));
}

void Library::afiseazaCarti() const{
    if(book_list.empty()){
        throw std::invalid_argument("Biblioteca nu contine nicio carte.");
    }
    for(const auto& carte:book_list){
        std::cout << carte->getAutor() << "-" <<  carte->getTitlu() << " - " << carte->getISBN() << " " << carte->isDisponibil() << '\n';
    }
}

void Library::imprumutaCarte(const std::string& titlu){
    for(const auto& carte:book_list){
        if(titlu == carte->getTitlu() && carte->isDisponibil()==true){
            carte->setDisponibil(false);
            return;
        }
        if(titlu == carte->getTitlu() && carte->isDisponibil()==false){
            throw std::runtime_error("Cartea este deja imprumutata!");
        }
    }
    throw std::invalid_argument("Cartea nu exista.");
}
void Library::sorteazaCarti(){
    std::sort(book_list.begin(), book_list.end(), [](const std::unique_ptr<Book>& a, const std::unique_ptr<Book>& b){
        return a->getTitlu() < b->getTitlu();
    });
}

void Library::salveazaInFisier(const std::string& numeFisier){
    std::ofstream fisier(numeFisier);
    if(!fisier.is_open()){
        throw std::runtime_error("Fisierul nu e deschis!");
    }
    for(const auto& carte:book_list){
        fisier << carte->getTitlu() << "," << carte->getAutor() << "," << carte->getISBN() << "," << carte->isDisponibil() << '\n';
    }
    fisier.close();
}

void Library::incarcaDinFisier(const std::string& numeFisier){
    std::ifstream fisier(numeFisier);
    if(!fisier.is_open()){
        throw std::runtime_error("Fisierul nu e deschis");
    }
}