#include <iostream>
using namespace std;

int main(){
    int x = 10;
    int y = 50;
    int *p = &x;
    cout << x << '\n';
    *p = 20;
    cout << x << '\n';
    p = &y;
    *p = 100;
    cout << "x=" << x << " " << "y=" << y << '\n';
    return 0;
}