#include <iostream>
#include <string>
using namespace std;

int vocale(string& s){
    int n = s.length();
    int count = 0;
    for(int i=0;i<n;i++){
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
        count++;
    }
return count;
}

int main(){
    string s;
    cin >> s;
    int v = vocale(s);

    cout << v << "\n";
return 0;
}