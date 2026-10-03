#include <iostream>
#include <string>
#include "Book.h"
#include "Library.h"


int main(){
    Library biblioteca;
    try{
        biblioteca.incarcaDinFisier("carti.txt");
    }
    catch(const std::exception& e){
        std::cout << e.what() << '\n';
    }
        while(true){
            std::cout << "Alege operatiunea:\n 1.Adauga Carte\n 2.Afiseaza toate cartile\n 3.Imprumuta o carte\n 4.Sorteaza Cartile\n 5.Salveaza si iesi\n";
            int numar_operatie;
            if(!(std::cin >> numar_operatie)){
                break;
            }
        try{
            switch(numar_operatie){
                case 1:{
                std::string titlu, autor, isbn;
                std::cout << "Titlu: " << '\n';
                std::getline(std::cin >> std::ws, titlu);
                std::cout << "Autor: " << '\n';
                std::getline(std::cin >> std::ws, autor);
                std::cout << "ISBN: " << '\n';
                std::getline(std::cin >> std::ws, isbn);

                biblioteca.adaugaCarte(titlu, autor, isbn, true);
                std::cout << "Carte adaugata." << '\n';
                break;
                }

                case 2:
                biblioteca.afiseazaCarti();
                break;

                case 3:{
                std::string titlu;
                std::cout << "Titlul cartii pe care doresti s-o imprumuti: " << '\n';
                std::getline(std::cin >> std::ws, titlu);
                biblioteca.imprumutaCarte(titlu);
                std::cout << "Carte imprumutata." << '\n';
                break;
                }

                case 4:
                biblioteca.sorteazaCarti();
                break;

                case 5:
                biblioteca.salveazaInFisier("carti.txt");
                return 0;
                break;
                
                default:
                    std::cout << "optiune invalida: alege de la 1 la 5" << '\n';
                    break;
            }
        } catch(const std::exception& e){
            std::cout << e.what() << '\n';
        }
    }
    return 0;
}