#include <iostream>
#include <queue>
using namespace std;

int main(){
    priority_queue<int> scoruri;
    scoruri.push(300);
    scoruri.push(10);
    scoruri.push(456);
    scoruri.push(120);
    scoruri.push(653);
    scoruri.push(101);

    for(int i=0;i<3 && !scoruri.empty();i++){
        cout << scoruri.top() << "\n";
        scoruri.pop();
    }

    return 0;
}