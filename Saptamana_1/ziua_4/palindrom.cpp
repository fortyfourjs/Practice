#include <iostream>
#include <string>
using namespace std;

bool verifica_palindrom(string& s){
    int n = s.size();
    for(int i=0; i<n/2; i++){
        if(s[i] != s[n-i-1]){
            return false;
        }
    }
return true;
}

string curata_string(const string& s){
    int n = s.size();
    string rezultat = "";
    for(int i=0; i<n; i++){
        if(isalnum(s[i])){
            char litera_mica=tolower(s[i]);
            rezultat.push_back(litera_mica);
        }
    }
return rezultat;
}

int main(){
    string sir = "A man, a plan, a canal: Panama";
    string sir_curat = curata_string(sir);
    if(verifica_palindrom(sir_curat)){
        cout << "e palindrom" << '\n';
    }else{
        cout << "nu e palindrom" << '\n';
    }
    return 0;
}