#include <iostream>
using namespace std;

int* duplicateArray(const int* original, int size){
    int* newArr = new int[size];
    for(int i=0;i<size;i++){
        newArr[i] = original[i];
        cout << "valoarea " << newArr[i] << " la adresa: " << &newArr[i] << '\n';
    }
return newArr;
}

void reverseArray(int* arr, int size){
    int* left = arr;
    int* right = arr + size - 1;
    for(int i=0;i<size/2;i++){
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }

}
int main(){
    int n;
    cout << "introdu n=" << '\n';
    cin >> n;
    int* arr = new int[n];
    for(int i=0;i<n;i++){
        cin >> arr[i];
        cout << "valoarea " << arr[i] << " la adresa: " << &arr[i] << '\n';
    }
    int* copie = duplicateArray(arr, n);
    cout << "ELEMENTELE COPIE PE HEAP " << '\n';
    for(int i=0;i<n;i++){
        cout << "valoarea " << copie[i] << " la adresa: " << &copie[i] << '\n';
    }
    reverseArray(copie, n);
    cout << "REVERSE COPIE " << '\n';
    for(int i=0;i<n;i++){
        cout << *(copie + i);
    }
    delete[] arr;
    arr = nullptr;
    delete[] copie;
    copie = nullptr;
    return 0;
    }
