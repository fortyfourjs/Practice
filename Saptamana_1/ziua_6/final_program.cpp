#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int sterge_dubluri(vector<int>& v){
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
double media(vector<int>& v){
    double suma=0;
    for(int i=0;i<v.size();i++){
        suma += v[i];
    }
return suma/v.size();
}

vector<int> curata_string(string s){
    vector<int> cifre = {};
    for(int i=0;i<s.size();i++){
        if(isdigit(s[i])){
            cifre.push_back(s[i] - '0');
        }
    }
return cifre;
}

int main(){
    string s = "3,1,5,8,7,8,1";
    cout << s;
    cout << '\n';
vector<int> cifre_string = curata_string(s);
for(int n : cifre_string){
    cout << n << " ";
}
cout << '\n';
sort(cifre_string.begin(), cifre_string.end());
for(int n : cifre_string){
    cout << n << " ";
}
cout << '\n';
sterge_dubluri(cifre_string);
for(int n : cifre_string){
    cout << n << " ";
}
cout << '\n';
cout << "Media=" << media(cifre_string) << "\n";

return 0;
}