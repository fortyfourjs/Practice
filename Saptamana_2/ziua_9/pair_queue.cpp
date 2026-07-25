#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main(){
    queue<pair<string,int>> comenzi;
    comenzi.push({"laptop", 3000});   
    comenzi.push({"mouse", 150});
    comenzi.push({"tastatura", 250});

    while(!comenzi.empty()){
        cout << "Se proceseaza " << comenzi.front().first << " in valoare de " << comenzi.front().second << " RON" << '\n';
        comenzi.pop();
    }
return 0;
}