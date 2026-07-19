#include <iostream>
#include <unordered_map>
using namespace std;

void introducere_string(string& s){
    cout << "Introdu un text" << '\n';
    getline(cin >> ws, s);

    cout << s << '\n';
    
}
void populeaza_unorderedmap(string&s, unordered_map<char, int>& um){
    for(int i=0; i<s.size();i++){
        um[s[i]]++;
    }
}
void afiseaza_tabel(const unordered_map<char, int>& um){
    for(const auto& [caracter, frecventa] : um){
        cout << caracter << "\t\t" << frecventa << "\n";
    }
}
int main(){
    string text = "";
    introducere_string(text);
    unordered_map<char, int> frecventa;
    populeaza_unorderedmap(text, frecventa);
    afiseaza_tabel(frecventa);

    return 0;
}