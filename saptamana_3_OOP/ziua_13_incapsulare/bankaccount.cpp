#include <iostream>
#include <string>
using namespace std;

class BankAccount{
    private:
        string accountNumber;
        double balance;
    public:
        BankAccount(string accNum, double initialBalance){
            accountNumber = accNum;
            if(initialBalance >= 0){
                balance = initialBalance;
                cout << "Soldul curent:" << balance << " RON" << '\n';
            }else{
                balance = 0.0;
            } 
        }
        void deposit(double amount){
            if(amount > 0){
                balance += amount;
                cout << "Soldul curent:" << balance << " RON" << '\n';
            }else{
                cout << "Suma trebuie sa fie pozitiva!" << '\n';
            }
            
        }
        void withdraw(double amount){
            if(amount > 0 && amount <= balance){
                balance -= amount;
                cout << "Soldul curent:" << balance << " RON" << '\n';
            }else{
                cout << "Fonduri insuficiente" << '\n';
                cout << "Soldul curent:" << balance << " RON" << '\n';
            }
        }
        double getBalance() const{
            return balance;
        }
};
int main(){
    BankAccount cont("RON4341RO", 3000);
    cont.deposit(300);
    cont.withdraw(3400);
    cout << cont.getBalance();
    cont.deposit(-4050);
    return 0;
}