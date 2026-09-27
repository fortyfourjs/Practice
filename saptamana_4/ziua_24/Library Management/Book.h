#include <string>
#include <iostream>
class Book {
    private:
        std::string titlu;
        std::string autor;
        std::string isbn;
        bool disponibil;
    
    public:
        Book(std::string t, std::string a, std::string i, bool disp){
            titlu = t;
            autor = a;
            isbn = i;
            disponibil = disp;
        }
        std::string getTitlu() const{
            return titlu;
        }
        std::string getAutor() const{
            return autor;
        }
        std::string getISBN() const{
            return isbn;
        }
        bool isDisponibil(){
            return disponibil;
        }
        void setDisponibil(bool stare){
            disponibil = stare;
        }
};