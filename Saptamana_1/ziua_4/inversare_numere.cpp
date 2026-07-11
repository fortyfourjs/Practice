#include <iostream>
using namespace std;

void inverseaza(int& a, int& b){
    int temp;
    temp = a;
    a=b;
    b=temp;
}
int main(){
    int x = 5;
    int y = 3;
    cout << "inainte: x=" << x << " inainte: y=" << y << '\n';
    inverseaza(x,y);
    cout << "dupa: x=" << x << " inainte: y=" << y << '\n';
    return 0;
}