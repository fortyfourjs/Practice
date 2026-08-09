#include <iostream>
#include <memory>
using namespace std;

void preiaTablou(unique_ptr<int[]> ptr, int size){
    cout << "VALORI IN HEAP" << '\n';

    for(int i=0;i<size;i++){
        cin >> ptr[i];
        cout << "Valoarea " << ptr[i] << " la adresa " << &ptr[i] << '\n';
    }
}
int main(){
    cout << "marime: " << '\n';
    int size;
    cin >> size;
    auto array = make_unique<int[]>(size);
    preiaTablou(move(array), size);
    if(array == nullptr){
        cout << "memorie eliberata" << '\n';
    }else{
        cout << "memorie ocupata" << '\n';
    }
    return 0;
}