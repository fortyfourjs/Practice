#include <iostream>
using namespace std;


void swap_ref(int& a, int& b){
    int temp;
    temp = a;
    a = b;
    b = temp;
    cout << "a=" << a << " " << "b=" << b << '\n';
}

void swap_ptr(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;

    cout << "a=" << *a << " " << "b=" << *b << '\n';
}

int main(){
    int a = 6;
    int b = 8;
    swap_ref(a, b);
    a=6;
    b=8;
    
    swap_ptr(&a, &b);
}