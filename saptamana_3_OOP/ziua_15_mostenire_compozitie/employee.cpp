#include <iostream>
using namespace std;

class Employee{
    protected:
        string name;
        int id;
        double salary;
    public:
        Employee(string n, int i, double s){
            name = n;
            id = i;
            salary = s;
        }
    void printInfo() const{
        cout << "Nume: " << name << " ID: " << id << " Salariu: " << salary << '\n';
    }
};

class Developer : public Employee{
    private:
        string programmingLanguage;
    public:
        Developer(string n, int i, double s, string lang) : Employee(n, i, s), programmingLanguage(lang){}
    void printDevInfo() const{
        printInfo();
        cout << "Limbaj: " << programmingLanguage << '\n';
    } 
};
int main(){
    Developer angajat1("ion",13,1340.3, "C++");
    angajat1.printDevInfo();
    return 0;
}