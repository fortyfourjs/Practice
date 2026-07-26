#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;


int main(){
    queue<pair<int, string>> clienti;
    clienti.push({1, "Alex"});
    clienti.push({2, "Ion"});
    clienti.push({3, "Vali"});

    while(!clienti.empty()){
        cout << "A fost servit clientul NR:" << clienti.front().first << " " << clienti.front().second << '\n';
        clienti.pop();
    }

    return 0;

}