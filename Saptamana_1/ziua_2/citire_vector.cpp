#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector vocale {"a", "e", "i", "o", "u"};
    cout << vocale[1];
    cout << sizeof(char) << "bytes\n";
    cout << &vocale[0] << "\n";
    cout << &vocale[1] << "\n";
    cout << &vocale[2] << "\n";

    vector nr {1, 4, 9, 16, 25};

    cout << nr[3] << '\n';

    vector<int> numere(3);
    cin >> numere[0] >> numere[1] >> numere[2];
    cout << numere[0] + numere[1] + numere[2] << '\n';

    cout << vocale.size() << '\n';
   
    vector<char> test{'h', 'e', 'l', 'l', 'o'};
    cout << test.size() << '\n';
    cout << test[1];
    cout << test.at(1);
    return 0;
}