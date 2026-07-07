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

return 0;
}