#include <iostream>
#include <vector>
using namespace std;


class Book{
    private:
        string title;
        string author;
    public:
        Book(string t, string a){
            title = t;
            author = a;
        }
        string getTitle() const{
            return title;
        }
        string getAuthor() const{
            return author;
        }
};
class Library{
    private:
        vector<Book> books;
    public:
        void addBook(const Book& book){
            books.push_back(book);
        }
        void showBooks() const{
            for(const auto& i : books){
                cout << "titlu: " << i.getTitle() << " autor: " << i.getAuthor() << '\n';
            }
            
        }
};
int main(){
    Library b;
    Book cartea1("titlu1", "autor1");
    Book cartea2("titlu2", "autor2");
    b.addBook(cartea1);
    b.addBook(cartea2);
    b.showBooks();

    return 0;
}