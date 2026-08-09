#include <iostream>
#include <memory>
using namespace std;

int main(){
    auto p1 = make_shared<int>(100);
    cout << "valoarea: " << *p1 << " nr:" << p1.use_count() << '\n';
    {
        auto p2 = p1;
        cout << "valoarea: " << *p1 << " nr:" << p1.use_count() << '\n';
    }
    cout << "valoarea: " << *p1 << " nr:" << p1.use_count() << '\n';
    return 0;
}