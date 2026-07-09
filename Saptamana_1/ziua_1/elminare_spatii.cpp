#include <iostream>
#include <string>
using namespace std;

void eliminare_spatii(string& s){
    int i = 0;
    while(i<s.length()){
        if(s[i] != ' '){
            i++;
        }
        else{
            s.erase(i, 1);
        }
    }
}

int main(){
    string s;
    getline(cin >> ws, s);

    eliminare_spatii(s);
    cout << s << '\n';
    string c = s.substr(2, 3); //substring al s incepand de la poz 2(3 caractere)
    cout << c << '\n';

return 0;
}