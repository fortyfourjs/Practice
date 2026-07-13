#include <iostream>
using namespace std;

int main(){
    int pas = 1;
    
    while(true){
        int* vector_dinamic = new int[10000000];
        vector_dinamic[0] = 7; 
        
        cout << "Pasul " << pas << ": Am alocat ~40 MB. Adresa: " << vector_dinamic << '\n';
        pas++;
    }

    return 0;
}