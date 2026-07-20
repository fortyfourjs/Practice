#include <iostream>
#include <unordered_map>
using namespace std;

void introducere_string(string& s1, string& s2){
    cout << "Introdu primul cuvant" << "\n";
    getline(cin>>ws, s1);
    cout << "Introdu al doilea cuvant" << "\n";
    getline(cin>>ws, s2);
}

bool verifica_anagram(string& s1, string& s2, unordered_map<char, int> hashmap){
    if(s1.size() != s2.size()){
        return false;
    }
    for(int i=0;i<s1.size();i++){
        hashmap[s1[i]]++;
    }
    for(int i=0;i<s2.size();i++){
            hashmap[s2[i]]--;
        }
   
    for(const auto& [caracter, frecventa] : hashmap){
        if(frecventa != 0){
            return false;
        }
    }
return true;
    
}

int main(){
    string s1 = "";
    string s2 = "";
    introducere_string(s1, s2);
    unordered_map<char, int> hashmap;
    if(verifica_anagram(s1, s2, hashmap)){
        cout << "ANAGRAM" << '\n';
    }else{
        cout << "NOT ANAGRAM" << '\n';
    }
    return 0;
}