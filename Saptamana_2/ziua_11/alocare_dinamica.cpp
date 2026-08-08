#include <iostream>
using namespace std;

int main(){
    int n;
    cout << "introdu n=" << '\n';
    cin >> n;
    int* arr = new int[n];
    for(int i=0;i<n;i++){
        cin >> arr[i];
        cout << "valoarea " << arr[i] << " la adresa: " << &arr[i] << '\n';
    }
    delete[]arr;
    arr = nullptr;
  
    return 0;
}