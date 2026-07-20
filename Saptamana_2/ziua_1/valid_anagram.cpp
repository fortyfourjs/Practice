#include <iostream>
#include <unordered_map>
using namespace std;

void populeaza_hashmap(string& s, unordered_map<char, int>& hashmap){
    for(int i=0; i<s.size();i++){
        hashmap[s[i]]++;
    }
}

void introducere_string(string& s1, string& s2){
    cout << "introdu primul cuvant" << "\n";
    getline(cin>>ws, s1);
    cout << "introdu al doilea cuvant" << "\n";
    getline(cin>>ws, s2);
    
}
int main(){
    string s1 = "";
    string s2 = "";
    introducere_string(s1, s2);
    cout << s1 << " " << s2 << '\n';
    unordered_map<char, int> hm_s1;
    populeaza_hashmap(s1, hm_s1);
    unordered_map<char, int> hm_s2;
    populeaza_hashmap(s2, hm_s2);
    if(hm_s1 == hm_s2){
        cout << "ANAGRAM" << '\n';
    }

    return 0;
    



}