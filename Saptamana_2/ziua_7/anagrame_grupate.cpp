#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<vector<string>> verifica_anagrame(vector<string>& cuvinte){
    unordered_map<string, vector<string>> grupuri;
    for(int i=0;i<cuvinte.size();i++){
        string cuvant_curent = cuvinte[i];
        string cuvant_sortat = cuvant_curent;
        sort(cuvant_sortat.begin(), cuvant_sortat.end());
        grupuri[cuvant_sortat].push_back(cuvant_curent);
    }
    vector<vector<string>> rezultat;
    for(const auto& [cheie, lista_de_cuvinte] : grupuri){
        rezultat.push_back(lista_de_cuvinte);
    }
    return rezultat;
}

int main(){

    vector<string> s = {"eat","tea","tan","ate","nat","bat"};
    vector<vector<string>> anagrame = verifica_anagrame(s);
    for(auto grup : anagrame){
        cout << "[ ";
        for(const string& cuvant : grup){
            cout << cuvant << " ";
        }
        cout << " ]";
    }

    return 0;
}