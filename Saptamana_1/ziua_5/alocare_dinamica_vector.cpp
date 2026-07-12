#include <iostream>
using namespace std;

int main(){
    int dimensiune;
    cout << "Ce dimensiune vrei sa aiba vectorul?" << '\n';
    cin >> dimensiune;
    int* vector_dinamic = new int[dimensiune];
    for(int i=0; i<dimensiune;i++){
        int numar_citit;
        cin >> numar_citit;
        vector_dinamic[i] = numar_citit;
        
    }
    for(int i=0;i<dimensiune;i++){
        cout << vector_dinamic[i];
    }

    delete[] vector_dinamic;

    vector_dinamic = nullptr;


    return 0;
}