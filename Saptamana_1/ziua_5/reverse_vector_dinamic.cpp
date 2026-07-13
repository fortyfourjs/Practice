#include <iostream>
#include <vector>
using namespace std;


void inverseaza(int* arr, int dimensiune){

    for(int i=0; i<dimensiune/2; i++){
        int temp = arr[i];
        arr[i] = arr[dimensiune-i-1];
        arr[dimensiune-i-1] = temp;    
    }
}

int main(){
    int arr[] = {50, 40, 30, 20, 10};
    for(int i=0;i<5;i++){
        cout << arr[i] << " ";
    }
    cout << '\n';
    inverseaza(arr, 5);
    for(int i=0;i<5;i++){
        cout << arr[i] << " ";
    }

    return 0;
}