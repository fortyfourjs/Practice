#include <iostream>
using namespace std;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
    cout << "a=" << *a << " " << "b=" << *b << "\n";
}

int main(){
    int a = 7;
    int b = 3;
    swap(&a, &b);
    return 0;
}