#include <iostream>
#include <memory>
using namespace std;

void processArray(int size){
    auto array = make_unique<int[]>(size);
    cout << "VALORI IN HEAP" << '\n';
    for(int i=0;i<size;i++){
        cin >> array[i];
        cout << "valoarea " << array[i] << " la adresa: " << &array[i] << '\n';
    }
}
int main(){
    int n;
    cout << "introdu n: "<< '\n';
    cin >> n;

    cout << "INAINTE DE FUNCTIE" << '\n';
    processArray(n);
    cout << "DUPA FUNCTIE" << '\n';

return 0;
}
