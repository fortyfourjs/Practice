#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int elimina_duplicate(vector<int>& v){
    int n = v.size();
    int unic = 1;
    for(int i=1;i<n;i++){
        if(v[i] != v[i-1]){
            v[unic] = v[i];
            unic++;
        }
    }
    v.resize(unic);
    return unic;
}

int main(){
    vector<int> lista_random = {8,5,9,22,53,78,5,7,8,4,9,34,65,34,2,7,9};
    cout << lista_random.size() << '\n';
    sort(lista_random.begin(), lista_random.end());
    for(const auto& elem : lista_random){
        cout << elem << " ";
    }
    cout << '\n';
    reverse(lista_random.begin(), lista_random.end());
    elimina_duplicate(lista_random);
    for(const auto& elem : lista_random){
        cout << elem << " ";
    }

    return 0;
}