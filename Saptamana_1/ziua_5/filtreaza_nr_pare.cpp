#include <iostream>
using namespace std;

int* filtreaza_pare(int* arr, int dimensiune, int& dimensiune_noua){
    int count = 0;
    for(int i=0; i<dimensiune; i++){
        if(arr[i]%2 == 0){
            count++;  
        }
    }
    dimensiune_noua = count;
    int* rezultat = new int[dimensiune_noua];
    int index_nou = 0;
    for(int i=0; i<dimensiune; i++){
        if(arr[i]%2 == 0){
            rezultat[index_nou] = arr[i];
            index_nou++;
        }
    }
    return rezultat;

}
int main(){
    int arr[] = {1,2,3,4,5,6,7,8};
    int dimensiune_noua = 0;

    int* pare = filtreaza_pare(arr, 8, dimensiune_noua);
    for(int i=0; i<dimensiune_noua;i++){
        cout << pare[i] << " ";
    }
    cout << '\n';
    delete[] pare;
    pare = nullptr;

    return 0;

}